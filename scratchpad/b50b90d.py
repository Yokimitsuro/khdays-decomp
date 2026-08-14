"""One branch condition apart. 'nStep <= nCur' branches but compares the
operands the other way round; 'nCur >= nStep' compares the ROM's way but gets
predicated. Look for a spelling that does both.
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

BODY_IN = """                nCur = *(int *)(data_ov002_0207e764 + nOffset);
                if (nStep >= nCur) {
                    nCur = nStep;
                }
"""

FORMS = {
    "empty_then": "            if (nCur < nStep) {\n"
                  "            } else {\n" + BODY_IN + "            }\n",
    "le_inner_le": "            if (nStep <= nCur) {\n"
                   "                nCur = *(int *)(data_ov002_0207e764"
                   " + nOffset);\n"
                   "                if (nCur <= nStep) {\n"
                   "                    nCur = nStep;\n"
                   "                }\n            }\n",
    "ge_inner_le": "            if (nCur >= nStep) {\n"
                   "                nCur = *(int *)(data_ov002_0207e764"
                   " + nOffset);\n"
                   "                if (nCur <= nStep) {\n"
                   "                    nCur = nStep;\n"
                   "                }\n            }\n",
    "lt_continue": "            if (nCur < nStep) {\n"
                   "                nCur = nCur;\n"
                   "            } else {\n" + BODY_IN + "            }\n",
    "while_break": "            while (nCur >= nStep) {\n" + BODY_IN
                   + "                break;\n            }\n",
    "do_break": "            do {\n"
                "                if (nCur < nStep) {\n"
                "                    break;\n"
                "                }\n" + BODY_IN + "            } while (0);\n",
}

for tag, form in FORMS.items():
    s = BASE.replace(OLD, form)
    p = "build/try/b50b90_h.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-14s FAIL" % tag)
        continue
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
    g = " ; ".join(ins[59:61]) if len(ins) > 60 else "?"
    if len(mine) != len(orig):
        print("%-14s SIZE %+d  [%s]" % (tag, len(mine) - len(orig), g))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-14s bytes=%d  [%s]%s" % (tag, n, g, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
