import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_020519b0"]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}

HEAD = open("build/try/b19b0_g_both_in.c").read().split("        switch (ctx) {")[0]

CASES = {
    "c0": "        case 0:\n            if (from == 4) {\n                result = 5;\n            }\n            break;\n",
    "c1": "        case 1:\n            break;\n",
    "c2": "        case 2:\n            if (to == 3) {\n                result = 5;\n            }\n            break;\n",
    "c3": "        case 3:\n            break;\n",
    "c4": "        case 4:\n            if (from == 0x2f && to == 0x30) {\n                result = 8;\n            }\n            break;\n",
    "c13": "        case 13:\n            if (from == 0x2f && to == 0x32) {\n                result = 5;\n            }\n            if (from == 0x32 && to == 0x32) {\n                result = 5;\n            }\n            break;\n",
    "c19": "        case 0x13:\n            if (from == 0x30 && to == 0x2f) {\n                result = 5;\n            }\n            break;\n",
    "def": "        default:\n            break;\n",
}


def score(tag, order):
    body = "        switch (ctx) {\n" + "".join(CASES[c] for c in order) + "        }\n"
    s = HEAD + body + "    }\n    return result;\n}\n"
    p = "build/try/b19b0_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-26s FAIL" % tag)
        return 99
    if len(mine) != len(orig):
        print("%-26s SIZE %d (%+d)" % (tag, len(mine), len(mine) - len(orig)))
        return 99
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-26s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    if nd == 0:
        open("build/try/func_ov002_020519b0.c", "w").write(s)
        print("PROMOTED")
    return nd


LOW = ["c0", "c1", "c2", "c3", "c4"]
score("m_default_end", LOW + ["c13", "c19", "def"])
score("n_default_first", ["def"] + LOW + ["c13", "c19"])
score("o_high_first", ["c13", "c19"] + LOW)
score("p_high_first_def", ["c13", "c19"] + LOW + ["def"])
score("q_19_before_13", LOW + ["c19", "c13"])
score("r_interleaved", ["c0", "c13", "c1", "c2", "c19", "c3", "c4"])
