"""Count how many instructions mention each callee-saved register in the ROM and
in the candidate. If the allocator ranks by use count, the group that gets r4
should be the busiest one.
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


def counts(code):
    c = dict((r, 0) for r in REGS)
    for i in md.disasm(bytes(code), 0):
        t = i.mnemonic + " " + i.op_str
        if t.startswith(("push", "pop", "stmdb", "ldmia")):
            continue
        seen = set()
        for m in re.finditer(r"\b(r1[0-5]|r[0-9]|sb|sl)\b", t):
            r = ALIAS.get(m.group(1), m.group(1))
            if r in c and r not in seen:
                c[r] += 1
                seen.add(r)
    return c


a = counts(ORIG)
b = counts(MINE)
print("reg   ROM  MINE")
for r in REGS:
    print("%-4s %4d %5d" % (r, a[r], b[r]))
print()
print("ROM  order by count:",
      " ".join("%s=%d" % (r, a[r]) for r in sorted(REGS, key=lambda x: -a[x])))
print("MINE order by count:",
      " ".join("%s=%d" % (r, b[r]) for r in sorted(REGS, key=lambda x: -b[x])))
