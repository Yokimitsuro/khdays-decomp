"""Final axis: the types in the codegen struct and the locals. Casts that vanish
change the expression trees mwcc builds without changing the emitted code, which
is the kind of thing that can rotate the register assignment.
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


def score(tag, s):
    p = "build/try/b5bff4_ty.c"
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


# cached entry typed as a halfword pointer, dropping both casts
s1 = BASE.replace("    void *pCachedEntry;     /* +0x4a4 */",
                  "    u16 *pCachedEntry;      /* +0x4a4 */")
s1 = s1.replace("u16 nKey = *(u16 *)s->pCachedEntry;",
                "u16 nKey = *s->pCachedEntry;")
s1 = s1.replace("*(int *)((u8 *)s->pCachedEntry + 4) != 0",
                "*(int *)(s->pCachedEntry + 2) != 0")
score("entry_u16", s1)

# the list lookups returning a halfword pointer directly
s2 = BASE.replace("extern void *func_02010154(void *pList, u16 nIndex);",
                  "extern u16 *func_02010154(void *pList, u16 nIndex);")
s2 = s2.replace("pEntry = (u16 *)func_02010154", "pEntry = func_02010154")
score("lookup_u16", s2)

# both
s3 = s1.replace("extern void *func_02010154(void *pList, u16 nIndex);",
                "extern u16 *func_02010154(void *pList, u16 nIndex);")
s3 = s3.replace("pEntry = (u16 *)func_02010154", "pEntry = func_02010154")
score("both_u16", s3)

# the object in case 0 arm 2 typed as a halfword pointer too
s4 = BASE.replace("extern void *NNS_FndGetNextListObject(void *pList,"
                  " void *pPrev);",
                  "extern u16 *NNS_FndGetNextListObject(void *pList,"
                  " void *pPrev);")
s4 = s4.replace("void *pObject = NNS_FndGetNextListObject",
                "u16 *pObject = NNS_FndGetNextListObject")
score("object_u16", s4)
