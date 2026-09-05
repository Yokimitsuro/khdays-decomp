import json
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "tools"
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import mobiclip_reference as reference
import mobiclip_capture_verify as capture_verify


def word_stream(bit_text):
    padding = (-len(bit_text)) % 16
    bit_text += "0" * padding
    data = bytearray()
    for offset in range(0, len(bit_text), 16):
        word = int(bit_text[offset : offset + 16], 2)
        data.extend((word & 0xFF, word >> 8))
    return bytes(data)


def ue_bits(value):
    payload = format(value + 1, "b")
    return "0" * (len(payload) - 1) + payload


class WordBitReaderTests(unittest.TestCase):
    def test_reads_little_endian_words_msb_first(self):
        reader = reference.WordBitReader(bytes((0x34, 0x12, 0xCD, 0xAB)))
        self.assertEqual(reader.read_bits(16), 0x1234)
        self.assertEqual(reader.read_bits(16), 0xABCD)
        self.assertEqual(reader.bit_position, 32)

    def test_unsigned_golomb_crosses_word_refill_boundary(self):
        values = (0, 1, 2, 3, 4, 15, 31, 7)
        reader = reference.WordBitReader(word_stream("".join(map(ue_bits, values))))
        self.assertEqual(
            [reader.read_unsigned_exp_golomb() for _ in values], list(values)
        )

    def test_signed_golomb_mapping_matches_arm_odd_even_path(self):
        values = (0, 1, -1, 2, -2, 9, -9)
        codes = [2 * value - 1 if value > 0 else -2 * value for value in values]
        reader = reference.WordBitReader(word_stream("".join(map(ue_bits, codes))))
        self.assertEqual([reader.read_signed_exp_golomb() for _ in values], list(values))

    def test_failed_refill_restores_position(self):
        reader = reference.WordBitReader(bytes((0, 0)))
        with self.assertRaises(EOFError):
            reader.read_unsigned_exp_golomb()
        self.assertEqual(reader.bit_position, 0)

    def test_peek_does_not_advance(self):
        reader = reference.WordBitReader(word_stream("101001"))
        self.assertEqual(reader.peek_bits(4), 0b1010)
        self.assertEqual(reader.bit_position, 0)
        self.assertEqual(reader.read_bits(4), 0b1010)


class PackedQuantScanTests(unittest.TestCase):
    def test_unpacks_index_and_positive_multiplier(self):
        self.assertEqual(reference.unpack_quant_scan(0x0001232A, -3), (0x2A, -0x123 * 3))

    def test_sign_extends_sixteen_bit_multiplier(self):
        self.assertEqual(reference.unpack_quant_scan(0x00FFFE07, 5), (7, -10))

    def test_builds_exact_scan_and_dequant_fields_for_every_valid_qp(self):
        for quantizer in range(12, 54):
            quant8, quant4 = reference.build_quant_scan_tables(quantizer)
            row = quantizer % 6
            shift = quantizer // 6
            for index, entry in enumerate(quant4):
                scan, multiplier = reference.unpack_quant_scan(entry, 1)
                self.assertEqual(scan, reference.ZIGZAG4X4[index])
                self.assertEqual(multiplier, reference.QUANT4X4[row][index] << shift)
            for index, entry in enumerate(quant8):
                scan, multiplier = reference.unpack_quant_scan(entry, 1)
                self.assertEqual(scan, reference.ZIGZAG8X8[index])
                self.assertEqual(multiplier, reference.QUANT8X8[row][index] << (shift - 2))

    def test_rejects_quantizers_that_overlap_or_overrun_payload_tables(self):
        for quantizer in (-1, 0, 11, 54, 63):
            with self.assertRaises(ValueError):
                reference.build_quant_scan_tables(quantizer)

    def test_prediction_border_reset_preserves_other_cache_entries(self):
        modes = list(range(40))
        reset = reference.reset_prediction_borders(modes)
        borders = {1, 2, 3, 4, 8, 16, 24, 32}
        for index in range(40):
            self.assertEqual(reset[index], 9 if index in borders else index)
        self.assertEqual(modes, list(range(40)))


