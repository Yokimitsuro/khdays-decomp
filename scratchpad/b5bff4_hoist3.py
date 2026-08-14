"""Hoist subsets of the case locals to function scope. The names are shared
between cases 2 and 3, so one declaration at function scope serves both and no
renaming is needed.
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
BASE = open("build/try/b5bff4_offset_last.c").read()

HEAD = """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
C2 = """        u16 *pEntry;
        int bFlag;
        int nSlot;
"""
C3 = """        u16 *pEntry;
        int nTag;
        int nSlot;
"""
assert HEAD in BASE and C2 in BASE and C3 in BASE

DECL = {"entry": "    u16 *pEntry;\n",
        "slot": "    int nSlot;\n",
        "flag": "    int bFlag;\n",
        "tag": "    int nTag;\n"}
LINE2 = {"entry": "        u16 *pEntry;\n", "flag": "        int bFlag;\n",
         "slot": "        int nSlot;\n"}
LINE3 = {"entry": "        u16 *pEntry;\n", "tag": "        int nTag;\n",
         "slot": "        int nSlot;\n"}


def build(hoist):
    c2 = "".join(LINE2[k] for k in ("entry", "flag", "slot")
                 if k not in hoist)
    c3 = "".join(LINE3[k] for k in ("entry", "tag", "slot")
                 if k not in hoist)
    s = BASE.replace(C2, c2).replace(C3, c3)
    decls = "".join(DECL[k] for k in ("entry", "slot", "flag", "tag")
                    if k in hoist)
    return s.replace(HEAD, HEAD.replace("    int nColumn;\n",
                                        "    int nColumn;\n" + decls))


def score(tag, s):
    p = "build/try/b5bff4_h.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-26s FAIL" % tag)
        return 9999
    if len(mine) != len(orig):
        print("%-26s SIZE %+d" % (tag, len(mine) - len(orig)))
        return 9999
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-26s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
    return n


NAMES = ["entry", "slot", "flag", "tag"]
best = [9999, None]
for r in range(0, 5):
    for combo in itertools.combinations(NAMES, r):
        n = score(",".join(combo) or "(none)", build(set(combo)))
        if n < best[0]:
            best[0] = n
            best[1] = combo
        if n == 0:
            raise SystemExit
print("best %s bytes %s" % (best[1], best[0]))
