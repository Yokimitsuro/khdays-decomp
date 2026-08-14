"""Rescan the matched corpus with the now-precise signature: a function whose
prologue loads a global pointer into a HIGH callee-saved register while the two
parameters sit on r6 and r5. If even one matched source does that, its source
shows directly how it is done.
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

# map symbol -> integrated source path
srcs = {}
for pat in ("src/**/calls/*.c", "src/**/auto/*.c",
            "libs/**/calls/*.c", "libs/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        srcs[os.path.splitext(os.path.basename(p))[0]] = p
print("matched sources in tree:", len(srcs))

HIGH = ("r7", "r8", "sb", "sl", "fp", "r9", "r10", "r11")
hits = []
scanned = 0
for sym, path in sorted(srcs.items()):
    e = IDX.get(sym)
    if not e:
        continue
    code = bytearray.fromhex(e["hex"])
    if len(code) < 64:
        continue
    ins = []
    for n, i in enumerate(md.disasm(bytes(code), 0)):
        if n > 14:
            break
        ins.append(i.mnemonic + " " + i.op_str)
    if not ins or not ins[0].startswith("push"):
        continue
    scanned += 1
    p0 = p1 = ptr = None
    for t in ins:
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and p0 is None:
            p0 = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and p1 is None:
            p1 = m.group(1)
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m and ptr is None and m.group(1) in HIGH:
            ptr = m.group(1)
    if ptr and p0 == "r6" and p1 == "r5":
        hits.append((sym, path, ptr, len(code), ins[0]))

print("scanned %d matched ARM functions with a push prologue" % scanned)
print()
if hits:
    for sym, path, ptr, size, push in hits:
        print("HIT %-28s ptr=%-4s %5dB  %s" % (sym, ptr, size, path))
        print("      %s" % push)
else:
    print("no matched source loads a global pointer into a high callee-saved "
          "register with the parameters on r6 and r5")

# looser: pointer high, parameters anywhere
loose = []
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
            loose.append((sym, m.group(1), len(code), path))
            break
print()
print("looser scan, pointer in a high register regardless of parameters: %d"
      % len(loose))
for sym, ptr, size, path in loose[:25]:
    print("   %-30s ptr=%-4s %5dB  %s" % (sym, ptr, size, path))
