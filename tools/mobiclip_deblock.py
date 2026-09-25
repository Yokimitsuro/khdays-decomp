#!/usr/bin/env python3
"""Semantic model of the MobiClip deblocking post-filter (ov024 0x02092e60).

The player can hand a decoded frame through this filter before the colour
converter (func_ov024_02085ab8, display modes 1 and 2). It copies the frame's
planes into a second pair of 256-byte-stride planes, smoothing the 8-pixel block
edges on the way:

* vertical edges (x = 8, 16, ...) are filtered during the copy, row by row;
* horizontal edges (y = 8, 16, ...) are filtered in place afterwards, unless the
  request's vertical-only flag is set (mode 1);
* luma edges may also adjust the second pixel on each side, chroma edges only
  the two pixels touching the edge. The chroma buffer holds the Co and Cg planes
  side by side (+0x80), each at half the luma size.

An edge is filtered when |p0 - q0| < alpha, |p1 - p0| < beta and |q1 - q0| < beta,
with alpha/beta picked by the frame's quantiser. Then, with
avg = (p0 + q0 + 1) >> 1 and d = (p1 - q1 + 4) >> 3 (arithmetic),
p0' = clip(avg + d) and q0' = clip(avg - d); for luma, p1' = (p2 + avg + 1) >> 1
when |p2 - p0| < beta, and the same on the q side. clip() is the caller's byte
table read at +0x40, so indexes may run 64 below zero.

`--selftest` runs the ROM's own instructions (tools/arm_exec.py) and this model on
random frames and on frames decoded from a MODS stream, and compares every byte.
"""

from __future__ import annotations

import argparse
import random
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
STRIDE = 0x100

# Edge thresholds by quantiser, qp 12..48. Both tables are all-zero below the point
# where filtering starts (alpha from qp 16, beta from qp 15).
ALPHA = bytes([
    0, 0, 0, 0, 3, 4, 5, 5, 6, 7, 8, 10, 11, 13, 15, 17, 19, 22, 25, 29, 33, 38, 44,
    50, 57, 66, 75, 86, 98, 112, 128, 147, 168, 192, 219, 251, 255,
])
BETA = bytes([
    0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 11, 12, 12,
    13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18,
])
QP_MIN = 12
QP_MAX = 48
# The kernel indexes both tables from fixed bases without a range check. Above
# qp 48 its alpha read runs on into the beta table and its beta read into the two
# padding bytes and the first bytes of the next routine's push instruction:
# the thresholds it actually uses for qp 49..53 (alpha 0 disables 49..51).
ALPHA_OVERRUN = {49: 0, 50: 0, 51: 0, 52: 1, 53: 1}
BETA_OVERRUN = {49: 0, 50: 0, 51: 0xF0, 52: 0x5F, 53: 0x2D}


def thresholds(qp: int) -> tuple[int, int]:
    if QP_MIN <= qp <= QP_MAX:
        return ALPHA[qp - QP_MIN], BETA[qp - QP_MIN]
    if qp in ALPHA_OVERRUN:
        return ALPHA_OVERRUN[qp], BETA_OVERRUN[qp]
    raise ValueError(f"quantiser {qp} is outside the stream's 12..53 range")


def _asr(value: int, shift: int) -> int:
    return value >> shift            # Python's >> on int is arithmetic


def _edge(p2, p1, p0, q0, q1, q2, alpha, beta, clip, luma):
    """Filter one edge crossing; returns the new (p1, p0, q0, q1) or None."""
    if not (abs(p0 - q0) < alpha and abs(p1 - p0) < beta and abs(q1 - q0) < beta):
        return None
    avg = (p0 + q0 + 1) >> 1
    d = _asr(p1 - q1 + 4, 3)
    np0 = clip(avg + d)
    nq0 = clip(avg - d)
    np1, nq1 = p1, q1
    if luma:
        if abs(p2 - p0) < beta:
            np1 = (p2 + avg + 1) >> 1
        if abs(q2 - q0) < beta:
            nq1 = (q2 + avg + 1) >> 1
    return np1, np0, nq0, nq1


def filter_plane(src: bytes, width: int, height: int, alpha: int, beta: int, clip,
                 luma: bool, vertical_only: bool) -> bytearray:
    """Copy one 256-stride plane (width x height) and filter its block edges."""
    dst = bytearray(len(src))
    for y in range(height):
        row = bytearray(src[y * STRIDE:y * STRIDE + width])
        for x in range(8, width, 8):
            p2, p1, p0, q0, q1, q2 = row[x - 3:x + 3]
            out = _edge(p2, p1, p0, q0, q1, q2, alpha, beta, clip, luma)
            if out:
                row[x - 2:x + 2] = bytes(out)
        dst[y * STRIDE:y * STRIDE + width] = row
    if not vertical_only:
        for y in range(8, height, 8):
            for x in range(width):
                def px(dy):
                    return dst[(y + dy) * STRIDE + x]
                p2, p1, p0, q0, q1, q2 = px(-3), px(-2), px(-1), px(0), px(1), px(2)
                out = _edge(p2, p1, p0, q0, q1, q2, alpha, beta, clip, luma)
                if out:
                    np1, np0, nq0, nq1 = out
                    dst[(y - 2) * STRIDE + x] = np1
                    dst[(y - 1) * STRIDE + x] = np0
                    dst[y * STRIDE + x] = nq0
                    dst[(y + 1) * STRIDE + x] = nq1
    return dst


