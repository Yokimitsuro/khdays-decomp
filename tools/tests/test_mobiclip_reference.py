import json
import subprocess
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "tools"
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import mobiclip_reference as reference


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
