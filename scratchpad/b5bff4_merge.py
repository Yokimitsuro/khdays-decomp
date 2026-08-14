"""Registered hypothesis: give case 2's second index and case 3's rebind the same
function-scope variable so the two branch webs fuse into one spanning case 2 to
case 3. If the fused web interferes with nTag, the whole-function set needs five
colours as in the ROM and the session pointer is displaced.
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
    for t in ins[:14]:
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
    return d, ",".join(top)


def report(tag, src):
    p = "build/try/b5bff4_mg.c"
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
    d, top = wmap(code)
    print("%-26s %-5d b=%-4s s=%-4s nClass=%-4s nTag=%-4s top=%s"
          % (tag, len(code), n, d.get("s", "?"), d.get("nClass", "?"),
             d.get("nTag", "?"), top))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
TOP = "    int nColumn;\n    int nTag;\n"
C2 = "        int nNew = nTo + nColumn * 6;\n"
C3 = "        nClass = nTo + nColumn * 6;"
assert TOP in BASE and C2 in BASE and C3 in BASE
print("ROM                        1416  b=0    s=r8   nClass=r4   nTag=r7   "
      "top=r4,r5,r6,r7,r8")
report("mine", BASE)

# A: one function-scope index used by case 2's second index and case 3's rebind
A = BASE.replace(TOP, TOP + "    int nIndex;\n")
A = A.replace(C2, "")
h, t = A.split("    case 2: {", 1)
t = t.replace("nNew", "nIndex")
A = h + "    case 2: {" + t
A = A.replace("        int nOld = nFrom + nColumn * 6;\n",
              "        int nOld = nFrom + nColumn * 6;\n"
              "\n        nIndex = nTo + nColumn * 6;\n", 1)
h, t = A.split("    case 3: {", 1)
t = t.replace("nClass = nTo + nColumn * 6;", "nIndex = nTo + nColumn * 6;")
t = t.replace("(u16)nClass", "(u16)nIndex")
t = t.replace("nTo, nClass, 1, 1, 1", "nTo, nIndex, 1, 1, 1")
t = t.replace("s->bKey = (u8)nClass;", "s->bKey = (u8)nIndex;")
report("c2_c3_share_index", h + "    case 3: {" + t)

# B: the same variable also carries case 1's index
B = (h + "    case 3: {" + t)
B = B.replace("""        int nOffset = nColumn * 6;
        int nIndex;

""", "        int nOffset = nColumn * 6;\n\n")
report("plus_case1", B)

# C: case 2's FIRST index and case 3's first index share instead
C = BASE.replace(TOP, TOP + "    int nOldIndex;\n")
C = C.replace("        int nOld = nFrom + nColumn * 6;\n", "", 1)
h2, t2 = C.split("    case 2: {", 1)
t2 = t2.replace("nOld", "nOldIndex")
C = h2 + "    case 2: {" + t2
C = C.replace("        int nNew = nTo + nColumn * 6;\n",
              "        int nNew = nTo + nColumn * 6;\n"
              "\n        nOldIndex = nFrom + nColumn * 6;\n", 1)
h2, t2 = C.split("    case 3: {", 1)
t2 = t2.replace("        int nOld = nFrom + nColumn * 6;\n", "")
t2 = t2.replace("nOld", "nOldIndex")
report("c2_c3_share_old", h2 + "    case 3: {" + t2)
