"""The one matched exemplar with a high context pointer, func_ov000_02050ec4,
differs from this function in three ways: no parameters, a switch on a memory
read instead of a call result, and array and struct locals. Isolate which of
those puts the context high.
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
    order = []
    for t in ins:
        if t.startswith(("push", "pop", "stmdb", "ldmia")):
            continue
        for m in RE.finditer(t):
            r = ALIAS.get(m.group(1), m.group(1))
            if r not in FIXED and r not in order:
                order.append(r)
    print("%-26s size=%-5d ctx=%-4s map=%s" % (tag, len(code), ctx,
                                               " ".join(order)))


probe("base", BASE)

# switch on a memory read instead of the call result
s = BASE.replace("    int nClass = classify(&nColumn, s->bMode);",
                 "    int nClass;\n\n    classify(&nColumn, s->bMode);")
s = s.replace("    switch (nClass) {", "    switch (s->bKind) {")
probe("switch_on_memory", s)

# no parameters, values read from the context instead
s2 = BASE.replace("void repro2(int nFrom, int nTo) {",
                  "void repro2(void) {\n"
                  "    int nFrom = g_ctx->bIndex;\n"
                  "    int nTo = g_ctx->bKey;")
probe("no_params", s2)

# an array local and a struct local, address taken
s3 = BASE.replace("    int nColumn;",
                  "    int nColumn;\n    int aScratch[2];\n"
                  "    struct { int a; int b; int c; } work;")
s3 = s3.replace("    call3(s->bMode, nTo, 0);",
                "    aScratch[0] = 0;\n    work.a = 0;\n"
                "    classify(aScratch, work.a);\n"
                "    call3(s->bMode, nTo, 0);", 1)
probe("array_locals", s3)
