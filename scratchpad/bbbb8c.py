"""Two scheduling residues left: case 7's add has its operands the other way
round, and case 1's stack adjust does not get hoisted into the load-use slot.
Sweep both spellings together.
"""
import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0206bbb8"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

RMW_OLD = """        *(short *)(root + 0x8b6e + nSlot * 2) =
            (short)(nValue + *(short *)(root + 0x8b6e + nSlot * 2));
"""
assert RMW_OLD in BASE

RMWS = {
    "value_first": RMW_OLD,
    "load_first": "        *(short *)(root + 0x8b6e + nSlot * 2) =\n"
                  "            (short)(*(short *)(root + 0x8b6e + nSlot * 2)"
                  " + nValue);\n",
    "plus_equals": "        *(short *)(root + 0x8b6e + nSlot * 2) +=\n"
                   "            (short)nValue;\n",
    "local": "        {\n"
             "            short nCur = *(short *)(root + 0x8b6e + nSlot * 2);\n\n"
             "            *(short *)(root + 0x8b6e + nSlot * 2) =\n"
             "                (short)(nCur + nValue);\n"
             "        }\n",
    "shortval": "        *(short *)(root + 0x8b6e + nSlot * 2) =\n"
                "            (short)(*(short *)(root + 0x8b6e + nSlot * 2)"
                " + (short)nValue);\n",
}

TAIL_OLD = """        *(u16 *)(root + 0x8b6a) |= 4;
        return;
    }
    case 0:
"""
assert TAIL_OLD in BASE

TAILS = {
    "compound": TAIL_OLD,
    "ptr": "        {\n"
           "            u16 *pFlags = (u16 *)(root + 0x8b6a);\n\n"
           "            *pFlags |= 4;\n"
           "        }\n        return;\n    }\n    case 0:\n",
    "readmod": "        {\n"
               "            u16 nFlags = *(u16 *)(root + 0x8b6a);\n\n"
               "            *(u16 *)(root + 0x8b6a) = (u16)(nFlags | 4);\n"
               "        }\n        return;\n    }\n    case 0:\n",
    "orderswap": "        *(u16 *)(root + 0x8b6a) =\n"
                 "            (u16)(4 | *(u16 *)(root + 0x8b6a));\n"
                 "        return;\n    }\n    case 0:\n",
}

best = [999, None]
for rk, tk in itertools.product(RMWS, TAILS):
    s = BASE.replace(RMW_OLD, RMWS[rk]).replace(TAIL_OLD, TAILS[tk])
    p = "build/try/bbbb8_sweep3.c"
    open(p, "w").write(s)
    tag = "%s/%s" % (rk, tk)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-26s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-26s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    if n < best[0]:
        best[0] = n
        best[1] = tag
        print("%-26s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
