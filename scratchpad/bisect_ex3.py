"""Split the exemplar into declarations and body and test each side, to find
whether its high context comes from what it declares or from what it does.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SRC = open("src/overlays/ov000/calls/func_ov000_02050ec4.c").read()
HEAD, BODY = SRC.split("void func_ov000_02050ec4(void)\n{\n", 1)
BODY = BODY.rstrip()
assert BODY.endswith("}")
INNER = BODY[:-1]

DECLS = """    Ov000LoadPageContext *ctx = data_ov000_0205ac24;
    int i;
    u32 j;
    int cur[2];
    Ov000ScrollWork w;
    int move;
    int entry;
"""
assert DECLS in INNER
REST = INNER.split(DECLS, 1)[1]


def probe(tag, inner):
    src = HEAD + "void func_ov000_02050ec4(void)\n{\n" + inner + "\n}\n"
    p = "scratchpad/bisect_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-28s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ctx = "?"
    for t in ins[:12]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r[0-9]+\]$", t)
        if m and ctx == "?":
            ctx = m.group(1)
    saved = sorted(set(re.findall(r"\b(r[4-9]|r1[01]|sb|sl|fp)\b",
                                  ins[0] if ins else "")))
    print("%-28s size=%-5d ctx=%-4s saved=%d" % (tag, len(code), ctx,
                                                 len(saved)))


probe("full exemplar", DECLS + REST)

# drop the aggregate locals, keeping the rest of the body only if it compiles
for drop in ("int cur[2];", "Ov000ScrollWork w;", "u32 j;", "int move;",
             "int entry;"):
    d = DECLS.replace("    %s\n" % drop, "")
    probe("without %s" % drop, d + REST)

# only the declarations plus a single context store
probe("decls + one store",
      DECLS + "\n    ctx->nActiveState = 1;\n")
