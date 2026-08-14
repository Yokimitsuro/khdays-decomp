"""Four eight-argument calls over two cases is the real function's shape and
gives s=r4; three over two cases gives s=r8. Explore the boundary: vary how the
four calls split between the cases, whether each half uses its own index
variable, and whether the eighth argument is a constant or a live variable.
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


def acase(label, base, ncalls, sepidx, liveArg, start):
    decls = ""
    if sepidx:
        decls = "".join("        int n%d = p%d + nColumn * 6;\n"
                        % (start + j, j % 2) for j in range(ncalls))
    else:
        decls = "        int n%d = p0 + nColumn * 6;\n" % start
    body = ""
    for j in range(ncalls):
        idx = (start + j) if sepidx else start
        if not sepidx and j > 0:
            body += "        n%d = p%d + nColumn * 6;\n" % (start, j % 2)
        arg8 = "tag" if liveArg else "0"
        t = ("        tag = 0;\n"
             "        if (pe != 0) {\n"
             "            tag = mid(pe[1] & 0xff);\n        }\n"
             if liveArg else "")
        body += """        pe = (u16 *)lst(s->%s, (u16)n%d);
        flag = 0;
        if (q2(0, *pe) != 0 && q2(1, *pe) != 0) {
            flag = 1;
        }
%s        if (pe == 0) {
            slot = -1;
        } else {
            slot = mid(*pe);
        }
        r8f(s->%s, slot, p%d, n%d, 1, flag, %d, %s);
""" % (base, idx, t, base, j % 2, idx, j, arg8)
    return ("    case %d: {\n%s        u16 *pe;\n        int flag;\n"
            "        int slot;\n\n%s        break;\n    }\n"
            % (label, decls, body))


def build(split, sepidx, liveArg):
    a, b = split
    body = ""
    start = 0
    if a:
        body += acase(2, "listItems", a, sepidx, liveArg, start)
        start += a if sepidx else 1
    if b:
        body += acase(3, "listEntries", b, sepidx, liveArg, start)
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
""" % body


def probe(body):
    p = "build/try/b5bff4_sp3.c"
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


print("ROM real (2+2 calls)  p0=r6 p1=r5 s=r8   |   my build  p0=r6 p1=r5 s=r4")
print()
gold = []
for split, si, la in itertools.product(
        ((2, 2), (3, 1), (1, 3), (2, 1), (1, 2)), (0, 1), (0, 1)):
    r = probe(build(split, si, la))
    tag = "split=%d+%d sep=%d live8=%d" % (split[0], split[1], si, la)
    if r[0] == "FAIL":
        print("%-30s FAIL %s" % (tag, r[1]))
        continue
    size, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    both = faithful and s == "r8"
    print("%-30s %-4d p0=%-4s p1=%-4s s=%-4s%s%s"
          % (tag, size, p0, p1, s,
             "  faithful" if faithful else "",
             "   <== ROM EXACT" if both else
             ("   s=r8" if s == "r8" else "")))
    if both:
        gold.append(tag)
print()
print("ROM-exact assignment:", gold if gold else "none")
