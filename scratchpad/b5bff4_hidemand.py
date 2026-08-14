"""At four callee-saved registers the repro shows the ROM's pattern (classifier
on r4, pointer above); from five up it flips to mine (pointer on r4). The real
function needs seven. So search at that fixed demand for any configuration that
still shows the ROM's pattern, and read off what causes it.
"""
import sys
import os
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
HEAD = """typedef struct { int a; int b; int c; int d; } S;
extern S *gp;
extern void snk(int);
extern int cls(int);
extern int mid(int);
extern int q(int);
extern void r3(int, int, int);
"""


def build(nwide, s_in_wide, surv, tag, wide_case):
    decls = "".join("        int w%d = mid(p1 + %d);\n" % (i, i)
                    for i in range(nwide))
    mids = "".join("        snk(mid(w%d));\n" % i for i in range(nwide))
    tot = " + ".join("w%d" % i for i in range(nwide)) or "0"
    sline = "        snk(s->c);\n" if s_in_wide else ""
    wide = "    case %d: {\n%s%s%s        snk(%s);\n        break;\n    }\n" % (
        wide_case, decls, sline, mids, tot)
    tagblk = ("    case 3:\n        tag = mid(p1);\n"
              "        snk(mid(tag));\n        snk(tag);\n        break;\n"
              if tag else "    case 3: snk(mid(p0)); break;\n")
    survblk = "    if (q(0) == 0) { snk(q(1)); }\n" if surv else ""
    others = "".join("    case %d: snk(mid(p0)); break;\n" % i
                     for i in (0, 1, 2) if i != wide_case)
    body = ""
    for i in (0, 1, 2):
        if i == wide_case:
            body += wide
        else:
            body += "    case %d: snk(mid(p0)); break;\n" % i
    return """
void f(int p0, int p1) {
    S *s = gp;
    int k = cls(s->b);
    int tag;

%s    r3(s->b, p1, 0);

    switch (k) {
%s%s    }
    r3(s->a, p1, 0);
    snk(s->b);
}
""" % (survblk, body, tagblk)


def probe(tag, body):
    p = "build/try/b5bff4_hd.c"
    open(p, "w").write(HEAD + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        return None
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
    kreg = "?"
    for t in ins:
        m = re.match(r"^cmp (r\w+), #3$", t)
        if m:
            kreg = m.group(1)
            break
    nsaved = len([x for x in re.findall(r"r\d+|sb|sl|fp",
                                        ins[0]) if x not in ("r3",)])
    return (len(code), ins[0][5:], d.get("p0", "?"), d.get("p1", "?"),
            d.get("s", "?"), kreg)


hits = []
for nwide, sw, sv, tg, wc in itertools.product(
        (4, 5), (0, 1), (0, 1), (0, 1), (1, 2)):
    tag = "w=%d s_in=%d surv=%d tag=%d case=%d" % (nwide, sw, sv, tg, wc)
    r = probe(tag, build(nwide, sw, sv, tg, wc))
    if r is None:
        print("%-32s FAIL" % tag)
        continue
    size, push, p0, p1, s, k = r
    rom_like = s not in ("r4", "?")
    print("%-32s %-4d p0=%-4s p1=%-4s s=%-4s k=%-4s %s%s"
          % (tag, size, p0, p1, s, k, push[:34],
             "  <== ROM-like" if rom_like else ""))
    if rom_like:
        hits.append(tag)
print()
print("ROM-like at high demand:", hits if hits else "none")
