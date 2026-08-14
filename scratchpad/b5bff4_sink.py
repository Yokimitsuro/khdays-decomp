"""If the source initialises nTag BEFORE the switch and mwcc sinks the store into
case 3 -- the only place nTag is used -- the emitted code is unchanged, but at
the point the webs are built nTag is live across the dispatch and therefore
interferes with nClass. That forces five colours for the whole-function set,
which is exactly what the ROM has and my build lacks.
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
    p = "build/try/b5bff4_sk.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-28s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
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
    print("%-28s %-5d b=%-4s s=%-4s nClass=%-4s nTag=%-4s top=%s"
          % (tag, len(code), n, d.get("s", "?"), d.get("nClass", "?"),
             d.get("nTag", "?"), top))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
print("ROM                          1416  b=0    s=r8   nClass=r4   nTag=r7   "
      "top=r4,r5,r6,r7,r8")
report("mine", BASE)

# 1. nTag zeroed before the switch, the store left to be sunk into case 3
S1 = BASE.replace("        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);\n"
                  "        nTag = 0;\n",
                  "        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);\n")
S1 = S1.replace("    func_ov002_0205b7dc(s->bMode, nTo, 0);\n\n    switch (nClass) {",
                "    func_ov002_0205b7dc(s->bMode, nTo, 0);\n"
                "    nTag = 0;\n\n    switch (nClass) {")
report("nTag_zero_before_switch", S1)

# 2. nTag given an initialiser at its declaration
S2 = BASE.replace("        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);\n"
                  "        nTag = 0;\n",
                  "        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nOld);\n")
S2 = S2.replace("    int nColumn;\n    int nTag;\n",
                "    int nColumn;\n    int nTag = 0;\n")
report("nTag_init_at_decl", S2)

# 3. nTag zeroed before the switch AND kept zeroed in case 3, to see the cost
S3 = BASE.replace("    func_ov002_0205b7dc(s->bMode, nTo, 0);\n\n    switch (nClass) {",
                  "    func_ov002_0205b7dc(s->bMode, nTo, 0);\n"
                  "    nTag = 0;\n\n    switch (nClass) {")
report("nTag_zero_both", S3)
