import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import mobiclip_payload


class MobiClipPayloadTests(unittest.TestCase):
    def test_decode_forward_arm_branch(self):
        self.assertEqual(
            mobiclip_payload.decode_arm_branch(0xEA0005BA, 0x0208C8C4),
            0x0208DFB4,
        )

    def test_non_branch_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "not an ARM B/BL"):
            mobiclip_payload.decode_arm_branch(0xE1A00000, 0x0208C8C4)

    def test_extract_checks_and_writes_local_manifest(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "ov024.bin"
            output = root / "payload.bin"
            overlay_size = (
                mobiclip_payload.PAYLOAD_BASE
                - mobiclip_payload.OVERLAY_BASE
                + mobiclip_payload.PAYLOAD_SIZE
            )
            overlay = bytearray(overlay_size)
            offset = mobiclip_payload.PAYLOAD_BASE - mobiclip_payload.OVERLAY_BASE
            overlay[offset:offset + 4] = (0xEA0005BA).to_bytes(4, "little")
            source.write_bytes(overlay)

            manifest, manifest_path = mobiclip_payload.extract(source, output)

            self.assertEqual(output.stat().st_size, mobiclip_payload.PAYLOAD_SIZE)
            self.assertTrue(manifest_path.is_file())
            self.assertEqual(manifest["entry_address"], "0x0208dfb4")
            self.assertEqual(manifest["schema_version"], 2)
            self.assertEqual(len(manifest["decode_tables"]), 2)
            for table in manifest["decode_tables"]:
                self.assertEqual(Path(table["path"]).stat().st_size, 0x2100)
                self.assertEqual(
                    table["layout"],
                    "4096 little-endian uint16 VLC entries + 256 residue bytes",
                )


if __name__ == "__main__":
    unittest.main()
