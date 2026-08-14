"""Never tried: switch on the classifier CALL directly, so its result is an
anonymous compiler temporary instead of a named source variable. It still needs a
callee-saved register because three calls sit between it and the dispatch, but a
temporary and a named variable are different objects at web-construction time,
which is where the residue lives.
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
    p = "build/try/b5bff4_an.c"
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
    sr = kr = "?"
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    for t in ins[:14]:
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and sr == "?":
            sr = m.group(1)
    for t in ins:
        m = re.match(r"^cmp (r\w+), #5$", t)
        if m:
            kr = m.group(1)
            break
    return len(code), n, "s=%s k=%s" % (sr, kr)


# case 3 with its own variable, since nClass no longer exists
def own_case3(src):
    head, tail = src.split("    case 3: {", 1)
    body, rest = tail.split("    case 4:", 1)
    body = body.replace("        int nSlot;\n",
                        "        int nSlot;\n        int nNewKey;\n")
    body = body.replace("nClass = nTo + nColumn * 6;", "nNewKey = nTo + nColumn * 6;")
    body = body.replace("(u16)nClass", "(u16)nNewKey")
    body = body.replace("nTo, nClass, 1, 1, 1", "nTo, nNewKey, 1, 1, 1")
    body = body.replace("s->bKey = (u8)nClass;", "s->bKey = (u8)nNewKey;")
    return head + "    case 3: {" + body + "    case 4:" + rest


print("ROM: s=r8 k=r4   |   base: s=r4 k=r7")
size, n, m = score(BASE)
print("%-34s %-6d %-6s %s" % ("base", size, n, m))

# 1. anonymous: switch directly on the call
V1 = own_case3(BASE).replace(DECL, """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
""")
V1 = V1.replace("    switch (nClass) {",
                "    switch (func_ov002_0205a3f0(&nColumn, s->bMode)) {", 1)
# the classifier call must still happen before the two preceding statements, so
# keep the original order by moving those after it is impossible; instead place
# the call where it was and switch on a second call is wrong. Use a comma form.
size, n, m = score(V1)
print("%-34s %-6s %-6s %s" % ("anonymous switch (moved)", size, n, m))

# 2. the call kept in place, its value carried to the switch by the comma
#    operator so no named variable exists
V2 = own_case3(BASE).replace(DECL, """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClassTmp;
""")
V2 = V2.replace("    if (func_ov002_0205374c(",
                "    nClassTmp = func_ov002_0205a3f0(&nColumn, s->bMode);\n"
                "    if (func_ov002_0205374c(", 1)
V2 = V2.replace("    switch (nClass) {", "    switch (nClassTmp) {", 1)
size, n, m = score(V2)
print("%-34s %-6s %-6s %s" % ("separate temp name", size, n, m))

# 3. the classifier result stored through a one-element array, so it is not a
#    plain scalar variable
V3 = own_case3(BASE).replace(DECL, """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int aClass[1];
""")
V3 = V3.replace("    if (func_ov002_0205374c(",
                "    aClass[0] = func_ov002_0205a3f0(&nColumn, s->bMode);\n"
                "    if (func_ov002_0205374c(", 1)
V3 = V3.replace("    switch (nClass) {", "    switch (aClass[0]) {", 1)
size, n, m = score(V3)
print("%-34s %-6s %-6s %s" % ("through a one-element array", size, n, m))
