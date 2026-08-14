"""Dump the prologue and source of the matched functions the corpus scan found
with a global pointer in a high callee-saved register, so the mechanism that
gets a pointer above r4 in REAL matched code can be read rather than guessed.
Symbols are discovered by the scan, never named literally.
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
HIGH = ("r7", "r8", "sb", "sl", "fp", "r9", "r10", "r11")

srcs = {}
for pat in ("src/**/calls/*.c", "src/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        if "asm_stubs" in p:
            continue
        srcs[os.path.splitext(os.path.basename(p))[0]] = p

found = []
for sym, path in sorted(srcs.items()):
    e = IDX.get(sym)
    if not e:
        continue
    code = bytearray.fromhex(e["hex"])
    if len(code) < 256:
        continue
    ins = []
    for n, i in enumerate(md.disasm(bytes(code), 0)):
        if n > 14:
            break
        ins.append(i.mnemonic + " " + i.op_str)
    if not ins or not ins[0].startswith("push"):
        continue
    for t in ins:
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m and m.group(1) in HIGH:
            found.append((sym, path, m.group(1), len(code), ins))
            break

print("real-C matched functions with a high pointer:", len(found))
for sym, path, ptr, size, ins in found[:3]:
    print()
    print("=== %s   ptr=%s   %d bytes" % (sym, ptr, size))
    for n, t in enumerate(ins[:12]):
        print("    %2d %s" % (n, t))
    body = open(path).read()
    print("--- source (first 60 lines)")
    for line in body.split("\n")[:60]:
        print("    " + line)
