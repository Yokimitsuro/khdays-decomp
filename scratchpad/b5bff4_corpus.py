"""A matched large ARM switch function in the tree, func_ov000_02050ec4,
declares its context pointer FIRST and then every other local at function
scope, with no declarations inside the cases. The earlier hoist-all test put
the session last; retry with the corpus shape.
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
BASE = open("build/try/b5bff4_offset_last.c").read()

HEAD = """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
C0A1 = "        case 1: {\n            int nValue = func_ov002_0205a638();\n"
C0A2 = ("        case 2: {\n            int nValue;\n"
        "            void *pObject = NNS_FndGetNextListObject(s->listItems,"
        " 0);\n")
C1 = "    case 1: {\n        int nIndex;\n        int nOffset = nColumn * 6;\n"
C2 = ("    case 2: {\n        int nOld = nFrom + nColumn * 6;\n"
      "        int nNew = nTo + nColumn * 6;\n        u16 *pEntry;\n"
      "        int bFlag;\n        int nSlot;\n")
C3 = ("    case 3: {\n        int nOld = nFrom + nColumn * 6;\n"
      "        int nNew = nTo + nColumn * 6;\n        u16 *pEntry;\n"
      "        int nTag;\n        int nSlot;\n")
C5 = ("    case 5: {\n        int bFlag = 0;\n"
      "        u16 nKey = *(u16 *)s->pCachedEntry;\n")
for blk in (HEAD, C0A1, C0A2, C1, C2, C3, C5):
    assert blk in BASE, blk[:40]

s = BASE
s = s.replace(C0A1, "        case 1: {\n            nValue ="
                    " func_ov002_0205a638();\n")
s = s.replace(C0A2, "        case 2: {\n            pObject ="
                    " NNS_FndGetNextListObject(s->listItems, 0);\n")
s = s.replace(C1, "    case 1: {\n        nOffset = nColumn * 6;\n")
s = s.replace(C2, "    case 2: {\n        nOld = nFrom + nColumn * 6;\n"
                  "        nNew = nTo + nColumn * 6;\n")
s = s.replace(C3, "    case 3: {\n        nOld = nFrom + nColumn * 6;\n"
                  "        nNew = nTo + nColumn * 6;\n")
s = s.replace(C5, "    case 5: {\n        bFlag = 0;\n"
                  "        nKey = *(u16 *)s->pCachedEntry;\n")

NEW = """    Ov002PanelSession *s = data_ov002_0207f620;
    int nColumn;
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

    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
s = s.replace(HEAD, NEW)

p = "build/try/b5bff4_corpus.c"
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