def deblock(luma: bytes, chroma: bytes, width: int, height: int, qp: int,
            clip_table: bytes, vertical_only: bool) -> tuple[bytearray, bytearray]:
    """The whole post-filter: returns the (luma, chroma) destination buffers.

    luma is height rows of 256 bytes; chroma is height/2 rows of 256 bytes with the
    Co plane at +0 and the Cg plane at +0x80. clip_table is the caller's table; the
    kernel reads it at +0x40 + value.
    """
    alpha, beta = thresholds(qp)

    def clip(value: int) -> int:
        return clip_table[0x40 + value]

    out_luma = filter_plane(luma, width, height, alpha, beta, clip, True, vertical_only)
    half_w, half_h = width >> 1, height >> 1
    out_chroma = bytearray(len(chroma))
    for base in (0, 0x80):
        plane = bytearray(len(chroma))
        for y in range(half_h):
            plane[y * STRIDE:y * STRIDE + half_w] = chroma[y * STRIDE + base:y * STRIDE + base + half_w]
        filtered = filter_plane(plane, half_w, half_h, alpha, beta, clip, False, vertical_only)
        for y in range(half_h):
            out_chroma[y * STRIDE + base:y * STRIDE + base + half_w] = filtered[y * STRIDE:y * STRIDE + half_w]
    return out_luma, out_chroma


# -- replay against the ROM ----------------------------------------------------------

def _rom_kernel():
    from mobiclip_kernel_inventory import OVERLAY, OVERLAY_BASE

    image = OVERLAY.read_bytes()
    return image, OVERLAY_BASE


def run_original(luma: bytes, chroma: bytes, width: int, height: int, qp: int,
                 clip_table: bytes, vertical_only: bool):
    """Run the ROM's 0x02092e60 on the same request inside tools/arm_exec.py."""
    from arm_exec import Cpu, Memory

    image, base = _rom_kernel()
    mem = Memory()
    start, end = 0x02092E60, 0x020933AC
    mem.map(start, image[start - base:end - base])
    src_l, src_c, dst_l, dst_c, table, req = 0x02200000, 0x02210000, 0x02220000, 0x02230000, 0x02240000, 0x02250000
    rows_l, rows_c = height, height >> 1
    mem.map(src_l, luma[:rows_l * STRIDE].ljust(rows_l * STRIDE, b"\0"))
    mem.map(src_c, chroma[:rows_c * STRIDE].ljust(rows_c * STRIDE, b"\0"))
    out_l = mem.map(dst_l, size=rows_l * STRIDE)
    out_c = mem.map(dst_c, size=rows_c * STRIDE)
    mem.map(table, clip_table)
    request = mem.map(req, size=0x24)
    fields = [src_l, src_c, dst_l, dst_c, width, height, qp, table, 1 if vertical_only else 0]
    for i, value in enumerate(fields):
        request[i * 4:i * 4 + 4] = value.to_bytes(4, "little")
    stack = 0x02260000
    mem.map(stack - 0x1000, size=0x1000)
    cpu = Cpu(mem)
    cpu.call(start, [req], sp=stack)
    return bytes(out_l), bytes(out_c)


def rom_clip_table() -> bytes:
    image, base = _rom_kernel()
    start = 0x020933AC
    return image[start - base:start - base + 0x180]


def _compare(luma, chroma, width, height, qp, table, vertical_only):
    want = run_original(luma, chroma, width, height, qp, table, vertical_only)
    got = deblock(luma, chroma, width, height, qp, table, vertical_only)
    rows_l, rows_c = height, height >> 1
    for name, a, b, rows, cols in (("luma", want[0], got[0], rows_l, width),
                                   ("chroma", want[1], got[1], rows_c, 256)):
        for y in range(rows):
            ra = a[y * STRIDE:y * STRIDE + cols]
            rb = bytes(b[y * STRIDE:y * STRIDE + cols])
            if ra != rb:
                x = next(i for i in range(cols) if ra[i] != rb[i])
                raise AssertionError(
                    f"{name} differs at ({x},{y}) qp={qp} {width}x{height} vonly={vertical_only}: "
                    f"rom {ra[x]} model {rb[x]}")


