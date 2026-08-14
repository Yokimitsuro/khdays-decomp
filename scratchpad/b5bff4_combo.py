"""Report the whole web map, not just the session, and sweep the two levers that
have been shown to move it: the const global with the session's declaration
position, and the order of case 2's two indices.
ROM map: nFrom=r6 s=r8 nTo=r5 nClass=r4 nOld=r4 nNew=r7
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
    # case 2: the two indices are the only add rX, r6/r5, r2 pair
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
    p = "build/try/b5bff4_cm.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-30s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
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
    print("%-30s %-5d b=%-4s %s%s" % (tag, len(code), n, w,
                                      "  <== ROM" if w == ROM else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


BASE = open("build/try/func_ov002_0205bff4.c").read()
GLOB = "extern Ov002PanelSession *data_ov002_0207f620;"
CGLOB = "extern Ov002PanelSession *const data_ov002_0207f620;"
DECL = """    int nColumn;
    int nTag;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
"""
OLDNEW = """        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
"""
NEWOLD = """        int nNew = nTo + nColumn * 6;
        int nOld = nFrom + nColumn * 6;
"""
assert GLOB in BASE and DECL in BASE and OLDNEW in BASE
print("%-30s %-5s %-6s %s" % ("ROM target", 1416, "b=0", ROM))

POS = {
    "s1": """    Ov002PanelSession *s = data_ov002_0207f620;
    int nColumn;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "s2": """    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nTag;
    int nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
""",
    "s3": DECL,
}
for g, gname in ((GLOB, "plain"), (CGLOB, "const")):
    for pn, pd in sorted(POS.items()):
        for on, od in (("old1st", OLDNEW), ("new1st", NEWOLD)):
            src = BASE.replace(GLOB, g).replace(DECL, pd).replace(OLDNEW, od)
            report("%s %s %s" % (gname, pn, on), src)
