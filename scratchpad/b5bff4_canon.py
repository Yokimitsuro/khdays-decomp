"""Definitive diagnostic: rename registers canonically in both streams, by first
appearance, and see whether they then match exactly. If they do the residue is
purely allocation; if not there is a structural difference still hiding.
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
orig = bytearray.fromhex(json.load(open("build/func_index.json"))[SYM]["hex"])
o = compile_c("build/try/%s.c" % SYM, False)
mine, _ = text_relocs(o)

RE = re.compile(r"\b(r1[0-5]|r[0-9]|sb|sl|fp|ip|lr|sp|pc)\b")
ALIAS = {"sb": "r9", "sl": "r10", "fp": "r11", "ip": "r12"}
FIXED = {"sp", "pc", "lr", "r0", "r1", "r2", "r3", "r12", "ip"}


def canon(code):
    out = []
    mapping = {}
    nxt = [0]
    for i in md.disasm(bytes(code), 0):
        text = i.mnemonic + " " + i.op_str

        def sub(m):
            r = ALIAS.get(m.group(1), m.group(1))
            if r in FIXED:
                return r
            if r not in mapping:
                mapping[r] = "V%d" % nxt[0]
                nxt[0] += 1
            return mapping[r]
        out.append(RE.sub(sub, text))
    return out, mapping


a, ma = canon(orig)
b, mb = canon(mine)
print("ROM map :", ma)
print("MINE map:", mb)
print("instr ROM %d MINE %d" % (len(a), len(b)))
diff = 0
for k in range(min(len(a), len(b))):
    if a[k] != b[k]:
        diff += 1
        if diff <= 15:
            print("%03d %-32s | %-32s" % (k, a[k], b[k]))
print("canonical differences:", diff)
