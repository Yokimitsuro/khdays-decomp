"""Exhaustive grid on the real function over every size-preserving lever found so
far, scored by differing bytes. Each knob is a source rewrite that emits the same
instructions; the combination is what has never been searched jointly.
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

DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
C2_NEWOLD = """        int nNew = nTo + nColumn * 6;
        int nOld = nFrom + nColumn * 6;
"""
C2_OLDNEW = """        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
"""
C1_SEP = """        int nOffset = nColumn * 6;
        int nIndex;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nIndex = nColumn * 6 + nTo;
        func_ov002_0205afb4(nIndex, nTo, 1, func_ov002_0205a600(nIndex), 1);
        s->bIndex = (u8)nIndex;
"""
C1_SHARE = """        int nOffset = nColumn * 6;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nClass = nColumn * 6 + nTo;
        func_ov002_0205afb4(nClass, nTo, 1, func_ov002_0205a600(nClass), 1);
        s->bIndex = (u8)nClass;
"""
assert DECL in BASE and C2_NEWOLD in BASE and C1_SEP in BASE


def k_decl(src, v):
    opts = [DECL,
            """    Ov002PanelSession *s = data_ov002_0207f620;
    int nColumn;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
            """    int nColumn;
    int nTag;
    int nClass;
    Ov002PanelSession *s = data_ov002_0207f620;

    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""]
    return src.replace(DECL, opts[v])


def k_c2(src, v):
    return src if v == 0 else src.replace(C2_NEWOLD, C2_OLDNEW)


def k_c1(src, v):
    return src if v == 0 else src.replace(C1_SEP, C1_SHARE)


def k_c3(src, v):
    """case 3 rebinds nClass, or uses its own variable."""
    if v == 0:
        return src
    head, tail = src.split("    case 3: {", 1)
    body, rest = tail.split("    case 4:", 1)
    body = body.replace("        int nSlot;\n",
                        "        int nSlot;\n        int nNewKey;\n")
    body = body.replace("nClass = nTo + nColumn * 6;", "nNewKey = nTo + nColumn * 6;")
    body = body.replace("(u16)nClass", "(u16)nNewKey")
    body = body.replace("nTo, nClass, 1, 1, 1", "nTo, nNewKey, 1, 1, 1")
    body = body.replace("s->bKey = (u8)nClass;", "s->bKey = (u8)nNewKey;")
    return head + "    case 3: {" + body + "    case 4:" + rest


def k_tag(src, v):
    """nTag at function scope, or local to case 3."""
    if v == 0:
        return src
    s = src.replace("    int nColumn;\n    int nTag;\n", "    int nColumn;\n")
    s = s.replace("    Ov002PanelSession *s = data_ov002_0207f620;\n    int nColumn;\n    int nTag;\n",
                  "    Ov002PanelSession *s = data_ov002_0207f620;\n    int nColumn;\n")
    head, tail = s.split("    case 3: {", 1)
    tail = tail.replace("        int nSlot;\n", "        int nSlot;\n        int nTag;\n", 1)
    return head + "    case 3: {" + tail


def k_c2decl(src, v):
    """order of case 2's flag and slot declarations."""
    if v == 0:
        return src
    return src.replace("        int bFlag;\n        int nSlot;\n",
                       "        int nSlot;\n        int bFlag;\n")


KNOBS = [("decl", k_decl, 3), ("c2", k_c2, 2), ("c1", k_c1, 2),
         ("c3", k_c3, 2), ("tag", k_tag, 2), ("c2d", k_c2decl, 2)]

best = (10 ** 9, None, None)
results = {}
n = 0
for combo in itertools.product(*[range(k[2]) for k in KNOBS]):
    src = BASE
    for (name, fn, _), v in zip(KNOBS, combo):
        src = fn(src, v)
    p = "build/try/b5bff4_g2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception:
        continue
    n += 1
    if len(code) != len(ORIG):
        continue
    a = bytearray(ORIG)
    b = bytearray(code)
    for off in set(OREL) | set(mrel):
        for kk in range(4):
            if off + kk < len(a):
                a[off + kk] = 0
                b[off + kk] = 0
    d = sum(1 for i in range(len(a)) if a[i] != b[i])
    tag = " ".join("%s=%d" % (k[0], v) for k, v in zip(KNOBS, combo))
    results[tag] = d
    if d < best[0]:
        best = (d, tag, src)
        print("new best %d bytes: %s" % (d, tag))
    if d == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("MATCH " + tag)
        break

print()
print("compiled %d, distinct byte counts: %s"
      % (n, sorted(set(results.values()))))
print("best: %d bytes  %s" % (best[0], best[1]))
if best[2]:
    open("build/try/b5bff4_grid_best.c", "w").write(best[2])
