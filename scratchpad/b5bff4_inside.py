"""The faithful family is: high demand, classifier surviving calls, a branch
local, and the first parameter's register recycled for a branch temporary --
that last feature is what puts the parameters on r6 and r5 as in both real
builds. Sweep inside that family over the axes not yet varied, looking for the
pointer anywhere other than r4.
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


def build(nwide, nrec, s_in_wide, rebind, tail):
    rec = ""
    for j in range(nrec):
        rec += ("        {\n"
                "            int rc%d = mid(p0 + %d);\n"
                "            snk(mid(rc%d));\n"
                "            snk(rc%d);\n"
                "        }\n" % (j, 9 + j, j, j))
    decls = "".join("        int w%d = mid(p1 + %d);\n" % (j, j)
                    for j in range(nwide))
    mids = "".join("        snk(mid(w%d));\n" % j for j in range(nwide))
    tot = " + ".join("w%d" % j for j in range(nwide)) or "0"
    sline = "        snk(s->c);\n" if s_in_wide else ""
    wide = ("    case 2: {\n%s%s%s        snk(%s);\n%s        break;\n    }\n"
            % (decls, sline, mids, tot, rec))
    c3 = ("    case 3:\n"
          "        %s = mid(p1);\n"
          "        snk(mid(%s));\n"
          "        snk(%s);\n"
          "        break;\n" % (("k", "k", "k") if rebind else
                                ("tag", "tag", "tag")))
    tails = {
        0: "    r3(s->a, p1, 0);\n    snk(s->b);\n",
        1: "    snk(s->b);\n",
        2: "    r3(s->a, p1, 0);\n    snk(s->b);\n    snk(s->d);\n",
    }
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
%s%s    case 4: break;
    case 5: snk(mid(p1)); break;
    }
%s}
""" % (wide, c3, tails[tail])


def probe(body):
    p = "build/try/b5bff4_in2.c"
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
    return (len(code), ins[0][5:], d.get("p0", "?"), d.get("p1", "?"),
            d.get("s", "?"))


hits = []
n = 0
for nwide, nrec, sw, rb, tl in itertools.product(
        (3, 4), (1, 2), (0, 1), (0, 1), (0, 1, 2)):
    r = probe(build(nwide, nrec, sw, rb, tl))
    n += 1
    tag = "w=%d rec=%d s_in=%d rebind=%d tail=%d" % (nwide, nrec, sw, rb, tl)
    if r is None:
        print("%-36s FAIL" % tag)
        continue
    size, push, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    interesting = faithful and s != "r4"
    print("%-36s %-4d p0=%-4s p1=%-4s s=%-4s%s%s"
          % (tag, size, p0, p1, s,
             "  faithful" if faithful else "",
             "   <== POINTER MOVED" if interesting else ""))
    if interesting:
        hits.append(tag)
print()
print("compiled %d; pointer off r4 in a faithful config: %s"
      % (n, hits if hits else "none"))
