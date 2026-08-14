"""The emitted code is identical instruction for instruction, so the register
ranking must be shifted by something that does not change the code: an extra
named temporary that mwcc coalesces away. Try naming the intermediate results
this function currently passes straight through.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0205bff4"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/func_ov002_0205bff4.c").read()

GUARD = """    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
"""
assert GUARD in BASE
HEAD = """    int nColumn;
    int nTag;
"""
assert HEAD in BASE


def score(tag, s):
    p = "build/try/b5bff4_t.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-22s FAIL" % tag)
        return 9999
    if len(mine) != len(orig):
        print("%-22s SIZE %+d" % (tag, len(mine) - len(orig)))
        return 9999
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-22s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
    return n


# name the tag lookup result
s1 = BASE.replace(HEAD, HEAD + "    int nEntry;\n")
s1 = s1.replace(GUARD, """    nEntry = func_ov002_020536bc(0xe);
    if (func_ov002_0205374c(nEntry) == 0) {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
""")
score("name_entry", s1)

# name both intermediate results
s2 = BASE.replace(HEAD, HEAD + "    int nEntry;\n    int nSub;\n")
s2 = s2.replace(GUARD, """    nEntry = func_ov002_020536bc(0xe);
    if (func_ov002_0205374c(nEntry) == 0) {
        nSub = func_ov002_02053558(0x79);
        func_ov002_020535f0(nSub);
    }
""")
score("name_both", s2)

# name only the inner one
s3 = BASE.replace(HEAD, HEAD + "    int nSub;\n")
s3 = s3.replace(GUARD, """    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {
        nSub = func_ov002_02053558(0x79);
        func_ov002_020535f0(nSub);
    }
""")
score("name_sub", s3)

# invert the guard so the body is the fall-through
s4 = BASE.replace(GUARD, """    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) != 0) {
    } else {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
""")
score("invert_guard", s4)