class FrameHeaderTests(unittest.TestCase):
    def test_decodes_iframe_format_table_and_absolute_qp(self):
        bits = "1" + "1" + "1" + format(23, "06b")
        header = reference.decode_frame_header(
            reference.WordBitReader(word_stream(bits)), 31, False
        )
        self.assertEqual(
            header,
            reference.FrameHeader(
                intra=True,
                format_variant=True,
                coefficient_table_variant=1,
                quantizer=23,
            ),
        )

    def test_decodes_pframe_signed_qp_delta_and_forces_table_zero(self):
        delta = -2
        code = -2 * delta
        bits = "0" + ue_bits(code)
        header = reference.decode_frame_header(
            reference.WordBitReader(word_stream(bits)), 30, True
        )
        self.assertEqual(
            header,
            reference.FrameHeader(
                intra=False,
                format_variant=True,
                coefficient_table_variant=0,
                quantizer=28,
            ),
        )

    def test_rejects_qp_outside_ds_packed_table_range(self):
        bits = "1" + "0" + "0" + format(11, "06b")
        with self.assertRaises(ValueError):
            reference.decode_frame_header(
                reference.WordBitReader(word_stream(bits)), 30, False
            )


class MotionVectorTests(unittest.TestCase):
    def test_component_median_matches_three_neighbour_core(self):
        prediction = reference.median_motion_vector(
            reference.MotionVector(9, -5),
            reference.MotionVector(-4, 12),
            reference.MotionVector(3, 1),
        )
        self.assertEqual(prediction, reference.MotionVector(3, 1))

    def test_decodes_x_then_y_signed_golomb_deltas(self):
        delta_x = 3
        delta_y = -2
        bits = ue_bits(2 * delta_x - 1) + ue_bits(-2 * delta_y)
        motion = reference.decode_predicted_motion(
            reference.WordBitReader(word_stream(bits)),
            reference.MotionVector(10, -7),
        )
        self.assertEqual(motion, reference.MotionVector(13, -9))


class PredictedIntraModeTests(unittest.TestCase):
    def test_reuses_minimum_left_and_upper_mode(self):
        modes = bytearray([9] * 40)
        modes[1] = 2
        modes[4] = 5
        mode = reference.decode_predicted_intra_mode(
            reference.WordBitReader(word_stream("1")), modes, 4, 0, 4
        )
        self.assertEqual(mode, 2)
        self.assertEqual(modes[5], 2)

    def test_explicit_mode_skips_predicted_value_and_expands_8x8_cache(self):
        modes = bytearray([9] * 40)
        mode = reference.decode_predicted_intra_mode(
            reference.WordBitReader(word_stream("0" + "011")),
            modes,
            0,
            0,
            8,
        )
        self.assertEqual(mode, 4)
        self.assertEqual([modes[index] for index in (4, 5, 8, 9)], [4] * 4)

    def test_rejects_invalid_prediction_cache_shape(self):
        with self.assertRaises(ValueError):
            reference.decode_predicted_intra_mode(
                reference.WordBitReader(word_stream("1")), [9] * 39, 0, 0, 4
            )


