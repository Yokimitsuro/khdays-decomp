"""Dichotomy: pDst added last gives the ROM's final add but a two-register
frame; folded early gives the ROM's four-register frame but one instruction
short. The ROM's r5 holds the aligned value across the divisions, so bind that
and see whether the pressure and the association can hold at the same time.
"""
import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_020576d8"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/b576d8_flat.c").read()

HEAD_OLD = ("    int nAligned = ((nPad + nWidth + 7) / 8) * 8;\n"
            "    int nStart = nAligned - (nRight + nPad + 1);\n")
assert HEAD_OLD in BASE
PTR_OLD = ("    p = pDst + nRow * 4 + (nStart / 8) * 0x20"
           " + (nStart % 8) / 2;\n")
assert PTR_OLD in BASE

HEADS = {
    "two_locals": HEAD_OLD,
    "one_expr": "    int nStart = ((nPad + nWidth + 7) / 8) * 8"
                " - (nRight + nPad + 1);\n",
    "sum_local": "    int nSum = nPad + nWidth + 7;\n"
                 "    int nStart = nSum / 8 * 8 - (nRight + nPad + 1);\n",
}
PTRS = {
    "folded": PTR_OLD,
    "paren": "    p = pDst + (nRow * 4 + (nStart / 8) * 0x20"
             " + (nStart % 8) / 2);\n",
    "index": "    p = &pDst[nRow * 4 + (nStart / 8) * 0x20"
             " + (nStart % 8) / 2];\n",
}

best = [999, None]
for hk, pk in itertools.product(HEADS, PTRS):
    s = BASE.replace(HEAD_OLD, HEADS[hk]).replace(PTR_OLD, PTRS[pk])
    p = "build/try/b576d8_sweep.c"
    open(p, "w").write(s)
    tag = "%s/%s" % (hk, pk)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-24s FAIL" % tag)
        continue
    ins = list(md.disasm(bytes(mine), 0))
    push = ins[0].op_str if ins else ""
    if len(mine) != len(orig):
        print("%-24s SIZE %+d push=%s" % (tag, len(mine) - len(orig), push))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-24s bytes=%d push=%s%s" % (tag, n, push,
                                        "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
