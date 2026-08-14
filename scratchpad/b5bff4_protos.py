"""Untested axis: the declared parameter types of the eight-argument callee. The
ROM materialises a zero in a register and stores it into two stack slots rather
than storing constants directly, which is the kind of thing a narrower declared
parameter type changes. Vary the declared types of the trailing arguments.
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
BASE = open("build/try/%s.c" % SYM).read()
OLD = """extern void func_ov002_0205b0dc(void *pList, int nSlot, int nSub, int nIndex,
                                int a, int b, int c, int d);"""
assert OLD in BASE


def sess(code):
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            return m.group(1)
    return "?"


def report(tag, proto):
    src = BASE.replace(OLD, proto)
    p = "build/try/b5bff4_pr.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-30s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
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
    print("%-30s size=%-5d bytes=%-4s s=%s%s"
          % (tag, len(code), n, sess(code), "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


report("base (all int)", OLD)

VARIANTS = {
    "trailing u8": """extern void func_ov002_0205b0dc(void *pList, int nSlot, int nSub, int nIndex,
                                u8 a, u8 b, u8 c, int d);""",
    "trailing short": """extern void func_ov002_0205b0dc(void *pList, int nSlot, int nSub, int nIndex,
                                short a, short b, short c, int d);""",
    "index u16": """extern void func_ov002_0205b0dc(void *pList, int nSlot, int nSub, u16 nIndex,
                                int a, int b, int c, int d);""",
    "sub u8 index u8": """extern void func_ov002_0205b0dc(void *pList, int nSlot, u8 nSub, u8 nIndex,
                                int a, int b, int c, int d);""",
    "list u8 ptr": """extern void func_ov002_0205b0dc(u8 *pList, int nSlot, int nSub, int nIndex,
                                int a, int b, int c, int d);""",
    "unsigned trailing": """extern void func_ov002_0205b0dc(void *pList, int nSlot, int nSub, int nIndex,
                                unsigned a, unsigned b, unsigned c, unsigned d);""",
    "last two u8": """extern void func_ov002_0205b0dc(void *pList, int nSlot, int nSub, int nIndex,
                                int a, int b, u8 c, u8 d);""",
}
for tag, proto in sorted(VARIANTS.items()):
    report(tag, proto)
