"""Probe the pool order directly: vary the number of parameters and the number of
long-lived locals, and print which callee-saved register each takes, in order.
The question is what makes the fourth allocated register be r8 (the ROM and both
ov002 witnesses) rather than r7 (my build).
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
extern int *gp;
extern void sink8(int, int, int, int, int, int, int, int);
"""


def build(nparam, nlocal, wide):
    params = ", ".join("int p%d" % i for i in range(nparam)) or "void"
    locals_ = "".join("    int v%d = src();\n" % i for i in range(nlocal))
    ptr = "    int *s = gp;\n"
    uses = ""
    for i in range(nparam):
        uses += "    snk(mid(p%d));\n" % i
    for i in range(nlocal):
        uses += "    snk(mid(v%d));\n" % i
    wideblk = ""
    if wide:
        wideblk = ("    sink8(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);\n")
    tail = "    snk(s[0]);\n"
    for i in range(nparam):
        tail += "    snk(p%d);\n" % i
    for i in range(nlocal):
        tail += "    snk(v%d);\n" % i
    return """
void f(%s) {
%s%s%s%s%s}
""" % (params, ptr, locals_, uses, wideblk, tail)


def probe(nparam, nlocal, wide):
    src = HEAD + build(nparam, nlocal, wide)
    p = "build/try/b5bff4_pl.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        return None, str(ex).split("\n")[0][:50]
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    push = ins[0][5:] if ins[0].startswith("push") else "(none)"
    order = []
    d = {}
    for t in ins[:6 + 2 * (nparam + nlocal)]:
        m = re.match(r"^mov (r\w+), r([0-3])$", t)
        if m:
            k = "p%s" % m.group(2)
            if k not in d:
                d[k] = m.group(1)
                order.append("%s=%s" % (k, m.group(1)))
            continue
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m and "s" not in d:
            d["s"] = m.group(1)
            order.append("s=%s" % m.group(1))
            continue
        m = re.match(r"^mov (r\w+), r0$", t)
        if m:
            k = "v%d" % len([x for x in d if x.startswith("v")])
            d[k] = m.group(1)
            order.append("%s=%s" % (k, m.group(1)))
    return (push, " ".join(order)), None


print("ROM of the active function: p0=r6 p1=r5 nClass=r4 s=r8 nTag=r7")
print("the fourth callee-saved allocated is r8 in the ROM, r7 in my build")
print()
for wide in (0, 1):
    print("--- eight-argument call present: %s" % bool(wide))
    for nparam in (1, 2, 3, 4):
        for nlocal in (1, 2, 3):
            r, err = probe(nparam, nlocal, wide)
            if err:
                print("   params=%d locals=%d  FAIL %s" % (nparam, nlocal, err))
                continue
            push, order = r
            print("   params=%d locals=%d  push=%-34s %s"
                  % (nparam, nlocal, push[:34], order))
