import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_020698f8"]
orig = bytearray.fromhex(e["hex"])
orel = {o: sy for o, sy in e["relocs"]}
om = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]

BASE = open("build/try/func_ov002_020698f8.c").read()


def score(tag, s):
    p = "build/try/b8f8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, True)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-20s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return 99
    if len(mine) != len(orig):
        print("%-20s SIZE %d" % (tag, len(mine)))
        return 99
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-20s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    return nd


print("baseline")
score("base", BASE)

# lift node to function scope so mwcc keeps the flag-setting move
s = BASE.replace("    int seatId;\n", "    int seatId;\n    int node;\n")
s = s.replace("                int node = func_ov002_02073880(seat);\n\n"
              "                if (node != 0) {",
              "                node = func_ov002_02073880(seat);\n"
              "                if (node != 0) {")
s = s.replace("            {\n"
              "                node = func_ov002_02073880(seat);\n",
              "            {\n"
              "                node = func_ov002_02073880(seat);\n")
s = s.replace("            int node = func_ov002_02073880(seat);\n\n"
              "            if (node != 0) {",
              "            node = func_ov002_02073880(seat);\n"
              "            if (node != 0) {")
score("nodeouter", s)

# same, and also give the seat-node result a use so it cannot be folded
s2 = s.replace("    slot = index * 0x44 + *(char **)(session + 4);",
               "    slot = *(char **)(session + 4) + index * 0x44;")
score("nodeouter_addswap", s2)
