#!/usr/bin/env python3
"""Generate the C for the "VM emit handler" family.

Every member has the same skeleton: pull N operands out of the script VM's
descriptor array into a stack struct, fetch a target id and a builder id, call an
overlay-specific builder with (id, &params), and hand the result to
func_ov002_0207643c. They differ only in which fetcher serves each slot, the
descriptor offsets, and whether a slot is stored as a word or a byte.

    python tools/gen_vm_emit.py func_ov016_020814b0 [--write]

Reads build/func_index.json (bytes + relocs) and disassembles with capstone, so
it needs no Ghidra round trip. Emits to build/try/ unless --write is given.
"""
import json
import os
import re
import sys

import capstone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
FETCHERS = {"func_02021948", "func_02021980", "func_02021994",
            "func_020219a8", "func_020219c0"}
SINK = "func_ov002_0207643c"


def analyse(name):
    e = IDX[name]
    code = bytes.fromhex(e["hex"])
    rel = {off: sym for off, sym in e["relocs"]}
    md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
    md.detail = False
    ins = list(md.disasm(code, 0))

    ops = []            # (fetcher, desc_off, store_off, width) ; store_off None = register
    desc_off = 0        # running "adds r1, #imm" accumulator
    base = 0            # "adds r4, #imm" advances the descriptor BASE persistently
    pending = None
    frame = 0
    for i in ins:
        m = i.mnemonic, i.op_str
        if i.mnemonic == "sub" and i.op_str.startswith("sp,"):
            frame = int(i.op_str.split("#")[1], 0)
        elif i.mnemonic == "adds" and re.match(r"^r1, r\d+, #0$", i.op_str):
            desc_off = base
        elif i.mnemonic == "adds" and re.match(r"^r1, #", i.op_str):
            desc_off += int(i.op_str.split("#")[1], 0)
        elif i.mnemonic == "adds" and re.match(r"^r4, #", i.op_str):
            # the tail advances the descriptor BASE, and it stays advanced --
            # tracking it as a one-shot offset silently emits `descs` for the
            # last fetch when the ROM means `descs + 8`.
            base += int(i.op_str.split("#")[1], 0)
            desc_off = base
        elif i.mnemonic == "bl":
            sym = rel.get(i.address)
            if sym in FETCHERS:
                pending = (sym, desc_off)
                desc_off = 0
            elif sym is not None:
                # The LAST operand fetch feeds the builder call directly (via the
                # u16 cast) with no store or register copy in between, so it is
                # still pending here. Flush it before recording the call or it is
                # silently lost -- which is exactly what the first version did.
                if pending is not None:
                    ops.append((pending[0], pending[1], None, None))
                    pending = None
                ops.append(("CALL", sym, None, None))
        elif pending is not None and i.mnemonic in ("str", "strb"):
            m2 = re.match(r"^r0, \[(sp|r1), #(0x[0-9a-f]+|\d+)\]$", i.op_str)
            off = int(m2.group(2), 0) if m2 else 0
            ops.append((pending[0], pending[1], off, 1 if i.mnemonic == "strb" else 4))
            pending = None
        elif pending is not None and i.mnemonic == "str" and i.op_str == "r0, [sp]":
            ops.append((pending[0], pending[1], 0, 4))
            pending = None
        elif pending is not None and i.mnemonic == "adds" and re.match(r"^r\d+, r0, #0$", i.op_str):
            ops.append((pending[0], pending[1], None, None))
            pending = None
    if pending is not None:
        ops.append((pending[0], pending[1], None, None))
    return e, frame, ops, rel


def emit(name, e, frame, ops, rel):
    unit = re.match(r"func_(ov\d+)_", name)
    pfx = (unit.group(1).replace("ov", "Ov") if unit else "Main")
    stores = [o for o in ops if o[0] != "CALL" and o[2] is not None]
    regs = [o for o in ops if o[0] != "CALL" and o[2] is None]
    calls = [o for o in ops if o[0] == "CALL"]
    builder = calls[0][1] if calls else "?"

    # struct: only the slots actually written, padded to the frame size
    fields = sorted(stores, key=lambda o: o[2])
    lines = []
    cur = 0
    for _f, _d, off, w in fields:
        if off > cur:
            lines.append("    char pad%02x[%d];" % (cur, off - cur))
            cur = off
        if w == 4:
            lines.append("    int nField%02x;            /* +0x%02x */" % (off, off))
        else:
            lines.append("    unsigned char bField%02x;   /* +0x%02x */" % (off, off))
        cur += w
    if cur < frame:
        lines.append("    char pad%02x[%d];" % (cur, frame - cur))
    struct = "typedef struct {\n%s\n} %sEmitParams;          /* 0x%x */\n" % (
        "\n".join(lines), pfx, frame)

    externs = []
    for f in sorted({o[0] for o in ops if o[0] != "CALL"}):
        externs.append("extern int %s(void *self, void *desc);" % f)
    externs.append("extern int %s(unsigned short id, %sEmitParams *params);" % (builder, pfx))
    externs.append("extern void %s(int target, int value);" % SINK)

    # Emit in the order the ROM performs the fetches. Some members fetch the
    # target and builder id FIRST and the operands after; hard-coding
    # operands-then-tail costs bytes on exactly those.
    body = []
    seen_regs = 0
    for f, d, off, w in ops:
        if f == "CALL":
            continue
        arg = "descs" if d == 0 else "descs + 0x%x" % d
        if off is None:
            lhs = "target" if seen_regs == 0 else "id"
            seen_regs += 1
            body.append("    %s = %s(self, %s);" % (lhs, f, arg))
        else:
            nm = ("nField%02x" if w == 4 else "bField%02x") % off
            body.append("    params.%s = %s(self, %s);" % (nm, f, arg))
    # The ROM keeps the builder id as a full word and truncates AT THE USE
    # (lsls/lsrs immediately before the call). Declaring id as unsigned short
    # truncates at the assignment instead, which reorders two instructions on
    # every member that fetches the id early.
    body.append("    %s(target, %s((unsigned short)id, &params));" % (SINK, builder))
    body.append("    return 1;")

    return "%s\n%s\n\nint %s(void *self, char *descs) {\n    %sEmitParams params;\n    int target;\n    int id;\n\n%s\n}\n" % (
        struct, "\n".join(externs), name, pfx, "\n".join(body))


def main():
    name = sys.argv[1]
    e, frame, ops, rel = analyse(name)
    src = emit(name, e, frame, ops, rel)
    out = os.path.join(ROOT, "build", "try", name + ".c")
    open(out, "w").write(src)
    print(out)
    print(src)


if __name__ == "__main__":
    main()
