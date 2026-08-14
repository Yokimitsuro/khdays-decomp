"""Close the gap in last turn's conclusion. Several knobs were each measured inert
on their own, but two inert knobs can in principle combine into something that is
not. Cross six of them, plus the conversion flag, and check whether any pairing
beats 67 bytes or reaches r8.
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


def k_cast(src, v):
    if not v:
        return src
    return src.replace(
        "    Ov002PanelSession *s = data_ov002_0207f620;",
        "    Ov002PanelSession *s = (Ov002PanelSession *)data_ov002_0207f620;")


def k_nested(src, v):
    """case 2's short-circuit written as nested ifs."""
    if not v:
        return src
    return src.replace("""        bFlag = 0;
        if (func_ov002_0205a714(0, *pEntry) != 0 &&
            func_ov002_0205a730(0, *pEntry) != 0) {
            bFlag = 1;
        }
""", """        bFlag = 0;
        if (func_ov002_0205a714(0, *pEntry) != 0) {
            if (func_ov002_0205a730(0, *pEntry) != 0) {
                bFlag = 1;
            }
        }
""")


def k_default(src, v):
    if not v:
        return src
    return src.replace("    case 4:\n        break;\n",
                       "    default:\n        break;\n")


def k_pretemp(src, v):
    if not v:
        return src
    s = src.replace("    int nColumn;\n    int nTag;\n",
                    "    int nColumn;\n    int nTag;\n    int nEntry;\n")
    return s.replace("""    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {""",
                     """    nEntry = func_ov002_020536bc(0xe);
    if (func_ov002_0205374c(nEntry) == 0) {""")


def k_pad(src, v):
    if not v:
        return src
    return src.replace("""    u8 pad0008[4];
    int nField000c;         /* +0xc */
    u8 pad0010[4];
""", """    int pad0008;
    int nField000c;         /* +0xc */
    int pad0010;
""")


def k_static(src, v):
    if not v:
        return src
    return src.replace("void func_ov002_0205bff4(int nFrom, int nTo) {",
                       "static void func_ov002_0205bff4(int nFrom, int nTo) {")


def k_names(src, v):
    if not v:
        return src
    for old, new in (("nFrom", "a"), ("nTo", "b"), ("nClass", "d"),
                     ("nTag", "e")):
        src = re.sub(r"\b%s\b" % old, new, src)
    return src


KNOBS = [("cast", k_cast), ("nested", k_nested), ("default", k_default),
         ("pretemp", k_pretemp), ("pad", k_pad), ("static", k_static),
         ("names", k_names)]

best = (999, None)
reached = {}
n_ok = 0
for combo in itertools.product((0, 1), repeat=len(KNOBS)):
    src = BASE
    for (name, fn), v in zip(KNOBS, combo):
        src = fn(src, v)
    p = "build/try/b5bff4_cx.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception:
        continue
    if len(code) != len(ORIG):
        continue
    a = bytearray(ORIG)
    b = bytearray(code)
    for off in set(OREL) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    d = sum(1 for i in range(len(a)) if a[i] != b[i])
    sr = "?"
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    n_ok += 1
    reached.setdefault(sr, []).append(d)
    tag = " ".join(k[0] for k, v in zip(KNOBS, combo) if v) or "(none)"
    if d < best[0]:
        best = (d, tag)
        print("new best %d bytes  s=%s  %s" % (d, sr, tag))
    if sr == "r8":
        print("REACHED r8: %s (%d bytes)" % (tag, d))
    if d == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("MATCH " + tag)
        break

print()
print("compiled and size-correct: %d of %d" % (n_ok, 2 ** len(KNOBS)))
for sr in sorted(reached):
    print("   s=%-4s best=%-4d over %d" % (sr, min(reached[sr]), len(reached[sr])))
print("best overall: %s bytes  %s" % best)
