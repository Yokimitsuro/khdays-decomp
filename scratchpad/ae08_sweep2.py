"""Wide sweep of the second argument of the 0205abe0 call, looking for the
ne-first predicated pair the ROM emits."""
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
CALL = "    func_ov002_0205abe0(nSlot, %s, 0);"

EXPRS = [
    "bFlag == 0",
    "!bFlag",
    "0 == bFlag",
    "!(bFlag != 0)",
    "bFlag != 0 ? 0 : 1",
    "(bFlag != 0) == 0",
    "(unsigned)bFlag == 0",
    "bFlag ^ 1",
    "1 - (bFlag != 0)",
    "bFlag == 0 ? 1 : 0",
    "(bFlag | 0) == 0",
    "bFlag < 1 && bFlag > -1",
]
PRE = {
    "decl u": "    unsigned uFlag = bFlag;\n" + CALL % "uFlag == 0",
    "decl neg first": "    int bClear = bFlag != 0 ? 0 : 1;\n" + CALL % "bClear",
    "sep stmt": "    { int bClear;\n      bClear = bFlag != 0 ? 0 : 1;\n"
                "      func_ov002_0205abe0(nSlot, bClear, 0); }",
    "cast short": CALL % "(int)(short)(bFlag == 0)",
}

VARIANTS = {e: CALL % e for e in EXPRS}
VARIANTS.update(PRE)

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
for label, repl in VARIANTS.items():
    open(tmp, "w").write(SRC.replace(ANCHOR, repl))
    try:
        obj = vi.compile_c(tmp, False)
    except subprocess.CalledProcessError:
        print("%-24s COMPILE FAIL" % label)
        continue
    mine, _ = vi.text_relocs(obj)
    ml = lines(mine)
    n = max(len(ROML), len(ml))
    real = [i for i in range(n)
            if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")
            and not (i < len(ROML) and i < len(ml)
                     and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
    tag = "  *** MATCH ***" if not real else ""
    print("%-24s size=%-4d real=%-3d %s%s" % (label, len(mine), len(real), real[:4], tag))
os.remove(tmp)
