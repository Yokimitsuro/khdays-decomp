"""Body is now identical; only the prologue register order differs. The ROM
materializes pAnim first and narrows the blend last, so the narrowing must come
after the counter in declaration order.
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
BASE = open("build/try/b7c618_h_refresh.c").read()
OLD = "    short nB = (short)nBlend;\n    int nTrack;\n"


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


score("l_nblast", BASE.replace(OLD, "    int nTrack;\n    short nB = (short)nBlend;\n"))
score("m_split", BASE.replace(OLD, "    int nTrack;\n    short nB;\n\n    nB = (short)nBlend;\n"))
score("n_nofirst", BASE.replace(OLD, "    int nTrack;\n    short nB;\n")
      .replace("    for (nTrack = 0;", "    nB = (short)nBlend;\n    for (nTrack = 0;"))
# narrow inline at the call instead of through a local
s = BASE.replace(OLD, "    int nTrack;\n").replace(", nB)", ", (short)nBlend)")
score("o_inline", s)
# same, with the blend parameter already a short
s = BASE.replace(OLD, "    int nTrack;\n").replace(", nB)", ", nBlend)")
score("p_shortparam", s.replace("short *pAnim, int nBlend", "short *pAnim, short nBlend"))
