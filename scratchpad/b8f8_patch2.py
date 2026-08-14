import sys
import os
import json

p = "build/try/func_ov002_020698f8.c"
s = open(p).read()

# the two stack slots are swapped: the ROM keeps the slot pointer at sp+0 and the
# value at sp+4, so declare the value first
s = s.replace("    char *slot;\n    int value;\n", "    int value;\n    char *slot;\n")

# the ROM multiplies before loading the table
s = s.replace("slot = *(char **)(session + 4) + index * 0x44;",
              "slot = index * 0x44 + *(char **)(session + 4);")

# binding the call result to a local makes mwcc reuse the flags from the move
s = s.replace("            if (func_ov002_02073880(seat) != 0) {\n"
              "                func_ov022_020883d4(index);\n"
              "                *(int *)(session + 0xc0) = "
              "(*(int *)(session + 0xc0) >= 3) ? 4 : 1;\n"
              "                result = 0;\n"
              "            }\n",
              "            {\n"
              "                int node = func_ov002_02073880(seat);\n\n"
              "                if (node != 0) {\n"
              "                    func_ov022_020883d4(index);\n"
              "                    *(int *)(session + 0xc0) = "
              "(*(int *)(session + 0xc0) >= 3) ? 4 : 1;\n"
              "                    result = 0;\n"
              "                }\n"
              "            }\n")
s = s.replace("        if (func_ov002_02073880(seat) != 0) {\n"
              "            func_ov022_020883d4(index);\n"
              "        }\n",
              "        {\n"
              "            int node = func_ov002_02073880(seat);\n\n"
              "            if (node != 0) {\n"
              "                func_ov022_020883d4(index);\n"
              "            }\n"
              "        }\n")
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
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("masked byte diffs:", nd)
    for k in range(len(om)):
        aa = om[k]
        bb = mm[k] if k < len(mm) else "-"
        if aa != bb and not aa.startswith("bl"):
            print("  %03d %-30s | %s" % (k, aa, bb))
