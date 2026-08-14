"""Extending the class past the switch flips the pair the ROM's way but costs
code. Look for shapes that extend its live range without adding instructions:
assigning it in every case, or making it the value each case carries.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
BASE = open("scratchpad/repro.c").read()


def probe(tag, src):
    p = "scratchpad/repro_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ses = cls = "?"
    for t in ins[:14]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r2\]$", t)
        if m and ses == "?":
            ses = m.group(1)
        m = re.match(r"mov (r[0-9]+|sb|sl|fp), r0$", t)
        if m and cls == "?" and ses != "?":
            cls = m.group(1)
    print("%-24s size=%-4d session=%-4s class=%-4s%s"
          % (tag, len(code), ses, cls,
             "   FLIPPED" if ses != "?" and cls != "?"
             and int(re.sub(r"\D", "", ses.replace("sb", "9")
                            .replace("sl", "10")) or 0)
             > int(re.sub(r"\D", "", cls.replace("sb", "9")
                          .replace("sl", "10")) or 0) else ""))


probe("base", BASE)

# the class assigned in case 0 as well
s = BASE.replace("""        case 0:
            call3(s->bIndex, s->bKind, 0);
            break;""",
                 """        case 0:
            nClass = s->bIndex;
            call3(nClass, s->bKind, 0);
            break;""")
probe("class_in_case0", s)

# the class assigned in case 2 as well
s = BASE.replace("""        int nOld = nFrom + nColumn * 6;

        nTag = 0;""",
                 """        int nOld = nFrom + nColumn * 6;

        nClass = nOld;
        nTag = 0;""")
probe("class_in_case2", s)

# the class carries the tag in case 2
s = BASE.replace("""        nTag = 0;
        if (nOld != 0) {
            nTag = call0();
        }
        call4(nOld, nTag, 1, 0);""",
                 """        nClass = 0;
        if (nOld != 0) {
            nClass = call0();
        }
        call4(nOld, nClass, 1, 0);""")
probe("class_is_tag", s)

# the class assigned in every case
s = BASE.replace("""        case 0:
            call3(s->bIndex, s->bKind, 0);
            break;""",
                 """        case 0:
            nClass = s->bIndex;
            call3(nClass, s->bKind, 0);
            break;""")
s = s.replace("""        nTag = 0;
        if (nOld != 0) {
            nTag = call0();
        }
        call4(nOld, nTag, 1, 0);""",
              """        nClass = 0;
        if (nOld != 0) {
            nClass = call0();
        }
        call4(nOld, nClass, 1, 0);""")
probe("class_everywhere", s)

# the session read once into a second variable used only in the tail
s = BASE.replace("    s->bKind = (u8)nTo;\n    tail(s->bMode, nTo, 0);",
                 "    s->bKind = (u8)nTo;\n    tail(s->bMode, nTo, 0);")
probe("noop", s)
