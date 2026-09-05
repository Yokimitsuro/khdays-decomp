#!/usr/bin/env python3
"""Rebuild and byte-verify every control-metadata region in MobiClip.

The retail payload stores dispatch destinations as signed offsets from the
start of each table.  MWCC cannot express ``target - table`` as a static C
initializer, so this probe emits symbolic ``R_ARM_REL32`` entries with GNU
as and resolves them with the project's real mwldarm linker.
"""

from __future__ import annotations

import argparse
import hashlib
import os
import shutil
import struct
import subprocess
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BASE = 0x0208C8C4
SIZE = 0x659C
SHA256 = "5508ae5f765eb86e81b2ad8d76dccf6d4a30e3381d3e8b248fb8d4a6204b83f5"
MWLDARM = ROOT / "tools/mwccarm/2.0/sp2p4/mwldarm.exe"
LICENSE = ROOT / "tools/mwccarm/license.dat"


@dataclass(frozen=True)
class RawPart:
    name: str
    address: int
    size: int


@dataclass(frozen=True)
class RelativeTable:
    name: str
    address: int
    count: int
    signed: bool = False
    relative_base: int | None = None

    @property
    def size(self) -> int:
        return self.count * 4

    @property
    def base(self) -> int:
        return self.address if self.relative_base is None else self.relative_base


@dataclass(frozen=True)
class Region:
    name: str
    start: int
    end: int
    parts: tuple[RawPart | RelativeTable, ...]

    @property
    def size(self) -> int:
        return self.end - self.start


