"""Exactly three webs rotate between the two builds: the session pointer, the
classifier result and case 2's second index. The first two are pinned by the
prologue, but case 2's index is free to be written several ways that all emit
the same instructions. Sweep those.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}


def sess(code):
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            return m.group(1)
    return "?"


def report(tag, src):
    p = "build/try/b5bff4_c2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:60]))
        return
    n = "-"
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-24s size=%-5d bytes=%-4s s=%s%s"
          % (tag, len(code), n, sess(code), "   <== ROM" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
OLDNEW = """        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
"""
assert OLDNEW in BASE
report("base", BASE)

# the two indices declared the other way round
report("new_before_old", BASE.replace(OLDNEW, """        int nNew = nTo + nColumn * 6;
        int nOld = nFrom + nColumn * 6;
"""))

# declared without initialisers, assigned in each order
report("assign_old_new", BASE.replace(OLDNEW, """        int nOld;
        int nNew;

        nOld = nFrom + nColumn * 6;
        nNew = nTo + nColumn * 6;
"""))
report("assign_new_old", BASE.replace(OLDNEW, """        int nOld;
        int nNew;

        nNew = nTo + nColumn * 6;
        nOld = nFrom + nColumn * 6;
"""))

# the second index computed only where it is used, so its web starts later
LATE = BASE.replace(OLDNEW, "        int nOld = nFrom + nColumn * 6;\n        int nNew;\n")
LATE = LATE.replace("        pEntry = (u16 *)func_02010154(s->listItems, (u16)nNew);",
                    "        nNew = nTo + nColumn * 6;\n"
                    "        pEntry = (u16 *)func_02010154(s->listItems, (u16)nNew);")
report("new_computed_late", LATE)

# the indices declared at the top of the function instead of inside the case
TOP = BASE.replace("""    int nColumn;
    int nTag;
""", """    int nColumn;
    int nTag;
    int nOld;
    int nNew;
""")
TOP = TOP.replace(OLDNEW, """        nOld = nFrom + nColumn * 6;
        nNew = nTo + nColumn * 6;
""")
report("indices_at_top", TOP)

TOP2 = BASE.replace("""    int nColumn;
    int nTag;
""", """    int nColumn;
    int nTag;
    int nNew;
    int nOld;
""")
TOP2 = TOP2.replace(OLDNEW, """        nOld = nFrom + nColumn * 6;
        nNew = nTo + nColumn * 6;
""")
report("indices_at_top_rev", TOP2)

# case 3 uses the same pair of names, so the two cases share the webs
C3 = TOP.replace("""        int nOld = nFrom + nColumn * 6;
        u16 *pEntry;
        int nSlot;

        nClass = nTo + nColumn * 6;
""", """        u16 *pEntry;
        int nSlot;

        nOld = nFrom + nColumn * 6;
        nClass = nTo + nColumn * 6;
""")
report("case3_shares_names", C3)
