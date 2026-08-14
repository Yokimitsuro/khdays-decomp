"""The class coalesces with the case scratch group, so whichever case opens
that group decides the register. Vary how case 0's two arms declare theirs.
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
BASE = open("build/try/%s.c" % SYM).read()


def score(tag, s):
    p = "build/try/b5bff4_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-16s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    if len(mine) != len(orig):
        print("%-16s SIZE %+d" % (tag, len(mine) - len(orig)))
        return
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-16s bytes=%d%s" % (tag, n, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED " + tag)


ARM1 = """        case 1: {
            int nValue = func_ov002_0205a638();

            func_ov002_0205aba4(4, 0, 0, 0);
            func_ov002_0205ae08(nFrom + 2, nValue, 0);
            break;
        }
"""
ARM2 = """        case 2: {
            int nValue;
            void *pObject = NNS_FndGetNextListObject(s->listItems, 0);

            if (pObject == 0) {
                pObject = NNS_FndGetNextListObject(s->listEntries, 0);
            }
            if (pObject != 0 && func_ov002_0205a7b8() != 0) {
                nValue = 1;
            } else {
                nValue = 0;
            }
"""
assert ARM1 in BASE and ARM2 in BASE

# one shared scratch declared at the outer case scope
s1 = BASE.replace("    case 0:\n        switch (nFrom) {",
                  "    case 0: {\n        int nValue;\n\n        switch (nFrom) {")
s1 = s1.replace(ARM1, """        case 1:
            nValue = func_ov002_0205a638();
            func_ov002_0205aba4(4, 0, 0, 0);
            func_ov002_0205ae08(nFrom + 2, nValue, 0);
            break;
""")
s1 = s1.replace(ARM2, """        case 2: {
            void *pObject = NNS_FndGetNextListObject(s->listItems, 0);

            if (pObject == 0) {
                pObject = NNS_FndGetNextListObject(s->listEntries, 0);
            }
            if (pObject != 0 && func_ov002_0205a7b8() != 0) {
                nValue = 1;
            } else {
                nValue = 0;
            }
""")
s1 = s1.replace("""        case 2:
            func_ov002_0205ae08(4, 1, 1);
            break;
        }
        break;
""", """        case 2:
            func_ov002_0205ae08(4, 1, 1);
            break;
        }
        break;
    }
""")
score("shared_scratch", s1)

# the object reused as the value, no separate int
s2 = BASE.replace(ARM2, """        case 2: {
            int nValue;
            void *pObject;

            pObject = NNS_FndGetNextListObject(s->listItems, 0);
            if (pObject == 0) {
                pObject = NNS_FndGetNextListObject(s->listEntries, 0);
            }
            if (pObject != 0 && func_ov002_0205a7b8() != 0) {
                nValue = 1;
            } else {
                nValue = 0;
            }
""")
score("obj_split", s2)
