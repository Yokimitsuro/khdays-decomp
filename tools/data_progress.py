#!/usr/bin/env python3
"""Inventory initialized ARM9 data for progress reporting.

The public report can be generated without a ROM: section extents come from the
checked-in delink configuration. Bytes remain unmatched until a separate
byte/relocation verifier supplies evidence; preserving a binary payload or
naming a symbol never counts as reconstructed DATA.
"""
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SECTION_RE = re.compile(
    r"^\s+\.(?P<section>text|rodata|ctor|data|bss)\s+"
    r"start:0x(?P<start>[0-9a-fA-F]+)\s+end:0x(?P<end>[0-9a-fA-F]+)"
)


def unit_for_delinks(path, root=ROOT):
    rel = path.relative_to(root / "config" / "arm9")
    if rel.parts == ("delinks.txt",):
        return "main"
    if len(rel.parts) == 2 and rel.parts[1] == "delinks.txt":
        return rel.parts[0]
    if len(rel.parts) == 3 and rel.parts[0] == "overlays" and rel.parts[2] == "delinks.txt":
        return rel.parts[1]
    raise ValueError(f"Unrecognized ARM9 delinks path: {path}")


def read_module_sections(path, initialized_sections):
    """Read only the leading module section map, never per-source ranges."""
    regions = []
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line.strip():
            break
        match = SECTION_RE.match(line)
        if not match:
            break
        section = match.group("section")
        if section not in initialized_sections:
            continue
        start = int(match.group("start"), 16)
        end = int(match.group("end"), 16)
        if end < start:
            raise ValueError(f"Invalid {section} range in {path}: {start:#x}..{end:#x}")
        if end != start:
            regions.append({"section": section, "start": start, "end": end})
    return regions


def _split_with_overrides(region, overrides):
    cuts = {region["start"], region["end"]}
    applicable = []
    for override in overrides:
        start = int(override["start"], 0)
        end = int(override["end"], 0)
        if end <= region["start"] or start >= region["end"]:
            continue
        if start < region["start"] or end > region["end"] or end <= start:
            raise ValueError(
                f"Classification override {override['name']} crosses a section boundary"
            )
        cuts.update((start, end))
        applicable.append((start, end, override))

    out = []
    ordered = sorted(cuts)
    for start, end in zip(ordered, ordered[1:]):
        owner = [item for item in applicable if item[0] <= start and end <= item[1]]
        if len(owner) > 1:
            raise ValueError(f"Overlapping DATA classification overrides at {start:#x}")
        item = dict(region, start=start, end=end)
        if owner:
            override = owner[0][2]
            item["name"] = override["name"]
            item["progress_category"] = override["progress_category"]
            item["classification"] = override["classification"]
        out.append(item)
    return out


def load_data_inventory(root=ROOT, policy_path=None):
    """Return initialized data regions with honest, initially-unmatched state."""
    root = Path(root)
    policy_path = Path(policy_path) if policy_path else root / "config" / "arm9" / "data_progress.json"
    policy = json.loads(policy_path.read_text(encoding="utf-8"))
    if policy.get("schema_version") != 1:
        raise ValueError("Unsupported DATA progress policy schema")
    if policy.get("matched_ranges"):
        raise ValueError(
            "matched_ranges requires a byte-and-relocation verifier; manual DATA completion is forbidden"
        )

    sections = set(policy["initialized_sections"])
    overrides_by_unit = {}
    for override in policy.get("classification_overrides", []):
        overrides_by_unit.setdefault(override["unit"], []).append(override)

    inventory = []
    cfg = root / "config" / "arm9"
    for path in sorted(cfg.rglob("delinks.txt")):
        unit = unit_for_delinks(path, root)
        for region in read_module_sections(path, sections):
            region["unit"] = unit
            for item in _split_with_overrides(region, overrides_by_unit.get(unit, [])):
                item["size"] = item["end"] - item["start"]
                item["matched"] = False
                inventory.append(item)

    for unit, overrides in overrides_by_unit.items():
        for override in overrides:
            start = int(override["start"], 0)
            end = int(override["end"], 0)
            covered = any(
                item["unit"] == unit and item["start"] == start and item["end"] == end
                for item in inventory
            )
            if not covered:
                raise ValueError(f"DATA override not found in section inventory: {override['name']}")
    return inventory


def main():
    inventory = load_data_inventory()
    total = sum(item["size"] for item in inventory)
    matched = sum(item["size"] for item in inventory if item["matched"])
    percent = 100.0 * matched / total if total else 100.0
    print(f"initialized DATA: {matched}/{total} bytes ({percent:.2f}%)")
    for item in inventory:
        if item.get("classification") == "executable_payload":
            print(
                f"{item['name']}: {item['start']:#010x}-{item['end']:#010x} "
                f"({item['size']} bytes, executable payload, unmatched)"
            )


if __name__ == "__main__":
    main()
