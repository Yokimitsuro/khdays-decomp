#!/usr/bin/env python3
"""Semantic model of the MobiClip FastAudio decoder (ov024 0x02087318).

Audio coding 2 of the MobiClip player (func_ov024_02085c8c): every 0x28-byte
block of one channel becomes 256 signed 16-bit samples.

Block layout, as ten little-endian 32-bit words w0..w9 (each read as two u16s):

* w0 holds seven of the eight reflection coefficients of an 8th-order lattice
  filter: 6+6+5+5+4+3+3 bits, each an index into its own quantiser table. The
  sixth (k5) is indexed by the lowest bit of w3, w5, w7 and w9 (w3 highest).
* w1 holds, per 64-sample sub-block, a 6-bit excitation scale (bits 8, 14, 20,
  26) and a 2-bit phase (bits 0, 2, 4, 6).
* w2..w9 hold four sub-blocks of 21 three-bit excitation codes: ten from the
  even word (bits 29..2), ten from the odd word, and one made of the even word's
  two low bits and bit 1 of the odd word.

Each sub-block expands to 64 samples: `phase` zeros, then the 21 pulses
EXCITATION[scale][code] two zeros apart, then 3 - phase zeros. The 256 pulses
run through the lattice (Q15 multiplies rounded with +0x4000, 32-bit wrap), a
de-emphasis y = x + 0.86 * y' (0x6e14 in Q15), and are doubled and saturated.
The channel keeps the lattice memory and the de-emphasis output between blocks.

`--selftest` replays the ROM's own instructions (tools/arm_exec.py) against this
model on random blocks, one block at a time and as long runs with the channel
state carried over.
"""

from __future__ import annotations

import argparse
import random
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BLOCK_BYTES = 0x28
SAMPLES = 256
DEEMPHASIS = 0x6E14            # 0.86 in Q15
ROUND = 0x4000

