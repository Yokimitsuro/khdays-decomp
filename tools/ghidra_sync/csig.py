"""Parse matched .c files into a Ghidra sync spec: prototype, plate comment, local structs.

    python tools/ghidra_sync/csig.py <listfile> [out.json]

<listfile> holds one source path per line (relative to the repo root), e.g. the .c files a
batch of contribution PRs added:  git diff --name-status BASE HEAD -- src libs | ...
The default output is build/ghidra_sync_spec.json, which tools/ghidra_sync/SyncContribSpec.py
applies inside Ghidra (add tools/ghidra_sync to Ghidra's script directories and run it).
"""
import re, sys, os, json
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.chdir(ROOT)

SCALARS = {
    "unsigned char": "u8", "signed char": "s8", "char": "char",
    "unsigned short": "u16", "signed short": "s16", "short": "s16", "unsigned short int": "u16", "short int": "s16",
    "unsigned int": "u32", "signed int": "s32", "int": "s32", "unsigned": "u32", "unsigned long": "u32", "long": "s32", "signed long": "s32",
    "unsigned long long": "u64", "signed long long": "s64", "long long": "s64",
    "void": "void", "float": "float", "double": "double",
    "u8": "u8", "s8": "s8", "u16": "u16", "s16": "s16", "u32": "u32", "s32": "s32", "u64": "u64", "s64": "s64",
    "fx32": "fx32", "fx16": "fx16", "fx64": "fx64", "fx64c": "fx64", "BOOL": "BOOL", "vu32": "vu32", "vu16": "vu16", "vu8": "vu8",
    "size_t": "u32", "uint": "u32", "byte": "u8", "bool": "u8",
}

def strip_comments(s):
    s = re.sub(r"/\*.*?\*/", lambda m: " " * 0 + "\n" * m.group(0).count("\n"), s, flags=re.S)
    s = re.sub(r"//[^\n]*", "", s)
    return s

def leading_comment(s):
    m = re.match(r"\s*/\*(.*?)\*/", s, re.S)
    if not m:
        return ""
    body = m.group(1)
    lines = [re.sub(r"^\s*\*\s?", "", l).rstrip() for l in body.strip("\n").split("\n")]
    text = "\n".join(lines).strip()
    return text

def parse_type(txt, typedefs):
    """'const struct Foo *' -> (base, ptr, const). base is 'struct Foo' or a scalar key."""
    t = txt.strip()
    t = re.sub(r"\s+", " ", t)
    const = False
    words = t.replace("*", " * ").split()
    ptr = words.count("*")
    words = [w for w in words if w != "*"]
    if "const" in words:
        const = True
        words = [w for w in words if w != "const"]
    words = [w for w in words if w not in ("volatile", "register", "static", "inline", "extern")]
    if not words:
        return None
    if words[0] == "struct" or words[0] == "union":
        if len(words) != 2:
            return None
        return ("struct " + words[1], ptr, const)
    base = " ".join(words)
    if base in SCALARS:
        base = SCALARS[base]
    elif base in typedefs:
        base = typedefs[base]
    else:
        base = "type " + base   # a typedef name we don't know (VecFx32, a struct alias...)
    return (base, ptr, const)

def parse_decl(decl, typedefs):
    """one declarator 'TYPE NAME[N] : BITS' -> dict or None"""
    d = decl.strip()
    if not d:
        return None
    # function pointer: TYPE (*name)(...)
    m = re.match(r"^(.*?)\(\s*\*\s*(\w+)\s*\)\s*\(.*\)$", d, re.S)
    if m:
        return {"base": "funcptr", "ptr": 1, "name": m.group(2), "array": [], "bits": None, "const": False}
    bits = None
    m = re.match(r"^(.*?):\s*(\d+)$", d, re.S)
    if m:
        d, bits = m.group(1).strip(), int(m.group(2))
    dims = []
    while True:
        m = re.match(r"^(.*)\[\s*([^\]]*?)\s*\]$", d, re.S)
        if not m:
            break
        d = m.group(1).strip()
        dims.insert(0, m.group(2))
    m = re.match(r"^(.*?)([\w]+)$", d, re.S)
    if not m:
        return None
    ty, name = m.group(1), m.group(2)
    pt = parse_type(ty, typedefs)
    if pt is None:
        return None
    return {"base": pt[0], "ptr": pt[1], "const": pt[2], "name": name, "array": dims, "bits": bits}

def eval_dim(x, defines):
    x = x.strip()
    if not x:
        return None
    try:
        return int(eval(x, {"__builtins__": {}}, dict(defines)))
    except Exception:
        return None

