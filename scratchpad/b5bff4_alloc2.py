"""Sweep 2: perturb only how the session pointer is produced and held, and print
the opening instructions literally so the assignment is read rather than guessed.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}
ROMHEAD = "push|sub|ldr r2|mov r6, r0|ldr r8, [r2]|mov r5, r1|ldrb r1, [r8, #1]"


def head(code):
    out = []
    for n, i in enumerate(md.disasm(bytes(code), 0)):
        if n > 9:
            break
        t = i.mnemonic + " " + i.op_str
        if n in (0, 1):
            t = i.mnemonic
        if n == 2:
            t = "ldr r2"
        out.append(t)
    return "|".join(out)


def report(tag, src):
    p = "build/try/b5bff4_a2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    n = "-"
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    h = head(code)
    print("%-24s %-5d b=%-4s %s%s" % (tag, len(code), n, h,
                                      "   <== ROM" if h == ROMHEAD else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert DECL in BASE
print("%-24s %-5s %-6s %s" % ("ROM target", "1416", "b=0", ROMHEAD))
report("base", BASE)

VARIANTS = {
    # the session taken through an intermediate pointer
    "via_temp": """    int nColumn;
    int nTag;
    Ov002PanelSession *p = data_ov002_0207f620;
    Ov002PanelSession *s = p;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    # the mode read into its own local before the call
    "mode_local": """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nMode = s->bMode;
    int nClass = func_ov002_0205a3f0(&nColumn, nMode);
""",
    # the classifier called first, the session bound afterwards from a copy the
    # compiler already had to make for the bMode read
    "class_first": """    int nColumn;
    int nTag;
    Ov002PanelSession *s;
    int nClass;

    s = data_ov002_0207f620;
    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    # session declared last among the locals
    "s_decl_last": """    int nColumn;
    int nTag;
    int nClass;
    Ov002PanelSession *s = data_ov002_0207f620;

    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    # nColumn and nTag declared after the session
    "scalars_after": """    Ov002PanelSession *s = data_ov002_0207f620;
    int nColumn;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    # the session is the very first declaration
    "s_only_first": """    Ov002PanelSession *s = data_ov002_0207f620;
    int nColumn;
    int nTag;
    int nClass;

    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
}
for tag, d in sorted(VARIANTS.items()):
    report(tag, BASE.replace(DECL, d))

# the classifier result held in a variable that is plainly dead after dispatch
report("class_copy", BASE.replace(DECL, DECL + "    nClass = nClass;\n"))

# an extra pointer local aliasing the session, used for the wide offsets only
WIDE = BASE.replace(DECL, DECL.replace(
    "    int nClass =",
    "    u8 *pBase = (u8 *)data_ov002_0207f620;\n    int nClass ="))
report("wide_alias", WIDE)
