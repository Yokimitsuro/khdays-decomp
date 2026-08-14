"""Loop depth multiplies spill weight in most allocators. A body wrapped in a loop
that exits after one iteration emits straight-line code but carries a loop in the
IR, so the weighting can differ. do-while(0) was tried long ago; the for and while
forms and wrapping the whole body were not.
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
    p = "build/try/b5bff4_lw.c"
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


head, rest = BASE.split("    switch (nClass) {\n", 1)
body, tail = rest.split("    }\n\n    s->bKind = (u8)nTo;", 1)
SW = "    switch (nClass) {\n" + body + "    }\n"
TAIL = "\n    s->bKind = (u8)nTo;" + tail

# the switch's own breaks must keep binding to the switch, so the wrapper only
# encloses the switch and exits right after it
VAR = {
    "do while zero": head + "    do {\n" + SW + "    } while (0);\n" + TAIL,
    "for ever with break": head + "    for (;;) {\n" + SW + "        break;\n    }\n" + TAIL,
    "while one with break": head + "    while (1) {\n" + SW + "        break;\n    }\n" + TAIL,
    "for once": head + "    {\n        int nOnce;\n\n        for (nOnce = 0; nOnce < 1; nOnce++) {\n"
               + SW + "        }\n    }\n" + TAIL,
    "goto loop": head + "Lonce:\n" + SW + "    if (0) {\n        goto Lonce;\n    }\n" + TAIL,
}

print("%-30s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-30s %-6d %-6s s=%s" % ("base", size, n, sr))
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
