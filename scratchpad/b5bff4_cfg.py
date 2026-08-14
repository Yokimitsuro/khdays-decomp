"""Last untried mechanism: the control flow graph. An edge that emits no
instruction still changes liveness, so replacing break with an explicit goto to
a shared tail label can alter the allocation while leaving the linear code
identical.
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
    p = "build/try/b5bff4_cfg.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
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
TAIL = """    s->bKind = (u8)nTo;
    func_ov002_0205b7dc(s->bMode, nTo, 0);
"""
assert TAIL in BASE

report("base", BASE)

# every outer case leaves through a goto to a shared label
head, rest = BASE.split("    switch (nClass) {", 1)
body, tail = rest.split(TAIL, 1)
# only replace the breaks that end an outer case, which sit at four spaces
outer = re.sub(r"\n        break;\n(    \}?\n)?(\n?    case |\n    \}\n)",
               lambda m: "\n        goto done;\n" + (m.group(1) or "")
               + m.group(2), body)
g1 = (head + "    switch (nClass) {" + outer + "done:\n" + TAIL + tail)
report("goto_tail", g1)

# the empty case jumps explicitly
g2 = BASE.replace("    case 4:\n        break;\n",
                  "    case 4:\n        goto done;\n")
g2 = g2.replace(TAIL, "done:\n" + TAIL)
report("case4_goto", g2)

# a do-while(0) wrapper around the switch, so break leaves the wrapper
g3 = BASE.replace("    switch (nClass) {", "    do {\n    switch (nClass) {")
g3 = g3.replace(TAIL, "    } while (0);\n\n" + TAIL)
report("dowhile_wrap", g3)
