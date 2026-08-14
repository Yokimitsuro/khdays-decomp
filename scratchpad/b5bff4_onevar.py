"""The ROM's class register also carries case 1's offset and index, case 2's
old index and case 5's flag: thirteen instructions where the candidate uses the
nFrom register instead. That is one variable reused across the switch. Apply it.
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
RE = re.compile(r"\b(r1[0-5]|r[0-9]|sb|sl|fp|ip|lr|sp|pc)\b")
ALIAS = {"sb": "r9", "sl": "r10", "fp": "r11", "ip": "r12"}
FIXED = {"sp", "pc", "lr", "r0", "r1", "r2", "r3", "r12"}
TARGET = "r6 r8 r5 r4 r7 r10 r9"


def vmap(code):
    order = []
    for i in md.disasm(bytes(code), 0):
        t = i.mnemonic + " " + i.op_str
        if t.startswith(("push", "pop", "stmdb", "ldmia")):
            continue
        for m in RE.finditer(t):
            r = ALIAS.get(m.group(1), m.group(1))
            if r not in FIXED and r not in order:
                order.append(r)
    return " ".join(order)


def report(tag, src):
    p = "build/try/b5bff4_ov.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-18s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
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
    vm = vmap(code)
    print("%-18s size=%-5d bytes=%-5s map=%s%s"
          % (tag, len(code), n, vm, "   TARGET" if vm == TARGET else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


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
C1_NEW = """    case 1:
        nClass = nColumn * 6;
        func_ov002_0205afb4(nFrom + nClass, nFrom, 1,
                            func_ov002_0205a600(nFrom + nClass), 0);
        nClass = nColumn * 6 + nTo;
        func_ov002_0205afb4(nClass, nTo, 1, func_ov002_0205a600(nClass), 1);
        s->bIndex = (u8)nClass;
        break;
"""
assert C1_OLD in BASE

C2_OLD = """        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
        u16 *pEntry;
        int bFlag;
        int nSlot;
"""
C2_NEW = """        int nNew = nTo + nColumn * 6;
        u16 *pEntry;
        int bFlag;
        int nSlot;

        nClass = nFrom + nColumn * 6;
"""
assert C2_OLD in BASE

C5_OLD = """        int bFlag = 0;
        u16 nKey = *(u16 *)s->pCachedEntry;

        if (*(int *)((u8 *)s->pCachedEntry + 4) != 0 &&
            func_ov002_0205a714(0, nKey) != 0 &&
            func_ov002_0205a730(0, nKey) != 0) {
            bFlag = 1;
        }
"""
C5_NEW = """        u16 nKey = *(u16 *)s->pCachedEntry;
        int bFlag = 0;

        if (*(int *)((u8 *)s->pCachedEntry + 4) != 0 &&
            func_ov002_0205a714(0, nKey) != 0 &&
            func_ov002_0205a730(0, nKey) != 0) {
            bFlag = 1;
        }
        nClass = 1;
"""
assert C5_OLD in BASE
C5_USE = [("func_ov002_0205ad5c(4, 0, 0x3e0, (u16)(bFlag != 0 ? 0xf : 0xe), 1);",
           "func_ov002_0205ad5c(4, 0, 0x3e0, (u16)(bFlag != 0 ? 0xf : 0xe),\n"
           "                                nClass);"),
          ("func_ov002_0205abe0(5, 1, 0);",
           "func_ov002_0205abe0(5, nClass, 0);"),
          ("func_ov002_0205ad5c(5, 0, 0x3f0, 0xf, 1);",
           "func_ov002_0205ad5c(5, 0, 0x3f0, 0xf, nClass);"),
          ("func_ov002_0205abe0(4, 1, 0);",
           "func_ov002_0205abe0(4, nClass, 0);")]


def case2(s):
    head, rest = s.split("    case 2: {", 1)
    body, tail = rest.split("    case 3: {", 1)
    body = body.replace(C2_OLD, C2_NEW).replace("nOld", "nClass")
    return head + "    case 2: {" + body + "    case 3: {" + tail


report("base", BASE)
s1 = BASE.replace(C1_OLD, C1_NEW)
report("c1", s1)
report("c1+c2", case2(s1))
s3 = case2(s1).replace(C5_OLD, C5_NEW)
for a, b in C5_USE:
    s3 = s3.replace(a, b)
report("c1+c2+c5", s3)
