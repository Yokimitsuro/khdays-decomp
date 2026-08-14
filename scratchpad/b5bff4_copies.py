"""Introduce copies that mwcc coalesces away. A copy of a value used in some
places creates an extra web at the point webs are built, but copy propagation
removes it before code is emitted, so the instructions can stay identical while
the web count and numbering change. That is the only way left to alter the web
structure of the real function without altering its code.
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


def report(tag, src):
    p = "build/try/b5bff4_cp.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-30s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return
    n = "-"
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
    print("%-30s size=%-5d bytes=%-4s s=%s%s"
          % (tag, len(code), n, sr, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


report("base", BASE)

# a copy of the session used only in the tail
S1 = BASE.replace(DECL, DECL + "    Ov002PanelSession *s2 = s;\n")
S1 = S1.replace("    s->bKind = (u8)nTo;\n    func_ov002_0205b7dc(s->bMode, nTo, 0);",
                "    s2->bKind = (u8)nTo;\n    func_ov002_0205b7dc(s2->bMode, nTo, 0);")
report("session copy in tail", S1)

# a copy of the session used inside case 2 only
S2 = BASE.replace(DECL, DECL + "    Ov002PanelSession *s2 = s;\n")
h, t = S2.split("    case 2: {", 1)
body, rest = t.split("    case 3: {", 1)
body = body.replace("s->listItems", "s2->listItems")
report("session copy in case 2", h + "    case 2: {" + body + "    case 3: {" + rest)

# a copy of the classifier result used for the dispatch
S3 = BASE.replace(DECL, DECL + "    int nClass2 = nClass;\n")
S3 = S3.replace("    switch (nClass) {", "    switch (nClass2) {", 1)
report("classifier copy", S3)

# a copy of the second parameter used in the tail
S4 = BASE.replace(DECL, DECL + "    int nTo2 = nTo;\n")
S4 = S4.replace("    s->bKind = (u8)nTo;\n    func_ov002_0205b7dc(s->bMode, nTo, 0);",
                "    s->bKind = (u8)nTo2;\n    func_ov002_0205b7dc(s->bMode, nTo2, 0);")
report("second parameter copy", S4)

# a copy of the first parameter used inside case 2
S5 = BASE.replace(DECL, DECL + "    int nFrom2 = nFrom;\n")
h, t = S5.split("    case 2: {", 1)
body, rest = t.split("    case 3: {", 1)
body = body.replace("nSlot, nFrom, nOld", "nSlot, nFrom2, nOld")
report("first parameter copy", h + "    case 2: {" + body + "    case 3: {" + rest)

# both session and classifier copies
S6 = BASE.replace(DECL, DECL + "    Ov002PanelSession *s2 = s;\n"
                               "    int nClass2 = nClass;\n")
S6 = S6.replace("    switch (nClass) {", "    switch (nClass2) {", 1)
S6 = S6.replace("    s->bKind = (u8)nTo;\n    func_ov002_0205b7dc(s->bMode, nTo, 0);",
                "    s2->bKind = (u8)nTo;\n    func_ov002_0205b7dc(s2->bMode, nTo, 0);")
report("session and classifier", S6)
