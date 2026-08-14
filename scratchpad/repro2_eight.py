"""The exemplar saves eight callee-saved registers and its context lands sixth;
this function saves seven and its session lands first. Test whether the number
of saved registers is what decides, by forcing an eighth in the reproduction.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
BASE = open("scratchpad/repro2.c").read()


def probe(tag, src):
    p = "scratchpad/repro2_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ctx = "?"
    for t in ins[:14]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r[0-9]+\]$", t)
        if m and ctx == "?":
            ctx = m.group(1)
    saved = sorted(set(re.findall(r"\b(r[4-9]|r1[01]|sb|sl|fp)\b",
                                  ins[0] if ins else "")))
    print("%-26s size=%-5d ctx=%-4s saved=%d %s"
          % (tag, len(code), ctx, len(saved), ",".join(saved)))


probe("base", BASE)

# add two long lived values used at both ends, forcing more saved registers
s = BASE.replace("void repro2(int nFrom, int nTo) {",
                 "void repro2(int nFrom, int nTo, int nA, int nB) {")
s = s.replace("    call3(s->bMode, nTo, 0);",
              "    call3(s->bMode, nTo, nA);", 1)
s = s.replace("    s->bKind = (u8)nTo;\n    call3(s->bMode, nTo, 0);",
              "    s->bKind = (u8)nTo;\n    call3(s->bMode, nA, nB);")
probe("two_more_params", s)

# one extra long lived local
s2 = BASE.replace("    Ctx *s = g_ctx;",
                  "    Ctx *s = g_ctx;\n    int nHold;")
s2 = s2.replace("    call3(s->bMode, nTo, 0);",
                "    nHold = classify(&nColumn, 1);\n"
                "    call3(s->bMode, nTo, 0);", 1)
s2 = s2.replace("    s->bKind = (u8)nTo;\n    call3(s->bMode, nTo, 0);",
                "    s->bKind = (u8)nTo;\n    call3(s->bMode, nTo, nHold);")
probe("one_more_local", s2)

# three extra long lived locals
s3 = BASE.replace("    Ctx *s = g_ctx;",
                  "    Ctx *s = g_ctx;\n    int nH1;\n    int nH2;\n"
                  "    int nH3;")
s3 = s3.replace("    call3(s->bMode, nTo, 0);",
                "    nH1 = classify(&nColumn, 1);\n"
                "    nH2 = classify(&nColumn, 2);\n"
                "    nH3 = classify(&nColumn, 3);\n"
                "    call3(s->bMode, nTo, 0);", 1)
s3 = s3.replace("    s->bKind = (u8)nTo;\n    call3(s->bMode, nTo, 0);",
                "    s->bKind = (u8)nTo;\n    call3(nH1, nH2, nH3);")
probe("three_more_locals", s3)
