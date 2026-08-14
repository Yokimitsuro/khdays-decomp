"""The named offset local gets the ROM's association, pDst added last, but drops
the frame from four pushed registers to two. Get the same association from
parentheses inside one expression instead.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
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
DECL_NEW = "    u8 *p;\n    int i;\n"

FORMS = {
    "paren_all": "    p = pDst + (nRow * 4 + (nStart / 8) * 0x20"
                 " + (nStart % 8) / 2);\n",
    "paren_tail": "    p = pDst + nRow * 4 + ((nStart / 8) * 0x20"
                  " + (nStart % 8) / 2);\n",
    "flat": "    p = pDst + nRow * 4 + (nStart / 8) * 0x20"
            " + (nStart % 8) / 2;\n",
    "paren_rowfirst": "    p = pDst + (nRow * 4 + ((nStart / 8) * 0x20"
                      " + (nStart % 8) / 2));\n",
    "cast": "    p = (u8 *)((int)pDst + (nRow * 4 + (nStart / 8) * 0x20"
            " + (nStart % 8) / 2));\n",
}

best = [999, None]
for tag, form in FORMS.items():
    s = BASE.replace(DECL_OLD, DECL_NEW).replace(OFF_OLD, form)
    p = "build/try/b576d8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-18s FAIL" % tag)
        continue
    ins = list(md.disasm(bytes(mine), 0))
    push = ins[0].op_str if ins else ""
    if len(mine) != len(orig):
        print("%-18s SIZE %+d  push=%s" % (tag, len(mine) - len(orig), push))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-18s bytes=%d push=%s%s" % (tag, n, push,
                                        "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
