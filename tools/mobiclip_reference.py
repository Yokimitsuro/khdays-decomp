#!/usr/bin/env python3
"""Semantic oracle for the recovered MobiClip coefficient transform paths.

This module intentionally contains no original payload bytes.  Its JSON mode
is suitable for comparing coefficients and reconstructed blocks captured from
an emulator with the isolated C++ reconstruction in mobiclip_reference.cpp.
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from typing import Iterable


QUANT4X4 = (
    (10, 13, 13, 10, 16, 10, 13, 13, 13, 13, 16, 10, 16, 13, 13, 16),
    (11, 14, 14, 11, 18, 11, 14, 14, 14, 14, 18, 11, 18, 14, 14, 18),
    (13, 16, 16, 13, 20, 13, 16, 16, 16, 16, 20, 13, 20, 16, 16, 20),
    (14, 18, 18, 14, 23, 14, 18, 18, 18, 18, 23, 14, 23, 18, 18, 23),
    (16, 20, 20, 16, 25, 16, 20, 20, 20, 20, 25, 16, 25, 20, 20, 25),
    (18, 23, 23, 18, 29, 18, 23, 23, 23, 23, 29, 18, 29, 23, 23, 29),
)

QUANT8X8 = (
    (
        20, 19, 19, 25, 18, 25, 19, 24, 24, 19, 20, 18, 32, 18, 20, 19,
        19, 24, 24, 19, 19, 25, 18, 25, 18, 25, 18, 25, 19, 24, 24, 19,
        19, 24, 24, 19, 18, 32, 18, 20, 18, 32, 18, 24, 24, 19, 19, 24,
        24, 18, 25, 18, 25, 18, 19, 24, 24, 19, 18, 32, 18, 24, 24, 18,
    ),
    (
        22, 21, 21, 28, 19, 28, 21, 26, 26, 21, 22, 19, 35, 19, 22, 21,
        21, 26, 26, 21, 21, 28, 19, 28, 19, 28, 19, 28, 21, 26, 26, 21,
        21, 26, 26, 21, 19, 35, 19, 22, 19, 35, 19, 26, 26, 21, 21, 26,
        26, 19, 28, 19, 28, 19, 21, 26, 26, 21, 19, 35, 19, 26, 26, 19,
    ),
    (
        26, 24, 24, 33, 23, 33, 24, 31, 31, 24, 26, 23, 42, 23, 26, 24,
        24, 31, 31, 24, 24, 33, 23, 33, 23, 33, 23, 33, 24, 31, 31, 24,
        24, 31, 31, 24, 23, 42, 23, 26, 23, 42, 23, 31, 31, 24, 24, 31,
        31, 23, 33, 23, 33, 23, 24, 31, 31, 24, 23, 42, 23, 31, 31, 23,
    ),
    (
        28, 26, 26, 35, 25, 35, 26, 33, 33, 26, 28, 25, 45, 25, 28, 26,
        26, 33, 33, 26, 26, 35, 25, 35, 25, 35, 25, 35, 26, 33, 33, 26,
        26, 33, 33, 26, 25, 45, 25, 28, 25, 45, 25, 33, 33, 26, 26, 33,
        33, 25, 35, 25, 35, 25, 26, 33, 33, 26, 25, 45, 25, 33, 33, 25,
    ),
    (
        32, 30, 30, 40, 28, 40, 30, 38, 38, 30, 32, 28, 51, 28, 32, 30,
        30, 38, 38, 30, 30, 40, 28, 40, 28, 40, 28, 40, 30, 38, 38, 30,
        30, 38, 38, 30, 28, 51, 28, 32, 28, 51, 28, 38, 38, 30, 30, 38,
        38, 28, 40, 28, 40, 28, 30, 38, 38, 30, 28, 51, 28, 38, 38, 28,
    ),
    (
        36, 34, 34, 46, 32, 46, 34, 43, 43, 34, 36, 32, 58, 32, 36, 34,
        34, 43, 43, 34, 34, 46, 32, 46, 32, 46, 32, 46, 34, 43, 43, 34,
        34, 43, 43, 34, 32, 58, 32, 36, 32, 58, 32, 43, 43, 34, 34, 43,
        43, 32, 46, 32, 46, 32, 34, 43, 43, 34, 32, 58, 32, 43, 43, 32,
    ),
)

ZIGZAG4X4 = (0, 4, 1, 2, 5, 8, 12, 9, 6, 3, 7, 10, 13, 14, 11, 15)
ZIGZAG8X8 = (
    0, 1, 8, 16, 9, 2, 3, 10, 17, 24, 32, 25, 18, 11, 4, 5,
    12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6, 7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
)


def _u32(value: int) -> int:
    return value & 0xFFFFFFFF


def _s32(value: int) -> int:
    value &= 0xFFFFFFFF
    return value - 0x100000000 if value & 0x80000000 else value


def _asr(value: int, shift: int) -> int:
    return _s32(value) >> shift


class WordBitReader:
    """MSB-first reader over the little-endian uint16 refill order in the ARM."""

    def __init__(self, data: bytes | bytearray | memoryview):
        self.data = bytes(data)
        self.bit_position = 0

    def read_bit(self) -> int:
        word_offset = (self.bit_position // 16) * 2
        if word_offset + 1 >= len(self.data):
            raise EOFError("MobiClip bitstream ended inside a uint16 refill")
        bit_in_word = self.bit_position % 16
        word = self.data[word_offset] | (self.data[word_offset + 1] << 8)
        self.bit_position += 1
        return (word >> (15 - bit_in_word)) & 1

    def read_bits(self, count: int) -> int:
        if not 0 <= count <= 32:
            raise ValueError("bit count must be in 0..32")
        start = self.bit_position
        value = 0
        try:
            for _ in range(count):
                value = (value << 1) | self.read_bit()
        except EOFError:
            self.bit_position = start
            raise
        return value

    def read_unsigned_exp_golomb(self) -> int:
        start = self.bit_position
        zeros = 0
        try:
            while self.read_bit() == 0:
                zeros += 1
                if zeros > 31:
                    raise ValueError("Exp-Golomb prefix exceeds 31 zero bits")
            suffix = self.read_bits(zeros)
        except (EOFError, ValueError):
            self.bit_position = start
            raise
        return ((1 << zeros) - 1) + suffix

    def read_signed_exp_golomb(self) -> int:
        code = self.read_unsigned_exp_golomb()
        return (code + 1) // 2 if code & 1 else -(code // 2)


def unpack_quant_scan(entry: int, level: int) -> tuple[int, int]:
    """Return (scan index, dequantized coefficient) from one packed entry."""
    multiplier = (entry >> 8) & 0xFFFF
    if multiplier & 0x8000:
        multiplier -= 0x10000
    return entry & 0xFF, multiplier * level


def build_quant_scan_tables(quantizer: int) -> tuple[list[int], list[int]]:
    """Build the packed state +0x74/+0x174 tables for a valid DS stream QP."""
    if not 12 <= quantizer <= 53:
        raise ValueError("quantizer must be in the valid Nintendo DS range 12..53")
    row = quantizer % 6
    shift = quantizer // 6
    quant_scan4 = [
        (base << (shift + 8)) | scan
        for base, scan in zip(QUANT4X4[row], ZIGZAG4X4)
    ]
    quant_scan8 = [
        (base << (shift + 6)) | scan
        for base, scan in zip(QUANT8X8[row], ZIGZAG8X8)
    ]
    return quant_scan8, quant_scan4


def reset_prediction_borders(prediction_modes: Iterable[int]) -> list[int]:
    modes = list(prediction_modes)
    if len(modes) != 40:
        raise ValueError("expected 40 prediction-cache entries")
    for index in (1, 2, 3, 4, 8, 16, 24, 32):
        modes[index] = 9
    return modes


def _inverse4(values: Iterable[int]) -> list[int]:
    rs = [_s32(value) for value in values]
    if len(rs) != 4:
        raise ValueError("inverse4 requires four values")

    a = _u32(rs[0] + rs[2])
    b = _u32(rs[0] - rs[2])
    c = _u32(rs[1] + _asr(rs[3], 1))
    d = _u32(_asr(rs[1], 1) - rs[3])
    return [
        _s32(a + c),
        _s32(b + d),
        _s32(b - d),
        _s32(a - c),
    ]


def _inverse8(values: Iterable[int]) -> list[int]:
    rs = [_s32(value) for value in values]
    if len(rs) != 8:
        raise ValueError("inverse8 requires eight values")

    even = _inverse4((rs[0], rs[2], rs[4], rs[6]))
    e = _u32(rs[7] + rs[1] - rs[3] - _asr(rs[3], 1))
    f = _u32(rs[7] - rs[1] + rs[5] + _asr(rs[5], 1))
    g = _u32(rs[5] - rs[3] - rs[7] - _asr(rs[7], 1))
    h = _u32(rs[5] + rs[3] + rs[1] + _asr(rs[1], 1))
    x3 = _u32(g + _asr(h, 2))
    x2 = _u32(e + _asr(f, 2))
    x1 = _u32(_asr(e, 2) - f)
    x0 = _u32(h - _asr(g, 2))
    return [
        _s32(even[0] + x0),
        _s32(even[1] + x1),
        _s32(even[2] + x2),
        _s32(even[3] + x3),
        _s32(even[3] - x3),
        _s32(even[2] - x2),
        _s32(even[1] - x1),
        _s32(even[0] - x0),
    ]


def inverse_transform(coefficients: Iterable[int], size: int) -> list[int]:
    """Apply the recovered separable 4x4 or 8x8 transform and >>6 scaling."""
    if size not in (4, 8):
        raise ValueError("size must be 4 or 8")
    block = [_s32(value) for value in coefficients]
    if len(block) != size * size:
        raise ValueError(f"expected {size * size} coefficients")

    block[0] = _s32(block[0] + 32)
    transform = _inverse4 if size == 4 else _inverse8
    for y in range(size):
        start = y * size
        block[start : start + size] = transform(block[start : start + size])

    block = [block[y * size + x] for x in range(size) for y in range(size)]
    for y in range(size):
        start = y * size
        block[start : start + size] = transform(block[start : start + size])

    return [_asr(value, 6) for value in block]


def reconstruct_block(
    coefficients: Iterable[int], prediction: Iterable[int], size: int
) -> list[int]:
    residual = inverse_transform(coefficients, size)
    predicted = list(prediction)
    if len(predicted) != size * size:
        raise ValueError(f"expected {size * size} prediction samples")
    return [max(0, min(255, sample + delta)) for sample, delta in zip(predicted, residual)]


def evaluate_capture(capture: dict) -> dict:
    size = int(capture["size"])
    coefficients = capture["coefficients"]
    residual = inverse_transform(coefficients, size)
    result = {"size": size, "residual": residual}
    if "prediction" in capture:
        result["reconstructed"] = reconstruct_block(
            coefficients, capture["prediction"], size
        )
    if "observed" in capture:
        if "reconstructed" not in result:
            raise ValueError("observed output requires prediction samples")
        observed = list(capture["observed"])
        if len(observed) != size * size:
            raise ValueError(f"expected {size * size} observed samples")
        mismatches = [
            index
            for index, (expected, actual) in enumerate(
                zip(result["reconstructed"], observed)
            )
            if expected != actual
        ]
        result["matchesObserved"] = not mismatches
        result["mismatchIndices"] = mismatches
    return result


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Evaluate a JSON MobiClip transform capture"
    )
    parser.add_argument(
        "capture",
        nargs="?",
        type=Path,
        help="JSON input path; stdin is used when omitted",
    )
    args = parser.parse_args(argv)
    if args.capture:
        capture = json.loads(args.capture.read_text(encoding="utf-8"))
    else:
        capture = json.load(sys.stdin)
    json.dump(evaluate_capture(capture), sys.stdout, indent=2)
    sys.stdout.write("\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
