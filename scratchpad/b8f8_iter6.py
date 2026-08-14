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

BASE = open("build/try/b8f8_C_two_step.c").read()


def score(tag, s):
    p = "build/try/b8f8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, True)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return 99
    if len(mine) != len(orig):
        print("%-26s SIZE %d" % (tag, len(mine)))
        return 99
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-26s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    if nd == 0:
        open("build/try/func_ov002_020698f8.c", "w").write(s)
        print("PROMOTED")
    return nd


print("baseline")
score("i6_base", BASE)

# the final add's operand order
ADDS = [
    ("    slot = (char *)(index * 0x44);\n"
     "    slot = slot + (int)*(char **)(session + 4);\n", "orig"),
    ("    slot = (char *)(index * 0x44);\n"
     "    slot = (char *)((int)*(char **)(session + 4) + (int)slot);\n", "tblfirst"),
    ("    slot = (char *)(index * 0x44);\n"
     "    slot = *(char **)(session + 4) + (int)slot;\n", "ptrplusoff"),
]
OLD = ("    slot = (char *)(index * 0x44);\n"
       "    slot = slot + (int)*(char **)(session + 4);\n")

# how the two call-result tests are written
TESTS = [
    ("as_is", None),
    ("bare", ("if ((node = func_ov002_02073880(seat)) != 0) {",
              "if (node = func_ov002_02073880(seat)) {")),
    ("neq_split", ("if ((node = func_ov002_02073880(seat)) != 0) {",
                   "node = func_ov002_02073880(seat);\n                if (node) {")),
]

for addtxt, aname in ADDS:
    for tname, rep in TESTS:
        s = BASE.replace(OLD, addtxt)
        if rep:
            s = s.replace(rep[0], rep[1])
        score("i6_%s_%s" % (aname, tname), s)
