"""Recorded next hypothesis: raise the number of values live at the same time
inside case 2, so the branch's webs are coloured before the whole-function
pointer, and watch for the ROM's fingerprint -- the top-level webs skipping r7
and the pointer landing on a high register.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
sys.path.insert(0, os.path.join(os.getcwd(), "scratchpad"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM
from b5bff4_repro import HDR, BODY

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)


def probe(code):
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {}
    for t in ins[:16]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and "s" not in d:
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
    # which callee-saved registers the four top-level webs occupy
    top = set(v for kk, v in d.items() if kk in ("p0", "p1", "s", "k"))
    return d, top


def show(tag, src):
    p = "build/try/b5bff4_pr.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    d, top = probe(code)
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    push = ins[0]
    skip7 = "r7" not in top
    print("%-24s size=%-5d p0=%-4s p1=%-4s s=%-4s k=%-4s top=%-22s%s"
          % (tag, len(code), d.get("p0", "?"), d.get("p1", "?"),
             d.get("s", "?"), d.get("k", "?"), ",".join(sorted(top)),
             "   SKIPS r7" if skip7 else ""))


show("base", HDR + BODY)

# Add N further indices to case 2, all live across the first list call, so the
# branch needs more registers at once.
ANCHOR = "        int nNew = nTo + nColumn * 6;\n"
CALL = "        q5(s->listItems, nSlot, nFrom, nOld, 1, bFlag, 0, 0);\n"
assert ANCHOR in BODY and CALL in BODY
for n in (1, 2, 3, 4):
    decls = "".join("        int nX%d = nTo + nColumn * %d;\n" % (i, 7 + i)
                    for i in range(n))
    uses = "".join("        q1(nX%d, nFrom, 0);\n" % i for i in range(n))
    src = BODY.replace(ANCHOR, ANCHOR + decls)
    src = src.replace(CALL, CALL + uses)
    show("case2 +%d live" % n, HDR + src)

# Same, but the extra values are live from before the switch, so they compete
# with the pointer directly.
for n in (1, 2, 3):
    decls = "".join("    int nY%d = q0(%d);\n" % (i, 20 + i) for i in range(n))
    uses = "".join("    q1(nY%d, nTo, 0);\n" % i for i in range(n))
    src = BODY.replace("    q1(s->bMode, nTo, 0);\n\n    switch",
                       "    q1(s->bMode, nTo, 0);\n\n    switch")
    src = src.replace("    Sess *s = gp;\n", "    Sess *s = gp;\n" + decls)
    src = src.replace("    s->bKind = (u8)nTo;\n",
                      uses + "    s->bKind = (u8)nTo;\n")
    show("global +%d live" % n, HDR + src)
