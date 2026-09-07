#!/usr/bin/env python3
"""Emit -- or re-validate -- a mnemonic assembly stub for a ROM function.

A few routines in this ROM are not compiler output. They cannot be recovered as
C, but they can still be checked in as source rather than as a gap: one readable
ARM mnemonic per ROM word, inside CodeWarrior's whole-function `asm` syntax. No
`incbin`, no `.inst`, no numeric opcode words.

    python tools/gen_asm_stub.py <function>              # print the source
    python tools/gen_asm_stub.py <function> -o <path>    # write it
    python tools/gen_asm_stub.py <function> --check <path>

Both writing and checking assemble the result with the project's compiler and
compare it byte for byte against build/func_index.json, so a stub in the tree
stays revalidable rather than being trusted on the word of whoever made it.

The generator only translates; it does not name anything. Give the function its
semantic name, prototype and types in Ghidra as usual, and put the algorithm in
the stub's header so the port does not have to read the assembly.
"""
import argparse
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

from match import FLAGS, LIC, MWCC, text_relocs  # noqa: E402
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM  # noqa: E402

NL = "\n"
ALIAS = {"sb": "r9", "sl": "r10", "fp": "r11", "ip": "r12"}
SHIFT = re.compile(r"^(lsl|lsr|asr|ror)(\w*)$")
ONE_REG = re.compile(r"^\{(r\d+)\}$")


def rom_bytes(function):
    with open(os.path.join(ROOT, "build", "func_index.json"), encoding="utf-8") as fh:
        index = json.load(fh)
    if function not in index:
        raise SystemExit("not in build/func_index.json: " + function)
    entry = index[function]
    if entry.get("mode") != "arm":
        raise SystemExit("only ARM functions are supported: " + function)
    return bytes.fromhex(entry["hex"])


def to_mnemonics(rom):
    """One source line per ROM word, in CodeWarrior's assembler syntax."""
    md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
    ins = list(md.disasm(rom, 0))
    if len(ins) * 4 != len(rom):
        raise SystemExit("function does not disassemble cleanly to ARM words")

    labels = {}
    for i in ins:
        if i.mnemonic.startswith("b") and i.op_str.startswith("#"):
            labels[int(i.op_str[1:], 0)] = "L%03x" % int(i.op_str[1:], 0)

    lines = []
    for i in ins:
        if i.address in labels:
            lines.append(labels[i.address] + ":")
        mnem = i.mnemonic
        ops = re.sub(r"\b(sb|sl|fp|ip)\b", lambda m: ALIAS[m.group(1)], i.op_str)

        # Capstone prints UAL shifts; CodeWarrior wants the mov form.
        shift = SHIFT.match(mnem)
        if shift:
            parts = [p.strip() for p in ops.split(",")]
            mnem = "mov" + shift.group(2)
            ops = "%s, %s, %s %s" % (parts[0], parts[1], shift.group(1), parts[2])

        if mnem.startswith("b") and ops.startswith("#"):
            ops = labels[int(ops[1:], 0)]

        # A one-register push or pop is a single load/store, not an LDM/STM.
        one = ONE_REG.match(ops.replace(" ", ""))
        if one and mnem in ("push", "pop"):
            reg = one.group(1)
            mnem, ops = (("str", reg + ", [sp, #-4]!") if mnem == "push"
                         else ("ldr", reg + ", [sp], #4"))
        elif mnem.startswith("push"):
            mnem, ops = "stmfd" + mnem[4:], "sp!, " + ops
        elif mnem.startswith("pop"):
            mnem, ops = "ldmfd" + mnem[3:], "sp!, " + ops

        lines.append("    %-9s %s" % (mnem, ops))
    return NL.join(lines)


def render(function, body, header=None):
    note = header or (
        "/* %s: not compiler output. Checked in as one readable mnemonic per\n"
        " * ROM word -- no incbin, no .inst, no opcode words. Regenerate or\n"
        " * re-validate with tools/gen_asm_stub.py.\n"
        " */" % function)
    return "%s%svoid %s(void);%s%sasm void %s(void)%s{%s%s%s}%s" % (
        note, NL * 2, function, NL * 2, "", function, NL, NL, body, NL, NL)


def assemble(source):
    tmp = os.path.join(ROOT, "build", "try", "_asmstub_check.c")
    obj = tmp + ".o"
    os.makedirs(os.path.dirname(tmp), exist_ok=True)
    if os.path.exists(obj):
        os.remove(obj)
    with open(tmp, "w", newline=NL, encoding="utf-8") as fh:
        fh.write(source)
    env = dict(os.environ, LM_LICENSE_FILE=LIC, MWCIncludes=".")
    run = subprocess.run([MWCC, "-c"] + list(FLAGS) + ["-o", obj, tmp],
                         capture_output=True, env=env, text=True)
    if not os.path.exists(obj):
        raise SystemExit("assembly failed:\n" + run.stdout + run.stderr)
    text, relocs = text_relocs(obj)
    return bytes(text), relocs


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("function")
    ap.add_argument("-o", "--out", help="write the stub here")
    ap.add_argument("--check", help="re-validate an existing stub instead")
    args = ap.parse_args()

    rom = rom_bytes(args.function)

    if args.check:
        with open(args.check, encoding="utf-8", newline="") as fh:
            source = fh.read().replace("\r\n", NL)
        built, relocs = assemble(source)
        ok = built == rom
        print("%s: %s (%d bytes, %d relocations)"
              % (args.check, "byte-exact" if ok else "DIFFERS",
                 len(built), len(relocs)))
        return 0 if ok else 1

    body = to_mnemonics(rom)
    source = render(args.function, body)
    built, relocs = assemble(source)
    if built != rom:
        raise SystemExit("generated stub is not byte-exact; do not check it in")
    print("byte-exact: %d bytes, %d relocations" % (len(built), len(relocs)),
          file=sys.stderr)
    if args.out:
        with open(args.out, "w", newline=NL, encoding="utf-8") as fh:
            fh.write(source)
        print("wrote " + args.out, file=sys.stderr)
    else:
        sys.stdout.write(source)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
