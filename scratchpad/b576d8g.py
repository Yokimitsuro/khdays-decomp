"""Cross the head spelling with the loop-order fix and the pointer association.
The loops now match exactly; the whole residue is that mwcc uses one fewer
callee-saved register than the ROM.
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

TMPL = """typedef unsigned char u8;

void func_ov002_020576d8(u8 *pDst, int nRight, int nCount, int nWidth,
                         int nPad, int nRow, const u8 *pSrc) {
%(head)s%(decl)s
    if (nStart < 0) {
        nStart = 0;
    }
%(ptr)s
    i = 0;
    if ((nStart & 1) != 0) {
        if (nCount <= 0) {
            return;
        }
        do {
            *p = (u8)((*p & 0xf) | (pSrc[i] << 4));
            i++;
            p += 4;
        } while (i < nCount);
        return;
    }
    if (nCount <= 0) {
        return;
    }
    do {
        *p = (u8)((*p & 0xf0) | pSrc[i]);
        i++;
        p += 4;
    } while (i < nCount);
}
"""

HEADS = {
    "two": "    int nAligned = ((nPad + nWidth + 7) / 8) * 8;\n"
           "    int nStart = nAligned - (nRight + nPad + 1);\n",
    "one": "    int nStart = ((nPad + nWidth + 7) / 8) * 8"
           " - (nRight + nPad + 1);\n",
    "sum": "    int nSum = nPad + nWidth + 7;\n"
           "    int nStart = nSum / 8 * 8 - (nRight + nPad + 1);\n",
    "end": "    int nEnd = nRight + nPad + 1;\n"
           "    int nStart = ((nPad + nWidth + 7) / 8) * 8 - nEnd;\n",
}
DECLS = {
    "i_first": "    int i;\n    u8 *p;\n",
    "p_first": "    u8 *p;\n    int i;\n",
}
PTRS = {
    "paren": "    p = pDst + (" + OFF + ");\n",
    "folded": "    p = pDst + " + OFF + ";\n",
}

best = [999, None]
for hk, dk, pk in itertools.product(HEADS, DECLS, PTRS):
    s = TMPL % {"head": HEADS[hk], "decl": DECLS[dk], "ptr": PTRS[pk]}
    tag = "%s/%s/%s" % (hk, dk, pk)
    path = "build/try/b576d8_x.c"
    open(path, "w").write(s)
    try:
        o = compile_c(path, False)
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
