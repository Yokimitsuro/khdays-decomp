"""Diagnostic reading only, in service of the active function: dump the two small
ov002 neighbours that show the SAME r8 pointer pattern. A 208-byte witness of the
pattern is a far cheaper case study than the 1416-byte active function. Nothing
is written for them; they are evidence.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
IDX = json.load(open("build/func_index.json"))
TARGET = "func_ov002_0205bff4"
HIGH = ("r7", "r8", "sb", "sl", "fp")

rows = []
for sym, e in IDX.items():
    m = re.match(r"^func_ov002_([0-9a-f]{8})$", sym)
    if m:
        rows.append((int(m.group(1), 16), sym, e))
rows.sort()
pos = next(i for i, r in enumerate(rows) if r[1] == TARGET)

# pick the smallest neighbours within +-6 that load a pointer into r8
cands = []
for i in range(max(0, pos - 6), min(len(rows), pos + 7)):
    if i == pos:
        continue
    addr, sym, e = rows[i]
    code = bytearray.fromhex(e["hex"])
    ins = []
    for n, ii in enumerate(md.disasm(bytes(code), 0)):
        if n > 14:
            break
        ins.append(ii.mnemonic + " " + ii.op_str)
    if not ins or not ins[0].startswith("push"):
        continue
    for t in ins:
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m:
            if m.group(1) in HIGH:
                cands.append((len(code), i - pos, addr, sym, e))
            break
cands.sort()
print("neighbours within +-6 showing the pattern:",
      [(c[0], c[1]) for c in cands])

for size, delta, addr, sym, e in cands[:1]:
    print()
    print("=== witness at delta %+d, %08x, %d bytes, %d relocs"
          % (delta, addr, size, len(e["relocs"])))
    code = bytearray.fromhex(e["hex"])
    for n, i in enumerate(md.disasm(bytes(code), 0)):
        print("   %3d %04x  %s %s" % (n, i.address, i.mnemonic, i.op_str))
