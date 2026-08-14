"""Bisect properly: empty out one case body at a time from the exemplar and see
which removal makes its context pointer drop from r9 to a low register.
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
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ctx = "?"
    for t in ins[:12]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r[0-9]+\]$", t)
        if m and ctx == "?":
            ctx = m.group(1)
    n = len(set(re.findall(r"\b(r[4-9]|r1[01]|sb|sl|fp)\b",
                           ins[0] if ins else "")))
    print("%-24s size=%-5d ctx=%-4s saved=%d" % (tag, len(code), ctx, n))


probe("exemplar", SRC)

lines = SRC.split("\n")
# locate the top-level case labels inside the outer switch
idx = [i for i, l in enumerate(lines)
       if re.match(r"^    case [0-9]+:$", l) or l == "    default:"]
print("top level case labels at lines:", idx)

for k, start in enumerate(idx):
    end = idx[k + 1] if k + 1 < len(idx) else None
    if end is None:
        continue
    # keep the label, empty the body
    body = lines[start + 1:end]
    if all(re.match(r"^    case [0-9]+:$", b) for b in body):
        continue
    new = lines[:start + 1] + ["        break;"] + lines[end:]
    probe("empty body after L%d" % start, "\n".join(new))
