"""The repro was missing the one thing that makes the real function's classifier
result occupy a callee-saved register: three calls sit between the classifier
call and the dispatch, so the result must survive them. Add that, then vary the
branch-local count, and look for the configuration where the branch local does
NOT share a colour with the classifier result -- which is the ROM's five-colour
shape.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
HEAD = """typedef struct { int a; int b; int c; int d; } S;
extern S *gp;
extern void snk(int);
extern int cls(int);
extern int mid(int);
extern int q(int);
extern void r3(int, int, int);
"""


def build(ntag, nsurv=3, tail_ptr=True):
    surv = "".join("    if (q(%d) == 0) { snk(q(%d)); }\n" % (i, i)
                   for i in range(nsurv))
    cases = []
    for i in range(4):
        if i < ntag:
            cases.append("    case %d:\n"
                         "        t%d = mid(p1 + %d);\n"
                         "        snk(mid(t%d));\n"
                         "        snk(t%d);\n"
                         "        break;\n" % (i, i, i, i, i))
        else:
            cases.append("    case %d: snk(mid(p0)); break;\n" % i)
    decls = "".join("    int t%d;\n" % i for i in range(ntag))
    tail = ("    r3(s->a, p1, 0);\n    snk(s->b);\n" if tail_ptr
            else "    snk(p0 + p1);\n")
    return """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);
%s
%s    r3(s->b, p1, 0);

    switch (k) {
%s    }
%s}
""" % (decls, surv, "".join(cases), tail)


def show(tag, body):
    p = "build/try/b5bff4_sv.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-28s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {}
    for t in ins[:16]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and "s" not in d:
            d["s"] = m.group(1)
        m = re.match(r"^mov (r\w+), r0$", t)
        if m:
            if "p0" not in d:
                d["p0"] = m.group(1)
            elif "k" not in d:
                d["k"] = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and "p1" not in d:
            d["p1"] = m.group(1)
    # the dispatch compare names the classifier's register
    kreg = "?"
    for t in ins:
        m = re.match(r"^cmp (r\w+), #3$", t)
        if m:
            kreg = m.group(1)
            break
    print("%-28s %-5d push=%-30s p0=%-4s p1=%-4s s=%-4s k=%-4s"
          % (tag, len(code), ins[0][5:], d.get("p0", "?"), d.get("p1", "?"),
             d.get("s", "?"), kreg))


for n in range(0, 4):
    show("survive3 tags=%d" % n, build(n))
print()
for n in range(0, 4):
    show("survive1 tags=%d" % n, build(n, nsurv=1))
