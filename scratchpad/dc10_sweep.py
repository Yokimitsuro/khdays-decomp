"""Sweep caching forms for the two pool loads and the split address."""
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
path = os.path.join(ROOT, "build", "try", NAME + ".c")
SRC = open(path).read()
MARK = "int " + NAME + "(int nKey) {"
HEAD = SRC[:SRC.index(MARK)]
SLOT = "    nSlot = func_ov002_02076468(%s);\n"
TAIL = ("    if (nSlot == 0) {\n        return 0;\n    }\n"
        "    return func_ov002_0207a23c(nSlot, nKey) >= 0;\n}\n")
GUARD_G = "    if ((data_0204c240 & 2) != 0) {\n        return 0;\n    }\n"
GUARD_L = "    if ((nFlags & 2) != 0) {\n        return 0;\n    }\n"
FLAG = "    u8 nFlags = data_0204c240;\n"

TABLE = "    Ov002ModuleTable *pTable = &data_ov002_0207fa00->table;\n"
FIELD = "    signed char *pId = &data_ov002_0207fa00->table.cModuleId;\n"
HOST = "    Ov002ModuleHost *h = data_ov002_0207fa00;\n"
SLOTD = "    int nSlot;\n"

V = {
    "A base": TABLE + SLOTD + "\n" + GUARD_G + SLOT % "pTable->cModuleId",
    "B field ptr": FIELD + SLOTD + "\n" + GUARD_G + SLOT % "*pId",
    "C host cached": HOST + SLOTD + "\n" + GUARD_G + SLOT % "h->table.cModuleId",
    "D flag first": FLAG + TABLE + SLOTD + "\n" + GUARD_L + SLOT % "pTable->cModuleId",
    "E table first": TABLE + FLAG + SLOTD + "\n" + GUARD_L + SLOT % "pTable->cModuleId",
    "F field + flag": FIELD + FLAG + SLOTD + "\n" + GUARD_L + SLOT % "*pId",
    "G host + flag": HOST + FLAG + SLOTD + "\n" + GUARD_L + SLOT % "h->table.cModuleId",
    "H slot first": SLOTD + TABLE + "\n" + GUARD_G + SLOT % "pTable->cModuleId",
    "I value cached": "    int nId = data_ov002_0207fa00->table.cModuleId;\n" + SLOTD
                      + "\n" + GUARD_G + SLOT % "nId",
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
for label, body in V.items():
    open(tmp, "w").write(HEAD + MARK + "\n" + body + TAIL)
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
    print("%-18s size=%-4d real=%-3d %s%s"
          % (label, len(mine), len(real), real[:4], "  *** MATCH ***" if not real else ""))
os.remove(tmp)
