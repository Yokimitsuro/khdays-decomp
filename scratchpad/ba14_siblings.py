"""Find matched functions that index the same 0x44-stride roster table."""
import os
import re
import json
import glob
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_ARM

idx = json.load(open("build/func_index.json"))
have = {}
for pat in ("src/**/calls/*.c", "src/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        if "asm_stubs" in p.replace("\\", "/"):
            continue
        have[os.path.splitext(os.path.basename(p))[0]] = p

hits = []
for name, e in idx.items():
    p = have.get(name)
    if p is None:
        continue
    md = Cs(CS_ARCH_ARM,
            CS_MODE_THUMB if e.get("mode") == "thumb" else CS_MODE_ARM)
    txt = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes.fromhex(e["hex"]), 0)]
    has44 = any(re.search(r"#0x44$", t) for t in txt)
    hasmul = any(t.startswith("muls") or t.startswith("mul") for t in txt)
    if not (has44 and hasmul):
        continue
    hits.append((name, e["size"], e.get("mode"), p, txt[:8]))

print("%d matched functions multiply by 0x44" % len(hits))
for name, size, mode, p, t in hits:
    print("\n=== %s (%d B, %s) %s" % (name, size, mode, p))
    for x in t:
        print("      " + x)
