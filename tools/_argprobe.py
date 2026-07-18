"""Parks a +-4 = una instruccion. En vez de adivinar el argumento que falta, ALINEA
   los dos streams y LEE la constante de la instruccion que solo tiene la ROM.
   (Adivinar 0/1/-1 falla en cuanto la constante es 0x14 -- pillado por autotest.)"""
import json, os, re, sys, glob, subprocess, difflib
from concurrent.futures import ThreadPoolExecutor
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = r"E:\KH 3582\decomp"
sys.path.insert(0, os.path.join(ROOT, "tools"))
from match import text_relocs, FLAGS

MWCC = os.path.join(ROOT, "tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
LIC = os.path.join(ROOT, "tools", "mwccarm", "license.dat")
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
TMP = os.path.join(ROOT, "build", "try", "arg2")
os.makedirs(TMP, exist_ok=True)
MD_A = Cs(CS_ARCH_ARM, CS_MODE_ARM)
MD_T = Cs(CS_ARCH_ARM, CS_MODE_THUMB)


def build(cpath, name, thumb, slot):
    o = os.path.join(TMP, "%s_%d.o" % (name, slot))
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    flags = FLAGS + (["-thumb"] if thumb else [])
    r = subprocess.run([MWCC, "-c", *flags, "-o", o, cpath],
                       capture_output=True, text=True, env=env)
    if r.returncode != 0:
        return None
    try:
        return text_relocs(o)
    except Exception:
        return None


def exact(mine, mr, name):
    e = IDX[name]
    orig = bytearray.fromhex(e["hex"])
    if len(mine) != len(orig):
        return False
    orel = {off: s for off, s in e["relocs"]}
    mrel = {off: n for off, (n, _t) in mr.items()}
    m, ob = bytearray(mine), bytearray(orig)
    for off in set(mrel) | set(orel):
        for k in range(4):
            if off + k < len(ob):
                m[off + k] = 0
                ob[off + k] = 0
    return sum(1 for a, b in zip(m, ob) if a != b) == 0 and mrel == orel


def dis(b, thumb):
    md = MD_T if thumb else MD_A
    return [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(b), 0)]


def rom_only(name, mine, thumb):
    """instrucciones que SOLO tiene la ROM (y las que solo tengo yo)"""
    o = dis(bytearray.fromhex(IDX[name]["hex"]), thumb)
    m = dis(mine, thumb)
    ro, mo = [], []
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(a=o, b=m, autojunk=False).get_opcodes():
        if tag in ("delete", "replace"):
            ro += o[i1:i2]
        if tag in ("insert", "replace"):
            mo += m[j1:j2]
    return ro, mo


CONST = re.compile(r"^(mov|movs)\s+\w+,\s*#(-?(?:0x)?[0-9a-fA-F]+)$")
NEG = re.compile(r"^(mvn|mvns)\s+\w+,\s*#(-?(?:0x)?[0-9a-fA-F]+)$")


def wanted_consts(ro):
    out = []
    for ins in ro:
        m = CONST.match(ins)
        if m:
            out.append(m.group(2))
            continue
        m = NEG.match(ins)
        if m:
            v = int(m.group(2), 0)
            out.append(str(~v))
    return out


def calls(src, selfname):
    out = []
    for m in re.finditer(r"\b(func_[0-9a-zA-Z_]+|[A-Z][A-Za-z0-9_]*)\s*\(", src):
        nm = m.group(1)
        if nm == selfname:
            continue
        i = m.end() - 1
        depth, j = 0, i
        while j < len(src):
            if src[j] == "(":
                depth += 1
            elif src[j] == ")":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        if j >= len(src):
            continue
        ls = src.rfind("\n", 0, m.start()) + 1
        if src[ls:m.start()].strip().startswith("extern"):
            continue
        out.append((i, j, nm))
    return out


def split_args(inner):
    parts, depth, cur = [], 0, ""
    for ch in inner:
        if ch == "," and depth == 0:
            parts.append(cur); cur = ""; continue
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        cur += ch
    if cur.strip() or parts:
        parts.append(cur)
    return parts


def work(case):
    name, cpath, mode, delta = case
    src = open(cpath, encoding="utf-8", errors="replace").read()
    body = src[src.index("extern"):] if "extern" in src else src
    th = (mode == "thumb")
    base = build(cpath, name, th, 0)
    if not base:
        return None
    ro, mo = rom_only(name, base[0], th)
    cs = calls(body, name)
    tries = []
    if delta < 0:
        vals = wanted_consts(ro) or ["0"]
        for (a, b, nm) in reversed(cs):
            for v in dict.fromkeys(vals):
                inner = body[a + 1:b]
                sep = ", " if inner.strip() else ""
                tries.append(("+%s -> %s" % (v, nm), body[:b] + sep + v + body[b:]))
    else:
        for (a, b, nm) in reversed(cs):
            parts = split_args(body[a + 1:b])
            if len(parts) >= 2:
                tries.append(("-ultimo arg de %s (%s)" % (nm, parts[-1].strip()),
                              body[:a + 1] + ",".join(parts[:-1]) + body[b:]))
    for k, (label, text) in enumerate(tries):
        p = os.path.join(TMP, "%s_%d.c" % (name, k))
        open(p, "w", encoding="utf-8", newline="\n").write(text)
        r = build(p, name, th, k + 1)
        if r and exact(r[0], r[1], name):
            return (name, cpath, label, text)
    return None


if __name__ == "__main__":
    triage = json.load(open(os.path.join(ROOT, "build", "sweep", "triage", "triage.json")))
    cases = [(r[0], r[1], r[4], r[3]) for r in triage
             if r[2] == "size" and abs(r[3]) == 4 and os.path.exists(r[1])]
    print("parks a +-4:", len(cases))
    hits = []
    with ThreadPoolExecutor(max_workers=10) as ex:
        for i, r in enumerate(ex.map(work, cases)):
            if r:
                hits.append(r)
                print("  HIT %-34s %s" % (r[0], r[2]), file=sys.stderr)
            if (i + 1) % 20 == 0:
                print("  ...%d/%d (%d)" % (i + 1, len(cases), len(hits)), file=sys.stderr)
    print()
    print("=== RESCATADAS: %d / %d ===" % (len(hits), len(cases)))
    for n, c, l, _ in hits:
        print("  %-34s %s" % (n, l))
    json.dump([[n, c, l] for n, c, l, _ in hits], open(os.path.join(TMP, "hits.json"), "w"))
    for n, c, l, t in hits:
        open(os.path.join(TMP, n + ".final.c"), "w", encoding="utf-8", newline="\n").write(t)
