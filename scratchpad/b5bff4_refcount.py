"""Colouring is first-free-colour, so the ORDER decides everything, and the usual
ordering key is spill priority, i.e. reference count. Test that directly on the
repro: vary how many times the pointer and the classifier result are referenced
and watch which one takes r4. If priority is the reference count, the pointer
moves off r4 as soon as it is referenced less than the others.
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
"""


def probe(code):
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {}
    for t in ins[:14]:
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
    return d


def show(tag, body):
    p = "build/try/b5bff4_rc.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    d = probe(code)
    print("%-26s %-5d p0=%-4s p1=%-4s s=%-4s k=%-4s"
          % (tag, len(code), d.get("p0", "?"), d.get("p1", "?"),
             d.get("s", "?"), d.get("k", "?")))


def make(ns, nk):
    """ns uses of the pointer and nk uses of the classifier result, both after
    the switch so both webs stay live to the end."""
    su = "".join("    snk(s->%s);\n" % "abcd"[i % 4] for i in range(ns))
    ku = "".join("    snk(k + %d);\n" % i for i in range(nk))
    return """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);

    switch (k) {
    case 0: snk(p0); break;
    case 1: snk(p1); break;
    case 2: snk(mid(p0)); break;
    case 3: snk(mid(p1)); break;
    }
%s%s    snk(p0 + p1);
}
""" % (su, ku)


for ns, nk in ((8, 1), (4, 4), (1, 8), (1, 16), (2, 12), (12, 2)):
    show("s_uses=%-2d k_uses=%-2d" % (ns, nk), make(ns, nk))
