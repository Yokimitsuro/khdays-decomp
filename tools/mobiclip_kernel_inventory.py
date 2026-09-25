#!/usr/bin/env python3
"""Code/DATA inventory of the MobiClip kernels that run in place from ov024 .rodata.

Besides the decoder payload copied to ITCM (tools/mobiclip_inventory.py), the
MobiClip library keeps two hand-written ARM blocks in its read-only data that the
player calls directly: the FastAudio decoder (0x02087318) and the deblocking
post-filter (0x02092e60). This walks every path from each block's entry points,
follows branches and calls, stops at computed or returning writes of pc, and
checks that the reachable instructions plus the declared embedded-DATA ranges
tile the block exactly -- no gap, no overlap.

    python tools/mobiclip_kernel_inventory.py            # both blocks
    python tools/mobiclip_kernel_inventory.py deblock --json
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs
from capstone import arm

ROOT = Path(__file__).resolve().parents[1]
OVERLAY = ROOT / "extract/dec/overlays/overlay_024.bin"
OVERLAY_BASE = 0x02082960

# name -> (start, end, entry points, embedded DATA ranges [start, end, label])
BLOCKS = {
    "fastaudio": (
        0x02087318, 0x020886C4,
        [0x02087318],
        [
            (0x0208731C, 0x0208741C, "gFastAudioReflection6Bit"),
            (0x0208741C, 0x0208749C, "gFastAudioReflection2"),
            (0x0208749C, 0x0208751C, "gFastAudioReflection3"),
            (0x0208751C, 0x0208755C, "gFastAudioReflection4"),
            (0x0208755C, 0x0208757C, "gFastAudioReflection6"),
            (0x0208757C, 0x0208759C, "gFastAudioReflection7"),
            (0x02087B08, 0x02087B48, "gFastAudioReflection5"),
            (0x02087D14, 0x02087D24, "gFastAudioSynthesisConstants"),
            (0x02087EC4, 0x020886C4, "gFastAudioExcitation"),
        ],
    ),
    "deblock": (
        0x02092E60, 0x020933AC,
        [0x02092E60],
        [
            (0x02092F44, 0x02092F69, "gMobiClipDeblockAlpha"),
            (0x02092F69, 0x02092F8E, "gMobiClipDeblockBeta"),
            (0x02092F8E, 0x02092F90, "gMobiClipDeblockPad"),
            (0x0209339C, 0x020933AC, "gMobiClipDeblockTailWords"),
        ],
    ),
}


def load_block(name: str):
    start, end, entries, data = BLOCKS[name]
    image = OVERLAY.read_bytes()
    return start, end, entries, data, image[start - OVERLAY_BASE:end - OVERLAY_BASE]


def walk(name: str) -> dict:
    start, end, entries, data, raw = load_block(name)
    md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
    md.detail = True
    code = set()
    pending = list(entries)
    calls = set()
    while pending:
        address = pending.pop()
        while True:
            if address in code:
                break
            if not start <= address < end:
                raise ValueError(f"{name}: path leaves the block at 0x{address:08x}")
            if any(lo <= address < hi for lo, hi, _ in data):
                raise ValueError(f"{name}: path runs into embedded DATA at 0x{address:08x}")
            word = raw[address - start:address - start + 4]
            insn = next(md.disasm(word, address), None)
            if insn is None:
                raise ValueError(f"{name}: undecodable word at 0x{address:08x}")
            code.add(address)
            conditional = insn.cc not in (arm.ARM_CC_AL, arm.ARM_CC_INVALID)
            mnemonic = insn.id
            if mnemonic in (arm.ARM_INS_B, arm.ARM_INS_BL):
                target = insn.operands[0].imm
                if mnemonic == arm.ARM_INS_BL:
                    calls.add(target)
                    pending.append(target)
                    address += 4
                    continue
                pending.append(target)
                if not conditional:
                    break
                address += 4
                continue
            writes_pc = arm.ARM_REG_PC in insn.regs_access()[1]
            if writes_pc:
                # pop {..., pc}, mov pc, lr, bx lr, ldr pc, [...]: the path ends here
                if not conditional:
                    break
            address += 4
    words = sorted(code)
    covered = len(words) * 4 + sum(hi - lo for lo, hi, _ in data)
    gaps = []
    cursor = start
    marks = sorted([(a, a + 4) for a in words] + [(lo, hi) for lo, hi, _ in data])
    for lo, hi in marks:
        if lo > cursor:
            gaps.append((cursor, lo))
        if lo < cursor:
            raise ValueError(f"{name}: overlap at 0x{lo:08x}")
        cursor = max(cursor, hi)
    if cursor < end:
        gaps.append((cursor, end))
    return {
        "name": name,
        "start": start,
        "end": end,
        "instructions": len(words),
        "embedded_data_bytes": sum(hi - lo for lo, hi, _ in data),
        "covered": covered,
        "size": end - start,
        "gaps": gaps,
        "calls": sorted(calls),
        "code": words,
    }


def main() -> None:
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or sorted(BLOCKS)
    ok = True
    for name in names:
        result = walk(name)
        if "--json" in sys.argv:
            print(json.dumps({k: v for k, v in result.items() if k != "code"}, indent=2))
        tiled = not result["gaps"] and result["covered"] == result["size"]
        ok &= tiled
        print(
            f"{name}: 0x{result['start']:08x}-0x{result['end']:08x} {result['size']} bytes = "
            f"{result['instructions']} instructions + {result['embedded_data_bytes']} DATA bytes"
            + ("" if tiled else f"; GAPS {[(hex(a), hex(b)) for a, b in result['gaps']]}")
        )
    raise SystemExit(0 if ok else 1)


if __name__ == "__main__":
    main()
