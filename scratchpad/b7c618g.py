"""Pointer-type and narrowing-type axes for func_ov002_0207c618."""
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

DECL = ("typedef unsigned short u16;\n\n"
        "extern void func_0202accc(void *pAnim, u16 nTrack, void *pTable,"
        " int nBlend);\n"
        "extern void func_01fff774(void *pAnim, u16 nTrack, int nFrame);\n\n")


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


# nB typed int rather than short
score("a2_intnb", DECL +
      "void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame) {\n"
      "    int nB = (short)nBlend;\n    int nTrack;\n\n"
      "    for (nTrack = 0; nTrack < 5; nTrack++) {\n"
      "        u16 t = (u16)nTrack;\n\n"
      "        if (pAnim[t + 0x70] > 0) {\n"
      "            func_0202accc(pAnim, t, pAnim + 0x70, nB);\n"
      "            func_01fff774(pAnim, (u16)nTrack, nFrame);\n"
      "        }\n    }\n}\n")

# the animation as a byte pointer with byte offsets
score("b2_bytes", DECL +
      "void func_ov002_0207c618(char *pAnim, int nBlend, int nFrame) {\n"
      "    short nB = (short)nBlend;\n    int nTrack;\n\n"
      "    for (nTrack = 0; nTrack < 5; nTrack++) {\n"
      "        u16 t = (u16)nTrack;\n\n"
      "        if (*(short *)(pAnim + t * 2 + 0xe0) > 0) {\n"
      "            func_0202accc(pAnim, t, pAnim + 0xe0, nB);\n"
      "            func_01fff774(pAnim, (u16)nTrack, nFrame);\n"
      "        }\n    }\n}\n")

# a struct with the table as a member array
score("c2_struct", DECL +
      "typedef struct {\n    char pad0000[0xe0];\n    short anTracks[5];\n"
      "} Ov002Anim;\n\n"
      "void func_ov002_0207c618(Ov002Anim *pAnim, int nBlend, int nFrame) {\n"
      "    short nB = (short)nBlend;\n    int nTrack;\n\n"
      "    for (nTrack = 0; nTrack < 5; nTrack++) {\n"
      "        u16 t = (u16)nTrack;\n\n"
      "        if (pAnim->anTracks[t] > 0) {\n"
      "            func_0202accc(pAnim, t, pAnim->anTracks, nB);\n"
      "            func_01fff774(pAnim, (u16)nTrack, nFrame);\n"
      "        }\n    }\n}\n")

# the narrowing written as a mask-and-sign rather than a cast
score("d2_void", DECL +
      "void func_ov002_0207c618(void *pAnim, int nBlend, int nFrame) {\n"
      "    short nB = (short)nBlend;\n    int nTrack;\n\n"
      "    for (nTrack = 0; nTrack < 5; nTrack++) {\n"
      "        u16 t = (u16)nTrack;\n\n"
      "        if (((short *)pAnim)[t + 0x70] > 0) {\n"
      "            func_0202accc(pAnim, t, (short *)pAnim + 0x70, nB);\n"
      "            func_01fff774(pAnim, (u16)nTrack, nFrame);\n"
      "        }\n    }\n}\n")
