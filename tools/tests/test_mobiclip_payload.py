import sys
import struct
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import mobiclip_payload
import mobiclip_inventory
import mobiclip_control_metadata_probe
import mobiclip_semantic_data_probe
import mobiclip_mods
import mobiclip_frame_verify


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
            self.assertEqual(manifest["schema_version"], 3)
            self.assertEqual(len(manifest["decode_tables"]), 2)
            for table in manifest["decode_tables"]:
                self.assertEqual(Path(table["path"]).stat().st_size, 0x2100)
                self.assertEqual(
                    table["layout"],
                    "4096 little-endian uint16 VLC entries + 256 residue bytes",
                )
                self.assertEqual(
                    table["packed_entry"]["bits_4_8"], "level magnitude"
                )
                self.assertEqual(
                    table["escape_prefix"],
                    "top seven reservoir bits equal 0b0000011",
                )
                self.assertEqual(len(table["lookup_sha256"]), 64)
            self.assertEqual(len(table["residue_sha256"]), 64)


class MobiClipModsTests(unittest.TestCase):
    def test_parses_n3_header_and_packet_boundaries(self):
        header = bytearray(0x30)
        values = (
            b"MODS", b"N3", 0x0A, 2, 256, 160, 15 * 0x01000000,
            0, 0, 0, 12, 0, 0x48, 1,
        )
        struct.pack_into("<4s2sHIIIIHHIIIII", header, 0, *values)
        data = header + b"HE\0\0"
        data += struct.pack("<I", 8 << 14) + b"12345678"
        data += struct.pack("<I", 4 << 14) + b"abcd"
        data += bytes(8)
        parsed = mobiclip_mods.parse_header(data)
        self.assertEqual(parsed.packet_data_offset, 0x34)
        self.assertEqual(parsed.frames_per_second, 15.0)
        packets = list(mobiclip_mods.iter_packets(data, parsed))
        self.assertEqual([packet.payload_size for packet in packets], [8, 4])
        self.assertEqual([packet.offset for packet in packets], [0x34, 0x40])

    def test_rejects_non_mobiclip_video_codec(self):
        header = struct.pack(
            "<4s2sHIIIIHHIIIII", b"MODS", b"N2", 9,
            0, 256, 160, 0, 0, 0, 0, 0, 0, 0, 0,
        )
        with self.assertRaises(ValueError):
            mobiclip_mods.parse_header(header)

    def test_reads_bounded_keyframe_table(self):
        header = mobiclip_mods.ModsHeader(
            "N2", 10, 0, 16, 16, 0, 0, 0, 0, 0, 0, 8, 2, 0x30
        )
        data = b"\0" * 8 + struct.pack("<IIII", 3, 0x40, 9, 0x80)
        self.assertEqual(
            mobiclip_frame_verify.read_keyframes(data, header),
            [(3, 0x40), (9, 0x80)],
        )


class MobiClipInventoryTests(unittest.TestCase):
    def test_reserved_zero_dispatch_entries_are_not_code_targets(self):
        records, targets = mobiclip_inventory.read_tables(
            bytes(mobiclip_inventory.SIZE)
        )
        self.assertFalse(targets)
        pframe = next(x for x in records if x["name"] == "pframe_macroblock")
        self.assertIsNone(pframe["entries"][0]["target"])

    def test_signed_relative_tables_resolve_backwards(self):
        payload = bytearray(mobiclip_inventory.SIZE)
        for address, count, _, _ in mobiclip_inventory.SIGNED_TABLES:
            for index in range(count):
                offset = -4 * (index + 1)
                start = address - mobiclip_inventory.BASE + index * 4
                payload[start:start + 4] = offset.to_bytes(4, "little", signed=True)
        records, targets = mobiclip_inventory.read_signed_tables(payload)
        self.assertEqual(len(records), 2)
        self.assertIn(0x0208F2F4, targets)
        self.assertIn(0x020902A8, targets)

    def test_range_builder_keeps_real_gaps(self):
        base = mobiclip_inventory.BASE
        result = mobiclip_inventory.make_ranges(
            {base, base + 4, base + 12}, "arm_code"
        )
        self.assertEqual(
            [(entry["start"], entry["end"]) for entry in result],
            [
                (f"0x{base:08x}", f"0x{base + 8:08x}"),
                (f"0x{base + 12:08x}", f"0x{base + 16:08x}"),
            ],
        )

    def test_proven_data_regions_cover_exact_static_total(self):
        self.assertEqual(
            sum(end - start for start, end, _ in mobiclip_inventory.DATA_REGIONS),
            0x970,
        )
        self.assertEqual(mobiclip_inventory.SIZE - 0x970, 0x5C2C)


class MobiClipSemanticDataProbeTests(unittest.TestCase):
    def test_semantic_regions_have_exact_compiled_total(self):
        regions = mobiclip_semantic_data_probe.semantic_regions()
        self.assertEqual(sum(len(data) for _, _, data in regions), 848)
        self.assertEqual(regions[0][0], 0x0208E188)
        self.assertEqual(regions[-1][0], 0x02092D88)

    def test_generated_source_uses_rwx_semantic_section(self):
        source = mobiclip_semantic_data_probe.render_source(
            mobiclip_semantic_data_probe.semantic_regions()
        )
        self.assertIn('".mobiclip_semantic" abs32 RWX', source)
        self.assertIn("gMobiClipQuant8BaseMatrices[384]", source)


class MobiClipControlMetadataProbeTests(unittest.TestCase):
    def test_control_regions_cover_exact_remaining_data_total(self):
        mobiclip_control_metadata_probe.validate_layout()
        self.assertEqual(
            sum(
                region.size
                for region in mobiclip_control_metadata_probe.REGIONS
            ),
            1568,
        )
        self.assertEqual(len(mobiclip_control_metadata_probe.REGIONS), 25)

    def test_generated_tables_use_symbolic_relative_offsets(self):
        payload = bytearray(mobiclip_control_metadata_probe.SIZE)
        table = mobiclip_control_metadata_probe.REGIONS[1].parts[0]
        payload[table.address - mobiclip_control_metadata_probe.BASE:
                table.address - mobiclip_control_metadata_probe.BASE + 4] = (
            0x80
        ).to_bytes(4, "little")
        source, targets = mobiclip_control_metadata_probe.render_assembly(payload)
        self.assertIn(
            ".word MobiClip_Code_0208C950 - .",
            source,
        )
        self.assertIn(".word 0 /* reserved */", source)
        self.assertIn(0x0208C950, targets)

    def test_cross_base_tables_apply_entry_correction(self):
        payload = bytearray(mobiclip_control_metadata_probe.SIZE)
        table = mobiclip_control_metadata_probe.REGIONS[6].parts[0]
        payload[table.address - mobiclip_control_metadata_probe.BASE:
                table.address - mobiclip_control_metadata_probe.BASE + 8] = (
            (0x80).to_bytes(4, "little")
            + (0x84).to_bytes(4, "little")
        )
        source, _ = mobiclip_control_metadata_probe.render_assembly(payload)
        self.assertIn(".word MobiClip_Code_0208CD68 - . + 0x114", source)
        self.assertIn(".word MobiClip_Code_0208CD6C - . + 0x118", source)


if __name__ == "__main__":
    unittest.main()
