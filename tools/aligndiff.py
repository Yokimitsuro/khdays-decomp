#!/usr/bin/env python3
"""Classify a candidate's residue against the ROM by ALIGNED instruction diff.

    python tools/aligndiff.py <func_name> <cand.c> [<cand2.c> ...]

Why: tools/diffdis.py compares position by position, so a single inserted or deleted
instruction shifts everything after it and reports hundreds of false differences. Sequence
alignment separates the three things that actually matter:

    identical    -- same instruction, nothing to do
    regonly      -- same opcode, different register: allocation, fix structure first
    structural   -- different opcodes or different counts: a real source-shape difference

Rank candidates by `structural` ascending, not by the positional diff count, which is noise.
Measured on func_ov030_020b4864: the positional count said 94 vs 98 while structural said
22 vs 18, and the 18 was the better source.

ARM/Thumb is taken from build/func_index.json (the same authority verify_idx uses): the
candidate is compiled in that mode and both streams are decoded in it. Earlier versions
hardcoded ARM and, on a Thumb function, printed a confident wrong answer.
"""
import os, sys, json, difflib
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

if len(sys.argv) < 3:
    raise SystemExit(__doc__)
idx = json.load(open(os.path.join(ROOT, 'build', 'func_index.json')))
name = sys.argv[1]
if name not in idx:
    raise SystemExit('not in build/func_index.json: ' + name)
thumb = idx[name]['mode'] == 'thumb'
orig = bytes.fromhex(idx[name]['hex'])
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)


def dis(b):
    return [i.mnemonic + " " + i.op_str for i in md.disasm(b, 0)]


def masked(b, offsets):
    """Zero every relocated word, exactly as verify_idx does before comparing. The ROM holds
    linked targets (and `blx` after fix_interwork) where the object holds `bl #0` and empty
    pool words; left unmasked they count as structural differences on a byte-exact match."""
    b = bytearray(b)
    for off in offsets:
        for k in range(4):
            if off + k < len(b):
                b[off + k] = 0
    return bytes(b)


A = dis(masked(orig, (off for off, _ in idx[name]['relocs'])))
for path in sys.argv[2:]:
    mine, mrel = text_relocs(compile_c(path, thumb))
    B = dis(masked(mine, mrel))
    eq = reg = st = 0
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, A, B, autojunk=False).get_opcodes():
        if tag == 'equal':
            eq += i2 - i1
        elif (i2 - i1) == (j2 - j1) and all(
                A[i1 + k].split()[0] == B[j1 + k].split()[0] for k in range(i2 - i1)):
            reg += i2 - i1
        else:
            st += max(i2 - i1, j2 - j1)
    print("%-42s %-5s bytes=%-5d identical=%-4d regonly=%-4d structural=%d"
          % (os.path.basename(path), idx[name]['mode'], len(mine), eq, reg, st))