REGIONS = (
    Region(
        "payload_header", 0x0208C8C8, 0x0208C8D0,
        (RawPart("payload_configuration", 0x0208C8C8, 8),),
    ),
    Region(
        "luma_interpolation_dispatch", 0x0208C8D0, 0x0208C910,
        (RelativeTable("luma_interpolation", 0x0208C8D0, 16),),
    ),
    Region(
        "chroma_interpolation_dispatch", 0x0208C910, 0x0208C950,
        (RelativeTable("chroma_interpolation", 0x0208C910, 16),),
    ),
    Region(
        "pframe_prefix_offsets_and_lengths", 0x0208CA44, 0x0208CA98,
        (
            RawPart("pframe_prefix_codes", 0x0208CA44, 32),
            RelativeTable("pframe_macroblock", 0x0208CA64, 10),
            RawPart("pframe_code_lengths", 0x0208CA8C, 12),
        ),
    ),
    Region(
        "luma_kernel_dispatch", 0x0208CBA4, 0x0208CBE4,
        (RelativeTable("motion16_dispatch", 0x0208CBA4, 16),),
    ),
    Region(
        "motion16_selector_and_offsets", 0x0208CCD8, 0x0208CD1C,
        (
            RawPart("motion16_selectors", 0x0208CCD8, 16),
            RelativeTable("motion16_modes", 0x0208CCE8, 10),
            RawPart("motion16_code_lengths", 0x0208CD10, 12),
        ),
    ),
    Region(
        "chroma_kernel_dispatch", 0x0208CDFC, 0x0208CE1C,
        (RelativeTable("motion8x16_dispatch", 0x0208CDFC, 8,
                       relative_base=0x0208CCE8),),
    ),
    Region(
        "motion8x16_selector_and_offsets", 0x0208CF10, 0x0208CF54,
        (
            RawPart("motion8x16_selectors", 0x0208CF10, 16),
            RelativeTable("motion8x16_modes", 0x0208CF20, 10),
            RawPart("motion8x16_code_lengths", 0x0208CF48, 12),
        ),
    ),
    Region(
        "chroma_narrow_kernel_dispatch", 0x0208D034, 0x0208D044,
        (RelativeTable("intra16_dispatch", 0x0208D034, 4,
                       relative_base=0x0208CF20),),
    ),
    Region(
        "intra16_selector_and_offsets", 0x0208D138, 0x0208D194,
        (
            RawPart("intra16_selectors", 0x0208D138, 32),
            RelativeTable("intra16_modes_a", 0x0208D158, 10),
            RawPart("intra16_code_lengths", 0x0208D180, 20),
        ),
    ),
    Region(
        "motion8x8_selector_and_offsets", 0x0208D25C, 0x0208D2A0,
        (
            RawPart("motion8x8_selectors", 0x0208D25C, 16),
            RelativeTable("intra16_modes_b", 0x0208D26C, 10),
            RawPart("motion8x8_code_lengths", 0x0208D294, 12),
        ),
    ),
    Region(
        "motion16x4_selector_and_offsets", 0x0208D380, 0x0208D3C4,
        (
            RawPart("motion16x4_selectors", 0x0208D380, 16),
            RelativeTable("motion16x8_modes_a", 0x0208D390, 10),
            RawPart("motion16x4_code_lengths", 0x0208D3B8, 12),
        ),
    ),
    Region(
        "motion16x2_selector_and_offsets", 0x0208D4A4, 0x0208D4E8,
        (
            RawPart("motion16x2_selectors", 0x0208D4A4, 16),
            RelativeTable("motion16x8_modes_b", 0x0208D4B4, 10),
            RawPart("motion16x2_code_lengths", 0x0208D4DC, 12),
        ),
    ),
    Region(
        "motion8x8_alt_selector_and_offsets", 0x0208D5B0, 0x0208D5F4,
        (
            RawPart("motion8x8_alt_selectors", 0x0208D5B0, 16),
            RelativeTable("motion16x8_modes_c", 0x0208D5C0, 10),
            RawPart("motion8x8_alt_code_lengths", 0x0208D5E8, 12),
        ),
    ),
    Region(
        "predicted_mode_a_selector_and_offsets", 0x0208D6D4, 0x0208D718,
        (
            RawPart("predicted_mode_a_selectors", 0x0208D6D4, 16),
            RelativeTable("predicted_intra_modes_a", 0x0208D6E4, 10),
            RawPart("predicted_mode_a_code_lengths", 0x0208D70C, 12),
        ),
    ),
    Region(
        "predicted_mode_b_selector_and_offsets", 0x0208D7F8, 0x0208D83C,
        (
            RawPart("predicted_mode_b_selectors", 0x0208D7F8, 16),
            RelativeTable("predicted_intra_modes_b", 0x0208D808, 10),
            RawPart("predicted_mode_b_code_lengths", 0x0208D830, 12),
        ),
    ),
    Region(
        "predicted_mode_c_selector_and_offsets", 0x0208D904, 0x0208D954,
        (
            RawPart("predicted_mode_c_selectors", 0x0208D904, 16),
            RelativeTable("predicted_intra_modes_c", 0x0208D914, 10),
            RawPart("predicted_mode_c_code_lengths", 0x0208D93C, 24),
        ),
    ),
    Region(
        "predicted_mode_d_selector_and_offsets", 0x0208DA34, 0x0208DA94,
        (
            RawPart("predicted_mode_d_selectors", 0x0208DA34, 32),
            RelativeTable("predicted_intra_modes_d", 0x0208DA54, 10),
            RawPart("predicted_mode_d_code_lengths", 0x0208DA7C, 24),
        ),
    ),
    Region(
        "predicted_mode_e_selector_and_offsets", 0x0208DB74, 0x0208DBC4,
        (
            RawPart("predicted_mode_e_selectors", 0x0208DB74, 16),
            RelativeTable("predicted_intra_modes_e", 0x0208DB84, 10),
            RawPart("predicted_mode_e_code_lengths", 0x0208DBAC, 24),
        ),
    ),
    Region(
        "predicted_mode_f_selector_and_offsets", 0x0208DC8C, 0x0208DCE4,
        (
            RawPart("predicted_mode_f_selectors", 0x0208DC8C, 32),
            RelativeTable("predicted_intra_modes_f", 0x0208DCAC, 10),
            RawPart("predicted_mode_f_code_lengths", 0x0208DCD4, 16),
        ),
    ),
    Region(
        "predicted_mode_g_selector_and_offsets", 0x0208DDAC, 0x0208DDF4,
        (
            RawPart("predicted_mode_g_selectors", 0x0208DDAC, 16),
            RelativeTable("predicted_intra_modes_g", 0x0208DDBC, 10),
            RawPart("predicted_mode_g_code_lengths", 0x0208DDE4, 16),
        ),
    ),
    Region(
        "predicted_mode_h_selector_and_offsets", 0x0208DEBC, 0x0208DF04,
        (
            RawPart("predicted_mode_h_selectors", 0x0208DEBC, 8),
            RelativeTable("predicted_intra_modes_h", 0x0208DEC4, 10),
            RawPart("predicted_mode_h_code_lengths", 0x0208DEEC, 24),
        ),
    ),
    Region(
        "intra_prediction_dispatch", 0x0208E4DC, 0x0208E52C,
        (RelativeTable("intra_prediction", 0x0208E4DC, 20),),
    ),
    Region(
        "intra8_neighbor_dispatch", 0x0208F2F8, 0x0208F308,
        (RelativeTable("intra8_neighbor", 0x0208F2F8, 4, signed=True),),
    ),
    Region(
        "intra4_neighbor_dispatch", 0x020902AC, 0x020902BC,
        (RelativeTable("intra4_neighbor", 0x020902AC, 4, signed=True),),
    ),
)