def selftest(count: int, seed: int, mods: str | None) -> None:
    table = rom_clip_table()
    rng = random.Random(seed)
    cases = 0
    for n in range(count):
        width = rng.choice([32, 64, 128, 256])
        height = rng.choice([32, 64, 96, 192])
        qp = rng.randint(12, 53)
        vonly = rng.random() < 0.5
        # smooth-ish content with random block offsets so every edge class occurs
        luma = bytearray(height * STRIDE)
        chroma = bytearray((height >> 1) * STRIDE)
        for buf, rows, cols in ((luma, height, width), (chroma, height >> 1, 256)):
            level = rng.randint(0, 255)
            for y in range(rows):
                for x in range(cols):
                    if x % 8 == 0 or rng.random() < 0.02:
                        level = max(0, min(255, level + rng.randint(-12, 12)))
                    buf[y * STRIDE + x] = max(0, min(255, level + rng.randint(-3, 3)))
        _compare(bytes(luma), bytes(chroma), width, height, qp, table, vonly)
        cases += 1
    print(f"random frames: {cases} requests byte-exact against the ROM kernel")
    if mods:
        frames = decoded_frames(mods)
        for index, (luma, chroma, width, height, qp) in enumerate(frames):
            for vonly in (False, True):
                _compare(luma, chroma, width, height, qp, table, vonly)
        print(f"{mods}: {len(frames)} decoded frames x 2 modes byte-exact against the ROM kernel")


def decoded_frames(path: str, count: int = 30):
    """The first frames of a MODS stream decoded by the semantic MobiClip decoder
    (tools/mobiclip_reference.py), laid out as the player's native planes: 256-byte
    rows, the two chroma planes side by side at +0 and +0x80."""
    import mobiclip_mods
    import mobiclip_reference

    data = Path(path).read_bytes()
    header = mobiclip_mods.parse_header(data)
    if header.width > 256 or header.width % 32 or header.height % 32:
        raise ValueError(f"{path}: {header.width}x{header.height} does not fit the kernel's planes")
    scratch = ROOT / "scratch/mobiclip"
    tables = ((scratch / "coefficient_table_0_0208a7c4.bin").read_bytes(),
              (scratch / "coefficient_table_1_020886c4.bin").read_bytes())
    histories = []
    quantizer, variant = 12, False
    frames = []
    w, h = header.width, header.height
    for packet in list(mobiclip_mods.iter_packets(data, header))[:count]:
        end = packet.payload_offset + packet.payload_size
        decoded = mobiclip_reference.decode_frame(
            data[packet.payload_offset:end], w, h, tables, histories, quantizer, variant)
        luma = bytearray(h * STRIDE)
        for y in range(h):
            luma[y * STRIDE:y * STRIDE + w] = decoded.luma[y * w:(y + 1) * w]
        chroma = bytearray((h >> 1) * STRIDE)
        half = w >> 1
        for y in range(h >> 1):
            chroma[y * STRIDE:y * STRIDE + half] = decoded.chroma_first[y * half:(y + 1) * half]
            chroma[y * STRIDE + 0x80:y * STRIDE + 0x80 + half] = decoded.chroma_second[y * half:(y + 1) * half]
        frames.append((bytes(luma), bytes(chroma), w, h, decoded.header.quantizer))
        quantizer, variant = decoded.header.quantizer, decoded.header.format_variant
        histories.insert(0, decoded)
        del histories[6:]
    return frames


def replay_capture(path: str) -> None:
    """Check a DeSmuME capture (tools/mobiclip_kernel_capture.lua) of the real call."""
    import json

    manifest = json.loads(Path(path).read_text(encoding="utf-8"))
    folder = Path(path).parent
    width, height = manifest["width"], manifest["height"]
    qp, vertical_only = manifest["quantiser"], bool(manifest["vertical_only"])
    before = [(folder / manifest[k]).read_bytes() for k in ("before_luma", "before_chroma")]
    after = [(folder / manifest[k]).read_bytes() for k in ("after_luma", "after_chroma")]
    table = (folder / manifest["clip_table"]).read_bytes()
    model = deblock(before[0], before[1], width, height, qp, table, vertical_only)
    replay = run_original(before[0], before[1], width, height, qp, table, vertical_only)
    half = width >> 1
    for name, want, got, rom, rows, spans in (
            ("luma", after[0], model[0], replay[0], height, [(0, width)]),
            ("chroma", after[1], model[1], replay[1], height >> 1, [(0, half), (0x80, 0x80 + half)])):
        for y in range(rows):
            for lo, hi in spans:
                a = want[y * STRIDE + lo:y * STRIDE + hi]
                if bytes(got[y * STRIDE + lo:y * STRIDE + hi]) != a:
                    raise AssertionError(f"capture {name} row {y}: the model differs from the hardware")
                if rom[y * STRIDE + lo:y * STRIDE + hi] != a:
                    raise AssertionError(f"capture {name} row {y}: tools/arm_exec.py differs from the hardware")
    print(f"{path}: {width}x{height} qp {qp} vertical_only={vertical_only}: model and ARM replay "
          f"match the captured planes byte for byte")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--capture", help="replay a DeSmuME capture manifest (deblock.json)")
    ap.add_argument("--count", type=int, default=40)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--mods", help="decode this MODS file and replay every frame")
    args = ap.parse_args()
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    if args.selftest:
        selftest(args.count, args.seed, args.mods)
    if args.capture:
        replay_capture(args.capture)


if __name__ == "__main__":
    main()
