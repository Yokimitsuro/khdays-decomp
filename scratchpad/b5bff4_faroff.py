"""The repro's struct is 16 bytes, so every field access is a direct load off the
pointer. The real struct is 0x4a8, so the list members at 0x480 and 0x498 need an
`add rX, s, #0x480` first, which materialises an extra temporary at every such
access -- ten of them in the real function. That is a source of webs and of
pressure the repro has never had. Add it.
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
typedef struct {
    int a; int b; int c; int d;
    u8 pad[0x470];
    u8 listItems[0x18];
    u8 listEntries[0xc];
    void *pCached;
} S;
extern S *gp;
extern void snk(int);
extern void snkp(void *);
extern int cls(int);
extern int mid(int);
extern int q(int);
extern void r3(int, int, int);
extern void *lst(void *, int);
"""


def build(nfar, nwide=4, rec=1):
    far = "".join("        snkp(lst(s->listItems, w%d));\n" % (j % nwide)
                  for j in range(nfar))
    decls = "".join("        int w%d = mid(p1 + %d);\n" % (j, j)
                    for j in range(nwide))
    mids = "".join("        snk(mid(w%d));\n" % j for j in range(nwide))
    tot = " + ".join("w%d" % j for j in range(nwide))
    recb = ("        {\n"
            "            int rc = mid(p0 + 9);\n"
            "            snk(mid(rc));\n"
            "            snk(rc);\n"
            "        }\n" if rec else "")
    return """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);
    int tag;

    if (q(0) == 0) { snk(q(1)); }
    r3(s->b, p1, 0);

    switch (k) {
    case 0: snk(mid(p0)); break;
    case 1: snk(mid(p1)); break;
    case 2: {
%s%s%s        snk(%s);
%s        break;
    }
    case 3:
        tag = mid(p1);
        snkp(lst(s->listEntries, tag));
        snk(tag);
        break;
    case 4: break;
    case 5: snk(mid(p1)); break;
    }
    r3(s->a, p1, 0);
    snk(s->b);
}
""" % (decls, far, mids, tot, recb)


def probe(body):
    p = "build/try/b5bff4_fo.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        return ("FAIL", str(ex).split("\n")[0][:50])
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {}
    for t in ins[:16]:
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
for nfar, nwide, rec in itertools.product((0, 2, 4, 6, 8), (3, 4), (0, 1)):
    r = probe(build(nfar, nwide, rec))
    tag = "far=%d wide=%d rec=%d" % (nfar, nwide, rec)
    if r[0] == "FAIL":
        print("%-26s FAIL %s" % (tag, r[1]))
        continue
    size, push, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    moved = faithful and s != "r4"
    print("%-26s %-4d p0=%-4s p1=%-4s s=%-4s %s%s%s"
          % (tag, size, p0, p1, s, push[:30],
             "  faithful" if faithful else "",
             "   <== POINTER MOVED" if moved else ""))
    if moved:
        hits.append(tag)
print()
print("pointer off r4 in a faithful config:", hits if hits else "none")
