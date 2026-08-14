"""Untried axis: the order of the extern declarations. mwcc numbers its
internal symbols in declaration order, and that numbering can leak into how
virtual registers are ranked.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0205bff4"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/func_ov002_0205bff4.c").read()

head, body = BASE.split("void func_ov002_0205bff4(", 1)
body = "void func_ov002_0205bff4(" + body

# split the head into the struct part and the extern part
i = head.index("extern Ov002PanelSession")
pre, externs = head[:i], head[i:]
lines = [l for l in externs.strip().split("\n") if l.strip()]
# join continuation lines
decls = []
cur = ""
for l in lines:
    cur = (cur + " " + l.strip()).strip() if cur else l
    if cur.rstrip().endswith(";"):
        decls.append(cur)
        cur = ""
assert not cur


def score(tag, order):
    s = pre + "\n".join(order) + "\n\n" + body
    p = "build/try/b5bff4_e.c"
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


print("%d extern declarations" % len(decls))
score("as_is", decls)
score("reversed", list(reversed(decls)))
score("sorted", sorted(decls))
# data declaration last
data = [d for d in decls if d.startswith("extern Ov002PanelSession")]
rest = [d for d in decls if not d.startswith("extern Ov002PanelSession")]
score("data_last", rest + data)
