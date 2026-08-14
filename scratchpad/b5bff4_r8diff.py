"""The two-pointer form finally puts the session in r8, the ROM's register, at a
cost of 8 bytes. Find out exactly which instructions those 8 bytes are: if they
are a redundant reload, a restructuring might keep the two webs while emitting
one load.
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
BASE = open("build/try/%s.c" % SYM).read()
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
NEW = DECL + "    Ov002PanelSession *s2 = data_ov002_0207f620;\n"
head, tail = BASE.replace(DECL, NEW).split("    switch (nClass) {", 1)
src = head + "    switch (nClass) {" + tail.replace("s->", "s2->")
open("build/try/b5bff4_r8.c", "w").write(src)
o = compile_c("build/try/b5bff4_r8.c", False)
code, _ = text_relocs(o)
print("variant size %d, ROM size %d, difference %d bytes"
      % (len(code), len(ORIG), len(code) - len(ORIG)))
print()
la = list(md.disasm(bytes(ORIG), 0))
lb = list(md.disasm(bytes(code), 0))
print("ROM instructions %d, variant %d" % (len(la), len(lb)))
print()
print("first 26 instructions side by side")
for i in range(26):
    a = (la[i].mnemonic + " " + la[i].op_str) if i < len(la) else ""
    b = (lb[i].mnemonic + " " + lb[i].op_str) if i < len(lb) else ""
    print("  %3d %-34s | %-34s %s" % (i, a, b, "" if a == b else "<<"))
