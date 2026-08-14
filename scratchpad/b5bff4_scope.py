"""Declare the session inside a block that spans the whole body, with the other
locals outside it, so mwcc creates its virtual register after theirs instead of
before.
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

HEAD = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert HEAD in BASE
head, body = BASE.split(HEAD, 1)
# body ends with the closing brace of the function
assert body.rstrip().endswith("}")
inner = body.rstrip()[:-1].rstrip()


def score(tag, s):
    p = "build/try/b5bff4_sc.c"
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


# session inside a block spanning the body
s1 = (head
      + "    int nColumn;\n    int nTag;\n    int nClass;\n\n"
      + "    {\n        Ov002PanelSession *s = data_ov002_0207f620;\n\n"
      + "        nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n"
      + inner + "\n    }\n}\n")
score("session_block", s1)

# session and class both inside, column outside
s2 = (head
      + "    int nColumn;\n    int nTag;\n\n"
      + "    {\n        Ov002PanelSession *s = data_ov002_0207f620;\n"
      + "        int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n"
      + inner + "\n    }\n}\n")
score("both_block", s2)

# class outside, session and the rest inside, tag inside too
s3 = (head
      + "    int nColumn;\n    int nClass;\n\n"
      + "    {\n        Ov002PanelSession *s = data_ov002_0207f620;\n"
      + "        int nTag;\n\n"
      + "        nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n"
      + inner + "\n    }\n}\n")
score("tag_inside", s3)
