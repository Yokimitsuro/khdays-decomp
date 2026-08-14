"""Exhaustive grid over independent source knobs on the repro, collecting every
distinct (p0, p1, s, k) assignment reachable. The ROM's tuple is
p0=r6 p1=r5 s=r8 k=r4, whose top four webs occupy r4, r5, r6, r8 and skip r7 --
something no build of mine has ever produced. If it is reachable at all, this
finds it and names the knobs that get there.
"""
import sys
import os
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
sys.path.insert(0, os.path.join(os.getcwd(), "scratchpad"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM
from b5bff4_repro import HDR, BODY

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
TARGET = ("r6", "r5", "r8", "r4")

DECL = "    Sess *s = gp;\n    int nClass = cls(&nColumn, s->bMode);"


def k_cls(body, v):
    if v == 0:
        return body
    if v == 1:
        return body.replace(DECL,
                            "    int nClass = cls(&nColumn, gp->bMode);\n"
                            "    Sess *s = gp;")
    return body.replace(DECL,
                        "    int nClass;\n    Sess *s = gp;\n\n"
                        "    nClass = cls(&nColumn, s->bMode);")


def k_tail(body, v):
    if v == 0:
        return body
    return body.replace("    s->bKind = (u8)nTo;\n    q1(s->bMode, nTo, 0);\n}",
                        "    gp->bKind = (u8)nTo;\n    q1(gp->bMode, nTo, 0);\n}")


def k_c2(body, v):
    if v == 0:
        return body
    return body.replace(
        "        int nNew = nTo + nColumn * 6;\n"
        "        int nOld = nFrom + nColumn * 6;\n",
        "        int nOld = nFrom + nColumn * 6;\n"
        "        int nNew = nTo + nColumn * 6;\n")


def k_extra(body, v):
    if v == 0:
        return body
    return body.replace("    q1(s->bMode, nTo, 0);\n\n    switch",
                        "    q1(s->bMode, nTo, 0);\n    nTag = q0(7);\n\n    switch")


def k_c5(body, v):
    if v == 0:
        return body
    head, tail = body.split("    case 5: {", 1)
    tail = tail.replace("int bFlag = 0;", "", 1)
    tail = tail.replace("bFlag = 1;", "nClass = 1;")
    tail = tail.replace("bFlag != 0 ?", "nClass != 0 ?")
    tail = tail.replace("u16 nKey = *(u16 *)s->pCachedEntry;",
                        "u16 nKey = *(u16 *)s->pCachedEntry;\n\n        nClass = 0;")
    return head + "    case 5: {" + tail


def k_params(body, v):
    if v == 0:
        return body
    return body.replace(
        "void rep(int nFrom, int nTo) {\n    int nColumn;",
        "void rep(int nFrom0, int nTo0) {\n    int nFrom = nFrom0;\n"
        "    int nTo = nTo0;\n    int nColumn;")


KNOBS = [("cls", k_cls, 3), ("tail", k_tail, 2), ("c2", k_c2, 2),
         ("extra", k_extra, 2), ("c5", k_c5, 2), ("params", k_params, 2)]


def probe(code):
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {}
    for t in ins[:16]:
        m = re.match(r"^ldr (r\w+), \[r(?:1|2)\]$", t)
        if m and "s" not in d and m.group(1) not in ("r0",):
            d["s"] = m.group(1)
        m = re.match(r"^mov (r\w+), r0$", t)
        if m:
            if "p0" not in d:
                d["p0"] = m.group(1)
            elif "k" not in d:
                d["k"] = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and "p1" not in d:
            d["p1"] = m.group(1)
    return (d.get("p0", "?"), d.get("p1", "?"), d.get("s", "?"), d.get("k", "?"))


seen = {}
hits = []
n = 0
for combo in itertools.product(*[range(k[2]) for k in KNOBS]):
    body = BODY
    for (name, fn, _), v in zip(KNOBS, combo):
        body = fn(body, v)
    p = "build/try/b5bff4_gr.c"
    open(p, "w").write(HDR + body)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception:
        continue
    n += 1
    t = probe(code)
    tag = " ".join("%s=%d" % (k[0], v) for k, v in zip(KNOBS, combo))
    seen.setdefault(t, tag)
    if t == TARGET:
        hits.append(tag)

print("compiled %d variants, %d distinct assignments" % (n, len(seen)))
for t, tag in sorted(seen.items()):
    star = "   <== ROM" if t == TARGET else ""
    print("  p0=%-4s p1=%-4s s=%-4s k=%-4s  first seen: %s%s"
          % (t[0], t[1], t[2], t[3], tag, star))
print()
print("ROM-tuple hits:", hits if hits else "none")
