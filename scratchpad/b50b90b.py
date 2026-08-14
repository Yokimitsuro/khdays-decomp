"""Second round on the first clamp of func_ov002_02050b90. The second clamp has
an identical three-instruction body and mwcc branches over it; the first it
predicates. Try shapes that change what the guard is computed from.
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

OLD = """            int nCur = *(int *)(nCam + 0x98);
            int nStep = nCur - 0x80;

            if (nCur >= nStep) {
                nCur = *(int *)(data_ov002_0207e764 + nOffset);
                if (nStep >= nCur) {
                    nCur = nStep;
                }
            }
            *(int *)(nCam + 0x98) = nCur;
"""
assert OLD in BASE

HEAD = "            int nCur = *(int *)(nCam + 0x98);\n" \
       "            int nStep = nCur - 0x80;\n\n"
TAIL = "            *(int *)(nCam + 0x98) = nCur;\n"

FORMS = {
    "diffguard": HEAD + "            if (nCur - nStep >= 0) {\n"
                        "                nCur = *(int *)(data_ov002_0207e764"
                        " + nOffset);\n"
                        "                if (nStep >= nCur) {\n"
                        "                    nCur = nStep;\n"
                        "                }\n            }\n" + TAIL,
    "gt_zero": HEAD + "            if (nCur - nStep > 0) {\n"
                      "                nCur = *(int *)(data_ov002_0207e764"
                      " + nOffset);\n"
                      "                if (nStep >= nCur) {\n"
                      "                    nCur = nStep;\n"
                      "                }\n            }\n" + TAIL,
    "not_less": HEAD + "            if (!(nCur < nStep)) {\n"
                       "                nCur = *(int *)(data_ov002_0207e764"
                       " + nOffset);\n"
                       "                if (nStep >= nCur) {\n"
                       "                    nCur = nStep;\n"
                       "                }\n            }\n" + TAIL,
    "ternary_outer": HEAD + "            nCur = (nCur < nStep)\n"
                            "                       ? nCur\n"
                            "                       : ((nStep >="
                            " *(int *)(data_ov002_0207e764 + nOffset))\n"
                            "                              ? nStep\n"
                            "                              : *(int *)"
                            "(data_ov002_0207e764 + nOffset));\n" + TAIL,
    "floorlocal": HEAD + "            if (nCur >= nStep) {\n"
                         "                int nFloor ="
                         " *(int *)(data_ov002_0207e764 + nOffset);\n\n"
                         "                nCur = nFloor;\n"
                         "                if (nStep >= nFloor) {\n"
                         "                    nCur = nStep;\n"
                         "                }\n            }\n" + TAIL,
    "step_first": "            int nStep;\n"
                  "            int nCur = *(int *)(nCam + 0x98);\n\n"
                  "            nStep = nCur - 0x80;\n"
                  "            if (nCur >= nStep) {\n"
                  "                nCur = *(int *)(data_ov002_0207e764"
                  " + nOffset);\n"
                  "                if (nStep >= nCur) {\n"
                  "                    nCur = nStep;\n"
                  "                }\n            }\n" + TAIL,
}

best = [999, None]
for tag, form in FORMS.items():
    s = BASE.replace(OLD, form)
    p = "build/try/b50b90_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-16s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-16s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-16s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
