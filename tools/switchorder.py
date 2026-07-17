#!/usr/bin/env python3
"""Recover the SOURCE ORDER of a dense switch's cases from the ROM.

A dense switch compiles to `cmp rX,#N ; addls pc,pc,rX,lsl #2` followed by one branch per case
value. Two orders are in play:
  - the jump TABLE is indexed by the case value, so its order is forced and tells you nothing;
  - the case BODIES are laid out in SOURCE order.
So sorting the table's targets by address recovers the order the cases were written in -- which is
routinely NOT 0,1,2,... Writing the switch in that order makes the whole layout fall out for free
(ov005_0205b100: 476/476 bytes, 119/119 instructions on the first compile).

Cases sharing a target share a body (`case 0: case 14: case 19:`). The branch immediately before
the table is the `default`.

Usage:  python tools/switchorder.py func_ov005_0205b100
"""
import json
import os
import sys

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    name = sys.argv[1]
    thumb = "--thumb" in sys.argv
    idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
    if name not in idx:
        raise SystemExit("not in func_index: " + name)
    e = idx[name]
    base = int(name[-8:], 16)
    code = bytes.fromhex(e["hex"])
    rel = {off: sym for off, sym in e["relocs"]}
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    ins = list(md.disasm(code, base))

    # Find the dispatch: `addls pc, pc, rX, lsl #2` (or `addcc`/`addlo` variants).
    disp = None
    for i, x in enumerate(ins):
        if x.mnemonic.startswith("add") and x.op_str.replace(" ", "").startswith("pc,pc,"):
            disp = i
            break
    if disp is None:
        raise SystemExit("no `add pc, pc, rX, lsl #2` dispatch found -- not a dense switch?")

    # The bound comes from the cmp just before it.
    bound = None
    for x in reversed(ins[:disp]):
        if x.mnemonic.startswith("cmp"):
            bound = int(x.op_str.split("#")[-1], 0)
            break
    n = (bound + 1) if bound is not None else 0

    # `add pc, pc, rX, lsl #2` at A computes A+8 + idx*4, so the TABLE always starts two
    # instructions after the dispatch, and the one at A+4 is the out-of-range fall-through --
    # i.e. the default. Usually that is a `b default_body`, but when the default body is short
    # (often just the epilogue) mwcc puts it INLINE there instead. Either way tbl0 is fixed;
    # only how to read the default differs.
    tbl0 = disp + 2
    nxt = ins[disp + 1]
    if nxt.mnemonic == "b":
        default = int(nxt.op_str.replace("#", ""), 16) - base
        default_note = "+0x%03x" % default
    else:
        default = nxt.address - base
        default_note = "+0x%03x (INLINE at the fall-through -- `%s %s`)" % (
            default, nxt.mnemonic, nxt.op_str)

    print("%s: %d bytes" % (name, e["size"]))
    print("dispatch at +0x%03x, bound=%s -> %d cases" % (ins[disp].address - base, bound, n))
    print("default -> %s" % default_note)
    print()

    # A table slot is USUALLY `b body`, but a case whose body is a single instruction gets that
    # instruction INLINE in the slot instead -- `case 0: return;` shows up as a bare
    # `pop {...,pc}` sitting in the table. So a non-branch slot is not an error: the slot IS
    # the body, and its address is its own.
    targets = {}
    inline = {}
    for k in range(n):
        x = ins[tbl0 + k]
        if x.mnemonic == "b":
            targets[k] = int(x.op_str.replace("#", ""), 16) - base
        else:
            targets[k] = x.address - base
            inline[k] = "%s %s" % (x.mnemonic, x.op_str)

    # group case values by body, then order the bodies by address = source order
    bodies = {}
    for case, t in targets.items():
        bodies.setdefault(t, []).append(case)

    def callee_at(t):
        for o in range(t, min(t + 20, len(code)), 4):
            if o in rel:
                return rel[o]
        return ""

    print("SOURCE ORDER (write the cases in exactly this order):")
    for t in sorted(bodies):
        cases = sorted(bodies[t])
        label = " ".join("case %d:" % c for c in cases)
        note = callee_at(t)
        for c in cases:
            if c in inline:
                note = ("INLINE IN THE TABLE SLOT (`%s`) -- a one-instruction body" % inline[c]
                        + (" / " + note if note else ""))
                break
        print("  +0x%03x  %-34s %s" % (t, label, note))
    print("  +0x%03x  default:                           %s" % (default, callee_at(default)))


if __name__ == "__main__":
    main()