def parse_file(path):
    raw = open(path, encoding="utf-8", errors="replace").read()
    plate = leading_comment(raw)
    code = strip_comments(raw)
    defines = {}
    for m in re.finditer(r"^\s*#\s*define\s+(\w+)\s+([^\n]+)$", code, re.M):
        v = eval_dim(m.group(2), defines)
        if v is not None:
            defines[m.group(1)] = v
    code_nopp = re.sub(r"^\s*#[^\n]*$", "", code, flags=re.M)
    typedefs = {}
    for m in re.finditer(r"^\s*typedef\s+[^;{}]*?\(\s*\*\s*(\w+)\s*\)\s*\([^;]*?\)\s*;", code_nopp, re.M | re.S):
        typedefs[m.group(1)] = "funcptr"
    for m in re.finditer(r"^\s*typedef\s+([^;{}()]+?)\s+(\w+)\s*;", code_nopp, re.M):
        pt = parse_type(m.group(1), typedefs)
        if pt and pt[1] == 0 and not pt[0].startswith("type "):
            typedefs[m.group(2)] = pt[0]
        elif pt and pt[0].startswith("struct "):
            typedefs[m.group(2)] = pt[0]
    # struct definitions (no nested braces)
    structs = []
    aliases = {}
    for m in re.finditer(r"(typedef\s+)?struct\s+(\w+)?\s*\{([^{}]*)\}\s*(\w+)?\s*;", code_nopp, re.S):
        tag, body, alias = m.group(2), m.group(3), m.group(4)
        name = tag or alias
        if not name:
            continue
        if alias and tag and alias != tag:
            aliases[alias] = "struct " + tag
            typedefs[alias] = "struct " + tag
        if alias and not tag:
            typedefs[alias] = "struct " + alias
        # canonical name from a comment right before the struct: /* Ov022Actor */ or /* Ov022X: ... */
        pre = raw[:raw.find(body[:40])] if body.strip() else ""
        canon = None
        cm = re.findall(r"/\*\s*([A-Z]\w+)(?::| --|\s*\*/)", pre[-400:])
        if cm:
            cand = cm[-1]
            if cand != name and re.match(r"^(Ov\d+|Nitro|NNS|Coll|Hit|Vec|Mtx|G3|OS|SND|Player)", cand):
                canon = cand
        fields = []
        ok = True
        # offset comments per field from the raw text of this struct body
        rawbody = ""
        rm = re.search(r"struct\s+" + (re.escape(tag) if tag else "") + r"\s*\{(.*?)\}\s*" + (re.escape(alias) if alias else "") + r"\s*;", raw, re.S)
        if rm:
            rawbody = rm.group(1)
        offs = {}
        for line in rawbody.split("\n"):
            om = re.search(r"/\*\s*0x([0-9a-fA-F]+)", line)
            nm = re.search(r"\b(\w+)\s*(?:\[[^\]]*\])*\s*(?::\s*\d+)?\s*;", strip_comments(line))
            if om and nm:
                offs[nm.group(1)] = int(om.group(1), 16)
        for decl in body.split(";"):
            decl = decl.strip()
            if not decl:
                continue
            if "{" in decl or "}" in decl:
                ok = False; break
            # multiple declarators: TYPE a, b;
            parts = [decl]
            if "," in decl and "(" not in decl:
                head = decl
                mm = re.match(r"^(.*?)\s*(\**\s*\w+(?:\s*\[[^\]]*\])*(?:\s*:\s*\d+)?(?:\s*,\s*\**\s*\w+(?:\s*\[[^\]]*\])*(?:\s*:\s*\d+)?)+)$", decl, re.S)
                if mm:
                    ty = mm.group(1)
                    parts = [ty + " " + p.strip() for p in mm.group(2).split(",")]
            for p in parts:
                f = parse_decl(p, typedefs)
                if f is None:
                    ok = False; break
                dims = [eval_dim(x, defines) for x in f["array"]]
                if any(v is None for v in dims):
                    ok = False; break
                f["array"] = dims
                f["off"] = offs.get(f["name"])
                fields.append(f)
            if not ok:
                break
        structs.append({"name": name, "fields": fields, "ok": ok, "canon": canon})
    # the function definition
    stem = os.path.splitext(os.path.basename(path))[0]
    fm = None
    for m in re.finditer(r"^([^\n;{}]*?)\b" + re.escape(stem) + r"\s*\(([^)]*)\)\s*\{", code_nopp, re.M):
        head = m.group(1)
        if "extern" in head:
            continue
        fm = m
        break
    proto = None
    if fm:
        rt = parse_type(fm.group(1), typedefs)
        params = []
        ptxt = fm.group(2).strip()
        pok = True
        if ptxt and ptxt != "void":
            depth = 0; cur = ""; items = []
            for ch in ptxt:
                if ch == "(": depth += 1
                if ch == ")": depth -= 1
                if ch == "," and depth == 0:
                    items.append(cur); cur = ""
                else:
                    cur += ch
            items.append(cur)
            for i, it in enumerate(items):
                it = it.strip()
                if it == "...":
                    pok = False; break
                f = parse_decl(it, typedefs)
                if f is None:
                    # unnamed parameter: just a type
                    pt = parse_type(it, typedefs)
                    if pt is None:
                        pok = False; break
                    f = {"base": pt[0], "ptr": pt[1], "const": pt[2], "name": "param_%d" % (i + 1), "array": [], "bits": None}
                if f["array"]:
                    f["ptr"] += 1; f["array"] = []
                params.append(f)
        if rt is not None and pok:
            proto = {"ret": {"base": rt[0], "ptr": rt[1]}, "params": params}
    return {"path": path, "name": stem, "plate": plate, "structs": structs, "proto": proto, "typedefs": typedefs}

def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    files = [l.strip() for l in open(sys.argv[1], encoding="utf-8") if l.strip()]
    outpath = sys.argv[2] if len(sys.argv) > 2 else os.path.join(ROOT, "build", "ghidra_sync_spec.json")
    out = []
    bad = 0
    for f in files:
        try:
            out.append(parse_file(f))
        except Exception as e:
            bad += 1
            print("FAIL", f, e)
    json.dump(out, open(outpath, "w", encoding="utf-8"), indent=0)
    np = sum(1 for o in out if o["proto"])
    ns = sum(len([s for s in o["structs"] if s["ok"]]) for o in out)
    nb = sum(len([s for s in o["structs"] if not s["ok"]]) for o in out)
    print("files", len(out), "with proto", np, "structs ok", ns, "structs skipped", nb, "parse failures", bad)

if __name__ == "__main__":
    main()
