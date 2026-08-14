"""With the cast the session ranks last, which is the ROM's position for it. The
ROM also ranks the CLASS first, ahead of both parameters. Sweep for what moves a
value to the front of the allocation order.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
BASE = open("scratchpad/repro2.c").read()
CAST = ("    Ctx *s = (Ctx *)(int)g_ctx;")
PLAIN = "    Ctx *s = g_ctx;"
assert PLAIN in BASE


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
    r = {"p1": "?", "p2": "?", "ses": "?", "cls": "?"}
    for t in ins[:16]:
        m = re.match(r"mov (r[0-9]+|sb|sl), r0$", t)
        if m and r["p1"] == "?" and r["ses"] == "?":
            r["p1"] = m.group(1)
            continue
        m = re.match(r"mov (r[0-9]+|sb|sl), r1$", t)
        if m and r["p2"] == "?":
            r["p2"] = m.group(1)
            continue
        m = re.match(r"ldr (r[0-9]+|sb|sl), \[r2\]$", t)
        if m and r["ses"] == "?":
            r["ses"] = m.group(1)
            continue
        m = re.match(r"mov (r[0-9]+|sb|sl), r0$", t)
        if m and r["cls"] == "?" and r["ses"] != "?":
            r["cls"] = m.group(1)
    print("%-26s size=%-5d p1=%-4s p2=%-4s ses=%-4s cls=%-4s"
          % (tag, len(code), r["p1"], r["p2"], r["ses"], r["cls"]))


CB = BASE.replace(PLAIN, CAST)
probe("cast", CB)

# the class also cast through an integer
probe("cast+cls_cast", CB.replace(
    "    int nClass = classify(&nColumn, s->bMode);",
    "    int nClass = (int)classify(&nColumn, s->bMode);"))

# the parameters cast, to push them later
probe("cast+p_cast", CB.replace(
    "void repro2(int nFrom, int nTo) {",
    "void repro2(int nFrom0, int nTo0) {\n"
    "    int nFrom = (int)nFrom0;\n    int nTo = (int)nTo0;"))

# the parameters copied into locals through arithmetic
probe("cast+p_arith", CB.replace(
    "void repro2(int nFrom, int nTo) {",
    "void repro2(int nFrom0, int nTo0) {\n"
    "    int nFrom = nFrom0 + 0;\n    int nTo = nTo0 + 0;"))

# session cast and parameters cast
probe("cast+both", CB.replace(
    "void repro2(int nFrom, int nTo) {",
    "void repro2(int nFrom0, int nTo0) {\n"
    "    int nFrom = (int)nFrom0;\n    int nTo = (int)nTo0;").replace(
    "    int nClass = classify(&nColumn, s->bMode);",
    "    int nClass = (int)classify(&nColumn, s->bMode);"))
