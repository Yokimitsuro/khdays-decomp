"""Build up from the reproduction toward the exemplar instead of tearing the
exemplar down, since reducing it degenerates the function. Add its distinctive
features one at a time and watch for the context leaving r4: a loop that writes
through the context, an array-of-struct member store whose index also comes from
the context, and a second context local in an inner block.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
BASE = open("scratchpad/repro2.c").read()


def probe(tag, src):
    p = "scratchpad/repro2_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-28s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ctx = "?"
    for t in ins[:14]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r[0-9]+\]$", t)
        if m and ctx == "?":
            ctx = m.group(1)
    flag = "   <<< MOVED" if ctx not in ("r4", "?") else ""
    print("%-28s size=%-5d ctx=%-4s%s" % (tag, len(code), ctx, flag))


probe("base", BASE)

# give the context an array of structs and write through it in a loop
STRUCT = """typedef struct {
    int x;
    int y;
} CtxPair;

"""
s = BASE.replace("typedef struct {\n    u8 bKind;",
                 STRUCT + "typedef struct {\n    u8 bKind;")
s = s.replace("    u8 pad0005[0x4a7];",
              "    u8 pad0005[0x3];\n    CtxPair aPairs[4];\n"
              "    int nPageIndex;\n    u8 pad0028[0x484];")
s = s.replace("""        case 0:
            call3(s->bIndex, s->bKind, 0);
            break;""",
              """        case 0: {
            int i;

            for (i = 0; i < 4; i++) {
                g_ctx->aPairs[i].y = 0;
            }
            break;
        }""")
probe("loop_through_global", s)

# the same loop but through the local
s2 = s.replace("                g_ctx->aPairs[i].y = 0;",
               "                s->aPairs[i].y = 0;")
probe("loop_through_local", s2)

# an array store indexed by another context field
s3 = s.replace("""            for (i = 0; i < 4; i++) {
                g_ctx->aPairs[i].y = 0;
            }""",
               """            i = 0;
            s->aPairs[s->nPageIndex].y = 0x24000;
            {
                Ctx *c2 = g_ctx;

                if (c2->bKind != 0 && c2->nPageIndex < 3) {
                    c2->aPairs[c2->nPageIndex].y += 0x8000;
                }
            }""")
probe("indexed_store_plus_c2", s3)
