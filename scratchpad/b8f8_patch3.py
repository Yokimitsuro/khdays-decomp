import sys
import os
import json

p = "build/try/func_ov002_020698f8.c"
s = open(p).read()

# the ROM reads +0x10 before +0xc, so bind the seat id first
s = s.replace("    slot = index * 0x44 + *(char **)(session + 4);\n"
              "    value = *(int *)(slot + 0xc);\n"
              "    if (*(int *)(slot + 0x10) == -1) {\n"
              "        seat = 0;\n"
              "    } else {\n"
              "        seat = func_ov002_0207285c(*(int *)(slot + 0x10));\n"
              "    }\n",
              "    slot = index * 0x44 + *(char **)(session + 4);\n"
              "    seatId = *(int *)(slot + 0x10);\n"
              "    value = *(int *)(slot + 0xc);\n"
              "    if (seatId == -1) {\n"
              "        seat = 0;\n"
              "    } else {\n"
              "        seat = func_ov002_0207285c(seatId);\n"
              "    }\n")
s = s.replace("    int value;\n    char *slot;\n",
              "    int value;\n    char *slot;\n    int seatId;\n")
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
if len(mine) == len(orig):
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    print("masked byte diffs:", sum(1 for i in range(len(a)) if a[i] != b[i]))
    for k in range(len(om)):
        aa = om[k]
        bb = mm[k] if k < len(mm) else "-"
        if aa != bb and not aa.startswith("bl"):
            print("  %03d %-30s | %s" % (k, aa, bb))
