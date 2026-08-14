import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

NAME = "func_ov002_02069a7c"
idx = json.load(open("build/func_index.json"))
e = idx[NAME]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
md = Cs(CS_ARCH_ARM, CS_MODE_ARM)

HEAD = """typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern int func_01fffde0(int index);
extern Vec3 *func_ov022_020881f8(int index);
extern int func_0202c268(unsigned short id, Vec3 *from, Vec3 *dir, int mask);

"""

MAIN = """        Vec3 *v = func_ov022_020881f8(index);
        int e = func_01fffde0(index);

        from.x = v->x;
        from.y = v->y + 0x1000;
        from.z = v->z;
        dir.x = 0;
        dir.y = -0x32000;
        dir.z = 0;
        if (func_0202c268((unsigned short)h, &from, &dir,
                          *(int *)(e + 0x20)) == 0) {
            ok = 0;
        }
"""


def run(tag, decls, body):
    src = (HEAD + "int func_ov002_02069a7c(int index) {\n" + decls
           + "    int ok = 1;\n"
             "    short h = *(short *)(func_01fffde0(index) + 0x66);\n\n"
           + body + "    return ok;\n}\n")
    p = "build/try/ba7c_%s.c" % tag
    with open(p, "w") as f:
        f.write(src)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return
    if len(mine) != len(orig):
        print("%-24s SIZE %d" % (tag, len(mine)))
        return
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-24s bytes=%-3d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))


D1 = "    Vec3 dir;\n    Vec3 from;\n"
D2 = "    Vec3 from;\n    Vec3 dir;\n"
NEG = "    if (h < 0) {\n        ok = 0;\n    } else {\n" + MAIN + "    }\n"
POS = "    if (h >= 0) {\n" + MAIN + "    } else {\n        ok = 0;\n    }\n"

for dn, d in (("dirfirst", D1), ("fromfirst", D2)):
    for bn, bd in (("neg", NEG), ("pos", POS)):
        run("%s_%s" % (dn, bn), d, bd)
