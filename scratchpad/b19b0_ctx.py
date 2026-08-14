import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_020519b0"]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}

HEAD = """int func_ov002_020519b0(int from, int to, int ctx) {
    int result = 0;

    if (from == to) {
        return 0;
    }

    switch (from) {
    case 0:
        if ((to < 0x1b || to >= 0x2e) && to >= 0) {
            result = 5;
        }
        if (to == 0x11 || to == 0x12 || to == 0x1a || to == 0xc) {
            result = 0;
        }
        break;
    case 1:
        result = (to == 3) ? 10 : 5;
        break;
    case 3:
        if (to != 2 && to != 6 && to != 5) {
            result = 5;
        }
        break;
    case 14:
        result = 3;
        break;
    case 15:
        result = 10;
        break;
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
        result = 5;
        break;
    }

    if (from >= 0x2e || to >= 0x2e) {
"""

TAIL = """    }
    return result;
}
"""

C0 = """            if (from == 4) {
                result = 5;
            }
            break;
"""
C2 = """            if (to == 3) {
                result = 5;
            }
            break;
"""
C4 = """            if (from == 0x2f && to == 0x30) {
                result = 8;
            }
            break;
"""
C13 = """            if (from == 0x2f && to == 0x32) {
                result = 5;
            }
            if (from == 0x32 && to == 0x32) {
                result = 5;
            }
            break;
"""
C19 = """            if (from == 0x30 && to == 0x2f) {
                result = 5;
            }
            break;
"""


def score(tag, body):
    s = HEAD + body + TAIL
    p = "build/try/b19b0_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL" % tag)
        return 99
    if len(mine) != len(orig):
        print("%-24s SIZE %d" % (tag, len(mine)))
        return 99
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-24s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    if nd == 0:
        open("build/try/func_ov002_020519b0.c", "w").write(s)
        print("PROMOTED")
    return nd


# no empty cases at all
score("a_noempty",
      "        switch (ctx) {\n        case 0:\n" + C0
      + "        case 2:\n" + C2 + "        case 4:\n" + C4
      + "        case 13:\n" + C13 + "        case 0x13:\n" + C19
      + "        }\n")

# empty cases present, as before
score("b_withempty",
      "        switch (ctx) {\n        case 0:\n" + C0
      + "        case 1:\n            break;\n"
      + "        case 2:\n" + C2
      + "        case 3:\n            break;\n"
      + "        case 4:\n" + C4
      + "        case 13:\n" + C13 + "        case 0x13:\n" + C19
      + "        }\n")

# the low group as a switch, 13 and 0x13 split out as if statements after it
score("c_split13",
      "        switch (ctx) {\n        case 0:\n" + C0
      + "        case 1:\n            break;\n"
      + "        case 2:\n" + C2
      + "        case 3:\n            break;\n"
      + "        case 4:\n" + C4
      + "        }\n"
      "        if (ctx == 13) {\n" + C13.replace("            break;\n", "")
      + "        }\n"
      "        if (ctx == 0x13) {\n" + C19.replace("            break;\n", "")
      + "        }\n")

# empty cases padded all the way to 12 so the table is forced dense low only
score("d_pad",
      "        switch (ctx) {\n        case 0:\n" + C0
      + "        case 1:\n        case 2:\n" + C2
      + "        case 3:\n        case 4:\n" + C4
      + "        case 13:\n" + C13 + "        case 0x13:\n" + C19
      + "        }\n")
