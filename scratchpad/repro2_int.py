"""Neither creation order, use count nor group size moves the session, so what
pins it to r4 may be that it is the only pointer-typed value of the three. Type
it as an integer and reach the fields through casts.
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

# the session held as an integer, fields reached through casts
FIELDS = {
    "s->bKind": "*(u8 *)(s + 0)",
    "s->bMode": "*(u8 *)(s + 1)",
    "s->bIndex": "*(u8 *)(s + 2)",
    "s->bListIndex": "*(u8 *)(s + 3)",
    "s->bKey": "*(u8 *)(s + 4)",
}
s = BASE.replace("    Ctx *s = g_ctx;", "    int s = (int)g_ctx;")
for a, b in sorted(FIELDS.items(), key=lambda kv: -len(kv[0])):
    s = s.replace(a, b)
s = s.replace("lookup(s,", "lookup((void *)s,").replace(
    "call8(s,", "call8((void *)s,")
probe("session_as_int", s)

# a second long lived pointer, to see whether the first gives up r4
s2 = BASE.replace("    Ctx *s = g_ctx;",
                  "    Ctx *s = g_ctx;\n    u16 *pHot = (u16 *)g_ctx;")
s2 = s2.replace("    call3(s->bMode, nTo, 0);",
                "    call3(s->bMode, nTo, *pHot);", 1)
s2 = s2.replace("    s->bKind = (u8)nTo;\n    call3(s->bMode, nTo, 0);",
                "    s->bKind = (u8)nTo;\n    call3(s->bMode, nTo, *pHot);")
probe("second_pointer", s2)
