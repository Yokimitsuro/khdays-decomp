"""Third sweep: flip the r4/r9 assignment between the row and the resource
pointer, via statement order, a separate row local, and dead-store web ordering.
"""
import importlib.util
import itertools
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

TOP = """typedef unsigned short u16;

extern int func_ov002_02053bb8(int nItemId);
extern void MIi_CpuClear16(int nValue, int pDest, int nSize);

void func_ov002_0205ad5c(int nSlot, int nColumn, int nTile, int nPalette,
                         int bRightAlign) {
"""
BODY = """
    MIi_CpuClear16(0, pRes + %(R)s * 0x40, 0x16);
    MIi_CpuClear16(0, pRes + (%(R)s + 1) * 0x40, 0x16);

    nLower = nTile + 8;
    for (i = 0; i < 8; i++) {
        int nCol = nColumn + (nIndent + i);

        *(u16 *)(pRes + (nCol + %(R)s * 0x20) * 2) = nTile | (nPalette << 12);
        *(u16 *)(pRes + (nCol + (%(R)s + 1) * 0x20) * 2) =
            nLower | (nPalette << 12);
        nTile++;
        nLower++;
    }
}
"""

CALL = "    pRes = func_ov002_02053bb8(9);\n"
IND = "    nIndent = bRightAlign ? 2 : 1;\n"

CASES = {}

# statement order, parameter mutated into the row
for order in itertools.permutations(["call", "row", "ind"]):
    stmt = ""
    for k in order:
        stmt += {"call": CALL, "row": "    nSlot = 0x18 - (6 - nSlot) * 2;\n",
                 "ind": IND}[k]
    CASES["mut " + ",".join(order)] = (
        "    int i;\n    int pRes;\n    int nIndent;\n    int nLower;\n",
        stmt, "nSlot")

# separate row local, swept through every declaration slot
NAMES = ["i", "pRes", "nIndent", "nLower"]
for pos in range(5):
    decl = list(NAMES)
    decl.insert(pos, "nRow")
    CASES["row local @%d" % pos] = (
        "".join("    int %s;\n" % v for v in decl),
        CALL + "    nRow = 0x18 - (6 - nSlot) * 2;\n" + IND, "nRow")

# dead stores, which order the allocator webs
CASES["dead pRes"] = (
    "    int i;\n    int pRes;\n    int nIndent;\n    int nLower;\n",
    "    pRes = 0;\n" + CALL + "    nSlot = 0x18 - (6 - nSlot) * 2;\n" + IND,
    "nSlot")
CASES["dead slot"] = (
    "    int i;\n    int pRes;\n    int nIndent;\n    int nLower;\n",
    CALL + "    nSlot = 0x18 - (6 - nSlot) * 2;\n" + IND, "nSlot")
CASES["row via temp"] = (
    "    int i;\n    int pRes;\n    int nIndent;\n    int nLower;\n",
    "    nSlot = 6 - nSlot;\n    " + CALL.strip() + "\n"
    "    nSlot = 0x18 - nSlot * 2;\n" + IND, "nSlot")

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
rows = []
for label, (decl, stmt, rowexpr) in CASES.items():
    src = TOP + decl + "\n" + stmt + (BODY % {"R": rowexpr})
    open(tmp, "w").write(src)
    try:
        obj = vi.compile_c(tmp, False)
    except subprocess.CalledProcessError:
        print("%-18s COMPILE FAIL" % label)
        continue
    mine, _ = vi.text_relocs(obj)
    ml = lines(mine)
    n = max(len(ROML), len(ml))
    real = [i for i in range(n)
            if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")
            and not (i < len(ROML) and i < len(ml)
                     and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
    rows.append((len(real), len(mine), label))
    print("%-18s size=%-4d real=%-3d%s"
          % (label, len(mine), len(real), "  *** MATCH ***" if not real else ""))
os.remove(tmp)
rows.sort()
print("\nBEST:", rows[0])
