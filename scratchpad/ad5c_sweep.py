"""Sweep declaration and statement order for the register assignment residue."""
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
extern void MIi_CpuClear16(int nValue, int pDest, int nSize);

void func_ov002_0205ad5c(int nSlot, int nColumn, int nTile, int nPalette,
                         int bRightAlign) {
%s
%s
    MIi_CpuClear16(0, pRes + %s * 0x40, 0x16);
    MIi_CpuClear16(0, pRes + (%s + 1) * 0x40, 0x16);

    nLower = nTile + 8;
    for (i = 0; i < 8; i++) {
        int nCol = nColumn + (nIndent + i);

        *(u16 *)(pRes + (nCol + %s * 0x20) * 2) = nTile | (nPalette << 12);
        *(u16 *)(pRes + (nCol + (%s + 1) * 0x20) * 2) =
            nLower | (nPalette << 12);
        nTile++;
        nLower++;
    }
}
"""

CALL = "    pRes = func_ov002_02053bb8(9);\n"
ROWM = "    nSlot = 0x18 - (6 - nSlot) * 2;\n"
IND = "    nIndent = bRightAlign ? 2 : 1;\n"

DECLS = {
    "res,ind,i,low": "    int pRes;\n    int nIndent;\n    int i;\n    int nLower;\n",
    "ind,res,i,low": "    int nIndent;\n    int pRes;\n    int i;\n    int nLower;\n",
    "i,low,res,ind": "    int i;\n    int nLower;\n    int pRes;\n    int nIndent;\n",
    "low,i,ind,res": "    int nLower;\n    int i;\n    int nIndent;\n    int pRes;\n",
    "res,i,low,ind": "    int pRes;\n    int i;\n    int nLower;\n    int nIndent;\n",
}
ORDERS = {
    "call,row,ind": CALL + ROWM + IND,
    "call,ind,row": CALL + IND + ROWM,
    "row,call,ind": ROWM + CALL + IND,
    "ind,call,row": IND + CALL + ROWM,
    "row,ind,call": ROWM + IND + CALL,
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
rows = []
for dname, decl in DECLS.items():
    for oname, body in ORDERS.items():
        open(tmp, "w").write(HEAD % (decl, body, "nSlot", "nSlot", "nSlot", "nSlot"))
        try:
            obj = vi.compile_c(tmp, False)
        except subprocess.CalledProcessError:
            print("%-14s %-14s COMPILE FAIL" % (dname, oname))
            continue
        mine, _ = vi.text_relocs(obj)
        ml = lines(mine)
        n = max(len(ROML), len(ml))
        real = [i for i in range(n)
                if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")
                and not (i < len(ROML) and i < len(ml)
                         and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
        rows.append((len(real), len(mine), dname, oname))
        flag = "  *** MATCH ***" if not real else ""
        print("%-14s %-14s size=%-4d real=%-3d%s" % (dname, oname, len(mine), len(real), flag))
os.remove(tmp)
rows.sort()
print("\nBEST:", rows[0])
