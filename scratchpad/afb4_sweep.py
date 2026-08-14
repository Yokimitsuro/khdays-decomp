"""All declaration orders of the five locals, to settle the r5/r6 assignment."""
import importlib.util
import itertools
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

OLD = re.search(r"    Ov002PanelSession \*s = data_ov002_0207f620;\n"
                r"(?:    (?:u16|int) \w+;\n)+", SRC).group(0)

DECL = {
    "s": "    Ov002PanelSession *s;\n",
    "nTile": "    u16 nTile;\n",
    "nPalette": "    u16 nPalette;\n",
    "nStyle": "    int nStyle;\n",
    "nSlotState": "    int nSlotState;\n",
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
rows = []
for perm in itertools.permutations(DECL):
    new = "".join(DECL[v] for v in perm) + "\n    s = data_ov002_0207f620;\n"
    open(tmp, "w").write(SRC.replace(OLD, new))
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
    rows.append((len(real), len(mine), ",".join(perm)))
rows.sort()
for r in rows[:6]:
    print("real=%-3d size=%-4d %s%s" % (r[0], r[1], r[2],
                                        "  *** MATCH ***" if r[0] == 0 else ""))
os.remove(tmp)
