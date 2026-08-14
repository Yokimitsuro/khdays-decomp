"""Second sweep: web-ordering levers for the r5/r6 swap between the session
pointer and the style index."""
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

HEADER = ("    Ov002PanelSession *s = data_ov002_0207f620;\n"
          "    u16 nTile;\n    u16 nPalette;\n    int nStyle;\n"
          "    int nSlotState;\n")

VARIANTS = {
    "base": HEADER,
    "dead style": HEADER + "\n    nStyle = 0;\n",
    "dead tile": HEADER + "\n    nTile = 0;\n",
    "dead state": HEADER + "\n    nSlotState = 0;\n",
    "dead palette": HEADER + "\n    nPalette = 0;\n",
    "style seeded -1": ("    Ov002PanelSession *s = data_ov002_0207f620;\n"
                        "    u16 nTile;\n    u16 nPalette;\n    int nStyle = -1;\n"
                        "    int nSlotState;\n"),
    "s late": ("    Ov002PanelSession *s;\n    u16 nTile;\n    u16 nPalette;\n"
               "    int nStyle;\n    int nSlotState;\n\n"
               "    s = data_ov002_0207f620;\n"),
    "s void cast": ("    Ov002PanelSession *s = (Ov002PanelSession *)"
                    "(void *)data_ov002_0207f620;\n"
                    "    u16 nTile;\n    u16 nPalette;\n    int nStyle;\n"
                    "    int nSlotState;\n"),
    "style before s": ("    int nStyle;\n    Ov002PanelSession *s = "
                       "data_ov002_0207f620;\n    u16 nTile;\n    u16 nPalette;\n"
                       "    int nSlotState;\n"),
    "dead style then s": ("    int nStyle;\n    Ov002PanelSession *s;\n"
                          "    u16 nTile;\n    u16 nPalette;\n    int nSlotState;\n"
                          "\n    nStyle = 0;\n    s = data_ov002_0207f620;\n"),
    "s then dead style": ("    Ov002PanelSession *s;\n    int nStyle;\n"
                          "    u16 nTile;\n    u16 nPalette;\n    int nSlotState;\n"
                          "\n    s = data_ov002_0207f620;\n    nStyle = 0;\n"),
}

tmp = os.path.join(ROOT, "build", "try", "_sweep.c")
rows = []
for label, head in VARIANTS.items():
    open(tmp, "w").write(SRC.replace(HEADER, head))
    try:
        obj = vi.compile_c(tmp, False)
    except subprocess.CalledProcessError:
        print("%-20s COMPILE FAIL" % label)
        continue
    mine, _ = vi.text_relocs(obj)
    ml = lines(mine)
    n = max(len(ROML), len(ml))
    real = [i for i in range(n)
            if (ROML[i] if i < len(ROML) else "") != (ml[i] if i < len(ml) else "")
            and not (i < len(ROML) and i < len(ml)
                     and ROML[i].startswith("bl") and ml[i].startswith("bl"))]
    rows.append((len(real), len(mine), label))
    print("%-20s size=%-4d real=%-3d%s"
          % (label, len(mine), len(real), "  *** MATCH ***" if not real else ""))
os.remove(tmp)
rows.sort()
print("\nBEST:", rows[0])
