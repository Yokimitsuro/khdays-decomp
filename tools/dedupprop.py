# dedupprop.py -- masked-hex twin propagation.
#
# Two functions whose bytes are identical once the reloc'd words are masked out are the same
# code modulo which symbols they reference. If one already has a matched .c, the twin's .c is
# that same source with the reloc symbols substituted in sorted-offset order.
#
# Builds masked_hex -> {done reps, undone twins}, writes each twin's .c from its rep, verifies
# with verify_idx (ARM, then --thumb), keeps the MATCHes and removes the rest. Idempotent.
#
# Usage:  python dedupprop.py [--write]     (default is a dry run)
import json, glob, os, re, subprocess, sys, collections

ROOT = r"E:\KH 3582\decomp"
WRITE = "--write" in sys.argv

idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

def is_nonmatching(path):
    return os.sep + "nonmatching" + os.sep in path


def is_asm(path):
    """An ASM stub -- inline asm or a raw `dcd` blob of the ROM bytes."""
    if os.sep + "asm_stubs" + os.sep in path:
        return True
    try:
        s = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return False
    return "__asm" in s or "asm void" in s or "asm {" in s


# Where each already-carved function lives.
#
# `done` gates who may be a REP. Two kinds of file must never be one:
#   - nonmatching/: a recorded failure, and exactly the kind of function a matched twin can
#     rescue, so it belongs in `attempted` instead;
#   - ASM stubs: propagating one produces another `asm void` + `dcd` blob of the ROM bytes. That
#     is not decompilation, it lands in calls/ where real C lives, and -- worst of all -- a blob
#     ALWAYS verifies, so it would "rescue" a nonmatching file and destroy a real analysis.
#     (2026-07-17: this generated 188 blobs and binned 24 nonmatching write-ups before it was
#     caught. The tell was progress.py's ASM count going UP.)
done, attempted = {}, {}
for p in glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True):
    n = os.path.basename(p)[:-2]
    if is_nonmatching(p):
        attempted[n] = p
    elif not is_asm(p):
        done[n] = p

def masked(e):
    """hex with every reloc'd word zeroed -> identical for twins."""
    b = bytearray.fromhex(e["hex"])
    for off, _sym in e["relocs"]:
        if off + 4 <= len(b):
            b[off:off + 4] = b"\x00\x00\x00\x00"
    return bytes(b).hex()

groups = collections.defaultdict(list)
for name, e in idx.items():
    if not name.startswith("func_"):
        continue
    if e.get("size", 0) < 8:
        continue
    groups[masked(e)].append(name)

cands = []
for mh, names in groups.items():
    if len(names) < 2:
        continue
    reps = [n for n in names if n in done]
    todo = [n for n in names if n not in done]
    if not reps or not todo:
        continue
    # prefer a rep whose reloc count matches (they all should, being twins)
    rep = reps[0]
    for t in todo:
        if len(idx[t]["relocs"]) == len(idx[rep]["relocs"]):
            cands.append((rep, t))

print("groups=%d  candidate twins=%d" % (len(groups), len(cands)))
if not cands:
    sys.exit(0)

def subst(src, rep, twin):
    """rep's source -> twin's, swapping reloc symbols in sorted-offset order + the func name."""
    rs = [s for _o, s in sorted(idx[rep]["relocs"])]
    ts = [s for _o, s in sorted(idx[twin]["relocs"])]
    if len(rs) != len(ts):
        return None
    pairs = []
    seen = set()
    for a, b in zip(rs, ts):
        if a not in seen:
            seen.add(a)
            pairs.append((a, b))
    # name first, then symbols, via placeholders so no substring clobbers another
    pairs.insert(0, (rep, twin))
    out = src
    for i, (a, _b) in enumerate(pairs):
        out = re.sub(r"\b%s\b" % re.escape(a), "\x00PH%d\x00" % i, out)
    for i, (_a, b) in enumerate(pairs):
        out = out.replace("\x00PH%d\x00" % i, b)
    return out

def verify(path, name, thumb):
    cmd = [sys.executable, os.path.join(ROOT, "tools", "verify_idx.py"), path, name]
    if thumb:
        cmd.append("--thumb")
    try:
        r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=180)
        return "MATCH" in (r.stdout or "")
    except Exception:
        return False

matched, failed, rescued = [], [], []
for rep, twin in cands:
    src = open(done[rep], encoding="utf-8", errors="replace").read()
    new = subst(src, rep, twin)
    if new is None:
        continue
    # same dir kind as the rep (auto/ vs calls/), under the twin's own overlay
    m = re.match(r"func_(ov\d+)_", twin)
    ovl = m.group(1) if m else None
    kind = "auto" if not idx[twin]["relocs"] else "calls"
    if ovl:
        d = os.path.join(ROOT, "src", "overlays", ovl, kind)
    else:
        d = os.path.join(ROOT, "src", kind)
    if not os.path.isdir(d):
        continue
    path = os.path.join(d, twin + ".c")
    if os.path.exists(path):
        continue
    tag = "  (rescues a nonmatching/)" if twin in attempted else ""
    if not WRITE:
        print("  would try %-26s <- %s%s" % (twin, rep, tag))
        continue
    open(path, "w", encoding="utf-8", newline="\n").write(new)
    ok = verify(path, twin, False) or verify(path, twin, True)
    if ok:
        matched.append((twin, rep))
        # A matched twin retires any earlier nonmatching/ attempt -- leaving it would claim the
        # function is an unresolvable tie while the byte-exact C sits next to it.
        if twin in attempted:
            os.remove(attempted[twin])
            rescued.append(twin)
        print("  MATCH   %-26s <- %s%s" % (twin, rep, tag))
    else:
        os.remove(path)
        failed.append((twin, rep))

print()
print("matched=%d  failed=%d  rescued-from-nonmatching=%d" % (len(matched), len(failed), len(rescued)))
for t in rescued:
    print("  retired nonmatching/%s.c" % t)
