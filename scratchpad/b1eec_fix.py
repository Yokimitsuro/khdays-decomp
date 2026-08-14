"""Two residues on func_ov002_02051eec:
 - the early return is 'le' in the ROM and 'lt' in the candidate;
 - the ROM stores the loaded block into the array BEFORE moving it into the
   third argument register, the candidate moves first.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_02051eec"]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/func_ov002_02051eec.c").read()

STORE = """            pState->apBlocks[i] = pData;
            func_0202a3cc(pState->pTables + nOffset, pActor + 4, pData,
                          nHeap + 7);
"""
VIA_ARRAY = """            pState->apBlocks[i] = pData;
            func_0202a3cc(pState->pTables + nOffset, pActor + 4,
                          pState->apBlocks[i], nHeap + 7);
"""


def score(tag, s):
    p = "build/try/b1eec_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-14s FAIL" % tag)
        return
    if len(mine) != len(orig):
        print("%-14s SIZE %d (%+d)" % (tag, len(mine), len(mine) - len(orig)))
        return
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-14s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/func_ov002_02051eec.c", "w").write(s)
        print("PROMOTED " + tag)


LE = BASE.replace("if (nCount < 1) {", "if (nCount <= 0) {")
score("a_le", LE)
score("b_array", BASE.replace(STORE, VIA_ARRAY))
score("c_both", LE.replace(STORE, VIA_ARRAY))
