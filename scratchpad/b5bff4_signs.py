"""Signedness sweep. Width was swept long ago but signedness of the classifier's
return, of nClass itself and of the out-parameter never was, and a different
integer type is a real IR difference that can reach the allocator. The ROM's
dispatch uses an unsigned compare (cmp then addls), which is consistent with
either signedness, so the source is genuinely free here.
"""
import sys
import os
import json
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

PROTO = "extern int func_ov002_0205a3f0(int *pOut, int nCode);"
DECLS = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert PROTO in BASE and DECLS in BASE


def score(src):
    p = "build/try/b5bff4_sg.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:45]
    n = None
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
    return len(code), n, sr


RET = {"int": "int", "unsigned": "unsigned int"}
COL = {"int": "int", "unsigned": "unsigned int"}
CLS = {"int": "int", "unsigned": "unsigned int"}

print("%-42s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
best = (99, None)
for rname, rt in sorted(RET.items()):
    for cname, ct in sorted(COL.items()):
        for kname, kt in sorted(CLS.items()):
            proto = "extern %s func_ov002_0205a3f0(%s *pOut, int nCode);" % (rt, ct)
            decls = ("    %s nColumn;\n    int nTag;\n"
                     "    Ov002PanelSession *s = data_ov002_0207f620;\n"
                     "    %s nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n"
                     % (ct, kt))
            src = BASE.replace(PROTO, proto).replace(DECLS, decls)
            size, n, sr = score(src)
            tag = "ret=%s col=%s cls=%s" % (rname, cname, kname)
            if size is None:
                print("%-42s FAIL %s" % (tag, sr))
                continue
            print("%-42s %-6d %-6s %s%s"
                  % (tag, size, n, sr, "   MATCH" if n == 0 else ""))
            if isinstance(n, int) and n < best[0]:
                best = (n, tag)
            if n == 0:
                open("build/try/%s.c" % SYM, "w").write(src)
                print("PROMOTED " + tag)

# nTag signedness on its own
for t in ("unsigned int", "short", "unsigned short", "char", "long"):
    src = BASE.replace("    int nTag;\n", "    %s nTag;\n" % t)
    size, n, sr = score(src)
    tag = "nTag=%s" % t
    if size is None:
        print("%-42s FAIL %s" % (tag, sr))
        continue
    print("%-42s %-6d %-6s %s%s" % (tag, size, n, sr, "   MATCH" if n == 0 else ""))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
