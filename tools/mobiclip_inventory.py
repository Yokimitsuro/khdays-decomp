#!/usr/bin/env python3
"""Reproducible ARM-code/data inventory for the ignored MobiClip payload."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import deque
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_LITTLE_ENDIAN, Cs
from capstone.arm import (
    ARM_CC_AL,
    ARM_CC_INVALID,
    ARM_OP_IMM,
    ARM_OP_REG,
    ARM_REG_LR,
    ARM_REG_PC,
)
from mobiclip_reference import (
    BLOCK4X4_COEFFICIENT_MASKS,
    BLOCK8X8_COEFFICIENT_MASKS,
    PACKED_AVERAGE_LANE_MASK,
    PFRAME_BLOCK4X4_COEFFICIENT_MASKS,
    PFRAME_BLOCK8X8_COEFFICIENT_MASKS,
    QUANT4X4,
    QUANT8X8,
    ZIGZAG4X4,
    ZIGZAG8X8,
)

ROOT = Path(__file__).resolve().parents[1]
BASE, SIZE = 0x0208C8C4, 0x659C
SHA256 = "5508ae5f765eb86e81b2ad8d76dccf6d4a30e3381d3e8b248fb8d4a6204b83f5"

# Entries validated independently in Ghidra. Some routines share tails.
ENTRIES = (
    0x0208C950, 0x0208CA98, 0x0208CAC0, 0x0208CAD8, 0x0208CAF0,
    0x0208CB08, 0x0208CB20, 0x0208CB38, 0x0208CB54, 0x0208CB70,
    0x0208CBE4, 0x0208CDC8, 0x0208D000, 0x0208D34C, 0x0208D6A0,
    0x0208DFB4, 0x0208E1C8, 0x0208E28C, 0x0208E364, 0x0208E5A0,
    0x0208E5F8, 0x0208E6F0, 0x0208E8A8, 0x0208E8F8, 0x0208E928,
    0x0208E93C, 0x0208E978, 0x0208E97C, 0x0208EE8C, 0x02090058,
    0x02090674, 0x02090860, 0x02091218, 0x020913BC, 0x02091534,
    0x020916AC, 0x02091888, 0x020919FC, 0x02091BC8, 0x02091D14,
)

# Computed continuations that are not standalone Ghidra functions.
COMPUTED_SEEDS = (
    0x0208CAB8,
    0x0208E150,
    0x02090AC8,
    0x02090C74,
    0x02090D94,
    0x02090F14,
)

# table address, entry count, relative base, name
TABLES = (
    (0x0208C8D0, 16, 0x0208C8D0, "luma_interpolation"),
    (0x0208C910, 16, 0x0208C910, "chroma_interpolation"),
    (0x0208CA64, 10, 0x0208CA64, "pframe_macroblock"),
    (0x0208CBA4, 16, 0x0208CBA4, "motion16_dispatch"),
    (0x0208CCE8, 10, 0x0208CCE8, "motion16_modes"),
    (0x0208CDFC, 8, 0x0208CCE8, "motion8x16_dispatch"),
    (0x0208CF20, 10, 0x0208CF20, "motion8x16_modes"),
    (0x0208D034, 4, 0x0208CF20, "intra16_dispatch"),
    (0x0208D158, 10, 0x0208D158, "intra16_modes_a"),
    (0x0208D26C, 10, 0x0208D26C, "intra16_modes_b"),
    (0x0208D390, 10, 0x0208D390, "motion16x8_modes_a"),
    (0x0208D4B4, 10, 0x0208D4B4, "motion16x8_modes_b"),
    (0x0208D5C0, 10, 0x0208D5C0, "motion16x8_modes_c"),
    (0x0208D6E4, 10, 0x0208D6E4, "predicted_intra_modes_a"),
    (0x0208D808, 10, 0x0208D808, "predicted_intra_modes_b"),
    (0x0208D914, 10, 0x0208D914, "predicted_intra_modes_c"),
    (0x0208DA54, 10, 0x0208DA54, "predicted_intra_modes_d"),
    (0x0208DB84, 10, 0x0208DB84, "predicted_intra_modes_e"),
    (0x0208DCAC, 10, 0x0208DCAC, "predicted_intra_modes_f"),
    (0x0208DDBC, 10, 0x0208DDBC, "predicted_intra_modes_g"),
    (0x0208DEC4, 10, 0x0208DEC4, "predicted_intra_modes_h"),
    (0x0208E4DC, 20, 0x0208E4DC, "intra_prediction"),
)

# These four-way tables contain signed offsets back to prediction helpers.
SIGNED_TABLES = (
    (0x0208F2F8, 4, 0x0208F2F8, "intra8_neighbor_dispatch"),
    (0x020902AC, 4, 0x020902AC, "intra4_neighbor_dispatch"),
)

# Proven non-instruction ranges. End addresses are exclusive.
DATA_REGIONS = (
    (0x0208C8C8, 0x0208C8D0, "payload_header"),
    (0x0208C8D0, 0x0208C910, "luma_interpolation_dispatch"),
    (0x0208C910, 0x0208C950, "chroma_interpolation_dispatch"),
    (0x0208CA44, 0x0208CA98, "pframe_prefix_offsets_and_lengths"),
    (0x0208CBA4, 0x0208CBE4, "luma_kernel_dispatch"),
    (0x0208CCD8, 0x0208CD1C, "motion16_selector_and_offsets"),
    (0x0208CDFC, 0x0208CE1C, "chroma_kernel_dispatch"),
    (0x0208CF10, 0x0208CF54, "motion8x16_selector_and_offsets"),
    (0x0208D034, 0x0208D044, "chroma_narrow_kernel_dispatch"),
    (0x0208D138, 0x0208D194, "intra16_selector_and_offsets"),
    (0x0208D25C, 0x0208D2A0, "motion8x8_selector_and_offsets"),
    (0x0208D380, 0x0208D3C4, "motion16x4_selector_and_offsets"),
    (0x0208D4A4, 0x0208D4E8, "motion16x2_selector_and_offsets"),
    (0x0208D5B0, 0x0208D5F4, "motion8x8_alt_selector_and_offsets"),
    (0x0208D6D4, 0x0208D718, "predicted_mode_a_selector_and_offsets"),
    (0x0208D7F8, 0x0208D83C, "predicted_mode_b_selector_and_offsets"),
    (0x0208D904, 0x0208D954, "predicted_mode_c_selector_and_offsets"),
    (0x0208DA34, 0x0208DA94, "predicted_mode_d_selector_and_offsets"),
    (0x0208DB74, 0x0208DBC4, "predicted_mode_e_selector_and_offsets"),
    (0x0208DC8C, 0x0208DCE4, "predicted_mode_f_selector_and_offsets"),
    (0x0208DDAC, 0x0208DDF4, "predicted_mode_g_selector_and_offsets"),
    (0x0208DEBC, 0x0208DF04, "predicted_mode_h_selector_and_offsets"),
    (0x0208E188, 0x0208E1C8, "iframe_residual_permutation"),
    (0x0208E324, 0x0208E364, "pframe_residual_mask"),
    (0x0208E4DC, 0x0208E52C, "intra_prediction_dispatch"),
    (0x0208E6B8, 0x0208E6CC, "intra_coefficient_mask"),
    (0x0208E788, 0x0208E798, "pframe_coefficient_mask"),
    (0x0208F2F8, 0x0208F308, "intra8_neighbor_dispatch"),
    (0x020902AC, 0x020902BC, "intra4_neighbor_dispatch"),
    (0x02090F7C, 0x020910FC, "quant8_base_matrices"),
    (0x020910FC, 0x0209113C, "scan8"),
    (0x0209113C, 0x0209119C, "quant4_base_matrices"),
    (0x0209119C, 0x020911AC, "scan4"),
    (0x020911AC, 0x020911E2, "qp_shift"),
    (0x020911E2, 0x02091218, "qp_matrix_selector"),
    (0x02091E4C, 0x02091E50, "packed_average_lane_mask"),
    (0x020925F8, 0x020925FC, "packed_average_lane_mask_1"),
    (0x02092AF4, 0x02092AF8, "packed_average_lane_mask_2"),
    (0x02092D88, 0x02092D8C, "packed_average_lane_mask_3"),
)


def inside(address: int) -> bool:
    return BASE <= address < BASE + SIZE and address % 4 == 0


def read_tables(payload: bytes) -> tuple[list[dict], set[int]]:
    records, targets = [], set()
    for address, count, relative_base, name in TABLES:
        entries = []
        for index in range(count):
            offset = struct.unpack_from("<I", payload, address - BASE + 4 * index)[0]
            if offset == 0:
                entries.append({"index": index, "offset": 0, "target": None})
                continue
            target = relative_base + offset
            if not inside(target):
                raise ValueError(f"{name}[{index}] target outside payload: {target:#x}")
            targets.add(target)
            entries.append({"index": index, "offset": offset, "target": f"0x{target:08x}"})
        records.append({
            "name": name, "address": f"0x{address:08x}", "size": count * 4,
            "relative_base": f"0x{relative_base:08x}", "entries": entries,
        })
    return records, targets


def read_signed_tables(payload: bytes) -> tuple[list[dict], set[int]]:
    records, targets = [], set()
    for address, count, relative_base, name in SIGNED_TABLES:
        entries = []
        for index in range(count):
            offset = struct.unpack_from("<i", payload, address - BASE + 4 * index)[0]
            target = relative_base + offset
            if not inside(target):
                raise ValueError(f"{name}[{index}] target outside payload: {target:#x}")
            targets.add(target)
            entries.append({"index": index, "offset": offset, "target": f"0x{target:08x}"})
        records.append({
            "name": name, "address": f"0x{address:08x}", "size": count * 4,
            "relative_base": f"0x{relative_base:08x}", "entries": entries,
        })
    return records, targets


def verify_semantic_data(payload: bytes) -> list[dict]:
    flatten = lambda rows: bytes(value for row in rows for value in row)
    regions = (
        (0x0208E188, "iframe_residual_permutation", bytes(BLOCK8X8_COEFFICIENT_MASKS)),
        (0x0208E324, "pframe_residual_mask", bytes(PFRAME_BLOCK8X8_COEFFICIENT_MASKS)),
        (
            0x0208E6B8,
            "intra_coefficient_mask_padded",
            bytes((0, *BLOCK4X4_COEFFICIENT_MASKS, 0, 0, 0)),
        ),
        (
            0x0208E788,
            "pframe_coefficient_mask",
            bytes(PFRAME_BLOCK4X4_COEFFICIENT_MASKS),
        ),
        (0x02090F7C, "quant8_base_matrices", flatten(QUANT8X8)),
        (0x020910FC, "scan8", bytes(ZIGZAG8X8)),
        (0x0209113C, "quant4_base_matrices", flatten(QUANT4X4)),
        (0x0209119C, "scan4", bytes(ZIGZAG4X4)),
        (0x020911AC, "qp_shift", bytes(qp // 6 for qp in range(54))),
        (0x020911E2, "qp_matrix_selector", bytes(qp % 6 for qp in range(54))),
        (
            0x02091E4C,
            "packed_average_lane_mask",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x020925F8,
            "packed_average_lane_mask_1",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x02092AF4,
            "packed_average_lane_mask_2",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
        (
            0x02092D88,
            "packed_average_lane_mask_3",
            PACKED_AVERAGE_LANE_MASK.to_bytes(4, "little"),
        ),
    )
    records = []
    for address, name, expected in regions:
        observed = payload[address - BASE:address - BASE + len(expected)]
        if observed != expected:
            raise ValueError(f"semantic data mismatch in {name} at {address:#010x}")
        records.append({
            "name": name,
            "address": f"0x{address:08x}",
            "size": len(expected),
            "sha256": hashlib.sha256(expected).hexdigest(),
            "matches_payload": True,
        })
    return records


def infer_relative_tables(payload: bytes) -> tuple[list[dict], set[int]]:
    """Find additional relative dispatch tables whose targets begin in ARM mode."""
    records, targets = [], set()
    address = BASE
    while address < BASE + SIZE:
        entries = []
        cursor = address
        while cursor < BASE + SIZE:
            offset = struct.unpack_from("<I", payload, cursor - BASE)[0]
            target = address + offset
            if offset % 4 or not inside(target):
                break
            target_word = struct.unpack_from("<I", payload, target - BASE)[0]
            if target_word >> 28 != 0xE:
                break
            entries.append({"offset": offset, "target": f"0x{target:08x}"})
            cursor += 4
        if len(entries) >= 3:
            records.append({
                "name": f"inferred_relative_{address:08x}",
                "address": f"0x{address:08x}",
                "size": len(entries) * 4,
                "relative_base": f"0x{address:08x}",
                "entries": [
                    {"index": index, **entry} for index, entry in enumerate(entries)
                ],
            })
            targets.update(int(entry["target"], 16) for entry in entries)
            address = cursor
        else:
            address += 4
    return records, targets


def discover(payload: bytes, seeds: set[int]) -> tuple[set[int], set[int]]:
    decoder = Cs(CS_ARCH_ARM, CS_MODE_ARM | CS_MODE_LITTLE_ENDIAN)
    decoder.detail = True
    pending, queued, code, targets = deque(sorted(seeds)), set(seeds), set(), set()
    while pending:
        address = pending.popleft()
        while inside(address) and address not in code:
            raw = payload[address - BASE:address - BASE + 4]
            decoded = list(decoder.disasm(raw, address, count=1))
            if len(decoded) != 1 or decoded[0].size != 4:
                break
            insn = decoded[0]
            code.add(address)
            mnemonic = insn.mnemonic
            # Private dispatchers synthesize LR immediately before an
            # indirect `add pc, ...`.  That address is a real continuation,
            # but no direct branch points at it, so seed it explicitly.
            continuation = None
            if (
                mnemonic in {"add", "sub"}
                and len(insn.operands) >= 3
                and insn.operands[0].type == ARM_OP_REG
                and insn.operands[0].reg == ARM_REG_LR
                and insn.operands[1].type == ARM_OP_REG
                and insn.operands[1].reg == ARM_REG_PC
                and insn.operands[2].type == ARM_OP_IMM
            ):
                delta = insn.operands[2].imm
                continuation = address + 8 + (delta if mnemonic == "add" else -delta)
            elif (
                mnemonic == "mov"
                and len(insn.operands) >= 2
                and insn.operands[0].type == ARM_OP_REG
                and insn.operands[0].reg == ARM_REG_LR
                and insn.operands[1].type == ARM_OP_REG
                and insn.operands[1].reg == ARM_REG_PC
            ):
                continuation = address + 8
            if continuation is not None and inside(continuation):
                targets.add(continuation)
                if continuation not in queued and continuation not in code:
                    queued.add(continuation)
                    pending.append(continuation)
            if mnemonic.startswith("b") and insn.operands:
                operand = insn.operands[-1]
                target = operand.imm & 0xFFFFFFFF if operand.type == ARM_OP_IMM else None
                if target is not None and inside(target):
                    targets.add(target)
                    if target not in queued and target not in code:
                        queued.add(target)
                        pending.append(target)
            call = mnemonic in {"bl", "blx"}
            branch = mnemonic == "b" or (
                mnemonic.startswith("b") and not call
                and mnemonic not in {"bic", "bfi", "bfc"}
            )
            conditional = insn.cc not in {ARM_CC_AL, ARM_CC_INVALID}
            writes_pc = ARM_REG_PC in insn.regs_write
            explicit_pc_destination = (
                bool(insn.operands)
                and insn.operands[0].type == ARM_OP_REG
                and insn.operands[0].reg == ARM_REG_PC
            )
            stack_return = mnemonic.startswith("pop") and "pc" in insn.op_str
            stack_return |= mnemonic.startswith("ldm") and "pc" in insn.op_str
            if (branch and not conditional) or mnemonic in {"bx", "bxj"}:
                break
            if stack_return:
                break
            # Direct conditional branches write PC but also have a fallthrough.
            # Only terminate here for computed PC writes such as ldr/add/mov pc.
            if (
                (writes_pc or explicit_pc_destination)
                and not call
                and not branch
                and not conditional
            ):
                break
            address += 4
    return code, targets


def make_ranges(addresses: set[int], classification: str) -> list[dict]:
    if not addresses:
        return []
    result = []
    start = previous = min(addresses)
    for address in sorted(addresses)[1:]:
        if address != previous + 4:
            result.append({
                "classification": classification, "start": f"0x{start:08x}",
                "end": f"0x{previous + 4:08x}", "size": previous + 4 - start,
            })
            start = address
        previous = address
    result.append({
        "classification": classification, "start": f"0x{start:08x}",
        "end": f"0x{previous + 4:08x}", "size": previous + 4 - start,
    })
    return result


def build_inventory(payload: bytes) -> dict:
    digest = hashlib.sha256(payload).hexdigest()
    if len(payload) != SIZE or digest != SHA256:
        raise ValueError(f"unexpected payload: size={len(payload):#x}, sha256={digest}")
    semantic_data = verify_semantic_data(payload)
    tables, table_targets = read_tables(payload)
    signed_tables, signed_targets = read_signed_tables(payload)
    table_targets |= signed_targets
    inferred, inferred_targets = infer_relative_tables(payload)
    known_table_addresses = {address for address, _, _, _ in TABLES}
    inferred = [
        table for table in inferred
        if int(table["address"], 16) not in known_table_addresses
    ]
    table_targets |= inferred_targets
    seeds = set(ENTRIES) | set(COMPUTED_SEEDS) | table_targets | {BASE}
    code, targets = discover(payload, seeds)
    data = set(range(BASE, BASE + SIZE, 4)) - code
    expected_data = {
        address
        for address in range(BASE, BASE + SIZE, 4)
        if any(address < end and address + 4 > start for start, end, _ in DATA_REGIONS)
    }
    if data != expected_data:
        missing = sorted(expected_data - data)
        unexpected = sorted(data - expected_data)
        raise ValueError(
            "code/data inventory drift: "
            f"missing={[hex(x) for x in missing[:8]]}, "
            f"unexpected={[hex(x) for x in unexpected[:8]]}"
        )
    return {
        "schema_version": 1,
        "payload_base": f"0x{BASE:08x}", "payload_size": SIZE,
        "payload_sha256": digest, "architecture": "ARMv5TE little-endian ARM mode",
        "method": "recursive traversal from validated entries and relative dispatch tables",
        "counts": {
            "validated_function_entries": len(ENTRIES), "unique_seed_entries": len(seeds),
            "direct_control_flow_targets": len(targets), "code_instructions": len(code),
            "code_bytes": len(code) * 4, "data_bytes": len(data) * 4,
            "semantic_data_bytes": sum(region["size"] for region in semantic_data),
            "control_metadata_bytes": (
                len(data) * 4 - sum(region["size"] for region in semantic_data)
            ),
            "classified_bytes": SIZE,
        },
        "validated_entries": [f"0x{x:08x}" for x in ENTRIES],
        "computed_continuations": [f"0x{x:08x}" for x in COMPUTED_SEEDS],
        "relative_tables": tables,
        "signed_relative_tables": signed_tables,
        "inferred_relative_tables": inferred,
        "embedded_data_regions": [
            {
                "name": name, "start": f"0x{start:08x}",
                "end": f"0x{end:08x}", "size": end - start,
            }
            for start, end, name in DATA_REGIONS
        ],
        "semantic_data_regions": semantic_data,
        "ranges": sorted(
            make_ranges(code, "arm_code")
            + make_ranges(data, "embedded_data"),
            key=lambda item: int(item["start"], 16),
        ),
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--payload", type=Path, default=ROOT / "scratch/mobiclip/data_ov024_0208c8c4.bin")
    parser.add_argument("--output", type=Path, default=ROOT / "scratch/mobiclip/mobiclip_inventory.json")
    args = parser.parse_args()
    inventory = build_inventory(args.payload.read_bytes())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(inventory, indent=2) + "\n", encoding="utf-8")
    counts = inventory["counts"]
    print(f"classified {SIZE:#x} bytes: {counts['code_bytes']:#x} ARM code, {counts['data_bytes']:#x} embedded data")
    print(f"validated entries: {counts['validated_function_entries']}")
    print(f"inventory: {args.output}")


if __name__ == "__main__":
    main()
