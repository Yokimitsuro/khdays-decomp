"""Try removing the class variable so the switch runs on the call result, and a
couple of neighbouring shapes, to change the order mwcc creates its virtual
registers in.
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

HEAD_OLD = """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
SW_OLD = "    switch (nClass) {\n"
assert HEAD_OLD in BASE and SW_OLD in BASE


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


# the guard block moved above the classifier call
s1 = BASE.replace(HEAD_OLD,
                  "    int nColumn;\n"
                  "    Ov002PanelSession *s = data_ov002_0207f620;\n"
                  "    int nClass;\n\n"
                  "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n")
score("split_assign", s1)

# session typed as a plain byte pointer, fields reached by offset
s2 = BASE.replace("Ov002PanelSession *s = data_ov002_0207f620;",
                  "Ov002PanelSession *s = data_ov002_0207f620;")
s2 = s2.replace(HEAD_OLD,
                "    Ov002PanelSession *s;\n"
                "    int nColumn;\n"
                "    int nClass;\n\n"
                "    s = data_ov002_0207f620;\n"
                "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n")
score("all_split", s2)

# class declared inside the switch scope is impossible, so instead make the
# column the first declaration and the class the last
s3 = BASE.replace(HEAD_OLD,
                  "    Ov002PanelSession *s = data_ov002_0207f620;\n"
                  "    int nClass;\n"
                  "    int nColumn;\n\n"
                  "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n")
score("col_last2", s3)