class ModeVlcTests(unittest.TestCase):
    def test_motion_dimensions_map_to_all_sixteen_native_contexts(self):
        sizes = (16, 8, 4, 2)
        observed = tuple(
            reference.motion_context_codebook(width, height)
            for height in sizes
            for width in sizes
        )
        self.assertEqual(observed, reference.MOTION_CONTEXT_CODEBOOKS)
        self.assertEqual(len(set(observed)), 16)

    def test_invalid_motion_context_dimensions_are_rejected(self):
        with self.assertRaises(ValueError):
            reference.motion_context_codebook(16, 6)

    def test_all_sixteen_inline_codebooks_decode_every_replicated_prefix(self):
        self.assertEqual(len(reference.INLINE_MODE_CODEBOOKS), 16)
        for name, (prefixes, lengths) in reference.INLINE_MODE_CODEBOOKS.items():
            prefix_bits = (len(prefixes) - 1).bit_length()
            for encoded, expected in enumerate(prefixes):
                with self.subTest(codebook=name, prefix=encoded):
                    reader = reference.WordBitReader(
                        word_stream(format(encoded, f"0{prefix_bits}b"))
                    )
                    self.assertEqual(reference.decode_inline_mode(reader, name), expected)
                    self.assertEqual(reader.bit_position, lengths[expected])

    def test_all_inline_codebooks_avoid_reserved_dispatch_slots(self):
        for prefixes, lengths in reference.INLINE_MODE_CODEBOOKS.values():
            self.assertTrue(all(lengths[mode] for mode in prefixes))

    def test_unknown_inline_codebook_is_rejected_without_consuming_bits(self):
        reader = reference.WordBitReader(word_stream("0"))
        with self.assertRaises(ValueError):
            reference.decode_inline_mode(reader, "missing")
        self.assertEqual(reader.bit_position, 0)

    def test_all_replicated_prefixes_select_mode_and_consume_exact_length(self):
        cases = (
            (
                reference.PFRAME_MODE_PREFIX,
                reference.PFRAME_MODE_LENGTHS,
                reference.decode_pframe_macroblock_mode,
            ),
            (
                reference.MOTION16_MODE_PREFIX,
                reference.MOTION16_MODE_LENGTHS,
                reference.decode_motion16_mode,
            ),
            (
                reference.MOTION8X16_MODE_PREFIX,
                reference.MOTION8X16_MODE_LENGTHS,
                reference.decode_motion8x16_mode,
            ),
            (
                reference.INTRA16_MODE_PREFIX,
                reference.INTRA16_MODE_LENGTHS,
                reference.decode_intra16_mode,
            ),
        )
        for prefixes, lengths, decoder in cases:
            prefix_bits = (len(prefixes) - 1).bit_length()
            for encoded, expected in enumerate(prefixes):
                with self.subTest(decoder=decoder.__name__, prefix=encoded):
                    reader = reference.WordBitReader(
                        word_stream(format(encoded, f"0{prefix_bits}b"))
                    )
                    self.assertEqual(decoder(reader), expected)
                    self.assertEqual(reader.bit_position, lengths[expected])

    def test_mode_tables_never_select_reserved_zero_length_slot(self):
        for prefixes, lengths in (
            (reference.PFRAME_MODE_PREFIX, reference.PFRAME_MODE_LENGTHS),
            (reference.MOTION16_MODE_PREFIX, reference.MOTION16_MODE_LENGTHS),
            (reference.MOTION8X16_MODE_PREFIX, reference.MOTION8X16_MODE_LENGTHS),
            (reference.INTRA16_MODE_PREFIX, reference.INTRA16_MODE_LENGTHS),
        ):
            self.assertTrue(all(lengths[mode] for mode in prefixes))


