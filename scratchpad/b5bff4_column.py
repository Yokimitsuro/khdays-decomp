"""nColumn is the one object never varied: it is address-taken, which pins it to
the stack and makes it a different kind of web from the register locals. Vary how
its address reaches the classifier and how it is declared.
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
    p = "build/try/b5bff4_cl.c"
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


VARIANTS = {
    "pointer variable": """    int nColumn;
    int *pColumn = &nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(pColumn, s->bMode);
""",
    "one element array": """    int aColumn[1];
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(aColumn, s->bMode);
""",
    "array indexed uses": """    int aColumn[1];
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&aColumn[0], s->bMode);
""",
    "declared last": """    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nColumn;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "initialised": """    int nColumn = 0;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "struct wrapper": """    struct { int n; } sColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&sColumn.n, s->bMode);
""",
}

print("ROM: s=r8   |   base: s=r4, 67 bytes")
size, n, sr = score(BASE)
print("%-26s %-6d %-6s s=%s" % ("base", size, n, sr))
best = (99, None)
for tag, decl in sorted(VARIANTS.items()):
    src = BASE.replace(DECL, decl)
    if "aColumn" in decl:
        src = re.sub(r"\bnColumn\b", "aColumn[0]", src)
        src = src.replace("func_ov002_0205a3f0(aColumn[0]",
                          "func_ov002_0205a3f0(aColumn")
        src = src.replace("&aColumn[0][0]", "&aColumn[0]")
        src = src.replace("int aColumn[0][1];", "int aColumn[1];")
    if "sColumn" in decl:
        src = re.sub(r"\bnColumn\b", "sColumn.n", src)
        src = src.replace("&sColumn.n, s->bMode", "&sColumn.n, s->bMode")
    size, n, sr = score(src)
    if size is None:
        print("%-26s FAIL %s" % (tag, sr))
        continue
    mark = "   MATCH" if n == 0 else ("   POINTER IN " + sr if sr not in ("r4", "?") else "")
    print("%-26s %-6d %-6s s=%s%s" % (tag, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
