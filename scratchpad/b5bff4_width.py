"""Switch operand width: the ROM's range check is unsigned (cmp then addls), so
try the class as unsigned, and as a narrow copy, since the operand width changes
how mwcc materialises the index and therefore when it creates that register.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0205bff4"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/func_ov002_0205bff4.c").read()

HEAD = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert HEAD in BASE


def score(tag, head, extra=None):
    s = BASE.replace(HEAD, head)
    if extra:
        s = s.replace("    switch (nClass) {", extra)
    p = "build/try/b5bff4_w.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-22s FAIL" % tag)
        return 9999
    if len(mine) != len(orig):
        print("%-22s SIZE %+d" % (tag, len(mine) - len(orig)))
        return 9999
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-22s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
    return n


BASEHEAD = ("    int nColumn;\n    int nTag;\n"
            "    Ov002PanelSession *s = data_ov002_0207f620;\n")

score("unsigned_class",
      BASEHEAD + "    unsigned int nClass = func_ov002_0205a3f0("
                 "&nColumn, s->bMode);\n")
score("u8_class",
      BASEHEAD + "    u8 nClass = (u8)func_ov002_0205a3f0("
                 "&nColumn, s->bMode);\n")
score("u16_class",
      BASEHEAD + "    u16 nClass = (u16)func_ov002_0205a3f0("
                 "&nColumn, s->bMode);\n")
score("classifier_unsigned",
      BASEHEAD + "    unsigned int nClass;\n\n"
                 "    nClass = (unsigned int)func_ov002_0205a3f0("
                 "&nColumn, s->bMode);\n")
