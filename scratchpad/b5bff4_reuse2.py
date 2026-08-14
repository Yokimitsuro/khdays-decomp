"""Reuse the class variable as each case's destination index, which is what the
canonical comparison shows the ROM doing.
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

C1_OLD = """    case 1: {
        int nOffset = nColumn * 6;
        int nIndex;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nIndex = nColumn * 6 + nTo;
        func_ov002_0205afb4(nIndex, nTo, 1, func_ov002_0205a600(nIndex), 1);
        s->bIndex = (u8)nIndex;
        break;
    }
"""
C1_NEW = """    case 1: {
        int nOffset = nColumn * 6;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nClass = nColumn * 6 + nTo;
        func_ov002_0205afb4(nClass, nTo, 1, func_ov002_0205a600(nClass), 1);
        s->bIndex = (u8)nClass;
        break;
    }
"""
assert C1_OLD in BASE

C3_OLD = """        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
        u16 *pEntry;
        int nSlot;
"""
C3_NEW = """        int nOld = nFrom + nColumn * 6;
        u16 *pEntry;
        int nSlot;

        nClass = nTo + nColumn * 6;
"""
assert C3_OLD in BASE


def score(tag, s):
    p = "build/try/b5bff4_ru.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-18s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return 9999
    if len(mine) != len(orig):
        print("%-18s SIZE %+d" % (tag, len(mine) - len(orig)))
        return 9999
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-18s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
    return n


def case3(s):
    head, rest = s.split("    case 3: {", 1)
    body, tail = rest.split("    case 4:", 1)
    body = body.replace(C3_OLD, C3_NEW).replace("nNew", "nClass")
    return head + "    case 3: {" + body + "    case 4:" + tail


score("case1", BASE.replace(C1_OLD, C1_NEW))
score("case3", case3(BASE))
score("both", case3(BASE.replace(C1_OLD, C1_NEW)))
