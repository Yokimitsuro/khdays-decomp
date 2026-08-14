import sys
import os
import json
import itertools

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

BASE = """        Vec3 *v = func_ov022_020881f8(index);
        int e = func_01fffde0(index);

%s        if (func_0202c268((unsigned short)h, &from, &dir,
                          *(int *)(e + 0x20)) == 0) {
            ok = 0;
        }
"""

A = {
    "X": "        from.x = v->x;\n",
    "Y": "        from.y = v->y + 0x1000;\n",
    "Z": "        from.z = v->z;\n",
    "x": "        dir.x = 0;\n",
    "y": "        dir.y = -0x32000;\n",
    "z": "        dir.z = 0;\n",
}


def run(tag, src):
    p = "build/try/ba7c_%s.c" % tag
    with open(p, "w") as f:
        f.write(src)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        return None
    if len(mine) != len(orig):
        return None
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    return sum(1 for i in range(len(a)) if a[i] != b[i])


best = (99, None, None)
n = 0
# keep the from-triple in source order, permute only the dir triple, then also
# try interleavings of the two triples
for dirperm in itertools.permutations("xyz"):
    for order in ("FD", "DF"):
        seq = ("XYZ" + "".join(dirperm)) if order == "FD" \
            else ("".join(dirperm) + "XYZ")
        main = BASE % "".join(A[c] for c in seq)
        src = (HEAD + "int func_ov002_02069a7c(int index) {\n"
               "    Vec3 from;\n    Vec3 dir;\n"
               "    int ok = 1;\n"
               "    short h = *(short *)(func_01fffde0(index) + 0x66);\n\n"
               "    if (h >= 0) {\n" + main
               + "    } else {\n        ok = 0;\n    }\n    return ok;\n}\n")
        tag = "d_%s_%s" % ("".join(dirperm), order)
        nd = run(tag, src)
        n += 1
        if nd is not None:
            print("%-16s bytes=%-3d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
            if nd < best[0]:
                best = (nd, tag, src)
print("\ntried %d, best=%s bytes=%d" % (n, best[1], best[0]))
if best[2] and best[0] == 0:
    with open("build/try/func_ov002_02069a7c.c", "w") as f:
        f.write(best[2])
    print("PROMOTED")
