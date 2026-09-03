import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import gen_report
import report_asm
import update_readme


def function(name, category, unit="ov002", source=None, size=4):
    return dict(name=name, category=category, unit=unit, source=source, size=size, mode="arm")


class ReportTests(unittest.TestCase):
    def setUp(self):
        self.c = function("real", "c_decompiled_matched")
        self.clz = function("approved", "asm_stub_matched", source="src/calls/approved.c")
        self.entry = dict(source=self.clz["source"], size=4, mode="arm")

    def test_matching_and_real_c_are_separate(self):
        funcs = [self.c, self.clz]
        matching = gen_report.build_report(funcs, {"approved": self.entry})
        pure_c = gen_report.build_report(funcs, {})
        self.assertEqual(matching["measures"]["matchedCodePercent"], 100)
        self.assertEqual(matching["measures"]["completeUnits"], 1)
        self.assertTrue(matching["units"][0]["metadata"]["complete"])
        self.assertEqual(pure_c["measures"]["matchedCodePercent"], 50)
        self.assertFalse(pure_c["units"][0]["metadata"]["complete"])

    def test_other_asm_and_sdk_names_are_not_matches(self):
        funcs = [function("stub", "asm_stub_matched", source="libs/nitro/os/asm_stubs/auto/stub.c"),
                 function("sdk", "sdk_identified"),
                 function("named", "named_only")]
        report = gen_report.build_report(funcs, {})
        self.assertEqual(report["measures"]["matchedFunctions"], 0)
        self.assertEqual(report["measures"]["completeCode"], "0")

    def test_changed_symbol_metadata_is_rejected(self):
        for field, value in [("size", 8), ("source", "other.c"), ("mode", "thumb")]:
            changed = dict(self.clz, **{field: value})
            with self.subTest(field=field), self.assertRaises(ValueError):
                gen_report.build_report([changed], {"approved": self.entry})

    def test_category_measures_are_populated(self):
        report = gen_report.build_report([self.c], {})
        self.assertEqual(report["categories"][0]["measures"]["matchedCode"], "4")

    def test_initialized_data_is_reported_separately(self):
        data = [dict(unit="ov002", section="rodata", start=0x1000, end=0x1020,
                     size=0x20, matched=False)]
        report = gen_report.build_report([self.c], {}, data)
        self.assertEqual(report["measures"]["totalData"], "32")
        self.assertEqual(report["measures"]["matchedData"], "0")
        self.assertEqual(report["measures"]["matchedDataPercent"], 0)
        self.assertFalse(report["units"][0]["metadata"]["complete"])

    def test_executable_payload_has_its_own_category(self):
        data = [dict(unit="ov024", section="rodata", start=0x208C8C4, end=0x2092E60,
                     size=0x659C, matched=False, progress_category="mobiclip_payload",
                     classification="executable_payload")]
        report = gen_report.build_report([], {}, data)
        category = report["categories"][0]
        self.assertEqual(category["id"], "mobiclip_payload")
        self.assertEqual(category["name"], "MobiClip executable payload")
        self.assertEqual(category["measures"]["totalData"], str(0x659C))

    def test_empty_report(self):
        report = gen_report.build_report([], {})
        self.assertEqual(report["measures"]["totalUnits"], 0)

    def test_generated_readme_policy_is_idempotent(self):
        original = "Heading\n| Real C-decompiled matched **bytes** | **123** | old wording |\nTail\n"
        changed = update_readme.update_policy_descriptions(original)
        self.assertIn("**123**", changed)
        self.assertIn("not as C", changed)
        self.assertEqual(changed, update_readme.update_policy_descriptions(changed))
        self.assertTrue(changed.startswith("Heading\n"))
        self.assertTrue(changed.endswith("Tail\n"))

    def test_checked_in_manifest_is_source_bound(self):
        entries = report_asm.load_verified_matches()
        self.assertEqual(len(entries), 27)
        self.assertEqual(sum(e["kind"] == "authorized_clz" for e in entries.values()), 2)
        self.assertEqual(sum(e["kind"] == "canonical_sdk_asm" for e in entries.values()), 25)

    def test_closed_modules_keep_honest_real_c_counts(self):
        entries = report_asm.load_verified_matches()
        functions = []
        for unit, count in [("ov002", 1477), ("ov003", 27), ("itcm", 129)]:
            functions.extend(function(f"{unit}_real_{i}", "c_decompiled_matched", unit) for i in range(count))
        for name, entry in entries.items():
            unit = name.split("_")[1] if entry["kind"] == "authorized_clz" else "itcm"
            f = function(name, "asm_stub_matched", unit, entry["source"], entry["size"])
            f["mode"] = entry["mode"]
            functions.append(f)
        matched = gen_report.build_report(functions, entries)
        pure_c = gen_report.build_report(functions, {})
        self.assertEqual(matched["measures"]["completeUnits"], 3)
        for unit in matched["units"]:
            self.assertEqual(unit["measures"]["matchedCodePercent"], 100)
        counts = {u["name"]: u["measures"]["matchedFunctions"] for u in pure_c["units"]}
        self.assertEqual(counts, {"ov002": 1477, "ov003": 27, "itcm": 129})


class AttestationTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.source = self.root / "libs/nitro/os/asm_stubs/auto/test.c"
        self.source.parent.mkdir(parents=True)
        self.source.write_text("asm void test(void) { bx lr }\n", encoding="utf-8")
        self.entry = dict(kind="canonical_sdk_asm", source=self.source.relative_to(self.root).as_posix(),
                          source_sha256=report_asm.source_digest(self.source), target_sha256="a" * 64,
                          size=4, mode="arm")
        self.manifest = self.root / report_asm.MANIFEST
        self.manifest.parent.mkdir(parents=True)
        self.write_manifest()

    def write_manifest(self):
        self.manifest.write_text(json.dumps(dict(schema_version=1, functions={"test": self.entry})))

    def test_valid_and_stale_source(self):
        self.assertIn("test", report_asm.load_verified_matches(self.root))
        self.source.write_text("asm void test(void) { nop }\n")
        with self.assertRaisesRegex(ValueError, "Stale"):
            report_asm.load_verified_matches(self.root)

    def test_crlf_does_not_invalidate_source(self):
        self.source.write_bytes(b"asm void test(void) { bx lr }\r\n")
        self.assertIn("test", report_asm.load_verified_matches(self.root))

    def test_game_stub_cannot_claim_sdk_ownership(self):
        self.entry["source"] = "src/asm_stubs/auto/test.c"
        with self.assertRaisesRegex(ValueError, "library-owned"):
            report_asm.validate_owner("test", self.entry, self.root)

    def test_nonmatching_and_path_traversal_are_rejected(self):
        for source in ["../test.c", "src/nonmatching/test.c"]:
            with self.subTest(source=source), self.assertRaises(ValueError):
                report_asm.validate_owner("test", dict(self.entry, source=source), self.root)

    def test_missing_byte_evidence_is_rejected(self):
        self.entry.pop("target_sha256")
        self.write_manifest()
        with self.assertRaisesRegex(ValueError, "evidence"):
            report_asm.load_verified_matches(self.root)

    def test_clz_requires_authorization_and_exact_scope(self):
        approval_path = self.root / "config/arm9/asm_exceptions.json"
        approval_path.write_text(json.dumps({"exceptions": {}}))
        entry = dict(self.entry, kind="authorized_clz")
        with self.assertRaisesRegex(ValueError, "authorization"):
            report_asm.validate_owner("test", entry, self.root)
        approval = dict(kind="single_inline_clz", approved_by="user",
                        classification="authorized_asm_exception", counts_as_real_c=False)
        approval_path.write_text(json.dumps({"exceptions": {"test": approval}}))
        self.source.write_text("int test(int x) { asm { clz x, x } return x; }\n")
        report_asm.validate_owner("test", entry, self.root)
        for extra in ["asm { nop }", "asm { clz x, x }", "__asm nop", "dcd 0"]:
            self.source.write_text("asm { clz x, x } " + extra)
            with self.subTest(extra=extra), self.assertRaisesRegex(ValueError, "scope"):
                report_asm.validate_owner("test", entry, self.root)


if __name__ == "__main__":
    unittest.main()
