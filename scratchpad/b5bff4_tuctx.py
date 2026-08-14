"""Last stateful axis: what precedes the function in its translation unit. mwcc
may carry allocator state across functions in a unit, and the real source file
certainly had other functions before this one. verify_idx extracts by symbol, so
extra functions in the file are harmless to the check.
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
assert SIG in BASE

PRE = {
    "trivial": """static void ov002_pre0(void) {
}

""",
    "one pointer local": """static void ov002_pre1(int a) {
    Ov002PanelSession *p = data_ov002_0207f620;

    func_ov002_02053cd4(p->bMode + a);
}

""",
    "heavy, seven registers": """static void ov002_pre2(int a, int b) {
    Ov002PanelSession *p = data_ov002_0207f620;
    int c = func_ov002_0205a3f0(&a, p->bMode);
    int d;

    switch (c) {
    case 0:
        func_ov002_0205ae08(p->wField0014, p->nField000c, 0);
        break;
    case 1: {
        int e = a + b * 6;
        int f = b + b * 6;

        func_ov002_0205b0dc(p->listItems, e, a, f, 1, 0, 0, 0);
        func_ov002_0205b0dc(p->listItems, f, b, e, 1, 1, 0, 0);
        break;
    }
    case 2:
        d = func_ov002_0206dc10(b);
        func_ov002_0205b0dc(p->listEntries, d, a, b, 1, 1, 1, d);
        break;
    }
    p->bKind = (u8)b;
}

""",
}


def score(src):
    p = "build/try/b5bff4_tu.c"
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


def report(tag, src):
    size, n, sr = score(src)
    if size is None:
        print("%-32s FAIL %s" % (tag, sr))
        return
    print("%-32s size=%-5d bytes=%-5s s=%s%s"
          % (tag, size, n, sr, "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


report("nothing before", BASE)
for tag, pre in sorted(PRE.items()):
    report("before: " + tag, BASE.replace(SIG, pre + SIG))
# all three, and the heavy one twice
allpre = "".join(PRE[k] for k in sorted(PRE))
report("before: all three", BASE.replace(SIG, allpre + SIG))
report("after: heavy", BASE + "\n" + PRE["heavy, seven registers"]
       .replace("ov002_pre2", "ov002_post2"))
