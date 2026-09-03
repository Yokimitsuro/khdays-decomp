import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_progress


class DataProgressTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.config = self.root / "config" / "arm9" / "overlays" / "ov024"
        self.config.mkdir(parents=True)
        (self.config / "delinks.txt").write_text(
            "  .text start:0x02080000 end:0x02081000\n"
            "  .rodata start:0x02081000 end:0x02082000\n"
            "  .ctor start:0x02082000 end:0x02082004\n"
            "  .data start:0x02082004 end:0x02083000\n"
            "  .bss start:0x02083000 end:0x02084000\n"
            "\n"
            "source.c:\n",
            encoding="utf-8",
        )

    def write_policy(self, **changes):
        policy = {
            "schema_version": 1,
            "initialized_sections": ["rodata", "ctor", "data"],
            "classification_overrides": [{
                "unit": "ov024",
                "name": "payload",
                "start": "0x02081800",
                "end": "0x02081c00",
                "classification": "executable_payload",
                "progress_category": "mobiclip_payload",
            }],
            "matched_ranges": [],
        }
        policy.update(changes)
        path = self.root / "config" / "arm9" / "data_progress.json"
        path.write_text(json.dumps(policy), encoding="utf-8")
        return path

    def test_initialized_sections_and_override_are_split(self):
        inventory = data_progress.load_data_inventory(self.root, self.write_policy())
        self.assertEqual(sum(item["size"] for item in inventory), 0x2000)
        self.assertFalse(any(item["section"] == "bss" for item in inventory))
        payload = [item for item in inventory if item.get("name") == "payload"]
        self.assertEqual(len(payload), 1)
        self.assertEqual(payload[0]["size"], 0x400)
        self.assertEqual(payload[0]["progress_category"], "mobiclip_payload")
        self.assertFalse(payload[0]["matched"])

    def test_manual_matches_are_rejected_without_verifier(self):
        policy = self.write_policy(matched_ranges=[{"start": "0x02081000"}])
        with self.assertRaisesRegex(ValueError, "byte-and-relocation verifier"):
            data_progress.load_data_inventory(self.root, policy)


if __name__ == "__main__":
    unittest.main()
