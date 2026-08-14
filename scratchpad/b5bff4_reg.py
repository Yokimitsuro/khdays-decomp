"""The residue is a three-way rotation of r4, r7 and r8 between the session,
the shared scratch and the tag. Try the register storage class, which is a
source-level hint mwcc honours and which period game code used freely.
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

SESSION = "    Ov002PanelSession *s = data_ov002_0207f620;\n"
CLASS = "    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n"
COLUMN = "    int nColumn;\n"
assert SESSION in BASE and CLASS in BASE and COLUMN in BASE


def score(tag, s):
    p = "build/try/b5bff4_r.c"
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


score("reg_session", BASE.replace(SESSION, "    register " + SESSION.strip()
                                  + "\n"))
score("reg_class", BASE.replace(CLASS, "    register " + CLASS.strip() + "\n"))
score("reg_both", BASE.replace(SESSION, "    register " + SESSION.strip()
                               + "\n").replace(CLASS, "    register "
                                               + CLASS.strip() + "\n"))
score("reg_tag", BASE.replace("    int nTag;\n", "    register int nTag;\n"))
score("reg_sess_tag", BASE.replace(SESSION, "    register " + SESSION.strip()
                                   + "\n").replace("    int nTag;\n",
                                                   "    register int nTag;\n"))
