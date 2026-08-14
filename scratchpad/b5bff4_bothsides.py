"""Stack arguments moved the pointer off r4 for the first time, but only in
configurations whose parameters land on r4 and r8 instead of r6 and r5. Search
for one that has both: the pointer high AND the parameters where both real
builds put them. Extra branch locals in the other cases raise total demand
without touching the wide case's peak, which is the knob most likely to restore
the parameter assignment.
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
extern int q(int);
extern void r3(int, int, int);
extern void *lst(void *, u16);
extern void r8f(void *, int, int, int, int, int, int, int);
"""


def build(nwide, nstack, rec, nother):
    decls = "".join("        int w%d = mid(p1 + %d);\n" % (j, j)
                    for j in range(nwide))
    mids = "".join("        snk(mid(w%d));\n" % j for j in range(nwide))
    tot = " + ".join("w%d" % j for j in range(nwide))
    stack = ""
    for j in range(nstack):
        stack += ("        pe = (u16 *)lst(s->listItems, (u16)w%d);\n"
                  "        r8f(s->listItems, pe == 0 ? -1 : mid(*pe), p0,\n"
                  "            w%d, 1, %d, 0, 0);\n"
                  % (j % nwide, j % nwide, j))
    recb = ("        {\n"
            "            int rc = mid(p0 + 9);\n"
            "            snk(mid(rc));\n"
            "            snk(rc);\n"
            "        }\n" if rec else "")
    other = ""
    for j in range(nother):
        other += ("    case %d: {\n"
                  "        int o%d = mid(p0 + %d);\n"
                  "        int o%db = mid(p1 + %d);\n"
                  "        snk(mid(o%d));\n"
                  "        snk(o%d + o%db);\n"
                  "        break;\n    }\n" % (6 + j, j, j, j, j, j, j, j))
    return """
void f(int p0, int p1) {
    S *s = gp;
    int nColumn;
    int k = cls(&nColumn, s->b);
    int tag;
    u16 *pe;

    if (q(0) == 0) { snk(q(1)); }
    r3(s->b, p1, 0);

    switch (k) {
    case 0: snk(mid(p0)); break;
    case 1: snk(mid(p1 * nColumn)); break;
    case 2: {
%s%s%s        snk(%s);
%s        break;
    }
    case 3:
        tag = mid(p1);
        r8f(s->listEntries, 0, p0, tag, 1, 1, 0, tag);
        snk(tag);
        break;
    case 4: break;
    case 5: snk(mid(p1)); break;
%s    }
    r3(s->a, p1, 0);
    snk(s->b);
}
""" % (decls, mids, stack, tot, recb, other)


def probe(body):
    p = "build/try/b5bff4_bs.c"
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
    return (len(code), ins[0][5:], d.get("p0", "?"), d.get("p1", "?"),
            d.get("s", "?"))


print("target: p0=r6 p1=r5 with the pointer OFF r4 (ROM has s=r8)")
print()
gold = []
n = 0
for nwide, nstack, rec, nother in itertools.product(
        (2, 3, 4), (1, 2), (0, 1), (0, 1, 2, 3)):
    r = probe(build(nwide, nstack, rec, nother))
    n += 1
    tag = "wide=%d stack=%d rec=%d other=%d" % (nwide, nstack, rec, nother)
    if r[0] == "FAIL":
        print("%-32s FAIL %s" % (tag, r[1]))
        continue
    size, push, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    moved = s not in ("r4", "?")
    mark = ""
    if faithful and moved:
        mark = "   <== BOTH"
        gold.append((tag, s))
    elif moved:
        mark = "   off r4"
    elif faithful:
        mark = "   faithful"
    print("%-32s %-4d p0=%-4s p1=%-4s s=%-4s%s" % (tag, size, p0, p1, s, mark))
print()
print("compiled %d; faithful AND pointer off r4: %s" % (n, gold if gold else "none"))
