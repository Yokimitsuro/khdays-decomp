"""Never varied: the short-circuit chains. This function has four of them (case 0's
object test, case 2's two flag tests, case 5's three-term test). A chain of && and
the equivalent nested ifs emit the same branches but are different shapes in the
IR, which is where the residue lives.
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


def score(src):
    p = "build/try/b5bff4_ac.c"
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


# case 2's flag test, twice
C2_AND = """        bFlag = 0;
        if (func_ov002_0205a714(0, *pEntry) != 0 &&
            func_ov002_0205a730(0, *pEntry) != 0) {
            bFlag = 1;
        }
"""
C2_NEST = """        bFlag = 0;
        if (func_ov002_0205a714(0, *pEntry) != 0) {
            if (func_ov002_0205a730(0, *pEntry) != 0) {
                bFlag = 1;
            }
        }
"""
# case 0's object test
C0_AND = """            if (pObject != 0 && func_ov002_0205a7b8() != 0) {
                nValue = 1;
            } else {
                nValue = 0;
            }
"""
C0_NEST = """            nValue = 0;
            if (pObject != 0) {
                if (func_ov002_0205a7b8() != 0) {
                    nValue = 1;
                }
            }
"""
# case 5's three-term test
C5_AND = """        if (*(int *)((u8 *)s->pCachedEntry + 4) != 0 &&
            func_ov002_0205a714(0, nKey) != 0 &&
            func_ov002_0205a730(0, nKey) != 0) {
            bFlag = 1;
        }
"""
C5_NEST = """        if (*(int *)((u8 *)s->pCachedEntry + 4) != 0) {
            if (func_ov002_0205a714(0, nKey) != 0) {
                if (func_ov002_0205a730(0, nKey) != 0) {
                    bFlag = 1;
                }
            }
        }
"""
present = [C2_AND in BASE, C0_AND in BASE, C5_AND in BASE]
print("anchors found:", present)

print("%-30s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-30s %-6d %-6s s=%s" % ("base", size, n, sr))
best = (99, None)
for c2, c0, c5 in itertools.product((0, 1), repeat=3):
    if not (c2 or c0 or c5):
        continue
    src = BASE
    if c2:
        src = src.replace(C2_AND, C2_NEST)
    if c0:
        src = src.replace(C0_AND, C0_NEST)
    if c5:
        src = src.replace(C5_AND, C5_NEST)
    size, n, sr = score(src)
    tag = "c2=%d c0=%d c5=%d" % (c2, c0, c5)
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
