"""Declaration position and initialiser form for the destination pointer."""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_020576d8"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/b576d8_flat.c").read()

OFF = "nRow * 4 + (nStart / 8) * 0x20 + (nStart % 8) / 2"
PTR_OLD = "    p = pDst + " + OFF + ";\n"
DECL_OLD = "    u8 *p;\n    int i;\n"
assert PTR_OLD in BASE and DECL_OLD in BASE

VARIANTS = {
    "init_paren": (DECL_OLD.replace("    u8 *p;\n", ""),
                   "    {\n        u8 *p = pDst + (" + OFF + ");\n"),
    "init_flat": (DECL_OLD.replace("    u8 *p;\n", ""),
                  "    {\n        u8 *p = pDst + " + OFF + ";\n"),
}

best = [999, None]
# variant a: p declared after i
s = BASE.replace(DECL_OLD, "    int i;\n    u8 *p;\n")
cases = {"p_after_i": s,
         "p_after_i_paren": s.replace(PTR_OLD,
                                      "    p = pDst + (" + OFF + ");\n")}
# variant b: p initialised at its declaration, placed where the assignment was
s2 = BASE.replace(DECL_OLD, "    int i;\n")
s2 = s2.replace(PTR_OLD, "    {\n    u8 *p = pDst + " + OFF + ";\n")
s2 = s2.rstrip()[:-1] + "    }\n}\n"
cases["p_scoped"] = s2
s3 = BASE.replace(DECL_OLD, "    int i;\n")
s3 = s3.replace(PTR_OLD, "    {\n    u8 *p = pDst + (" + OFF + ");\n")
s3 = s3.rstrip()[:-1] + "    }\n}\n"
cases["p_scoped_paren"] = s3

for tag, s in cases.items():
    p = "build/try/b576d8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-18s FAIL" % tag)
        continue
    ins = list(md.disasm(bytes(mine), 0))
    push = ins[0].op_str if ins else ""
    if len(mine) != len(orig):
        print("%-18s SIZE %+d push=%s" % (tag, len(mine) - len(orig), push))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-18s bytes=%d push=%s%s" % (tag, n, push,
                                        "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
