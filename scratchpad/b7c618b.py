"""The ROM indexes the table with the u16-converted track, not the raw counter:
'add r0, r6, r1, lsl #1' takes r1, the converted value, and the conversion sits
at the top of the loop body ahead of the test.
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


HEAD = """typedef unsigned short u16;

extern void func_0202accc(void *pAnim, u16 nTrack, void *pTable, int nBlend);
extern void func_01fff774(void *pAnim, u16 nTrack, int nFrame);

/* Rebind and seek every track of an animation that has a table entry. */
void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame) {
"""

BODY = """
    for (nTrack = 0; nTrack < 5; nTrack++) {
        u16 t = (u16)nTrack;

        if (pAnim[t + 0x70] %s 0) {
            func_0202accc(pAnim, t, pAnim + 0x70, nB);
            func_01fff774(pAnim, t, nFrame);
        }
    }
}
"""

DECLS = {
    "e_nb_first": "    short nB = (short)nBlend;\n    int nTrack;\n",
    "f_nb_last": "    int nTrack;\n    short nB = (short)nBlend;\n",
    "g_split": "    int nTrack;\n    short nB;\n\n    nB = (short)nBlend;\n",
}
for tag, decl in DECLS.items():
    for cmp_tag, op in [("gt", "> "), ("ge", ">= 1 &&  1 <=")]:
        if cmp_tag == "ge":
            continue
        score(tag, HEAD + decl + BODY % op.strip())
