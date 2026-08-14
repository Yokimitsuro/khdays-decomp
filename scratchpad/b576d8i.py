"""Everything outside the offset computation now matches. Re-sweep the pointer
association on this corrected base: the earlier pointer sweeps ran against the
old loop bodies, so their verdicts no longer apply.
"""
import sys
import os
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_020576d8"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()
OLD = ("    p = (u8 *)(nRow * 4 + (nStart / 8) * 0x20 + (int)pDst"
       " + (nStart % 8) / 2);\n")
assert OLD in BASE

T_ROW = "nRow * 4"
T_TILE = "(nStart / 8) * 0x20"
T_HALF = "(nStart % 8) / 2"
T_DST = "(int)pDst"

best = [999, None]
seen = set()
for perm in itertools.permutations([T_ROW, T_TILE, T_HALF, T_DST]):
    if perm in seen:
        continue
    seen.add(perm)
    form = "    p = (u8 *)(" + " + ".join(perm) + ");\n"
    s = BASE.replace(OLD, form)
    path = "build/try/b576d8_z.c"
    open(path, "w").write(s)
    tag = " ".join(x[:6] for x in perm)
    try:
        o = compile_c(path, False)
        mine, mrel = text_relocs(o)
    except Exception:
        continue
    ins = list(md.disasm(bytes(mine), 0))
    push = ins[0].op_str if ins else ""
    if len(mine) != len(orig):
        continue
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    n = sum(1 for i in range(len(a)) if a[i] != b[i])
    if n < best[0]:
        best[0] = n
        best[1] = form
        print("%-34s bytes=%d push=%s%s" % (tag, n, push,
                                            "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(s)
        print("PROMOTED")
        break
print("best bytes %s form %s" % (best[0], (best[1] or "").strip()))
