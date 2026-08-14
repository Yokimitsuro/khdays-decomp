"""Decisive check never done explicitly: is the entire residue a SINGLE global
register permutation? Walk both instruction streams, accumulate the mapping from
my registers to the ROM's, and report conflicts. If the mapping is consistent
everywhere, the residue is exactly one relabelling and my model is right; if
there are conflicts, something else differs and the model is wrong.
"""
import sys
import os
import json
import re
from collections import defaultdict

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
code, _ = text_relocs(compile_c("build/try/%s.c" % SYM, False))

ALIAS = {"sb": "r9", "sl": "r10", "fp": "r11", "ip": "r12"}
RE = re.compile(r"\b(r1[0-5]|r[0-9]|sb|sl|fp|ip|lr|sp|pc)\b")


def norm(t):
    return RE.sub(lambda m: ALIAS.get(m.group(1), m.group(1)), t)


la = list(md.disasm(bytes(ORIG), 0))
lb = list(md.disasm(bytes(code), 0))
print("ROM %d instructions, mine %d" % (len(la), len(lb)))
assert len(la) == len(lb)

pairs = defaultdict(lambda: defaultdict(int))
shape_mismatch = []
for i in range(len(la)):
    ta = norm(la[i].mnemonic + " " + la[i].op_str)
    tb = norm(lb[i].mnemonic + " " + lb[i].op_str)
    if ta == tb:
        continue
    ra = RE.findall(ta)
    rb = RE.findall(tb)
    # same mnemonic and same operand skeleton?
    sa = RE.sub("#", ta)
    sb2 = RE.sub("#", tb)
    if sa != sb2 or len(ra) != len(rb):
        shape_mismatch.append((i, ta, tb))
        continue
    for x, y in zip(rb, ra):
        pairs[x][y] += 1

print()
print("instructions whose SHAPE differs (not just registers): %d"
      % len(shape_mismatch))
for i, ta, tb in shape_mismatch[:10]:
    print("   %3d ROM %-32s mine %s" % (i, ta, tb))

print()
print("register mapping observed, mine -> ROM:")
conflicts = 0
mapping = {}
for mine in sorted(pairs, key=lambda r: (len(r), r)):
    tot = sum(pairs[mine].values())
    best = max(pairs[mine], key=lambda r: pairs[mine][r])
    entries = ", ".join("%s x%d" % (k, v) for k, v in
                        sorted(pairs[mine].items(), key=lambda kv: -kv[1]))
    ok = len(pairs[mine]) == 1
    if not ok:
        conflicts += 1
    mapping[mine] = best
    print("   %-4s -> %-28s %s" % (mine, entries, "" if ok else "CONFLICT"))

print()
print("registers with a conflicting mapping: %d" % conflicts)

# apply the best mapping to my stream and count what remains
resid = 0
for i in range(len(la)):
    ta = norm(la[i].mnemonic + " " + la[i].op_str)
    tb = norm(lb[i].mnemonic + " " + lb[i].op_str)
    tb2 = RE.sub(lambda m: mapping.get(ALIAS.get(m.group(1), m.group(1)),
                                       ALIAS.get(m.group(1), m.group(1))), tb)
    if ta != tb2:
        resid += 1
print("instructions still differing after applying the mapping: %d" % resid)
if resid == 0 and not shape_mismatch:
    print()
    print("CONCLUSION: the entire residue is ONE global register permutation.")
