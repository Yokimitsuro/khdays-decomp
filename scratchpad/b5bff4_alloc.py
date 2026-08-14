"""Diagnostic sweep, not a match attempt.

The residue is now exactly two assignments: the ROM gives the session pointer r8
and the classifier result r4; mwcc gives them r4 and r7. Instructions 3, 4, 5 and
9 define nFrom, s, nTo and nClass, so read the four destination registers out of
each build and report the tuple. Size may change freely; the question is only
which perturbation moves s off r4.
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
TARGET = "nFrom=r6 s=r8 nTo=r5 nClass=r4"


def probe(code):
    """Find the four defining instructions by shape, not by index."""
    out = {}
    for i in md.disasm(bytes(code), 0):
        t = i.mnemonic + " " + i.op_str
        if "nFrom" not in out:
            m = re.match(r"^mov (r\w+), r0$", t)
            if m:
                out["nFrom"] = m.group(1)
                continue
        if "s" not in out:
            m = re.match(r"^ldr (r\w+), \[r2\]$", t)
            if m:
                out["s"] = m.group(1)
                continue
        if "nTo" not in out:
            m = re.match(r"^mov (r\w+), r1$", t)
            if m:
                out["nTo"] = m.group(1)
                continue
        if "nClass" not in out and "nTo" in out:
            m = re.match(r"^mov (r\w+), r0$", t)
            if m:
                out["nClass"] = m.group(1)
                break
    return "nFrom=%s s=%s nTo=%s nClass=%s" % (
        out.get("nFrom", "?"), out.get("s", "?"),
        out.get("nTo", "?"), out.get("nClass", "?"))


def report(tag, src):
    p = "build/try/b5bff4_al.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
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
    pr = probe(code)
    print("%-26s size=%-5d bytes=%-4s %s%s"
          % (tag, len(code), n, pr, "   <== ROM" if pr == TARGET else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
SIG = "void func_ov002_0205bff4(int nFrom, int nTo) {"
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert SIG in BASE and DECL in BASE
print("%-26s %19s %s" % ("ROM target", "", TARGET))
report("base", BASE)

# 1. the function returns a value instead of void
report("ret_int", BASE.replace(SIG, "int func_ov002_0205bff4(int nFrom, int nTo) {"))

# 2. an extra unused local, declared first and declared last
report("dummy_first", BASE.replace(DECL, "    int nSpare;\n" + DECL))
report("dummy_last", BASE.replace(DECL, DECL + "    int nSpare;\n"))

# 3. the session read straight from the global in the classifier call, so the
#    cached pointer becomes a compiler temporary created after nClass
D3 = """    int nColumn;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, data_ov002_0207f620->bMode);
    Ov002PanelSession *s = data_ov002_0207f620;
"""
report("s_after_nClass", BASE.replace(DECL, D3))

# 4. no local at all: every access goes through the global
NOLOCAL = BASE.replace(DECL, """    int nColumn;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, data_ov002_0207f620->bMode);
""")
NOLOCAL = re.sub(r"\bs->", "data_ov002_0207f620->", NOLOCAL)
NOLOCAL = NOLOCAL.replace("(u8 *)data_ov002_0207f620->pCachedEntry",
                          "(u8 *)data_ov002_0207f620->pCachedEntry")
report("no_local", NOLOCAL)

# 5. a third parameter, so the parameter registers shift
report("three_params",
       BASE.replace(SIG, "void func_ov002_0205bff4(int nFrom, int nTo, int nSpare) {"))

# 6. parameters swapped in the signature
S6 = BASE.replace(SIG, "void func_ov002_0205bff4(int nTo, int nFrom) {")
report("params_swapped", S6)

# 7. nClass declared before the session
D7 = """    int nColumn;
    int nTag;
    int nClass;
    Ov002PanelSession *s = data_ov002_0207f620;

    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
report("nClass_decl_first", BASE.replace(DECL, D7))

# 8. the session pointer taken again after the classifier call
D8 = """    int nColumn;
    int nTag;
    Ov002PanelSession *s;
    int nClass = func_ov002_0205a3f0(&nColumn, data_ov002_0207f620->bMode);

    s = data_ov002_0207f620;
"""
report("s_reload_after", BASE.replace(DECL, D8))

# 9. session held as a plain char pointer, so its type is not a struct pointer
report("s_void_ptr", BASE.replace(
    "Ov002PanelSession *s = data_ov002_0207f620;",
    "Ov002PanelSession *const s = data_ov002_0207f620;"))
