import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_020698f8"]
orig = bytearray.fromhex(e["hex"])
orel = {o: sy for o, sy in e["relocs"]}
BASE = open("build/try/func_ov002_020698f8.c").read()

OLD = ("    slot = (char *)(index * 0x44);\n"
       "    slot = *(char **)(session + 4) + (int)slot;\n")


def score(tag, s):
    p = "build/try/b8f8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, True)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return 99
    if len(mine) != len(orig):
        print("%-22s SIZE %d" % (tag, len(mine)))
        return 99
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-22s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    return nd


print("current (two-step)")
score("clean_base", BASE)

CANDS = {
    "off_local": ("    int off = index * 0x44;\n\n"
                  "    slot = *(char **)(session + 4) + off;\n"),
    "off_decl_top": ("    slot = *(char **)(session + 4) + off;\n"),
    "cast_int": ("    slot = *(char **)(session + 4) + (int)(index * 0x44);\n"),
    "mul_first": ("    slot = index * 0x44 + *(char **)(session + 4);\n"),
}

for tag, txt in CANDS.items():
    s = BASE.replace(OLD, txt)
    if tag == "off_decl_top":
        s = s.replace("    int seat;\n", "    int seat;\n    int off = index * 0x44;\n")
        # the declaration must come after index is resolved, so this one is a
        # deliberate probe rather than a real candidate
    score("clean_" + tag, s)
