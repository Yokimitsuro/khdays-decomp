"""Second sweep: make the column sum land in a fresh web without sinking it."""
import importlib.util
import json
import os
import subprocess
import sys

import capstone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
spec = importlib.util.spec_from_file_location("vi", os.path.join(ROOT, "tools", "verify_idx.py"))
vi = importlib.util.module_from_spec(spec)
sys.argv = ["verify_idx.py"]
spec.loader.exec_module(vi)

NAME = json.load(open(os.path.join(ROOT, "build", "active_function.json")))["function"]
idx = json.load(open(vi.IDX))
rom = bytearray.fromhex(idx[NAME]["hex"])
base = int(NAME.rsplit("_", 1)[-1], 16)
md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_ARM)


def lines(buf):
    return ["%-8s %s" % (i.mnemonic, i.op_str) for i in md.disasm(bytes(buf), base)]


ROML = lines(rom)

HEAD = """typedef unsigned short u16;

extern int func_ov002_02053bb8(int nItemId);
extern void func_ov002_02053cd4(int nItemId);
extern void func_ov002_0205aa14(int pDst, u16 nTopLeft, u16 nTopRight,
                                u16 nBottomLeft, u16 nBottomRight);

void func_ov002_0205aa3c(int nRow, int nValue, int nColumn, int bWide,
                         int bShowZero) {
%s
    if (nValue > 0) {
        if (nTens == 0) {
            if (nOnes > 0) {
                func_ov002_0205aa14(pDst, nOnes + 0x201, 0, nOnes + 0x221, 0);
            }
        } else {
            func_ov002_0205aa14(pDst, nTens + 0x201, nOnes + 0x20b,
                                nTens + 0x221, nOnes + 0x22b);
        }
    } else if (bShowZero) {
        func_ov002_0205aa14(pDst, 0x201, 0, 0x221, 0);
    } else {
        func_ov002_0205aa14(pDst, 0x11f, 0, 0x13f, 0);
    }

    if (bWide == 0) {
        *(u16 *)(pDst + 4) = 0;
        *(u16 *)(pDst + 0x44) = 0;
    }
    func_ov002_02053cd4(0xb);
}
"""

DIV = "    nTens = nValue / 10;\n    nOnes = nValue % 10;\n"
PD = "    pDst = func_ov002_02053bb8(0xb) + (%s + (nRow * 2 + 0xc) * 0x20) * 2;\n"
DECL3 = "    int nTens;\n    int nOnes;\n    int pDst;\n"
DECL4 = "    int nTens;\n    int nOnes;\n    int nX;\n    int pDst;\n"
DECL4B = "    int nTens;\n    int nOnes;\n    int pDst;\n    int nX;\n"
DECL5 = "    int nTens;\n    int nOnes;\n    int nCol;\n    int nX;\n    int pDst;\n"

V = {
    "baseline A": DECL3 + DIV + "    nColumn += bWide ? 10 : 9;\n" + PD % "nColumn",
    "G c99 midblock": DECL3 + DIV
        + "    { int nX = (bWide ? 10 : 9) + nColumn;\n"
        + "      pDst = func_ov002_02053bb8(0xb) + (nX + (nRow * 2 + 0xc) * 0x20) * 2; }\n",
    "H nX decl3rd": DECL4 + DIV + "    nX = (bWide ? 10 : 9) + nColumn;\n" + PD % "nX",
    "I nX decllast": DECL4B + DIV + "    nX = (bWide ? 10 : 9) + nColumn;\n" + PD % "nX",
    "J nCol+nX": DECL5 + DIV + "    nCol = bWide ? 10 : 9;\n    nX = nCol + nColumn;\n" + PD % "nX",
    "K nX rev": DECL4 + DIV + "    nX = nColumn + (bWide ? 10 : 9);\n" + PD % "nX",
    "L nX first": DECL4 + "    nX = (bWide ? 10 : 9) + nColumn;\n" + DIV + PD % "nX",
    "M assign not +=": DECL3 + DIV + "    nColumn = (bWide ? 10 : 9) + nColumn;\n" + PD % "nColumn",
    "N ifelse assign": DECL4 + DIV
        + "    if (bWide) { nX = nColumn + 10; } else { nX = nColumn + 9; }\n" + PD % "nX",
    "O nX = col then +=": DECL4 + DIV
        + "    nX = nColumn;\n    nX += bWide ? 10 : 9;\n" + PD % "nX",
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
best = None
for label, body in V.items():
    open(tmp, "w").write(HEAD % body)
    try:
        obj = vi.compile_c(tmp, False)
    except subprocess.CalledProcessError:
        print("%-20s COMPILE FAIL" % label)
        continue
    mine, _ = vi.text_relocs(obj)
    ml = lines(mine)
    n = max(len(ROML), len(ml))
    diffs = [i for i in range(n)
             if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")]
    print("%-20s size=%-4d instrs=%-3d firstdiff=%-5s ndiff=%d"
          % (label, len(mine), len(ml), diffs[0] if diffs else "-", len(diffs)))
    if not diffs:
        print("   *** EXACT INSTRUCTION MATCH ***")
os.remove(tmp)
