import json
import sys
import tempfile
import unittest
from pathlib import Path


sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import configure
import verify_executable_data


GOOD_SOURCE = """\
    .syntax unified
    .arch armv5te
    .section .rodata,"a",%progbits
    .arm
    .align 2
    .global payload
    .type payload, %object
payload:
MobiClip_Code_00001000:
    mov r0, r0
    .global gMobiClip_table
gMobiClip_table:
    .word 0 /* reserved */
    .size payload, . - payload
"""


class ExecutableDataSourceTests(unittest.TestCase):
    SPEC = {
        "start": 0x1000,
        "end": 0x1008,
        "size": 8,
        "instruction_count": 1,
        "embedded_data_bytes": 4,
    }

    def test_mnemonic_code_and_named_data_cover_the_range(self):
        self.assertEqual(
            verify_executable_data.validate_source(GOOD_SOURCE, self.SPEC),
            {"instruction_count": 1, "embedded_data_bytes": 4},
        )

    def test_incbin_is_never_reconstructed_data(self):
        bad = GOOD_SOURCE.replace("    .word 0 /* reserved */", '    .incbin "payload.bin"')
        with self.assertRaisesRegex(ValueError, "forbidden opaque directive"):
            verify_executable_data.validate_source(bad, self.SPEC)

    def test_numeric_opcode_words_are_refused(self):
        bad = GOOD_SOURCE.replace(".word 0 /* reserved */", ".word 0xe1a00000")
        with self.assertRaisesRegex(ValueError, "non-symbolic/non-reserved"):
            verify_executable_data.validate_source(bad, self.SPEC)

    def test_raw_bytes_cannot_be_emitted_from_code_mode(self):
        bad = GOOD_SOURCE.replace("    mov r0, r0", "    mov r0, r0\n    .byte 0")
        with self.assertRaisesRegex(ValueError, "outside a named DATA region"):
            verify_executable_data.validate_source(bad, self.SPEC)

    def test_every_code_label_requires_one_mnemonic(self):
        bad = GOOD_SOURCE.replace("    mov r0, r0\n", "")
        with self.assertRaisesRegex(ValueError, "ARM mnemonic is required"):
            verify_executable_data.validate_source(bad, self.SPEC)


class ExecutableDataPolicyTests(unittest.TestCase):
    def test_registered_policy_becomes_a_complete_spec(self):
        with tempfile.TemporaryDirectory() as directory:
            policy = Path(directory) / "data_progress.json"
            policy.write_text(json.dumps({
                "classification_overrides": [{
                    "unit": "ov024",
                    "name": "payload",
                    "start": "0x1000",
                    "end": "0x1008",
                    "verification": {
                        "format": "arm_mnemonic_payload_v1",
                        "source_symbol": "payload",
                        "sha256": "00",
                        "instruction_count": 1,
                        "embedded_data_bytes": 4,
                    },
                }],
            }), encoding="utf-8")
            spec = verify_executable_data.load_spec("payload", policy)
        self.assertEqual(spec["module"], "ov024")
        self.assertEqual(spec["section"], "rodata")
        self.assertEqual(spec["size"], 8)


class ConfigureAssemblyTests(unittest.TestCase):
    def test_source_rules_are_selected_by_extension(self):
        self.assertEqual(configure.source_rule("src/x.c"), "mwcc")
        self.assertEqual(configure.source_rule("src/x.s"), "armasm")

    def test_unknown_source_type_is_refused(self):
        with self.assertRaisesRegex(ValueError, "unsupported reconstructed source type"):
            configure.source_rule("src/x.bin")


if __name__ == "__main__":
    unittest.main()
