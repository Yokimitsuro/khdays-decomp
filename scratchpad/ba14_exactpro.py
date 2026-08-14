"""Find matched THUMB functions whose first five instructions have the ROM's exact
prologue shape: pool load, parameter save, deref, pool load, register-offset load."""
import os
import re
import json
import glob
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

idx = json.load(open("build/func_index.json"))
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
have = {}
for pat in ("src/**/calls/*.c", "src/**/auto/*.c", "libs/**/calls/*.c",
            "libs/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        if "asm_stubs" in p.replace("\\", "/"):
            continue
        have[os.path.splitext(os.path.basename(p))[0]] = p

PAT = [
    r"^ldr r\d, \[pc",
    r"^adds r\d, r0, #0$",
    r"^ldr r\d, \[r\d\]$",
]

loose = []
strict = []
for name, e in idx.items():
    if e.get("mode") != "thumb":
        continue
    p = have.get(name)
    if p is None:
        continue
    txt = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes.fromhex(e["hex"]), 0)]
    if len(txt) < 6 or not txt[0].startswith("push"):
        continue
    if not all(re.match(PAT[k], txt[k + 1]) for k in range(3)):
        continue
    loose.append((name, e["size"], p, txt[:7]))
    if re.match(r"^ldr r\d, \[pc", txt[4]) and re.match(r"^ldr r\d, \[r\d, r\d\]$", txt[5]):
        strict.append((name, e["size"], p, txt[:7]))

print("LOOSE (pool, save, deref): %d" % len(loose))
for name, size, p, t in loose:
    print("  %-26s %4d  %s" % (name, size, p))
print("\nSTRICT (plus second pool load and register-offset load): %d" % len(strict))
for name, size, p, t in strict:
    print("\n=== %s (%d B) %s" % (name, size, p))
    for x in t:
        print("      " + x)
