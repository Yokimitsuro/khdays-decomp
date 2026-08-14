"""Discriminating probe: a long-lived local defined FIRST and a short-lived local
defined SECOND, both forced into callee-saved registers by living across a call.
If locals ascend from r4 by definition order, the long one takes r4. If they
ascend by live-range length, the short one takes r4 -- which is the ROM's
pattern for nClass against the session pointer.
"""
import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
HEAD = """extern void snk(int);
extern int src(void);
extern int cls(int);
extern int mid(int);
"""


def show(tag, body, n=10):
    p = "build/try/b5bff4_ds.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    ins = []
    for k, i in enumerate(md.disasm(bytes(code), 0)):
        if k >= n:
            break
        ins.append(i.mnemonic + " " + i.op_str)
    print("%-24s %-4d %s" % (tag, len(code), " | ".join(ins)))


# lng defined first, alive to the end. shrt defined second, alive across two
# calls then dead. Both need callee-saved registers.
show("long_first_short_2nd", """
void f(void) {
    int lng = src();
    int shrt = src();
    snk(mid(shrt));
    snk(mid(shrt));
    snk(mid(0));
    snk(mid(0));
    snk(lng);
}
""")

# mirror: shrt defined first, lng second
show("short_first_long_2nd", """
void f(void) {
    int shrt = src();
    int lng = src();
    snk(mid(shrt));
    snk(mid(shrt));
    snk(mid(0));
    snk(mid(0));
    snk(lng);
}
""")

# three locals: very short, medium, very long, defined longest-first
show("three_longest_first", """
void f(void) {
    int lng = src();
    int med = src();
    int shr = src();
    snk(mid(shr));
    snk(mid(med));
    snk(mid(med));
    snk(mid(0));
    snk(lng);
}
""")
