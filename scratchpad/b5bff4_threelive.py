"""Recorded plan: reproduce the ROM's case 2 exactly in liveness terms -- two
indices computed up front, the slot and the flag consumed as arguments right
before the eight-argument call, so only three values survive it. Then vary the
few things around it and see whether the ROM's combination, parameters on r6 and
r5 together with the pointer on a high register, is reachable at all.
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
extern int q2(int, int);
extern void r3(int, int, int);
extern void *lst(void *, u16);
extern void r8f(void *, int, int, int, int, int, int, int);
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


def build(with3, with_pre, tail_full):
    pre = ("    if (q(0) == 0) { snk(q(1)); }\n"
           "    r3(s->b, p1, 0);\n" if with_pre else "    r3(s->b, p1, 0);\n")
    tail = ("    s->a = (u8)p1;\n    r3(s->b, p1, 0);\n    snk(q(9));\n"
            "    snk(q(11));\n" if tail_full else "    snk(s->b);\n")
    return """
void f(int p0, int p1) {
    int nColumn;
    int tag;
    S *s = gp;
    int k = cls(&nColumn, s->b);

%s
    switch (k) {
    case 0: snk(mid(p0)); break;
    case 1: snk(mid(p1 * nColumn)); break;
%s%s    case 4: break;
    case 5: snk(mid(p1)); break;
    }
%s}
""" % (pre, CASE2, CASE3 if with3 else "", tail)


def probe(body):
    p = "build/try/b5bff4_tl.c"
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


print("ROM real   p0=r6 p1=r5 s=r8    |    my real build  p0=r6 p1=r5 s=r4")
print()
for w3, wp, tf in itertools.product((0, 1), (0, 1), (0, 1)):
    r = probe(build(w3, wp, tf))
    tag = "case3=%d pre=%d tail=%d" % (w3, wp, tf)
    if r[0] == "FAIL":
        print("%-26s FAIL %s" % (tag, r[1]))
        continue
    size, push, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    moved = s not in ("r4", "?")
    print("%-26s %-4d p0=%-4s p1=%-4s s=%-4s %-32s%s%s"
          % (tag, size, p0, p1, s, push[:32],
             " faithful" if faithful else "",
             "  <== BOTH" if (faithful and moved) else
             ("  off r4" if moved else "")))
