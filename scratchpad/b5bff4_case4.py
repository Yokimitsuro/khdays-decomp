"""The empty case 4 emits no body, so its position in the source is free: the
jump table is ordered by value and the bodies are laid out in source order, so
moving an empty case cannot change the emitted layout. But it does change the
order in which the front end walks the cases, which is where web numbering comes
from. Never tested.
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
C4 = "    case 4:\n        break;\n\n"
assert C4 in BASE


def score(src):
    p = "build/try/b5bff4_c4.c"
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


print("%-30s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-30s %-6d %-6s s=%s" % ("base (case 4 in place)", size, n, sr))

stripped = BASE.replace(C4, "")
VAR = {}
# case 4 moved to the very end of the switch
VAR["case 4 last"] = stripped.replace(
    "    }\n\n    s->bKind = (u8)nTo;", C4 + "    }\n\n    s->bKind = (u8)nTo;")
# case 4 moved to the front
VAR["case 4 first"] = stripped.replace(
    "    switch (nClass) {\n", "    switch (nClass) {\n" + C4)
# case 4 dropped entirely
VAR["case 4 removed"] = stripped
# case 4 folded onto the switch's default
VAR["case 4 as default"] = stripped.replace(
    "    }\n\n    s->bKind = (u8)nTo;",
    "    default:\n        break;\n    }\n\n    s->bKind = (u8)nTo;")
# case 4 placed between cases 1 and 2
VAR["case 4 before case 2"] = stripped.replace("    case 2: {", C4 + "    case 2: {", 1)
# case 4 placed between cases 2 and 3
VAR["case 4 before case 3"] = stripped.replace("    case 3: {", C4 + "    case 3: {", 1)

best = (99, None)
for tag, src in sorted(VAR.items()):
    size, n, sr = score(src)
    if size is None:
        print("%-30s FAIL %s" % (tag, sr))
        continue
    mark = "   MATCH" if n == 0 else ("   POINTER IN " + sr if sr not in ("r4", "?") else "")
    print("%-30s %-6d %-6s s=%s%s" % (tag, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
