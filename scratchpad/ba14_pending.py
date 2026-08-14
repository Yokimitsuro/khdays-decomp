"""List the still-unsolved ROM functions that share the save-at-2 opening class,
to see whether the class is recurring and whether a smaller member of it would
be easier to reason about."""
import os
import re
import json
import glob
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

idx = json.load(open("build/func_index.json"))
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

have = set()
for pat in ("src/**/calls/*.c", "src/**/auto/*.c", "libs/**/calls/*.c",
            "libs/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        if "asm_stubs" in p.replace("\\", "/"):
            continue
        have.add(os.path.splitext(os.path.basename(p))[0])

PAT = [r"^ldr r\d, \[pc", r"^adds r\d, r0, #0$", r"^ldr r\d, \[r\d\]$"]

rows = []
for name, e in idx.items():
    if e.get("mode") != "thumb":
        continue
    txt = [i.mnemonic + " " + i.op_str
           for i in md.disasm(bytes.fromhex(e["hex"]), 0)]
    if len(txt) < 6 or not txt[0].startswith("push"):
        continue
    if not all(re.match(PAT[k], txt[k + 1]) for k in range(3)):
        continue
    if name in have:
        continue
    rows.append((e["size"], name, txt))

rows.sort()
print("%d pending functions share the save-at-2 opening class" % len(rows))
for size, name, txt in rows:
    print("\n=== %s (%d B)" % (name, size))
    for x in txt[:12]:
        print("      " + x)
