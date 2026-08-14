"""Measure the three ingredients together for the first time: parameters, a
switch, and branch-local webs. The active function is exactly that shape -- two
parameters, three whole-function values and several branch webs -- and the
straight-line rules measured so far do not survive the combination.
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
extern int cls(int);
extern int *gp;
"""


def build(nparam, nwhole, mbranch, ptr):
    params = ", ".join("int p%d" % i for i in range(nparam)) or "void"
    decls = ""
    if ptr:
        decls += "    int *s = gp;\n"
    decls += "".join("    int w%d = src();\n" % i for i in range(nwhole))
    cases = ""
    for c in range(4):
        if c < mbranch:
            cases += ("    case %d: {\n"
                      "        int b%d = src();\n"
                      "        snk(mid(b%d));\n"
                      "        snk(mid(b%d));\n"
                      "        snk(b%d);\n"
                      "        break;\n    }\n" % (c, c, c, c, c))
        else:
            cases += "    case %d: snk(%d); break;\n" % (c, c)
    tail = ""
    if ptr:
        tail += "    snk(s[0]);\n"
    tail += "".join("    snk(w%d);\n" % i for i in range(nwhole))
    tail += "".join("    snk(p%d);\n" % i for i in range(nparam))
    return """
void f(%s) {
%s    int k = cls(0);

    switch (k) {
%s    }
%s}
""" % (params, decls, cases, tail)


def probe(nparam, nwhole, mbranch, ptr):
    src = HEAD + build(nparam, nwhole, mbranch, ptr)
    p = "build/try/b5bff4_t3.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        return None, str(ex).split("\n")[0][:50]
    txt = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    push = txt[0][5:] if txt[0].startswith("push") else "(none)"
    d = {}
    for n, t in enumerate(txt[:6 + 3 * (nparam + nwhole)]):
        m = re.match(r"^mov (r\w+), r([0-3])$", t)
        if m:
            k = "p%s" % m.group(2)
            d.setdefault(k, m.group(1))
            continue
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", t)
        if m and "s" not in d and ptr:
            d["s"] = m.group(1)
            continue
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and n > 0 and txt[n - 1].startswith("bl"):
            k = "w%d" % len([x for x in d if x.startswith("w")])
            d.setdefault(k, m.group(1))
    keys = (["p%d" % i for i in range(nparam)] + (["s"] if ptr else []) +
            ["w%d" % i for i in range(nwhole)])
    return (push, " ".join("%s=%s" % (k, d.get(k, "?")) for k in keys)), None


print("active function ROM: nFrom=r6 nTo=r5 s=r8 nClass=r4 nTag=r7")
print("my build           : nFrom=r6 nTo=r5 s=r4 nClass=r7 nTag=r7")
print()
for nparam in (2,):
    for ptr in (1,):
        for nwhole in (1, 2, 3):
            for mbranch in (0, 1, 2, 3, 4):
                r, err = probe(nparam, nwhole, mbranch, ptr)
                if err:
                    print("  whole=%d branch=%d FAIL %s" % (nwhole, mbranch, err))
                    continue
                push, mapping = r
                print("  whole=%d branch=%d push=%-34s %s"
                      % (nwhole, mbranch, push[:34], mapping))
