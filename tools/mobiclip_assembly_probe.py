#!/usr/bin/env python3
"""Reassemble the carved MobiClip ARM ranges from readable mnemonics.

Generated source and binaries stay under ignored scratch storage. Code is
emitted as ARM instructions with an explicit label at every instruction.
Interleaved DATA is emitted as named constants and symbolic relative dispatch
entries using the same semantic definitions as the two dedicated DATA probes.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import shutil
import subprocess
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_GRP_CALL, CS_GRP_JUMP, CS_MODE_ARM, CS_MODE_LITTLE_ENDIAN
from capstone import Cs
from capstone.arm import ARM_OP_IMM

from mobiclip_control_metadata_probe import (
    REGIONS as CONTROL_REGIONS,
    RawPart,
    RelativeTable,
    table_entries,
)
from mobiclip_semantic_data_probe import semantic_regions


ROOT = Path(__file__).resolve().parents[1]
BASE = 0x0208C8C4
SIZE = 0x659C
SHA256 = "5508ae5f765eb86e81b2ad8d76dccf6d4a30e3381d3e8b248fb8d4a6204b83f5"


def find_tool(name: str) -> str:
    configured = shutil.which(name)
    if configured:
        return configured
    candidates = sorted(Path("C:/Program Files (x86)").glob(
        f"Arm GNU Toolchain arm-none-eabi/*/bin/{name}.exe"
    ))
    if not candidates:
        raise FileNotFoundError(f"{name} was not found")
    return str(candidates[0])


def byte_directives(data: bytes) -> list[str]:
    return [
        "    .byte " + ", ".join(f"0x{value:02x}" for value in data[offset:offset + 16])
        for offset in range(0, len(data), 16)
    ]


def render_one_data_region(payload: bytes, start: int, end: int) -> list[str]:
    control = {region.start: region for region in CONTROL_REGIONS}.get(start)
    semantic = {
        address: (name, data) for address, name, data in semantic_regions()
    }.get(start)
    if control is not None:
        if control.end != end:
            raise ValueError(f"control region boundary mismatch at {start:#x}")
        symbol = f"gMobiClip_{control.name}"
        lines = [
            f"    /* control metadata {start:#010x}..{end:#010x} */",
            f"    .global {symbol}",
            f"    .type {symbol}, %object",
            f"{symbol}:",
        ]
        for part in control.parts:
            lines.append(f"    /* {part.name} */")
            if isinstance(part, RawPart):
                offset = part.address - BASE
                lines.extend(byte_directives(payload[offset:offset + part.size]))
                continue
            assert isinstance(part, RelativeTable)
            table_symbol = f"gMobiClip_{part.name}"
            lines += [f"    .global {table_symbol}", f"{table_symbol}:"]
            for index, (_offset, target) in enumerate(table_entries(payload, part)):
                if target is None:
                    lines.append("    .word 0 /* reserved */")
                    continue
                entry_address = part.address + index * 4
                correction = entry_address - part.base
                suffix = f" + {correction:#x}" if correction else ""
                lines.append(
                    f"    .word MobiClip_Code_{target:08X} - .{suffix}"
                )
        lines.append(f"    .size {symbol}, . - {symbol}")
        return lines
    if semantic is not None:
        name, data = semantic
        if start + len(data) != end:
            raise ValueError(f"semantic region boundary mismatch at {start:#x}")
        return [
            f"    /* semantic constants {start:#010x}..{end:#010x} */",
            f"    .global {name}",
            f"    .type {name}, %object",
            f"{name}:",
            *byte_directives(data),
            f"    .size {name}, . - {name}",
        ]
    raise ValueError(f"unclassified embedded DATA region {start:#x}..{end:#x}")


def render_data_range(payload: bytes, start: int, end: int) -> list[str]:
    boundaries = {region.start: region.end for region in CONTROL_REGIONS}
    boundaries.update(
        (address, address + len(data))
        for address, _name, data in semantic_regions()
    )
    lines: list[str] = []
    cursor = start
    while cursor < end:
        region_end = boundaries.get(cursor)
        if region_end is None or region_end > end:
            raise ValueError(f"no semantic DATA region starts at {cursor:#x}")
        lines.extend(render_one_data_region(payload, cursor, region_end))
        cursor = region_end
    return lines


def render(payload: bytes, inventory: dict) -> tuple[str, int]:
    engine = Cs(CS_ARCH_ARM, CS_MODE_ARM | CS_MODE_LITTLE_ENDIAN)
    engine.detail = True
    lines = [
        "    .syntax unified",
        "    .arch armv5te",
        '    .section .rodata,"a",%progbits',
        "    .arm",
        "    .align 2",
        "    .global data_ov024_0208c8c4",
        "    .type data_ov024_0208c8c4, %object",
        "data_ov024_0208c8c4:",
    ]
    instruction_count = 0
    for item in inventory["ranges"]:
        start = int(item["start"], 0)
        end = int(item["end"], 0)
        data = payload[start - BASE:end - BASE]
        if item["classification"] != "arm_code":
            lines.extend(render_data_range(payload, start, end))
            continue
        instructions = list(engine.disasm(data, start))
        if len(instructions) * 4 != len(data):
            raise ValueError(f"Capstone did not cover code range {start:#x}..{end:#x}")
        for instruction in instructions:
            lines.append(f"MobiClip_Code_{instruction.address:08X}:")
            operand = instruction.op_str
            if instruction.group(CS_GRP_JUMP) or instruction.group(CS_GRP_CALL):
                immediate = next(
                    (op.imm for op in instruction.operands if op.type == ARM_OP_IMM),
                    None,
                )
                if immediate is not None and BASE <= immediate < BASE + SIZE:
                    operand = f"MobiClip_Code_{immediate:08X}"
            suffix = f" {operand}" if operand else ""
            lines.append(f"    {instruction.mnemonic}{suffix}")
            instruction_count += 1
    lines += [
        "    .size data_ov024_0208c8c4, . - data_ov024_0208c8c4",
        "",
    ]
    return "\n".join(lines), instruction_count


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--payload", type=Path,
        default=ROOT / "scratch/mobiclip/data_ov024_0208c8c4.bin",
    )
    parser.add_argument(
        "--inventory", type=Path,
        default=ROOT / "scratch/mobiclip/mobiclip_inventory.json",
    )
    parser.add_argument(
        "--output-dir", type=Path,
        default=ROOT / "scratch/mobiclip/assembly-probe",
    )
    parser.add_argument(
        "--source-output", type=Path,
        help="also write the deterministic mnemonic source to this path",
    )
    args = parser.parse_args()
    payload = args.payload.read_bytes()
    digest = hashlib.sha256(payload).hexdigest()
    if len(payload) != SIZE or digest != SHA256:
        raise ValueError(f"unexpected payload size/hash: {len(payload):#x}, {digest}")
    inventory = json.loads(args.inventory.read_text(encoding="utf-8"))
    source_text, instruction_count = render(payload, inventory)
    if instruction_count != 5899:
        raise ValueError(f"expected 5899 instructions, got {instruction_count}")

    args.output_dir.mkdir(parents=True, exist_ok=True)
    source = args.output_dir / "mobiclip_payload.s"
    obj = args.output_dir / "mobiclip_payload.o"
    rebuilt = args.output_dir / "mobiclip_payload.bin"
    source.write_text(source_text, encoding="ascii", newline="\n")
    if args.source_output is not None:
        args.source_output.parent.mkdir(parents=True, exist_ok=True)
        args.source_output.write_text(source_text, encoding="ascii", newline="\n")
    subprocess.run([
        find_tool("arm-none-eabi-as"), "-mcpu=arm946e-s", "-o", str(obj), str(source),
    ], check=True)
    subprocess.run([
        find_tool("arm-none-eabi-objcopy"), "-O", "binary",
        "--only-section=.rodata", str(obj), str(rebuilt),
    ], check=True)
    actual = rebuilt.read_bytes()
    if actual != payload:
        mismatch = next(
            index for index, (left, right) in enumerate(zip(actual, payload))
            if left != right
        )
        raise ValueError(
            f"reassembled payload differs at {BASE + mismatch:#010x}: "
            f"got {actual[mismatch:mismatch + 4].hex()}, "
            f"expected {payload[mismatch:mismatch + 4].hex()}"
        )
    print(f"reassembled {instruction_count} ARM instructions and {SIZE:#x} total bytes")
    print(f"sha256: {hashlib.sha256(actual).hexdigest()}")
    print(f"source: {source}")
    if args.source_output is not None:
        print(f"checked-in candidate: {args.source_output}")


if __name__ == "__main__":
    main()
