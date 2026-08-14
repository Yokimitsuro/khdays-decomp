"""Minimal shapes of the exemplar: does its high context survive when the body
is reduced to a single store, with and without the other locals? That separates
the declarations from the body once and for all.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SRC = open("src/overlays/ov000/calls/func_ov000_02050ec4.c").read()
HEAD = SRC.split("void func_ov000_02050ec4(void)\n{\n", 1)[0]
DECLS = ("    Ov000LoadPageContext *ctx = data_ov000_0205ac24;\n"
         "    int i;\n    u32 j;\n    int cur[2];\n"
         "    Ov000ScrollWork w;\n    int move;\n    int entry;\n")
STORE = "\n    ctx->nActiveState = 1;\n"


def probe(tag, inner):
    src = HEAD + "void func_ov000_02050ec4(void)\n{\n" + inner + "\n}\n"
    open("scratchpad/bisect_t.c", "w").write(src)
    try:
        o = compile_c("scratchpad/bisect_t.c", False)
        code, _ = text_relocs(o)
    except Exception:
        print("%-26s FAIL" % tag)
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ctx = "?"
    for t in ins[:12]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r[0-9]+\]$", t)
        if m and ctx == "?":
            ctx = m.group(1)
    print("%-26s size=%-5d ctx=%-4s push=%s"
          % (tag, len(code), ctx, ins[0][5:] if ins else "none"))


probe("all decls + one store", DECLS + STORE)
probe("ctx only + one store",
      "    Ov000LoadPageContext *ctx = data_ov000_0205ac24;\n" + STORE)
