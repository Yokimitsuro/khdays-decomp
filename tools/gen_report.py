#!/usr/bin/env python3
"""Generate an objdiff/decomp.dev report with honest C progress.

Only functions classified as ``c_decompiled_matched`` are reported as complete.
ASM stubs, inline ASM placeholders, SDK identifications, and named-only symbols
are deliberately excluded from the main matched progress calculation.
"""
import json
from collections import defaultdict
from pathlib import Path

import audit_progress

ROOT = Path(__file__).resolve().parents[1]


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
        units[func["unit"]].append({
            "name": func["name"],
            "size": func["size"],
            "category": category,
            "matched": category == "c_decompiled_matched",
        })

    report_units = []
    for unit in sorted(units):
        funcs = sorted(units[unit], key=lambda item: item["name"])
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
            },
        })

    all_funcs = [func for funcs in units.values() for func in funcs]
    aggregate = measures(all_funcs)
    aggregate["totalUnits"] = len(units)
    aggregate["completeUnits"] = sum(1 for unit in report_units if unit["metadata"]["complete"])

    report = {
        "measures": aggregate,
        "units": report_units,
        "version": 2,
        "categories": [],
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
