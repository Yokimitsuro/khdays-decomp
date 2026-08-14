"""Structural diff of a candidate against the ROM."""
import sys
import os
import json
import difflib

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
idx = json.load(open("build/func_index.json"))
orig = bytearray.fromhex(idx["func_ov002_02052024"]["hex"])
path = sys.argv[1]
o = compile_c(path, False)
mine, _ = text_relocs(o)
om = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]
mm = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
print("ROM %d instr / MINE %d instr (need %+d)"
      % (len(om), len(mm), len(om) - len(mm)))
sm = difflib.SequenceMatcher(None, [x.split()[0] for x in om],
                             [x.split()[0] for x in mm])
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        continue
    print("--- %s ROM[%d:%d] MINE[%d:%d]" % (tag, i1, i2, j1, j2))
    for k in range(i1, i2):
        print("   ROM  " + om[k])
    for k in range(j1, j2):
        print("   MINE " + mm[k])
