"""Compare the allocation style of the ov002 functions adjacent in address to the
active one. Functions next to each other in an overlay very likely came from the
same translation unit, so if the neighbours also park a global pointer in a high
callee-saved register the cause is unit-wide rather than local to this body.
Symbols are discovered by address order, never named literally.
"""
import sys
import os
import json
import re
import glob

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
IDX = json.load(open("build/func_index.json"))
TARGET = "func_ov002_0205bff4"
HIGH = ("r7", "r8", "sb", "sl", "fp")

matched = set()
for pat in ("src/**/calls/*.c", "src/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        if "asm_stubs" in p:
            continue
        matched.add(os.path.splitext(os.path.basename(p))[0])

rows = []
for sym, e in IDX.items():
    m = re.match(r"^func_ov002_([0-9a-f]{8})$", sym)
    if not m:
        continue
    rows.append((int(m.group(1), 16), sym, e))
rows.sort()
pos = next(i for i, r in enumerate(rows) if r[1] == TARGET)
print("ov002 functions in index: %d; active one at position %d" % (len(rows), pos))
print()
print("%-6s %-10s %-7s %-6s %-24s %-5s %-5s %-6s %s"
      % ("delta", "addr", "size", "state", "push", "p0", "p1", "ptr", "high"))

lo = max(0, pos - 12)
hi = min(len(rows), pos + 13)
for i in range(lo, hi):
    addr, sym, e = rows[i]
    code = bytearray.fromhex(e["hex"])
    ins = []
    for n, ii in enumerate(md.disasm(bytes(code), 0)):
        if n > 14:
            break
        ins.append(ii.mnemonic + " " + ii.op_str)
    if not ins:
        continue
    push = ins[0][5:] if ins[0].startswith("push") else "(no push)"
    p0 = p1 = ptr = "-"
    for t in ins:
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and p0 == "-":
            p0 = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and p1 == "-":
            p1 = m.group(1)
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m and ptr == "-":
            ptr = m.group(1)
    state = "MATCHED" if sym in matched else "pending"
    if sym == TARGET:
        state = "ACTIVE"
    print("%-6s %08x   %-7d %-6s %-24s %-5s %-5s %-6s %s"
          % (i - pos, addr, len(code), state, push[:24], p0, p1, ptr,
             "YES" if ptr in HIGH else ""))

# how common is a high pointer among ALL ov002 functions, matched or not
tot = hip = 0
for addr, sym, e in rows:
    code = bytearray.fromhex(e["hex"])
    if len(code) < 128:
        continue
    ins = []
    for n, ii in enumerate(md.disasm(bytes(code), 0)):
        if n > 14:
            break
        ins.append(ii.mnemonic + " " + ii.op_str)
    if not ins or not ins[0].startswith("push"):
        continue
    tot += 1
    for t in ins:
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m:
            if m.group(1) in HIGH:
                hip += 1
            break
print()
print("ov002 functions over 128 bytes with a push prologue: %d" % tot)
print("of those, a pointer loaded into a HIGH callee-saved register: %d" % hip)
