"""Translation-unit context is the first axis in many turns that changes the real
function's output: one preceding function took the residue from 67 to 66, three
took it to 65. Sweep the number and shape of preceding functions properly.
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
BASE = open("build/try/%s.c" % SYM).read()
SIG = "void func_ov002_0205bff4(int nFrom, int nTo) {"


def mkfn(i, kind):
    """kind 0 trivial, 1 one pointer local, 2 heavy with seven registers."""
    if kind == 0:
        return "static void ov002_f%d(void) {\n}\n\n" % i
    if kind == 1:
        return ("static void ov002_f%d(int a) {\n"
                "    Ov002PanelSession *p = data_ov002_0207f620;\n\n"
                "    func_ov002_02053cd4(p->bMode + a);\n}\n\n" % i)
    return ("static void ov002_f%d(int a, int b) {\n"
            "    Ov002PanelSession *p = data_ov002_0207f620;\n"
            "    int c = func_ov002_0205a3f0(&a, p->bMode);\n"
            "    int d;\n\n"
            "    switch (c) {\n"
            "    case 0:\n"
            "        func_ov002_0205ae08(p->wField0014, p->nField000c, 0);\n"
            "        break;\n"
            "    case 1: {\n"
            "        int e = a + b * 6;\n"
            "        int f = b + b * 6;\n\n"
            "        func_ov002_0205b0dc(p->listItems, e, a, f, 1, 0, 0, 0);\n"
            "        func_ov002_0205b0dc(p->listItems, f, b, e, 1, 1, 0, 0);\n"
            "        break;\n    }\n"
            "    case 2:\n"
            "        d = func_ov002_0206dc10(b);\n"
            "        func_ov002_0205b0dc(p->listEntries, d, a, b, 1, 1, 1, d);\n"
            "        break;\n    }\n"
            "    p->bKind = (u8)b;\n}\n\n" % i)


def score(src):
    p = "build/try/b5bff4_ts2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:45]
    n = None
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    sr = "?"
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    return len(code), n, sr


best = (99, None)
print("%-40s %-6s %-6s %s" % ("preceding functions", "size", "bytes", "s"))
for kind in (0, 1, 2):
    for count in (0, 1, 2, 3, 4, 6, 8):
        pre = "".join(mkfn(i, kind) for i in range(count))
        size, n, sr = score(BASE.replace(SIG, pre + SIG))
        tag = "kind=%d count=%d" % (kind, count)
        if size is None:
            print("%-40s FAIL %s" % (tag, sr))
            continue
        print("%-40s %-6d %-6s %s%s"
              % (tag, size, n, sr, "   MATCH" if n == 0 else ""))
        if n is not None and n < best[0]:
            best = (n, tag)
        if n == 0:
            open("build/try/%s.c" % SYM, "w").write(BASE.replace(SIG, pre + SIG))
            print("PROMOTED " + tag)
print()
print("best: %s bytes  %s" % best)
