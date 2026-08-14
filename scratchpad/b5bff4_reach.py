"""Establish whether r8 is reachable at all for the session from source. Cross the
conversion flag, now known to be the real lever, with every other knob that has
ever moved anything: the const global, the declaration position, the case 2 index
order and the address-taken local's form. Report the SET of registers reached.
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
GLOB = "extern Ov002PanelSession *data_ov002_0207f620;"
CGLOB = "extern Ov002PanelSession *const data_ov002_0207f620;"
SDECL = "    Ov002PanelSession *s = data_ov002_0207f620;"
CAST = "    Ov002PanelSession *s = (Ov002PanelSession *)data_ov002_0207f620;"
C2_A = """        int nNew = nTo + nColumn * 6;
        int nOld = nFrom + nColumn * 6;
"""
C2_B = """        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
"""
COL_A = "    int nColumn;\n"
COL_B = "    int aColumn[1];\n"


def score(src):
    p = "build/try/b5bff4_rc2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception:
        return None, None, "?"
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
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    return len(code), n, sr


reached = {}
n_ok = 0
for cast, cg, pos, c2, col in itertools.product(
        (0, 1), (0, 1), (0, 1, 2), (0, 1), (0, 1)):
    src = BASE
    decl = CAST if cast else SDECL
    src = src.replace(SDECL, decl)
    if cg:
        src = src.replace(GLOB, CGLOB)
    if c2:
        src = src.replace(C2_A, C2_B)
    if col:
        src = src.replace(COL_A, COL_B, 1)
        src = re.sub(r"\bnColumn\b", "aColumn[0]", src)
        src = src.replace("&aColumn[0]", "aColumn")
        src = src.replace("int aColumn[0][1];", "int aColumn[1];")
    if pos == 1:
        src = src.replace("    int nTag;\n" + decl + "\n",
                          decl + "\n    int nTag;\n")
    elif pos == 2:
        src = src.replace(decl + "\n", "")
        src = src.replace("    int nTag;\n", "    int nTag;\n" + decl + "\n", 1)
    size, d, sr = score(src)
    if size is None or d is None:
        continue
    n_ok += 1
    reached.setdefault(sr, []).append(d)
    if sr == "r8":
        print("REACHED r8 with cast=%d const=%d pos=%d c2=%d col=%d, %d bytes"
              % (cast, cg, pos, c2, col, d))
    if d == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("MATCH")

print("compiled and size-correct: %d variants" % n_ok)
print("registers the session reached, with best byte count:")
for sr in sorted(reached):
    print("   s=%-4s best=%-4d over %d variants" % (sr, min(reached[sr]),
                                                    len(reached[sr])))
print()
print("r8 reachable from source:", "YES" if "r8" in reached else "NO")
