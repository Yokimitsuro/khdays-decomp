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


def load_verified_ranges(root=ROOT):
    """Ranges proved by tools/verify_data.py, re-proved here instead of trusted.

    A receipt records what was verified; it is not a licence to count it. Every
    receipt is re-run against the ROM-derived index, so a stale or edited source
    stops counting on its own. Where the index is absent -- CI has no ROM and no
    delinked build -- there is nothing to check against and the honest answer is
    an empty list, which is why the public number stays at zero there.
    """
    root = Path(root)
    index_path = root / "build" / "data_index.json"
    receipts_dir = root / "build" / "data_receipts"
    if not index_path.exists():
        return [], "no DATA index; run tools/index_data.py on a delinked build"
    if not receipts_dir.is_dir():
        return [], "no DATA receipts yet"

    import sys

    sys.path.insert(0, str(Path(__file__).resolve().parent))
    try:
        import verify_data
    except ImportError as exc:
        # Verifying needs pyelftools and the compiler; a plain checkout has neither.
        # Reporting zero is the honest answer there, not a crash.
        return [], "the verifier is unavailable here (%s)" % exc

    index = json.loads(index_path.read_text(encoding="utf-8"))
    ranges = []
    rejected = []
    for path in sorted(receipts_dir.glob("*.json")):
        receipt = json.loads(path.read_text(encoding="utf-8"))
        symbol = receipt.get("symbol")
        source = root / receipt.get("source", "")
        if not source.is_file():
            rejected.append(f"{symbol}: source {receipt.get('source')} is gone")
            continue
        try:
            status, message, info = verify_data.verify(str(source), symbol, index)
        except ImportError as exc:
            # The compiler front end is only pulled in when a proof is actually run.
            return [], "the verifier is unavailable here (%s)" % exc
        if status != verify_data.MATCH:
            rejected.append(f"{symbol}: {message}")
            continue
        if info.get("start") is None:
            rejected.append(f"{symbol}: verified but its address is unknown, so it cannot count")
            continue
        # Keyed by unit as well as address: overlays are loaded over each other, so
        # ov006 .rodata and ov009 .data really do share addresses and an
        # address-only match would count the same bytes for both.
        ranges.append((info["module"], info["section"], info["start"], info["end"]))
    return ranges, "; ".join(rejected)


def _overlap(item, ranges):
    return sum(
        max(0, min(item["end"], end) - max(item["start"], start))
        for unit, section, start, end in ranges
        if unit == item["unit"] and section == item["section"]
    )


def main():
    inventory = load_data_inventory()
    total = sum(item["size"] for item in inventory)
    ranges, note = load_verified_ranges()
    for item in inventory:
        covered = _overlap(item, ranges)
        item["verified_bytes"] = covered
        item["matched"] = covered == item["size"] and item["size"] > 0
    matched = sum(item["verified_bytes"] for item in inventory)
    percent = 100.0 * matched / total if total else 100.0
    print(f"initialized DATA: {matched}/{total} bytes ({percent:.2f}%)")
    if note:
        print(f"  not counted: {note}")
    for item in inventory:
        if item.get("classification") == "executable_payload":
            print(
                f"{item['name']}: {item['start']:#010x}-{item['end']:#010x} "
                f"({item['size']} bytes, executable payload, unmatched)"
            )


if __name__ == "__main__":
    main()
