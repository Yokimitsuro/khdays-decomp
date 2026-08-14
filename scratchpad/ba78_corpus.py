"""Find matched THUMB functions that copy a struct through a pointer cursor
inside a loop -- the shape func_ov002_0206ba78 needs."""
import os
import json
import glob
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

ROOT = os.getcwd()
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

# every function that has real C in the tree
have = {}
for pat in ("src/**/calls/*.c", "src/**/auto/*.c", "libs/**/calls/*.c",
            "libs/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        have[os.path.splitext(os.path.basename(p))[0]] = p

hits = []
for name, e in idx.items():
    if e.get("mode") != "thumb":
        continue
    p = have.get(name)
    if p is None:
        continue
    ins = list(md.disasm(bytes.fromhex(e["hex"]), 0))
    txt = [i.mnemonic + " " + i.op_str for i in ins]
    for k, t in enumerate(txt):
        if not t.startswith("ldm"):
            continue
        window = txt[k:k + 6]
        if not any(w.startswith("stm") for w in window):
            continue
        # a backward branch anywhere means the copy sits in a loop
        loop = any(w.startswith(("b ", "blt", "ble", "bne", "beq", "bgt", "bge"))
                   and w.split("#")[-1].strip().startswith("0x")
                   for w in txt)
        hits.append((name, p, e["size"], k, txt))
        break

print("%d thumb functions with an ldm/stm struct copy and real C" % len(hits))
for name, p, size, k, txt in hits:
    print("  %-28s %4d  %s" % (name, size, p))
