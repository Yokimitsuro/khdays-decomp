"""Search the repro for any form that puts the whole-function pointer in a HIGH
callee-saved register while the two parameters stay on r6 and r5. Target
p0=r6 p1=r5 s=r8 k=r4. Code size may change freely here; the point is to find
the mechanism, which is then carried back to the real function.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
sys.path.insert(0, os.path.join(os.getcwd(), "scratchpad"))
from b5bff4_repro import HDR, BODY, analyse

HITS = []


def show(tag, src):
    d, err = analyse(src)
    if err:
        print("%-26s FAIL %s" % (tag, err))
        return
    p0, p1, s, k = (d.get("p0", "?"), d.get("p1", "?"),
                    d.get("s", "?"), d.get("k", "?"))
    hi = s not in ("r4", "?") and p0 == "r6" and p1 == "r5"
    print("%-26s size=%-5d p0=%-4s p1=%-4s s=%-4s k=%-4s%s"
          % (tag, d["size"], p0, p1, s, k, "   <== HIGH" if hi else ""))
    if hi:
        HITS.append(tag)


show("base", HDR + BODY)

# 1. a second long-lived local produced before the classifier
show("extra_live_before", HDR + BODY.replace(
    "    Sess *s = gp;\n    int nClass = cls(&nColumn, s->bMode);",
    "    Sess *s = gp;\n    int nHold = q0(7);\n"
    "    int nClass = cls(&nColumn, s->bMode);").replace(
    "    q1(s->bMode, nTo, 0);\n}", "    q1(s->bMode, nHold, 0);\n}"))

# 2. a second long-lived local produced after the classifier
show("extra_live_after", HDR + BODY.replace(
    "    q1(s->bMode, nTo, 0);\n\n    switch",
    "    q1(s->bMode, nTo, 0);\n    nTag = q0(7);\n\n    switch").replace(
    "    q1(s->bMode, nTo, 0);\n}", "    q1(s->bMode, nTag, 0);\n}"))

# 3. the pointer reloaded in the tail, so its live range has a hole
show("s_reloaded_in_tail", HDR + BODY.replace(
    "    s->bKind = (u8)nTo;\n    q1(s->bMode, nTo, 0);\n}",
    "    gp->bKind = (u8)nTo;\n    q1(gp->bMode, nTo, 0);\n}"))

# 4. the pointer only used inside the switch, tail through the global
show("s_dead_before_tail", HDR + BODY.replace(
    "    q1(s->bMode, nTo, 0);\n\n    switch",
    "    q1(gp->bMode, nTo, 0);\n\n    switch").replace(
    "    s->bKind = (u8)nTo;\n    q1(s->bMode, nTo, 0);\n}",
    "    gp->bKind = (u8)nTo;\n    q1(gp->bMode, nTo, 0);\n}"))

# 5. the classifier does not read through the pointer
show("cls_no_ptr", HDR + BODY.replace(
    "int nClass = cls(&nColumn, s->bMode);", "int nClass = cls(&nColumn, nFrom);"))

# 6. the pointer taken after the classifier, which no longer needs it
show("cls_no_ptr_s_after", HDR + BODY.replace(
    "    Sess *s = gp;\n    int nClass = cls(&nColumn, s->bMode);",
    "    int nClass = cls(&nColumn, nFrom);\n    Sess *s = gp;"))

# 7. nClass used again after the switch, extending its web
show("nClass_used_after", HDR + BODY.replace(
    "    s->bKind = (u8)nTo;\n    q1(s->bMode, nTo, 0);\n}",
    "    s->bKind = (u8)nTo;\n    q1(s->bMode, nTo, nClass);\n}"))

# 8. both nClass and the pointer used after the switch
show("both_used_after", HDR + BODY.replace(
    "    s->bKind = (u8)nTo;\n    q1(s->bMode, nTo, 0);\n}",
    "    s->bKind = (u8)nClass;\n    q1(s->bMode, nTo, nClass);\n}"))

# 9. the parameters copied into locals, so the params themselves are short
show("params_copied", HDR + BODY.replace(
    "void rep(int nFrom, int nTo) {\n    int nColumn;",
    "void rep(int nFrom0, int nTo0) {\n    int nFrom = nFrom0;\n"
    "    int nTo = nTo0;\n    int nColumn;"))

# 10. fewer cases, so fewer webs compete
for drop in ("case 0:", "case 1:", "case 5:"):
    body = BODY
    i = body.find("    " + drop)
    if i < 0:
        continue
    j = body.find("\n    case ", i + 5)
    if j < 0:
        j = body.rfind("    }\n\n    s->bKind")
    show("drop " + drop, HDR + body[:i] + body[j + 1:])

# 11. the struct accessed through a pointer to a smaller type for the wide
#     offsets, so the pointer's reference count drops
show("split_base", HDR + BODY.replace(
    "    Sess *s = gp;\n",
    "    Sess *s = gp;\n    u8 *pList = (u8 *)gp;\n").replace(
    "s->listItems", "(pList + 0x480)"))

print()
print("HIGH hits:", HITS if HITS else "none")
