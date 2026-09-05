#!/usr/bin/env python3
"""Extract and sanity-check ov024's position-independent MobiClip payload.

The output is analysis material derived from the user's ROM and must stay in an
ignored local directory. This helper contains no original payload bytes.
"""
import argparse
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
OVERLAY_BASE = 0x02082960
PAYLOAD_BASE = 0x0208C8C4
PAYLOAD_SIZE = 0x659C
EXPECTED_ENTRY_OFFSET = 0x16F0
DECODE_TABLE_SIZE = 0x2100
DECODE_TABLES = (
    ("coefficient_table_1", 0x020886C4),
    ("coefficient_table_0", 0x0208A7C4),
)


def decode_arm_branch(word, address):
    if word & 0x0E000000 != 0x0A000000:
        raise ValueError(f"first word is not an ARM B/BL instruction: {word:#010x}")
    displacement = (word & 0x00FFFFFF) << 2
    if displacement & 0x02000000:
        displacement -= 0x04000000
    return address + 8 + displacement


def extract(source, output):
    overlay = source.read_bytes()
    offset = PAYLOAD_BASE - OVERLAY_BASE
    end = offset + PAYLOAD_SIZE
    if end > len(overlay):
        raise ValueError(
            f"overlay too short: need {end:#x} bytes, found {len(overlay):#x}"
        )
    payload = overlay[offset:end]
    first_word = int.from_bytes(payload[:4], "little")
    entry = decode_arm_branch(first_word, PAYLOAD_BASE)
    expected_entry = PAYLOAD_BASE + EXPECTED_ENTRY_OFFSET
    if entry != expected_entry:
        raise ValueError(f"entry mismatch: decoded {entry:#010x}, expected {expected_entry:#010x}")

    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(payload)
    decode_tables = []
    for name, address in DECODE_TABLES:
        table_offset = address - OVERLAY_BASE
        table_end = table_offset + DECODE_TABLE_SIZE
        if table_end > len(overlay):
            raise ValueError(
                f"overlay too short for {name}: need {table_end:#x} bytes, "
                f"found {len(overlay):#x}"
            )
        table = overlay[table_offset:table_end]
        table_path = output.with_name(f"{name}_{address:08x}.bin")
        table_path.write_bytes(table)
        decode_tables.append(
            {
                "name": name,
                "address": f"0x{address:08x}",
                "size": f"0x{DECODE_TABLE_SIZE:x}",
                "sha256": hashlib.sha256(table).hexdigest(),
                "lookup_sha256": hashlib.sha256(table[:0x2000]).hexdigest(),
                "residue_sha256": hashlib.sha256(table[0x2000:]).hexdigest(),
                "path": str(table_path.resolve()),
                "layout": "4096 little-endian uint16 VLC entries + 256 residue bytes",
                "packed_entry": {
                    "bits_0_3": "consumed bits including coefficient sign",
                    "bits_4_8": "level magnitude",
                    "bits_9_14": "run",
                    "bit_15": "last",
                },
                "escape_prefix": "top seven reservoir bits equal 0b0000011",
            }
        )
    manifest = {
        "schema_version": 3,
        "source": str(source.resolve()),
        "source_sha256": hashlib.sha256(overlay).hexdigest(),
        "overlay_base": f"0x{OVERLAY_BASE:08x}",
        "payload_base": f"0x{PAYLOAD_BASE:08x}",
        "payload_size": f"0x{PAYLOAD_SIZE:x}",
        "payload_sha256": hashlib.sha256(payload).hexdigest(),
        "first_arm_word": f"0x{first_word:08x}",
        "entry_offset": f"0x{EXPECTED_ENTRY_OFFSET:x}",
        "entry_address": f"0x{entry:08x}",
        "architecture": "ARMv5TE little-endian ARM mode",
        "decode_tables": decode_tables,
    }
    manifest_path = output.with_suffix(output.suffix + ".json")
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    return manifest, manifest_path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--source",
        type=Path,
        default=ROOT / "dsd_extract" / "arm9_overlays" / "ov024.bin",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=ROOT / "scratch" / "mobiclip" / "data_ov024_0208c8c4.bin",
    )
    args = parser.parse_args()
    manifest, manifest_path = extract(args.source, args.output)
    print(f"payload: {args.output} ({PAYLOAD_SIZE:#x} bytes)")
    print(f"sha256: {manifest['payload_sha256']}")
    print(f"entry: {manifest['entry_address']} (base + {manifest['entry_offset']})")
    for table in manifest["decode_tables"]:
        print(f"{table['name']}: {table['path']} ({table['sha256']})")
    print(f"manifest: {manifest_path}")


if __name__ == "__main__":
    main()
