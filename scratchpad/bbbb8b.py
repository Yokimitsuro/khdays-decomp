"""One instruction apart: the ROM schedules the stack adjust into the load-use
slot between the flags load and the or, in case 1 only. Cases 2 and 3 already
match, so vary case 1's loop and tail spelling.
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

OLD = """    case 1: {
        int i = 0;

        do {
            char *pEntry = session + i;

            if (pEntry[0xb9] == -1) {
                pEntry[0xb9] = (char)nIndex;
                break;
            }
            i++;
        } while (i < 5);
        *(u16 *)(root + 0x8b6a) |= 4;
        return;
    }
"""
assert OLD in BASE

LOOPS = {
    "do": "        int i = 0;\n\n"
          "        do {\n"
          "            char *pEntry = session + i;\n\n"
          "            if (pEntry[0xb9] == -1) {\n"
          "                pEntry[0xb9] = (char)nIndex;\n"
          "                break;\n"
          "            }\n"
          "            i++;\n"
          "        } while (i < 5);\n",
    "for": "        int i;\n\n"
           "        for (i = 0; i < 5; i++) {\n"
           "            char *pEntry = session + i;\n\n"
           "            if (pEntry[0xb9] == -1) {\n"
           "                pEntry[0xb9] = (char)nIndex;\n"
           "                break;\n"
           "            }\n"
           "        }\n",
    "do_decl": "        int i;\n\n        i = 0;\n"
               "        do {\n"
               "            char *pEntry = session + i;\n\n"
               "            if (pEntry[0xb9] == -1) {\n"
               "                pEntry[0xb9] = (char)nIndex;\n"
               "                break;\n"
               "            }\n"
               "            i++;\n"
               "        } while (i < 5);\n",
}
TAILS = {
    "compound": "        *(u16 *)(root + 0x8b6a) |= 4;\n        return;\n",
    "explicit": "        *(u16 *)(root + 0x8b6a) =\n"
                "            (u16)(*(u16 *)(root + 0x8b6a) | 4);\n"
                "        return;\n",
    "plainor": "        *(u16 *)(root + 0x8b6a) = *(u16 *)(root + 0x8b6a) | 4;\n"
               "        return;\n",
}

best = [999, None]
for lk, tk in itertools.product(LOOPS, TAILS):
    body = "    case 1: {\n" + LOOPS[lk] + TAILS[tk] + "    }\n"
    s = BASE.replace(OLD, body)
    p = "build/try/bbbb8_sweep2.c"
    open(p, "w").write(s)
    tag = "%s/%s" % (lk, tk)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-22s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-22s SIZE %d (%+d)" % (tag, len(mine), len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-22s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
print("best %s bytes %s" % (best[1], best[0]))
