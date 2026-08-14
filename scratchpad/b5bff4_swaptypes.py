"""Follows directly from the new lever. Pointer-typed values land on r4 and
integer-typed ones on r7. The ROM has nClass on r4 and the session on r8, which
is the opposite assignment to mine. So swap the TYPES: hold nClass as a pointer
and the session as an integer, and see where each lands. Casts are free, so the
emitted instructions should not change.
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
SDECL = "    Ov002PanelSession *s = data_ov002_0207f620;"
KDECL = "    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);"
assert SDECL in BASE and KDECL in BASE


def score(src):
    p = "build/try/b5bff4_st.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, "?", str(ex).split("\n")[0][:45]
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
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    sr = kr = "?"
    for t in ins[:14]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and sr == "?":
            sr = m.group(1)
    for t in ins:
        m = re.match(r"^cmp (r\w+), #5$", t)
        if m:
            kr = m.group(1)
            break
    return len(code), n, "s=%s k=%s" % (sr, kr), None


def make(sint, kptr):
    src = BASE
    if sint:
        src = src.replace(SDECL, "    int s = (int)data_ov002_0207f620;")
        src = re.sub(r"\bs->", "((Ov002PanelSession *)s)->", src)
    if kptr:
        src = src.replace(
            KDECL if not sint else
            "    int nClass = func_ov002_0205a3f0(&nColumn, "
            "((Ov002PanelSession *)s)->bMode);",
            "    void *nClass = (void *)func_ov002_0205a3f0(&nColumn, %s);"
            % ("((Ov002PanelSession *)s)->bMode" if sint else "s->bMode"))
        src = src.replace("    switch (nClass) {", "    switch ((int)nClass) {", 1)
        src = src.replace("nClass = nTo + nColumn * 6;",
                          "nClass = (void *)(nTo + nColumn * 6);")
        src = src.replace("(u16)nClass", "(u16)(int)nClass")
        src = src.replace("nTo, nClass, 1, 1, 1", "nTo, (int)nClass, 1, 1, 1")
        src = src.replace("s->bKey = (u8)nClass;", "s->bKey = (u8)(int)nClass;")
        src = src.replace("((Ov002PanelSession *)s)->bKey = (u8)nClass;",
                          "((Ov002PanelSession *)s)->bKey = (u8)(int)nClass;")
    return src


print("ROM: s=r8 k=r4")
print("%-30s %-6s %-6s %s" % ("variant", "size", "bytes", "map"))
best = (999, None)
for sint, kptr in itertools.product((0, 1), repeat=2):
    src = make(sint, kptr)
    size, n, m, err = score(src)
    tag = "s=%s nClass=%s" % ("int" if sint else "ptr", "ptr" if kptr else "int")
    if err:
        print("%-30s FAIL %s" % (tag, err))
        continue
    mark = "   MATCH" if n == 0 else ""
    print("%-30s %-6d %-6s %s%s" % (tag, size, n, m, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
