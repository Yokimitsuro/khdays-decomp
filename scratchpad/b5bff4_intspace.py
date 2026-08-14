"""Holding the session as an integer moves it from r4 to r7 at the correct size.
That is a new lever, so search the space it opens: integer-held session crossed
with the declaration position, the case 2 index order, the const global, and
whether nClass is also retyped. Looking for r8, or for fewer than 67 bytes.
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
GLOB = "extern Ov002PanelSession *data_ov002_0207f620;"
CGLOB = "extern Ov002PanelSession *const data_ov002_0207f620;"
OLD = "    Ov002PanelSession *s = data_ov002_0207f620;"
C2_NEWOLD = """        int nNew = nTo + nColumn * 6;
        int nOld = nFrom + nColumn * 6;
"""
C2_OLDNEW = """        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
"""
assert OLD in BASE and C2_NEWOLD in BASE


def score(src):
    p = "build/try/b5bff4_is.c"
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


def build(intty, pos, c2, cg):
    src = BASE
    if cg:
        src = src.replace(GLOB, CGLOB)
    if c2:
        src = src.replace(C2_NEWOLD, C2_OLDNEW)
    if intty:
        src = src.replace(OLD, "    %s s = (%s)data_ov002_0207f620;" % (intty, intty))
        src = re.sub(r"\bs->", "((Ov002PanelSession *)s)->", src)
        decl = "    %s s = (%s)data_ov002_0207f620;" % (intty, intty)
    else:
        decl = OLD
    if pos == 1:
        src = src.replace("    int nColumn;\n    int nTag;\n" + decl + "\n",
                          decl + "\n    int nColumn;\n    int nTag;\n")
    elif pos == 2:
        src = src.replace("    int nColumn;\n    int nTag;\n" + decl + "\n",
                          "    int nColumn;\n" + decl + "\n    int nTag;\n")
    return src


print("%-40s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
best = (999, None)
seen = {}
for intty in (None, "int", "unsigned int", "long"):
    for pos in (0, 1, 2):
        for c2 in (0, 1):
            for cg in (0, 1):
                src = build(intty, pos, c2, cg)
                size, n, sr = score(src)
                tag = "%s pos=%d c2=%d const=%d" % (intty or "pointer", pos, c2, cg)
                if size is None:
                    continue
                if n is None:
                    continue
                seen[tag] = (n, sr)
                if n < best[0]:
                    best = (n, tag)
                    print("%-40s %-6d %-6s s=%s   NEW BEST" % (tag, size, n, sr))
                if sr == "r8":
                    print("%-40s %-6d %-6s s=r8   POINTER ON r8" % (tag, size, n))
                if n == 0:
                    open("build/try/%s.c" % SYM, "w").write(src)
                    print("PROMOTED " + tag)
print()
regs = {}
for tag, (n, sr) in seen.items():
    regs.setdefault(sr, []).append(n)
print("registers reached and their best byte counts:")
for sr in sorted(regs):
    print("   s=%-4s best=%d over %d variants" % (sr, min(regs[sr]), len(regs[sr])))
print("best overall: %s bytes  %s" % best)
