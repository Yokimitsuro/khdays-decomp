"""Exact size and instruction count; the whole residue is that the ROM keeps
the session in r8 and the class in r4 while the candidate does the opposite.
Sweep the declaration order of the two.
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

OLD = """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert OLD in BASE

FORMS = {
    "class_decl_first": "    int nColumn;\n    int nClass;\n"
                        "    Ov002PanelSession *s = data_ov002_0207f620;\n\n"
                        "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n",
    "session_first_split": "    int nColumn;\n"
                           "    Ov002PanelSession *s = data_ov002_0207f620;\n"
                           "    int nClass;\n\n"
                           "    nClass = func_ov002_0205a3f0(&nColumn,"
                           " s->bMode);\n",
    "column_last": "    Ov002PanelSession *s = data_ov002_0207f620;\n"
                   "    int nColumn;\n"
                   "    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n",
    "class_first_decl": "    int nClass;\n    int nColumn;\n"
                        "    Ov002PanelSession *s = data_ov002_0207f620;\n\n"
                        "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n",
    "session_last": "    int nColumn;\n    int nClass;\n"
                    "    Ov002PanelSession *s;\n\n"
                    "    s = data_ov002_0207f620;\n"
                    "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n",
}

best = [9999, None]
for tag, form in FORMS.items():
    s = BASE.replace(OLD, form)
    p = "build/try/b5bff4_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-22s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-22s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-22s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
