"""The remaining residue is which tail the jump table's case 6 and default
entries point at, which follows from whether the stack adjust is hoisted in
case 1. Vary the arrangement of the trailing labels and the shared tail.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0206bbb8"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

OLD = """    case 0:
    case 4:
    case 5:
        break;
    case 6:
        return;
    default:
        return;
    }

    {
        Ov002Request req;

        req.nKind = (u8)nKind;
        req.nIndex = (u8)nIndex;
        req.nValue = nValue;
        func_ov002_0206c2a0(&req);
    }
}
"""
assert OLD in BASE

TAIL = """    {
        Ov002Request req;

        req.nKind = (u8)nKind;
        req.nIndex = (u8)nIndex;
        req.nValue = nValue;
        func_ov002_0206c2a0(&req);
    }
}
"""

VARIANTS = {
    "six_then_default": "    case 0:\n    case 4:\n    case 5:\n        break;\n"
                        "    case 6:\n        return;\n"
                        "    default:\n        return;\n    }\n\n" + TAIL,
    "six_with_default": "    case 0:\n    case 4:\n    case 5:\n        break;\n"
                        "    case 6:\n    default:\n        return;\n    }\n\n"
                        + TAIL,
    "default_only": "    case 0:\n    case 4:\n    case 5:\n        break;\n"
                    "    default:\n        return;\n    }\n\n" + TAIL,
    "default_first": "    default:\n        return;\n"
                     "    case 6:\n        return;\n"
                     "    case 0:\n    case 4:\n    case 5:\n        break;\n"
                     "    }\n\n" + TAIL,
    "break_default": "    case 0:\n    case 4:\n    case 5:\n"
                     "        break;\n"
                     "    case 6:\n        return;\n"
                     "    default:\n        break;\n    }\n\n"
                     "    if (nKind != 0 && nKind != 4 && nKind != 5) {\n"
                     "        return;\n    }\n" + TAIL,
}

best = [999, None]
for tag, v in VARIANTS.items():
    s = BASE.replace(OLD, v)
    p = "build/try/bbbb8_sweep5.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-20s FAIL" % tag)
        continue
    if len(mine) != len(orig):
        print("%-20s SIZE %+d" % (tag, len(mine) - len(orig)))
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-20s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n < best[0]:
        best[0] = n
        best[1] = tag
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
        break
print("best %s bytes %s" % (best[1], best[0]))