# Reflection-coefficient quantisers (Q15), one per lattice stage; k0 and k1 share the
# 6-bit table, k5 is the one indexed by the four scattered bits.
REFLECTION_6BIT = (
    -32665, -32460, -32256, -32051, -31846, -31641, -31436, -31232,
    -30719, -29901, -29081, -28261, -27443, -26623, -25805, -24985,
    -24165, -23347, -22527, -21300, -19660, -18024, -16384, -14744,
    -13108, -11468, -9832, -8192, -6552, -4916, -3276, -1640,
    0, 1640, 3276, 4916, 6552, 8192, 9832, 11468,
    13108, 14744, 16384, 18024, 19660, 21300, 22527, 23347,
    24167, 24985, 25805, 26623, 27443, 28261, 29081, 29901,
    30719, 31232, 31436, 31641, 31846, 32051, 32256, 32460,
)
REFLECTION_2 = (
    -27443, -26623, -25805, -24985, -24165, -23347, -22527, -21300,
    -19660, -18024, -16384, -14744, -13108, -11468, -9832, -8192,
    -6552, -4916, -3276, -1640, 0, 1640, 3276, 4916,
    6552, 8192, 9832, 11468, 13108, 14744, 16384, 18024,
)
REFLECTION_3 = (
    -18024, -16384, -14744, -13108, -11468, -9832, -8192, -6552,
    -4916, -3276, -1640, 0, 1640, 3276, 4916, 6552,
    8192, 9832, 11468, 13108, 14744, 16384, 18024, 19660,
    21300, 22527, 23347, 24167, 24985, 25805, 26623, 27443,
)
REFLECTION_4 = (
    -19664, -17260, -14860, -12456, -10052, -7648, -5248, -2844,
    -440, 1960, 4364, 6768, 9172, 11572, 13976, 16380,
)
REFLECTION_6 = (
    -13108, -9176, -5244, -1312, 2620, 6552, 10484, 14412,
)
REFLECTION_7 = (
    -6556, -2844, 872, 4584, 8296, 12012, 15724, 19436,
)
REFLECTION_5 = (
    -9832, -7644, -5460, -3276, -1092, 1092, 3276, 5460,
    7644, 9832, 12016, 14200, 16384, 18568, 20752, 22527,
)
# Excitation levels by 6-bit scale: 8 pulse amplitudes, roughly (2c - 7) * step.
EXCITATION = (
    (-28, -20, -12, -4, 4, 12, 20, 28),
    (-56, -40, -24, -8, 8, 24, 40, 56),
    (-84, -60, -36, -12, 12, 36, 60, 84),
    (-112, -80, -48, -16, 16, 48, 80, 112),
    (-140, -100, -60, -20, 20, 60, 100, 140),
    (-168, -120, -72, -24, 24, 72, 120, 168),
    (-196, -140, -84, -28, 28, 84, 140, 196),
    (-224, -160, -96, -32, 32, 96, 160, 224),
    (-252, -180, -108, -36, 36, 108, 180, 252),
    (-280, -200, -120, -40, 40, 120, 200, 280),
    (-308, -220, -132, -44, 44, 132, 220, 308),
    (-336, -240, -144, -48, 48, 144, 240, 336),
    (-364, -260, -156, -52, 52, 156, 260, 364),
    (-392, -280, -168, -56, 56, 168, 280, 392),
    (-420, -300, -180, -60, 60, 180, 300, 420),
    (-448, -320, -192, -64, 64, 192, 320, 448),
    (-504, -360, -216, -72, 72, 216, 360, 504),
    (-560, -400, -240, -80, 80, 240, 400, 560),
    (-616, -440, -264, -88, 88, 264, 440, 616),
    (-672, -480, -288, -96, 96, 288, 480, 672),
    (-728, -520, -312, -104, 104, 312, 520, 728),
    (-784, -560, -336, -112, 112, 336, 560, 784),
    (-840, -600, -360, -120, 120, 360, 600, 840),
    (-896, -640, -384, -128, 128, 384, 640, 896),
    (-1008, -720, -432, -144, 144, 432, 720, 1008),
    (-1120, -800, -480, -160, 160, 480, 800, 1120),
    (-1232, -880, -528, -176, 176, 528, 880, 1232),
    (-1344, -960, -576, -192, 192, 576, 960, 1344),
    (-1456, -1040, -624, -208, 208, 624, 1040, 1456),
    (-1568, -1120, -672, -224, 224, 672, 1120, 1568),
    (-1680, -1200, -720, -240, 240, 720, 1200, 1680),
    (-1792, -1280, -768, -256, 256, 768, 1280, 1792),
    (-2016, -1440, -864, -288, 288, 864, 1440, 2016),
    (-2240, -1600, -960, -320, 320, 960, 1600, 2240),
    (-2464, -1760, -1056, -352, 352, 1056, 1760, 2464),
    (-2688, -1920, -1152, -384, 384, 1152, 1920, 2688),
    (-2912, -2080, -1248, -416, 416, 1248, 2080, 2912),
    (-3136, -2240, -1344, -448, 448, 1344, 2240, 3136),
    (-3360, -2400, -1440, -480, 480, 1440, 2400, 3360),
    (-3584, -2560, -1536, -512, 512, 1536, 2560, 3584),
    (-4032, -2880, -1728, -576, 576, 1728, 2880, 4032),
    (-4480, -3200, -1920, -640, 640, 1920, 3200, 4480),
    (-4928, -3520, -2112, -704, 704, 2112, 3520, 4928),
    (-5376, -3840, -2304, -768, 768, 2304, 3840, 5376),
    (-5824, -4160, -2496, -832, 832, 2496, 4160, 5824),
    (-6272, -4480, -2688, -896, 896, 2688, 4480, 6272),
    (-6720, -4800, -2880, -960, 960, 2880, 4800, 6720),
    (-7168, -5120, -3072, -1024, 1024, 3072, 5120, 7168),
    (-8063, -5759, -3456, -1152, 1152, 3456, 5760, 8064),
    (-8959, -6399, -3840, -1280, 1280, 3840, 6400, 8960),
    (-9855, -7039, -4224, -1408, 1408, 4224, 7040, 9856),
    (-10751, -7679, -4608, -1536, 1536, 4608, 7680, 10752),
    (-11647, -8319, -4992, -1664, 1664, 4992, 8320, 11648),
    (-12543, -8959, -5376, -1792, 1792, 5376, 8960, 12544),
    (-13439, -9599, -5760, -1920, 1920, 5760, 9600, 13440),
    (-14335, -10239, -6144, -2048, 2048, 6144, 10240, 14336),
    (-16127, -11519, -6912, -2304, 2304, 6912, 11519, 16127),
    (-17919, -12799, -7680, -2560, 2560, 7680, 12799, 17919),
    (-19711, -14079, -8448, -2816, 2816, 8448, 14079, 19711),
    (-21503, -15359, -9216, -3072, 3072, 9216, 15359, 21503),
    (-23295, -16639, -9984, -3328, 3328, 9984, 16639, 23295),
    (-25087, -17919, -10752, -3584, 3584, 10752, 17919, 25087),
    (-26879, -19199, -11520, -3840, 3840, 11520, 19199, 26879),
    (-28671, -20479, -12288, -4096, 4096, 12288, 20479, 28671),
)


def _s32(value: int) -> int:
    value &= 0xFFFFFFFF
    return value - (1 << 32) if value & 0x80000000 else value


