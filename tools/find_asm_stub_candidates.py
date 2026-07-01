#!/usr/bin/env python3
"""List small ASM stubs that are good candidates for real C decompilation."""
import argparse
import json
import os
import re
from pathlib import Path

import audit_progress

ROOT = Path(__file__).resolve().parents[1]


def load_json(path, default):
    if not path.exists():
        return default
    with path.open(encoding="utf-8") as f:
        return json.load(f)


def load_func_index():
    return load_json(ROOT / "build" / "func_index.json", {})


def source_name(path):
    return Path(path).stem if path else None


def addr_suffix(name):
    match = re.search(r"(?:^func_(?:ov\d+_)?|_0x)([0-9a-fA-F]{8})$", name)
    return int(match.group(1), 16) if match else None


def index_entry(func, index, by_unit_addr, by_addr):
    names = [func["name"], source_name(func.get("source"))]
    for name in names:
        if name and name in index:
            return index[name]

    addr = addr_suffix(func["name"]) or addr_suffix(source_name(func.get("source")) or "")
    if addr is None:
        return None

    unit = func["unit"]
    if (unit, addr) in by_unit_addr:
        return by_unit_addr[(unit, addr)]
    entries = by_addr.get(addr, [])
    return entries[0] if len(entries) == 1 else None


def build_index_maps(index):
    by_unit_addr = {}
    by_addr = {}
    for name, info in index.items():
        addr = addr_suffix(name)
        if addr is None:
            continue
        unit = audit_progress.unit_from_module(info.get("module", "unknown"))
        by_unit_addr[(unit, addr)] = info
        by_addr.setdefault(addr, []).append(info)
    return by_unit_addr, by_addr


def verify_hint(func, entry):
    source = func.get("source")
    if not source or entry is None:
        return f"python tools/getcand.py {func['name']}"

    mode = entry.get("mode")
    thumb = " --thumb" if mode == "thumb" else ""
    source_path = str(ROOT / source).replace("\\", "/")

    if entry.get("relocs"):
        obj = str(ROOT / "build" / "delinks" / (entry["module"] + ".o")).replace("\\", "/")
        return f'python tools/match.py "{source_path}" --obj "{obj}" --func {Path(source).stem}{thumb}'

    return f'python tools/match.py "{source_path}" {entry.get("hex", "")}{thumb}'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--limit", type=int, default=40, help="maximum rows to print")
    parser.add_argument("--max-size", type=int, default=64, help="maximum function size in bytes")
    parser.add_argument("--unit", help="only show one unit, e.g. main or ov012")
    parser.add_argument("--include-thumb", action="store_true", help="include Thumb functions")
    parser.add_argument("--include-calls", action="store_true", help="include functions with relocations")
    parser.add_argument("--json", action="store_true", help="write JSON instead of Markdown table")
    args = parser.parse_args()

    functions, _unknown = audit_progress.classify_functions()
    index = load_func_index()
    by_unit_addr, by_addr = build_index_maps(index)
    rows = []

    for func in functions:
        if func["category"] != "asm_stub_matched":
            continue
        if args.unit and func["unit"] != args.unit:
            continue
        if func["size"] > args.max_size:
            continue

        entry = index_entry(func, index, by_unit_addr, by_addr)
        mode = func.get("mode") or (entry.get("mode", "unknown") if entry else "unknown")
        relocs = len(entry.get("relocs", [])) if entry else None
        if not args.include_thumb and mode == "thumb":
            continue
        if not args.include_calls and relocs:
            continue

        rows.append({
            "name": func["name"],
            "source": func.get("source"),
            "unit": func["unit"],
            "size": func["size"],
            "mode": mode,
            "relocs": relocs,
            "verify": verify_hint(func, entry),
        })

    rows.sort(key=lambda row: (
        row["size"],
        row["relocs"] if row["relocs"] is not None else 99,
        row["unit"],
        row["name"],
    ))
    rows = rows[:args.limit]

    if args.json:
        print(json.dumps(rows, indent=2, sort_keys=True))
        return

    print("| Function | Unit | Size | Mode | Relocs | Source |")
    print("|---|---:|---:|---|---:|---|")
    for row in rows:
        relocs = "?" if row["relocs"] is None else str(row["relocs"])
        print(
            f"| `{row['name']}` | {row['unit']} | {row['size']} | "
            f"{row['mode']} | {relocs} | `{row['source']}` |"
        )
    if rows:
        print()
        print("First verify command:")
        print(f"`{rows[0]['verify']}`")


if __name__ == "__main__":
    main()
