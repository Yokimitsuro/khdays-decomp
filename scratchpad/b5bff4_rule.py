"""Probe mwcc's callee-saved assignment rule on synthetic functions, so the
ordering that decides the session pointer's register is measured rather than
guessed. Each probe has long-lived locals with controlled reference counts.
"""
import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)

HEAD = """typedef unsigned char u8;
extern int g;
extern void snk(int);
extern int src(void);
"""


def show(tag, body, n=26):
    src = HEAD + body
    p = "build/try/b5bff4_rule.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-16s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    print("--- %s (%d bytes)" % (tag, len(code)))
    for k, i in enumerate(md.disasm(bytes(code), 0)):
        if k >= n:
            break
        print("    %2d %s %s" % (k, i.mnemonic, i.op_str))


# Four locals loaded from distinct calls, then referenced a controlled number of
# times: a is referenced most, d least.
show("desc_refs", """
void f(void) {
    int a = src();
    int b = src();
    int c = src();
    int d = src();
    snk(a); snk(a); snk(a); snk(a); snk(a); snk(a); snk(a); snk(a);
    snk(b); snk(b); snk(b); snk(b);
    snk(c); snk(c);
    snk(d);
    snk(a + b + c + d);
}
""")

# The same but with the reference counts reversed against declaration order.
show("asc_refs", """
void f(void) {
    int a = src();
    int b = src();
    int c = src();
    int d = src();
    snk(d); snk(d); snk(d); snk(d); snk(d); snk(d); snk(d); snk(d);
    snk(c); snk(c); snk(c); snk(c);
    snk(b); snk(b);
    snk(a);
    snk(a + b + c + d);
}
""")

# Two parameters plus two locals, matching the real function's shape.
show("params_locals", """
void f(int p0, int p1) {
    int a = src();
    int b = src();
    snk(p0); snk(p1);
    snk(a); snk(a); snk(a); snk(a); snk(a); snk(a); snk(a); snk(a);
    snk(b);
    snk(p0 + p1 + a + b);
}
""")
