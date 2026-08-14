"""One conversion in the initialiser moves the cached global from r4 to r7, which
is one position later in the allocation order r6, r5, r4, r7, r8. The ROM needs
it at r8, one position further still. Test whether conversions STACK: two casts,
three casts, a cast through several types, and casts combined with the levers
that individually shift position.
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
SDECL = "    Ov002PanelSession *s = data_ov002_0207f620;"
assert SDECL in BASE


def score(src):
    p = "build/try/b5bff4_sk2.c"
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


FORMS = {
    "no cast (base)": SDECL,
    "one cast": "    Ov002PanelSession *s = "
                "(Ov002PanelSession *)data_ov002_0207f620;",
    "two casts": "    Ov002PanelSession *s = "
                 "(Ov002PanelSession *)(void *)data_ov002_0207f620;",
    "three casts": "    Ov002PanelSession *s = "
                   "(Ov002PanelSession *)(u8 *)(void *)data_ov002_0207f620;",
    "four casts": "    Ov002PanelSession *s = (Ov002PanelSession *)(void *)"
                  "(u8 *)(void *)data_ov002_0207f620;",
    "cast through int": "    Ov002PanelSession *s = "
                        "(Ov002PanelSession *)(int)data_ov002_0207f620;",
    "cast through int twice": "    Ov002PanelSession *s = (Ov002PanelSession *)"
                              "(int)(unsigned)data_ov002_0207f620;",
}
C2_NEWOLD = """        int nNew = nTo + nColumn * 6;
        int nOld = nFrom + nColumn * 6;
"""
C2_OLDNEW = """        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
"""

print("ROM: s=r8   |   order of the pool: r6, r5, r4, r7, r8")
print("%-30s %-6s %-6s %-6s %s" % ("variant", "c2", "size", "bytes", "s"))
best = (999, None)
for tag, decl in FORMS.items():
    for c2 in (0, 1):
        src = BASE.replace(SDECL, decl)
        if c2:
            src = src.replace(C2_NEWOLD, C2_OLDNEW)
        size, n, sr, err = score(src)
        if err:
            print("%-30s %-6d FAIL %s" % (tag, c2, err))
            continue
        mark = ""
        if n == 0:
            mark = "   MATCH"
        elif sr == "r8":
            mark = "   POINTER ON r8"
        print("%-30s %-6d %-6d %-6s s=%s%s" % (tag, c2, size, n, sr, mark))
        if isinstance(n, int) and n < best[0]:
            best = (n, "%s c2=%d" % (tag, c2))
        if n == 0:
            open("build/try/%s.c" % SYM, "w").write(src)
            print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
