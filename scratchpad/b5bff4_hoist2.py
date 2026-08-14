"""Hoisting only case 3's tag moved 74 to 73, so the coalescing group responds
to which locals live longer. Sweep the subsets: tag, then tag plus the entry
pointer, then plus the slot, then the same for case 2.
"""
import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0205bff4"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
# Start from the version with nothing hoisted.
BASE = open("build/try/b5bff4_offset_last.c").read()

HEAD = """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert HEAD in BASE

C2 = """        u16 *pEntry;
        int bFlag;
        int nSlot;

"""
C3 = """        u16 *pEntry;
        int nTag;
        int nSlot;

"""
assert C2 in BASE and C3 in BASE


def build(hoist):
    s = BASE
    decls = ""
    c2_keep = []
    c3_keep = []
    if "tag" in hoist:
        decls += "    int nTag;\n"
    else:
        c3_keep.append("        int nTag;\n")
    if "entry3" in hoist:
        decls += "    u16 *pEntry3;\n"
    if "slot3" in hoist:
        decls += "    int nSlot3;\n"
    if "entry2" in hoist:
        decls += "    u16 *pEntry2;\n"
    if "slot2" in hoist:
        decls += "    int nSlot2;\n"
    if "flag2" in hoist:
        decls += "    int bFlag;\n"

    # case 3 block
    c3 = ""
    if "entry3" not in hoist:
        c3 += "        u16 *pEntry;\n"
    c3 += "".join(c3_keep)
    if "slot3" not in hoist:
        c3 += "        int nSlot;\n"
    c3 = c3 + "\n" if c3 else ""
    # case 2 block
    c2 = ""
    if "entry2" not in hoist:
        c2 += "        u16 *pEntry;\n"
    if "flag2" not in hoist:
        c2 += "        int bFlag;\n"
    if "slot2" not in hoist:
        c2 += "        int nSlot;\n"
    c2 = c2 + "\n" if c2 else ""

    s = s.replace(C2, c2).replace(C3, c3)
    s = s.replace(HEAD, HEAD.replace("    int nColumn;\n",
                                     "    int nColumn;\n" + decls))
    # rename the hoisted ones so the two cases do not clash
    parts = s.split("    case 3: {")
    if "entry3" in hoist:
        parts[1] = parts[1].replace("pEntry", "pEntry3")
    if "slot3" in hoist:
        parts[1] = parts[1].replace("nSlot", "nSlot3")
    s = "    case 3: {".join(parts)
    parts = s.split("    case 2: {")
    tail = parts[1].split("    case 3: {")
    if "entry2" in hoist:
        tail[0] = tail[0].replace("pEntry", "pEntry2")
    if "slot2" in hoist:
        tail[0] = tail[0].replace("nSlot", "nSlot2")
    parts[1] = "    case 3: {".join(tail)
    s = "    case 2: {".join(parts)
    return s


def score(tag, s):
    p = "build/try/b5bff4_h.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-30s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return 9999
    if len(mine) != len(orig):
        print("%-30s SIZE %+d" % (tag, len(mine) - len(orig)))
        return 9999
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-30s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
    return n


NAMES = ["tag", "entry3", "slot3", "entry2", "slot2", "flag2"]
best = [9999, None]
for r in range(0, 4):
    for combo in itertools.combinations(NAMES, r):
        n = score(",".join(combo) or "(none)", build(set(combo)))
        if n < best[0]:
            best[0] = n
            best[1] = combo
        if n == 0:
            raise SystemExit
print("best %s bytes %s" % (best[1], best[0]))
