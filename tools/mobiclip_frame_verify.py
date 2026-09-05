#!/usr/bin/env python3
"""Verify reconstructed MODS I-frames byte-for-byte against FFmpeg."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import subprocess
from pathlib import Path

import mobiclip_mods
import mobiclip_reference


ROOT = Path(__file__).resolve().parents[1]


def read_keyframes(data: bytes, header: mobiclip_mods.ModsHeader):
    if not header.key_table_offset:
        raise ValueError("MODS container has no keyframe table")
    end = header.key_table_offset + header.key_frame_count * 8
    if end > len(data):
        raise ValueError("truncated MODS keyframe table")
    return [
        struct.unpack_from("<II", data, header.key_table_offset + index * 8)
        for index in range(header.key_frame_count)
    ]


def ffmpeg_frames(mods_path: Path, indices: list[int], frame_size: int) -> list[bytes]:
    expression = "+".join(f"eq(n\\,{index})" for index in indices)
    completed = subprocess.run(
        [
            "ffmpeg", "-v", "error", "-i", str(mods_path),
            "-vf", f"select={expression}", "-vsync", "0",
            "-pix_fmt", "yuv420p", "-f", "rawvideo", "pipe:1",
        ],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=True,
    )
    expected_size = frame_size * len(indices)
    if len(completed.stdout) != expected_size:
        raise ValueError(
            f"FFmpeg returned {len(completed.stdout)} bytes; expected {expected_size}"
        )
    return [
        completed.stdout[offset:offset + frame_size]
        for offset in range(0, expected_size, frame_size)
    ]


def ffmpeg_first_frames(mods_path: Path, count: int, frame_size: int):
    process = subprocess.Popen(
        [
            "ffmpeg", "-v", "error", "-i", str(mods_path),
            "-frames:v", str(count), "-pix_fmt", "yuv420p",
            "-f", "rawvideo", "pipe:1",
        ],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    assert process.stdout is not None
    assert process.stderr is not None
    try:
        for frame_index in range(count):
            chunks = []
            remaining = frame_size
            while remaining:
                chunk = process.stdout.read(remaining)
                if not chunk:
                    break
                chunks.append(chunk)
                remaining -= len(chunk)
            frame = b"".join(chunks)
            if len(frame) != frame_size:
                raise ValueError(
                    f"FFmpeg frame {frame_index} has {len(frame)} bytes; "
                    f"expected {frame_size}"
                )
            yield frame
        error = process.stderr.read().decode("utf-8", errors="replace")
        return_code = process.wait()
        if return_code:
            raise subprocess.CalledProcessError(return_code, process.args, stderr=error)
    finally:
        if process.poll() is None:
            process.kill()
            process.wait()


def verify(
    mods_path: Path,
    table0_path: Path,
    table1_path: Path,
    count: int,
) -> dict:
    data = mods_path.read_bytes()
    header = mobiclip_mods.parse_header(data)
    keyframes = read_keyframes(data, header)[:count]
    if not keyframes:
        raise ValueError("no keyframes selected")
    indices = [frame for frame, _ in keyframes]
    luma_size = header.width * header.height
    chroma_size = luma_size // 4
    frame_size = luma_size + 2 * chroma_size
    expected_frames = ffmpeg_frames(mods_path, indices, frame_size)
    tables = (table0_path.read_bytes(), table1_path.read_bytes())

    records = []
    for (frame_index, packet_offset), expected in zip(keyframes, expected_frames):
        if packet_offset + 4 > len(data):
            raise ValueError(f"keyframe {frame_index} packet header is truncated")
        packed = struct.unpack_from("<I", data, packet_offset)[0]
        packet_size = packed >> 14
        packet_end = packet_offset + 4 + packet_size
        if packet_end > len(data):
            raise ValueError(f"keyframe {frame_index} packet is truncated")
        decoded = mobiclip_reference.decode_iframe(
            data[packet_offset + 4:packet_end], header.width, header.height, tables
        )
        # MODS stores the first chroma block as Cg. FFmpeg exposes planar
        # YCoCg as Y, Co, Cg, so reorder the reconstructed planes here.
        observed = decoded.luma + decoded.chroma_second + decoded.chroma_first
        matches = observed == expected
        records.append({
            "frame": frame_index,
            "packet_offset": packet_offset,
            "packet_size": packet_size,
            "video_bits_consumed": decoded.bits_consumed,
            "quantizer": decoded.header.quantizer,
            "coefficient_table_variant": decoded.header.coefficient_table_variant,
            "expected_sha256": hashlib.sha256(expected).hexdigest(),
            "observed_sha256": hashlib.sha256(observed).hexdigest(),
            "matches": matches,
        })
        if not matches:
            mismatch = next(
                index for index, (left, right) in enumerate(zip(observed, expected))
                if left != right
            )
            raise ValueError(
                f"keyframe {frame_index} differs from FFmpeg at frame byte {mismatch:#x}"
            )
    return {
        "schema_version": 1,
        "mods": str(mods_path.resolve()),
        "mods_sha256": hashlib.sha256(data).hexdigest(),
        "dimensions": [header.width, header.height],
        "verified_keyframes": len(records),
        "all_match": all(record["matches"] for record in records),
        "frames": records,
    }


def verify_sequence(
    mods_path: Path,
    table0_path: Path,
    table1_path: Path,
    count: int,
) -> dict:
    data = mods_path.read_bytes()
    header = mobiclip_mods.parse_header(data)
    packets = list(mobiclip_mods.iter_packets(data, header))[:count]
    if len(packets) != count:
        raise ValueError("requested sequence exceeds available MODS packets")
    luma_size = header.width * header.height
    chroma_size = luma_size // 4
    frame_size = luma_size + 2 * chroma_size
    expected_frames = ffmpeg_first_frames(mods_path, count, frame_size)
    tables = (table0_path.read_bytes(), table1_path.read_bytes())
    histories = []
    previous_quantizer = 12
    previous_format_variant = False
    records = []

    for packet, expected in zip(packets, expected_frames):
        packet_end = packet.payload_offset + packet.payload_size
        decoded = mobiclip_reference.decode_frame(
            data[packet.payload_offset:packet_end], header.width, header.height,
            tables, histories, previous_quantizer, previous_format_variant,
        )
        observed = decoded.luma + decoded.chroma_second + decoded.chroma_first
        if observed != expected:
            mismatch = next(
                index for index, (left, right) in enumerate(zip(observed, expected))
                if left != right
            )
            raise ValueError(
                f"frame {packet.frame_index} differs from FFmpeg at byte {mismatch:#x}"
            )
        records.append({
            "frame": packet.frame_index,
            "type": "I" if decoded.header.intra else "P",
            "packet_offset": packet.offset,
            "packet_size": packet.payload_size,
            "video_bits_consumed": decoded.bits_consumed,
            "quantizer": decoded.header.quantizer,
            "sha256": hashlib.sha256(observed).hexdigest(),
            "matches": True,
        })
        previous_quantizer = decoded.header.quantizer
        previous_format_variant = decoded.header.format_variant
        histories.insert(0, decoded)
        del histories[6:]
        if len(records) % 250 == 0 or len(records) == count:
            print(f"verified sequential frame {len(records)}/{count}", flush=True)

    return {
        "schema_version": 1,
        "mods": str(mods_path.resolve()),
        "mods_sha256": hashlib.sha256(data).hexdigest(),
        "dimensions": [header.width, header.height],
        "verified_frames": len(records),
        "i_frames": sum(record["type"] == "I" for record in records),
        "p_frames": sum(record["type"] == "P" for record in records),
        "all_match": True,
        "frames": records,
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--mods", type=Path,
        default=ROOT / "scratch/mobiclip/streams/802.mods",
    )
    parser.add_argument(
        "--table0", type=Path,
        default=ROOT / "scratch/mobiclip/coefficient_table_0_0208a7c4.bin",
    )
    parser.add_argument(
        "--table1", type=Path,
        default=ROOT / "scratch/mobiclip/coefficient_table_1_020886c4.bin",
    )
    parser.add_argument("--count", type=int, default=20)
    parser.add_argument("--sequence-count", type=int, default=100)
    parser.add_argument(
        "--output", type=Path,
        default=ROOT / "scratch/mobiclip/streams/802_iframe_verification.json",
    )
    args = parser.parse_args()
    if args.count <= 0:
        raise ValueError("--count must be positive")
    result = verify(args.mods, args.table0, args.table1, args.count)
    sequence = verify_sequence(
        args.mods, args.table0, args.table1, args.sequence_count
    )
    result["sequence"] = sequence
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(
        f"matched {result['verified_keyframes']} complete I-frames "
        f"({result['dimensions'][0]}x{result['dimensions'][1]}) against FFmpeg"
    )
    print(
        f"matched {sequence['verified_frames']} sequential frames "
        f"({sequence['i_frames']} I + {sequence['p_frames']} P)"
    )
    print(f"manifest: {args.output}")


if __name__ == "__main__":
    main()
