"""The ROM allocates the session last of the three, which is how an allocator
treats a value it can rematerialise. A pointer read from a const global is
exactly that. Probe qualifier placements on the reproduction.
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
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
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
    print("%-24s size=%-4d push=%-30s session=%-4s class=%-4s"
          % (tag, len(code), ins[0][5:] if ins else "?", ses, cls))


probe("base", BASE)
probe("ext_const", BASE.replace("extern Ctx *g_ctx;",
                                "extern Ctx *const g_ctx;"))
probe("local_const", BASE.replace("    Ctx *s = g_ctx;",
                                  "    Ctx *const s = g_ctx;"))
probe("both_const", BASE.replace("extern Ctx *g_ctx;",
                                 "extern Ctx *const g_ctx;")
      .replace("    Ctx *s = g_ctx;", "    Ctx *const s = g_ctx;"))
probe("target_const", BASE.replace("extern Ctx *g_ctx;",
                                   "extern const Ctx *g_ctx;")
      .replace("    Ctx *s = g_ctx;", "    const Ctx *s = g_ctx;")
      .replace("s->bIndex = (u8)nClass;", "")
      .replace("s->bKind = (u8)nTo;", ""))
probe("array_global", BASE.replace("extern Ctx *g_ctx;",
                                   "extern Ctx *g_ctx[1];")
      .replace("    Ctx *s = g_ctx;", "    Ctx *s = g_ctx[0];"))
