"""Sweep the prototypes of the other callees in cases 2 and 3. A callee's
declared prototype is a real codegen input rather than a rewrite of the body,
and last turn one such change moved the register allocation, so the axis is live.
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


def sess(code):
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            return m.group(1)
    return "?"


def score(src):
    p = "build/try/b5bff4_p2.c"
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
    return len(code), n, sess(code)


# each knob replaces one extern declaration
KNOBS = {
    "lst": ("extern void *func_02010154(void *pList, u16 nIndex);",
            ["extern void *func_02010154(void *pList, u16 nIndex);",
             "extern u16 *func_02010154(void *pList, u16 nIndex);",
             "extern void *func_02010154(u8 *pList, u16 nIndex);",
             "extern void *func_02010154(void *pList, int nIndex);"]),
    "slot": ("extern int func_ov002_0205a540(int nKey);",
             ["extern int func_ov002_0205a540(int nKey);",
              "extern int func_ov002_0205a540(u16 nKey);",
              "extern int func_ov002_0205a540(unsigned nKey);"]),
    "q714": ("extern int func_ov002_0205a714(int a, int nKey);",
             ["extern int func_ov002_0205a714(int a, int nKey);",
              "extern int func_ov002_0205a714(int a, u16 nKey);",
              "extern int func_ov002_0205a714(u8 a, int nKey);"]),
    "tagfn": ("extern int func_ov002_0206dc10(int nTag);",
              ["extern int func_ov002_0206dc10(int nTag);",
               "extern int func_ov002_0206dc10(u8 nTag);",
               "extern int func_ov002_0206dc10(unsigned nTag);"]),
}
for name, (old, _) in KNOBS.items():
    assert old in BASE, name

best = (10 ** 9, None)
n = 0
vals = {}
keys = list(KNOBS)
for combo in itertools.product(*[range(len(KNOBS[k][1])) for k in keys]):
    src = BASE
    for k, v in zip(keys, combo):
        src = src.replace(KNOBS[k][0], KNOBS[k][1][v])
    size, d, sr = score(src)
    n += 1
    tag = " ".join("%s=%d" % (k, v) for k, v in zip(keys, combo))
    if size is None:
        continue
    if d is None:
        vals.setdefault("size %d" % size, 0)
        vals["size %d" % size] += 1
        continue
    vals.setdefault(d, 0)
    vals[d] += 1
    if d < best[0]:
        best = (d, tag)
        print("new best %d bytes  s=%s  %s" % (d, sr, tag))
    if sr not in ("r4", "?"):
        print("POINTER MOVED to %s: %s (%d bytes diff)" % (sr, tag, d))
    if d == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("MATCH " + tag)
        break

print()
print("compiled %d combinations" % n)
print("outcome histogram:", dict(sorted(vals.items(), key=str)))
print("best: %d bytes  %s" % (best[0], best[1]))
