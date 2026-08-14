"""mwcc prefers nFrom's register for the three stray values. Splitting the
PARAMETER's range with a copy it coalesces for free may change which register
looks free at those points. Never tried: the earlier split tests were on the
session, not on a parameter.
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
    p = "build/try/b5bff4_sp.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
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
    print("%-24s size=%-5d bytes=%-5s map=%s%s"
          % (tag, len(code), n, vm, "   TARGET" if vm == TARGET else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
SIG = "void func_ov002_0205bff4(int nFrom, int nTo) {"
assert SIG in BASE
print("%-24s %27s map=%s" % ("ROM target", "", TARGET))
report("base", BASE)

# a copy of the first parameter used everywhere in the body
s = BASE.replace(SIG, "void func_ov002_0205bff4(int nFrom0, int nTo) {\n"
                      "    int nFrom = nFrom0;")
report("copy_p1", s)

# copies of both parameters
s2 = BASE.replace(SIG, "void func_ov002_0205bff4(int nFrom0, int nTo0) {\n"
                       "    int nFrom = nFrom0;\n    int nTo = nTo0;")
report("copy_both", s2)

# the copy made after the classifier call, splitting the range in the middle
s3 = BASE.replace(SIG, "void func_ov002_0205bff4(int nFrom0, int nTo) {\n"
                       "    int nFrom;")
s3 = s3.replace("    if (func_ov002_0205374c(",
                "    nFrom = nFrom0;\n    if (func_ov002_0205374c(", 1)
report("copy_p1_late", s3)
