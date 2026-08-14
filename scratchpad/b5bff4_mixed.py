"""s=r8 shows up when each call has its own index variable AND the eighth
argument is a live variable rather than a constant. The real function is MIXED:
case 2 passes the constant 0 as the eighth argument, case 3 passes nTag, which
is live across both of its calls. Sweep the per-case combination.
"""
import sys
import os
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
HEAD = """typedef unsigned char u8;
typedef unsigned short u16;
typedef struct {
    u8 a; u8 b; u8 c; u8 d;
    u8 pad[0x47c];
    u8 listItems[0x18];
    u8 listEntries[0xc];
    void *pCached;
} S;
extern S *gp;
extern void snk(int);
extern int cls(int *pOut, int nCode);
extern int mid(int);
extern int q2(int, int);
extern void r3(int, int, int);
extern void *lst(void *, u16);
extern void r8f(void *, int, int, int, int, int, int, int);
"""


def acase(label, base, sepidx, liveArg, start, flagged):
    if sepidx:
        decls = ("        int n%d = p0 + nColumn * 6;\n"
                 "        int n%d = p1 + nColumn * 6;\n" % (start, start + 1))
    else:
        decls = "        int n%d = p0 + nColumn * 6;\n" % start
    body = ""
    for j in range(2):
        idx = (start + j) if sepidx else start
        if not sepidx and j > 0:
            body += "        n%d = p1 + nColumn * 6;\n" % start
        t = ("        tag = 0;\n" if (liveArg and j == 0) else "")
        if liveArg:
            t += ("        if (pe != 0) {\n"
                  "            tag = mid(pe[1] & 0xff);\n        }\n")
        fl = ("        flag = 0;\n"
              "        if (q2(0, *pe) != 0 && q2(1, *pe) != 0) {\n"
              "            flag = 1;\n        }\n" if flagged else "")
        arg6 = "flag" if flagged else "1"
        arg8 = "tag" if liveArg else "0"
        body += """        pe = (u16 *)lst(s->%s, (u16)n%d);
%s%s        if (pe == 0) {
            slot = -1;
        } else {
            slot = mid(*pe);
        }
        r8f(s->%s, slot, p%d, n%d, 1, %s, %d, %s);
""" % (base, idx, fl, t, base, j, idx, arg6, j, arg8)
    return ("    case %d: {\n%s        u16 *pe;\n        int flag;\n"
            "        int slot;\n\n%s        break;\n    }\n"
            % (label, decls, body))


def build(sep2, live2, sep3, live3):
    b = acase(2, "listItems", sep2, live2, 0, 1)
    b += acase(3, "listEntries", sep3, live3, 10, 0)
    return """
void f(int p0, int p1) {
    int nColumn;
    int tag;
    S *s = gp;
    int k = cls(&nColumn, s->b);

    r3(s->b, p1, 0);

    switch (k) {
    case 0: snk(mid(p0)); break;
    case 1: snk(mid(p1 * nColumn)); break;
%s    case 4: break;
    case 5: snk(mid(p1)); break;
    }
    snk(s->b);
    snk(tag);
}
""" % b


def probe(body):
    p = "build/try/b5bff4_mx.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        return ("FAIL", str(ex).split("\n")[0][:60])
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {}
    for t in ins[:18]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and "s" not in d:
            d["s"] = m.group(1)
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and "p0" not in d:
            d["p0"] = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and "p1" not in d:
            d["p1"] = m.group(1)
    return (len(code), d.get("p0", "?"), d.get("p1", "?"), d.get("s", "?"))


print("ROM real  p0=r6 p1=r5 s=r8   |   my build  p0=r6 p1=r5 s=r4")
print("(the real function is case2 live8=0 flagged, case3 live8=1)")
print()
gold = []
for s2, l2, s3, l3 in itertools.product((0, 1), (0, 1), (0, 1), (0, 1)):
    r = probe(build(s2, l2, s3, l3))
    tag = "c2:sep=%d live8=%d  c3:sep=%d live8=%d" % (s2, l2, s3, l3)
    if r[0] == "FAIL":
        print("%-36s FAIL %s" % (tag, r[1]))
        continue
    size, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    both = faithful and s == "r8"
    print("%-36s %-4d p0=%-4s p1=%-4s s=%-4s%s%s"
          % (tag, size, p0, p1, s,
             "  faithful" if faithful else "",
             "   <== ROM EXACT" if both else ("   s=r8" if s == "r8" else "")))
    if both:
        gold.append(tag)
print()
print("ROM-exact:", gold if gold else "none")
