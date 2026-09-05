#!/usr/bin/env python3
"""Replay a DeSmuME MobiClip capture against the semantic decoder."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import mobiclip_reference


ROOT = Path(__file__).resolve().parents[1]


def split_native_chroma(data: bytes, width: int, height: int) -> tuple[bytes, bytes]:
    """Split native [plane0|plane1] rows into compact half-resolution planes."""
    row_width = width // 2
    rows = height // 2
    if len(data) != width * rows:
        raise ValueError("native chroma buffer has the wrong size")
    first = b"".join(data[y * width:y * width + row_width] for y in range(rows))
    second = b"".join(
        data[y * width + row_width:(y + 1) * width] for y in range(rows)
    )
    return first, second


def join_native_chroma(
    first: bytes, second: bytes, width: int, height: int,
) -> bytes:
    """Join compact half-resolution planes into native side-by-side rows."""
    row_width = width // 2
    rows = height // 2
    expected = row_width * rows
    if len(first) != expected or len(second) != expected:
        raise ValueError("compact chroma plane has the wrong size")
    return b"".join(
        first[y * row_width:(y + 1) * row_width]
        + second[y * row_width:(y + 1) * row_width]
        for y in range(rows)
    )


def decoder_return_bytes(bits_consumed: int) -> int:
    """Convert the word-oriented reader position to the native byte return."""
    return ((bits_consumed + 15) // 16) * 2


def _u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def verify_capture(
    manifest_path: Path, table0_path: Path, table1_path: Path,
) -> dict:
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    directory = manifest_path.parent
    stem = manifest_path.stem.removesuffix("_manifest")
    width = int(manifest["width"])
    height = int(manifest["height"])

    before_state = (directory / manifest["files"]["beforeState"]).read_bytes()
    after_state = (directory / manifest["files"]["afterState"]).read_bytes()
    bitstream = (directory / manifest["files"]["bitstream"]).read_bytes()
    if len(before_state) != manifest["stateSize"] or len(after_state) != len(before_state):
        raise ValueError("captured decoder state has the wrong size")

    previous_quantizer = _u32(before_state, 0x3B4)
    previous_format_variant = bool(_u32(before_state, 0x3BC))
    histories = []
    for index in range(1, 6):
        luma = (directory / f"{stem}_before_luma{index}.bin").read_bytes()
        chroma = (directory / f"{stem}_before_chroma{index}.bin").read_bytes()
        chroma_first, chroma_second = split_native_chroma(chroma, width, height)
        histories.append(mobiclip_reference.DecodedPFrame(
            header=mobiclip_reference.FrameHeader(
                False, previous_format_variant, 0, previous_quantizer,
            ),
            width=width,
            height=height,
            luma=luma,
            chroma_first=chroma_first,
            chroma_second=chroma_second,
            bits_consumed=0,
        ))

    decoded = mobiclip_reference.decode_frame(
        bitstream,
        width,
        height,
        (table0_path.read_bytes(), table1_path.read_bytes()),
        histories,
        previous_quantizer,
        previous_format_variant,
    )
    observed_luma = (directory / f"{stem}_after_luma0.bin").read_bytes()
    observed_chroma = (directory / f"{stem}_after_chroma0.bin").read_bytes()
    decoded_chroma = join_native_chroma(
        decoded.chroma_first, decoded.chroma_second, width, height,
    )
    returned_bytes = decoder_return_bytes(decoded.bits_consumed)
    selected_table = _u32(before_state, 0x3C + 4 * decoded.header.coefficient_table_variant)

    unchanged_histories = True
    for kind in ("luma", "chroma"):
        for index in range(1, 6):
            unchanged_histories &= (
                directory / f"{stem}_before_{kind}{index}.bin"
            ).read_bytes() == (
                directory / f"{stem}_after_{kind}{index}.bin"
            ).read_bytes()

    checks = {
        "luma": decoded.luma == observed_luma,
        "chroma": decoded_chroma == observed_chroma,
        "decoderReturnBytes": returned_bytes == int(manifest["decoderReturnBytes"]),
        "quantizerState": _u32(after_state, 0x3B4) == decoded.header.quantizer,
        "formatState": bool(_u32(after_state, 0x3BC)) == decoded.header.format_variant,
        "coefficientTableState": _u32(after_state, 0x3B8) == selected_table,
        "historyBuffersUnchanged": unchanged_histories,
    }
    return {
        "manifest": str(manifest_path.resolve()),
        "frameType": "I" if decoded.header.intra else "P",
        "dimensions": [width, height],
        "previousQuantizer": previous_quantizer,
        "quantizer": decoded.header.quantizer,
        "formatVariant": decoded.header.format_variant,
        "coefficientTableVariant": decoded.header.coefficient_table_variant,
        "bitsConsumed": decoded.bits_consumed,
        "decoderReturnBytes": returned_bytes,
        "expectedLumaSha256": _sha256(observed_luma),
        "decodedLumaSha256": _sha256(decoded.luma),
        "expectedChromaSha256": _sha256(observed_chroma),
        "decodedChromaSha256": _sha256(decoded_chroma),
        "checks": checks,
        "allMatch": all(checks.values()),
    }


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Replay a DeSmuME MobiClip frame capture byte-for-byte",
    )
    parser.add_argument("manifest", type=Path)
    parser.add_argument(
        "--table0", type=Path,
        default=ROOT / "scratch/mobiclip/coefficient_table_0_0208a7c4.bin",
    )
    parser.add_argument(
        "--table1", type=Path,
        default=ROOT / "scratch/mobiclip/coefficient_table_1_020886c4.bin",
    )
    args = parser.parse_args()
    report = verify_capture(args.manifest, args.table0, args.table1)
    print(json.dumps(report, indent=2))
    if not report["allMatch"]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
