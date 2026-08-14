"""With the classifier surviving calls, the repro gives the ROM's relative order:
classifier on r4, pointer above it. My real build instead puts the pointer on r4.
The one structural feature the repro lacks is that my nClass is REBOUND inside a
case. Test whether that rebinding is what drags the pointer down to r4.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
sys.path.insert(0, os.path.join(os.getcwd(), "scratchpad"))
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


def build(rebind, ntag=1, nsurv=3):
    surv = "".join("    if (q(%d) == 0) { snk(q(%d)); }\n" % (i, i)
                   for i in range(nsurv))
    decls = "".join("    int t%d;\n" % i for i in range(ntag))
    extra = "" if rebind != "own" else "    int nKey;\n"
    if rebind == "none":
        case3 = ("    case 3:\n"
                 "        snk(mid(p0));\n"
                 "        break;\n")
    elif rebind == "k":
        case3 = ("    case 3:\n"
                 "        k = p1 + 6;\n"
                 "        snk(mid(k));\n"
                 "        snk(k);\n"
                 "        break;\n")
    else:
        case3 = ("    case 3:\n"
                 "        nKey = p1 + 6;\n"
                 "        snk(mid(nKey));\n"
                 "        snk(nKey);\n"
                 "        break;\n")
    cases = []
    for i in range(3):
        if i < ntag:
            cases.append("    case %d:\n"
                         "        t%d = mid(p1 + %d);\n"
                         "        snk(mid(t%d));\n"
                         "        snk(t%d);\n"
                         "        break;\n" % (i, i, i, i, i))
        else:
            cases.append("    case %d: snk(mid(p0)); break;\n" % i)
    return """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);
%s%s
%s    r3(s->b, p1, 0);

    switch (k) {
%s%s    }
    r3(s->a, p1, 0);
    snk(s->b);
}
""" % (decls, extra, surv, "".join(cases), case3)


def show(tag, body):
    p = "build/try/b5bff4_rb.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
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
    print("%-26s %-5d p0=%-4s p1=%-4s s=%-4s k=%-4s"
          % (tag, len(code), d.get("p0", "?"), d.get("p1", "?"),
             d.get("s", "?"), kreg))


print("ROM real function          1416  p0=r6   p1=r5   s=r8   k=r4")
print("my real build              1416  p0=r6   p1=r5   s=r4   k=r7")
print()
for rb in ("none", "own", "k"):
    for nt in (0, 1, 2):
        show("rebind=%-5s tags=%d" % (rb, nt), build(rb, ntag=nt))
