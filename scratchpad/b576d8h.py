"""No calls in this function, so the callee-saved choice is pure allocator
ordering: one more value must be live at the offset computation. Try groupings
that force simultaneous partial sums, including pDst neither first nor last.
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

TMPL = """typedef unsigned char u8;

void func_ov002_020576d8(u8 *pDst, int nRight, int nCount, int nWidth,
                         int nPad, int nRow, const u8 *pSrc) {
    int nAligned = ((nPad + nWidth + 7) / 8) * 8;
    int nStart = nAligned - (nRight + nPad + 1);
    int i;
    u8 *p;
%(extra)s
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

CASES = {
    "mid": ("", "    p = (u8 *)(nRow * 4 + (int)pDst + (nStart / 8) * 0x20"
                " + (nStart % 8) / 2);\n"),
    "mid2": ("", "    p = (u8 *)(nRow * 4 + (nStart / 8) * 0x20 + (int)pDst"
                 " + (nStart % 8) / 2);\n"),
    "rowlocal": ("    int nRowOff;\n",
                 "    nRowOff = nRow * 4;\n"
                 "    p = pDst + nRowOff + (nStart / 8) * 0x20"
                 " + (nStart % 8) / 2;\n"),
    "rowlocal_paren": ("    int nRowOff;\n",
                       "    nRowOff = nRow * 4;\n"
                       "    p = pDst + (nRowOff + (nStart / 8) * 0x20"
                       " + (nStart % 8) / 2);\n"),
    "tilelocal": ("    int nTileOff;\n",
                  "    nTileOff = (nStart / 8) * 0x20;\n"
                  "    p = pDst + nRow * 4 + nTileOff + (nStart % 8) / 2;\n"),
    "halflocal": ("    int nHalfOff;\n",
                  "    nHalfOff = (nStart % 8) / 2;\n"
                  "    p = pDst + nRow * 4 + (nStart / 8) * 0x20 + nHalfOff;\n"),
    "twostep": ("", "    p = pDst + nRow * 4;\n"
                    "    p = p + ((nStart / 8) * 0x20 + (nStart % 8) / 2);\n"),
}

best = [999, None]
for tag, (extra, ptr) in CASES.items():
    s = TMPL % {"extra": extra, "ptr": ptr}
    path = "build/try/b576d8_y.c"
    open(path, "w").write(s)
    try:
        o = compile_c(path, False)
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
