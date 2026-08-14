"""DIAGNOSTIC ONLY, never for integration: the contract bars asm in integrated C.
With -gccext,on mwcc may accept GCC explicit register variables. Pinning the
session to r8 answers a question no amount of source rewriting has: is that ONE
decision responsible for all 67 bytes, or is my model of the residue wrong?
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
OLD = "    Ov002PanelSession *s = data_ov002_0207f620;"
assert OLD in BASE


def score(src):
    p = "build/try/b5bff4_pin.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:70]
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


FORMS = [
    ('gcc asm r8',
     '    register Ov002PanelSession *s __asm("r8") = data_ov002_0207f620;'),
    ('gcc asm bare',
     '    register Ov002PanelSession *s asm("r8") = data_ov002_0207f620;'),
    ('mwcc register r8',
     '    register Ov002PanelSession *s : "r8" = data_ov002_0207f620;'),
    ('declspec',
     '    __declspec(register r8) Ov002PanelSession *s = data_ov002_0207f620;'),
]

print("%-24s %-6s %-6s %s" % ("form", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-24s %-6d %-6s s=%s" % ("base", size, n, sr))
for tag, decl in FORMS:
    size, n, sr = score(BASE.replace(OLD, decl))
    if size is None:
        print("%-24s rejected: %s" % (tag, sr))
        continue
    mark = "   ALL 67 BYTES EXPLAINED" if n == 0 else ""
    print("%-24s %-6d %-6s s=%s%s" % (tag, size, n, sr, mark))
