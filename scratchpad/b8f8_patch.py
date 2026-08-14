import sys
import os
import json

p = "build/try/func_ov002_020698f8.c"
s = open(p).read()
s = s.replace("void *slot, short value);", "void *slot, int value);")
s = s.replace("slot, (short)value);", "slot, value);")
s = s.replace("(*(int *)(session + 0xc0) < 3) ? 2 : 5",
              "(*(int *)(session + 0xc0) >= 3) ? 5 : 2")
s = s.replace("(*(int *)(session + 0xc0) < 3) ? 1 : 4",
              "(*(int *)(session + 0xc0) >= 3) ? 4 : 1")
open(p, "w").write(s)
print("patched")

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_020698f8"]
orig = bytearray.fromhex(e["hex"])
orel = {o: sy for o, sy in e["relocs"]}
om = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]
o = compile_c(p, True)
mine, mrel = text_relocs(o)
mm = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
print("size mine=%d orig=%d" % (len(mine), len(orig)))
print("instr diffs:", sum(1 for k in range(min(len(om), len(mm))) if om[k] != mm[k]))
if len(mine) == len(orig):
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    print("masked byte diffs:", sum(1 for i in range(len(a)) if a[i] != b[i]))
