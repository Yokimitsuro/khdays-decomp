"""A second pointer web puts the first pointer in r8, but the two-load form costs
8 bytes. Try deriving the second web from the first at offset zero, which emits
no code: address-of the first field, a byte pointer cast back, and similar. The
plain copies were folded by propagation; a derived address may survive as its own
web while still costing nothing.
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

FORMS = {
    "address of first field":
        "    Ov002PanelSession *s2 = (Ov002PanelSession *)&s->bKind;\n",
    "byte pointer round trip":
        "    u8 *pBase = (u8 *)s;\n"
        "    Ov002PanelSession *s2 = (Ov002PanelSession *)pBase;\n",
    "array decay":
        "    Ov002PanelSession *s2 = (Ov002PanelSession *)(s->listItems - 0x480);\n",
    "difference of two":
        "    Ov002PanelSession *s2 = (Ov002PanelSession *)((u8 *)s + 0);\n",
    "second global read late":
        "    Ov002PanelSession *s2;\n",
}


def score(src):
    p = "build/try/b5bff4_dv.c"
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


print("%-30s %-6s %-6s %s" % ("form", "size", "bytes", "s"))
best = (99, None)
for fname, decl in sorted(FORMS.items()):
    src = BASE.replace(DECL, DECL + decl)
    if fname == "second global read late":
        src = src.replace("    func_ov002_0205b7dc(s->bMode, nTo, 0);\n\n    switch",
                          "    s2 = data_ov002_0207f620;\n"
                          "    func_ov002_0205b7dc(s->bMode, nTo, 0);\n\n    switch", 1)
    head, tail = src.split("    switch (nClass) {", 1)
    src = head + "    switch (nClass) {" + tail.replace("s->", "s2->")
    size, n, sr = score(src)
    if size is None:
        print("%-30s FAIL %s" % (fname, sr))
        continue
    mark = ""
    if n == 0:
        mark = "   MATCH"
    elif sr not in ("r4", "?"):
        mark = "   POINTER IN " + sr
    print("%-30s %-6d %-6s %s%s" % (fname, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, fname)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + fname)
print()
print("best: %s bytes  %s" % best)
