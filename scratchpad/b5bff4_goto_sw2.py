"""Same idea, correct transformation: in each outer case block replace the LAST
line that is exactly eight spaces and break with a goto, since that is the one
belonging to the outer switch; inner breaks stay.
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


def vmap(code):
    order = []
    for i in md.disasm(bytes(code), 0):
        t = i.mnemonic + " " + i.op_str
        if t.startswith(("push", "pop", "stmdb", "ldmia")):
            continue
        for m in RE.finditer(t):
            r = ALIAS.get(m.group(1), m.group(1))
            if r not in FIXED and r not in order:
                order.append(r)
    return " ".join(order)


def report(tag, src):
    p = "build/try/b5bff4_gs2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
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
    vm = vmap(code)
    print("%-22s size=%-5d bytes=%-5s map=%s%s"
          % (tag, len(code), n, vm, "   TARGET" if vm == TARGET else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
print("%-22s %31s map=%s" % ("ROM target", "", TARGET))

head, rest = BASE.split("    switch (nClass) {\n", 1)
body, tail = rest.split("    }\n\n    s->bKind = (u8)nTo;", 1)
parts = re.split(r"\n    (?=case [0-9]+:)", "\n" + body.strip("\n"))
labels = []
blocks = []
for p in parts:
    p = p.strip("\n")
    m = re.match(r"case ([0-9]+):", p)
    if not m:
        continue
    labels.append(int(m.group(1)))
    blocks.append(re.sub(r"^case [0-9]+:\s*\n?", "", p))


def last_break_to_goto(blk):
    lines = blk.split("\n")
    for i in range(len(lines) - 1, -1, -1):
        if lines[i] == "        break;":
            lines[i] = "        goto Ldone;"
            return "\n".join(lines)
    return blk + "\n        goto Ldone;"


sw = "    switch (nClass) {\n"
for n in labels:
    sw += "    case %d:\n        goto L%d;\n" % (n, n)
sw += "    }\n    goto Ldone;\n\n"
for n, blk in zip(labels, blocks):
    sw += "L%d:\n%s\n" % (n, last_break_to_goto(blk))
sw += "\nLdone:\n    s->bKind = (u8)nTo;" + tail
report("goto switch", head + sw)
