"""Change the exemplar toward this function with edits that do not break its
body: add unused parameters, and make the outer switch run on a call result
instead of a memory read. Watch whether its context leaves r9.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SRC = open("src/overlays/ov000/calls/func_ov000_02050ec4.c").read()
SIG = "void func_ov000_02050ec4(void)"
SW = "    switch (ctx->nActiveState) {"
assert SIG in SRC and SW in SRC


def probe(tag, src):
    p = "scratchpad/bisect_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-30s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ctx = "?"
    for t in ins[:14]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r[0-9]+\]$", t)
        if m and ctx == "?":
            ctx = m.group(1)
    flag = "   <<< DROPPED" if ctx in ("r4", "r5") else ""
    print("%-30s size=%-5d ctx=%-4s%s" % (tag, len(code), ctx, flag))


probe("exemplar", SRC)
probe("plus two params",
      SRC.replace(SIG, "void func_ov000_02050ec4(int nA, int nB)"))

DECL = "extern int ov000_Classify(int *pOut, int nMode);\n"
s = SRC.replace(SIG, DECL + "\n" + SIG)
s = s.replace("    int entry;\n", "    int entry;\n    int nCol;\n")
s = s.replace(SW, "    switch (ov000_Classify(&nCol, ctx->nActiveState)) {")
probe("switch on call result", s)

s2 = s.replace(SIG, "void func_ov000_02050ec4(int nA, int nB)")
probe("params + call switch", s2)
