"""Full web map including nTag and case 3's rebind, which the earlier probes
missed. ROM: nFrom=r6 nTo=r5 s=r8 nClass=r4 nTag=r7 c3key=r4 -- five distinct
top-level registers and NO split of nClass. Mine splits nClass, so its dispatch
value shares r7 with nTag and only four registers are needed.
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
    for n, t in enumerate(ins):
        if n < 14:
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
    # case 3: the rebind is the second `add rX, r5, r2`; nTag is the `mov rX, #0`
    # that immediately follows the case-3 list call.
    adds = [m.group(1) for m in
            (re.match(r"^add (r\w+), r5, r2$", t) for t in ins) if m]
    d["c3key"] = adds[1] if len(adds) > 1 else "?"
    for n, t in enumerate(ins):
        if n > 205 and re.match(r"^mov (r\w+), #0$", t):
            d["nTag"] = re.match(r"^mov (r\w+), #0$", t).group(1)
            break
    keys = ("nFrom", "nTo", "s", "nClass", "nTag", "c3key")
    top = sorted(set(d.get(k, "?") for k in ("nFrom", "nTo", "s", "nClass", "nTag")))
    return (" ".join("%s=%s" % (k, d.get(k, "?")) for k in keys),
            ",".join(top))


def report(tag, src):
    p = "build/try/b5bff4_m2.c"
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
    w, top = wmap(code)
    print("%-24s %-5d b=%-4s %s | top=%s" % (tag, len(code), n, w, top))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


rw, rtop = wmap(ORIG)
print("%-24s %-5d b=%-4s %s | top=%s" % ("ROM", len(ORIG), 0, rw, rtop))
BASE = open("build/try/%s.c" % SYM).read()
report("mine", BASE)

# case 3 with its own variable instead of rebinding nClass
head, tail = BASE.split("    case 3: {", 1)
body, rest = tail.split("    case 4:", 1)
b2 = body.replace("        int nSlot;\n", "        int nSlot;\n        int nNewKey;\n")
b2 = b2.replace("nClass = nTo + nColumn * 6;", "nNewKey = nTo + nColumn * 6;")
b2 = b2.replace("(u16)nClass", "(u16)nNewKey")
b2 = b2.replace("nTo, nClass, 1, 1, 1", "nTo, nNewKey, 1, 1, 1")
b2 = b2.replace("s->bKey = (u8)nClass;", "s->bKey = (u8)nNewKey;")
report("case3_own_var", head + "    case 3: {" + b2 + "    case 4:" + rest)

# nTag scoped to case 3 rather than the function
s3 = BASE.replace("    int nColumn;\n    int nTag;\n", "    int nColumn;\n")
h3, t3 = s3.split("    case 3: {", 1)
t3 = t3.replace("        int nSlot;\n", "        int nSlot;\n        int nTag;\n", 1)
report("nTag_in_case3", h3 + "    case 3: {" + t3)

# both
s4 = head + "    case 3: {" + b2 + "    case 4:" + rest
s4 = s4.replace("    int nColumn;\n    int nTag;\n", "    int nColumn;\n")
h4, t4 = s4.split("    case 3: {", 1)
t4 = t4.replace("        int nSlot;\n", "        int nSlot;\n        int nTag;\n", 1)
report("both", h4 + "    case 3: {" + t4)
