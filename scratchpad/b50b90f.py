"""Last residue on func_ov002_02050b90: the ROM keeps the target in r10 and the
loop counter in r9, the candidate the other way round. Sweep where the counter
is declared.
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

DECL = """    int nProbe;
    int aAim[3];
    int aTo[3];
    int nOffset = nIndex * 0xc;
    int nCam = *(int *)(func_02023bf0() + 0x20);
    int nTarget = *(int *)(data_ov002_0207e764 + nOffset);
"""
assert DECL in BASE
LOOP_DECL = "            int i = 0;\n\n            do {\n"
assert LOOP_DECL in BASE

VARIANTS = {
    "i_top": ("    int i;\n" + DECL, "            i = 0;\n\n            do {\n"),
    "i_after_probe": ("    int nProbe;\n    int i;\n" + DECL.split("\n", 1)[1],
                      "            i = 0;\n\n            do {\n"),
    "i_before_target": (DECL.replace(
        "    int nTarget =", "    int i;\n    int nTarget ="),
        "            i = 0;\n\n            do {\n"),
    "i_after_target": (DECL + "    int i;\n",
                       "            i = 0;\n\n            do {\n"),
    "i_outer_block": (DECL, "            int i;\n\n            i = 0;\n"
                            "            do {\n"),
}

for tag, (decl, loop) in VARIANTS.items():
    s = BASE.replace(DECL, decl).replace(LOOP_DECL, loop)
    p = "build/try/b50b90_%s.c" % tag
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
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
