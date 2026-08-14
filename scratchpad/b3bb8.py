"""func_ov002_02053bb8: mwcc predicates the one-instruction zero arm where the
ROM branches over the call block and lets the zero fall through to the shared
exit. Vary how that inner choice is written.
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
    "nested": "    } else {\n"
              "        if (nItemId == 0x18) {\n"
              "            nResult = G2S_GetBG0ScrPtr();\n"
              "        } else {\n"
              "            nResult = 0;\n"
              "        }\n    }\n",
    "ternary": "    } else {\n"
               "        nResult = (nItemId == 0x18) ? G2S_GetBG0ScrPtr() : 0;\n"
               "    }\n",
    "inverted": "    } else if (nItemId != 0x18) {\n"
                "        nResult = 0;\n"
                "    } else {\n"
                "        nResult = G2S_GetBG0ScrPtr();\n"
                "    }\n",
    "preset": "    } else {\n"
              "        nResult = 0;\n"
              "        if (nItemId == 0x18) {\n"
              "            nResult = G2S_GetBG0ScrPtr();\n"
              "        }\n    }\n",
    "early": "    } else if (nItemId == 0x18) {\n"
             "        return G2S_GetBG0ScrPtr();\n"
             "    } else {\n"
             "        nResult = 0;\n"
             "    }\n",
    "early2": "    } else {\n"
              "        if (nItemId != 0x18) {\n"
              "            return 0;\n"
              "        }\n"
              "        nResult = G2S_GetBG0ScrPtr();\n"
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
        print("%-12s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-12s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-12s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