def validate_layout() -> None:
    if sum(region.size for region in REGIONS) != 1568:
        raise ValueError("control metadata no longer totals 1568 bytes")
    for region in REGIONS:
        cursor = region.start
        for part in region.parts:
            if part.address != cursor:
                raise ValueError(f"gap or overlap before {part.name}")
            cursor += part.size
        if cursor != region.end:
            raise ValueError(f"parts do not cover {region.name}")


def load_payload(path: Path) -> bytes:
    payload = path.read_bytes()
    digest = hashlib.sha256(payload).hexdigest()
    if len(payload) != SIZE or digest != SHA256:
        raise ValueError(f"unexpected payload: size={len(payload):#x}, sha256={digest}")
    return payload


def payload_slice(payload: bytes, address: int, size: int) -> bytes:
    return payload[address - BASE:address - BASE + size]


def target_symbol(address: int) -> str:
    return f"MobiClip_Code_{address:08X}"


def table_entries(payload: bytes, table: RelativeTable) -> list[tuple[int, int | None]]:
    entries = []
    fmt = "<i" if table.signed else "<I"
    for index in range(table.count):
        offset = struct.unpack_from(fmt, payload, table.address - BASE + index * 4)[0]
        if not table.signed and offset == 0:
            entries.append((offset, None))
        else:
            entries.append((offset, table.base + offset))
    return entries


def byte_directive(data: bytes) -> str:
    return "    .byte " + ", ".join(f"0x{value:02x}" for value in data)


def render_assembly(payload: bytes) -> tuple[str, set[int]]:
    lines = ["    .syntax unified", "    .arch armv5te", ""]
    targets: set[int] = set()
    for region in REGIONS:
        section = f".mobiclip_control_{region.start:08x}"
        symbol = f"gMobiClip_{region.name}"
        lines += [
            f'    .section {section},"axw",%progbits',
            "    .align 2",
            f"    .global {symbol}",
            f"    .type {symbol}, %object",
            f"{symbol}:",
        ]
        for part in region.parts:
            lines.append(f"    /* {part.name} @ 0x{part.address:08x} */")
            if isinstance(part, RawPart):
                data = payload_slice(payload, part.address, part.size)
                for offset in range(0, len(data), 16):
                    lines.append(byte_directive(data[offset:offset + 16]))
                continue
            table_label = f"gMobiClip_{part.name}"
            lines += [f"    .global {table_label}", f"{table_label}:"]
            for index, (offset, target) in enumerate(table_entries(payload, part)):
                if target is None:
                    lines.append("    .word 0 /* reserved */")
                else:
                    targets.add(target)
                    entry_address = part.address + index * 4
                    correction = entry_address - part.base
                    suffix = f" + {correction:#x}" if correction else ""
                    lines.append(
                        f"    .word {target_symbol(target)} - .{suffix}"
                    )
        lines += [f"    .size {symbol}, . - {symbol}", ""]
    return "\n".join(lines), targets