class RunLevelPlacementTests(unittest.TestCase):
    def test_places_run_level_symbols_in_scan_order_and_dequantizes(self):
        _, quant4 = reference.build_quant_scan_tables(12)
        symbols = (
            reference.RunLevelSymbol(run=0, level=2, last=False),
            reference.RunLevelSymbol(run=2, level=-1, last=True),
        )
        coefficients = reference.place_run_level_coefficients(symbols, quant4, 16)

        first_index, first_value = reference.unpack_quant_scan(quant4[0], 2)
        second_index, second_value = reference.unpack_quant_scan(quant4[3], -1)
        expected = [0] * 16
        expected[first_index] = first_value
        expected[second_index] = second_value
        self.assertEqual(coefficients, expected)

    def test_accepts_last_symbol_at_final_scan_position(self):
        _, quant4 = reference.build_quant_scan_tables(17)
        symbol = reference.RunLevelSymbol(run=15, level=1, last=True)
        coefficients = reference.place_run_level_coefficients((symbol,), quant4, 16)
        index, value = reference.unpack_quant_scan(quant4[15], 1)
        self.assertEqual(coefficients[index], value)
        self.assertEqual(sum(value != 0 for value in coefficients), 1)

    def test_rejects_overrun_unterminated_and_invalid_scan_index(self):
        _, quant4 = reference.build_quant_scan_tables(12)
        with self.assertRaises(ValueError):
            reference.place_run_level_coefficients(
                (reference.RunLevelSymbol(run=16, level=1, last=True),), quant4, 16
            )
        with self.assertRaises(ValueError):
            reference.place_run_level_coefficients(
                (reference.RunLevelSymbol(run=0, level=1, last=False),), quant4, 16
            )
        invalid_scan = list(quant4)
        invalid_scan[0] = (invalid_scan[0] & ~0xFF) | 16
        with self.assertRaises(ValueError):
            reference.place_run_level_coefficients(
                (reference.RunLevelSymbol(run=0, level=1, last=True),), invalid_scan, 16
            )


class PackedVlcDecodeTests(unittest.TestCase):
    @staticmethod
    def _table_for(bit_text, packed):
        padded = bit_text + "0" * (12 - len(bit_text))
        lookup = [0] * 4096
        lookup[int(padded[:12], 2)] = packed
        return lookup

    def test_decodes_common_symbol_and_embedded_sign_bit(self):
        bits = "101" + "0" * 13
        packed = 0x8000 | (2 << 9) | (3 << 4) | 3
        lookup = self._table_for(bits[:12], packed)
        symbol = reference.decode_run_level_symbol(
            reference.WordBitReader(word_stream(bits)), lookup, bytes(256)
        )
        self.assertEqual(symbol, reference.RunLevelSymbol(2, -3, True))

    def test_decodes_level_escape_with_residue_before_sign(self):
        bits = "0000011" + "0" + "101" + "0" * 21
        packed = (4 << 9) | (2 << 4) | 3
        lookup = self._table_for(bits[8:20], packed)
        residue = bytearray(256)
        residue[4] = 7
        symbol = reference.decode_run_level_symbol(
            reference.WordBitReader(word_stream(bits)), lookup, residue
        )
        self.assertEqual(symbol, reference.RunLevelSymbol(4, -9, False))

    def test_decodes_run_escape_with_residue(self):
        bits = "0000011" + "10" + "100" + "0" * 20
        packed = 0x8000 | (3 << 9) | (5 << 4) | 3
        lookup = self._table_for(bits[9:21], packed)
        residue = bytearray(256)
        residue[128 + 64 + 5] = 11
        symbol = reference.decode_run_level_symbol(
            reference.WordBitReader(word_stream(bits)), lookup, residue
        )
        self.assertEqual(symbol, reference.RunLevelSymbol(14, 5, True))

    def test_decodes_full_escape_with_signed_twelve_bit_level(self):
        raw_level = (-37) & 0xFFF
        bits = "0000011" + "11" + "1" + format(23, "06b") + format(raw_level, "012b")
        symbol = reference.decode_run_level_symbol(
            reference.WordBitReader(word_stream(bits)), [0] * 4096, bytes(256)
        )
        self.assertEqual(symbol, reference.RunLevelSymbol(23, -37, True))

    def test_reservoir_reader_replays_arm_refill_state(self):
        reader = reference.ReservoirBitReader(0xA8000000, 2, (0xBEEF,))
        self.assertEqual(reader.read_bits(4), 0b1010)
        self.assertEqual(reader.words_consumed, 1)
        self.assertEqual(reader.bits_remaining, 14)
        self.assertEqual(reader.reservoir, 0x8002FBBC)

    def test_evaluates_vlc_capture_coefficients_and_register_state(self):
        packed = 0x8000 | (2 << 9) | (3 << 4) | 3
        table = bytearray(0x2100)
        table[0xA00 * 2 : 0xA00 * 2 + 2] = packed.to_bytes(2, "little")
        quant_scan = [(1 << 8) | index for index in range(16)]
        coefficients = [0] * 16
        coefficients[2] = -3
        capture = {
            "reservoirBefore": "0xa0000000",
            "bitsRemainingBefore": 15,
            "nextInputWords": [0] * 32,
            "coefficientCount": 16,
            "quantScan": quant_scan,
            "coefficients": coefficients,
            "cursorBefore": "0x00001000",
            "cursorAfter": "0x00001000",
            "bitsRemainingAfter": 12,
            "reservoirAfter": "0x00000000",
        }
        result = reference.evaluate_vlc_capture(capture, bytes(table))
        self.assertTrue(result["matchesCoefficients"])
        self.assertTrue(result["matchesRegisterState"])
        self.assertEqual(
            result["symbols"], [{"run": 2, "level": -3, "last": True}]
        )


