"""Bisect the matched exemplar func_ov000_02050ec4, whose context pointer lands
in r9, by simplifying it toward the shape of func_ov002_0205bff4 until the
context drops to r4. Whatever step causes the drop is the mechanism.
"""
import sys
import os
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SRC = open("src/overlays/ov000/calls/func_ov000_02050ec4.c").read()


def probe(tag, src):
    p = "scratchpad/bisect_t.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ctx = "?"
    for t in ins[:12]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r[0-9]+\]$", t)
        if m and ctx == "?":
            ctx = m.group(1)
    print("%-26s size=%-5d ctx=%-4s push=%s"
          % (tag, len(code), ctx, ins[0][5:] if ins else "?"))


probe("exemplar", SRC)

# find the function body
head, body = SRC.split("void func_ov000_02050ec4(void)\n{\n", 1)
body = body.rstrip()
assert body.endswith("}")
inner = body[:-1]

# cut the switch cases progressively: keep only the first N case labels
cases = re.split(r"\n    case ", inner)
print("\n%d case chunks" % (len(cases) - 1))
for keep in (1, 2, 3, 4, len(cases) - 1):
    if keep >= len(cases):
        continue
    kept = cases[0] + "".join("\n    case " + c for c in cases[1:keep + 1])
    # close the switch and the function
    txt = kept.rstrip()
    if not txt.rstrip().endswith("}"):
        txt += "\n    }\n"
    src = head + "void func_ov000_02050ec4(void)\n{\n" + txt + "\n}\n"
    probe("keep %d cases" % keep, src)
