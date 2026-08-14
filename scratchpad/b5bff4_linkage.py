"""Untested axis: the function's own linkage and attributes. Every caller of this
function lives inside ov002, so the original could plausibly have been static in
its translation unit, and linkage is a codegen input rather than a body rewrite.
Diagnostic only: if a form changes the allocation, work out how to express it
without breaking the delink.
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
BASE = open("build/try/%s.c" % SYM).read()
SIG = "void func_ov002_0205bff4(int nFrom, int nTo) {"
assert SIG in BASE


def report(tag, src):
    p = "build/try/b5bff4_lk.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-28s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
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
    sr = "?"
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    print("%-28s size=%-5d bytes=%-4s s=%s%s"
          % (tag, len(code), n, sr, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


report("base (extern)", BASE)
report("static", BASE.replace(SIG, "static " + SIG))
report("a forward declaration", BASE.replace(
    SIG, "void func_ov002_0205bff4(int nFrom, int nTo);\n\n" + SIG))
report("static + forward decl", BASE.replace(
    SIG, "static void func_ov002_0205bff4(int nFrom, int nTo);\n\n"
         "static " + SIG))
# a caller in the same unit, which is what a static function would really have
report("static + local caller", BASE.replace(SIG, "static " + SIG) +
       "\nvoid ov002_PanelCursorMoveThunk(int a, int b) {\n"
       "    func_ov002_0205bff4(a, b);\n}\n")
report("old-style definition", BASE.replace(
    SIG, "void func_ov002_0205bff4(nFrom, nTo)\n    int nFrom;\n    int nTo;\n{"))