class IntraPredictionTests(unittest.TestCase):
    EXPECTED = (
        [67, 74, 81, 88, 67, 74, 81, 88, 67, 74, 81, 88, 67, 74, 81, 88],
        [73, 73, 73, 73, 86, 86, 86, 86, 99, 99, 99, 99, 112, 112, 112, 112],
        [78, 83, 88, 93, 89, 92, 94, 97, 100, 100, 101, 102, 111, 109, 108, 106],
        [85] * 16,
        [80, 86, 93, 99, 93, 99, 106, 109, 106, 109, 112, 112, 112, 112, 112, 112],
        [67, 65, 67, 74, 80, 73, 67, 65, 93, 86, 80, 73, 106, 99, 93, 86],
        [64, 71, 78, 85, 65, 67, 74, 81, 73, 64, 71, 78, 86, 65, 67, 74],
        [65, 67, 74, 81, 73, 65, 67, 74, 86, 73, 65, 67, 99, 86, 73, 65],
        [71, 78, 85, 92, 74, 81, 88, 95, 78, 85, 92, 99, 81, 88, 95, 102],
    )

    def test_all_nine_modes_match_fixed_gradient_vectors(self):
        width = height = stride = 12
        original = bytearray(
            (x * 7 + y * 13) & 0xFF
            for y in range(height)
            for x in range(width)
        )
        for mode, expected in enumerate(self.EXPECTED):
            with self.subTest(mode=mode):
                frame = bytearray(original)
                observed = reference.predict_intra_block(
                    frame, width, height, stride, 4, 4, 4, mode, plane_delta=3
                )
                self.assertEqual(observed, expected)

    def test_dc_origin_uses_native_neutral_value(self):
        frame = bytearray(8 * 8)
        block = reference.predict_intra_block(frame, 8, 8, 8, 0, 0, 8, 3)
        self.assertEqual(block, [0x80] * 64)

    def test_rejects_reserved_mode_and_invalid_block(self):
        frame = bytearray(8 * 8)
        with self.assertRaises(ValueError):
            reference.predict_intra_block(frame, 8, 8, 8, 0, 0, 4, 9)
        with self.assertRaises(ValueError):
            reference.predict_intra_block(frame, 8, 8, 8, 6, 6, 4, 0)


