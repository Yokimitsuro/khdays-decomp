#!/usr/bin/env python3
"""Compile and byte-check the semantically recovered MobiClip data tables."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile

from mobiclip_reference import (
    BLOCK4X4_COEFFICIENT_MASKS,
    BLOCK8X8_COEFFICIENT_MASKS,
    PACKED_AVERAGE_LANE_MASK,
    PFRAME_BLOCK4X4_COEFFICIENT_MASKS,
    PFRAME_BLOCK8X8_COEFFICIENT_MASKS,
    QUANT4X4,
    QUANT8X8,
    ZIGZAG4X4,
    ZIGZAG8X8,
)

ROOT = Path(__file__).resolve().parents[1]
PAYLOAD_BASE = 0x0208C8C4
PAYLOAD_SIZE = 0x659C
PAYLOAD_SHA256 = "5508ae5f765eb86e81b2ad8d76dccf6d4a30e3381d3e8b248fb8d4a6204b83f5"
MWCC = ROOT / "tools/mwccarm/3.0_patch4/mwccarm.exe"
LICENSE = ROOT / "tools/mwccarm/license.dat"


def flatten(rows) -> bytes:
    return bytes(value for row in rows for value in row)


def semantic_regions() -> list[tuple[int, str, bytes]]:
    return [
        (0x0208E188, "gMobiClipIFrameResidualPermutation", bytes(BLOCK8X8_COEFFICIENT_MASKS)),
        (0x0208E324, "gMobiClipPFrameResidualMask", bytes(PFRAME_BLOCK8X8_COEFFICIENT_MASKS)),
        (
            0x0208E6B8,
            "gMobiClipIntraCoefficientMaskPadded",
            bytes((0, *BLOCK4X4_COEFFICIENT_MASKS, 0, 0, 0)),
        ),
        (0x0208E788, "gMobiClipPFrameCoefficientMask", bytes(PFRAME_BLOCK4X4_COEFFICIENT_MASKS)),
        (0x02090F7C, "gMobiClipQuant8BaseMatrices", flatten(QUANT8X8)),
        (0x020910FC, "gMobiClipScan8", bytes(ZIGZAG8X8)),
        (0x0209113C, "gMobiClipQuant4BaseMatrices", flatten(QUANT4X4)),
        (0x0209119C, "gMobiClipScan4", bytes(ZIGZAG4X4)),
        (0x020911AC, "gMobiClipQpShift", bytes(qp // 6 for qp in range(54))),
        (0x020911E2, "gMobiClipQpMatrixSelector", bytes(qp % 6 for qp in range(54))),
        (
            0x02091E4C,
            "gMobiClipPackedAverageLaneMask",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x020925F8,
            "gMobiClipPackedAverageLaneMask1",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x02092AF4,
            "gMobiClipPackedAverageLaneMask2",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x02092D88,
            "gMobiClipPackedAverageLaneMask3",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
    ]


def format_array(name: str, data: bytes) -> str:
    rows = []
    for offset in range(0, len(data), 16):
        rows.append("    " + ", ".join(str(value) for value in data[offset:offset + 16]) + ",")
    return (
        f"unsigned char {name}[{len(data)}] = {{\n"
        + "\n".join(rows)
        + "\n};\n"
    )


def render_source(regions: list[tuple[int, str, bytes]]) -> str:
    body = "\n".join(format_array(name, data) for _, name, data in regions)
    return (
        '#pragma define_section mobiclip_semantic ".mobiclip_semantic" abs32 RWX\n'
        "#pragma section mobiclip_semantic begin\n\n"
        + body
        + "\n#pragma section mobiclip_semantic end\n"
    )


def run_probe(output_dir: Path, payload_path: Path) -> dict:
    regions = semantic_regions()
    expected = b"".join(data for _, _, data in regions)
    payload = payload_path.read_bytes()
    payload_digest = hashlib.sha256(payload).hexdigest()
    if len(payload) != PAYLOAD_SIZE or payload_digest != PAYLOAD_SHA256:
        raise ValueError(
            f"unexpected payload: size={len(payload):#x}, sha256={payload_digest}"
        )
    for address, name, expected_region in regions:
        start = address - PAYLOAD_BASE
        if payload[start:start + len(expected_region)] != expected_region:
            raise ValueError(f"semantic source does not match payload region {name}")
    output_dir.mkdir(parents=True, exist_ok=True)
    source = output_dir / "mobiclip_semantic_data_probe.c"
    obj = output_dir / "mobiclip_semantic_data_probe.o"
    binary = output_dir / "mobiclip_semantic_data_probe.bin"
    source.write_text(render_source(regions), encoding="ascii")

    environment = os.environ.copy()
    environment["LM_LICENSE_FILE"] = str(LICENSE)
    subprocess.run(
        [
            str(MWCC),
            "-O4,p",
            "-proc", "arm946e",
            "-interworking",
            "-lang", "c99",
            "-enum", "int",
            "-char", "signed",
            "-inline", "on,noauto",
            "-Cpp_exceptions", "off",
            "-gccext,on",
            "-w", "all",
            "-c",
            "-o", str(obj),
            str(source),
        ],
        cwd=ROOT,
        env=environment,
        check=True,
    )
    observed_regions = []
    compiled_region_records = []
    with obj.open("rb") as stream:
        elf = ELFFile(stream)
        symbols = elf.get_section_by_name(".symtab")
        for address, name, expected_region in regions:
            matches = symbols.get_symbol_by_name(name)
            if not matches or len(matches) != 1:
                raise ValueError(f"missing or duplicate ELF symbol: {name}")
            symbol = matches[0]
            section_index = symbol["st_shndx"]
            elf_section = elf.get_section(section_index)
            start = symbol["st_value"]
            observed_region = elf_section.data()[start:start + len(expected_region)]
            observed_regions.append(observed_region)
            compiled_region_records.append({
                "name": name,
                "payload_address": f"0x{address:08x}",
                "size": len(expected_region),
                "section_index": section_index,
                "section_name": elf_section.name,
                "section_flags": elf_section["sh_flags"],
                "expected_sha256": hashlib.sha256(expected_region).hexdigest(),
                "observed_sha256": hashlib.sha256(observed_region).hexdigest(),
                "matches": observed_region == expected_region,
            })
    observed = b"".join(observed_regions)
    binary.write_bytes(observed)
    manifest = {
        "schema_version": 1,
        "section": ".mobiclip_semantic",
        "section_flags": "RWX",
        "payload_sha256": payload_digest,
        "expected_size": len(expected),
        "observed_size": len(observed),
        "expected_sha256": hashlib.sha256(expected).hexdigest(),
        "observed_sha256": hashlib.sha256(observed).hexdigest(),
        "matches": observed == expected,
        "regions": compiled_region_records,
        "source": str(source.resolve()),
        "object": str(obj.resolve()),
        "binary": str(binary.resolve()),
    }
    manifest_path = output_dir / "mobiclip_semantic_data_probe.json"
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    if not manifest["matches"]:
        raise ValueError(
            f"compiled section mismatch: expected {len(expected)} bytes, "
            f"observed {len(observed)}"
        )
    return manifest


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--output-dir",
        type=Path,
        default=ROOT / "scratch/mobiclip/semantic-data-probe",
    )
    parser.add_argument(
        "--payload",
        type=Path,
        default=ROOT / "scratch/mobiclip/data_ov024_0208c8c4.bin",
    )
    args = parser.parse_args()
    manifest = run_probe(args.output_dir, args.payload)
    print(
        f"matched {manifest['observed_size']} compiled semantic data bytes "
        f"({manifest['observed_sha256']})"
    )


if __name__ == "__main__":
    main()
