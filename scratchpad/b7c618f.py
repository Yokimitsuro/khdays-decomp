"""r5/r6/r7 hold blend,nFrame,pAnim in the candidate and nFrame,pAnim,blend in
the ROM: a rotation, which is what one extra value competing in the allocation
order looks like. Sweep candidates for that extra value.
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

HEAD = ("typedef unsigned short u16;\n\n"
        "extern void func_0202accc(void *pAnim, u16 nTrack, void *pTable,"
        " int nBlend);\n"
        "extern void func_01fff774(void *pAnim, u16 nTrack, int nFrame);\n\n"
        "void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame) {\n")


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


LOOP = """
    for (nTrack = 0; nTrack < 5; nTrack++) {
        u16 t = (u16)nTrack;

        if (%s > 0) {
            func_0202accc(pAnim, t, %s, nB);
            func_01fff774(pAnim, (u16)nTrack, nFrame);
        }
    }
}
"""

# an extra local for the table base, bound outside the loop
score("v_tablelocal",
      HEAD + "    short *pTable = pAnim + 0x70;\n"
             "    short nB = (short)nBlend;\n    int nTrack;\n"
      + LOOP % ("pTable[t]", "pTable"))

# the table local declared after the blend
score("w_tablelast",
      HEAD + "    short nB = (short)nBlend;\n    short *pTable = pAnim + 0x70;\n"
             "    int nTrack;\n"
      + LOOP % ("pTable[t]", "pTable"))

# an extra local for the tested entry
score("x_entry",
      HEAD + "    short nB = (short)nBlend;\n    int nTrack;\n"
      + """
    for (nTrack = 0; nTrack < 5; nTrack++) {
        u16 t = (u16)nTrack;
        short nEntry = pAnim[t + 0x70];

        if (nEntry > 0) {
            func_0202accc(pAnim, t, pAnim + 0x70, nB);
            func_01fff774(pAnim, (u16)nTrack, nFrame);
        }
    }
}
""")

# the frame bound to its own local ahead of everything
score("y_framelocal",
      HEAD + "    int nF = nFrame;\n    short nB = (short)nBlend;\n"
             "    int nTrack;\n"
      + (LOOP % ("pAnim[t + 0x70]", "pAnim + 0x70")).replace("nFrame)", "nF)"))

# the animation bound to its own local ahead of everything
score("z_animlocal",
      HEAD + "    short *pA = pAnim;\n    short nB = (short)nBlend;\n"
             "    int nTrack;\n"
      + (LOOP % ("pA[t + 0x70]", "pA + 0x70")).replace("func_0202accc(pAnim",
                                                       "func_0202accc(pA")
      .replace("func_01fff774(pAnim", "func_01fff774(pA"))
