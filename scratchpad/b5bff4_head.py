"""Print ROM and mine side by side over an instruction range."""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])

lo = int(sys.argv[1]) if len(sys.argv) > 1 else 0
hi = int(sys.argv[2]) if len(sys.argv) > 2 else 60
o = compile_c("build/try/%s.c" % SYM, False)
code, _ = text_relocs(o)

la = list(md.disasm(bytes(ORIG), 0))
lb = list(md.disasm(bytes(code), 0))
for i in range(lo, min(hi, len(la))):
    ta = la[i].mnemonic + " " + la[i].op_str
    tb = lb[i].mnemonic + " " + lb[i].op_str if i < len(lb) else ""
    print("%3d %04x | %-34s | %-34s %s" % (
        i, la[i].address, ta, tb, "" if ta == tb else "<<"))
