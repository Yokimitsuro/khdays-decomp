import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_02052024"]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/func_ov002_02052024.c").read()


def score(tag, s):
    p = "build/try/b2024_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:40]))
        return 99
    if len(mine) != len(orig):
        print("%-24s SIZE %d (%+d)" % (tag, len(mine), len(mine) - len(orig)))
        return 99
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-24s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    if nd == 0:
        open("build/try/func_ov002_02052024.c", "w").write(s)
        print("PROMOTED")
    return nd


print("baseline")
score("a_base", BASE)

# bind the animation object once
s = BASE.replace("    int code;\n    int i;\n",
                 "    char *anim = self + 4;\n    int code;\n    int i;\n")
s = s.replace("self + 4,", "anim,").replace("self + 4)", "anim)")
score("b_anim", s)

# bind the current mode byte once
s2 = BASE.replace("    int code;\n    int i;\n",
                  "    int code;\n    int cur;\n    int i;\n")
s2 = s2.replace("*state == mode", "*state == mode")
s2 = s2.replace("            if (*state == 0xe || *state == 0x13 || *state == 0x14) {",
                "            cur = *state;\n"
                "            if (cur == 0xe || cur == 0x13 || cur == 0x14) {")
score("c_cur", s2)

# bind the fifth argument once
s3 = BASE.replace("    int code;\n    int i;\n",
                  "    int code;\n    int i;\n    int fifth = arg5;\n")
s3 = s3.replace(", arg5);", ", fifth);")
score("d_fifth", s3)

# the state pointer typed as the table set throughout
s4 = BASE.replace("void func_ov002_02052024(char *self, char *state, int mode, int kind, int arg5) {",
                  "void func_ov002_02052024(char *self, Ov002TableSet *state, int mode,\n"
                  "                         int kind, int arg5) {")
s4 = s4.replace("*state == mode", "*(char *)state == mode")
s4 = s4.replace("((Ov002TableSet *)state)->pTables", "state->pTables")
s4 = s4.replace("if (*state == 0xe || *state == 0x13 || *state == 0x14)",
                "if (*(char *)state == 0xe || *(char *)state == 0x13 || *(char *)state == 0x14)")
s4 = s4.replace("    *state = (char)mode;\n", "    *(char *)state = (char)mode;\n")
s4 = s4.replace("*(int *)(state + 4) = 1;", "*(int *)((char *)state + 4) = 1;")
score("e_typedstate", s4)
