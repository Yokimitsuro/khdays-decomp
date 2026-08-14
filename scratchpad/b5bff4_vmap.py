"""Print the virtual-register map, physical register in order of first use in
the body, for the ROM and for a variant, so the allocation order can be compared
position by position.
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
ORIG = bytearray.fromhex(json.load(open("build/func_index.json"))[SYM]["hex"])
RE = re.compile(r"\b(r1[0-5]|r[0-9]|sb|sl|fp|ip|lr|sp|pc)\b")
ALIAS = {"sb": "r9", "sl": "r10", "fp": "r11", "ip": "r12"}
FIXED = {"sp", "pc", "lr", "r0", "r1", "r2", "r3", "r12"}


def vmap(code):
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    order = []
    for t in ins:
        if t.startswith(("push", "pop", "stmdb", "ldmia")):
            continue
        for m in RE.finditer(t):
            r = ALIAS.get(m.group(1), m.group(1))
            if r not in FIXED and r not in order:
                order.append(r)
    return order


def show(tag, src=None):
    if src is None:
        code = ORIG
    else:
        open("build/try/b5bff4_vm.c", "w").write(src)
        o = compile_c("build/try/b5bff4_vm.c", False)
        code, _ = text_relocs(o)
    print("%-16s %s" % (tag, " ".join(vmap(code))))


BASE = open("build/try/%s.c" % SYM).read()
SES = "    Ov002PanelSession *s = data_ov002_0207f620;\n"
show("ROM")
show("base", BASE)
show("via_int", BASE.replace(
    SES, "    Ov002PanelSession *s ="
         " (Ov002PanelSession *)(int)data_ov002_0207f620;\n"))
print()
print("positions are: p1, session, p2, class, tag, scratch, scratch")
print("read each line as the physical register taken by each role in turn")
