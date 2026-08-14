"""Recorded plan: get two pointer webs sharing ONE load, since propagation folds
every plain copy and a second load costs 8 bytes. Try forms where the second web
is not a copy: a conditional definition, a value round-tripped through a field of
the session, and the pointer recovered from an argument expression.
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
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert DECL in BASE


def score(src):
    p = "build/try/b5bff4_tw.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:45]
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


def swap_after_switch(src):
    head, tail = src.split("    switch (nClass) {", 1)
    return head + "    switch (nClass) {" + tail.replace("s->", "s2->")


VARIANTS = {}

# 1. the pointer conditionally redefined from itself, which is not a plain copy
VARIANTS["conditional self"] = swap_after_switch(BASE.replace(
    DECL, DECL + "    Ov002PanelSession *s2 = nClass != 0 ? s : s;\n"))

# 2. through the comma operator
VARIANTS["comma"] = swap_after_switch(BASE.replace(
    DECL, DECL + "    Ov002PanelSession *s2 = (nColumn, s);\n"))

# 3. through an address-of round trip of a pointer local
VARIANTS["address round trip"] = swap_after_switch(BASE.replace(
    DECL, DECL + "    Ov002PanelSession *s2 = *(Ov002PanelSession **)&s;\n"))

# 4. the second pointer taken from the field the session caches
VARIANTS["through cached field"] = swap_after_switch(BASE.replace(
    DECL, DECL + "    Ov002PanelSession *s2 = (Ov002PanelSession *)"
                 "((u8 *)s + (nColumn - nColumn));\n"))

# 5. no second variable, but the session re-read from the global for the tail
TAIL = BASE.replace(
    "    s->bKind = (u8)nTo;\n    func_ov002_0205b7dc(s->bMode, nTo, 0);",
    "    data_ov002_0207f620->bKind = (u8)nTo;\n"
    "    func_ov002_0205b7dc(data_ov002_0207f620->bMode, nTo, 0);")
VARIANTS["global in tail only"] = TAIL

# 6. the session re-read from the global inside case 5 only
h, t = BASE.split("    case 5: {", 1)
VARIANTS["global in case 5"] = h + "    case 5: {" + t.replace(
    "s->pCachedEntry", "data_ov002_0207f620->pCachedEntry")

print("%-28s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-28s %-6d %-6s %s" % ("base", size, n, sr))
best = (99, None)
for tag, src in sorted(VARIANTS.items()):
    size, n, sr = score(src)
    if size is None:
        print("%-28s FAIL %s" % (tag, sr))
        continue
    mark = ""
    if n == 0:
        mark = "   MATCH"
    elif sr not in ("r4", "?"):
        mark = "   POINTER IN " + sr
    print("%-28s %-6d %-6s %s%s" % (tag, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
