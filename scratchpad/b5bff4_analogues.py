"""Filter the ov002 functions with a high pointer down to those with EXACTLY the
active function's push list, seven callee-saved registers. Those are the exact
structural analogues; the smallest one becomes the cheap case study. Diagnostic
reading only, in service of the active function.
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
WANT = "{r3, r4, r5, r6, r7, r8, sb, sl, lr}"

matched = set()
for pat in ("src/**/calls/*.c", "src/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        if "asm_stubs" not in p:
            matched.add(os.path.splitext(os.path.basename(p))[0])

rows = []
for sym, e in IDX.items():
    m = re.match(r"^func_ov002_([0-9a-f]{8})$", sym)
    if m:
        rows.append((int(m.group(1), 16), sym, e))
rows.sort()

hits = []
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
    push = ins[0][5:]
    ptr = None
    for t in ins:
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m:
            ptr = m.group(1)
            break
    if ptr in HIGH:
        p0 = p1 = "-"
        for t in ins:
            m = re.match(r"^mov (r\w+), r0$", t)
            if m and p0 == "-":
                p0 = m.group(1)
            m = re.match(r"^mov (r\w+), r1$", t)
            if m and p1 == "-":
                p1 = m.group(1)
        loop = any(i.mnemonic in ("blt", "ble", "bne", "bgt", "bge", "b")
                   and i.operands and False for i in [])
        hits.append((len(code), addr, sym, ptr, push, p0, p1,
                     sym in matched))

print("ov002 functions with a high pointer: %d" % len(hits))
print()
print("%-8s %-10s %-6s %-4s %-6s %-6s %-8s %s"
      % ("size", "addr", "ptr", "p0", "p1", "state", "samepush", "push"))
exact = []
for size, addr, sym, ptr, push, p0, p1, ism in sorted(hits):
    same = (push == WANT)
    if same:
        exact.append((size, addr, sym))
    print("%-8d %08x   %-6s %-4s %-6s %-6s %-8s %s"
          % (size, addr, ptr, p0, p1, "MATCHED" if ism else "pending",
             "YES" if same else "", push[:34]))
print()
print("exact structural analogues (same push list): %d" % len(exact))
for size, addr, sym in sorted(exact):
    print("   %5dB  %08x" % (size, addr))

if exact:
    size, addr, sym = sorted(exact)[0]
    e = IDX[sym]
    print()
    print("=== smallest exact analogue: %08x, %d bytes, %d relocs"
          % (addr, size, len(e["relocs"])))
    code = bytearray.fromhex(e["hex"])
    for n, i in enumerate(md.disasm(bytes(code), 0)):
        if n > 45:
            break
        print("   %3d %04x  %s %s" % (n, i.address, i.mnemonic, i.op_str))
