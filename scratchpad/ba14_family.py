"""Scan every THUMB function in the ROM for the exact opening of
func_ov002_02069b14: pool load, parameter save, deref, pool load,
register-offset load. Matched or not."""
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

strict = []
loose = []
for name, e in idx.items():
    if e.get("mode") != "thumb":
        continue
    txt = [i.mnemonic + " " + i.op_str
           for i in md.disasm(bytes.fromhex(e["hex"]), 0)]
    if len(txt) < 6 or not txt[0].startswith("push"):
        continue
    if not all(re.match(PAT[k], txt[k + 1]) for k in range(3)):
        continue
    tag = "MATCHED" if name in have else "pending"
    loose.append((name, e["size"], tag))
    if (re.match(r"^ldr r\d, \[pc", txt[4])
            and re.match(r"^ldr r\d, \[r\d, r\d\]$", txt[5])):
        strict.append((name, e["size"], tag, txt[:9]))

print("LOOSE openings (pool, save, deref): %d" % len(loose))
nm = sum(1 for x in loose if x[2] == "MATCHED")
print("   matched %d / pending %d" % (nm, len(loose) - nm))
print("\nSTRICT, the full five-instruction opening: %d" % len(strict))
for name, size, tag, t in strict:
    print("\n=== %s (%d B) %s" % (name, size, tag))
    for x in t:
        print("      " + x)
