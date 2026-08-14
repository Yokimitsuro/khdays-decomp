"""Clean full sweep of which cases reuse nClass as their scratch variable. The
ROM keeps nClass's web unsplit, and its register r4 also carries case 1's index,
case 2's first index and case 5's flag. Earlier attempts covered only some
subsets and one had a substitution bug, so run all sixteen properly and report
the register map as well as the byte count.
"""
import sys
import os
import json
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

C1_OLD = """        int nOffset = nColumn * 6;
        int nIndex;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nIndex = nColumn * 6 + nTo;
        func_ov002_0205afb4(nIndex, nTo, 1, func_ov002_0205a600(nIndex), 1);
        s->bIndex = (u8)nIndex;
"""
C1_NEW = """        int nOffset = nColumn * 6;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nClass = nColumn * 6 + nTo;
        func_ov002_0205afb4(nClass, nTo, 1, func_ov002_0205a600(nClass), 1);
        s->bIndex = (u8)nClass;
"""
assert C1_OLD in BASE


def c2(src, on):
    if not on:
        return src
    head, tail = src.split("    case 2: {", 1)
    body, rest = tail.split("    case 3: {", 1)
    body = body.replace("        int nOld = nFrom + nColumn * 6;\n", "")
    body = body.replace("nOld", "nClass")
    body = body.replace("        int nNew = nTo + nColumn * 6;\n",
                        "        int nNew = nTo + nColumn * 6;\n"
                        "\n        nClass = nFrom + nColumn * 6;\n")
    return head + "    case 2: {" + body + "    case 3: {" + rest


def c3(src, on):
    """on keeps the ROM behaviour (nClass rebound); off gives case 3 its own."""
    if on:
        return src
    head, tail = src.split("    case 3: {", 1)
    body, rest = tail.split("    case 4:", 1)
    body = body.replace("        int nSlot;\n",
                        "        int nSlot;\n        int nNewKey;\n")
    body = body.replace("nClass = nTo + nColumn * 6;", "nNewKey = nTo + nColumn * 6;")
    body = body.replace("(u16)nClass", "(u16)nNewKey")
    body = body.replace("nTo, nClass, 1, 1, 1", "nTo, nNewKey, 1, 1, 1")
    body = body.replace("s->bKey = (u8)nClass;", "s->bKey = (u8)nNewKey;")
    return head + "    case 3: {" + body + "    case 4:" + rest


def c5(src, on):
    if not on:
        return src
    head, tail = src.split("    case 5: {", 1)
    tail = tail.replace("        int bFlag = 0;\n", "", 1)
    tail = tail.replace("u16 nKey = *(u16 *)s->pCachedEntry;",
                        "u16 nKey = *(u16 *)s->pCachedEntry;\n\n        nClass = 0;", 1)
    tail = tail.replace("bFlag = 1;", "nClass = 1;")
    tail = tail.replace("bFlag != 0 ?", "nClass != 0 ?")
    return head + "    case 5: {" + tail


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
    return "s=%-4s nClass=%-4s" % (d.get("s", "?"), d.get("nClass", "?"))


best = (99, None)
print("ROM: s=r8   nClass=r4")
for a, b, c, e in itertools.product((0, 1), repeat=4):
    src = BASE
    if a:
        src = src.replace(C1_OLD, C1_NEW)
    src = c2(src, b)
    src = c3(src, c)
    src = c5(src, e)
    p = "build/try/b5bff4_ru.c"
    open(p, "w").write(src)
    tag = "c1=%d c2=%d c3=%d c5=%d" % (a, b, c, e)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        continue
    n = "-"
    if len(code) == len(ORIG):
        x = bytearray(ORIG)
        y = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(x):
                    x[off + k] = 0
                    y[off + k] = 0
        n = sum(1 for i in range(len(x)) if x[i] != y[i])
    print("%-24s size=%-5d bytes=%-4s %s%s"
          % (tag, len(code), n, wmap(code), "   MATCH" if n == 0 else ""))
    if isinstance(n, int) and n < best[0]:
        best = (n, tag)
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
