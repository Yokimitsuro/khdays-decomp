#!/usr/bin/env python3
"""Positional instruction diff against build/func_index.json.

    python tools/posdiff.py <func_name> <a.c> [<b.c> ...]     # rank candidates
    python tools/posdiff.py <func_name> <a.c> --list          # show every mismatch

Why this exists, and why it is NOT an edit-distance tool
--------------------------------------------------------
The obvious way to score a near-miss candidate is an edit distance over the
disassembled instruction stream. That metric LIES once you are close, because it
weighs a renamed register exactly like a genuinely different instruction. On
func_ov000_02050ec4 it ranked a candidate with 24 mnemonic mismatches ABOVE one
with 4, and several hours went into optimising the wrong one.

So: once the size already matches, align by POSITION and report two numbers.

    mnemonic-mismatch   wrong instruction, or the right instructions in the wrong
                        order.
    operand-mismatch    same mnemonic, but a different immediate, memory offset or
                        shift, with register NAMES normalised away.
    full-mismatch       the above plus register-naming differences. Useful as a
                        tie-break only, never as the primary score.

RANK BY mnemonic + operand. Reporting the mnemonic count alone is a trap I fell into
on func_ov000_02050ec4: a candidate came out `mnemonic-mismatch=0` and I read it as
"the instruction stream is identical". It was not -- two adjacent loads had SWAPPED
MEMORY OFFSETS (0xc94 and 0xc98), which is a real defect the mnemonic view cannot see
because both instructions are `ldr`. The operand column exists so that cannot happen
again. A candidate is structurally correct only when mnemonic AND operand are both 0.

A candidate whose size differs is not comparable at all; those are reported as
`size N` and sorted last, because a positional alignment of two different-length
streams is meaningless.

Branch displacements and literal-pool offsets are normalised away, exactly as the
byte-level gate masks relocations -- otherwise one extra instruction early on
would show up as a mismatch on every later branch.
"""
import sys, os, json, re

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))


def _mode(name):
    """ARM unless symbols.txt says thumb. Any tool that compiles must handle both:
       verifying a THUMB function as ARM prints a meaningless size gap, which reads
       exactly like broken C."""
    for dirpath, _dirs, files in os.walk(os.path.join(ROOT, "config")):
        if "symbols.txt" not in files:
            continue
        with open(os.path.join(dirpath, "symbols.txt"), encoding="utf-8",
                  errors="replace") as fh:
            for line in fh:
                if line.startswith(name + " ") and "kind:function(thumb" in line:
                    return True
    return False


def _norm_regs(op_str):
    """Blank out register NAMES so what is left is immediates, offsets and shifts."""
    return re.sub(r"\b(r\d+|ip|lr|sl|fp|sb|sp)\b", "R", op_str)


def disasm(code, thumb):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    out = []
    for ins in md.disasm(bytes(code), 0):
        op = re.sub(r"\[pc, #(-?0x[0-9a-f]+|-?\d+)\]", "[pc,#POOL]", ins.op_str)
        if ins.mnemonic.startswith("bl") or ins.mnemonic == "b":
            op = "OFF"
        out.append((ins.mnemonic, op))
    return out


def score(name, cpath, thumb):
    orig = disasm(bytearray.fromhex(IDX[name]["hex"]), thumb)
    obj = compile_c(cpath, thumb)
    mine, _ = text_relocs(obj)
    m = disasm(mine, thumb)
    return orig, m


def main():
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)
    name = sys.argv[1]
    if name not in IDX:
        raise SystemExit("not in func_index: " + name)
    show = "--list" in sys.argv
    cands = [a for a in sys.argv[2:] if not a.startswith("--")]
    thumb = _mode(name)
    rows = []
    for c in cands:
        try:
            orig, m = score(name, c, thumb)
        except SystemExit:
            rows.append((9999, 9999, c, "compile failed")); continue
        if len(m) != len(orig):
            rows.append((9998, 9998, 9998, c, "size %d != %d" % (len(m) * 4, len(orig) * 4)))
            continue
        mn = sum(1 for a, b in zip(orig, m) if a[0] != b[0])
        op = sum(1 for a, b in zip(orig, m)
                 if a[0] == b[0] and _norm_regs(a[1]) != _norm_regs(b[1]))
        fl = sum(1 for a, b in zip(orig, m) if a != b)
        rows.append((mn + op, mn, op, fl, c, "ok"))
        if show:
            print("=== %s" % c)
            for k, (a, b) in enumerate(zip(orig, m)):
                if a != b:
                    if a[0] != b[0]:
                        tag = "MNEM"
                    elif _norm_regs(a[1]) != _norm_regs(b[1]):
                        tag = "OPND"
                    else:
                        tag = "    "
                    print("%s +0x%03X  %-34s | %s"
                          % (tag, k * 4, a[0] + " " + a[1], b[0] + " " + b[1]))
    rows.sort()
    for _tot, mn, op, fl, c, note in rows:
        head = "%-40s" % os.path.basename(c)
        if note == "ok":
            print("%s mnemonic=%-4d operand=%-4d full=%-4d" % (head, mn, op, fl))
        else:
            print("%s %s" % (head, note))


if __name__ == "__main__":
    main()
