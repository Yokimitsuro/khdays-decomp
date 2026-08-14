"""Broad sweep on the extended reproduction, which now pushes the same nine
registers as the real function and shows the same assignment. Looking for any
perturbation that puts the session in a higher register than the class.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
BASE = open("scratchpad/repro2.c").read()
NUM = {"r4": 4, "r5": 5, "r6": 6, "r7": 7, "r8": 8, "sb": 9, "sl": 10}


def probe(tag, src):
    p = "scratchpad/repro2_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ses = cls = "?"
    for t in ins[:14]:
        m = re.match(r"ldr (r[0-9]+|sb|sl), \[r2\]$", t)
        if m and ses == "?":
            ses = m.group(1)
        m = re.match(r"mov (r[0-9]+|sb|sl), r0$", t)
        if m and cls == "?" and ses != "?":
            cls = m.group(1)
    flag = ""
    if ses in NUM and cls in NUM and NUM[ses] > NUM[cls]:
        flag = "   <<< FLIPPED"
    print("%-26s size=%-5d session=%-4s class=%-4s%s"
          % (tag, len(code), ses, cls, flag))


probe("base", BASE)

# the tail reads the context through the global instead of the local
probe("tail_global", BASE.replace(
    "    s->bKind = (u8)nTo;\n    call3(s->bMode, nTo, 0);",
    "    g_ctx->bKind = (u8)nTo;\n    call3(g_ctx->bMode, nTo, 0);"))

# the first call reads the context through the global
probe("head_global", BASE.replace(
    "    call3(s->bMode, nTo, 0);", "    call3(g_ctx->bMode, nTo, 0);", 1))

# the classifier reads the mode through the global
probe("classify_global", BASE.replace(
    "    int nClass = classify(&nColumn, s->bMode);",
    "    int nClass = classify(&nColumn, g_ctx->bMode);"))

# no session local at all
s = BASE.replace("    Ctx *s = g_ctx;\n", "")
s = s.replace("s->", "g_ctx->").replace("lookup(s,", "lookup(g_ctx,")
s = s.replace("call8(s,", "call8(g_ctx,")
probe("no_local", s)

# the session bound a second time in the middle
probe("rebind_mid", BASE.replace(
    "    switch (nClass) {", "    s = g_ctx;\n    switch (nClass) {"))

# case order: 3 before 2
head, rest = BASE.split("    case 2: {", 1)
c2, rest2 = rest.split("    case 3: {", 1)
c3, tail = rest2.split("    }\n    }\n\n    s->bKind", 1)
probe("case3_first", head + "    case 3: {" + c3 + "    case 2: {" + c2
      + "    }\n    }\n\n    s->bKind" + tail)
