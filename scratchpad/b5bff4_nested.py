"""Last gross structural difference: the real case 0 holds two nested switches in
a row, on each parameter, with their own per-branch temporaries. Every case 0 in
the reproduction so far was a one-liner. Add the real shape and see whether it
breaks the coupling between the parameter assignment and the pointer's register.
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
    u16 w14;
    int f0c;
    u8 bits[0x470];
    u8 listItems[0x18];
    u8 listEntries[0xc];
    void *pCached;
} S;
extern S *gp;
extern void snk(int);
extern int cls(int *pOut, int nCode);
extern int mid(int);
extern int q2(int, int);
extern int nofn(void);
extern void r3(int, int, int);
extern void a3(int, int, int);
extern void a4(int, int, int, int);
extern void *lst(void *, u16);
extern void *nextobj(void *, void *);
extern void r8f(void *, int, int, int, int, int, int, int);
"""

NESTED = """    case 0:
        switch (p0) {
        case 0:
            a3(s->w14, s->f0c, 0);
            break;
        case 1: {
            int nValue = nofn();

            a4(4, 0, 0, 0);
            a3(p0 + 2, nValue, 0);
            break;
        }
        case 2: {
            int nValue;
            void *pObject = nextobj(s->listItems, 0);

            if (pObject == 0) {
                pObject = nextobj(s->listEntries, 0);
            }
            if (pObject != 0 && nofn() != 0) {
                nValue = 1;
            } else {
                nValue = 0;
            }
            a4(5, 0, 0, 0);
            a3(p0 + 2, nValue, 0);
            break;
        }
        }

        switch (p1) {
        case 0:
            a3(s->w14, s->f0c, 1);
            break;
        case 1:
            if (s->bits[0] == 0xff) {
                a3(3, 0, 1);
            } else {
                a3(3, 1, 1);
            }
            break;
        case 2:
            a3(4, 1, 1);
            break;
        }
        break;
"""

CASE2 = """    case 2: {
        int nNew = p1 + nColumn * 6;
        int nOld = p0 + nColumn * 6;
        u16 *pe;
        int flag;
        int slot;

        pe = (u16 *)lst(s->listItems, (u16)nOld);
        flag = 0;
        if (q2(0, *pe) != 0 && q2(1, *pe) != 0) {
            flag = 1;
        }
        if (pe == 0) {
            slot = -1;
        } else {
            slot = mid(*pe);
        }
        r8f(s->listItems, slot, p0, nOld, 1, flag, 0, 0);

        pe = (u16 *)lst(s->listItems, (u16)nNew);
        flag = 0;
        if (q2(0, *pe) != 0 && q2(1, *pe) != 0) {
            flag = 1;
        }
        if (pe == 0) {
            slot = -1;
        } else {
            slot = mid(*pe);
        }
        r8f(s->listItems, slot, p1, nNew, 1, flag, 1, 0);
        s->c = (u8)(nColumn * 6 + p1);
        break;
    }
"""

CASE3 = """    case 3: {
        int nOld = p0 + nColumn * 6;
        u16 *pe;
        int slot;

        k = p1 + nColumn * 6;
        pe = (u16 *)lst(s->listEntries, (u16)nOld);
        tag = 0;
        if (pe != 0) {
            tag = mid(pe[1] & 0xff);
        }
        if (pe == 0) {
            slot = -1;
        } else {
            slot = mid(*pe);
        }
        r8f(s->listEntries, slot, p0, nOld, 1, 1, 0, tag);

        pe = (u16 *)lst(s->listEntries, (u16)k);
        if (pe != 0) {
            tag = mid(pe[1] & 0xff);
        }
        if (pe == 0) {
            slot = -1;
        } else {
            slot = mid(*pe);
        }
        r8f(s->listEntries, slot, p1, k, 1, 1, 1, tag);
        s->d = (u8)k;
        s->pCached = pe;
        break;
    }
"""


def build(nested, with2, with3):
    body = (NESTED if nested else "    case 0: snk(mid(p0)); break;\n")
    body += "    case 1: snk(mid(p1 * nColumn)); break;\n"
    if with2:
        body += CASE2
    if with3:
        body += CASE3
    body += "    case 4: break;\n    case 5: snk(mid(p1)); break;\n"
    return """
void f(int p0, int p1) {
    int nColumn;
    int tag;
    S *s = gp;
    int k = cls(&nColumn, s->b);

    r3(s->b, p1, 0);

    switch (k) {
%s    }
    s->a = (u8)p1;
    r3(s->b, p1, 0);
    snk(tag);
}
""" % body


def probe(body):
    p = "build/try/b5bff4_ns.c"
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


print("ROM real  p0=r6 p1=r5 s=r8   |   my build  p0=r6 p1=r5 s=r4")
print()
for nest, w2, w3 in itertools.product((0, 1), (0, 1), (0, 1)):
    r = probe(build(nest, w2, w3))
    tag = "nested=%d case2=%d case3=%d" % (nest, w2, w3)
    if r[0] == "FAIL":
        print("%-28s FAIL %s" % (tag, r[1]))
        continue
    size, push, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    both = faithful and s == "r8"
    print("%-28s %-4d p0=%-4s p1=%-4s s=%-4s %-30s%s%s"
          % (tag, size, p0, p1, s, push[:30],
             " faithful" if faithful else "",
             "  <== ROM EXACT" if both else ("  s=r8" if s == "r8" else "")))
