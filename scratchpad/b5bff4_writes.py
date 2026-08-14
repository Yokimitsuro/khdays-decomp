"""Count how many times each callee-saved register is WRITTEN in each build.
The ROM writes r8 once, the session load, and r4 eighteen times as the shared
scratch. If the candidate shows the same shape with the two swapped, the rule is
not about definition counts either.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
ORIG = bytearray.fromhex(json.load(open("build/func_index.json"))[SYM]["hex"])
o = compile_c("build/try/%s.c" % SYM, False)
MINE, _ = text_relocs(o)
ALIAS = {"sb": "r9", "sl": "r10"}
REGS = ["r4", "r5", "r6", "r7", "r8", "r9", "r10"]


def writes(code):
    c = dict((r, 0) for r in REGS)
    for i in md.disasm(bytes(code), 0):
        t = i.mnemonic + " " + i.op_str
        if t.startswith(("push", "pop", "stmdb", "ldmia", "cmp", "tst",
                         "str", "b", "teq")):
            continue
        m = re.match(r"\S+\s+(r1[0-5]|r[0-9]|sb|sl)\b", t)
        if m:
            r = ALIAS.get(m.group(1), m.group(1))
            if r in c:
                c[r] += 1
    return c


a = writes(ORIG)
b = writes(MINE)
print("reg   ROM writes  MINE writes")
for r in REGS:
    print("%-4s %10d %12d" % (r, a[r], b[r]))
