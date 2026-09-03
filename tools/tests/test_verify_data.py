import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_progress
import gen_delinks
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

    def test_the_freshest_object_beats_a_crowd_of_stale_ones(self):
        # build/delinks keeps objects from earlier runs, so a majority vote let 37
        # stale copies outvote the one dsd had just written and reported a phantom
        # relocation as a genuine disagreement.
        stale = {"hex": "aa", "relocs": [[0, "phantom"]], "module": "main"}
        fresh = {"hex": "aa", "relocs": [], "module": "main"}
        entry, conflict = index_data.resolve({1: [stale, 37, 100.0], 2: [fresh, 1, 200.0]})
        self.assertEqual(entry["relocs"], [])
        self.assertIs(conflict, True)
        self.assertNotIn("ambiguous", entry)

    def test_equally_fresh_objects_that_disagree_stay_ambiguous(self):
        one = {"hex": "aa", "relocs": [[0, "alpha"]], "module": "main"}
        two = {"hex": "aa", "relocs": [[0, "gamma"]], "module": "main"}
        entry, conflict = index_data.resolve({1: [one, 3, 100.0], 2: [two, 3, 100.0]})
        self.assertIsInstance(conflict, list)
        self.assertIn("ambiguous", entry)

    def test_a_single_variant_is_no_conflict(self):
        only = {"hex": "aa", "relocs": [], "module": "main"}
        self.assertEqual(index_data.resolve({1: [only, 5, 100.0]}), (only, False))


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


class ReportedRangeTests(unittest.TestCase):
    REGION = {"unit": "ov006", "section": "rodata", "start": 0x020561C0, "end": 0x020563A4}

    def test_a_partly_proved_section_is_split_not_lost(self):
        # The report counts a region only when it is wholly matched, so leaving a
        # module's whole section as one region reported all-or-nothing: 6.01% against
        # a real 31.15%.
        proved = [("ov006", "rodata", 0x0205628C, 0x020563A4)]
        pieces = data_progress._split_by_ranges(dict(self.REGION), proved)
        self.assertEqual(len(pieces), 2)
        self.assertEqual([p["matched"] for p in pieces], [False, True])
        self.assertEqual(sum(p["size"] for p in pieces), 0x020563A4 - 0x020561C0)
        self.assertEqual(sum(p["verified_bytes"] for p in pieces), 0x020563A4 - 0x0205628C)

    def test_an_untouched_section_stays_one_unmatched_region(self):
        pieces = data_progress._split_by_ranges(dict(self.REGION), [])
        self.assertEqual(len(pieces), 1)
        self.assertFalse(pieces[0]["matched"])
        self.assertEqual(pieces[0]["verified_bytes"], 0)

    def test_another_units_range_does_not_split_this_one(self):
        proved = [("ov009", "data", 0x0205628C, 0x020563A4)]
        pieces = data_progress._split_by_ranges(dict(self.REGION), proved)
        self.assertEqual(len(pieces), 1)
        self.assertFalse(pieces[0]["matched"])

    def test_the_committed_delinks_are_what_the_report_reads(self):
        ranges = data_progress.load_delinked_data_ranges()
        self.assertTrue(ranges, "expected reconstructed DATA ranges in the delinks")
        for unit, section, start, end in ranges:
            self.assertIn(section, ("rodata", "ctor", "data"))
            self.assertLess(start, end)


class DataDelinkTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.receipts = self.root / "build" / "data_receipts"
        self.receipts.mkdir(parents=True)
        self.source = self.root / "src" / "ov006" / "tables.c"
        self.source.parent.mkdir(parents=True)
        self.source.write_text("const int x = 1;\n", encoding="utf-8")

    def digest(self):
        import hashlib

        return hashlib.sha256(self.source.read_bytes()).hexdigest()

    def receipt(self, symbol, start, end, **changes):
        body = {
            "symbol": symbol,
            "module": "ov006",
            "section": "rodata",
            "start": start,
            "end": end,
            "source": "src/ov006/tables.c",
            "source_sha256": self.digest(),
        }
        body.update(changes)
        (self.receipts / f"{symbol}.json").write_text(json.dumps(body), encoding="utf-8")

    def test_adjacent_symbols_become_one_range(self):
        self.receipt("a", 0x0205628C, 0x0205629C)
        self.receipt("b", 0x0205629C, 0x020562B0)
        blocks, modes, count = gen_delinks.gen_data_block("ov006", self.root)
        self.assertEqual(count, 1)
        self.assertIn(".rodata     start:0x0205628c end:0x020562b0", blocks[0])
        self.assertEqual(modes, {"src/ov006/tables.c": "arm"})

    def test_a_gap_keeps_the_ranges_apart(self):
        self.receipt("a", 0x0205628C, 0x0205629C)
        self.receipt("c", 0x020562B0, 0x020562D0)
        blocks, _modes, count = gen_delinks.gen_data_block("ov006", self.root)
        self.assertEqual(count, 2)
        self.assertIn("start:0x0205628c end:0x0205629c", blocks[0])
        self.assertIn("start:0x020562b0 end:0x020562d0", blocks[0])

    def test_an_edited_source_drops_out_of_the_build(self):
        self.receipt("a", 0x0205628C, 0x0205629C)
        self.source.write_text("const int x = 2;\n", encoding="utf-8")
        blocks, modes, count = gen_delinks.gen_data_block("ov006", self.root)
        self.assertEqual((blocks, modes, count), ([], {}, 0))

    def test_another_module_is_not_claimed(self):
        self.receipt("a", 0x0205628C, 0x0205629C)
        self.assertEqual(gen_delinks.gen_data_block("ov009", self.root), ([], {}, 0))


if __name__ == "__main__":
    unittest.main()
