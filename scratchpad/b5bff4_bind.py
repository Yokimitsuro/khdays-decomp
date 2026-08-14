"""The instruction streams are identical, so the live sets are identical and the
difference must be in the IR before allocation. Re-test the binding shapes on
the current base, reporting the map rather than only the score.
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
    p = "build/try/b5bff4_bd.c"
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
HEAD = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert HEAD in BASE

print("%-22s %31s map=%s" % ("ROM target", "", TARGET))
report("base", BASE)
report("embed_assign", BASE.replace(HEAD,
       "    int nColumn;\n    int nTag;\n    Ov002PanelSession *s;\n"
       "    int nClass = func_ov002_0205a3f0(\n"
       "        &nColumn, (s = data_ov002_0207f620)->bMode);\n"))
report("comma", BASE.replace(HEAD,
       "    int nColumn;\n    int nTag;\n    Ov002PanelSession *s;\n"
       "    int nClass;\n\n"
       "    s = data_ov002_0207f620,\n"
       "    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n"))
report("class_then_session", BASE.replace(HEAD,
       "    int nColumn;\n    int nTag;\n"
       "    int nClass = func_ov002_0205a3f0(\n"
       "        &nColumn, data_ov002_0207f620->bMode);\n"
       "    Ov002PanelSession *s = data_ov002_0207f620;\n"))
report("session_in_switch", BASE.replace(HEAD,
       "    int nColumn;\n    int nTag;\n    Ov002PanelSession *s;\n"
       "    int nClass;\n\n"
       "    nClass = func_ov002_0205a3f0(\n"
       "        &nColumn, data_ov002_0207f620->bMode);\n"
       "    s = data_ov002_0207f620;\n"))
