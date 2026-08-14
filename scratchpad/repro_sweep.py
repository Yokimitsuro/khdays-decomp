"""Fast harness on the minimal reproduction: report which physical register the
session pointer and the class value land in for each source perturbation. The
target is the ROM's shape, session in a HIGHER register than the class.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
BASE = open("scratchpad/repro.c").read()


def probe(tag, src):
    p = "scratchpad/repro_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ses = cls = "?"
    for t in ins[:14]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r2\]$", t)
        if m and ses == "?":
            ses = m.group(1)
        m = re.match(r"mov (r[0-9]+|sb|sl|fp), r0$", t)
        if m and cls == "?" and ses != "?":
            cls = m.group(1)
    print("%-22s size=%-4d push=%-28s session=%-4s class=%-4s"
          % (tag, len(code), ins[0][5:] if ins else "?", ses, cls))


probe("base", BASE)

# the session used many more times
s = BASE.replace("    tail(s->bMode, nTo, 0);",
                 "    tail(s->bMode, nTo, s->bKind);\n"
                 "    tail(s->bIndex, s->bKind, s->bMode);\n"
                 "    tail(s->bMode, s->bIndex, s->bKind);")
probe("session_more_uses", s)

# the class used again after the switch
s = BASE.replace("    tail(s->bMode, nTo, 0);",
                 "    tail(s->bMode, nTo, nClass);")
probe("class_live_after", s)

# an extra long lived variable defined before the session
s = BASE.replace("    Ctx *s = g_ctx;",
                 "    int nEarly = nFrom + nTo;\n    Ctx *s = g_ctx;")
s = s.replace("    tail(s->bMode, nTo, 0);", "    tail(s->bMode, nTo, nEarly);")
probe("extra_before", s)

# an extra long lived variable defined after the class
s = BASE.replace("    call3(s->bMode, nTo, 0);",
                 "    nLate = nFrom + nTo;\n    call3(s->bMode, nTo, 0);")
s = s.replace("    int nTag;", "    int nTag;\n    int nLate;")
s = s.replace("    tail(s->bMode, nTo, 0);", "    tail(s->bMode, nTo, nLate);")
probe("extra_after", s)

# the session dereferenced through a second pointer in the tail
s = BASE.replace("    tail(s->bMode, nTo, 0);",
                 "    tail(g_ctx->bMode, nTo, 0);")
probe("tail_global", s)

# the class not a variable, switch on the call
s = BASE.replace("    int nClass = classify(&nColumn, s->bMode);",
                 "    int nClass;\n")
s = s.replace("    call3(s->bMode, nTo, 0);",
              "    nClass = classify(&nColumn, s->bMode);\n"
              "    call3(s->bMode, nTo, 0);")
probe("class_later", s)
