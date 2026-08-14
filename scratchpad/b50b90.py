"""One instruction left on func_ov002_02050b90: mwcc predicates the first clamp
where the ROM branches over it. The second clamp, same shape, already branches.
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

FORMS = {
    "goto": """            int nCur = *(int *)(nCam + 0x98);
            int nStep = nCur - 0x80;

            if (nCur < nStep) {
                goto storeDown;
            }
            nCur = *(int *)(data_ov002_0207e764 + nOffset);
            if (nStep >= nCur) {
                nCur = nStep;
            }
        storeDown:
            *(int *)(nCam + 0x98) = nCur;
""",
    "switch": """            int nCur = *(int *)(nCam + 0x98);
            int nStep = nCur - 0x80;

            switch (nCur >= nStep) {
            case 1:
                nCur = *(int *)(data_ov002_0207e764 + nOffset);
                if (nStep >= nCur) {
                    nCur = nStep;
                }
                break;
            default:
                break;
            }
            *(int *)(nCam + 0x98) = nCur;
""",
    "nested_store": """            int nCur = *(int *)(nCam + 0x98);
            int nStep = nCur - 0x80;

            if (nCur >= nStep) {
                nCur = *(int *)(data_ov002_0207e764 + nOffset);
                if (nStep >= nCur) {
                    nCur = nStep;
                }
                *(int *)(nCam + 0x98) = nCur;
            } else {
                *(int *)(nCam + 0x98) = nCur;
            }
""",
    "inverted": """            int nCur = *(int *)(nCam + 0x98);
            int nStep = nCur - 0x80;

            if (nStep <= nCur) {
                nCur = *(int *)(data_ov002_0207e764 + nOffset);
                if (nCur <= nStep) {
                    nCur = nStep;
                }
            }
            *(int *)(nCam + 0x98) = nCur;
""",
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
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
