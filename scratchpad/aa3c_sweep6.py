"""Sixth sweep: mutate nCol (the selected constant) instead of nColumn."""
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
    int nCol;
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

DIVK = "    nTens = nValue / 10;\n    nOnes = nValue % 10;\n"
PD = "    pDst = func_ov002_02053bb8(0xb) + (nCol + (nRow * 2 + 0xc) * 0x20) * 2;\n"

SELECTS = {
    "if==0": "    nCol = 10;\n    if (bWide == 0) {\n        nCol = 9;\n    }\n",
    "ifelse": "    if (bWide == 0) {\n        nCol = 9;\n    } else {\n        nCol = 10;\n    }\n",
    "tern": "    nCol = bWide ? 10 : 9;\n",
    "ifne": "    nCol = 9;\n    if (bWide != 0) {\n        nCol = 10;\n    }\n",
}
ADDS = {
    "col+=colmn": "    nCol += nColumn;\n",
    "col=col+colmn": "    nCol = nCol + nColumn;\n",
    "col=colmn+col": "    nCol = nColumn + nCol;\n",
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
rows = []
for sname, sel in SELECTS.items():
    for aname, add in ADDS.items():
        for oname, body in (("div1st", DIVK + sel + add + PD),
                            ("sel1st", sel + DIVK + add + PD)):
            open(tmp, "w").write(HEAD % body)
            try:
                obj = vi.compile_c(tmp, False)
            except subprocess.CalledProcessError:
                print("%-8s %-16s %-7s COMPILE FAIL" % (sname, aname, oname))
                continue
            mine, _ = vi.text_relocs(obj)
            ml = lines(mine)
            n = max(len(ROML), len(ml))
            diffs = [i for i in range(n)
                     if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")]
            real = [i for i in diffs
                    if not (i < len(ROML) and i < len(ml)
                            and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
            rows.append((len(real), len(mine), sname, aname, oname))
            print("%-8s %-16s %-7s size=%-4d real=%d"
                  % (sname, aname, oname, len(mine), len(real)))
os.remove(tmp)
rows.sort()
print("\nBEST:", rows[0])
