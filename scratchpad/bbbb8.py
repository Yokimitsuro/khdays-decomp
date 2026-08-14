"""func_ov002_0206bbb8 case 7: the ROM emits two separate blocks each with its
own epilogue where the candidate predicates, and it builds the slot address two
different ways - base root+0x8b6e indexed by the slot for the read-modify-write,
base root+slot*2 with a displacement for the re-test.
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

OLD = """    case 7:
        *(short *)(root + 0x8b6e + nSlot * 2) =
            (short)(*(short *)(root + 0x8b6e + nSlot * 2) + nValue);
        if (*(short *)(root + 0x8b6e + nSlot * 2) == 0) {
            *(u16 *)(root + 0x8b6a) &= ~(1 << (nSlot + 3));
        } else {
            *(u16 *)(root + 0x8b6a) |= 1 << (nSlot + 3);
        }
        return;
"""
assert OLD in BASE

RMW = {
    "idxed": "        ((short *)(root + 0x8b6e))[nSlot] =\n"
             "            (short)(((short *)(root + 0x8b6e))[nSlot] + nValue);\n",
    "flat": "        *(short *)(root + 0x8b6e + nSlot * 2) =\n"
            "            (short)(*(short *)(root + 0x8b6e + nSlot * 2)"
            " + nValue);\n",
}
TEST = {
    "disp": "*(short *)(root + nSlot * 2 + 0x8b6e)",
    "idxed": "((short *)(root + 0x8b6e))[nSlot]",
}
SHAPE = {
    "tworet": "        if (%s == 0) {\n"
              "            *(u16 *)(root + 0x8b6a) &= ~(1 << (nSlot + 3));\n"
              "            return;\n"
              "        }\n"
              "        *(u16 *)(root + 0x8b6a) |= 1 << (nSlot + 3);\n"
              "        return;\n",
    "tworet_inv": "        if (%s != 0) {\n"
                  "            *(u16 *)(root + 0x8b6a) |= 1 << (nSlot + 3);\n"
                  "            return;\n"
                  "        }\n"
                  "        *(u16 *)(root + 0x8b6a) &= ~(1 << (nSlot + 3));\n"
                  "        return;\n",
    "ifelse": "        if (%s == 0) {\n"
              "            *(u16 *)(root + 0x8b6a) &= ~(1 << (nSlot + 3));\n"
              "        } else {\n"
              "            *(u16 *)(root + 0x8b6a) |= 1 << (nSlot + 3);\n"
              "        }\n        return;\n",
}

best = [999, None]
for rk, tk, sk in itertools.product(RMW, TEST, SHAPE):
    body = "    case 7:\n" + RMW[rk] + (SHAPE[sk] % TEST[tk])
    s = BASE.replace(OLD, body)
    p = "build/try/bbbb8_sweep.c"
    open(p, "w").write(s)
    tag = "%s/%s/%s" % (rk, tk, sk)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-26s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-26s SIZE %d (%+d)" % (tag, len(mine), len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-26s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
print("best %s bytes %s" % (best[1], best[0]))
