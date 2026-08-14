"""Run the const variants of the mixed-access test: with a const global mwcc can
fold the direct references onto the same load, so the code should stay the same
size while the value structure changes.
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
    p = "build/try/b5bff4_mx2.c"
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
    vm = vmap(code)
    print("%-26s size=%-5d bytes=%-5s map=%s%s"
          % (tag, len(code), n, vm, "   TARGET" if vm == TARGET else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
EXT = "extern Ov002PanelSession *data_ov002_0207f620;"
CONST = "extern Ov002PanelSession *const data_ov002_0207f620;"
G = "data_ov002_0207f620->"
TAIL = """    s->bKind = (u8)nTo;
    func_ov002_0205b7dc(s->bMode, nTo, 0);
"""
CB = BASE.replace(EXT, CONST)

print("%-26s %27s map=%s" % ("ROM target", "", TARGET))
report("const_only", CB)
report("const+tail_global",
       CB.replace(TAIL, "    " + G + "bKind = (u8)nTo;\n"
                        "    func_ov002_0205b7dc(" + G + "bMode, nTo, 0);\n"))

head, rest = CB.split("    case 0:\n        switch (nFrom) {", 1)
body, rest2 = rest.split("\n    case 1: {", 1)
report("const+case0_global",
       head + "    case 0:\n        switch (nFrom) {"
       + body.replace("s->", G) + "\n    case 1: {" + rest2)

# both regions through the global
s = (head + "    case 0:\n        switch (nFrom) {"
     + body.replace("s->", G) + "\n    case 1: {" + rest2)
report("const+both",
       s.replace(TAIL, "    " + G + "bKind = (u8)nTo;\n"
                       "    func_ov002_0205b7dc(" + G + "bMode, nTo, 0);\n"))
