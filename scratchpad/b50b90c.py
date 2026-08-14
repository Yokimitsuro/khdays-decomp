"""Exact size and instruction count with the subtraction guard; the ROM uses a
plain compare. A subtraction defeats mwcc's predication but spells the guard
wrong, while a plain relational gets predicated. Sweep spellings and report the
two guard instructions each produces.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_02050b90"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

OLD = """            if (nCur >= nStep) {
                nCur = *(int *)(data_ov002_0207e764 + nOffset);
                if (nStep >= nCur) {
                    nCur = nStep;
                }
            }
"""
assert OLD in BASE

BODY = """                nCur = *(int *)(data_ov002_0207e764 + nOffset);
                if (nStep >= nCur) {
                    nCur = nStep;
                }
            }
"""
GUARDS = {
    "ge": "            if (nCur >= nStep) {\n",
    "le_swapped": "            if (nStep <= nCur) {\n",
    "gt_minus1": "            if (nCur > nStep - 1) {\n",
    "lt_plus1": "            if (nStep < nCur + 1) {\n",
    "not_lt": "            if (!(nCur < nStep)) {\n",
    "ne_lt": "            if ((nCur < nStep) == 0) {\n",
    "sub_ge": "            if (nCur - nStep >= 0) {\n",
    "sub_gt": "            if (nCur - nStep > -1) {\n",
}

for tag, guard in GUARDS.items():
    s = BASE.replace(OLD, guard + BODY)
    p = "build/try/b50b90_g.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-12s FAIL" % tag)
        continue
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
    guard_txt = " ; ".join(ins[59:61]) if len(ins) > 60 else "?"
    if len(mine) != len(orig):
        print("%-12s SIZE %+d  [%s]" % (tag, len(mine) - len(orig), guard_txt))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-12s bytes=%d  [%s]%s" % (tag, n, guard_txt,
                                      "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
