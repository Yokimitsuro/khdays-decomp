"""Disabling copy propagation moves the pointer off r4, and copy propagation is
exactly what erased the plain copies tried earlier. So try copies that
propagation is less likely to see through: casts through other pointer types,
through an integer, and through a union. Placement varies too, since a copy only
matters where it is used.
"""
import sys
import os
import json
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert DECL in BASE

FORMS = {
    "void cast": "    Ov002PanelSession *s2 = (Ov002PanelSession *)(void *)s;\n",
    "u8 cast": "    Ov002PanelSession *s2 = (Ov002PanelSession *)(u8 *)s;\n",
    "int cast": "    Ov002PanelSession *s2 = (Ov002PanelSession *)(int)s;\n",
    "reload global": "    Ov002PanelSession *s2 = data_ov002_0207f620;\n",
    "offset zero": "    Ov002PanelSession *s2 = s + 0;\n",
}


def score(src):
    p = "build/try/b5bff4_hc.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:45]
    n = None
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    sr = "?"
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    return len(code), n, sr


def place(src, where):
    if where == "tail":
        return src.replace(
            "    s->bKind = (u8)nTo;\n    func_ov002_0205b7dc(s->bMode, nTo, 0);",
            "    s2->bKind = (u8)nTo;\n    func_ov002_0205b7dc(s2->bMode, nTo, 0);")
    if where == "case2":
        h, t = src.split("    case 2: {", 1)
        b, r = t.split("    case 3: {", 1)
        return h + "    case 2: {" + b.replace("s->listItems", "s2->listItems") + \
            "    case 3: {" + r
    if where == "case3":
        h, t = src.split("    case 3: {", 1)
        b, r = t.split("    case 4:", 1)
        return h + "    case 3: {" + b.replace("s->listEntries", "s2->listEntries") + \
            "    case 4:" + r
    # everywhere after the classifier call
    h, t = src.split("    switch (nClass) {", 1)
    return h + "    switch (nClass) {" + t.replace("s->", "s2->")


print("%-28s %-8s %-6s %-6s %s" % ("form", "place", "size", "bytes", "s"))
best = (99, None)
for fname, decl in sorted(FORMS.items()):
    for where in ("tail", "case2", "case3", "all"):
        src = place(BASE.replace(DECL, DECL + decl), where)
        size, n, sr = score(src)
        tag = "%s / %s" % (fname, where)
        if size is None:
            print("%-28s %-8s FAIL %s" % (fname, where, sr))
            continue
        mark = ""
        if n == 0:
            mark = "   MATCH"
        elif sr not in ("r4", "?"):
            mark = "   POINTER MOVED"
        print("%-28s %-8s %-6d %-6s %s%s" % (fname, where, size, n, sr, mark))
        if isinstance(n, int) and n < best[0]:
            best = (n, tag)
        if n == 0:
            open("build/try/%s.c" % SYM, "w").write(src)
            print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
