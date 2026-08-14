"""Never tried: hold the session as an INTEGER rather than a pointer and cast at
each use. Pointer type variations were swept (void, u8, typedef, const) but never
a non-pointer type. The casts are free, so the emitted code should be identical,
but an integer web and a pointer web are different objects to the allocator.
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
OLD = "    Ov002PanelSession *s = data_ov002_0207f620;"
assert OLD in BASE


def score(src):
    p = "build/try/b5bff4_ai.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:50]
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


def as_int(kind):
    """s held as an integer of the given type; every s-> becomes a cast."""
    src = BASE.replace(OLD, "    %s s = (%s)data_ov002_0207f620;" % (kind, kind))
    return re.sub(r"\bs->", "((Ov002PanelSession *)s)->", src)


print("%-28s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-28s %-6d %-6s s=%s" % ("base (pointer)", size, n, sr))
best = (99, None)
for kind in ("int", "unsigned int", "long", "unsigned long"):
    size, n, sr = score(as_int(kind))
    if size is None:
        print("%-28s FAIL %s" % (kind, sr))
        continue
    mark = "   MATCH" if n == 0 else ("   POINTER IN " + sr if sr not in ("r4", "?") else "")
    print("%-28s %-6d %-6s s=%s%s" % ("held as " + kind, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, kind)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(as_int(kind))
        print("PROMOTED held as " + kind)

# and a union of pointer and integer, so the object has both natures
UNI = BASE.replace(OLD, "    union { Ov002PanelSession *p; int n; } u;\n"
                        "    u.p = data_ov002_0207f620;")
UNI = re.sub(r"\bs->", "u.p->", UNI)
size, n, sr = score(UNI)
print("%-28s %-6s %-6s s=%s" % ("held in a union", size, n, sr))
print()
print("best: %s bytes  %s" % best)
