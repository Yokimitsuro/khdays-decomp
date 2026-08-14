"""The residue is a register permutation with everything else identical, which
on this codebase has twice been fixed by changing how many values are live.
Try binding the mode, read three times, and try dropping the offset local.
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
BASE = open("build/try/%s.c" % SYM).read()


def score(tag, s):
    p = "build/try/b5bff4_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-16s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    if len(mine) != len(orig):
        print("%-16s SIZE %+d" % (tag, len(mine) - len(orig)))
        return
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-16s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)


HEAD = """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert HEAD in BASE

# bind the mode, which is read three times
s1 = BASE.replace(HEAD,
                  "    int nColumn;\n"
                  "    Ov002PanelSession *s = data_ov002_0207f620;\n"
                  "    int nMode = s->bMode;\n"
                  "    int nClass = func_ov002_0205a3f0(&nColumn, nMode);\n")
s1 = s1.replace("func_ov002_0205b7dc(s->bMode, nTo, 0);",
                "func_ov002_0205b7dc(nMode, nTo, 0);")
score("bind_mode", s1)

# drop the offset local introduced for case 1
s2 = BASE.replace("        int nOffset = nColumn * 6;\n        int nIndex;\n",
                  "        int nIndex;\n        int nOffset = nColumn * 6;\n")
score("offset_last", s2)

# the column out parameter declared after the session
s3 = BASE.replace(HEAD,
                  "    Ov002PanelSession *s = data_ov002_0207f620;\n"
                  "    int nColumn;\n"
                  "    int nClass;\n\n"
                  "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n")
score("col_after", s3)
