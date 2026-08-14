"""All 24 local declaration orders, with nCol inside and outside the loop."""
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

HEAD = """typedef unsigned short u16;

extern int func_ov002_02053bb8(int nItemId);
extern void MIi_CpuClear16(int nValue, int pDest, int nSize);

void func_ov002_0205ad5c(int nSlot, int nColumn, int nTile, int nPalette,
                         int bRightAlign) {
%s%s
    pRes = func_ov002_02053bb8(9);
    nSlot = 0x18 - (6 - nSlot) * 2;
    nIndent = bRightAlign ? 2 : 1;

    MIi_CpuClear16(0, pRes + nSlot * 0x40, 0x16);
    MIi_CpuClear16(0, pRes + (nSlot + 1) * 0x40, 0x16);

    nLower = nTile + 8;
    for (i = 0; i < 8; i++) {
%s
        *(u16 *)(pRes + (nCol + nSlot * 0x20) * 2) = nTile | (nPalette << 12);
        *(u16 *)(pRes + (nCol + (nSlot + 1) * 0x20) * 2) =
            nLower | (nPalette << 12);
        nTile++;
        nLower++;
    }
}
"""

VARS = ["pRes", "nIndent", "i", "nLower"]
INNER = {
    "in": ("", "        int nCol = nColumn + (nIndent + i);\n"),
    "out": ("    int nCol;\n", "        nCol = nColumn + (nIndent + i);\n"),
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
rows = []
for perm in itertools.permutations(VARS):
    decl = "".join("    int %s;\n" % v for v in perm)
    for iname, (extra, body) in INNER.items():
        open(tmp, "w").write(HEAD % (decl, extra, body))
        try:
            obj = vi.compile_c(tmp, False)
        except subprocess.CalledProcessError:
            continue
        mine, _ = vi.text_relocs(obj)
        ml = lines(mine)
        n = max(len(ROML), len(ml))
        real = [i for i in range(n)
                if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")
                and not (i < len(ROML) and i < len(ml)
                         and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
        rows.append((len(real), len(mine), ",".join(perm), iname))
rows.sort()
for r in rows[:10]:
    print("real=%-3d size=%-4d %-32s nCol=%s%s"
          % (r[0], r[1], r[2], r[3], "  *** MATCH ***" if r[0] == 0 else ""))
os.remove(tmp)
