"""What promotes a value ahead of the parameters? Sweep on the reproduction,
reporting the virtual map. Base is r6 r4 r5 r7 ..., the shape wanted has the
class first: r6 r8 r5 r4 r7 in the real function's register count.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
BASE = open("scratchpad/repro2.c").read()
RE = re.compile(r"\b(r1[0-5]|r[0-9]|sb|sl|fp|ip|lr|sp|pc)\b")
ALIAS = {"sb": "r9", "sl": "r10", "fp": "r11", "ip": "r12"}
FIXED = {"sp", "pc", "lr", "r0", "r1", "r2", "r3", "r12"}


def vmap(code):
    order = []
    for i in md.disasm(bytes(code), 0):
        t = i.mnemonic + " " + i.op_str
        if t.startswith(("push", "pop", "stmdb", "ldmia")):
            continue
        for m in RE.finditer(t):
            r = ALIAS.get(m.group(1), m.group(1))
            if r not in FIXED and r not in order:
                order.append(r)
    return " ".join(order)


def probe(tag, src):
    p = "scratchpad/repro2_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return
    print("%-26s size=%-5d map=%s" % (tag, len(code), vmap(code)))


PLAIN = "    Ctx *s = g_ctx;"
CAST = "    Ctx *s = (Ctx *)(int)g_ctx;"
probe("base", BASE)
probe("cast", BASE.replace(PLAIN, CAST))

# the class used in many more places, to raise its usage count
more = BASE.replace("        case 0:\n            call3(s->bIndex, s->bKind, 0);",
                    "        case 0:\n            nClass = s->bIndex;\n"
                    "            call3(nClass, s->bKind, 0);")
probe("cast+cls_case0", more.replace(PLAIN, CAST))

# the parameters copied through the stack, to demote them
demote = BASE.replace("void repro2(int nFrom, int nTo) {",
                      "void repro2(int nFrom0, int nTo0) {\n"
                      "    int nFrom = (int)nFrom0;\n"
                      "    int nTo = (int)nTo0;")
probe("cast+p_demote", demote.replace(PLAIN, CAST))

# the class assigned before the parameters are first used
early = BASE.replace("    int nClass = classify(&nColumn, s->bMode);",
                     "    int nClass = classify(&nColumn, s->bMode);")
early = early.replace("    call3(s->bMode, nTo, 0);",
                      "    call3(s->bMode, nClass, 0);\n"
                      "    call3(s->bMode, nTo, 0);", 1)
probe("cls_used_early", early)
probe("cast+cls_early", early.replace(PLAIN, CAST))
