"""Hand-written goto transformation: the outer switch becomes a table of gotos
and the five bodies become labelled blocks in the same order, each ending in a
goto to the shared tail. Same code, same layout, different construction order.
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
OREL = {o: s for o, s in _e["relocs"]}
RE = re.compile(r"\b(r1[0-5]|r[0-9]|sb|sl|fp|ip|lr|sp|pc)\b")
ALIAS = {"sb": "r9", "sl": "r10", "fp": "r11", "ip": "r12"}
FIXED = {"sp", "pc", "lr", "r0", "r1", "r2", "r3", "r12"}
TARGET = "r6 r8 r5 r4 r7 r10 r9"

lines = open("build/try/%s.c" % SYM).read().split("\n")
# line numbers are 1-based in the reads above; convert to 0-based slices
head = lines[:60]                    # through the first b7dc call
case0 = lines[61:107]                # 'switch (nClass) {' .. case 0 body end
tail = lines[218:]                   # from the blank line before s->bKind

# rebuild: keep everything, but replace the outer switch with gotos
body0 = lines[62:106]                # case 0 body, the two inner switches
body1 = lines[109:117]               # case 1 block contents
body2 = lines[121:153]               # case 2
body3 = lines[157:187]               # case 3
body5 = lines[194:215]               # case 5

out = []
out.extend(lines[:60])
out.append("")
out.append("    switch (nClass) {")
for n in (0, 1, 2, 3):
    out.append("    case %d:" % n)
    out.append("        goto L%d;" % n)
out.append("    case 4:")
out.append("        goto Ldone;")
out.append("    case 5:")
out.append("        goto L5;")
out.append("    }")
out.append("    goto Ldone;")
out.append("")
out.append("L0:")
out.extend(body0)
out.append("    goto Ldone;")
out.append("")
for n, blk in ((1, body1), (2, body2), (3, body3), (5, body5)):
    out.append("L%d:" % n)
    out.append("    {")
    out.extend(blk)
    out.append("    }")
    out.append("    goto Ldone;")
    out.append("")
out.append("Ldone:")
out.extend(lines[219:])

src = "\n".join(out)
p = "build/try/b5bff4_goto.c"
open(p, "w").write(src)
try:
    o = compile_c(p, False)
    code, mrel = text_relocs(o)
    n = "-"
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    order = []
    for i in md.disasm(bytes(code), 0):
        t = i.mnemonic + " " + i.op_str
        if t.startswith(("push", "pop", "stmdb", "ldmia")):
            continue
        for m in RE.finditer(t):
            r = ALIAS.get(m.group(1), m.group(1))
            if r not in FIXED and r not in order:
                order.append(r)
    vm = " ".join(order)
    print("goto version   size=%-5d bytes=%-5s map=%s%s"
          % (len(code), n, vm, "   TARGET" if vm == TARGET else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED")
except Exception as ex:
    print("FAIL", str(ex).split("\n")[0][:200])
print("ROM target                          map=%s" % TARGET)
