"""Find matched THUMB functions with func_ov002_0206ba78's exact allocation signature:
a struct-copy cursor materialised into a HIGH (callee-saved) low register by a plain
`adds rH, rL, #0` move, where the source of that move is a LOW scratch register that
stays live afterwards."""
import os
import re
import json
import glob
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

idx = json.load(open(os.path.join("build", "func_index.json")))
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

have = {}
for pat in ("src/**/calls/*.c", "src/**/auto/*.c", "libs/**/calls/*.c",
            "libs/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        if "asm_stubs" in p.replace("\\", "/"):
            continue
        have[os.path.splitext(os.path.basename(p))[0]] = p

MOVE = re.compile(r"^adds (r[0-7]), (r[0-7]), #0$")

hits = []
for name, e in idx.items():
    if e.get("mode") != "thumb":
        continue
    p = have.get(name)
    if p is None:
        continue
    txt = [i.mnemonic + " " + i.op_str
           for i in md.disasm(bytes.fromhex(e["hex"]), 0)]
    for k, t in enumerate(txt):
        m = MOVE.match(t)
        if not m:
            continue
        dst, srcr = m.group(1), m.group(2)
        # the cursor must be callee-saved and its base a scratch register
        if dst not in ("r4", "r5", "r6", "r7"):
            continue
        if srcr not in ("r2", "r3"):
            continue
        # a struct copy must follow within a few instructions
        win = txt[k + 1:k + 6]
        if not any(w.startswith("stm " + dst) or w.startswith("adds " + dst + ", #")
                   for w in win):
            continue
        if not any(w.startswith("ldm") for w in win):
            continue
        # and the base register must still be used afterwards
        later = txt[k + 1:]
        if not any(re.search(r"\[%s[,\]]" % srcr, w) for w in later):
            continue
        hits.append((name, p, e["size"], k, dst, srcr, txt[max(0, k - 6):k + 8]))
        break

print("%d matched THUMB functions share the allocation signature" % len(hits))
for name, p, size, k, dst, srcr, ctx in hits:
    print("\n=== %s  (%d bytes)  cursor=%s base=%s  %s" % (name, size, dst, srcr, p))
    for t in ctx:
        print("      " + t)
