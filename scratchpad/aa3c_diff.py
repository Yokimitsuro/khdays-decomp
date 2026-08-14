"""Side-by-side ARM disassembly of the active candidate against the ROM."""
import importlib.util
import json
import os
import sys

import capstone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
spec = importlib.util.spec_from_file_location("vi", os.path.join(ROOT, "tools", "verify_idx.py"))
vi = importlib.util.module_from_spec(spec)
sys.argv = ["verify_idx.py"]
spec.loader.exec_module(vi)

NAME = json.load(open(os.path.join(ROOT, "build", "active_function.json")))["function"]
CPATH = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, "build", "try", NAME + ".c")

idx = json.load(open(vi.IDX))
rom = bytearray.fromhex(idx[NAME]["hex"])
base = int(NAME.rsplit("_", 1)[-1], 16)
obj = vi.compile_c(CPATH, False)
mine, _rel = vi.text_relocs(obj)

md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_ARM)


def lines(buf):
    out = []
    for i in md.disasm(bytes(buf), base):
        out.append("%-8s %s" % (i.mnemonic, i.op_str))
    return out


a, b = lines(rom), lines(mine)
print("ROM %d instrs / %d bytes   MINE %d instrs / %d bytes"
      % (len(a), len(rom), len(b), len(mine)))
n = max(len(a), len(b))
for i in range(n):
    x = a[i] if i < len(a) else ""
    y = b[i] if i < len(b) else ""
    print("%-3d %-46s %s %s" % (i, x, " " if x == y else "|", y))
