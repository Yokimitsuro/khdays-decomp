"""Check whether the 67 to 66 improvement from a preceding function is real or a
literal-pool artifact: report WHERE the differing bytes sit and whether the
instruction stream changed at all.
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
BASE = open("build/try/%s.c" % SYM).read()
SIG = "void func_ov002_0205bff4(int nFrom, int nTo) {"
PRE = ("static void ov002_f0(int a) {\n"
       "    Ov002PanelSession *p = data_ov002_0207f620;\n\n"
       "    func_ov002_02053cd4(p->bMode + a);\n}\n\n")


def build(src):
    p = "build/try/b5bff4_tc.c"
    open(p, "w").write(src)
    o = compile_c(p, False)
    return text_relocs(o)


c0, r0 = build(BASE)
c1, r1 = build(BASE.replace(SIG, PRE + SIG))
print("plain     %d bytes,  with preceding function %d bytes" % (len(c0), len(c1)))
print("instruction streams identical:", bytes(c0) == bytes(c1))

for label, code, mrel in (("plain", c0, r0), ("preceded", c1, r1)):
    a = bytearray(ORIG)
    b = bytearray(code)
    for off in set(OREL) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    diffs = [i for i in range(len(a)) if a[i] != b[i]]
    tail = [d for d in diffs if d >= len(ORIG) - 96]
    print("%-9s differing bytes=%-4d  last offset=0x%x  in final 96 bytes=%d"
          % (label, len(diffs), diffs[-1] if diffs else 0, len(tail)))

# where do the two builds differ from each other
d2 = [i for i in range(min(len(c0), len(c1))) if c0[i] != c1[i]]
print()
print("the two builds differ from EACH OTHER at %d offsets: %s"
      % (len(d2), [hex(x) for x in d2[:12]]))
if d2:
    lo = (d2[0] // 4) * 4
    print("first differing word at 0x%x" % lo)
    for name, code in (("plain", c0), ("preceded", c1)):
        w = code[lo:lo + 4]
        ins = list(md.disasm(bytes(w), lo))
        print("   %-9s %s  %s" % (name, w.hex(),
                                  (ins[0].mnemonic + " " + ins[0].op_str)
                                  if ins else "(not an instruction)"))
    print("function size 0x%x; literal pool normally sits at the end"
          % len(ORIG))
