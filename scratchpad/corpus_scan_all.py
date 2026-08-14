"""Scan the matched corpus for ARM functions that load a context pointer from a
global and keep it in a HIGH callee-saved register while something else takes
r4. Those are sources that already produce the allocation this function needs,
so their shape can be copied.
"""
import sys
import os
import re
import glob

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
NUM = {"r4": 4, "r5": 5, "r6": 6, "r7": 7, "r8": 8, "sb": 9, "sl": 10,
       "r9": 9, "r10": 10}

files = []
for pat in ("src/overlays/*/calls/*.c", "src/overlays/*/auto/*.c",
            "src/*/calls/*.c", "src/*/auto/*.c"):
    files.extend(glob.glob(pat))
files = [f for f in files if os.path.getsize(f) > 2000]
print("scanning %d matched sources" % len(files))

hits = []
for f in files:
    try:
        o = compile_c(f, False)
        code, _ = text_relocs(o)
    except Exception:
        continue
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    if not ins or not ins[0].startswith("push"):
        continue
    # need at least six callee-saved registers pushed
    pushed = re.findall(r"\b(r[4-9]|r1[01]|sb|sl|fp)\b", ins[0])
    if len(set(pushed)) < 5:
        continue
    # find a global pointer load in the first dozen instructions
    ctx = None
    for t in ins[:14]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[(r[0-9]+|sb|sl)\]$", t)
        if m and ctx is None:
            ctx = m.group(1)
    if ctx is None or ctx not in NUM:
        continue
    if NUM[ctx] >= 8:
        hits.append((f, ctx, len(code), ins[0][5:]))

print()
print("sources whose context pointer lands in r8 or higher:")
for f, ctx, size, push in sorted(hits, key=lambda h: -h[2]):
    print("  %-56s ctx=%-4s size=%-5d push=%s" % (f, ctx, size, push))
print("total", len(hits))
