import sys
import os
import json
import itertools

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


def score(tag, s, show=False):
    p = "build/try/b8f8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, True)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return 99, None
    if len(mine) != len(orig):
        print("%-24s SIZE %d" % (tag, len(mine)))
        return 99, None
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-24s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    if show and nd:
        mm = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
        for k in range(len(om)):
            if om[k] != (mm[k] if k < len(mm) else "-") and not om[k].startswith("bl"):
                print("    %03d %-28s | %s" % (k, om[k], mm[k] if k < len(mm) else "-"))
    return nd, s


# lever A: assignment inside the condition, so the move is not dead code
A_OLD1 = ("                node = func_ov002_02073880(seat);\n"
          "                if (node != 0) {")
A_NEW1 = "                if ((node = func_ov002_02073880(seat)) != 0) {"
A_OLD2 = ("            node = func_ov002_02073880(seat);\n"
          "            if (node != 0) {")
A_NEW2 = "            if ((node = func_ov002_02073880(seat)) != 0) {"

# the current file has block-scope declarations; normalise them first
s0 = BASE.replace("                int node = func_ov002_02073880(seat);\n\n"
                  "                if (node != 0) {", A_OLD1)
s0 = s0.replace("            int node = func_ov002_02073880(seat);\n\n"
                "            if (node != 0) {", A_OLD2)
if "int node;" not in s0:
    s0 = s0.replace("    int seatId;\n", "    int seatId;\n    int node;\n")

print("normalised baseline")
score("n0", s0)

sA = s0.replace(A_OLD1, A_NEW1).replace(A_OLD2, A_NEW2)
score("A_assign_in_cond", sA)

# lever B: compare the seat id against the constant in the other order
for tag, src in (("B_constfirst", sA.replace("if (seatId == -1) {", "if (-1 == seatId) {")),
                 ("B_notneg", sA.replace("if (seatId == -1) {", "if (seatId != -1) {")
                                 .replace("        seat = 0;\n    } else {\n"
                                          "        seat = func_ov002_0207285c(seatId);\n    }",
                                          "        seat = func_ov002_0207285c(seatId);\n"
                                          "    } else {\n        seat = 0;\n    }"))):
    score(tag, src)

# lever C: bind the table pointer separately, before or after the multiply
sC1 = sA.replace("    slot = index * 0x44 + *(char **)(session + 4);",
                 "    slot = (char *)(index * 0x44);\n"
                 "    slot = slot + (int)*(char **)(session + 4);")
score("C_two_step", sC1)
sC2 = sA.replace("    slot = index * 0x44 + *(char **)(session + 4);",
                 "    {\n        int off = index * 0x44;\n\n"
                 "        slot = *(char **)(session + 4) + off;\n    }")
score("C_off_local", sC2)
