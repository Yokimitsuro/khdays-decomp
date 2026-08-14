"""The ROM's r4 is the scratch every case reuses and it also holds the class,
so the class coalesces with the case locals. Which register that whole group
gets may follow from whether the case locals are declared at function scope.
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

# Strip the per-case declarations and hoist them.
BODY = BASE
DECL_BLOCKS = [
    ("        case 1: {\n            int nValue = func_ov002_0205a638();\n",
     "        case 1: {\n            nValue = func_ov002_0205a638();\n"),
    ("        case 2: {\n            int nValue;\n"
     "            void *pObject = NNS_FndGetNextListObject(s->listItems, 0);\n",
     "        case 2: {\n"
     "            pObject = NNS_FndGetNextListObject(s->listItems, 0);\n"),
    ("    case 1: {\n        int nOffset = nColumn * 6;\n        int nIndex;\n",
     "    case 1: {\n        nOffset = nColumn * 6;\n"),
    ("    case 2: {\n        int nOld = nFrom + nColumn * 6;\n"
     "        int nNew = nTo + nColumn * 6;\n        u16 *pEntry;\n"
     "        int bFlag;\n        int nSlot;\n",
     "    case 2: {\n        nOld = nFrom + nColumn * 6;\n"
     "        nNew = nTo + nColumn * 6;\n"),
    ("    case 3: {\n        int nOld = nFrom + nColumn * 6;\n"
     "        int nNew = nTo + nColumn * 6;\n        u16 *pEntry;\n"
     "        int nTag;\n        int nSlot;\n",
     "    case 3: {\n        nOld = nFrom + nColumn * 6;\n"
     "        nNew = nTo + nColumn * 6;\n"),
    ("    case 5: {\n        int bFlag = 0;\n"
     "        u16 nKey = *(u16 *)s->pCachedEntry;\n",
     "    case 5: {\n        bFlag = 0;\n"
     "        nKey = *(u16 *)s->pCachedEntry;\n"),
]
for a, b in DECL_BLOCKS:
    assert a in BODY, a[:40]
    BODY = BODY.replace(a, b)

HOISTED = """    int nColumn;
    int nClass;
    int nValue;
    void *pObject;
    int nOffset;
    int nIndex;
    int nOld;
    int nNew;
    u16 *pEntry;
    int bFlag;
    int nSlot;
    int nTag;
    u16 nKey;
    Ov002PanelSession *s = data_ov002_0207f620;

    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
s = BODY.replace(HEAD_OLD, HOISTED)
p = "build/try/b5bff4_hoist.c"
open(p, "w").write(s)
try:
    o = compile_c(p, False)
    mine, mrel = text_relocs(o)
    if len(mine) != len(orig):
        print("SIZE %+d" % (len(mine) - len(orig)))
    else:
        a = bytearray(orig)
        b = bytearray(mine)
        for off in set(orel) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
        print("bytes=%d%s" % (n, "   MATCH" if n == 0 else ""))
        if n == 0:
            open("build/try/%s.c" % SYM, "w").write(s)
            print("PROMOTED")
except Exception as ex:
    print("FAIL %s" % str(ex).split("\n")[0][:120])
