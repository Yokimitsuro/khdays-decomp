"""Fifth sweep: matrix over select form x add target x ordering, ranked by real
instruction differences against the ROM."""
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

D4 = "    int nTens;\n    int nOnes;\n    int nCol;\n    int pDst;\n"
D5 = "    int nTens;\n    int nOnes;\n    int nCol;\n    int nX;\n    int pDst;\n"

DIVC = "    nTens = nValue / nCol;\n    nOnes = nValue % nCol;\n"
DIVK = "    nTens = nValue / 10;\n    nOnes = nValue % 10;\n"

PD = "    pDst = func_ov002_02053bb8(0xb) + (%s + (nRow * 2 + 0xc) * 0x20) * 2;\n"

CASES = {}

# nCol seeded to 10, reused as the divisor, then demoted to 9.
CASES["1 divisor-shared, mutate col"] = D4 + (
    "    nCol = 10;\n" + DIVC
    + "    if (bWide == 0) {\n        nCol = 9;\n    }\n"
    + "    nColumn += nCol;\n" + PD % "nColumn")
CASES["2 divisor-shared, nX"] = D5 + (
    "    nCol = 10;\n" + DIVC
    + "    if (bWide == 0) {\n        nCol = 9;\n    }\n"
    + "    nX = nCol + nColumn;\n" + PD % "nX")
CASES["3 divisor-shared, inline"] = D4 + (
    "    nCol = 10;\n" + DIVC
    + "    if (bWide == 0) {\n        nCol = 9;\n    }\n"
    + PD % "nCol + nColumn")
CASES["4 divisor-shared, tern"] = D4 + (
    "    nCol = 10;\n" + DIVC
    + "    nCol = bWide ? nCol : 9;\n"
    + "    nColumn += nCol;\n" + PD % "nColumn")
CASES["5 const10, mutate col, if"] = D4 + (
    DIVK + "    nCol = 10;\n    if (bWide == 0) {\n        nCol = 9;\n    }\n"
    + "    nColumn += nCol;\n" + PD % "nColumn")
CASES["6 const10, mutate col, ifelse"] = D4 + (
    DIVK + "    if (bWide == 0) {\n        nCol = 9;\n    } else {\n        nCol = 10;\n    }\n"
    + "    nColumn += nCol;\n" + PD % "nColumn")
CASES["7 col before div"] = D4 + (
    "    nCol = 10;\n    if (bWide == 0) {\n        nCol = 9;\n    }\n" + DIVK
    + "    nColumn += nCol;\n" + PD % "nColumn")
CASES["8 divisor-shared, before div sel"] = D4 + (
    "    nCol = 10;\n" + DIVC
    + "    if (bWide == 0) {\n        nCol = 9;\n    }\n"
    + PD % "nColumn + nCol")
CASES["9 N ifelse fullsum (best so far)"] = D5 + (
    DIVK + "    if (bWide) {\n        nX = nColumn + 10;\n    } else {\n"
    "        nX = nColumn + 9;\n    }\n" + PD % "nX")
CASES["10 divisor-shared N"] = D5 + (
    "    nCol = 10;\n" + DIVC
    + "    if (bWide) {\n        nX = nColumn + nCol;\n    } else {\n"
      "        nX = nColumn + 9;\n    }\n" + PD % "nX")

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
rows = []
for label, body in CASES.items():
    decl, rest = body.split("\n", 1)
    # body already contains decls + statements; split at the blank marker
    parts = body
    open(tmp, "w").write(HEAD % ("", parts))
    try:
        obj = vi.compile_c(tmp, False)
    except subprocess.CalledProcessError as exc:
        print("%-34s COMPILE FAIL" % label)
        continue
    mine, _ = vi.text_relocs(obj)
    ml = lines(mine)
    n = max(len(ROML), len(ml))
    diffs = [i for i in range(n)
             if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")]
    real = [i for i in diffs
            if not (i < len(ROML) and i < len(ml)
                    and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
    rows.append((len(real), len(mine), label))
    print("%-34s size=%-4d instrs=%-3d real=%d" % (label, len(mine), len(ml), len(real)))
os.remove(tmp)
rows.sort()
print("\nBEST:", rows[0])
