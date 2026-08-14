"""Force nClass's def-use chain to reach into case 3 so the web is not split,
which is what the ROM shows (its case-3 rebind sits in nClass's own register).
The multiply-by-zero and or-with-zero forms fold away to the same instructions
but make the rebind READ the dispatch value, which is what prevents a split.
Diagnostic first: if any of these produces five distinct top-level registers and
moves the session pointer, the mechanism is confirmed and a natural source form
can then be looked for.
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


def wmap(code):
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    d = {}
    for n, t in enumerate(ins[:14]):
        m = re.match(r"^ldr (r\w+), \[r2\]$", t)
        if m and "s" not in d:
            d["s"] = m.group(1)
        m = re.match(r"^mov (r\w+), r0$", t)
        if m:
            if "nFrom" not in d:
                d["nFrom"] = m.group(1)
            elif "nClass" not in d:
                d["nClass"] = m.group(1)
        m = re.match(r"^mov (r\w+), r1$", t)
        if m and "nTo" not in d:
            d["nTo"] = m.group(1)
    for n, t in enumerate(ins):
        if n > 205:
            m = re.match(r"^mov (r\w+), #0$", t)
            if m:
                d["nTag"] = m.group(1)
                break
    top = sorted(set(d.get(k, "?") for k in
                     ("nFrom", "nTo", "s", "nClass", "nTag")))
    return d, top


def report(tag, src):
    p = "build/try/b5bff4_sp2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
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
    d, top = wmap(code)
    print("%-24s %-5d b=%-4s s=%-4s nClass=%-4s nTag=%-4s top=%s"
          % (tag, len(code), n, d.get("s", "?"), d.get("nClass", "?"),
             d.get("nTag", "?"), ",".join(top)))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
OLD = "        nClass = nTo + nColumn * 6;"
assert OLD in BASE
print("ROM                      1416  b=0    s=r8   nClass=r4   nTag=r7   top=r4,r5,r6,r7,r8")
report("mine", BASE)
for tag, expr in (
        ("mul_zero", "        nClass = nClass * 0 + nTo + nColumn * 6;"),
        ("and_zero", "        nClass = (nClass & 0) + nTo + nColumn * 6;"),
        ("sub_self", "        nClass = nClass - nClass + nTo + nColumn * 6;"),
        ("or_zero", "        nClass = (nClass | 0) * 0 + nTo + nColumn * 6;")):
    report(tag, BASE.replace(OLD, expr))
