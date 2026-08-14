"""Measure the COMBINED ordering: N whole-function values plus M branch-local
values, and read which register each takes. The straight-line rule is definition
order descending from the top; the question is how branch-local webs perturb the
whole-function ones, which is what the active function does and the straight-line
probe cannot capture.
"""
import sys
import os
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
HEAD = """extern void snk(int);
extern int src(void);
extern int mid(int);
extern int cls(int);
"""


def build(nwhole, mbranch):
    decls = "".join("    int w%d = src();\n" % i for i in range(nwhole))
    cases = ""
    for c in range(max(mbranch, 1)):
        if c < mbranch:
            cases += ("    case %d: {\n"
                      "        int b%d = src();\n"
                      "        snk(mid(b%d));\n"
                      "        snk(mid(b%d));\n"
                      "        snk(b%d);\n"
                      "        break;\n    }\n" % (c, c, c, c, c))
        else:
            cases += "    case %d: snk(0); break;\n" % c
    tail = "".join("    snk(w%d);\n" % i for i in range(nwhole))
    return """
void f(void) {
%s    int k = cls(0);

    switch (k) {
%s    }
%s}
""" % (decls, cases, tail)


def probe(nwhole, mbranch):
    src = HEAD + build(nwhole, mbranch)
    p = "build/try/b5bff4_cm2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        return None, str(ex).split("\n")[0][:50]
    ins = list(md.disasm(bytes(code), 0))
    txt = [i.mnemonic + " " + i.op_str for i in ins]
    push = txt[0][5:] if txt[0].startswith("push") else "(none)"
    # whole-function values are the first nwhole `mov rX, r0` after a bl
    whole = []
    for n, t in enumerate(txt):
        if len(whole) >= nwhole:
            break
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and n > 0 and txt[n - 1].startswith("bl"):
            whole.append(m.group(1))
    # branch values: the same shape but after the dispatch
    disp = next((n for n, t in enumerate(txt)
                 if t.startswith("cmp ") or t.startswith("addls")), 0)
    branch = []
    for n, t in enumerate(txt):
        if n <= disp:
            continue
        m = re.match(r"^mov (r\w+), r0$", t)
        if m and txt[n - 1].startswith("bl") and m.group(1) not in branch:
            branch.append(m.group(1))
    return (push, whole, branch), None


print("straight-line rule: definition order, descending from the top")
print("question: what do branch-local webs do to that order")
print()
for nwhole in (2, 3, 4):
    for mbranch in (0, 1, 2, 3):
        r, err = probe(nwhole, mbranch)
        if err:
            print("whole=%d branch=%d  FAIL %s" % (nwhole, mbranch, err))
            continue
        push, whole, branch = r
        print("whole=%d branch=%d  push=%-34s whole=%-20s branch=%s"
              % (nwhole, mbranch, push[:34],
                 ",".join(whole), ",".join(branch[:4])))
