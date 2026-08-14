"""Exact size and instruction count; only the evaluation order inside the
offset differs. The ROM starts the remainder term before finishing the quotient
term, so split them into named locals and vary which comes first.
"""
import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_020576d8"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

DECL_OLD = "    u8 *p;\n    int nOffset;\n    int i;\n"
OFF_OLD = ("    nOffset = nRow * 4 + (nStart / 8) * 0x20 + (nStart % 8) / 2;\n"
           "    p = pDst + nOffset;\n")
assert DECL_OLD in BASE and OFF_OLD in BASE

VARIANTS = {
    "half_first": ("    u8 *p;\n    int nHalf;\n    int nTile;\n"
                   "    int nOffset;\n    int i;\n",
                   "    nHalf = (nStart % 8) / 2;\n"
                   "    nTile = nStart / 8;\n"
                   "    nOffset = nRow * 4 + nTile * 0x20 + nHalf;\n"
                   "    p = pDst + nOffset;\n"),
    "tile_first": ("    u8 *p;\n    int nTile;\n    int nHalf;\n"
                   "    int nOffset;\n    int i;\n",
                   "    nTile = nStart / 8;\n"
                   "    nHalf = (nStart % 8) / 2;\n"
                   "    nOffset = nRow * 4 + nTile * 0x20 + nHalf;\n"
                   "    p = pDst + nOffset;\n"),
    "half_expr": ("    u8 *p;\n    int nHalf;\n    int nOffset;\n    int i;\n",
                  "    nHalf = (nStart % 8) / 2;\n"
                  "    nOffset = nRow * 4 + (nStart / 8) * 0x20 + nHalf;\n"
                  "    p = pDst + nOffset;\n"),
    "tile_expr": ("    u8 *p;\n    int nTile;\n    int nOffset;\n    int i;\n",
                  "    nTile = nStart / 8;\n"
                  "    nOffset = nRow * 4 + nTile * 0x20 + (nStart % 8) / 2;\n"
                  "    p = pDst + nOffset;\n"),
    "half_term_first": ("    u8 *p;\n    int nOffset;\n    int i;\n",
                        "    nOffset = nRow * 4 + (nStart % 8) / 2"
                        " + (nStart / 8) * 0x20;\n"
                        "    p = pDst + nOffset;\n"),
    "shift_form": ("    u8 *p;\n    int nOffset;\n    int i;\n",
                   "    nOffset = nRow * 4 + nStart / 8 * 0x20"
                   " + nStart % 8 / 2;\n"
                   "    p = pDst + nOffset;\n"),
}

best = [999, None]
for tag, (decl, off) in VARIANTS.items():
    s = BASE.replace(DECL_OLD, decl).replace(OFF_OLD, off)
    p = "build/try/b576d8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-18s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-18s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off2 in set(orel) | set(mrel):
        for k in range(4):
            if off2 + k < len(a):
                a[off2 + k] = 0
                b[off2 + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-18s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
