"""Third sweep: predicate only the constant, keep a single unconditional add."""
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
PD = "    pDst = func_ov002_02053bb8(0xb) + (nX + (nRow * 2 + 0xc) * 0x20) * 2;\n"

DECLS = {
    "d_ColX": "    int nTens;\n    int nOnes;\n    int nCol;\n    int nX;\n    int pDst;\n",
    "d_XCol": "    int nTens;\n    int nOnes;\n    int nX;\n    int nCol;\n    int pDst;\n",
    "d_last": "    int nTens;\n    int nOnes;\n    int pDst;\n    int nCol;\n    int nX;\n",
    "d_first": "    int nCol;\n    int nX;\n    int nTens;\n    int nOnes;\n    int pDst;\n",
}

BODIES = {
    "P if0": "    nCol = 10;\n    if (bWide == 0) {\n        nCol = 9;\n    }\n"
             "    nX = nCol + nColumn;\n",
    "Q rev": "    nCol = 10;\n    if (bWide == 0) {\n        nCol = 9;\n    }\n"
             "    nX = nColumn + nCol;\n",
    "S ifelse": "    if (bWide == 0) {\n        nCol = 9;\n    } else {\n        nCol = 10;\n    }\n"
                "    nX = nCol + nColumn;\n",
    "T not": "    nCol = 10;\n    if (!bWide) {\n        nCol = 9;\n    }\n"
             "    nX = nCol + nColumn;\n",
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
rows = []
for dname, decl in DECLS.items():
    for bname, body in BODIES.items():
        open(tmp, "w").write(HEAD % (decl + DIV + body + PD))
        try:
            obj = vi.compile_c(tmp, False)
        except subprocess.CalledProcessError:
            print("%-10s %-10s COMPILE FAIL" % (dname, bname))
            continue
        mine, _ = vi.text_relocs(obj)
        ml = lines(mine)
        n = max(len(ROML), len(ml))
        diffs = [i for i in range(n)
                 if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")]
        # ignore pure bl-target differences (relocated)
        real = [i for i in diffs
                if not (i < len(ROML) and i < len(ml)
                        and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
        rows.append((len(real), len(mine), dname, bname))
        print("%-10s %-10s size=%-4d instrs=%-3d ndiff=%-3d real=%d"
              % (dname, bname, len(mine), len(ml), len(diffs), len(real)))
os.remove(tmp)
rows.sort()
print("\nBEST:", rows[0])
