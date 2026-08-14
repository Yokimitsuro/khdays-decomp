"""My build assigns r4, r7, r8 to the three virtual registers in definition
order; the ROM assigns r4 and r7 to the two scratch groups and r8 to the
session. So the session's virtual register has to be created last. Re-sweep the
declaration permutations now that the case 3 reuse is in place.
"""
import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0205bff4"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

HEAD = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert HEAD in BASE

DECLS = {
    "col": "    int nColumn;\n",
    "tag": "    int nTag;\n",
    "ses": "    Ov002PanelSession *s;\n",
    "cls": "    int nClass;\n",
}
INIT = ("\n    s = data_ov002_0207f620;\n"
        "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n")

best = [9999, None]
for perm in itertools.permutations(DECLS):
    head = "".join(DECLS[k] for k in perm) + INIT
    s = BASE.replace(HEAD, head)
    p = "build/try/b5bff4_p2.c"
    open(p, "w").write(s)
    tag = "-".join(perm)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        continue
    if len(mine) != len(orig):
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    if n <= best[0]:
        best[0] = n
        best[1] = tag
        print("%-22s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
