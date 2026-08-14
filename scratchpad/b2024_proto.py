"""The ROM keeps 'code' raw in r8 and re-derives the 16-bit blend at each call
site. That is the signature of a narrowing conversion performed BY THE CALL,
not by an explicit cast in the source: if the callee's blend parameter is
declared short, mwcc emits lsl/asr at every call and must keep the raw value.
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

P_ACC = "void *table, int blend);"
P_AD = "void *table, int blend, int arg5);"


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
    nine = "sl" in (ins[0].op_str if ins else "")
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


# both blend parameters narrowed to short, source passes the raw int
s = BASE.replace(P_ACC, "void *table, short blend);")
s = s.replace(P_AD, "void *table, short blend, int arg5);")
score("g_bothshort", s.replace("(short)code", "code"))

# only the five-argument call narrowed
s = BASE.replace(P_AD, "void *table, short blend, int arg5);")
score("h_adshort", s.replace(", (short)code, arg5)", ", code, arg5)"))

# only the loop call narrowed
s = BASE.replace(P_ACC, "void *table, short blend);")
score("i_accshort", s.replace("self + 0x13c, (short)code)", "self + 0x13c, code)"))

# both narrowed, and the zero blend of the table path stays an int literal
s = BASE.replace(P_ACC, "void *table, short blend);")
s = s.replace(P_AD, "void *table, short blend, int arg5);")
s = s.replace("(short)code", "code")
score("j_shortcode", s.replace("    int code;\n", "    short code;\n"))
