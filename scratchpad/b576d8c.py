"""The one missing instruction is the final 'add r4, r0, r3', pDst added to a
fully computed offset. Parenthesising gets that but costs two callee-saved
registers. Try spellings that put pDst last as an addend instead.
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
BASE = open("build/try/b576d8_flat.c").read()

OLD = ("    p = pDst + nRow * 4 + (nStart / 8) * 0x20"
       " + (nStart % 8) / 2;\n")
assert OLD in BASE

FORMS = {
    "dst_last": "    p = (u8 *)(nRow * 4 + (nStart / 8) * 0x20"
                " + (nStart % 8) / 2 + (int)pDst);\n",
    "dst_last_paren": "    p = (u8 *)((nRow * 4 + (nStart / 8) * 0x20"
                      " + (nStart % 8) / 2) + (int)pDst);\n",
    "index": "    p = &pDst[nRow * 4 + (nStart / 8) * 0x20"
             " + (nStart % 8) / 2];\n",
    "index_noamp": "    p = pDst + (nRow << 2) + (nStart / 8 << 5)"
                   " + (nStart % 8) / 2;\n",
    "row_last": "    p = pDst + (nStart / 8) * 0x20 + (nStart % 8) / 2"
                " + nRow * 4;\n",
    "half_mid": "    p = pDst + nRow * 4 + (nStart % 8) / 2"
                " + (nStart / 8) * 0x20;\n",
}

best = [999, None]
for tag, form in FORMS.items():
    s = BASE.replace(OLD, form)
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
