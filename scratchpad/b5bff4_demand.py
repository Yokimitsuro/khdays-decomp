"""The repro needs four callee-saved registers, r4 to r7; the real function needs
seven, r4 to r10. That is the largest untested structural gap. Scale the repro's
demand by widening one case with N simultaneously live temporaries and watch
where the whole-function pointer lands as the range grows.
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
extern void r8f(int, int, int, int, int, int, int, int);
"""


def build(nwide):
    """One case holds nwide values live across a call at the same time."""
    decls = "".join("        int w%d = mid(p1 + %d);\n" % (i, i)
                    for i in range(nwide))
    uses = "        snk(%s);\n" % (" + ".join("w%d" % i for i in range(nwide))
                                   if nwide else "0")
    mids = "".join("        snk(mid(w%d));\n" % i for i in range(nwide))
    wide = ("    case 2: {\n%s%s%s        break;\n    }\n"
            % (decls, mids, uses))
    return """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);
    int tag;

    if (q(0) == 0) { snk(q(1)); }
    r3(s->b, p1, 0);

    switch (k) {
    case 0: snk(mid(p0)); break;
    case 1: snk(mid(p1)); break;
%s    case 3:
        tag = mid(p1);
        snk(mid(tag));
        snk(tag);
        break;
    }
    r3(s->a, p1, 0);
    snk(s->b);
}
""" % wide


def show(tag, body):
    p = "build/try/b5bff4_dm.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {}
    for t in ins[:16]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and "s" not in d:
            d["s"] = m.group(1)
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and "p0" not in d:
            d["p0"] = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and "p1" not in d:
            d["p1"] = m.group(1)
    kreg = "?"
    for t in ins:
        m = re.match(r"^cmp (r\w+), #3$", t)
        if m:
            kreg = m.group(1)
            break
    print("%-22s %-5d push=%-40s p0=%-4s p1=%-4s s=%-4s k=%-4s"
          % (tag, len(code), ins[0][5:], d.get("p0", "?"), d.get("p1", "?"),
             d.get("s", "?"), kreg))


print("ROM real function      1416  push={r3,r4,r5,r6,r7,r8,sb,sl,lr}"
      "        p0=r6   p1=r5   s=r8   k=r4")
print("my real build          1416  push={r3,r4,r5,r6,r7,r8,sb,sl,lr}"
      "        p0=r6   p1=r5   s=r4   k=r7")
print()
for n in range(0, 7):
    show("wide=%d" % n, build(n))
