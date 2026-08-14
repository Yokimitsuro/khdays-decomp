"""Take the two-web variant that reaches r8, drop its two extra instructions (the
second load), and align the rest against the ROM. If the remainder matches far
better than 67 bytes, the ROM's web structure really is two webs and the only
wrong thing is the extra load; if it matches worse, two webs is the wrong model.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
BASE = open("build/try/%s.c" % SYM).read()
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
NEW = DECL + "    Ov002PanelSession *s2 = data_ov002_0207f620;\n"
head, tail = BASE.replace(DECL, NEW).split("    switch (nClass) {", 1)
src = head + "    switch (nClass) {" + tail.replace("s->", "s2->")
open("build/try/b5bff4_al2.c", "w").write(src)
code, _ = text_relocs(compile_c("build/try/b5bff4_al2.c", False))

la = [i for i in md.disasm(bytes(ORIG), 0)]
lb = [i for i in md.disasm(bytes(code), 0)]
ta = [i.mnemonic + " " + i.op_str for i in la]
tb = [i.mnemonic + " " + i.op_str for i in lb]
print("ROM %d instructions, variant %d" % (len(ta), len(tb)))

# drop the two instructions that form the second load: the extra literal load
# and the extra dereference, found by shape near the top
drop = []
for n, t in enumerate(tb[:20]):
    if re.match(r"^ldr r1, \[pc, #0x[0-9a-f]+\]$", t) and n > 4:
        drop.append(n)
    if re.match(r"^ldr r7, \[r1\]$", t):
        drop.append(n)
print("dropping variant instructions", drop, [tb[d] for d in drop])
tb2 = [t for n, t in enumerate(tb) if n not in drop]
print("after dropping: %d instructions" % len(tb2))

if len(tb2) != len(ta):
    print("lengths still differ; cannot align cleanly")
else:
    same = sum(1 for x, y in zip(ta, tb2) if x == y)
    print("identical instructions after alignment: %d of %d" % (same, len(ta)))
    diff = [(n, x, y) for n, (x, y) in enumerate(zip(ta, tb2)) if x != y]
    print("differing instructions: %d" % len(diff))
    print()
    print("first 30 differences (branch targets shift, so ignore bl and b):")
    shown = 0
    for n, x, y in diff:
        if x.split()[0] in ("bl", "b", "beq", "bne", "blt", "bls", "bhi",
                            "addls", "popeq", "b.w"):
            continue
        print("  %3d %-34s | %s" % (n, x, y))
        shown += 1
        if shown >= 30:
            break
    real = [d for d in diff if d[1].split()[0] not in
            ("bl", "b", "beq", "bne", "blt", "bls", "bhi", "addls", "popeq")]
    print()
    print("non-branch differing instructions: %d (base candidate has 64)"
          % len(real))
