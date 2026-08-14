"""In the ROM case 1's index shares the class's register; in the candidate it
shares p1's. Growing the class's coalesced group may be what lifts it above the
parameters. Check the map for the case 1 reuse, alone and with the cast.
"""
import sys
import os
import json
import re
import itertools

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
    p = "build/try/b5bff4_gw.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
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
    print("%-22s size=%-5d bytes=%-5s map=%s%s"
          % (tag, len(code), n, vm, "   TARGET" if vm == TARGET else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
SES = "    Ov002PanelSession *s = data_ov002_0207f620;\n"
CAST = ("    Ov002PanelSession *s ="
        " (Ov002PanelSession *)(int)data_ov002_0207f620;\n")

C1_OLD = """        int nOffset = nColumn * 6;
        int nIndex;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nIndex = nColumn * 6 + nTo;
        func_ov002_0205afb4(nIndex, nTo, 1, func_ov002_0205a600(nIndex), 1);
        s->bIndex = (u8)nIndex;
"""
C1_NEW = """        int nOffset = nColumn * 6;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nClass = nColumn * 6 + nTo;
        func_ov002_0205afb4(nClass, nTo, 1, func_ov002_0205a600(nClass), 1);
        s->bIndex = (u8)nClass;
"""
assert C1_OLD in BASE

C5_OLD = """            func_ov002_0205ad5c(4, 0, 0x3e0, (u16)(bFlag != 0 ? 0xf : 0xe), 1);
            func_ov002_0205ad5c(5, 0, 0x3f0, 0xf, 0);
            func_ov002_0205abe0(4, 0, 0);
            func_ov002_0205abe0(5, 1, 0);
"""
C5_NEW = """            nClass = 1;
            func_ov002_0205ad5c(4, 0, 0x3e0, (u16)(bFlag != 0 ? 0xf : 0xe),
                                nClass);
            func_ov002_0205ad5c(5, 0, 0x3f0, 0xf, 0);
            func_ov002_0205abe0(4, 0, 0);
            func_ov002_0205abe0(5, nClass, 0);
"""
has5 = C5_OLD in BASE

print("%-22s %31s map=%s" % ("ROM target", "", TARGET))
for cast, c1, c5 in itertools.product([0, 1], [0, 1], [0, 1]):
    if c5 and not has5:
        continue
    s = BASE
    if cast:
        s = s.replace(SES, CAST)
    if c1:
        s = s.replace(C1_OLD, C1_NEW)
    if c5:
        s = s.replace(C5_OLD, C5_NEW)
    report("cast%d c1%d c5%d" % (cast, c1, c5), s)
