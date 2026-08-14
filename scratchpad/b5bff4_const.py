"""The ROM allocates the session last among the three despite defining it first,
which is how a compiler treats a value it considers re-derivable or lower
priority. Try qualifiers and shapes that change how the session's value is
classified.
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

SES = "    Ov002PanelSession *s = data_ov002_0207f620;\n"
assert SES in BASE
EXT = "extern Ov002PanelSession *data_ov002_0207f620;"
assert EXT in BASE


def score(tag, s):
    p = "build/try/b5bff4_cn.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-20s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return 9999
    if len(mine) != len(orig):
        print("%-20s SIZE %+d" % (tag, len(mine) - len(orig)))
        return 9999
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-20s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
    return n


score("const_ptr", BASE.replace(
    SES, "    Ov002PanelSession *const s = data_ov002_0207f620;\n"))
score("const_target", BASE.replace(
    SES, "    const Ov002PanelSession *s = data_ov002_0207f620;\n")
    if False else BASE)
score("ext_const", BASE.replace(
    EXT, "extern Ov002PanelSession *const data_ov002_0207f620;"))
score("both_const", BASE.replace(
    EXT, "extern Ov002PanelSession *const data_ov002_0207f620;").replace(
    SES, "    Ov002PanelSession *const s = data_ov002_0207f620;\n"))
