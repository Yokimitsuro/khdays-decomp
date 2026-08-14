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

CASES = {
    "c0": """    case 0:
        if ((to < 0x1b || to >= 0x2e) && to >= 0) {
            result = 5;
        }
        if (to == 0x11 || to == 0x12 || to == 0x1a || to == 0xc) {
            result = 0;
        }
        break;
""",
    "c1": """    case 1:
        result = (to == 3) ? 10 : 5;
        break;
""",
    "c3": """    case 3:
        if (to != 2 && to != 6 && to != 5) {
            result = 5;
        }
        break;
""",
    "c14": """    case 14:
        result = 3;
        break;
""",
    "c15": """    case 15:
        result = 10;
        break;
""",
    "cjt": """    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
        result = 5;
        break;
""",
}

TAIL = """
    if (from >= 0x2e || to >= 0x2e) {
        switch (ctx) {
        case 0:
            if (from == 4) {
                result = 5;
            }
            break;
        case 1:
            break;
        case 2:
            if (to == 3) {
                result = 5;
            }
            break;
        case 3:
            break;
        case 4:
            if (from == 0x2f && to == 0x30) {
                result = 8;
            }
            break;
        case 13:
            if (from == 0x2f && to == 0x32) {
                result = 5;
            }
            if (from == 0x32 && to == 0x32) {
                result = 5;
            }
            break;
        case 0x13:
            if (from == 0x30 && to == 0x2f) {
                result = 5;
            }
            break;
        }
    }
    return result;
}
"""


def score(tag, order):
    s = ("int func_ov002_020519b0(int from, int to, int ctx) {\n"
         "    int result = 0;\n\n"
         "    if (from == to) {\n        return 0;\n    }\n\n"
         "    switch (from) {\n"
         + "".join(CASES[c] for c in order)
         + "    }\n" + TAIL)
    p = "build/try/b19b0_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL" % tag)
        return 99
    if len(mine) != len(orig):
        print("%-26s SIZE %d" % (tag, len(mine)))
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


# the ROM lays the bodies out as 3, 1, 14, jump-table, 0
score("rom_order", ["c3", "c1", "c14", "cjt", "c0", "c15"])
score("rom_order_15mid", ["c3", "c1", "c14", "c15", "cjt", "c0"])
score("rom_order_15first", ["c15", "c3", "c1", "c14", "cjt", "c0"])
score("src_order", ["c0", "c1", "c3", "c14", "c15", "cjt"])
score("rev_order", ["cjt", "c15", "c14", "c3", "c1", "c0"])
