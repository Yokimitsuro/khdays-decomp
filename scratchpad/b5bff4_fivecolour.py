"""On the faithful harness, report the classifier's register AND the branch tag's
register, and sweep the four things that could stop them sharing a colour:
whether each is live after the switch, the tag's scope, and whether the
classifier variable is rebound inside case 3. The ROM keeps them apart, at r4
and r7; my build shares r7.
"""
import sys
import os
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
sys.path.insert(0, os.path.join(os.getcwd(), "scratchpad"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM
from b5bff4_nested import HEAD, NESTED, CASE2

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)


def case3(rebind, tag_scope):
    key = "k" if rebind else "nKey"
    decl = "        u16 *pe;\n        int slot;\n"
    if not rebind:
        decl += "        int nKey;\n"
    if tag_scope:
        decl += "        int tag;\n"
    return """    case 3: {
        int nOld = p0 + nColumn * 6;
%s
        %s = p1 + nColumn * 6;
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

        pe = (u16 *)lst(s->listEntries, (u16)%s);
        if (pe != 0) {
            tag = mid(pe[1] & 0xff);
        }
        if (pe == 0) {
            slot = -1;
        } else {
            slot = mid(*pe);
        }
        r8f(s->listEntries, slot, p1, %s, 1, 1, 1, tag);
        s->d = (u8)%s;
        s->pCached = pe;
        break;
    }
""" % (decl, key, key, key, key)


def build(rebind, tag_scope, tag_after, k_after):
    body = NESTED + "    case 1: snk(mid(p1 * nColumn)); break;\n"
    body += CASE2 + case3(rebind, tag_scope)
    body += "    case 4: break;\n    case 5: snk(mid(p1)); break;\n"
    decls = "    int nColumn;\n"
    if not tag_scope:
        decls += "    int tag;\n"
    tail = "    s->a = (u8)p1;\n    r3(s->b, p1, 0);\n"
    if tag_after and not tag_scope:
        tail += "    snk(tag);\n"
    if k_after:
        tail += "    snk(k);\n"
    return """
void f(int p0, int p1) {
%s    S *s = gp;
    int k = cls(&nColumn, s->b);

    r3(s->b, p1, 0);

    switch (k) {
%s    }
%s}
""" % (decls, body, tail)


def probe(body):
    p = "build/try/b5bff4_fc.c"
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
    kreg = "?"
    for t in ins:
        m = re.match(r"^cmp (r\w+), #5$", t)
        if m:
            kreg = m.group(1)
            break
    # the tag is the register zeroed right after the case-3 list call
    treg = "?"
    for n, t in enumerate(ins):
        if n > 60:
            m = re.match(r"^movs? (r\w+), #0$", t)
            if m and m.group(1) not in ("r0", "r1", "r2", "r3"):
                treg = m.group(1)
                break
    return (len(code), d.get("p0", "?"), d.get("p1", "?"), d.get("s", "?"),
            kreg, treg)


print("ROM: p0=r6 p1=r5 s=r8 k=r4 tag=r7  (FIVE colours)")
print("me : p0=r6 p1=r5 s=r4 k=r7 tag=r7  (four, k and tag share)")
print()
for rb, ts, ta, ka in itertools.product((0, 1), (0, 1), (0, 1), (0, 1)):
    r = probe(build(rb, ts, ta, ka))
    tag = "rebind=%d tagscope=%d tagAft=%d kAft=%d" % (rb, ts, ta, ka)
    if r[0] == "FAIL":
        print("%-38s FAIL %s" % (tag, r[1]))
        continue
    size, p0, p1, s, k, t = r
    five = (k != t and k != "?" and t != "?")
    print("%-38s %-4d p0=%-4s p1=%-4s s=%-4s k=%-4s tag=%-4s%s"
          % (tag, size, p0, p1, s, k, t, "   <== FIVE COLOURS" if five else ""))
