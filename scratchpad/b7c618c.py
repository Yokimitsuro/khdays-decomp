"""The ROM re-derives the narrowed track before the second call instead of
sharing it, the same lever proved on func_ov002_02052024. Vary how each call
site receives it.
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


def build(decl, idx_expr, a1, a2, blend, seek="u16"):
    return ("typedef unsigned short u16;\n\n"
            "extern void func_0202accc(void *pAnim, u16 nTrack, void *pTable,"
            " int nBlend);\n"
            "extern void func_01fff774(void *pAnim, %s nTrack, int nFrame);\n\n"
            "/* Rebind and seek every track that has a table entry. */\n"
            "void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame) {\n"
            "%s"
            "\n"
            "    for (nTrack = 0; nTrack < 5; nTrack++) {\n"
            "        u16 t = (u16)nTrack;\n"
            "\n"
            "        if (pAnim[%s + 0x70] > 0) {\n"
            "            func_0202accc(pAnim, %s, pAnim + 0x70, %s);\n"
            "            func_01fff774(pAnim, %s, nFrame);\n"
            "        }\n"
            "    }\n"
            "}\n" % (seek, decl, idx_expr, a1, blend, a2))


D = "    short nB = (short)nBlend;\n    int nTrack;\n"

score("h_refresh", build(D, "t", "t", "(u16)nTrack", "nB"))
score("i_bothfresh", build(D, "t", "(u16)nTrack", "(u16)nTrack", "nB"))
score("j_nolocal", build(D, "(u16)nTrack", "(u16)nTrack", "(u16)nTrack", "nB"))
score("k_seekint", build(D, "t", "t", "t", "nB", "int"))
