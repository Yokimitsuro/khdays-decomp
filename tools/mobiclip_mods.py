#!/usr/bin/env python3
"""Extract and inspect Nintendo DS MODS containers without touching the ROM."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from dataclasses import asdict, dataclass
from pathlib import Path

from ndspy.rom import NintendoDSRom


ROOT = Path(__file__).resolve().parents[1]
HEADER_SIZE = 0x30


@dataclass(frozen=True)
class ModsHeader:
    container: str
    video_codec: int
    frame_count: int
    width: int
    height: int
    fps_fixed: int
    audio_codec: int
    audio_channels: int
    audio_frequency: int
    largest_frame: int
    audio_info_offset: int
    key_table_offset: int
    key_frame_count: int
    packet_data_offset: int

    @property
    def frames_per_second(self) -> float:
        return self.fps_fixed / float(0x01000000)


@dataclass(frozen=True)
class PacketInfo:
    frame_index: int
    offset: int
    payload_offset: int
    payload_size: int
    audio_blocks_per_channel: int


def parse_header(data: bytes) -> ModsHeader:
    if len(data) < HEADER_SIZE:
        raise ValueError("MODS file is shorter than its fixed header")
    (
        magic,
        container_raw,
        video_codec,
        frame_count,
        width,
        height,
        fps_fixed,
        audio_codec,
        audio_channels,
        audio_frequency,
        largest_frame,
        audio_info_offset,
        key_table_offset,
        key_frame_count,
    ) = struct.unpack_from("<4s2sHIIIIHHIIIII", data)
    if magic != b"MODS":
        raise ValueError(f"unexpected MODS magic: {magic!r}")
    try:
        container = container_raw.decode("ascii")
    except UnicodeDecodeError as error:
        raise ValueError("invalid MODS container identifier") from error
    if container not in ("N2", "N3"):
        raise ValueError(f"unsupported MODS container: {container!r}")
    if video_codec != 0x0A:
        raise ValueError(f"unsupported MODS video codec: {video_codec:#x}")

    packet_data_offset = HEADER_SIZE
    if container == "N3":
        while True:
            if packet_data_offset + 4 > len(data):
                raise ValueError("unterminated MODS N3 parameter list")
            parameter_id, word_count = struct.unpack_from(
                "<2sH", data, packet_data_offset
            )
            packet_data_offset += 4
            parameter_size = word_count * 4
            if packet_data_offset + parameter_size > len(data):
                raise ValueError("truncated MODS N3 parameter block")
            packet_data_offset += parameter_size
            if parameter_id == b"HE":
                break

    return ModsHeader(
        container=container,
        video_codec=video_codec,
        frame_count=frame_count,
        width=width,
        height=height,
        fps_fixed=fps_fixed,
        audio_codec=audio_codec,
        audio_channels=audio_channels,
        audio_frequency=audio_frequency,
        largest_frame=largest_frame,
        audio_info_offset=audio_info_offset,
        key_table_offset=key_table_offset,
        key_frame_count=key_frame_count,
        packet_data_offset=packet_data_offset,
    )


def iter_packets(data: bytes, header: ModsHeader):
    limit_candidates = [len(data)]
    if header.audio_info_offset:
        limit_candidates.append(header.audio_info_offset)
    if header.key_table_offset:
        limit_candidates.append(header.key_table_offset)
    limit = min(offset for offset in limit_candidates if offset > 0)
    offset = header.packet_data_offset
    for frame_index in range(header.frame_count):
        if offset + 4 > limit:
            raise ValueError(f"packet {frame_index} header exceeds packet area")
        packed = struct.unpack_from("<I", data, offset)[0]
        audio_blocks = packed & 0x3FFF
        payload_size = packed >> 14
        payload_offset = offset + 4
        end = payload_offset + payload_size
        if end > limit:
            raise ValueError(f"packet {frame_index} payload exceeds packet area")
        yield PacketInfo(
            frame_index=frame_index,
            offset=offset,
            payload_offset=payload_offset,
            payload_size=payload_size,
            audio_blocks_per_channel=audio_blocks,
        )
        offset = end


def extract_member(rom_path: Path, member: str) -> bytes:
    rom = NintendoDSRom.fromFile(str(rom_path))
    try:
        file_id = rom.filenames.idOf(member)
    except Exception as error:
        raise ValueError(f"NitroFS member was not found: {member}") from error
    return bytes(rom.files[file_id])


def build_manifest(data: bytes, member: str) -> dict:
    header = parse_header(data)
    packets = list(iter_packets(data, header))
    first_packet = asdict(packets[0]) if packets else None
    return {
        "schema_version": 1,
        "member": member,
        "size": len(data),
        "sha256": hashlib.sha256(data).hexdigest(),
        "header": {
            **asdict(header),
            "frames_per_second": header.frames_per_second,
        },
        "packet_count": len(packets),
        "first_packet": first_packet,
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--rom", type=Path, default=ROOT / "days.nds")
    parser.add_argument("--member", default="mv/802.mods")
    parser.add_argument(
        "--output", type=Path,
        default=ROOT / "scratch/mobiclip/streams/802.mods",
    )
    args = parser.parse_args()

    data = extract_member(args.rom, args.member)
    manifest = build_manifest(data, args.member)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(data)
    manifest_path = args.output.with_suffix(args.output.suffix + ".json")
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    header = manifest["header"]
    print(
        f"extracted {args.member}: {header['width']}x{header['height']}, "
        f"{header['frame_count']} frames @ {header['frames_per_second']:.6f} fps"
    )
    print(f"packets: {manifest['packet_count']}; output: {args.output}")


if __name__ == "__main__":
    main()
