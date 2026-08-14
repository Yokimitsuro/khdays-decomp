"""Rebinding the session mid-function flips the pair but costs eight bytes.
Look for a second definition point that mwcc folds away, or a copy it coalesces,
so the ranking changes without the code changing.
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

SW = "    switch (nClass) {"
probe("self_assign", BASE.replace(SW, "    s = s;\n" + SW))
probe("copy_var", BASE.replace(
    "    Ctx *s = g_ctx;",
    "    Ctx *s0 = g_ctx;\n    Ctx *s = s0;"))
probe("copy_after_classify", BASE.replace(
    "    int nClass = classify(&nColumn, s->bMode);",
    "    int nClass = classify(&nColumn, s->bMode);\n"
    "    Ctx *s2 = s;").replace("s->", "s2->").replace(
    "    Ctx *s2 = s2;", "    Ctx *s2 = s;").replace(
    "    Ctx *s = g_ctx;", "    Ctx *s = g_ctx;").replace(
    "classify(&nColumn, s2->bMode)", "classify(&nColumn, s->bMode)").replace(
    "lookup(s,", "lookup(s2,").replace("call8(s,", "call8(s2,"))
probe("ternary_bind", BASE.replace(
    "    Ctx *s = g_ctx;",
    "    Ctx *s = g_ctx ? g_ctx : g_ctx;"))
probe("plus_zero", BASE.replace(
    "    Ctx *s = g_ctx;",
    "    Ctx *s = (Ctx *)((char *)g_ctx + 0);"))
probe("via_int", BASE.replace(
    "    Ctx *s = g_ctx;",
    "    Ctx *s = (Ctx *)(int)g_ctx;"))
