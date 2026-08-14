"""Case 3's contents do not matter; its mere presence does. Both cases carry
eight-argument calls, so the real variable is probably how many such calls the
function makes. Count them directly: one, two, three, four, spread over one or
two cases, and read where the pointer lands.
"""
import sys
import os
import re

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


def half(idx, base):
    return """        pe = (u16 *)lst(s->%s, (u16)n%d);
        flag = 0;
        if (q2(0, *pe) != 0 && q2(1, *pe) != 0) {
            flag = 1;
        }
        if (pe == 0) {
            slot = -1;
        } else {
            slot = mid(*pe);
        }
        r8f(s->%s, slot, p%d, n%d, 1, flag, %d, 0);
""" % (base, idx, base, idx % 2, idx, idx)


def build(ncalls, ncases):
    """ncalls eight-argument calls spread over ncases cases."""
    per = [0] * ncases
    for i in range(ncalls):
        per[i % ncases] += 1
    body = ""
    idx = 0
    for c in range(ncases):
        if per[c] == 0:
            continue
        decls = "".join("        int n%d = p%d + nColumn * 6;\n" % (idx + j, j % 2)
                        for j in range(per[c]))
        calls = "".join(half(idx + j, "listItems" if c == 0 else "listEntries")
                        for j in range(per[c]))
        body += ("    case %d: {\n%s        u16 *pe;\n        int flag;\n"
                 "        int slot;\n\n%s        break;\n    }\n"
                 % (2 + c, decls, calls))
        idx += per[c]
    return """
void f(int p0, int p1) {
    int nColumn;
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
}
""" % body


def probe(body):
    p = "build/try/b5bff4_cc.c"
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


print("ROM real (4 such calls, 2 cases)  p0=r6 p1=r5 s=r8")
print("my real build                     p0=r6 p1=r5 s=r4")
print()
for ncases in (1, 2):
    for ncalls in (1, 2, 3, 4, 5):
        if ncalls < ncases:
            continue
        r = probe(build(ncalls, ncases))
        tag = "calls=%d cases=%d" % (ncalls, ncases)
        if r[0] == "FAIL":
            print("%-22s FAIL %s" % (tag, r[1]))
            continue
        size, p0, p1, s = r
        faithful = (p0 == "r6" and p1 == "r5")
        print("%-22s %-4d p0=%-4s p1=%-4s s=%-4s%s%s"
              % (tag, size, p0, p1, s,
                 "  faithful" if faithful else "",
                 "   off r4" if s not in ("r4", "?") else ""))
