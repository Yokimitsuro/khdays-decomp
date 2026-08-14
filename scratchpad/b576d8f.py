"""The ROM loads *p before pSrc[i] in both loops; the candidate's temporary for
the source byte reverses that. Drop the temporary so the expression order
decides, and cross it with the pointer association.
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

OFF = "nRow * 4 + (nStart / 8) * 0x20 + (nStart % 8) / 2"

HEAD = ("typedef unsigned char u8;\n\n"
        "void func_ov002_020576d8(u8 *pDst, int nRight, int nCount,"
        " int nWidth,\n"
        "                         int nPad, int nRow, const u8 *pSrc) {\n"
        "    int nAligned = ((nPad + nWidth + 7) / 8) * 8;\n"
        "    int nStart = nAligned - (nRight + nPad + 1);\n"
        "%s"
        "\n"
        "    if (nStart < 0) {\n"
        "        nStart = 0;\n"
        "    }\n"
        "%s"
        "\n"
        "    i = 0;\n"
        "    if ((nStart & 1) != 0) {\n"
        "        if (nCount <= 0) {\n"
        "            return;\n"
        "        }\n"
        "        do {\n"
        "%s"
        "            i++;\n"
        "            p += 4;\n"
        "        } while (i < nCount);\n"
        "        return;\n"
        "    }\n"
        "    if (nCount <= 0) {\n"
        "        return;\n"
        "    }\n"
        "    do {\n"
        "%s"
        "        i++;\n"
        "        p += 4;\n"
        "    } while (i < nCount);\n"
        "}\n")

DECLS = {
    "p_first": "    u8 *p;\n    int i;\n",
    "i_first": "    int i;\n    u8 *p;\n",
}
PTRS = {
    "folded": "    p = pDst + " + OFF + ";\n",
    "paren": "    p = pDst + (" + OFF + ");\n",
}
HI = "            *p = (u8)((*p & 0xf) | (pSrc[i] << 4));\n"
LO = "        *p = (u8)((*p & 0xf0) | pSrc[i]);\n"

best = [999, None]
for dk, pk in itertools.product(DECLS, PTRS):
    s = HEAD % (DECLS[dk], PTRS[pk], HI, LO)
    tag = "%s/%s" % (dk, pk)
    p = "build/try/b576d8_%s_%s.c" % (dk, pk)
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
        print("%-18s SIZE %+d push=%s" % (tag, len(mine) - len(orig), push))
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
