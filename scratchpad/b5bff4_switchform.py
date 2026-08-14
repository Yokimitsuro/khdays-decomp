"""Switch-form variants. The colouring is first-free-colour, so only the ORDER in
which webs are coloured matters, and that order is set when the front end walks
the statements. The shape of the switch itself -- an explicit default, whether
the empty case is written out, the order of the case labels -- is the one part
of that walk not yet varied, and none of it changes the emitted code.
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
    p = "build/try/b5bff4_sf.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
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
    print("%-26s %-5d b=%-4s s=%s%s"
          % (tag, len(code), n, sess(code), "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
report("mine", BASE)

# an explicit empty default at the end of the outer switch
report("default_last", BASE.replace("""    case 4:
        break;
    }
""", """    case 4:
        break;
    default:
        break;
    }
"""))

# default in place of the empty case 4
report("default_for_4", BASE.replace("""    case 4:
        break;
""", """    default:
        break;
"""))

# the empty case dropped entirely
report("no_case4", BASE.replace("""    case 4:
        break;

""", ""))

# an explicit default on each inner switch of case 0
report("inner_defaults", BASE.replace("""        case 2: {
            int nValue;
""", """        default: {
            int nValue;
""", 1))

# the outer switch given a redundant cast, which changes the walk of the
# controlling expression without changing the dispatch
report("switch_cast", BASE.replace("    switch (nClass) {",
                                   "    switch ((int)nClass) {", 1))
