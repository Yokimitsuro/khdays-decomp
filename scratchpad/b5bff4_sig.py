"""The callee signature was the crack on func_ov002_02052024. Here the
classifier's out parameter and return feed both the switch and the column, so
its declared types decide where those values live.
"""
import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0205bff4"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/func_ov002_0205bff4.c").read()

SIG = "extern int func_ov002_0205a3f0(int *pOut, int nCode);"
assert SIG in BASE


def score(tag, sig, extra=None):
    s = BASE.replace(SIG, sig)
    if extra:
        for a, b in extra:
            s = s.replace(a, b)
    p = "build/try/b5bff4_sg.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-26s FAIL" % tag)
        return 9999
    if len(mine) != len(orig):
        print("%-26s SIZE %+d" % (tag, len(mine) - len(orig)))
        return 9999
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-26s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
    return n


RET = {"int": "int", "uint": "unsigned int", "u8": "u8", "u16": "u16"}
P0 = {"intp": "int *pOut", "voidp": "void *pOut", "uintp": "unsigned int *pOut"}
P1 = {"int": "int nCode", "uint": "unsigned int nCode", "u8": "u8 nCode",
      "u16": "u16 nCode"}

for rk, p0k, p1k in itertools.product(RET, P0, P1):
    sig = "extern %s func_ov002_0205a3f0(%s, %s);" % (RET[rk], P0[p0k], P1[p1k])
    extra = []
    if p0k == "voidp":
        extra.append(("func_ov002_0205a3f0(&nColumn,",
                      "func_ov002_0205a3f0((void *)&nColumn,"))
    if rk in ("u8", "u16"):
        extra.append(("    nClass = func_ov002_0205a3f0",
                      "    nClass = (int)func_ov002_0205a3f0"))
    score("%s/%s/%s" % (rk, p0k, p1k), sig, extra)
