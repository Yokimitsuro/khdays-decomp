"""mwcc pragmas are part of the SOURCE, not the toolchain, and several of them
aim straight at this residue: opt_lifetimes and register_coloring control the
very pass that decides the assignment. If one reproduces the ROM, that is
evidence about what the original translation unit contained.
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


def score(src):
    p = "build/try/b5bff4_pg.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:60]
    n = None
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    sr = "?"
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    return len(code), n, sr


PRAGMAS = [
    "register_coloring on",
    "register_coloring off",
    "opt_lifetimes on",
    "opt_lifetimes off",
    "global_optimizer on",
    "global_optimizer off",
    "optimize_for_size on",
    "optimize_for_size off",
    "opt_common_subs on",
    "opt_common_subs off",
    "opt_propagation on",
    "opt_propagation off",
    "opt_dead_code on",
    "opt_dead_code off",
    "peephole on",
    "peephole off",
    "opt_strength_reduction on",
    "opt_strength_reduction off",
    "optimization_level 4",
    "optimization_level 3",
    "optimization_level 2",
    "opt_dead_assignments on",
    "opt_dead_assignments off",
    "opt_loop_invariants on",
    "opt_loop_invariants off",
]

print("%-34s %-6s %-6s %s" % ("pragma", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-34s %-6d %-6s %s" % ("(none)", size, n, sr))
best = (99, None)
for pg in PRAGMAS:
    src = "#pragma %s\n\n" % pg + BASE
    size, n, sr = score(src)
    if size is None:
        print("%-34s FAIL %s" % (pg, sr))
        continue
    mark = ""
    if n == 0:
        mark = "   MATCH"
    elif sr not in ("r4", "?"):
        mark = "   POINTER MOVED"
    print("%-34s %-6d %-6s %s%s" % (pg, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, pg)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + pg)
        break
print()
print("best: %s bytes  %s" % best)
