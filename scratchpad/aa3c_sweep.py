"""Sweep source variants for the active function and report size / first diff."""
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
    int nTens;
    int nOnes;
    int pDst;
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
TAIL = "    pDst = func_ov002_02053bb8(0xb) + (%s + (nRow * 2 + 0xc) * 0x20) * 2;\n"

VARIANTS = {
    "A param += ternary": DIV + "    nColumn += bWide ? 10 : 9;\n" + TAIL % "nColumn",
    "B param += if/else": DIV + "    if (bWide) { nColumn += 10; } else { nColumn += 9; }\n" + TAIL % "nColumn",
    "C local then param": DIV + "    { int nCol = bWide ? 10 : 9; nColumn += nCol; }\n" + TAIL % "nColumn",
    "D ternary inline": DIV + TAIL % "(bWide ? 10 : 9) + nColumn",
    "E res split": DIV + "    nColumn += bWide ? 10 : 9;\n"
                   "    pDst = func_ov002_02053bb8(0xb);\n"
                   "    pDst += (nColumn + (nRow * 2 + 0xc) * 0x20) * 2;\n",
    "F col first": "    nColumn += bWide ? 10 : 9;\n" + DIV + TAIL % "nColumn",
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
for label, body in VARIANTS.items():
    open(tmp, "w").write(HEAD % body)
    try:
        obj = vi.compile_c(tmp, False)
    except subprocess.CalledProcessError as exc:
        print("%-22s COMPILE FAIL %s" % (label, exc))
        continue
    mine, _ = vi.text_relocs(obj)
    ml = lines(mine)
    first = next((i for i in range(max(len(ROML), len(ml)))
                  if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")), None)
    ndiff = sum(1 for i in range(max(len(ROML), len(ml)))
                if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else ""))
    print("%-22s size=%-4d (rom %d)  instrs=%-3d  firstdiff=%-4s diffs=%d"
          % (label, len(mine), len(rom), len(ml), first, ndiff))
os.remove(tmp)
