import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_progress
import index_data
import verify_data


class IndexDataTests(unittest.TestCase):
    def test_module_and_address_are_read_from_the_names(self):
        self.assertEqual(index_data.module_of("_dsd_gap@ov006_10"), "ov006")
        self.assertEqual(index_data.module_of("_dsd_gap@main_281"), "main")
        self.assertEqual(index_data.address_of("data_ov006_0205630c"), 0x0205630C)
        self.assertEqual(index_data.address_of("data_0204c058"), 0x0204C058)
        self.assertIsNone(index_data.address_of("SDK_STATIC_BSS_START"))

    def test_two_spellings_of_one_address_are_the_same_target(self):
        index_data.SYM_ADDR.update({"alpha": 0x02000100, "beta": 0x02000100, "gamma": 0x02000200})
        self.assertEqual(
            index_data.reloc_targets([(0, "alpha")]),
            index_data.reloc_targets([(0, "beta")]),
        )
        self.assertNotEqual(
            index_data.reloc_targets([(0, "alpha")]),
            index_data.reloc_targets([(0, "gamma")]),
        )

    def test_an_unknown_symbol_falls_back_to_its_spelling(self):
        self.assertEqual(index_data.reloc_targets([(4, "never_seen")]), ((4, "never_seen"),))


class RepoPathTests(unittest.TestCase):
    def test_a_source_on_another_drive_does_not_raise(self):
        # Windows relpath refuses to cross mounts; a scratch file must still get a
        # usable receipt path instead of taking the verifier down.
        path = verify_data._repo_path(str(Path(verify_data.ROOT) / "tools" / "verify_data.py"))
        self.assertTrue(path.endswith("tools/verify_data.py"))
        self.assertNotIn("\\", verify_data._repo_path("Z:/elsewhere/probe.c"))


class VerifiedRangeTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)

    def test_without_an_index_nothing_counts(self):
        ranges, note = data_progress.load_verified_ranges(self.root)
        self.assertEqual(ranges, [])
        self.assertIn("no DATA index", note)

    def test_receipts_without_an_index_still_count_nothing(self):
        (self.root / "build").mkdir()
        receipts = self.root / "build" / "data_receipts"
        receipts.mkdir()
        (receipts / "data_x.json").write_text(json.dumps({
            "symbol": "data_x", "source": "src/x.c", "module": "ov006",
            "section": "rodata", "start": 0x02000000, "end": 0x02000010,
        }), encoding="utf-8")
        ranges, note = data_progress.load_verified_ranges(self.root)
        self.assertEqual(ranges, [])
        self.assertIn("no DATA index", note)

    def test_overlaid_units_do_not_borrow_each_others_bytes(self):
        # ov006 .rodata and ov009 .data really do share addresses, because overlays
        # are loaded over one another. Counting by address alone doubled the total.
        item = {"unit": "ov009", "section": "data", "start": 0x02056220, "end": 0x020563E0}
        proved = [("ov006", "rodata", 0x0205630C, 0x020563A4)]
        self.assertEqual(data_progress._overlap(item, proved), 0)
        self.assertEqual(
            data_progress._overlap(
                {"unit": "ov006", "section": "rodata", "start": 0x020561C0, "end": 0x020563A4},
                proved,
            ),
            152,
        )

    def test_a_range_is_clipped_to_the_section_it_lands_in(self):
        item = {"unit": "ov006", "section": "rodata", "start": 0x02056300, "end": 0x02056340}
        proved = [("ov006", "rodata", 0x0205630C, 0x020563A4)]
        self.assertEqual(data_progress._overlap(item, proved), 0x02056340 - 0x0205630C)


if __name__ == "__main__":
    unittest.main()
