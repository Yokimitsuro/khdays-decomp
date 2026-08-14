"""The measured rule is that webs take callee-saved registers in declaration
order, descending r6, r5, r4 and then upward. The ROM orders nClass before the
session, which my source cannot do because nClass's initialiser reads s->bMode.
A const-qualified global lets mwcc keep the pointer across the call without a
reload, which is the only way to declare the session after nClass for free.
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
    p = "build/try/b5bff4_cg.c"
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
DECL = """    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
AFTER = """    int nClass = func_ov002_0205a3f0(&nColumn, data_ov002_0207f620->bMode);
    Ov002PanelSession *s = data_ov002_0207f620;
"""
assert GLOB in BASE and DECL in BASE
report("best (nNew first)", BASE)
report("const_global", BASE.replace(GLOB, CGLOB))
report("s_after_nClass", BASE.replace(DECL, AFTER))
report("const + s_after", BASE.replace(GLOB, CGLOB).replace(DECL, AFTER))

# same, but the session is a const pointer as well
AFTERC = """    int nClass = func_ov002_0205a3f0(&nColumn, data_ov002_0207f620->bMode);
    Ov002PanelSession *const s = data_ov002_0207f620;
"""
report("const + s_after_const", BASE.replace(GLOB, CGLOB).replace(DECL, AFTERC))

# the whole struct behind a const pointer to non-const data, declared after
NOLOCAL = BASE.replace(GLOB, CGLOB).replace(DECL, AFTER)
NOLOCAL = NOLOCAL.replace("    Ov002PanelSession *s = data_ov002_0207f620;\n", "")
NOLOCAL = re.sub(r"\bs->", "data_ov002_0207f620->", NOLOCAL)
NOLOCAL = NOLOCAL.replace("(u8 *)data_ov002_0207f620->pCachedEntry",
                          "(u8 *)data_ov002_0207f620->pCachedEntry")
report("const_global_no_local", NOLOCAL)
