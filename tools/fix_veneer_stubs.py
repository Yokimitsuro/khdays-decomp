#!/usr/bin/env python3
"""Rewrite `asm void` blocks whose ARM code is written as `dcd 0xNNNNNNNN`.

mwccarm places a `$d` (data) mapping symbol at the start of any block
that begins with `dcd`. mwld then treats the whole block as data and
inserts an interworking veneer when a caller resolves an extern in that
block across an ARM/THUMB boundary — shifting all subsequent bytes and
breaking byte-exactness.

Rewriting the leading `dcd 0xNNNNNNNN` lines (whose values encode ARM
instructions) as their actual mnemonics puts `$a` at 0 and `$d` only at
the point where real data begins, matching the delink baseline and
suppressing the spurious veneer.
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

# Map of ARM opcodes we see in these stubs to their mnemonic. Extend as
# new patterns show up.
ARM_OPS = {
    0xE59FC000: "ldr ip, [pc, #0]",
    0xE59FC004: "ldr ip, [pc, #4]",
    0xE59FC008: "ldr ip, [pc, #8]",
    0xE59FC00C: "ldr ip, [pc, #12]",
    0xE59F1000: "ldr r1, [pc, #0]",
    0xE59F1004: "ldr r1, [pc, #4]",
    0xE59F1008: "ldr r1, [pc, #8]",
    0xE59F100C: "ldr r1, [pc, #12]",
    0xE3A00000: "mov r0, #0",
    0xE3A00001: "mov r0, #1",
    0xE12FFF1C: "bx  ip",
    0xE12FFF11: "bx  r1",
    0xE12FFF10: "bx  r0",
}

DCD_HEX = re.compile(r"(?P<indent>\s+)dcd\s+0x([0-9a-fA-F]{8})\s*$", re.MULTILINE)


def rewrite(text):
    lines = text.splitlines(keepends=True)
    out = []
    changed = False
    for line in lines:
        m = DCD_HEX.match(line.rstrip("\n"))
        if m:
            val = int(m.group(2), 16)
            mnem = ARM_OPS.get(val)
            if mnem is not None:
                out.append(f"{m.group('indent')}{mnem}\n")
                changed = True
                continue
        out.append(line)
    return "".join(out), changed


fixed = 0
for c_file in list((ROOT / "libs").rglob("*.c")) + list((ROOT / "src").rglob("*.c")):
    text = c_file.read_text(encoding="utf-8", errors="replace")
    new_text, changed = rewrite(text)
    if changed:
        c_file.write_text(new_text, encoding="utf-8", newline="\n")
        fixed += 1

print(f"rewrote {fixed} files")
