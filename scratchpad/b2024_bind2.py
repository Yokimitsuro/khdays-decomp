"""Re-run the value-binding sweep on the corrected baseline (switch form, 364B).

The earlier sweep ran against the candidate that still range-optimized the
three-way test, so its results no longer apply. Target: one more long-lived
value so mwcc pushes nine callee-saved registers.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_02052024"]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/func_ov002_02052024.c").read()
DECL = "    int code;\n    int i;\n"


def score(tag, s):
    p = "build/try/b2024_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-14s FAIL" % tag)
        return
    ins = list(md.disasm(bytes(mine), 0))
    push = ins[0].op_str if ins else ""
    nine = "sl" in push
    extra = ""
    if len(mine) == len(orig):
        a = bytearray(orig)
        b = bytearray(mine)
        for off in set(orel) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
        extra = "  bytes=%d%s" % (n, "   MATCH" if n == 0 else "")
        if n == 0:
            open("build/try/func_ov002_02052024.c", "w").write(s)
            print("PROMOTED " + tag)
    print("%-14s SIZE %d (%+d) instr=%d nine=%s%s"
          % (tag, len(mine), len(mine) - len(orig), len(ins), nine, extra))


# bind the animation object once
s = BASE.replace(DECL, "    char *anim = self + 4;\n" + DECL)
score("a_anim", s.replace("self + 4,", "anim,").replace("self + 4)", "anim)"))

# bind the inline table once
s = BASE.replace(DECL, "    char *own = self + 0x13c;\n" + DECL)
score("b_own", s.replace("self + 0x13c", "own"))

# bind both
s = BASE.replace(DECL, "    char *anim = self + 4;\n"
                       "    char *own = self + 0x13c;\n" + DECL)
s = s.replace("self + 4,", "anim,").replace("self + 4)", "anim)")
score("c_both", s.replace("self + 0x13c", "own"))

# bind the fifth argument once
s = BASE.replace(DECL, DECL + "    int fifth = arg5;\n")
score("d_fifth", s.replace(", arg5);", ", fifth);"))

# bind the blend value once
s = BASE.replace(DECL, DECL + "    int blend;\n")
s = s.replace("    code = func_ov002_02052270",
              "    code = func_ov002_02052270")
s = s.replace("if (mode ", "blend = (short)code;\n    if (mode ", 1)
score("e_blend", s.replace("(short)code", "blend"))

# the table pointer read once into a local
s = BASE.replace("        int off = code * 0x24;\n",
                 "        char *tab = ((Ov002TableSet *)state)->pTables"
                 " + code * 0x24;\n")
s = s.replace("((Ov002TableSet *)state)->pTables + off,\n"
              "                          0)", "tab, 0)")
s = s.replace("((Ov002TableSet *)state)->pTables + off, 0,\n"
              "                      arg5)", "tab, 0, arg5)")
score("f_tab", s)
