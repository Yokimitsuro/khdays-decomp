"""Registered hypothesis: put the WHOLE switch in a static inline helper that
takes the session as its FIRST parameter. With -inline on,noauto mwcc expands
it, and an inlined function's parameters are created at expansion time, that is
AFTER the outer function's locals. That is the only construction that would
order the session pointer last, which is what the ROM shows (s coloured last,
on r8). The earlier inline test only factored a small slot-lookup helper.
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
    p = "build/try/b5bff4_bi2.c"
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
    d, top = wmap(code)
    print("%-24s %-5d b=%-4s s=%-4s nClass=%-4s nTag=%-4s top=%s"
          % (tag, len(code), n, d.get("s", "?"), d.get("nClass", "?"),
             d.get("nTag", "?"), top))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/%s.c" % SYM).read()
print("ROM                      1416  b=0    s=r8   nClass=r4   nTag=r7   "
      "top=r4,r5,r6,r7,r8")
report("mine", BASE)

head, rest = BASE.split("void func_ov002_0205bff4(int nFrom, int nTo) {\n", 1)
decls, body = rest.split("    switch (nClass) {\n", 1)
sw, tail = body.split("    }\n\n    s->bKind = (u8)nTo;", 1)
tailrest = tail.split("\n", 1)[1]

SIGS = {
    # session first, then the two parameters, then the classifier outputs
    "s_first": "Ov002PanelSession *s, int nFrom, int nTo, int nClass, int nColumn",
    # session last, to check the ordering claim in the other direction
    "s_last": "int nFrom, int nTo, int nClass, int nColumn, Ov002PanelSession *s",
}
for tag, sig in sorted(SIGS.items()):
    args = ("s, nFrom, nTo, nClass, nColumn" if tag == "s_first"
            else "nFrom, nTo, nClass, nColumn, s")
    helper = ("static inline void Ov002_PanelRepaintSlots(%s) {\n"
              "    int nTag;\n\n"
              "    switch (nClass) {\n%s    }\n}\n\n" % (sig, sw))
    outer = ("void func_ov002_0205bff4(int nFrom, int nTo) {\n"
             "    int nColumn;\n"
             "    Ov002PanelSession *s = data_ov002_0207f620;\n"
             "    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);\n"
             "\n"
             "    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {\n"
             "        func_ov002_020535f0(func_ov002_02053558(0x79));\n"
             "    }\n"
             "    func_ov002_0205b7dc(s->bMode, nTo, 0);\n"
             "    Ov002_PanelRepaintSlots(%s);\n\n"
             "    s->bKind = (u8)nTo;\n%s" % (args, tailrest))
    report(tag, head + helper + outer)
