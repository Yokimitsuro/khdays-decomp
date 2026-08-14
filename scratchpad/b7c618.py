"""func_ov002_0207c618: the ROM normalizes the blend at entry (lsl/asr into a
callee-saved register) and the candidate does not, because a short passed to a
short parameter needs no conversion. That points at an int parameter here.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0207c618"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

ACC_SHORT = "void *pTable, short nBlend);"
ACC_INT = "void *pTable, int nBlend);"


def score(tag, s):
    p = "build/try/b7c618_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-14s FAIL" % tag)
        return
    if len(mine) != len(orig):
        print("%-14s SIZE %d (%+d)" % (tag, len(mine), len(mine) - len(orig)))
        return
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-14s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)


# the bind takes an int blend, so the short parameter normalizes at entry
score("a_accint", BASE.replace(ACC_SHORT, ACC_INT))

# same, with the track held as an unsigned short variable
s = BASE.replace(ACC_SHORT, ACC_INT).replace("    int nTrack;\n",
                                             "    int nTrack;\n    u16 t;\n")
s = s.replace("(u16)nTrack", "t").replace("        if (pAnim",
                                          "        t = (u16)nTrack;\n        if (pAnim")
score("b_track", s)

# the blend as an int parameter narrowed once by an explicit local
s = BASE.replace(ACC_SHORT, ACC_INT)
s = s.replace("short nBlend, int nFrame", "int nBlend, int nFrame")
s = s.replace("    int nTrack;\n", "    int nTrack;\n    short nB = (short)nBlend;\n")
score("c_localshort", s.replace(", nBlend);", ", nB);"))

# a while loop instead of a for, blend short, bind int
s = BASE.replace(ACC_SHORT, ACC_INT)
s = s.replace("    for (nTrack = 0; nTrack < 5; nTrack++) {",
              "    nTrack = 0;\n    do {")
s = s.replace("        }\n    }\n}", "        }\n        nTrack++;\n    } while (nTrack < 5);\n}")
score("d_dowhile", s)
