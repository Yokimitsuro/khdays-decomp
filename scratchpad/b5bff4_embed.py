"""The session must be assigned before the classifier call but the ROM orders its
web after nClass. Assigning it inside the call's argument separates declaration
order from assignment order without a reload.
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
ROM = "nFrom=r6 nTo=r5 s=r8 nClass=r4 nOld=r4 nNew=r7"


def webmap(code):
    ins = [(i.mnemonic + " " + i.op_str) for i in md.disasm(bytes(code), 0)]
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
    for t in ins:
        m = re.match(r"^add (r\w+), r6, r2$", t)
        if m and "nOld" not in d:
            d["nOld"] = m.group(1)
        m = re.match(r"^add (r\w+), r5, r2$", t)
        if m and "nNew" not in d:
            d["nNew"] = m.group(1)
    return "nFrom=%s nTo=%s s=%s nClass=%s nOld=%s nNew=%s" % (
        d.get("nFrom", "?"), d.get("nTo", "?"), d.get("s", "?"),
        d.get("nClass", "?"), d.get("nOld", "?"), d.get("nNew", "?"))


def report(tag, src):
    p = "build/try/b5bff4_em.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-28s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
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
    w = webmap(code)
    print("%-28s %-5d b=%-4s %s%s" % (tag, len(code), n, w,
                                      "  <== ROM" if w == ROM else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/b5bff4_best.c").read()
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
assert DECL in BASE
report("best", BASE)

VAR = {
    "embed_s_decl_after": """    int nColumn;
    int nTag;
    int nClass;
    Ov002PanelSession *s;

    nClass = func_ov002_0205a3f0(&nColumn, (s = data_ov002_0207f620)->bMode);
""",
    "embed_s_decl_before": """    int nColumn;
    int nTag;
    Ov002PanelSession *s;
    int nClass;

    nClass = func_ov002_0205a3f0(&nColumn, (s = data_ov002_0207f620)->bMode);
""",
    "comma_s_decl_after": """    int nColumn;
    int nTag;
    int nClass;
    Ov002PanelSession *s;

    nClass = func_ov002_0205a3f0(&nColumn,
                                 (s = data_ov002_0207f620, s->bMode));
""",
    "embed_init_after": """    int nColumn;
    int nTag;
    Ov002PanelSession *s;
    int nClass = func_ov002_0205a3f0(&nColumn,
                                     (s = data_ov002_0207f620)->bMode);
""",
    "embed_global_read": """    int nColumn;
    int nTag;
    int nClass;
    Ov002PanelSession *s;

    nClass = func_ov002_0205a3f0(&nColumn, data_ov002_0207f620->bMode);
    s = data_ov002_0207f620;
""",
    "seq_s_then_class": """    int nColumn;
    int nTag;
    int nClass;
    Ov002PanelSession *s;

    s = data_ov002_0207f620;
    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
}
for tag, d in sorted(VAR.items()):
    report(tag, BASE.replace(DECL, d))
