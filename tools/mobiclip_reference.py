#!/usr/bin/env python3
"""Semantic oracle for the recovered MobiClip coefficient transform paths.

This module intentionally contains no original payload bytes.  Its JSON mode
is suitable for comparing coefficients and reconstructed blocks captured from
an emulator with the isolated C++ reconstruction in mobiclip_reference.cpp.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from dataclasses import dataclass
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

BLOCK8X8_COEFFICIENT_MASKS = (
    0, 31, 63, 15, 8, 4, 2, 1, 11, 14, 27, 13, 3, 7, 12, 23,
    29, 10, 30, 5, 16, 47, 55, 59, 19, 61, 62, 9, 28, 6, 21, 26,
    51, 17, 18, 20, 24, 32, 60, 53, 25, 22, 58, 48, 49, 50, 39, 52,
    43, 45, 57, 56, 35, 54, 46, 33, 37, 34, 36, 44, 42, 40, 41, 38,
)
PFRAME_BLOCK8X8_COEFFICIENT_MASKS = (
    0, 15, 4, 1, 8, 2, 12, 3, 5, 10, 13, 7, 14, 11, 31, 9,
    6, 16, 63, 30, 23, 29, 27, 28, 19, 24, 26, 18, 17, 20, 21, 32,
    47, 22, 25, 55, 61, 62, 59, 60, 51, 53, 33, 36, 34, 40, 35, 44,
    48, 39, 45, 37, 58, 43, 46, 42, 49, 52, 56, 50, 41, 38, 57, 54,
)
BLOCK4X4_COEFFICIENT_MASKS = (
    15, 0, 2, 1, 4, 8, 12, 3, 11, 13, 14, 7, 10, 5, 9, 6,
)
PFRAME_BLOCK4X4_COEFFICIENT_MASKS = (
    0, 4, 1, 8, 2, 12, 3, 5, 10, 15, 7, 13, 14, 11, 9, 6,
)
PACKED_AVERAGE_LANE_MASK = 0x7F7F7F7F

PFRAME_MODE_PREFIX = (
    1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 8, 8, 9, 9, 9, 9,
    4, 3, 2, 2, 7, 7, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0,
)
PFRAME_MODE_LENGTHS = (2, 2, 4, 5, 5, 5, 5, 4, 3, 3)
MOTION16_MODE_PREFIX = (0, 0, 0, 0, 9, 9, 5, 4, 2, 2, 3, 8, 1, 1, 1, 1)
MOTION16_MODE_LENGTHS = (2, 2, 3, 4, 4, 4, 0, 0, 4, 3)
MOTION8X16_MODE_PREFIX = (3, 3, 9, 5, 0, 0, 0, 0, 4, 8, 2, 2, 1, 1, 1, 1)
MOTION8X16_MODE_LENGTHS = (2, 2, 3, 3, 4, 4, 0, 0, 4, 4)
INTRA16_MODE_PREFIX = (
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    3, 3, 3, 3, 4, 4, 8, 5, 2, 2, 2, 2, 0, 0, 0, 0,
)
INTRA16_MODE_LENGTHS = (3, 1, 3, 3, 4, 5, 0, 0, 5, 0)

# All compact mode alphabets found beside the payload's relative dispatch
# tables.  Prefix rows are replicated direct-lookup tables; the length row is
# indexed by the selected mode.  Several contexts intentionally share a code
# length set while dispatching to different specialized ARM routines.
INLINE_MODE_CODEBOOKS = {
    "pframe_macroblock": (PFRAME_MODE_PREFIX, PFRAME_MODE_LENGTHS),
    "motion16": (MOTION16_MODE_PREFIX, MOTION16_MODE_LENGTHS),
    "motion8x16": (MOTION8X16_MODE_PREFIX, MOTION8X16_MODE_LENGTHS),
    "intra16": (INTRA16_MODE_PREFIX, INTRA16_MODE_LENGTHS),
    "motion8x8": (
        (0, 0, 0, 0, 5, 4, 8, 8, 2, 2, 3, 9, 1, 1, 1, 1),
        (2, 2, 3, 4, 4, 4, 0, 0, 3, 4),
    ),
    "motion16x4": (
        (0, 0, 0, 0, 3, 3, 8, 4, 2, 2, 5, 9, 1, 1, 1, 1),
        (2, 2, 3, 3, 4, 4, 0, 0, 4, 4),
    ),
    "motion16x2": (
        (1, 1, 1, 1, 1, 1, 1, 1, 9, 4, 2, 2, 0, 0, 5, 3),
        (3, 1, 3, 4, 4, 4, 0, 0, 0, 4),
    ),
    "motion8x8_alt": (
        (0, 0, 0, 0, 3, 3, 5, 9, 4, 8, 2, 2, 1, 1, 1, 1),
        (2, 2, 3, 3, 4, 4, 0, 0, 4, 4),
    ),
    "predicted_mode_a": (
        (2, 2, 2, 2, 8, 9, 3, 3, 5, 4, 0, 0, 1, 1, 1, 1),
        (3, 2, 2, 3, 4, 4, 0, 0, 4, 4),
    ),
    "predicted_mode_b": (
        (2, 2, 2, 2, 4, 4, 9, 5, 3, 3, 0, 0, 1, 1, 1, 1),
        (3, 2, 2, 3, 3, 4, 0, 0, 0, 4),
    ),
    "predicted_mode_c": (
        (0, 0, 0, 0, 3, 3, 9, 5, 8, 4, 2, 2, 1, 1, 1, 1),
        (2, 2, 3, 3, 4, 4, 0, 0, 4, 4),
    ),
    "predicted_mode_d": (
        (
            0, 0, 0, 0, 0, 0, 0, 0,
            4, 4, 4, 4, 3, 3, 3, 3,
            8, 9, 5, 5, 2, 2, 2, 2,
            1, 1, 1, 1, 1, 1, 1, 1,
        ),
        (2, 2, 3, 3, 3, 4, 0, 0, 5, 5),
    ),
    "predicted_mode_e": (
        (0, 0, 0, 0, 4, 4, 9, 5, 3, 3, 2, 2, 1, 1, 1, 1),
        (2, 2, 3, 3, 3, 4, 0, 0, 0, 4),
    ),
    "predicted_mode_f": (
        (
            0, 0, 0, 0, 0, 0, 0, 0,
            2, 2, 2, 2, 2, 2, 2, 2,
            3, 3, 3, 3, 4, 4, 8, 5,
            1, 1, 1, 1, 1, 1, 1, 1,
        ),
        (2, 2, 2, 3, 4, 5, 0, 0, 5, 0),
    ),
    "predicted_mode_g": (
        (0, 0, 0, 0, 4, 4, 8, 5, 3, 3, 2, 2, 1, 1, 1, 1),
        (2, 2, 3, 3, 3, 4, 0, 0, 4, 0),
    ),
    "predicted_mode_h": (
        (5, 4, 1, 1, 0, 0, 3, 2),
        (2, 2, 3, 3, 3, 3, 0, 0, 0, 0),
    ),
}

# Exact get_index(height) * 4 + get_index(width) order used by recursive
# motion partitioning.  Each entry above was matched byte-for-byte to the
# corresponding canonical VLC context.
MOTION_CONTEXT_CODEBOOKS = (
    "pframe_macroblock", "motion16", "motion8x16", "intra16",
    "motion8x8", "motion8x8_alt", "predicted_mode_c", "predicted_mode_f",
    "motion16x4", "predicted_mode_a", "predicted_mode_d", "predicted_mode_g",
    "motion16x2", "predicted_mode_b", "predicted_mode_e", "predicted_mode_h",
)


@dataclass(frozen=True)
class RunLevelSymbol:
    run: int
    level: int
    last: bool


@dataclass(frozen=True)
class FrameHeader:
    intra: bool
    format_variant: bool
    coefficient_table_variant: int
    quantizer: int


@dataclass(frozen=True)
class MotionVector:
    x: int
    y: int


@dataclass(frozen=True)
class DecodedIFrame:
    header: FrameHeader
    width: int
    height: int
    luma: bytes
    chroma_first: bytes
    chroma_second: bytes
    bits_consumed: int


@dataclass(frozen=True)
class DecodedPFrame:
    header: FrameHeader
    width: int
    height: int
    luma: bytes
    chroma_first: bytes
    chroma_second: bytes
    bits_consumed: int


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

    def peek_bits(self, count: int) -> int:
        start = self.bit_position
        try:
            return self.read_bits(count)
        finally:
            self.bit_position = start

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


class ReservoirBitReader:
    """Replay the payload's r1/r2/r3 bit-reader state from an emulator capture."""

    def __init__(
        self, reservoir: int, bits_remaining: int, next_words: Iterable[int]
    ):
        self.reservoir = _u32(reservoir)
        self.bits_remaining = int(bits_remaining)
        self.next_words = [int(word) & 0xFFFF for word in next_words]
        self.words_consumed = 0
        self.bit_position = 0

    def _refill(self) -> None:
        if self.words_consumed >= len(self.next_words):
            raise EOFError("captured MobiClip refill words exhausted")
        word = self.next_words[self.words_consumed]
        self.words_consumed += 1
        self.bits_remaining += 16
        shift = 16 - self.bits_remaining
        if not 0 <= shift < 32:
            raise ValueError("captured bit count produced an invalid refill shift")
        self.reservoir = _u32(self.reservoir | (word << shift))

    def read_bit(self) -> int:
        value = self.reservoir >> 31
        self.reservoir = _u32(self.reservoir << 1)
        self.bits_remaining -= 1
        self.bit_position += 1
        if self.bits_remaining < 0:
            self._refill()
        return value

    def read_bits(self, count: int) -> int:
        if not 0 <= count <= 32:
            raise ValueError("bit count must be in 0..32")
        snapshot = self.snapshot()
        value = 0
        try:
            for _ in range(count):
                value = (value << 1) | self.read_bit()
        except (EOFError, ValueError):
            self.restore(snapshot)
            raise
        return value

    def peek_bits(self, count: int) -> int:
        snapshot = self.snapshot()
        try:
            return self.read_bits(count)
        finally:
            self.restore(snapshot)

    def snapshot(self) -> tuple[int, int, int, int]:
        return (
            self.reservoir,
            self.bits_remaining,
            self.words_consumed,
            self.bit_position,
        )

    def restore(self, snapshot: tuple[int, int, int, int]) -> None:
        (
            self.reservoir,
            self.bits_remaining,
            self.words_consumed,
            self.bit_position,
        ) = snapshot


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


