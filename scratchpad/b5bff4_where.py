"""List the instructions where the ROM uses its class group, r4, and the
candidate uses the nFrom group, r6. Those are the values that must be made to
share the class variable in the source.
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
A = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(ORIG), 0)]
B = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(MINE), 0)]


def has(t, r):
    return re.search(r"\b%s\b" % r, t) is not None


print("instructions where ROM uses r4 and the candidate uses r6:")
n = 0
for k in range(min(len(A), len(B))):
    if has(A[k], "r4") and has(B[k], "r6") and not has(B[k], "r4"):
        n += 1
        print("  %03d  ROM %-28s | MINE %-28s" % (k, A[k], B[k]))
print("count", n)
print()
print("instructions where ROM uses r7 and the candidate uses r6:")
n = 0
for k in range(min(len(A), len(B))):
    if has(A[k], "r7") and has(B[k], "r6") and not has(B[k], "r7"):
        n += 1
        print("  %03d  ROM %-28s | MINE %-28s" % (k, A[k], B[k]))
print("count", n)
