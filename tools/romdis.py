"""Disassemble a function straight out of the ROM index, with reloc targets inlined.

Ghidra has no function object at some overlay addresses (the asm_stub carve left a
hole), so read the bytes from build/func_index.json instead and annotate each
relocated word with the symbol it resolves to.
Usage: python build/try/dis.py <name> [start] [count]
"""
import json, os, sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = "E:/KH 3582/decomp"
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
name = sys.argv[1]
start = int(sys.argv[2]) if len(sys.argv) > 2 else 0
count = int(sys.argv[3]) if len(sys.argv) > 3 else 10000

d = idx[name]
data = bytes.fromhex(d["hex"])
base = int(name.split("_")[-1], 16)
rel = {}
for o, s in d["relocs"]:
    rel[o & ~3] = s

thumb = d.get("mode") == "thumb"
print("mode: %s" % ("THUMB" if thumb else "ARM"))
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
n = 0
for ins in md.disasm(data, base):
    off = ins.address - base
    if off < start:
        continue
    if n >= count:
        break
    n += 1
    tag = "   ; -> " + rel[off] if off in rel else ""
    print("%04x  %-8s %s%s" % (off, ins.mnemonic, ins.op_str, tag))
