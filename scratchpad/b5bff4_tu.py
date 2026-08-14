"""Identical instructions from a deterministic compiler must come from different
input. Everything inside the function is exhausted, so test the one thing
outside it: whether the function is alone in its translation unit. Preceding
declarations or functions can shift compiler-internal counters.
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
    p = "build/try/b5bff4_tu.c"
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
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
report("alone", BASE)

# a static helper before it
PRE1 = """static int ov002_Unused(int a, int b) {
    return a + b;
}

"""
report("one_static_before", PRE1 + BASE)

# a bigger static helper with its own switch
PRE2 = """static int ov002_Unused2(int a, int b) {
    switch (a) {
    case 0:
        return b;
    case 1:
        return b + 1;
    case 2:
        return b + 2;
    default:
        return 0;
    }
}

"""
report("switch_static_before", PRE2 + BASE)

# extra typedefs and declarations before it
PRE3 = """typedef int Ov002Pad1;
typedef short Ov002Pad2;
extern int ov002_PadA(int);
extern int ov002_PadB(int, int);
extern int ov002_PadC(void);

"""
report("decls_before", PRE3 + BASE)

# the function preceded by a variable definition
PRE4 = "static int ov002_UnusedData;\n\n"
report("data_before", PRE4 + BASE)
