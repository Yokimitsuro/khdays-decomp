"""Adding one branch-local live value moved the pointer off r4 in the repro.
Dump the full map and scale the number of such values, to find the rule that
decides whether the whole-function pointer sits at the bottom or above the
branch locals.
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


def build(ntag, ncase=4):
    """ntag branch-local values, each live across two calls inside its own case."""
    cases = []
    for i in range(ncase):
        if i < ntag:
            cases.append("    case %d:\n"
                         "        t%d = mid(p1 + %d);\n"
                         "        snk(mid(t%d));\n"
                         "        snk(t%d);\n"
                         "        break;\n" % (i, i, i, i, i))
        else:
            cases.append("    case %d: snk(mid(p0)); break;\n" % i)
    decls = "".join("    int t%d;\n" % i for i in range(ntag))
    return """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);
%s
    switch (k) {
%s    }
    snk(s->a);
    snk(p0 + p1);
}
""" % (decls, "".join(cases))


def show(tag, body, dump=False):
    p = "build/try/b5bff4_ts.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    sreg = "?"
    for t in ins[:14]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m:
            sreg = m.group(1)
            break
    print("%-22s %-5d push=%-38s s=%s" % (tag, len(code), ins[0][5:], sreg))
    if dump:
        for k, t in enumerate(ins[:12]):
            print("        %2d %s" % (k, t))


for n in range(0, 5):
    show("branch locals = %d" % n, build(n), dump=(n == 1))
