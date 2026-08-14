"""The 656-byte exact analogue carries the combination my reproduction said could
not coexist: the same push list as the active function, the parameters on r6 and
r5, AND the global pointer in a high callee-saved register. Read its shape, since
it is direct ROM evidence that the combination is reachable. Diagnostic only.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
IDX = json.load(open("build/func_index.json"))
WANT = "{r3, r4, r5, r6, r7, r8, sb, sl, lr}"
HIGH = ("r7", "r8", "sb", "sl", "fp")

rows = []
for sym, e in IDX.items():
    m = re.match(r"^func_ov002_([0-9a-f]{8})$", sym)
    if m:
        rows.append((int(m.group(1), 16), sym, e))
rows.sort()

best = None
for addr, sym, e in rows:
    code = bytearray.fromhex(e["hex"])
    if not (300 < len(code) < 900):
        continue
    ins = []
    for n, ii in enumerate(md.disasm(bytes(code), 0)):
        if n > 14:
            break
        ins.append(ii.mnemonic + " " + ii.op_str)
    if not ins or ins[0][5:] != WANT:
        continue
    p0 = p1 = ptr = None
    for t in ins:
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and p0 is None:
            p0 = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and p1 is None:
            p1 = m.group(1)
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m and ptr is None:
            ptr = m.group(1)
    if p0 == "r6" and p1 == "r5" and ptr in HIGH:
        best = (addr, sym, e, ptr)
        break

if best is None:
    print("no analogue found in the size window")
    raise SystemExit

addr, sym, e, ptr = best
code = bytearray.fromhex(e["hex"])
print("=== analogue at %08x, %d bytes, %d relocs, pointer in %s"
      % (addr, len(code), len(e["relocs"]), ptr))
print("    push list identical to the active function; parameters on r6 and r5")
print()
ins = list(md.disasm(bytes(code), 0))
for n, i in enumerate(ins):
    if n > 55:
        break
    print("   %3d %04x  %s %s" % (n, i.address, i.mnemonic, i.op_str))
print("   ...")
# does it contain a backward branch, i.e. a loop
back = 0
for i in ins:
    m = re.match(r"^#?(0x)?[0-9a-fx]+$", i.op_str)
    if i.mnemonic.startswith("b") and i.op_str.startswith("#"):
        try:
            t = int(i.op_str[1:], 16)
        except ValueError:
            continue
        if t < i.address:
            back += 1
print()
print("backward branches (loops): %d" % back)
print("total instructions: %d" % len(ins))
