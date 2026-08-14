"""Canonical comparison, this time building the register map from first use in
the body only: the push and pop list every register in numeric order and would
otherwise fix the mapping before any real use.
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
FIXED = {"sp", "pc", "lr", "r0", "r1", "r2", "r3", "r12"}


def canon(code):
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    mapping = {}
    nxt = [0]
    for text in ins:
        if text.startswith(("push", "pop", "stmdb", "ldmia", "ldm", "stm")):
            continue
        for m in RE.finditer(text):
            r = ALIAS.get(m.group(1), m.group(1))
            if r in FIXED or r in mapping:
                continue
            mapping[r] = "V%d" % nxt[0]
            nxt[0] += 1
    out = []
    for text in ins:
        if text.startswith(("push", "pop", "stmdb", "ldmia", "ldm", "stm")):
            out.append(re.sub(r"\{[^}]*\}", "{SET}", text))
            continue
        out.append(RE.sub(lambda m: mapping.get(ALIAS.get(m.group(1),
                                                          m.group(1)),
                                                ALIAS.get(m.group(1),
                                                          m.group(1))), text))
    return out, mapping


a, ma = canon(orig)
b, mb = canon(mine)
print("ROM map :", ma)
print("MINE map:", mb)
print("instr ROM %d MINE %d" % (len(a), len(b)))
diff = 0
for k in range(min(len(a), len(b))):
    if a[k] != b[k] and not a[k].startswith("bl "):
        diff += 1
        if diff <= 20:
            print("%03d %-34s | %-34s" % (k, a[k], b[k]))
print("canonical differences excluding bl:", diff)
