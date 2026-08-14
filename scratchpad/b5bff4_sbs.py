"""Side-by-side listing of every differing instruction, with index."""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}

src = sys.argv[1] if len(sys.argv) > 1 else "build/try/%s.c" % SYM
o = compile_c(src, False)
code, mrel = text_relocs(o)
MINE = bytearray(code)

a = bytearray(ORIG)
b = bytearray(MINE)
for off in set(OREL) | set(mrel):
    for k in range(4):
        if off + k < len(a):
            a[off + k] = 0
            b[off + k] = 0

la = list(md.disasm(bytes(ORIG), 0))
lb = list(md.disasm(bytes(MINE), 0))
print("ROM %d instr  MINE %d instr" % (len(la), len(lb)))
nd = 0
for i in range(min(len(la), len(lb))):
    off = la[i].address
    same = all(a[off + k] == b[off + k] for k in range(4))
    if same:
        continue
    nd += 1
    print("%3d %04x | %-34s | %s" % (
        i, off,
        la[i].mnemonic + " " + la[i].op_str,
        lb[i].mnemonic + " " + lb[i].op_str))
print("differing instructions:", nd)
print("differing bytes:", sum(1 for i in range(len(a)) if a[i] != b[i]))
