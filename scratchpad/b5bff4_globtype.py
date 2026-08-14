"""Recorded hypothesis: the lever lives in how the LOAD is typed, so vary the type
of the global itself rather than the local that receives it. Every form keeps the
same access pattern via a cast, so the emitted instructions should be unchanged.
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
GLOB = "extern Ov002PanelSession *data_ov002_0207f620;"
SDECL = "    Ov002PanelSession *s = data_ov002_0207f620;"
assert GLOB in BASE and SDECL in BASE


def score(src):
    p = "build/try/b5bff4_gt.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, "?", str(ex).split("\n")[0][:45]
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
    return len(code), n, sr, None


VAR = {
    "global as int": ("extern int data_ov002_0207f620;",
                      "    Ov002PanelSession *s = "
                      "(Ov002PanelSession *)data_ov002_0207f620;"),
    "global as unsigned": ("extern unsigned int data_ov002_0207f620;",
                           "    Ov002PanelSession *s = "
                           "(Ov002PanelSession *)data_ov002_0207f620;"),
    "global as void pointer": ("extern void *data_ov002_0207f620;",
                               "    Ov002PanelSession *s = "
                               "(Ov002PanelSession *)data_ov002_0207f620;"),
    "global as byte pointer": ("extern u8 *data_ov002_0207f620;",
                               "    Ov002PanelSession *s = "
                               "(Ov002PanelSession *)data_ov002_0207f620;"),
    "global as long": ("extern long data_ov002_0207f620;",
                       "    Ov002PanelSession *s = "
                       "(Ov002PanelSession *)data_ov002_0207f620;"),
    "global as function pointer": ("extern void (*data_ov002_0207f620)(void);",
                                   "    Ov002PanelSession *s = "
                                   "(Ov002PanelSession *)data_ov002_0207f620;"),
    "global const int": ("extern const int data_ov002_0207f620;",
                         "    Ov002PanelSession *s = "
                         "(Ov002PanelSession *)data_ov002_0207f620;"),
}

print("ROM: s=r8   |   base: s=r4, 67 bytes")
print("%-32s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr, err = score(BASE)
print("%-32s %-6d %-6s s=%s" % ("base", size, n, sr))
best = (999, None)
for tag, (g, d) in sorted(VAR.items()):
    src = BASE.replace(GLOB, g).replace(SDECL, d)
    size, n, sr, err = score(src)
    if err:
        print("%-32s FAIL %s" % (tag, err))
        continue
    mark = "   MATCH" if n == 0 else ("   POINTER IN " + sr if sr not in ("r4", "?") else "")
    print("%-32s %-6d %-6s s=%s%s" % (tag, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
