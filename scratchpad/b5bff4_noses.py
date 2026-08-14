"""Same pushed register set, same instruction stream, only which variable gets
which register. The session is defined before the class in the candidate and
gets the lower register; in the ROM it is the other way round. Try letting mwcc
cache the global itself instead of binding a local.
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
assert HEAD_OLD in BASE


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


# no session local at all
noloc = BASE.replace(HEAD_OLD,
                     "    int nColumn;\n"
                     "    int nClass = func_ov002_0205a3f0("
                     "&nColumn, data_ov002_0207f620->bMode);\n")
noloc = noloc.replace("s->", "data_ov002_0207f620->")
score("noloc", noloc)

# session bound after the classifier call
after = BASE.replace(HEAD_OLD,
                     "    int nColumn;\n"
                     "    int nClass = func_ov002_0205a3f0("
                     "&nColumn, data_ov002_0207f620->bMode);\n"
                     "    Ov002PanelSession *s = data_ov002_0207f620;\n")
score("after", after)

# session bound after, as a statement
after2 = BASE.replace(HEAD_OLD,
                      "    int nColumn;\n"
                      "    Ov002PanelSession *s;\n"
                      "    int nClass = func_ov002_0205a3f0("
                      "&nColumn, data_ov002_0207f620->bMode);\n\n"
                      "    s = data_ov002_0207f620;\n")
score("after2", after2)
