"""The guard is not an if at all: the ROM's shape is a nested clamp whose first
test is 'step above the current value', answering with the current value, and
whose second test loads the floor lazily. Try that spelling.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

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
D = "*(int *)(data_ov002_0207e764 + nOffset)"

FORMS = {
    "clamp": "            nCur = (nStep > nCur)\n"
             "                       ? nCur\n"
             "                       : ((nStep < " + D + ")\n"
             "                              ? " + D + "\n"
             "                              : nStep);\n",
    "clamp_ge": "            nCur = (nStep > nCur)\n"
                "                       ? nCur\n"
                "                       : ((nStep >= " + D + ")\n"
                "                              ? nStep\n"
                "                              : " + D + ");\n",
    "clamp_if": "            if (nStep > nCur) {\n"
                "                nCur = nCur;\n"
                "            } else if (nStep < " + D + ") {\n"
                "                nCur = " + D + ";\n"
                "            } else {\n"
                "                nCur = nStep;\n"
                "            }\n",
    "clamp_mixed": "            if (nStep <= nCur) {\n"
                   "                nCur = " + D + ";\n"
                   "                if (nStep >= nCur) {\n"
                   "                    nCur = nStep;\n"
                   "                }\n            }\n",
}

for tag, form in FORMS.items():
    s = BASE.replace(OLD, form)
    p = "build/try/b50b90_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-14s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-14s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
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
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
