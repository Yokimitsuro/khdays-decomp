"""The straight-line probe said earlier definition takes the HIGHER register,
which is the ROM's pattern; my real function does the opposite for the session
pointer and the classifier result. The difference between those two values is
live-range length. Probe that directly: one value defined early and used to the
end, one defined later and dead almost immediately.
"""
import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
HEAD = """extern int g;
extern void snk(int);
extern int src(void);
extern int cls(int);
"""


def show(tag, body, n=12):
    p = "build/try/b5bff4_lf.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    print("--- %s (%d bytes)" % (tag, len(code)))
    for k, i in enumerate(md.disasm(bytes(code), 0)):
        if k >= n:
            break
        print("      %2d %s %s" % (k, i.mnemonic, i.op_str))


# LONG defined first and used last; SHORT defined second and dead at once.
show("long_first", """
void f(int p0, int p1) {
    int lng = src();
    int shrt = cls(lng);
    switch (shrt) {
    case 0: snk(p0); break;
    case 1: snk(p1); break;
    case 2: snk(lng); break;
    }
    snk(lng + p0 + p1);
}
""")

# The same with the short value defined first.
show("short_first", """
void f(int p0, int p1) {
    int shrt = src();
    int lng = cls(shrt);
    switch (shrt) {
    case 0: snk(p0); break;
    case 1: snk(p1); break;
    case 2: snk(lng); break;
    }
    snk(lng + p0 + p1);
}
""")

# Long-lived pointer plus a short classifier result, closest to the real shape.
show("ptr_and_class", """
extern int *gp;
void f(int p0, int p1) {
    int *s = gp;
    int k = cls(s[1]);
    switch (k) {
    case 0: snk(p0); break;
    case 1: snk(p1); break;
    case 2: snk(s[2]); break;
    }
    s[0] = p1;
    snk(s[1]);
}
""")
