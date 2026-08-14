"""In the ROM one register, r4, carries the classifier result and then case 1's
index, case 2's first index, case 3's rebind and case 5's flag. My source only
reuses nClass in case 3. Make the other cases share the same variable so the web
carries the same members, which raises its degree above the session pointer's.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}
ROM = "nFrom=r6 nTo=r5 s=r8 nClass=r4 nOld=r4 nNew=r7"


def webmap(code):
    ins = [(i.mnemonic + " " + i.op_str) for i in md.disasm(bytes(code), 0)]
    d = {}
    for t in ins[:14]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and "s" not in d:
            d["s"] = m.group(1)
        m = re.match(r"^mov (r\w+), r0$", t)
        if m:
            if "nFrom" not in d:
                d["nFrom"] = m.group(1)
            elif "nClass" not in d:
                d["nClass"] = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and "nTo" not in d:
            d["nTo"] = m.group(1)
    for t in ins:
        m = re.match(r"^add (r\w+), r6, r2$", t)
        if m and "nOld" not in d:
            d["nOld"] = m.group(1)
        m = re.match(r"^add (r\w+), r5, r2$", t)
        if m and "nNew" not in d:
            d["nNew"] = m.group(1)
    return "nFrom=%s nTo=%s s=%s nClass=%s nOld=%s nNew=%s" % (
        d.get("nFrom", "?"), d.get("nTo", "?"), d.get("s", "?"),
        d.get("nClass", "?"), d.get("nOld", "?"), d.get("nNew", "?"))


def report(tag, src):
    p = "build/try/b5bff4_sh.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return
    n = "-"
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    w = webmap(code)
    print("%-26s %-5d b=%-4s %s%s" % (tag, len(code), n, w,
                                      "  <== ROM" if w == ROM else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/b5bff4_best.c").read()
report("best", BASE)

C1_OLD = """    case 1: {
        int nOffset = nColumn * 6;
        int nIndex;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nIndex = nColumn * 6 + nTo;
        func_ov002_0205afb4(nIndex, nTo, 1, func_ov002_0205a600(nIndex), 1);
        s->bIndex = (u8)nIndex;
        break;
    }"""
C1_NEW = """    case 1: {
        int nOffset = nColumn * 6;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nClass = nColumn * 6 + nTo;
        func_ov002_0205afb4(nClass, nTo, 1, func_ov002_0205a600(nClass), 1);
        s->bIndex = (u8)nClass;
        break;
    }"""
assert C1_OLD in BASE

C5_OLD = """    case 5: {
        int bFlag = 0;
        u16 nKey = *(u16 *)s->pCachedEntry;
"""
C5_NEW = """    case 5: {
        u16 nKey = *(u16 *)s->pCachedEntry;

        nClass = 0;
"""
assert C5_OLD in BASE


def case5(src):
    s = src.replace(C5_OLD, C5_NEW)
    # rewrite the remaining uses of bFlag inside case 5 only
    head, tail = s.split("    case 5: {", 1)
    tail = tail.replace("bFlag = 1;", "nClass = 1;")
    tail = tail.replace("bFlag != 0 ?", "nClass != 0 ?")
    return head + "    case 5: {" + tail


report("case1_shares_nClass", BASE.replace(C1_OLD, C1_NEW))
report("case5_shares_nClass", case5(BASE))
report("case1+5_share", case5(BASE.replace(C1_OLD, C1_NEW)))

# also give case 2's first index the same variable
C2_OLD = """        int nNew = nTo + nColumn * 6;
        int nOld = nFrom + nColumn * 6;
"""
C2_NEW = """        int nNew = nTo + nColumn * 6;
"""
S = case5(BASE.replace(C1_OLD, C1_NEW))
S2 = S.replace(C2_OLD, C2_NEW)
head, tail = S2.split("    case 2: {", 1)
tail = tail.replace("nOld", "nClass", 3)
report("case1+2+5_share", head + "    case 2: {" + tail)
