"""Sweep the boolean form of the second argument of the 0205abe0 call."""
import importlib.util
import json
import os
import re
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
SRC = open(os.path.join(ROOT, "build", "try", NAME + ".c")).read()
ANCHOR = re.search(r"^.*0205abe0\(nSlot.*$", SRC, re.M).group(0)

VARIANTS = {
    "eq0": "    func_ov002_0205abe0(nSlot, bFlag == 0, 0);",
    "not": "    func_ov002_0205abe0(nSlot, !bFlag, 0);",
    "tern01": "    func_ov002_0205abe0(nSlot, bFlag ? 0 : 1, 0);",
    "tern10": "    func_ov002_0205abe0(nSlot, bFlag == 0 ? 1 : 0, 0);",
    "local eq": "    { int bClear = (bFlag == 0);\n"
                "      func_ov002_0205abe0(nSlot, bClear, 0); }",
    "local ifelse": "    { int bClear;\n"
                    "      if (bFlag) { bClear = 0; } else { bClear = 1; }\n"
                    "      func_ov002_0205abe0(nSlot, bClear, 0); }",
    "local ifelse inv": "    { int bClear;\n"
                        "      if (bFlag == 0) { bClear = 1; } else { bClear = 0; }\n"
                        "      func_ov002_0205abe0(nSlot, bClear, 0); }",
    "local seed1": "    { int bClear = 1;\n"
                   "      if (bFlag) { bClear = 0; }\n"
                   "      func_ov002_0205abe0(nSlot, bClear, 0); }",
    "local seed0": "    { int bClear = 0;\n"
                   "      if (bFlag == 0) { bClear = 1; }\n"
                   "      func_ov002_0205abe0(nSlot, bClear, 0); }",
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
for label, repl in VARIANTS.items():
    open(tmp, "w").write(SRC.replace(ANCHOR, repl))
    try:
        obj = vi.compile_c(tmp, False)
    except subprocess.CalledProcessError:
        print("%-18s COMPILE FAIL" % label)
        continue
    mine, _ = vi.text_relocs(obj)
    ml = lines(mine)
    n = max(len(ROML), len(ml))
    diffs = [i for i in range(n)
             if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")]
    real = [i for i in diffs
            if not (i < len(ROML) and i < len(ml)
                    and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
    print("%-18s size=%-4d real=%-3d %s" % (label, len(mine), len(real), real[:4]))
os.remove(tmp)
