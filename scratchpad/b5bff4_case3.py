"""Case 3 alone decides it: with case 3 the pointer takes r4, without it r7.
Bisect what inside case 3 does that -- the rebind of the classifier variable, the
tag variable carried across both halves, the cached-pointer store, or the second
eight-argument call.
"""
import sys
import os
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
HEAD = open("scratchpad/_b5bff4_head.txt").read() if os.path.exists(
    "scratchpad/_b5bff4_head.txt") else """typedef unsigned char u8;
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


def case3(rebind, use_tag, cache, second):
    """rebind: reuse k for the new index, or a fresh local.
    use_tag: carry a tag value across both halves, or pass a constant.
    cache: store the pointer on the session at the end.
    second: emit the second eight-argument call."""
    key = "k" if rebind else "nKey"
    decl = "        int nSlot;\n        u16 *pe;\n"
    if not rebind:
        decl += "        int nKey;\n"
    t0 = "        tag = 0;\n        if (pe != 0) {\n            tag = mid(pe[1] & 0xff);\n        }\n" \
        if use_tag else ""
    targ = "tag" if use_tag else "0"
    body = decl + """        nOld = p0 + nColumn * 6;
        %s = p1 + nColumn * 6;
        pe = (u16 *)lst(s->listEntries, (u16)nOld);
%s        if (pe == 0) {
            nSlot = -1;
        } else {
            nSlot = mid(*pe);
        }
        r8f(s->listEntries, nSlot, p0, nOld, 1, 1, 0, %s);
""" % (key, t0, targ)
    if second:
        t1 = ("        if (pe != 0) {\n"
              "            tag = mid(pe[1] & 0xff);\n        }\n"
              if use_tag else "")
        body += """        pe = (u16 *)lst(s->listEntries, (u16)%s);
%s        if (pe == 0) {
            nSlot = -1;
        } else {
            nSlot = mid(*pe);
        }
        r8f(s->listEntries, nSlot, p1, %s, 1, 1, 1, %s);
        s->d = (u8)%s;
""" % (key, t1, key, targ, key)
    if cache:
        body += "        s->pCached = pe;\n"
    return "    case 3: {\n        int nOld;\n" + body + "        break;\n    }\n"


def build(rebind, use_tag, cache, second):
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
%s%s    case 4: break;
    case 5: snk(mid(p1)); break;
    }
    snk(s->b);
    snk(tag);
}
""" % (CASE2, case3(rebind, use_tag, cache, second))


def probe(body):
    p = "build/try/b5bff4_c3.c"
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


print("ROM real   p0=r6 p1=r5 s=r8   |   my real build   p0=r6 p1=r5 s=r4")
print()
for rb, ut, ca, se in itertools.product((0, 1), (0, 1), (0, 1), (0, 1)):
    r = probe(build(rb, ut, ca, se))
    tag = "rebind=%d tag=%d cache=%d 2nd=%d" % (rb, ut, ca, se)
    if r[0] == "FAIL":
        print("%-32s FAIL %s" % (tag, r[1]))
        continue
    size, p0, p1, s = r
    faithful = (p0 == "r6" and p1 == "r5")
    moved = s not in ("r4", "?")
    print("%-32s %-4d p0=%-4s p1=%-4s s=%-4s%s%s"
          % (tag, size, p0, p1, s,
             "  faithful" if faithful else "",
             "   <== BOTH" if (faithful and moved) else
             ("   off r4" if moved else "")))
