"""The zero arm is a single instruction, so mwcc predicates it in every if/else
spelling. The ROM branches over the call block and lets the zero fall through,
which needs a construct mwcc does not predicate.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_02053bb8"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

OLD = """    } else if (nItemId == 0x18) {
        nResult = G2S_GetBG0ScrPtr();
    } else {
        nResult = 0;
    }
"""
assert OLD in BASE

VARIANTS = {
    "switch": "    } else {\n"
              "        switch (nItemId) {\n"
              "        case 0x18:\n"
              "            nResult = G2S_GetBG0ScrPtr();\n"
              "            break;\n"
              "        default:\n"
              "            nResult = 0;\n"
              "            break;\n"
              "        }\n    }\n",
    "goto": "    } else {\n"
            "        if (nItemId != 0x18) {\n"
            "            goto zero;\n"
            "        }\n"
            "        nResult = G2S_GetBG0ScrPtr();\n"
            "        goto done;\n"
            "    zero:\n"
            "        nResult = 0;\n"
            "    done:\n"
            "        ;\n    }\n",
    "dowhile": "    } else {\n"
               "        do {\n"
               "            if (nItemId == 0x18) {\n"
               "                nResult = G2S_GetBG0ScrPtr();\n"
               "                break;\n"
               "            }\n"
               "            nResult = 0;\n"
               "        } while (0);\n    }\n",
    "switch_noelse": "    } else switch (nItemId) {\n"
                     "    case 0x18:\n"
                     "        nResult = G2S_GetBG0ScrPtr();\n"
                     "        break;\n"
                     "    default:\n"
                     "        nResult = 0;\n"
                     "        break;\n"
                     "    }\n",
}

best = [999, None]
for tag, v in VARIANTS.items():
    s = BASE.replace(OLD, v)
    p = "build/try/b3bb8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-16s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-16s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-16s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
