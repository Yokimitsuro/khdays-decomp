"""Structural diff of a candidate against the ROM: romdiff.py <candidate.c> <symbol> [thumb]"""
import sys
import os
import json
import difflib

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

path = sys.argv[1]
sym = sys.argv[2]
thumb = len(sys.argv) > 3 and sys.argv[3] == "thumb"
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)

idx = json.load(open("build/func_index.json"))
orig = bytearray.fromhex(idx[sym]["hex"])
o = compile_c(path, thumb)
mine, _ = text_relocs(o)
om = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]
mm = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
print("ROM %dB/%d instr | MINE %dB/%d instr (need %+d instr)"
      % (len(orig), len(om), len(mine), len(mm), len(om) - len(mm)))
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
