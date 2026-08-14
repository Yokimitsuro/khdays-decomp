"""Bisect the body, not the source text: drop one outer case at a time and read
which register the session pointer lands in. Whichever region, when removed,
moves the session onto a high register is the region that drives the assignment.
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


def head(code):
    out = []
    for n, i in enumerate(md.disasm(bytes(code), 0)):
        if n > 6:
            break
        out.append(i.mnemonic + " " + i.op_str)
    return "|".join(out)


def sess(code):
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            return m.group(1)
    return "?"


def report(tag, src):
    p = "build/try/b5bff4_bi.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    print("%-22s size=%-5d  s=%s" % (tag, len(code), sess(code)))


BASE = open("build/try/%s.c" % SYM).read()
head_txt, rest = BASE.split("    switch (nClass) {\n", 1)
body, tail = rest.split("    }\n\n    s->bKind = (u8)nTo;", 1)
parts = re.split(r"\n    (?=case [0-9]+:)", "\n" + body.strip("\n"))
blocks = {}
order = []
for p in parts:
    p = p.strip("\n")
    m = re.match(r"case ([0-9]+):", p)
    if not m:
        continue
    order.append(int(m.group(1)))
    blocks[int(m.group(1))] = p
print("outer cases:", order)
report("base", BASE)


def build(keep):
    sw = "    switch (nClass) {\n"
    for n in order:
        if n in keep:
            sw += blocks[n] + "\n"
        else:
            sw += "    case %d:\n        break;\n" % n
    sw += "    }\n\n    s->bKind = (u8)nTo;" + tail
    return head_txt + sw


for n in order:
    keep = [k for k in order if k != n]
    report("drop case %d" % n, build(keep))
for n in order:
    report("only case %d" % n, build([n]))
report("no cases", build([]))
