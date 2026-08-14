"""The pre-switch block has never been varied. Its two nested calls can carry
named temporaries, the test can be spelled several ways, and the branch can be
inverted. All emit the same instructions but create different objects early in
the function, which is where web numbering starts.
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
PRE = """    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
"""
assert PRE in BASE
DECL = """    int nColumn;
    int nTag;
"""


def score(src):
    p = "build/try/b5bff4_pb.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:50]
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


VAR = {}
VAR["named outer temp"] = (DECL + "    int nEntry;\n", """    nEntry = func_ov002_020536bc(0xe);
    if (func_ov002_0205374c(nEntry) == 0) {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
""")
VAR["named inner temp"] = (DECL + "    int nAlt;\n", """    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {
        nAlt = func_ov002_02053558(0x79);
        func_ov002_020535f0(nAlt);
    }
""")
VAR["both named"] = (DECL + "    int nEntry;\n    int nAlt;\n", """    nEntry = func_ov002_020536bc(0xe);
    if (func_ov002_0205374c(nEntry) == 0) {
        nAlt = func_ov002_02053558(0x79);
        func_ov002_020535f0(nAlt);
    }
""")
VAR["negation form"] = (DECL, """    if (!func_ov002_0205374c(func_ov002_020536bc(0xe))) {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
""")
VAR["inverted branch"] = (DECL, """    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) != 0) {
    } else {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
""")
VAR["temp declared in block"] = (DECL, """    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {
        int nAlt = func_ov002_02053558(0x79);

        func_ov002_020535f0(nAlt);
    }
""")

print("%-30s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-30s %-6d %-6s s=%s" % ("base", size, n, sr))
best = (99, None)
for tag, (decl, pre) in sorted(VAR.items()):
    src = BASE.replace(DECL, decl).replace(PRE, pre)
    size, n, sr = score(src)
    if size is None:
        print("%-30s FAIL %s" % (tag, sr))
        continue
    mark = "   MATCH" if n == 0 else ("   POINTER IN " + sr if sr not in ("r4", "?") else "")
    print("%-30s %-6d %-6s s=%s%s" % (tag, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
