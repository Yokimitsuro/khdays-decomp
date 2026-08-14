"""In the repro the classifier result takes r4 and the pointer r5 -- the ROM's
relative order. The one structural difference from the real function is that
there the classifier result DIES at the dispatch. Vary exactly that.
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
    p = "build/try/b5bff4_ep.c"
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


SW = """    switch (k) {
    case 0: snk(p0); break;
    case 1: snk(p1); break;
    case 2: snk(mid(p0)); break;
    case 3: snk(mid(p1)); break;
    }
"""

# k alive after the switch
show("k_alive_after", """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);

%s    snk(k);
    snk(s->a);
    snk(p0 + p1);
}
""" % SW)

# k dead at the dispatch, exactly like the real function
show("k_dead_at_dispatch", """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);

%s    snk(s->a);
    snk(p0 + p1);
}
""" % SW)

# k dead, but rebound inside one case, as the real function does in case 3
show("k_rebound_in_case", """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);

    switch (k) {
    case 0: snk(p0); break;
    case 1: snk(p1); break;
    case 2: snk(mid(p0)); break;
    case 3:
        k = p1 + 6;
        snk(mid(k));
        snk(k);
        break;
    }
    snk(s->a);
    snk(p0 + p1);
}
""")

# k dead at dispatch and a second branch-local long value, like nTag
show("k_dead_plus_tag", """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);
    int tag;

    switch (k) {
    case 0: snk(p0); break;
    case 1: snk(p1); break;
    case 2: snk(mid(p0)); break;
    case 3:
        tag = mid(p1);
        snk(mid(tag));
        snk(tag);
        break;
    }
    snk(s->a);
    snk(p0 + p1);
}
""")