def decode_frame_header(
    reader: WordBitReader,
    previous_quantizer: int,
    previous_format_variant: bool,
) -> FrameHeader:
    """Parse the exact I/P prefix consumed by MobiClip_DecodeFrameCore."""
    intra = bool(reader.read_bit())
    if intra:
        format_variant = bool(reader.read_bit())
        table_variant = reader.read_bit()
        quantizer = reader.read_bits(6)
    else:
        format_variant = bool(previous_format_variant)
        table_variant = 0
        quantizer = previous_quantizer + reader.read_signed_exp_golomb()
    if not 12 <= quantizer <= 53:
        raise ValueError("decoded quantizer is outside the Nintendo DS range")
    return FrameHeader(intra, format_variant, table_variant, quantizer)


def median_motion_vector(
    left: MotionVector, upper_left: MotionVector, upper: MotionVector
) -> MotionVector:
    """Match the component-wise three-neighbour median in the P-frame loop."""
    return MotionVector(
        sorted((left.x, upper_left.x, upper.x))[1],
        sorted((left.y, upper_left.y, upper.y))[1],
    )


def decode_predicted_motion(
    reader: WordBitReader, prediction: MotionVector
) -> MotionVector:
    """Add the payload's x-then-y signed Exp-Golomb motion deltas."""
    delta_x = reader.read_signed_exp_golomb()
    delta_y = reader.read_signed_exp_golomb()
    return MotionVector(
        _s32(prediction.x + delta_x),
        _s32(prediction.y + delta_y),
    )


def reset_prediction_borders(prediction_modes: Iterable[int]) -> list[int]:
    modes = list(prediction_modes)
    if len(modes) != 40:
        raise ValueError("expected 40 prediction-cache entries")
    for index in (1, 2, 3, 4, 8, 16, 24, 32):
        modes[index] = 9
    return modes


