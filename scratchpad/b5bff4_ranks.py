"""Measure whether the callee-saved order sorts by INCREASING or DECREASING live
range. Build a harness with five values whose live ranges are controlled and
distinct, then read which register each takes. My build looks like shortest-range
takes the highest register; the ROM looks like the opposite.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
HEAD = """extern void snk(int);
extern int src(void);
extern int mid(int);
"""


def build(nfill):
    """v0 dies first, v4 lives to the end; nfill filler calls stretch the gaps."""
    fill = "".join("    snk(mid(%d));\n" % (100 + i) for i in range(nfill))
    body = "".join("    int v%d = src();\n" % i for i in range(5))
    body += "    snk(v0);\n" + fill
    body += "    snk(v1);\n" + fill
    body += "    snk(v2);\n" + fill
    body += "    snk(v3);\n" + fill
    body += "    snk(v4);\n"
    return "\nvoid f(void) {\n%s}\n" % body


def probe(nfill):
    src = HEAD + build(nfill)
    p = "build/try/b5bff4_rk.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        return None, str(ex).split("\n")[0][:50]
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    push = ins[0][5:] if ins[0].startswith("push") else "(none)"
    regs = []
    for t in ins[:24]:
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and m.group(1) not in regs:
            regs.append(m.group(1))
        if len(regs) == 5:
            break
    return (push, regs), None


print("v0 has the SHORTEST live range, v4 the LONGEST")
print("if the shortest takes the highest register, the list reads high to low")
print()
for nfill in (0, 1, 2, 3):
    r, err = probe(nfill)
    if err:
        print("fill=%d FAIL %s" % (nfill, err))
        continue
    push, regs = r
    order = " ".join("v%d=%s" % (i, g) for i, g in enumerate(regs))
    print("fill=%d push=%-32s %s" % (nfill, push[:32], order))

# and the mirror: v0 lives longest, v4 dies first
def build_rev(nfill):
    fill = "".join("    snk(mid(%d));\n" % (100 + i) for i in range(nfill))
    body = "".join("    int v%d = src();\n" % i for i in range(5))
    body += "    snk(v4);\n" + fill
    body += "    snk(v3);\n" + fill
    body += "    snk(v2);\n" + fill
    body += "    snk(v1);\n" + fill
    body += "    snk(v0);\n"
    return "\nvoid f(void) {\n%s}\n" % body


print()
print("mirror: v0 now has the LONGEST live range, v4 the shortest")
for nfill in (0, 1, 2, 3):
    src = HEAD + build_rev(nfill)
    p = "build/try/b5bff4_rk.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("fill=%d FAIL %s" % (nfill, str(ex).split("\n")[0][:50]))
        continue
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    push = ins[0][5:] if ins[0].startswith("push") else "(none)"
    regs = []
    for t in ins[:24]:
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and m.group(1) not in regs:
            regs.append(m.group(1))
        if len(regs) == 5:
            break
    order = " ".join("v%d=%s" % (i, g) for i, g in enumerate(regs))
    print("fill=%d push=%-32s %s" % (nfill, push[:32], order))
