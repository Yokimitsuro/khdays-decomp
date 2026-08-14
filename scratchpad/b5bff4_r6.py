"""The ROM writes r6 five times and the candidate eight. List both sets side by
side: whatever the three extra writes are, they are the values that must stop
sharing nFrom's register.
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


def wr(code, reg):
    out = []
    for k, i in enumerate(md.disasm(bytes(code), 0)):
        t = i.mnemonic + " " + i.op_str
        if t.startswith(("push", "pop", "stmdb", "ldmia", "cmp", "tst",
                         "str", "b", "teq")):
            continue
        m = re.match(r"\S+\s+(r1[0-5]|r[0-9]|sb|sl)\b", t)
        if m and m.group(1) == reg:
            out.append((k, t))
    return out


print("=== ROM writes to r6 ===")
for k, t in wr(ORIG, "r6"):
    print("  %03d %s" % (k, t))
print("=== MINE writes to r6 ===")
for k, t in wr(MINE, "r6"):
    print("  %03d %s" % (k, t))
print()
print("=== ROM writes to r7 ===")
for k, t in wr(ORIG, "r7"):
    print("  %03d %s" % (k, t))
print("=== MINE writes to r7 ===")
for k, t in wr(MINE, "r7"):
    print("  %03d %s" % (k, t))
