"""If the allocator ranks by use count and coalesces afterwards, splitting the
session's uses between two variables that coalesce for free should lower each
half's rank without changing a single instruction.
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


probe("base", BASE)

# split: a second name used inside the switch only
head, rest = BASE.split("    switch (nClass) {", 1)
body, tail = rest.rsplit("    s->bKind = (u8)nTo;", 1)
split = (head.replace("    Ctx *s = g_ctx;",
                      "    Ctx *s = g_ctx;\n    Ctx *s2;")
         + "    s2 = s;\n    switch (nClass) {"
         + body.replace("s->", "s2->").replace("lookup(s,", "lookup(s2,")
         .replace("call8(s,", "call8(s2,")
         + "    s->bKind = (u8)nTo;" + tail)
probe("split_two_names", split)

# split without the explicit copy statement, initialised at declaration
split2 = (head.replace("    Ctx *s = g_ctx;",
                       "    Ctx *s = g_ctx;\n    Ctx *s2 = g_ctx;")
          + "    switch (nClass) {"
          + body.replace("s->", "s2->").replace("lookup(s,", "lookup(s2,")
          .replace("call8(s,", "call8(s2,")
          + "    s->bKind = (u8)nTo;" + tail)
probe("split_two_globals", split2)

# three names, one per region
split3 = (head.replace("    Ctx *s = g_ctx;",
                       "    Ctx *s = g_ctx;\n    Ctx *s2 = g_ctx;\n"
                       "    Ctx *s3 = g_ctx;")
          + "    switch (nClass) {"
          + body.replace("s->", "s2->").replace("lookup(s,", "lookup(s2,")
          .replace("call8(s,", "call8(s2,")
          + "    s3->bKind = (u8)nTo;" + tail.replace("s->", "s3->"))
probe("split_three", split3)
