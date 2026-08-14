"""Second sweep: nesting depth, to reproduce the 0x17c + 0x8c00 + 6 split."""
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

TYPES3 = """typedef unsigned char u8;

typedef struct {
    u8 pad0000[6];
    signed char cModuleId;      /* +0x06 */
} Ov002ModuleEntry;

typedef struct {
    u8 pad0000[0x8c00];
    Ov002ModuleEntry entry;     /* +0x8c00 */
} Ov002ModuleTable;

typedef struct {
    u8 pad0000[0x17c];
    Ov002ModuleTable table;     /* +0x17c */
} Ov002ModuleHost;

extern Ov002ModuleHost *data_ov002_0207fa00;
extern u8 data_0204c240;

extern int func_ov002_02076468(int nModuleId);
extern int func_ov002_0207a23c(int nSlot, int nKey);

"""

BODY = """int func_ov002_0206dc10(int nKey) {
%s    int nSlot;

    if ((data_0204c240 & 2) != 0) {
        return 0;
    }
    nSlot = func_ov002_02076468(%s);
    if (nSlot == 0) {
        return 0;
    }
    return func_ov002_0207a23c(nSlot, nKey) >= 0;
}
"""

V = {
    "J entry ptr": ("    Ov002ModuleEntry *pEntry = "
                    "&data_ov002_0207fa00->table.entry;\n", "pEntry->cModuleId"),
    "K table ptr": ("    Ov002ModuleTable *pTable = "
                    "&data_ov002_0207fa00->table;\n", "pTable->entry.cModuleId"),
    "L entry val": ("    Ov002ModuleEntry *pEntry = "
                    "&data_ov002_0207fa00->table.entry;\n"
                    "    signed char cId = pEntry->cModuleId;\n", "cId"),
    "M host ptr": ("    Ov002ModuleHost *h = data_ov002_0207fa00;\n",
                   "h->table.entry.cModuleId"),
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
for label, (decl, expr) in V.items():
    open(tmp, "w").write(TYPES3 + BODY % (decl, expr))
    try:
        obj = vi.compile_c(tmp, False)
    except subprocess.CalledProcessError:
        print("%-16s COMPILE FAIL" % label)
        continue
    mine, _ = vi.text_relocs(obj)
    ml = lines(mine)
    n = max(len(ROML), len(ml))
    real = [i for i in range(n)
            if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")
            and not (i < len(ROML) and i < len(ml)
                     and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
    print("%-16s size=%-4d real=%-3d %s%s"
          % (label, len(mine), len(real), real[:4], "  *** MATCH ***" if not real else ""))
os.remove(tmp)
