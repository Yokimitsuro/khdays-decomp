import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_020698f8"]
orig = bytearray.fromhex(e["hex"])
orel = {o: sy for o, sy in e["relocs"]}

BASE = open("build/try/b8f8_i6_ptrplusoff_as_is.c").read()


def score(tag, s):
    p = "build/try/b8f8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, True)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return 99
    if len(mine) != len(orig):
        print("%-26s SIZE %d" % (tag, len(mine)))
        return 99
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-26s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    if nd == 0:
        open("build/try/func_ov002_020698f8.c", "w").write(s)
        print("PROMOTED")
    return nd


print("baseline")
score("i7_base", BASE)

RET = [("void *", "void *"), ("char *", "char *"), ("int *", "int *"),
       ("unsigned int", "unsigned int"), ("short", "short")]

for rt, nodet in RET:
    s = BASE.replace("extern int func_ov002_02073880(int seat);",
                     "extern %sfunc_ov002_02073880(int seat);" % rt)
    s = s.replace("    int node;\n", "    %snode;\n" % nodet)
    # the second call site also passes the session field
    score("i7_ret_" + rt.replace(" ", "").replace("*", "p"), s)
