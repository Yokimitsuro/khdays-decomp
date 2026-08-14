"""Hypothesis: 'code' declared short forces mwcc to re-normalize with lsl/asr at
every use instead of doing CSE once, which is the ROM's shape."""
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


def score(tag, s):
    p = "build/try/b2024_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-12s FAIL" % tag)
        return
    ins = list(md.disasm(bytes(mine), 0))
    push9 = "sl" in (ins[0].op_str if ins else "")
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
    print("%-12s SIZE %d (%+d) instr=%d push9=%s%s"
          % (tag, len(mine), len(mine) - len(orig), len(ins), push9, extra))


CAST = "(short)code"

# H1: code as short, explicit casts dropped
score("v_short", BASE.replace("    int code;\n", "    short code;\n")
      .replace(CAST, "code"))

# H2: code as short but the multiply widened back to int
s2 = BASE.replace("    int code;\n", "    short code;\n").replace(CAST, "code")
score("w_shortmul", s2.replace("int off = code * 0x24;",
                               "int off = (int)code * 0x24;"))

# H3: int code, each cast widened so mwcc sees two distinct expressions
score("x_twocast", BASE.replace(CAST, "(int)(short)code"))

# H4: code short, a separate int for the table index
s4 = BASE.replace("    int code;\n", "    short code;\n    int index;\n")
s4 = s4.replace("code = func_ov002_02052270", "index = func_ov002_02052270")
s4 = s4.replace("int off = code * 0x24;", "int off = index * 0x24;")
s4 = s4.replace(CAST, "code")
s4 = s4.replace("    if (mode ", "    code = (short)index;\n    if (mode ")
score("y_split", s4)
