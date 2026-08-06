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
"""
import sys, json, difflib
sys.path.insert(0, 'tools')
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

idx = json.load(open('build/func_index.json'))
name = sys.argv[1]
orig = bytes.fromhex(idx[name]['hex'])
md = Cs(CS_ARCH_ARM, CS_MODE_ARM)


def dis(b):
    return [i.mnemonic + " " + i.op_str for i in md.disasm(b, 0)]


A = dis(orig)
for path in sys.argv[2:]:
    mine, _ = text_relocs(compile_c(path, False))
    B = dis(mine)
    eq = reg = st = 0
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, A, B, autojunk=False).get_opcodes():
        if tag == 'equal':
            eq += i2 - i1
        elif (i2 - i1) == (j2 - j1) and all(
                A[i1 + k].split()[0] == B[j1 + k].split()[0] for k in range(i2 - i1)):
            reg += i2 - i1
        else:
            st += max(i2 - i1, j2 - j1)
    print("%-42s bytes=%-5d identical=%-4d regonly=%-4d structural=%d"
          % (path.split('/')[-1], len(mine), eq, reg, st))
