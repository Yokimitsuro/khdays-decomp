"""Never tried: the volatile qualifier. nColumn is address-taken and the ROM
re-reads it from the stack at every use, which is exactly what volatile forces,
so marking it volatile may leave the code identical while changing the IR a lot.
Also try volatile on the classifier's out-parameter and on the global.
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
GLOB = "extern Ov002PanelSession *data_ov002_0207f620;"
PROTO = "extern int func_ov002_0205a3f0(int *pOut, int nCode);"
COL = "    int nColumn;\n"
assert GLOB in BASE and PROTO in BASE and COL in BASE


def score(src):
    p = "build/try/b5bff4_vl.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, "?", str(ex).split("\n")[0][:55]
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
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    return len(code), n, sr, None


print("ROM: s=r8   |   base: s=r4, 67 bytes")
print("%-40s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr, err = score(BASE)
print("%-40s %-6d %-6s s=%s" % ("base", size, n, sr))

VAR = {}
VAR["volatile nColumn"] = BASE.replace(COL, "    volatile int nColumn;\n")
VAR["volatile out parameter"] = BASE.replace(
    PROTO, "extern int func_ov002_0205a3f0(volatile int *pOut, int nCode);")
VAR["both volatile"] = BASE.replace(COL, "    volatile int nColumn;\n").replace(
    PROTO, "extern int func_ov002_0205a3f0(volatile int *pOut, int nCode);")
VAR["volatile global"] = BASE.replace(
    GLOB, "extern Ov002PanelSession *volatile data_ov002_0207f620;")
VAR["volatile session pointer"] = BASE.replace(
    "    Ov002PanelSession *s = data_ov002_0207f620;",
    "    Ov002PanelSession *volatile s = data_ov002_0207f620;")
VAR["volatile nTag"] = BASE.replace("    int nTag;\n", "    volatile int nTag;\n")
VAR["pointer to volatile struct"] = BASE.replace(
    GLOB, "extern volatile Ov002PanelSession *data_ov002_0207f620;")

best = (999, None)
for tag, src in sorted(VAR.items()):
    size, n, sr, err = score(src)
    if err:
        print("%-40s rejected: %s" % (tag, err))
        continue
    mark = "   MATCH" if n == 0 else ("   POINTER IN " + sr if sr not in ("r4", "?") else "")
    print("%-40s %-6d %-6s s=%s%s" % (tag, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
