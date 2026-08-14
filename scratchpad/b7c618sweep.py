"""Systematic product sweep for func_ov002_0207c618: parameter width, callee
blend width, where the narrowing happens, and how each call receives the track.
"""
import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0207c618"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
best = [999, None, None]


def score(tag, s):
    p = "build/try/b7c618_sweep.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        return
    if len(mine) != len(orig):
        return
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    if n < best[0]:
        best[0] = n
        best[1] = tag
        best[2] = s
        print("%-46s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)


PARAM = ["int", "short"]
ACCB = ["int", "short", "u16"]
SEEKT = ["u16", "int"]
NARROW = ["local", "inline", "none"]
TRACK1 = ["t", "(u16)nTrack"]
TRACK2 = ["t", "(u16)nTrack"]

count = 0
for pw, ab, st, nw, t1, t2 in itertools.product(PARAM, ACCB, SEEKT, NARROW,
                                                TRACK1, TRACK2):
    if pw == "short" and nw == "local":
        continue
    if nw == "none":
        blend = "nBlend"
        decl = "    int nTrack;\n"
    elif nw == "local":
        blend = "nB"
        decl = "    short nB = (short)nBlend;\n    int nTrack;\n"
    else:
        blend = "(short)nBlend"
        decl = "    int nTrack;\n"
    src = ("typedef unsigned short u16;\n\n"
           "extern void func_0202accc(void *pAnim, u16 nTrack, void *pTable,"
           " %s nBlend);\n"
           "extern void func_01fff774(void *pAnim, %s nTrack, int nFrame);\n\n"
           "void func_ov002_0207c618(short *pAnim, %s nBlend, int nFrame) {\n"
           "%s\n"
           "    for (nTrack = 0; nTrack < 5; nTrack++) {\n"
           "        u16 t = (u16)nTrack;\n\n"
           "        if (pAnim[t + 0x70] > 0) {\n"
           "            func_0202accc(pAnim, %s, pAnim + 0x70, %s);\n"
           "            func_01fff774(pAnim, %s, nFrame);\n"
           "        }\n    }\n}\n"
           % (ab, st, pw, decl, t1, blend, t2))
    tag = "p=%s acc=%s seek=%s nar=%s t1=%s t2=%s" % (pw, ab, st, nw, t1, t2)
    score(tag, src)
    count += 1

print("tried %d combinations, best %d bytes: %s" % (count, best[0], best[1]))