def render_lcf(targets: set[int]) -> str:
    lines = ["MEMORY {"]
    for index, region in enumerate(REGIONS):
        lines.append(
            f"    META{index} : ORIGIN = 0x{region.start:08X} > {region.name}.bin"
        )
    lines += ["}", "", "SECTIONS {", f"    __startup = 0x{BASE:08X};"]
    for address in sorted(targets):
        lines.append(f"    {target_symbol(address)} = 0x{address:08X};")
    lines.append("")
    for index, region in enumerate(REGIONS):
        section = f".mobiclip_control_{region.start:08x}"
        lines += [
            f"    .meta{index} : {{",
            "        ALIGNALL(4);",
            f"        control_metadata.o({section})",
            f"    }} > META{index}",
        ]
    lines += ["}", ""]
    return "\n".join(lines)


def find_assembler() -> str:
    configured = shutil.which("arm-none-eabi-as")
    if configured:
        return configured
    candidates = sorted(Path("C:/Program Files (x86)").glob(
        "Arm GNU Toolchain arm-none-eabi/*/bin/arm-none-eabi-as.exe"
    ))
    if not candidates:
        raise FileNotFoundError("arm-none-eabi-as was not found")
    return str(candidates[0])


def run(command: list[str], *, cwd: Path, env: dict[str, str] | None = None) -> None:
    completed = subprocess.run(command, cwd=cwd, env=env, text=True)
    if completed.returncode:
        raise subprocess.CalledProcessError(completed.returncode, command)


def build_and_verify(payload: bytes, output_dir: Path) -> dict[str, object]:
    validate_layout()
    output_dir.mkdir(parents=True, exist_ok=True)
    assembly, targets = render_assembly(payload)
    lcf = render_lcf(targets)
    asm_path = output_dir / "control_metadata.s"
    obj_path = output_dir / "control_metadata.o"
    lcf_path = output_dir / "control_metadata.lcf"
    elf_path = output_dir / "control_metadata.elf"
    asm_path.write_text(assembly, encoding="utf-8", newline="\n")
    lcf_path.write_text(lcf, encoding="utf-8", newline="\n")

    run([find_assembler(), "-march=armv5te", "-o", str(obj_path), str(asm_path)], cwd=ROOT)
    env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
    run([
        str(MWLDARM), "-proc", "arm946e", "-nodead", "-nostdlib",
        "-map", "closure,unused", "-msgstyle", "gcc", "-o", str(elf_path),
        str(lcf_path), str(obj_path),
    ], cwd=ROOT, env=env)

    records = []
    for region in REGIONS:
        output = output_dir / f"{region.name}.bin"
        observed = output.read_bytes()
        expected = payload_slice(payload, region.start, region.size)
        if observed != expected:
            mismatch = next(
                index for index, (left, right) in enumerate(zip(observed, expected))
                if left != right
            ) if len(observed) == len(expected) else min(len(observed), len(expected))
            raise ValueError(
                f"{region.name} mismatch at +{mismatch:#x}: "
                f"linked={len(observed):#x}, expected={len(expected):#x}"
            )
        records.append({
            "name": region.name,
            "address": f"0x{region.start:08x}",
            "size": region.size,
            "sha256": hashlib.sha256(observed).hexdigest(),
            "matches_payload": True,
        })
    return {
        "control_metadata_bytes": sum(item["size"] for item in records),
        "relative_target_count": len(targets),
        "regions": records,
        "assembly": str(asm_path),
        "linked_elf": str(elf_path),
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--payload", type=Path,
        default=ROOT / "scratch/mobiclip/data_ov024_0208c8c4.bin",
    )
    parser.add_argument(
        "--output-dir", type=Path,
        default=ROOT / "scratch/mobiclip/control-metadata-probe",
    )
    args = parser.parse_args()
    result = build_and_verify(load_payload(args.payload), args.output_dir)
    print(
        f"matched {result['control_metadata_bytes']} linked control metadata bytes "
        f"across {len(result['regions'])} regions"
    )
    print(f"relative targets: {result['relative_target_count']}")
    print(f"linked ELF: {result['linked_elf']}")


if __name__ == "__main__":
    main()
