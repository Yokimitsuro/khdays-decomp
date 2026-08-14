"""The copy tests only ran in one orientation (s2 assigned from s). Try the
reverse and longer chains: the loaded variable first and the used one assigned
from it, and two- and three-link chains. Propagation should fold them all, but
the orientation determines WHICH name survives, and the surviving name's position
in the declaration list is what feeds web creation.
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
    p = "build/try/b5bff4_ch.c"
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


VAR = {
    "reverse one link": """    int nColumn;
    int nTag;
    Ov002PanelSession *s0 = data_ov002_0207f620;
    Ov002PanelSession *s = s0;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "reverse two links": """    int nColumn;
    int nTag;
    Ov002PanelSession *s0 = data_ov002_0207f620;
    Ov002PanelSession *s1 = s0;
    Ov002PanelSession *s = s1;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "chain before scalars": """    Ov002PanelSession *s0 = data_ov002_0207f620;
    Ov002PanelSession *s = s0;
    int nColumn;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "classifier then chain": """    int nColumn;
    int nTag;
    Ov002PanelSession *s0 = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s0->bMode);
    Ov002PanelSession *s = s0;
""",
    "chain used only after": """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
    s = s;
""",
}

print("%-28s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-28s %-6d %-6s s=%s" % ("base", size, n, sr))
best = (99, None)
for tag, decl in sorted(VAR.items()):
    size, n, sr = score(BASE.replace(DECL, decl))
    if size is None:
        print("%-28s FAIL %s" % (tag, sr))
        continue
    mark = "   MATCH" if n == 0 else ("   POINTER IN " + sr if sr not in ("r4", "?") else "")
    print("%-28s %-6d %-6s s=%s%s" % (tag, size, n, sr, mark))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(BASE.replace(DECL, decl))
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
