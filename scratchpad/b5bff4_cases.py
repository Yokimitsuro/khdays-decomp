"""The case bodies are laid out in source order and case 4 is empty, so where
its label sits changes the order mwcc processes the cases in without changing
the emitted layout. Try moving it and dropping it.
"""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0205bff4"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/func_ov002_0205bff4.c").read()

CASE4 = """    case 4:
        break;

    case 5: {
"""
assert CASE4 in BASE


def score(tag, s):
    p = "build/try/b5bff4_c.c"
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception:
        print("%-22s FAIL" % tag)
        return 9999
    if len(mine) != len(orig):
        print("%-22s SIZE %+d" % (tag, len(mine) - len(orig)))
        return 9999
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-22s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)
    return n


# drop the empty case entirely
score("no_case4", BASE.replace(CASE4, "    case 5: {\n"))

# case 4 grouped with a default at the end
s2 = BASE.replace(CASE4, "    case 5: {\n")
s2 = s2.replace("""        break;
    }
    }

    s->bKind = (u8)nTo;""", """        break;
    }
    case 4:
    default:
        break;
    }

    s->bKind = (u8)nTo;""")
score("case4_last", s2)

# explicit default only
s3 = BASE.replace(CASE4, "    case 5: {\n")
s3 = s3.replace("""        break;
    }
    }

    s->bKind = (u8)nTo;""", """        break;
    }
    default:
        break;
    }

    s->bKind = (u8)nTo;""")
score("default_last", s3)

# default first
s4 = BASE.replace("    switch (nClass) {\n    case 0:",
                  "    switch (nClass) {\n    default:\n        break;\n\n"
                  "    case 0:")
score("default_first", s4)
