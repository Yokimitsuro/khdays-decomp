"""Six bytes left on func_ov002_02050a54: the ROM's smull takes the difference
as Rm and the scale as Rs, the candidate takes them the other way round.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_02050a54"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

OLD = """            nBase -= (int)(((long long)(nBase - data_ov002_0207e764[2]) *
                            nScale + 0x800) >> 12);
"""
assert OLD in BASE

FORMS = {
    "scale_first": "            nBase -= (int)((nScale *\n"
                   "                            (long long)(nBase -"
                   " data_ov002_0207e764[2]) + 0x800) >> 12);\n",
    "both_ll": "            nBase -= (int)(((long long)nScale *\n"
               "                            (long long)(nBase -"
               " data_ov002_0207e764[2]) + 0x800) >> 12);\n",
    "diff_ll_second": "            nBase -= (int)(((long long)nScale *\n"
                      "                            (nBase -"
                      " data_ov002_0207e764[2]) + 0x800) >> 12);\n",
    "diff_local": "            int nDiff = nBase - data_ov002_0207e764[2];\n\n"
                  "            nBase -= (int)(((long long)nDiff * nScale"
                  " + 0x800) >> 12);\n",
    "diff_local_rev": "            int nDiff = nBase - data_ov002_0207e764[2];\n"
                      "\n"
                      "            nBase -= (int)(((long long)nScale * nDiff"
                      " + 0x800) >> 12);\n",
}

best = [999, None]
for tag, form in FORMS.items():
    s = BASE.replace(OLD, form)
    p = "build/try/b50a54_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-18s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-18s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-18s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