class MotionCompensationTests(unittest.TestCase):
    def test_four_fractional_phases_match_packed_arm_rounding(self):
        width = height = stride = 6
        source = bytes(
            (3 * x + 11 * y + 1) & 0xFF
            for y in range(height)
            for x in range(width)
        )
        expected = {
            (0, 0): [15, 18, 26, 29],
            (1, 0): [16, 19, 27, 30],
            (0, 1): [20, 23, 31, 34],
            (1, 1): [21, 24, 32, 35],
        }
        for components, block in expected.items():
            with self.subTest(motion=components):
                destination = bytearray(width * height)
                observed = reference.compensate_motion_block(
                    source,
                    destination,
                    width,
                    height,
                    stride,
                    stride,
                    1,
                    1,
                    2,
                    2,
                    reference.MotionVector(*components),
                )
                self.assertEqual(observed, block)

    def test_negative_odd_motion_uses_arithmetic_floor(self):
        source = bytes(range(64))
        destination = bytearray(64)
        observed = reference.compensate_motion_block(
            source, destination, 8, 8, 8, 8, 2, 2, 2, 1,
            reference.MotionVector(-1, 0),
        )
        self.assertEqual(observed, [17, 18])

    def test_rejects_fractional_sample_past_frame_edge(self):
        source = bytes(range(64))
        with self.assertRaises(ValueError):
            reference.compensate_motion_block(
                source, bytearray(64), 8, 8, 8, 8, 6, 6, 2, 2,
                reference.MotionVector(1, 1),
            )


class YCoCgConversionTests(unittest.TestCase):
    def test_neutral_chroma_and_odd_column_bias_match_arm(self):
        luma = [128] * (0x100 * 2)
        chroma = [128] * 0x100
        pixels = reference.convert_ycocg_to_rgb555(luma, chroma, 16, 2)
        self.assertEqual(pixels[:16:2], [0xC210] * 8)
        self.assertEqual(pixels[1:16:2], [0xBDEF] * 8)
        self.assertEqual(pixels[16::2], [0xBDEF] * 8)
        self.assertEqual(pixels[17::2], [0xC210] * 8)

    def test_inverse_ycocg_channel_equations_and_saturation(self):
        luma = [128] * (0x100 * 2)
        chroma = [128] * 0x100
        chroma[0] = 255
        chroma[0x80] = 0
        luma[1] = 132
        pixels = reference.convert_ycocg_to_rgb555(luma, chroma, 16, 2)
        self.assertEqual(pixels[0], 0xC01F)
        self.assertEqual(pixels[1], 0xC01F)

    def test_rejects_invalid_native_layout(self):
        with self.assertRaises(ValueError):
            reference.convert_ycocg_to_rgb555([0] * 32, [0] * 16, 15, 2)
        with self.assertRaises(ValueError):
            reference.convert_ycocg_to_rgb555(
                [0] * (0x100 * 2), [0] * 0x100, 16, 2, chroma_stride=0x80
            )

    def test_replays_raw_color_capture_with_destination_padding(self):
        luma = bytes([128] * (0x100 * 2))
        chroma = bytes([128] * 0x100)
        pixels = reference.convert_ycocg_to_rgb555(luma, chroma, 16, 2)
        row_bytes = 40
        output = bytearray(row_bytes * 2)
        for y in range(2):
            output[y * row_bytes : y * row_bytes + 32] = struct.pack(
                "<16H", *pixels[y * 16 : (y + 1) * 16]
            )
        with tempfile.TemporaryDirectory() as directory:
            base = Path(directory)
            (base / "luma.bin").write_bytes(luma)
            (base / "chroma.bin").write_bytes(chroma)
            (base / "rgb.bin").write_bytes(output)
            capture = {
                "width": 16,
                "height": 2,
                "lumaStride": 0x100,
                "chromaStride": 0x100,
                "destinationStrideBytes": row_bytes,
                "files": {
                    "luma": "luma.bin",
                    "chroma": "chroma.bin",
                    "rgb555": "rgb.bin",
                },
            }
            result = reference.evaluate_color_capture(capture, base)
        self.assertTrue(result["matchesObserved"])
        self.assertEqual(result["mismatchCount"], 0)
        self.assertEqual(
            result["expectedVisibleSha256"], result["observedVisibleSha256"]
        )