def decode_predicted_intra_mode(
    reader: WordBitReader,
    prediction_modes: list[int] | bytearray,
    block_x: int,
    block_y: int,
    size: int,
) -> int:
    """Decode one mode and update the native 40-byte prediction cache."""
    if len(prediction_modes) != 40:
        raise ValueError("expected 40 prediction-cache entries")
    if size not in (4, 8):
        raise ValueError("predicted intra block size must be 4 or 8")
    if block_x < 0 or block_y < 0:
        raise ValueError("predicted intra coordinates cannot be negative")
    index = (block_y & 0xC) | ((block_x // 4) % 4)
    predicted = min(
        prediction_modes[index],
        9 if index % 4 == 0 else prediction_modes[index + 3],
    )
    if predicted == 9:
        predicted = 3
    if reader.read_bit() == 0:
        alternative = reader.read_bits(3)
        predicted = alternative + (1 if alternative >= predicted else 0)
    prediction_modes[index + 4] = predicted
    if size == 8:
        prediction_modes[index + 5] = predicted
        prediction_modes[index + 8] = predicted
        prediction_modes[index + 9] = predicted
    return predicted


def _decode_prefix_mode(
    reader: WordBitReader,
    prefix_table: tuple[int, ...],
    lengths: tuple[int, ...],
) -> int:
    prefix_bits = (len(prefix_table) - 1).bit_length()
    if 1 << prefix_bits != len(prefix_table):
        raise ValueError("mode prefix table size must be a power of two")
    mode = prefix_table[reader.peek_bits(prefix_bits)]
    if not 0 <= mode < len(lengths) or lengths[mode] == 0:
        raise ValueError("mode prefix selected a reserved dispatch slot")
    reader.read_bits(lengths[mode])
    return mode


def decode_pframe_macroblock_mode(reader: WordBitReader) -> int:
    return _decode_prefix_mode(reader, PFRAME_MODE_PREFIX, PFRAME_MODE_LENGTHS)


def decode_motion16_mode(reader: WordBitReader) -> int:
    return _decode_prefix_mode(reader, MOTION16_MODE_PREFIX, MOTION16_MODE_LENGTHS)


def decode_motion8x16_mode(reader: WordBitReader) -> int:
    return _decode_prefix_mode(reader, MOTION8X16_MODE_PREFIX, MOTION8X16_MODE_LENGTHS)


def decode_intra16_mode(reader: WordBitReader) -> int:
    return _decode_prefix_mode(reader, INTRA16_MODE_PREFIX, INTRA16_MODE_LENGTHS)


def decode_inline_mode(reader: WordBitReader, codebook: str) -> int:
    """Decode any of the 16 compact mode contexts embedded in the payload."""
    try:
        prefix_table, lengths = INLINE_MODE_CODEBOOKS[codebook]
    except KeyError as error:
        raise ValueError(f"unknown MobiClip mode codebook: {codebook}") from error
    return _decode_prefix_mode(reader, prefix_table, lengths)


def motion_context_codebook(width: int, height: int) -> str:
    """Return the native VLC context for a recursive motion block size."""
    size_index = {16: 0, 8: 1, 4: 2, 2: 3}
    try:
        context = size_index[height] * 4 + size_index[width]
    except KeyError as error:
        raise ValueError("motion dimensions must be 2, 4, 8 or 16") from error
    return MOTION_CONTEXT_CODEBOOKS[context]


def _trunc_div(value: int, divisor: int) -> int:
    """C-style signed integer division by a positive divisor."""
    return value // divisor if value >= 0 else -((-value) // divisor)


def predict_intra_block(
    frame: bytearray | list[int],
    width: int,
    height: int,
    stride: int,
    block_x: int,
    block_y: int,
    size: int,
    mode: int,
    plane_delta: int = 0,
) -> list[int]:
    """Reconstruct one native MobiClip intra-prediction block in place."""
    if size not in (4, 8, 16):
        raise ValueError("intra block size must be 4, 8 or 16")
    if mode not in range(9):
        raise ValueError("intra prediction mode must be in 0..8")
    if width <= 0 or height <= 0 or stride < width:
        raise ValueError("invalid frame dimensions or stride")
    if block_x < 0 or block_y < 0:
        raise ValueError("intra block origin cannot be negative")
    if block_x + size > width or block_y + size > height:
        raise ValueError("intra block exceeds the frame")
    if len(frame) < stride * height:
        raise ValueError("intra frame buffer is too short")
    if isinstance(frame, bytes):
        raise TypeError("intra frame buffer must be mutable")
    if any(not 0 <= value <= 255 for value in frame):
        raise ValueError("intra frame samples must be bytes")

    def sample(relative_x: int, relative_y: int) -> int:
        x, y = relative_x, relative_y
        if x == -1 and y >= size:
            y = size - 1
        elif x >= -1 and y >= -1:
            pass
        elif x == -1 and y == -2:
            x, y = 0, -1
        elif x == -2 and y == -1:
            x, y = -1, 0
        absolute_x = max(0, min(width - 1, block_x + x))
        absolute_y = max(0, min(height - 1, block_y + y))
        return frame[absolute_y * stride + absolute_x]

    def half(a: int, b: int) -> int:
        return (a + b + 1) // 2

    def half3(a: int, b: int, c: int) -> int:
        return (a + 2 * b + c + 2) // 4

    def directional(relative_x: int, relative_y: int) -> int:
        x, y = relative_x, relative_y
        if mode == 0:
            return sample(x, y - 1)
        if mode == 1:
            return sample(x - 1, y)
        if mode == 4:
            edge_y = y + x // 2
            if x % 2 == 0:
                return half(sample(-1, edge_y), sample(-1, edge_y + 1))
            return half3(
                sample(-1, edge_y),
                sample(-1, edge_y + 1),
                sample(-1, edge_y + 2),
            )
        if mode == 5:
            if x == 0:
                return half(sample(-1, y - 1), sample(-1, y))
            if y == 0:
                return half3(sample(x - 3, -1), sample(x - 2, -1), sample(x - 1, -1))
            if x == 1:
                return half3(sample(-1, y - 2), sample(-1, y - 1), sample(-1, y))
            return sample(x - 2, y - 1)
        if mode == 6:
            if y == 0:
                return half(sample(x - 1, -1), sample(x, -1))
            if x == 0:
                return half3(sample(-1, y - 3), sample(-1, y - 2), sample(-1, y - 1))
            if y == 1:
                return half3(sample(x - 2, -1), sample(x - 1, -1), sample(x, -1))
            return sample(x - 1, y - 2)
        if mode == 7:
            center = sample(x - 1, y - 1)
            if x and y:
                return center
            side_a = sample(-1, y) if x == 0 else sample(x - 2, -1)
            side_b = sample(x, -1) if y == 0 else sample(-1, y - 2)
            return half3(side_a, center, side_b)
        if mode == 8:
            if y == 0:
                return half(sample(x, -1), sample(x + 1, -1))
            if y == 1:
                return half3(sample(x, -1), sample(x + 1, -1), sample(x + 2, -1))
            if x < size - 1:
                return sample(x + 1, y - 2)
            edge_x = y // 2 + size - 1
            if y % 2 == 0:
                return half(sample(edge_x, -1), sample(edge_x + 1, -1))
            return half3(
                sample(edge_x, -1),
                sample(edge_x + 1, -1),
                sample(edge_x + 2, -1),
            )
        raise AssertionError("non-directional intra mode")

    if mode == 2:
        plane_delta = max(-(1 << 16), min(1 << 16, plane_delta))
        bottommost = frame[(block_y + size - 1) * stride + max(block_x - 1, 0)]
        rightmost = frame[max(block_y - 1, 0) * stride + block_x + size - 1]
        average = (bottommost + rightmost + 1) // 2 + 2 * plane_delta

        def adjust(value: int) -> int:
            return _asr(value + 1, 1) if size == 16 else value

        shift = 3 if adjust(size) == 8 else 2
        top = [frame[max(block_y - 1, 0) * stride + block_x + x] for x in range(size)]
        left = [frame[(block_y + y) * stride + max(block_x - 1, 0)] for y in range(size)]
        slope_x = adjust(average - bottommost)
        slope_y = adjust(average - rightmost)
        horizontal = [
            adjust(((bottommost - value) << shift) + slope_x * (x + 1))
            for x, value in enumerate(top)
        ]
        vertical = [
            adjust(((rightmost - value) << shift) + slope_y * (y + 1))
            for y, value in enumerate(left)
        ]
        for y in range(size):
            for x in range(size):
                correction = _asr(
                    horizontal[x] * (y + 1) + vertical[y] * (x + 1),
                    2 * shift,
                )
                value = _trunc_div(top[x] + left[y] + correction + 1, 2) & 0xFF
                frame[(block_y + y) * stride + block_x + x] = value
    elif mode == 3:
        if block_x == 0 and block_y == 0:
            fill = 0x80
        elif block_x and block_y:
            left_sum = sum(frame[(block_y + y) * stride + block_x - 1] for y in range(size))
            top_sum = sum(frame[(block_y - 1) * stride + block_x + x] for x in range(size))
            fill = (((left_sum + top_sum) * 2) // (2 * size) + 1) // 2
        elif block_x:
            total = sum(frame[(block_y + y) * stride + block_x - 1] for y in range(size))
            fill = ((total * 2) // size + 1) // 2
        else:
            total = sum(frame[(block_y - 1) * stride + block_x + x] for x in range(size))
            fill = ((total * 2) // size + 1) // 2
        for y in range(size):
            for x in range(size):
                frame[(block_y + y) * stride + block_x + x] = fill
    else:
        for y in range(size):
            for x in range(size):
                frame[(block_y + y) * stride + block_x + x] = directional(x, y)

    return [
        frame[(block_y + y) * stride + block_x + x]
        for y in range(size)
        for x in range(size)
    ]


def compensate_motion_block(
    reference: bytes | bytearray | list[int],
    destination: bytearray | list[int],
    frame_width: int,
    frame_height: int,
    reference_stride: int,
    destination_stride: int,
    block_x: int,
    block_y: int,
    block_width: int,
    block_height: int,
    motion: MotionVector,
) -> list[int]:
    """Copy one native half-sample motion-compensated byte-plane block."""
    if frame_width <= 0 or frame_height <= 0:
        raise ValueError("motion frame dimensions must be positive")
    if reference_stride < frame_width or destination_stride < frame_width:
        raise ValueError("motion plane stride is too small")
    if block_width <= 0 or block_height <= 0:
        raise ValueError("motion block dimensions must be positive")
    if block_x < 0 or block_y < 0:
        raise ValueError("motion block origin cannot be negative")
    if block_x + block_width > frame_width or block_y + block_height > frame_height:
        raise ValueError("motion destination block exceeds the frame")
    if len(reference) < reference_stride * frame_height:
        raise ValueError("motion reference plane is too short")
    if len(destination) < destination_stride * frame_height:
        raise ValueError("motion destination plane is too short")
    if isinstance(destination, bytes):
        raise TypeError("motion destination plane must be mutable")

    source_x = block_x + (motion.x >> 1)
    source_y = block_y + (motion.y >> 1)
    horizontal_half = motion.x & 1
    vertical_half = motion.y & 1
    if source_x < 0 or source_y < 0:
        raise ValueError("motion source block begins outside the frame")
    if source_x + block_width + horizontal_half > frame_width:
        raise ValueError("motion source block exceeds the frame horizontally")
    if source_y + block_height + vertical_half > frame_height:
        raise ValueError("motion source block exceeds the frame vertically")

    def source(x: int, y: int) -> int:
        return reference[(source_y + y) * reference_stride + source_x + x]

    for y in range(block_height):
        for x in range(block_width):
            if not horizontal_half and not vertical_half:
                value = source(x, y)
            elif horizontal_half and not vertical_half:
                value = (source(x, y) >> 1) + (source(x + 1, y) >> 1)
            elif not horizontal_half and vertical_half:
                value = (source(x, y) >> 1) + (source(x, y + 1) >> 1)
            else:
                upper = ((source(x, y) >> 1) + (source(x + 1, y) >> 1)) >> 1
                lower = (
                    (source(x, y + 1) >> 1) + (source(x + 1, y + 1) >> 1)
                ) >> 1
                value = upper + lower
            destination[(block_y + y) * destination_stride + block_x + x] = value

    return [
        destination[(block_y + y) * destination_stride + block_x + x]
        for y in range(block_height)
        for x in range(block_width)
    ]


def _read_packed_run_level(
    reader: WordBitReader, lookup: list[int]
) -> tuple[int, int, bool, bool]:
    packed = lookup[reader.peek_bits(12)]
    consumed = packed & 0xF
    level = (packed >> 4) & 0x1F
    run = (packed >> 9) & 0x3F
    last = bool(packed & 0x8000)
    if consumed == 0 or level == 0:
        raise ValueError("invalid packed run/level lookup entry")
    consumed_value = reader.read_bits(consumed)
    return run, level, last, bool(consumed_value & 1)


def decode_run_level_symbol(
    reader: WordBitReader,
    lookup_entries: Iterable[int],
    residue_bytes: bytes | bytearray | memoryview,
) -> RunLevelSymbol:
    """Decode one symbol using the payload's 4096-entry VLC table layout."""
    lookup = list(lookup_entries)
    residue = bytes(residue_bytes)
    if len(lookup) != 4096:
        raise ValueError("expected 4096 packed VLC lookup entries")
    if len(residue) != 256:
        raise ValueError("expected 256 VLC residue bytes")

    if reader.peek_bits(7) != 3:
        run, level, last, negative = _read_packed_run_level(reader, lookup)
        return RunLevelSymbol(run, -level if negative else level, last)

    reader.read_bits(7)
    if reader.read_bit() == 0:
        run, level, last, negative = _read_packed_run_level(reader, lookup)
        level += residue[(64 if last else 0) + run]
        return RunLevelSymbol(run, -level if negative else level, last)

    if reader.read_bit() == 0:
        run, level, last, negative = _read_packed_run_level(reader, lookup)
        run += residue[128 + (64 if last else 0) + level]
        return RunLevelSymbol(run, -level if negative else level, last)

    last = bool(reader.read_bit())
    run = reader.read_bits(6)
    raw_level = reader.read_bits(12)
    level = raw_level - 0x1000 if raw_level & 0x800 else raw_level
    return RunLevelSymbol(run, level, last)


def place_run_level_coefficients(
    symbols: Iterable[RunLevelSymbol],
    quant_scan: Iterable[int],
    coefficient_count: int,
) -> list[int]:
    """Place one terminated run/level sequence into a cleared coefficient block."""
    if coefficient_count not in (16, 64):
        raise ValueError("coefficient count must select a 4x4 or 8x8 block")
    packed_scan = list(quant_scan)
    if len(packed_scan) < coefficient_count:
        raise ValueError("quant-scan table is shorter than the coefficient block")

    coefficients = [0] * coefficient_count
    position = 0
    for symbol in symbols:
        if symbol.run < 0 or position >= coefficient_count:
            raise ValueError("run exceeds the coefficient block")
        if symbol.run >= coefficient_count - position:
            raise ValueError("run exceeds the coefficient block")
        position += symbol.run
        index, value = unpack_quant_scan(packed_scan[position], symbol.level)
        if index >= coefficient_count:
            raise ValueError("quant-scan index exceeds the coefficient block")
        coefficients[index] = value
        position += 1
        if symbol.last:
            return coefficients
    raise ValueError("run/level sequence has no last symbol")


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


def _decode_coefficient_block(
    reader: WordBitReader,
    lookup: list[int],
    residue: bytes,
    quant_scan: list[int],
    size: int,
) -> list[int]:
    symbols = []
    while True:
        symbol = decode_run_level_symbol(reader, lookup, residue)
        symbols.append(symbol)
        if symbol.last:
            break
        if len(symbols) > size * size:
            raise ValueError("coefficient block has no terminating symbol")
    return place_run_level_coefficients(symbols, quant_scan, size * size)


def _add_coefficient_block(
    reader: WordBitReader,
    plane: bytearray,
    stride: int,
    block_x: int,
    block_y: int,
    size: int,
    lookup: list[int],
    residue: bytes,
    quant_scan: list[int],
) -> None:
    coefficients = _decode_coefficient_block(
        reader, lookup, residue, quant_scan, size
    )
    residual = inverse_transform(coefficients, size)
    for y in range(size):
        for x in range(size):
            index = (block_y + y) * stride + block_x + x
            plane[index] = max(0, min(255, plane[index] + residual[y * size + x]))


def _predict_intra(
    reader: WordBitReader,
    plane: bytearray,
    width: int,
    height: int,
    stride: int,
    block_x: int,
    block_y: int,
    size: int,
    mode: int,
) -> None:
    if mode == 9:
        return
    plane_delta = reader.read_signed_exp_golomb() if mode == 2 else 0
    predict_intra_block(
        plane, width, height, stride,
        block_x, block_y, size, mode, plane_delta,
    )


def _process_iframe_block(
    reader: WordBitReader,
    plane: bytearray,
    width: int,
    height: int,
    stride: int,
    block_x: int,
    block_y: int,
    mode: int,
    has_coefficients: bool,
    prediction_modes: bytearray,
    lookup: list[int],
    residue: bytes,
    quant_scan8: list[int],
    quant_scan4: list[int],
) -> None:
    if not has_coefficients:
        if mode < 0:
            mode = decode_predicted_intra_mode(
                reader, prediction_modes, block_x, block_y, 8
            )
        _predict_intra(
            reader, plane, width, height, stride,
            block_x, block_y, 8, mode,
        )
        return

    partition = reader.read_unsigned_exp_golomb()
    if partition > len(BLOCK4X4_COEFFICIENT_MASKS):
        raise ValueError("invalid I-frame coefficient partition")
    if partition == 0:
        if mode < 0:
            mode = decode_predicted_intra_mode(
                reader, prediction_modes, block_x, block_y, 8
            )
        _predict_intra(
            reader, plane, width, height, stride,
            block_x, block_y, 8, mode,
        )
        _add_coefficient_block(
            reader, plane, stride, block_x, block_y, 8,
            lookup, residue, quant_scan8,
        )
        return

    flags = BLOCK4X4_COEFFICIENT_MASKS[partition - 1]
    for local_y in (0, 4):
        for local_x in (0, 4):
            submode = mode
            if submode < 0:
                submode = decode_predicted_intra_mode(
                    reader, prediction_modes,
                    block_x + local_x, block_y + local_y, 4,
                )
            _predict_intra(
                reader, plane, width, height, stride,
                block_x + local_x, block_y + local_y, 4, submode,
            )
            if flags & 1:
                _add_coefficient_block(
                    reader, plane, stride,
                    block_x + local_x, block_y + local_y, 4,
                    lookup, residue, quant_scan4,
                )
            flags >>= 1


def _decode_intra_macroblock(
    reader: WordBitReader,
    luma: bytearray,
    chroma_first: bytearray,
    chroma_second: bytearray,
    width: int,
    height: int,
    macroblock_x: int,
    macroblock_y: int,
    predicted_modes: bool,
    prediction_modes: bytearray,
    lookup: list[int],
    residue: bytes,
    quant_scan8: list[int],
    quant_scan4: list[int],
) -> None:
    flags_index = reader.read_unsigned_exp_golomb()
    if flags_index >= len(BLOCK8X8_COEFFICIENT_MASKS):
        raise ValueError("invalid intra macroblock coefficient mask")
    flags = BLOCK8X8_COEFFICIENT_MASKS[flags_index]

    if predicted_modes:
        luma_mode = -1
    else:
        luma_mode = reader.read_bits(3)
        if luma_mode == 2:
            _predict_intra(
                reader, luma, width, height, width,
                macroblock_x, macroblock_y, 16, luma_mode,
            )
            luma_mode = 9
    for local_y in (0, 8):
        for local_x in (0, 8):
            _process_iframe_block(
                reader, luma, width, height, width,
                macroblock_x + local_x, macroblock_y + local_y,
                luma_mode, bool(flags & 1), prediction_modes,
                lookup, residue, quant_scan8, quant_scan4,
            )
            flags >>= 1

    chroma_width, chroma_height = width // 2, height // 2
    chroma_mode = reader.read_bits(3)
    if chroma_mode == 2:
        for plane in (chroma_first, chroma_second):
            _predict_intra(
                reader, plane, chroma_width, chroma_height, chroma_width,
                macroblock_x // 2, macroblock_y // 2, 8, chroma_mode,
            )
        chroma_mode = 9
    for plane in (chroma_first, chroma_second):
        _process_iframe_block(
            reader, plane, chroma_width, chroma_height, chroma_width,
            macroblock_x // 2, macroblock_y // 2,
            chroma_mode, bool(flags & 1), prediction_modes,
            lookup, residue, quant_scan8, quant_scan4,
        )
        flags >>= 1


def decode_iframe(
    bitstream: bytes | bytearray | memoryview,
    width: int,
    height: int,
    coefficient_tables: tuple[bytes, bytes],
) -> DecodedIFrame:
    """Decode one complete MODS I-frame using the reconstructed semantics.

    The two chroma planes are returned in bitstream order. For the MODS/YCoCg
    variant this is Cg first and Co second; FFmpeg's planar output stores them
    as Co then Cg.
    """
    if width <= 0 or height <= 0 or width % 16 or height % 16:
        raise ValueError("MobiClip frame dimensions must be positive multiples of 16")
    if len(coefficient_tables) != 2:
        raise ValueError("expected both MobiClip coefficient tables")
    tables = [split_vlc_table(data) for data in coefficient_tables]

    # The native caller and FFmpeg both provide safe look-ahead past the coded
    # payload. Compact tables may peek 5 or 12 bits when the selected codeword
    # itself is shorter and ends in the final word.
    reader = WordBitReader(bytes(bitstream) + bytes(16))
    header = decode_frame_header(reader, 12, False)
    if not header.intra:
        raise ValueError("decode_iframe requires an I-frame bitstream")
    lookup, residue = tables[header.coefficient_table_variant]
    quant_scan8, quant_scan4 = build_quant_scan_tables(header.quantizer)
    luma = bytearray(width * height)
    chroma_width, chroma_height = width // 2, height // 2
    chroma_first = bytearray(chroma_width * chroma_height)
    chroma_second = bytearray(chroma_width * chroma_height)
    prediction_modes = bytearray([9] * 40)

    for macroblock_y in range(0, height, 16):
        for macroblock_x in range(0, width, 16):
            predicted_modes = bool(reader.read_bit())
            _decode_intra_macroblock(
                reader, luma, chroma_first, chroma_second,
                width, height, macroblock_x, macroblock_y, predicted_modes,
                prediction_modes, lookup, residue, quant_scan8, quant_scan4,
            )

    return DecodedIFrame(
        header=header,
        width=width,
        height=height,
        luma=bytes(luma),
        chroma_first=bytes(chroma_first),
        chroma_second=bytes(chroma_second),
        bits_consumed=reader.bit_position,
    )


def _add_pframe_coefficients(
    reader: WordBitReader,
    plane: bytearray,
    stride: int,
    block_x: int,
    block_y: int,
    lookup: list[int],
    residue: bytes,
    quant_scan8: list[int],
    quant_scan4: list[int],
) -> None:
    partition = reader.read_unsigned_exp_golomb()
    if partition == 0:
        _add_coefficient_block(
            reader, plane, stride, block_x, block_y, 8,
            lookup, residue, quant_scan8,
        )
        return
    if partition >= len(PFRAME_BLOCK4X4_COEFFICIENT_MASKS):
        raise ValueError("invalid P-frame coefficient partition")
    flags = PFRAME_BLOCK4X4_COEFFICIENT_MASKS[partition]
    for local_y in (0, 4):
        for local_x in (0, 4):
            if flags & 1:
                _add_coefficient_block(
                    reader, plane, stride,
                    block_x + local_x, block_y + local_y, 4,
                    lookup, residue, quant_scan4,
                )
            flags >>= 1


def _predict_motion_recursive(
    reader: WordBitReader,
    mode: int,
    block_width: int,
    block_height: int,
    block_x: int,
    block_y: int,
    motion_slot: int,
    motion: list[MotionVector],
    histories: list[DecodedIFrame | DecodedPFrame],
    luma: bytearray,
    chroma_first: bytearray,
    chroma_second: bytearray,
    frame_width: int,
    frame_height: int,
) -> None:
    if mode <= 5:
        vector = motion[0]
        if mode > 0:
            vector = decode_predicted_motion(reader, vector)
        motion[motion_slot] = vector
        history_index = max(1, mode) - 1
        if history_index >= len(histories):
            raise ValueError("motion references an unavailable history frame")
        reference = histories[history_index]
        compensate_motion_block(
            reference.luma, luma, frame_width, frame_height,
            frame_width, frame_width, block_x, block_y,
            block_width, block_height, vector,
        )
        chroma_vector = MotionVector(vector.x >> 1, vector.y >> 1)
        chroma_width, chroma_height = frame_width // 2, frame_height // 2
        for source, destination in (
            (reference.chroma_first, chroma_first),
            (reference.chroma_second, chroma_second),
        ):
            compensate_motion_block(
                source, destination, chroma_width, chroma_height,
                chroma_width, chroma_width, block_x // 2, block_y // 2,
                block_width // 2, block_height // 2, chroma_vector,
            )
        return

    if mode not in (8, 9):
        raise ValueError("reserved mode reached recursive motion decoder")
    split_x = 0 if mode == 8 else block_width // 2
    split_y = block_height // 2 if mode == 8 else 0
    child_width = block_width - split_x
    child_height = block_height - split_y
    codebook = motion_context_codebook(child_width, child_height)
    for child in range(2):
        child_mode = decode_inline_mode(reader, codebook)
        _predict_motion_recursive(
            reader, child_mode, child_width, child_height,
            block_x + child * split_x, block_y + child * split_y,
            motion_slot, motion, histories,
            luma, chroma_first, chroma_second, frame_width, frame_height,
        )


def decode_pframe(
    bitstream: bytes | bytearray | memoryview,
    width: int,
    height: int,
    coefficient_table0: bytes,
    histories: list[DecodedIFrame | DecodedPFrame],
    previous_quantizer: int,
    previous_format_variant: bool,
) -> DecodedPFrame:
    """Decode one complete P-frame from a MODS packet payload."""
    if width <= 0 or height <= 0 or width % 16 or height % 16:
        raise ValueError("MobiClip frame dimensions must be positive multiples of 16")
    if not histories:
        raise ValueError("a P-frame requires at least one history frame")
    lookup, residue = split_vlc_table(coefficient_table0)
    reader = WordBitReader(bytes(bitstream) + bytes(16))
    header = decode_frame_header(reader, previous_quantizer, previous_format_variant)
    if header.intra:
        raise ValueError("decode_pframe requires a P-frame bitstream")
    quant_scan8, quant_scan4 = build_quant_scan_tables(header.quantizer)
    luma = bytearray(width * height)
    chroma_width, chroma_height = width // 2, height // 2
    chroma_first = bytearray(chroma_width * chroma_height)
    chroma_second = bytearray(chroma_width * chroma_height)
    prediction_modes = bytearray([9] * 40)
    motion = [MotionVector(0, 0) for _ in range(width // 16 + 3)]

    for macroblock_y in range(0, height, 16):
        for macroblock_x in range(0, width, 16):
            column = macroblock_x // 16
            motion[0] = median_motion_vector(
                motion[column + 1], motion[column + 2], motion[column + 3]
            )
            motion[column + 2] = MotionVector(0, 0)
            mode = decode_inline_mode(reader, MOTION_CONTEXT_CODEBOOKS[0])
            if mode in (6, 7):
                _decode_intra_macroblock(
                    reader, luma, chroma_first, chroma_second,
                    width, height, macroblock_x, macroblock_y, mode == 7,
                    prediction_modes, lookup, residue, quant_scan8, quant_scan4,
                )
                continue

            _predict_motion_recursive(
                reader, mode, 16, 16, macroblock_x, macroblock_y,
                column + 2, motion, histories,
                luma, chroma_first, chroma_second, width, height,
            )
            flags_index = reader.read_unsigned_exp_golomb()
            if flags_index >= len(PFRAME_BLOCK8X8_COEFFICIENT_MASKS):
                raise ValueError("invalid P-frame macroblock coefficient mask")
            flags = PFRAME_BLOCK8X8_COEFFICIENT_MASKS[flags_index]
            for local_y in (0, 8):
                for local_x in (0, 8):
                    if flags & 1:
                        _add_pframe_coefficients(
                            reader, luma, width,
                            macroblock_x + local_x, macroblock_y + local_y,
                            lookup, residue, quant_scan8, quant_scan4,
                        )
                    flags >>= 1
            for plane in (chroma_first, chroma_second):
                if flags & 1:
                    _add_pframe_coefficients(
                        reader, plane, chroma_width,
                        macroblock_x // 2, macroblock_y // 2,
                        lookup, residue, quant_scan8, quant_scan4,
                    )
                flags >>= 1

    return DecodedPFrame(
        header=header,
        width=width,
        height=height,
        luma=bytes(luma),
        chroma_first=bytes(chroma_first),
        chroma_second=bytes(chroma_second),
        bits_consumed=reader.bit_position,
    )


def decode_frame(
    bitstream: bytes | bytearray | memoryview,
    width: int,
    height: int,
    coefficient_tables: tuple[bytes, bytes],
    histories: list[DecodedIFrame | DecodedPFrame],
    previous_quantizer: int,
    previous_format_variant: bool,
) -> DecodedIFrame | DecodedPFrame:
    """Dispatch one complete MODS frame while preserving external ring state."""
    probe = WordBitReader(bytes(bitstream) + bytes(2))
    if probe.peek_bits(1):
        return decode_iframe(bitstream, width, height, coefficient_tables)
    return decode_pframe(
        bitstream, width, height, coefficient_tables[0], histories,
        previous_quantizer, previous_format_variant,
    )


def convert_ycocg_to_rgb555(
    luma: Iterable[int],
    chroma: Iterable[int],
    width: int,
    height: int,
    luma_stride: int = 0x100,
    chroma_stride: int = 0x100,
) -> list[int]:
    """Convert the native DS Y/Co-Cg planes into visible-row RGB555 pixels."""
    if width <= 0 or height <= 0 or width % 16 or height % 2:
        raise ValueError("width must be a positive multiple of 16 and height must be even")
    if luma_stride < width or chroma_stride < 0x80 + width // 2:
        raise ValueError("plane stride is too small")

    luma_values = list(luma)
    chroma_values = list(chroma)
    if len(luma_values) < luma_stride * height:
        raise ValueError("luma plane is too short")
    if len(chroma_values) < chroma_stride * (height // 2):
        raise ValueError("chroma plane is too short")

    def channel5(value: int) -> int:
        return max(0, min(255, value)) >> 3

    output = []
    for y in range(height):
        luma_row = y * luma_stride
        chroma_row = (y // 2) * chroma_stride
        for x in range(width):
            sample = luma_values[luma_row + x] - (4 if (x + y) & 1 else 0)
            co = chroma_values[chroma_row + x // 2] - 128
            cg = chroma_values[chroma_row + 0x80 + x // 2] - 128
            red = channel5(sample + co - cg)
            green = channel5(sample + cg)
            blue = channel5(sample - co - cg)
            output.append(0x8000 | red | (green << 5) | (blue << 10))
    return output


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


def split_vlc_table(table_data: bytes) -> tuple[list[int], bytes]:
    if len(table_data) != 0x2100:
        raise ValueError("packed VLC table must be exactly 0x2100 bytes")
    return list(struct.unpack("<4096H", table_data[:0x2000])), table_data[0x2000:]


def evaluate_vlc_capture(capture: dict, table_data: bytes) -> dict:
    lookup, residue = split_vlc_table(table_data)
    reader = ReservoirBitReader(
        int(capture["reservoirBefore"], 0),
        int(capture["bitsRemainingBefore"]),
        capture["nextInputWords"],
    )
    coefficient_count = int(capture["coefficientCount"])
    symbols = []
    position = 0
    while position < coefficient_count:
        symbol = decode_run_level_symbol(reader, lookup, residue)
        symbols.append(symbol)
        position += symbol.run + 1
        if symbol.last:
            break
    coefficients = place_run_level_coefficients(
        symbols, capture["quantScan"], coefficient_count
    )
    observed = list(capture["coefficients"])
    mismatch_indices = [
        index
        for index, (expected, actual) in enumerate(zip(coefficients, observed))
        if expected != actual
    ]
    cursor_before = int(capture["cursorBefore"], 0)
    cursor_after = cursor_before + reader.words_consumed * 2
    expected_cursor_after = int(capture["cursorAfter"], 0)
    expected_reservoir_after = int(capture["reservoirAfter"], 0)
    state_matches = (
        cursor_after == expected_cursor_after
        and reader.bits_remaining == int(capture["bitsRemainingAfter"])
        and reader.reservoir == expected_reservoir_after
    )
    return {
        "coefficientCount": coefficient_count,
        "symbols": [
            {"run": symbol.run, "level": symbol.level, "last": symbol.last}
            for symbol in symbols
        ],
        "coefficients": coefficients,
        "matchesCoefficients": not mismatch_indices,
        "mismatchIndices": mismatch_indices,
        "cursorAfter": f"0x{cursor_after:08x}",
        "bitsRemainingAfter": reader.bits_remaining,
        "reservoirAfter": f"0x{reader.reservoir:08x}",
        "matchesRegisterState": state_matches,
    }


def evaluate_color_capture(capture: dict, base_dir: Path) -> dict:
    width = int(capture["width"])
    height = int(capture["height"])
    luma_stride = int(capture["lumaStride"])
    chroma_stride = int(capture["chromaStride"])
    destination_stride = int(capture["destinationStrideBytes"])
    files = capture["files"]
    luma = (base_dir / files["luma"]).read_bytes()
    chroma = (base_dir / files["chroma"]).read_bytes()
    observed_data = (base_dir / files["rgb555"]).read_bytes()
    if destination_stride < width * 2:
        raise ValueError("destination stride is too small")
    if len(observed_data) < destination_stride * height:
        raise ValueError("RGB555 capture is too short")

    expected = convert_ycocg_to_rgb555(
        luma, chroma, width, height, luma_stride, chroma_stride
    )
    observed = []
    for y in range(height):
        row = observed_data[y * destination_stride : y * destination_stride + width * 2]
        observed.extend(struct.unpack(f"<{width}H", row))
    mismatches = [
        index
        for index, (wanted, actual) in enumerate(zip(expected, observed))
        if wanted != actual
    ]
    expected_bytes = struct.pack(f"<{len(expected)}H", *expected)
    observed_bytes = struct.pack(f"<{len(observed)}H", *observed)
    return {
        "width": width,
        "height": height,
        "matchesObserved": not mismatches,
        "mismatchCount": len(mismatches),
        "mismatchIndices": mismatches,
        "expectedVisibleSha256": hashlib.sha256(expected_bytes).hexdigest(),
        "observedVisibleSha256": hashlib.sha256(observed_bytes).hexdigest(),
    }


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
    parser.add_argument(
        "--vlc-table",
        type=Path,
        help="local 0x2100-byte packed VLC table for a VLC capture",
    )
    args = parser.parse_args(argv)
    if args.capture:
        capture = json.loads(args.capture.read_text(encoding="utf-8"))
    else:
        capture = json.load(sys.stdin)
    if capture.get("kind") == "ycocg_to_rgb555":
        base_dir = args.capture.parent if args.capture else Path.cwd()
        result = evaluate_color_capture(capture, base_dir)
    elif "reservoirBefore" in capture:
        if args.vlc_table is None:
            parser.error("--vlc-table is required for a VLC capture")
        result = evaluate_vlc_capture(capture, args.vlc_table.read_bytes())
    else:
        result = evaluate_capture(capture)
    json.dump(result, sys.stdout, indent=2)
    sys.stdout.write("\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