def _q15(a: int, b: int) -> int:
    """mla rd, a, b, #0x4000 followed by asr #15, with the 32-bit wrap."""
    return _s32(a * b + ROUND) >> 15


@dataclass
class Block:
    reflection: list[int]
    phase: list[int]
    scale: list[int]
    codes: list[int]


@dataclass
class ChannelState:
    memory: list[int] = field(default_factory=lambda: [0] * 9)
    deemphasis: int = 0


def parse(block: bytes) -> Block:
    if len(block) < BLOCK_BYTES:
        raise ValueError("a FastAudio block is 0x28 bytes")
    w = struct.unpack_from("<10I", block)
    k = [0] * 8
    k[0] = REFLECTION_6BIT[w[0] >> 26]
    k[1] = REFLECTION_6BIT[(w[0] >> 20) & 63]
    k[2] = REFLECTION_2[(w[0] >> 15) & 31]
    k[3] = REFLECTION_3[(w[0] >> 10) & 31]
    k[4] = REFLECTION_4[(w[0] >> 6) & 15]
    k[6] = REFLECTION_6[(w[0] >> 3) & 7]
    k[7] = REFLECTION_7[w[0] & 7]
    k[5] = REFLECTION_5[(w[3] & 1) << 3 | (w[5] & 1) << 2 | (w[7] & 1) << 1 | (w[9] & 1)]
    phase = [(w[1] >> shift) & 3 for shift in (0, 2, 4, 6)]
    scale = [(w[1] >> shift) & 63 for shift in (8, 14, 20, 26)]
    codes = []
    for sub in range(4):
        even, odd = w[2 + 2 * sub], w[3 + 2 * sub]
        codes += [(even >> (29 - 3 * i)) & 7 for i in range(10)]
        codes += [(odd >> (29 - 3 * i)) & 7 for i in range(10)]
        codes.append((even & 3) << 1 | (odd >> 1) & 1)
    return Block(k, phase, scale, codes)


def excitation(parsed: Block) -> list[int]:
    out = []
    for sub in range(4):
        levels = EXCITATION[parsed.scale[sub]]
        out += [0] * parsed.phase[sub]
        for i, code in enumerate(parsed.codes[21 * sub:21 * sub + 21]):
            out.append(levels[code])
            if i < 20:
                out += [0, 0]
        out += [0] * (3 - parsed.phase[sub])
    return out


def decode(block: bytes, state: ChannelState) -> list[int]:
    """One block to 256 samples; updates the channel state in place."""
    parsed = parse(block)
    k = parsed.reflection
    mem = state.memory
    y = state.deemphasis
    samples = []
    for x in excitation(parsed):
        for i in range(7, -1, -1):
            x = _s32(x - _q15(k[i], mem[i]))
            mem[i + 1] = _s32(mem[i] + _q15(k[i], x))
        mem[0] = x
        y = _s32(x + _q15(y, DEEMPHASIS))
        out = _s32(y + y)
        samples.append(max(-0x8000, min(0x7FFF, out)))
    state.deemphasis = y
    return samples


# -- replay against the ROM ----------------------------------------------------------

ENTRY = 0x02087318
END = 0x020886C4
CHANNEL_BYTES = 0x1D0          # packet, output, 0x1b8 of decoder state, ..., +0x1cc stride


def run_original(block: bytes, state: ChannelState, stride: int = 2):
    """Run the ROM's 0x02087318 on one block inside tools/arm_exec.py."""
    from arm_exec import Cpu, Memory
    from mobiclip_kernel_inventory import OVERLAY, OVERLAY_BASE

    image = OVERLAY.read_bytes()
    mem = Memory()
    mem.map(ENTRY, image[ENTRY - OVERLAY_BASE:END - OVERLAY_BASE])
    src, dst, chan, stack = 0x02200000, 0x02210000, 0x02220000, 0x02230000
    mem.map(src, block[:BLOCK_BYTES])
    out = mem.map(dst, size=SAMPLES * stride)
    ctx = mem.map(chan, size=CHANNEL_BYTES)
    mem.map(stack - 0x400, size=0x400)
    struct.pack_into("<II", ctx, 0, src, dst)
    struct.pack_into("<9i", ctx, 8 + 0x190, *state.memory)
    struct.pack_into("<i", ctx, 8 + 0x1B4, state.deemphasis)
    struct.pack_into("<I", ctx, 0x1CC, stride)
    Cpu(mem).call(ENTRY, [chan], sp=stack)
    samples = [struct.unpack_from("<h", out, i * stride)[0] for i in range(SAMPLES)]
    after = ChannelState(list(struct.unpack_from("<9i", ctx, 8 + 0x190)),
                         struct.unpack_from("<i", ctx, 8 + 0x1B4)[0])
    fields = struct.unpack_from("<100i", ctx, 8)
    return samples, after, fields


