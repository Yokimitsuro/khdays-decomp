"""The ROM interleaves the counter init between the nFrame move and the asr
that completes the blend narrowing, so the counter is initialised before the
blend is narrowed. Only a declaration initialiser plus a do/while can place the
narrowing after the counter init.
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
        "/* Rebind and seek every track that has a table entry. */\n"
        "void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame) {\n")

BODY_DO = """
    do {
        u16 t = (u16)nTrack;

        if (pAnim[t + 0x70] > 0) {
            func_0202accc(pAnim, t, pAnim + 0x70, nB);
            func_01fff774(pAnim, (u16)nTrack, nFrame);
        }
        nTrack++;
    } while (nTrack < 5);
}
"""

BODY_DO_PRE = """
    do {
        u16 t = (u16)nTrack;

        if (pAnim[t + 0x70] > 0) {
            func_0202accc(pAnim, t, pAnim + 0x70, nB);
            func_01fff774(pAnim, (u16)nTrack, nFrame);
        }
    } while (++nTrack < 5);
}
"""

BODY_FOR = """
    for (; nTrack < 5; nTrack++) {
        u16 t = (u16)nTrack;

        if (pAnim[t + 0x70] > 0) {
            func_0202accc(pAnim, t, pAnim + 0x70, nB);
            func_01fff774(pAnim, (u16)nTrack, nFrame);
        }
    }
}
"""


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


D_INIT_FIRST = "    int nTrack = 0;\n    short nB = (short)nBlend;\n"
D_NB_FIRST = "    short nB = (short)nBlend;\n    int nTrack = 0;\n"

score("q_init_do", HEAD + D_INIT_FIRST + BODY_DO)
score("r_init_dopre", HEAD + D_INIT_FIRST + BODY_DO_PRE)
score("s_init_for", HEAD + D_INIT_FIRST + BODY_FOR)
score("t_nb_do", HEAD + D_NB_FIRST + BODY_DO)
score("u_nb_for", HEAD + D_NB_FIRST + BODY_FOR)