class InverseTransformTests(unittest.TestCase):
    def test_dc_only_rounding_for_both_sizes(self):
        for size in (4, 8):
            coefficients = [0] * (size * size)
            coefficients[0] = 32
            self.assertEqual(reference.inverse_transform(coefficients, size), [1] * (size * size))

    def test_negative_dc_uses_arithmetic_shift(self):
        coefficients = [0] * 16
        coefficients[0] = -96
        self.assertEqual(reference.inverse_transform(coefficients, 4), [-1] * 16)

    def test_transform_preserves_expected_ac_symmetry(self):
        coefficients = [0] * 16
        coefficients[1] = 64
        residual = reference.inverse_transform(coefficients, 4)
        self.assertEqual(residual[0:4], [1, 1, 1, 1])
        self.assertEqual(residual[4:8], [1, 1, 1, 1])
        self.assertEqual(residual[8:12], [0, 0, 0, 0])
        self.assertEqual(residual[12:16], [-1, -1, -1, -1])

    def test_reconstruction_clips_to_byte_range(self):
        positive = [0] * 16
        positive[0] = 640
        negative = [0] * 16
        negative[0] = -672
        self.assertEqual(reference.reconstruct_block(positive, [250] * 16, 4), [255] * 16)
        self.assertEqual(reference.reconstruct_block(negative, [5] * 16, 4), [0] * 16)

    def test_rejects_invalid_shapes(self):
        with self.assertRaises(ValueError):
            reference.inverse_transform([0] * 16, 5)
        with self.assertRaises(ValueError):
            reference.inverse_transform([0] * 15, 4)


class CaptureReplayLayoutTests(unittest.TestCase):
    def test_native_chroma_split_join_round_trip(self):
        native = bytes(range(16))
        first, second = capture_verify.split_native_chroma(native, 8, 4)
        self.assertEqual(first, bytes([0, 1, 2, 3, 8, 9, 10, 11]))
        self.assertEqual(second, bytes([4, 5, 6, 7, 12, 13, 14, 15]))
        self.assertEqual(
            capture_verify.join_native_chroma(first, second, 8, 4), native
        )

    def test_native_chroma_rejects_wrong_sizes(self):
        with self.assertRaises(ValueError):
            capture_verify.split_native_chroma(bytes(15), 8, 4)
        with self.assertRaises(ValueError):
            capture_verify.join_native_chroma(bytes(7), bytes(8), 8, 4)

    def test_decoder_return_rounds_to_refill_words(self):
        self.assertEqual(capture_verify.decoder_return_bytes(0), 0)
        self.assertEqual(capture_verify.decoder_return_bytes(1), 2)
        self.assertEqual(capture_verify.decoder_return_bytes(16), 2)
        self.assertEqual(capture_verify.decoder_return_bytes(17), 4)
        self.assertEqual(capture_verify.decoder_return_bytes(3638), 456)


class ReferenceCliTests(unittest.TestCase):
    def test_json_capture_from_stdin(self):
        capture = {
            "size": 4,
            "coefficients": [32] + [0] * 15,
            "prediction": [10] * 16,
        }
        result = subprocess.run(
            [sys.executable, str(TOOLS / "mobiclip_reference.py")],
            input=json.dumps(capture),
            text=True,
            capture_output=True,
            check=False,
        )
        self.assertEqual(result.returncode, 0, result.stderr)
        decoded = json.loads(result.stdout)
        self.assertEqual(decoded["residual"], [1] * 16)
        self.assertEqual(decoded["reconstructed"], [11] * 16)

    def test_reports_byte_mismatches_from_emulator_capture(self):
        capture = {
            "size": 4,
            "coefficients": [32] + [0] * 15,
            "prediction": [10] * 16,
            "observed": [11] * 15 + [12],
        }
        decoded = reference.evaluate_capture(capture)
        self.assertFalse(decoded["matchesObserved"])
        self.assertEqual(decoded["mismatchIndices"], [15])


if __name__ == "__main__":
    unittest.main()
