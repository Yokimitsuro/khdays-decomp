"""Every ROM instruction that mentions r7, r8, sb or sl, with its index, so the
claim that the top four webs skip r7 can be checked rather than assumed.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
ORIG = bytearray.fromhex(json.load(open("build/func_index.json"))[SYM]["hex"])

for reg in ("r7", "r8", "sb", "sl"):
    pat = re.compile(r"\b%s\b" % reg)
    rows = []
    for n, i in enumerate(md.disasm(bytes(ORIG), 0)):
        t = i.mnemonic + " " + i.op_str
        if t.startswith(("push", "pop")):
            continue
        if pat.search(t):
            written = t.split(",")[0].split(" ")[-1] == reg
            rows.append((n, t, written))
    first_w = next((n for n, t, w in rows if w), None)
    print("=== %s: %d refs, first WRITE at instruction %s"
          % (reg, len(rows), first_w))
    for n, t, w in rows[:6]:
        print("    %3d %-34s %s" % (n, t, "WRITE" if w else ""))
    print("    ...")
