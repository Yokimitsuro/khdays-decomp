#!/usr/bin/env python3
"""Generate an objdiff/decomp.dev report with honest C progress.

Only functions classified as ``c_decompiled_matched`` are reported as complete.
ASM stubs, inline ASM placeholders, SDK identifications, and named-only symbols
are deliberately excluded from the main matched progress calculation.

Emits `progress_categories` per unit so decomp.dev can show separate bars
for NitroSDK identifications, per-overlay progress, and main-module code.
"""
import json
import re
from collections import defaultdict
from pathlib import Path

import audit_progress

ROOT = Path(__file__).resolve().parents[1]


# Category IDs used by decomp.dev's report. Human-friendly names in
# CATEGORY_LABELS below.
def category_for_source(src_path, unit):
    """Map a source file path to its objdiff progress category id.
    Falls back on the unit name (from the symbol index) when there is no
    source file yet — so named-only functions still land in the right
    per-overlay or main bucket."""
    if src_path:
        s = src_path.replace("\\", "/")
        m = re.match(r"^libs/(msl|nitro)/([^/]+)/", s)
        if m:
            return f"{m.group(1)}/{m.group(2)}"
        m = re.match(r"^src/overlays/(ov\d+)/", s)
        if m:
            return f"overlays/{m.group(1)}"
        if s.startswith("src/"):
            return "main"
    # Fall back on unit id from the symbol index.
    if unit and unit.startswith("ov"):
        return f"overlays/{unit}"
    if unit in ("main", "itcm", "dtcm"):
        return "main"
    return "unknown"


CATEGORY_LABELS = {
    "main": "Main + ITCM + DTCM",
    "unknown": "Unknown / uncategorized",
}
# libs/nitro/<mod> and libs/msl/c become "NitroSDK: <mod>" etc.
NITRO_NICE = {
    "wm": "Wireless (WM)", "snd": "Sound (SND)", "os": "OS", "nns": "NNS",
    "mtx": "Matrix (MTX)", "fs": "Filesystem (FS)", "fx": "Fixed-point (FX)",
    "gx": "Graphics (GX)", "mi": "Memory intrinsics (MI)", "pxi": "PXI",
    "card": "CARD", "nitro": "NitroSDK (misc)",
}


def measures(funcs):
    total = sum(func["size"] for func in funcs)
    matched = sum(func["size"] for func in funcs if func["matched"])
    total_functions = len(funcs)
    matched_functions = sum(1 for func in funcs if func["matched"])
    percent = 100.0 * matched / total if total else 100.0

    # protobuf-JSON: uint64 fields are strings; uint32 and floats are numbers.
    return {
        "fuzzyMatchPercent": percent,
        "totalCode": str(total),
        "matchedCode": str(matched),
        "matchedCodePercent": percent,
        "totalData": "0",
        "matchedData": "0",
        "matchedDataPercent": 100.0,
        "totalFunctions": total_functions,
        "matchedFunctions": matched_functions,
        "matchedFunctionsPercent": (
            100.0 * matched_functions / total_functions if total_functions else 100.0
        ),
        "completeCode": str(matched),
        "completeCodePercent": percent,
        "completeData": "0",
        "completeDataPercent": 100.0,
    }


def main():
    audited_functions, _unknown_sources, _shared_overlay_copies = audit_progress.classify_functions()
    units = defaultdict(list)

    for func in audited_functions:
        category = func["category"]
        pc = category_for_source(func.get("source"), func.get("unit"))
        units[func["unit"]].append({
            "name": func["name"],
            "size": func["size"],
            "category": category,
            "progress_category": pc,
            "matched": category == "c_decompiled_matched",
        })

    report_units = []
    all_categories = set()
    for unit in sorted(units):
        funcs = sorted(units[unit], key=lambda item: item["name"])
        # Attribute unit to the most-common progress category among its
        # functions (usually just one — overlays are self-contained).
        cat_count = defaultdict(int)
        for f in funcs:
            cat_count[f["progress_category"]] += f["size"] or 1
        unit_cats = sorted(cat_count, key=cat_count.get, reverse=True)
        primary = unit_cats[0] if unit_cats else "unknown"
        all_categories.update(unit_cats)
        report_units.append({
            "name": unit,
            "measures": measures(funcs),
            "sections": [],
            "functions": [
                {
                    "name": func["name"],
                    "size": str(func["size"]),
                    "fuzzyMatchPercent": 100.0 if func["matched"] else 0.0,
                }
                for func in funcs
            ],
            "metadata": {
                "moduleName": unit,
                "complete": all(func["matched"] for func in funcs),
                "progressCategories": [primary],
            },
        })

    all_funcs = [func for funcs in units.values() for func in funcs]
    aggregate = measures(all_funcs)
    aggregate["totalUnits"] = len(units)
    aggregate["completeUnits"] = sum(1 for unit in report_units if unit["metadata"]["complete"])

    def label_for(cat_id):
        if cat_id in CATEGORY_LABELS:
            return CATEGORY_LABELS[cat_id]
        if cat_id.startswith("nitro/"):
            return "NitroSDK: " + NITRO_NICE.get(cat_id.split("/", 1)[1], cat_id.split("/", 1)[1])
        if cat_id.startswith("msl/"):
            return "MSL: " + cat_id.split("/", 1)[1]
        if cat_id.startswith("overlays/ov"):
            return "Overlay " + cat_id.split("/ov", 1)[1]
        return cat_id

    categories = [
        {"id": cid, "name": label_for(cid)}
        for cid in sorted(all_categories)
    ]

    report = {
        "measures": aggregate,
        "units": report_units,
        "version": 2,
        "categories": categories,
    }

    build_dir = ROOT / "build"
    build_dir.mkdir(exist_ok=True)
    with (build_dir / "report.json").open("w", encoding="utf-8") as f:
        json.dump(report, f, indent=2, sort_keys=True)
        f.write("\n")

    print(
        "report.json -> "
        f"{len(units)} unidades, {aggregate['matchedCodePercent']:.2f}% C code "
        f"({aggregate['matchedCode']}/{aggregate['totalCode']} bytes), "
        f"{aggregate['matchedFunctions']}/{aggregate['totalFunctions']} funcs"
    )


if __name__ == "__main__":
    main()
