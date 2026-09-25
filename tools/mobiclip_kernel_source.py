#!/usr/bin/env python3
"""Render a MobiClip in-place kernel as checked-in ARM mnemonic source.

Takes the code/DATA partition proved by tools/mobiclip_kernel_inventory.py and
writes one labelled mnemonic per instruction (every branch and call target
symbolic), the embedded tables as named byte runs, and the block symbol the
player's code calls. The output is the starting point of the source; the
checked-in file is what tools/verify_executable_data.py proves.

    python tools/mobiclip_kernel_source.py deblock func_ov024_02092e60_unk out.s
"""

from __future__ import annotations

import sys
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs
from capstone import arm

import mobiclip_kernel_inventory as inv

ROUTINE_NAMES = {
    "fastaudio": {
        0x02087318: "FastAudio_DecodeBlock (entry: branch over the quantiser tables)",
        0x0208759C: "FastAudio_ParseBlock",
        0x02087B48: "FastAudio_ExpandSubBlock",
        0x02087D24: "FastAudio_DecodeBlockBody",
    },
    "deblock": {
        0x02092E60: "MobiClip_DeblockFrame",
        0x02092F90: "MobiClip_DeblockLumaVerticalEdges",
        0x020930C8: "MobiClip_DeblockLumaHorizontalEdges",
        0x020931BC: "MobiClip_DeblockChromaVerticalEdges",
        0x020932C4: "MobiClip_DeblockChromaHorizontalEdges",
    },
}


def label(address: int) -> str:
    return "MobiClip_Code_%08X" % address


def render(name: str, symbol: str, comments: dict[str, str] | None = None) -> str:
    result = inv.walk(name)
    start, end, _, data, raw = inv.load_block(name)
    code = set(result["code"])
    md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
    md.detail = True
    routines = ROUTINE_NAMES.get(name, {})
    comments = comments or {}
    out = [
        "    .syntax unified",
        "    .arch armv5te",
        '    .section .rodata,"a",%progbits',
        "    .arm",
        "    .align 2",
        f"    .global {symbol}",
        f"    .type {symbol}, %object",
        f"{symbol}:",
    ]
    address = start
    while address < end:
        region = next(((lo, hi, tag) for lo, hi, tag in data if lo == address), None)
        if region:
            lo, hi, tag = region
            if tag in comments:
                out.append(f"    /* {comments[tag]} */")
            out += [f"    .global {tag}", f"    .type {tag}, %object", f"{tag}:"]
            chunk = raw[lo - start:hi - start]
            for i in range(0, len(chunk), 16):
                out.append("    .byte " + ", ".join("0x%02x" % b for b in chunk[i:i + 16]))
            address = hi
            continue
        if address not in code:
            raise ValueError(f"0x{address:08x} is neither code nor declared DATA")
        if address in routines:
            out.append(f"    /* {routines[address]} */")
        insn = next(md.disasm(raw[address - start:address - start + 4], address))
        text = f"{insn.mnemonic} {insn.op_str}".strip()
        if insn.id in (arm.ARM_INS_B, arm.ARM_INS_BL):
            text = f"{insn.mnemonic} {label(insn.operands[0].imm)}"
        out.append(f"{label(address)}:")
        out.append(f"    {text}")
        address += 4
    out.append(f"    .size {symbol}, . - {symbol}")
    return "\n".join(out) + "\n"


def main() -> None:
    if len(sys.argv) != 4:
        raise SystemExit(__doc__)
    name, symbol, output = sys.argv[1:]
    Path(output).write_text(render(name, symbol), encoding="ascii", newline="\n")
    print(output)


if __name__ == "__main__":
    main()