def _check(block: bytes, state: ChannelState, stride: int) -> ChannelState:
    before = ChannelState(list(state.memory), state.deemphasis)
    want, rom_state, fields = run_original(block, before, stride)
    parsed = parse(block)
    expect_fields = parsed.reflection + parsed.phase + parsed.scale + parsed.codes
    if list(fields) != expect_fields:
        raise AssertionError(f"parsed fields differ for block {block.hex()}")
    got = decode(block, state)
    if got != want:
        n = next(i for i in range(SAMPLES) if got[i] != want[i])
        raise AssertionError(f"sample {n} differs for block {block.hex()}: rom {want[n]} model {got[n]}")
    if (state.memory, state.deemphasis) != (rom_state.memory, rom_state.deemphasis):
        raise AssertionError(f"channel state differs after block {block.hex()}")
    return state


def selftest(count: int, runs: int, run_length: int, seed: int) -> None:
    rng = random.Random(seed)
    for _ in range(count):
        state = ChannelState([rng.randint(-40000, 40000) for _ in range(9)], rng.randint(-40000, 40000))
        _check(bytes(rng.getrandbits(8) for _ in range(BLOCK_BYTES)), state, rng.choice([2, 4]))
    print(f"single blocks: {count} byte-exact against the ROM kernel (samples, fields, state)")
    for _ in range(runs):
        state = ChannelState()
        # plausible streams: small scales most of the time, loud bursts now and then
        for _ in range(run_length):
            block = bytearray(rng.getrandbits(8) for _ in range(BLOCK_BYTES))
            if rng.random() < 0.8:
                w1 = struct.unpack_from("<I", block, 4)[0]
                w1 &= ~((63 << 8) | (63 << 14) | (63 << 20) | (63 << 26)) & 0xFFFFFFFF
                for shift in (8, 14, 20, 26):
                    w1 |= rng.randint(0, 40) << shift
                struct.pack_into("<I", block, 4, w1)
            _check(bytes(block), state, 2)
    print(f"streams: {runs} x {run_length} consecutive blocks byte-exact with the channel state carried")


def replay_capture(path: str) -> None:
    """Check a DeSmuME capture (tools/mobiclip_kernel_capture.lua) of the real call."""
    import json

    manifest = json.loads(Path(path).read_text(encoding="utf-8"))
    folder = Path(path).parent
    block = (folder / manifest["block"]).read_bytes()
    before = (folder / manifest["before_channel"]).read_bytes()
    after = (folder / manifest["after_channel"]).read_bytes()
    output = (folder / manifest["output"]).read_bytes()
    stride = manifest["stride"]
    state = ChannelState(list(struct.unpack_from("<9i", before, 8 + 0x190)),
                         struct.unpack_from("<i", before, 8 + 0x1B4)[0])
    rom_samples, rom_state, rom_fields = run_original(
        block, ChannelState(list(state.memory), state.deemphasis), stride)
    samples = decode(block, state)
    want = [struct.unpack_from("<h", output, i * stride)[0] for i in range(SAMPLES)]
    parsed = parse(block)
    fields = parsed.reflection + parsed.phase + parsed.scale + parsed.codes
    want_fields = list(struct.unpack_from("<100i", after, 8))
    want_state = ChannelState(list(struct.unpack_from("<9i", after, 8 + 0x190)),
                              struct.unpack_from("<i", after, 8 + 0x1B4)[0])
    for name, got in (("model", (samples, fields, state)), ("ARM replay", (rom_samples, list(rom_fields), rom_state))):
        if got[0] != want:
            raise AssertionError(f"capture: {name} samples differ from the hardware")
        if got[1] != want_fields:
            raise AssertionError(f"capture: {name} parsed fields differ from the hardware")
        if (got[2].memory, got[2].deemphasis) != (want_state.memory, want_state.deemphasis):
            raise AssertionError(f"capture: {name} channel state differs from the hardware")
    print(f"{path}: model and ARM replay match the captured samples, fields and channel state")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--capture", help="replay a DeSmuME capture manifest (fastaudio.json)")
    ap.add_argument("--count", type=int, default=200)
    ap.add_argument("--runs", type=int, default=4)
    ap.add_argument("--run-length", type=int, default=100)
    ap.add_argument("--seed", type=int, default=1)
    args = ap.parse_args()
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    if args.selftest:
        selftest(args.count, args.runs, args.run_length, args.seed)
    if args.capture:
        replay_capture(args.capture)


if __name__ == "__main__":
    main()
