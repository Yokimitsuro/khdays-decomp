"""Untouched knob class: GCC function attributes on the callees, accepted because
-gccext,on is in the confirmed flags. Marking a callee const or pure changes what
mwcc believes a call does, which feeds liveness and common-subexpression work and
so can reach the allocator. Also try noreturn on none of them and a few others.
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


def score(src):
    p = "build/try/b5bff4_at.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, "?", str(ex).split("\n")[0][:55]
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
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    return len(code), n, sr, None


TARGETS = {
    "classifier": "extern int func_ov002_0205a3f0(int *pOut, int nCode);",
    "slot lookup": "extern int func_ov002_0205a540(int nKey);",
    "list get": "extern void *func_02010154(void *pList, u16 nIndex);",
    "tag lookup": "extern int func_ov002_0206dc10(int nTag);",
}
ATTRS = ("__attribute__((const))", "__attribute__((pure))")

print("ROM: s=r8   |   base: s=r4, 67 bytes")
print("%-46s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr, err = score(BASE)
print("%-46s %-6d %-6s s=%s" % ("base", size, n, sr))
best = (999, None)
for attr in ATTRS:
    for tname, decl in sorted(TARGETS.items()):
        newdecl = decl[:-1] + " " + attr + ";"
        size, n, sr, err = score(BASE.replace(decl, newdecl))
        tag = "%s on %s" % (attr.split("((")[1].rstrip("))"), tname)
        if err:
            print("%-46s rejected: %s" % (tag, err))
            continue
        mark = "   MATCH" if n == 0 else ("   POINTER IN " + sr if sr not in ("r4", "?") else "")
        print("%-46s %-6d %-6s s=%s%s" % (tag, size, n, sr, mark))
        if isinstance(n, int) and n < best[0]:
            best = (n, tag)
        if n == 0:
            open("build/try/%s.c" % SYM, "w").write(BASE.replace(decl, newdecl))
            print("PROMOTED " + tag)
    # all four at once
    src = BASE
    for decl in TARGETS.values():
        src = src.replace(decl, decl[:-1] + " " + attr + ";")
    size, n, sr, err = score(src)
    tag = "%s on all four" % attr.split("((")[1].rstrip("))")
    if not err:
        print("%-46s %-6d %-6s s=%s" % (tag, size, n, sr))
        if isinstance(n, int) and n < best[0]:
            best = (n, tag)
print()
print("best: %s bytes  %s" % best)
