"""In the ROM r7 holds case 3's tag while the class sits in r4 and the session
in r8; in the candidate r7 holds the class. Hoisting every local was worse, so
try hoisting only the ones the ROM keeps in the high registers.
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

HEAD = """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert HEAD in BASE
TAGDECL = """        u16 *pEntry;
        int nTag;
        int nSlot;

        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);
"""
assert TAGDECL in BASE


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


# hoist only the tag
s1 = BASE.replace(HEAD, HEAD.replace("    int nColumn;\n",
                                     "    int nColumn;\n    int nTag;\n"))
s1 = s1.replace(TAGDECL, """        u16 *pEntry;
        int nSlot;

        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);
""")
score("hoist_tag", s1)

# hoist the tag before the column
s2 = BASE.replace(HEAD, "    int nTag;\n" + HEAD)
s2 = s2.replace(TAGDECL, """        u16 *pEntry;
        int nSlot;

        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);
""")
score("tag_first", s2)

# hoist the tag after the session
s3 = BASE.replace(HEAD, HEAD + "    int nTag;\n")
s3 = s3.replace(TAGDECL, """        u16 *pEntry;
        int nSlot;

        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);
""")
score("tag_last", s3)
