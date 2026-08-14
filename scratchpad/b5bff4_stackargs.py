"""Recorded hypothesis: the last structural features the reproduction lacks are
the eight-argument calls, which push four arguments onto the stack and force the
sub sp reservation, and the address-taken local the classifier writes through.
Add both, then re-sweep the faithful family.
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


def build(nwide, rec, nstack, addr_taken):
    """nstack eight-argument calls inside the wide case; addr_taken decides
    whether the classifier writes through a pointer to a local."""
    decls = "".join("        int w%d = mid(p1 + %d);\n" % (j, j)
                    for j in range(nwide))
    mids = "".join("        snk(mid(w%d));\n" % j for j in range(nwide))
    tot = " + ".join("w%d" % j for j in range(nwide))
    stack = ""
    for j in range(nstack):
        stack += ("        pe = (u16 *)lst(s->listItems, (u16)w%d);\n"
                  "        r8f(s->listItems, pe == 0 ? -1 : mid(*pe), p0,\n"
                  "            w%d, 1, %d, 0, 0);\n" % (j % max(nwide, 1),
                                                        j % max(nwide, 1), j))
    recb = ("        {\n"
            "            int rc = mid(p0 + 9);\n"
            "            snk(mid(rc));\n"
            "            snk(rc);\n"
            "        }\n" if rec else "")
    cl = ("    int nColumn;\n    int k = cls(&nColumn, s->b);\n" if addr_taken
          else "    int nColumn = 3;\n    int k = cls((int *)0, s->b);\n")
    return """
void f(int p0, int p1) {
%s    int tag;
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
    }
    r3(s->a, p1, 0);
    snk(s->b);
}
""" % ("    S *s = gp;\n" + cl, decls, mids, stack, tot, recb)


def probe(body):
    p = "build/try/b5bff4_sa.c"
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


print("real builds  push={r3,r4,r5,r6,r7,r8,sb,sl,lr}  p0=r6 p1=r5  "
      "ROM s=r8 | mine s=r4")
print()
hits = []
n = 0
for nwide, rec, nstack, at in itertools.product(
        (2, 3, 4), (0, 1), (1, 2, 3), (0, 1)):
    r = probe(build(nwide, rec, nstack, at))
    n += 1
    tag = "wide=%d rec=%d stack=%d addr=%d" % (nwide, rec, nstack, at)
    if r[0] == "FAIL":
        print("%-30s FAIL %s" % (tag, r[1]))
        continue
    size, push, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    moved = s not in ("r4", "?")
    print("%-30s %-4d p0=%-4s p1=%-4s s=%-4s %s%s%s"
          % (tag, size, p0, p1, s, push[:30],
             "  faithful" if faithful else "",
             "   <== POINTER OFF r4" if moved else ""))
    if moved:
        hits.append((tag, s, faithful))
print()
print("compiled %d; pointer off r4: %s" % (n, hits if hits else "none"))
