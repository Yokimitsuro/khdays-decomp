"""Make the reproduction faithful at high demand. Both real builds put the
parameters on r6 and r5; the repro puts them on r7 and r5. Sweep the features
that plausibly decide that -- number of cases, how many temporaries are live at
once, and whether the first parameter's register is recycled for a branch
temporary after its last use, which is what the real function does at
instruction 174 -- and look for p0=r6 p1=r5. Only inside that family is a search
for the pointer's register meaningful.
"""
import sys
import os
import re
import itertools

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


def build(ncase, nwide, recycle):
    """ncase cases; one wide case with nwide simultaneous temporaries; recycle
    means the wide case creates a fresh long value after p0's last use."""
    body = ""
    for i in range(ncase):
        if i == 2:
            decls = "".join("        int w%d = mid(p1 + %d);\n" % (j, j)
                            for j in range(nwide))
            mids = "".join("        snk(mid(w%d));\n" % j for j in range(nwide))
            tot = " + ".join("w%d" % j for j in range(nwide)) or "0"
            rec = ("        {\n"
                   "            int rc = mid(p0 + 9);\n"
                   "            snk(mid(rc));\n"
                   "            snk(rc);\n"
                   "        }\n" if recycle else "")
            body += ("    case 2: {\n%s%s        snk(%s);\n%s"
                     "        break;\n    }\n" % (decls, mids, tot, rec))
        elif i == 3:
            body += ("    case 3:\n        tag = mid(p1);\n"
                     "        snk(mid(tag));\n        snk(tag);\n"
                     "        break;\n")
        else:
            body += "    case %d: snk(mid(p0)); break;\n" % i
    return """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);
    int tag;

    if (q(0) == 0) { snk(q(1)); }
    r3(s->b, p1, 0);

    switch (k) {
%s    }
    r3(s->a, p1, 0);
    snk(s->b);
}
""" % body


def probe(body):
    p = "build/try/b5bff4_ff.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception:
        return None
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
        m = re.match(r"^cmp (r\w+), #\d+$", t)
        if m and t.endswith("#%d" % (len(ins) and 0 or 0)):
            pass
    for t in ins:
        m = re.match(r"^cmp (r\w+), #[0-9]+$", t)
        if m:
            kreg = m.group(1)
            break
    return (len(code), ins[0][5:], d.get("p0", "?"), d.get("p1", "?"),
            d.get("s", "?"), kreg)


print("real builds            push={r3,r4,r5,r6,r7,r8,sb,sl,lr}  "
      "p0=r6 p1=r5   ROM s=r8 k=r4 | mine s=r4 k=r7")
print()
hits = []
for ncase, nwide, rec in itertools.product((4, 5, 6), (3, 4, 5), (0, 1)):
    r = probe(build(ncase, nwide, rec))
    tag = "cases=%d wide=%d recycle=%d" % (ncase, nwide, rec)
    if r is None:
        print("%-28s FAIL" % tag)
        continue
    size, push, p0, p1, s, k = r
    faithful = (p0 == "r6" and p1 == "r5")
    print("%-28s %-4d p0=%-4s p1=%-4s s=%-4s k=%-4s %s%s"
          % (tag, size, p0, p1, s, k, push[:32],
             "  <== faithful" if faithful else ""))
    if faithful:
        hits.append((tag, s))
print()
print("faithful configs:", hits if hits else "none")
