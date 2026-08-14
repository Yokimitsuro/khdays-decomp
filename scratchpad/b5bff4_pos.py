"""Under the const global the session moved to r7. Earlier declaration means a
higher register, so sweep where the session sits in the declaration list, and
how many scalars precede it, looking for r8.
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


def sess(code):
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            return m.group(1)
    return "?"


def report(tag, src):
    p = "build/try/b5bff4_pos.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:55]))
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
    print("%-26s size=%-5d bytes=%-4s s=%s%s"
          % (tag, len(code), n, sess(code), "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/b5bff4_best.c").read()
GLOB = "extern Ov002PanelSession *data_ov002_0207f620;"
CGLOB = "extern Ov002PanelSession *const data_ov002_0207f620;"
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert GLOB in BASE and DECL in BASE
CB = BASE.replace(GLOB, CGLOB)

POS = {
    "s_first": """    Ov002PanelSession *s = data_ov002_0207f620;
    int nColumn;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "s_second": """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "s_third": DECL,
    "s_first_split": """    Ov002PanelSession *s;
    int nColumn;
    int nTag;
    int nClass;

    s = data_ov002_0207f620;
    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
}
for tag, d in sorted(POS.items()):
    report("const " + tag, CB.replace(DECL, d))
    report("plain " + tag, BASE.replace(DECL, d))

# extra scalars ahead of the session, to push it further up the range
for k in (1, 2, 3):
    pad = "".join("    int nPad%d;\n" % i for i in range(k))
    d = pad + """    Ov002PanelSession *s = data_ov002_0207f620;
    int nColumn;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
    report("const pad%d_then_s" % k, CB.replace(DECL, d))
