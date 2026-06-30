#!/usr/bin/env python3
"""Audit decompilation progress categories.

This report is intentionally separate from byte-matching verification. Its job is
to keep public progress metrics honest by distinguishing real C implementations
from temporary ASM-based matches and SDK/library identifications.
"""
import json
import os
import re
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC_DIRS = [ROOT / "src" / "auto", ROOT / "src" / "calls"]
BUILD_DIR = ROOT / "build"

ASM_MARKERS = (
    r"\basm\s+(?:void|int|unsigned|signed|char|short|long|float|double|\*)",
    r"\b__asm\b",
    r"\bINLINE_ASM\b",
    r"\bNON_MATCHING\b",
    r"\bGLOBAL_ASM\b",
    r"\bINCLUDE_ASM\b",
)
ASM_RE = re.compile("|".join(f"(?:{pat})" for pat in ASM_MARKERS))


def load_json(path, default):
    if not path.exists():
        return default
    with path.open(encoding="utf-8") as f:
        return json.load(f)


def load_function_index():
    use_func_index = os.environ.get("KHDAYS_PROGRESS_USE_FUNC_INDEX") == "1"
    index = load_json(ROOT / "build" / "func_index.json", None)
    if index is not None and use_func_index:
        return index

    index = {}
    for symbols_path in (ROOT / "config").glob("**/symbols.txt"):
        path_text = str(symbols_path).replace("\\", "/")
        ov_match = re.search(r"overlays/(ov\d+)", path_text)
        module = (
            f"overlay@{ov_match.group(1)}" if ov_match
            else "itcm@itcm" if "/itcm/" in path_text
            else "dtcm@dtcm" if "/dtcm/" in path_text
            else "main@main"
        )
        with symbols_path.open(encoding="utf-8", errors="replace") as f:
            for line in f:
                match = re.match(r"(\S+)\s+kind:function\((arm|thumb),[^)]*size=0x([0-9a-fA-F]+)", line)
                if match:
                    index[match.group(1)] = {
                        "module": module,
                        "mode": match.group(2),
                        "size": int(match.group(3), 16),
                    }
    return index


def unit_from_module(module):
    match = re.search(r"@(ov\d+|main|itcm|dtcm)", module)
    return match.group(1) if match else module


def addr_suffix(name):
    match = re.search(r"(?:^func_(?:ov\d+_)?|_0x)([0-9a-fA-F]{8})$", name)
    return int(match.group(1), 16) if match else None


def source_category(path):
    text = path.read_text(encoding="utf-8", errors="replace")
    if ASM_RE.search(text):
        return "asm_stub_matched"
    return "c_decompiled_matched"


def load_sources():
    by_name = {}
    by_unit_addr = {}
    by_addr = defaultdict(list)
    unknown = []

    for src_dir in SRC_DIRS:
        for path in sorted(src_dir.glob("*.c")):
            name = path.stem
            category = source_category(path)
            entry = {
                "path": str(path.relative_to(ROOT)).replace("\\", "/"),
                "category": category,
            }
            by_name[name] = entry

            ov_match = re.match(r"func_(ov\d+)_([0-9a-fA-F]{8})$", name)
            if ov_match:
                by_unit_addr[(ov_match.group(1), int(ov_match.group(2), 16))] = entry
            else:
                addr = addr_suffix(name)
                if addr is not None:
                    by_addr[addr].append(entry)
                    unknown.append(entry)

    return by_name, by_unit_addr, by_addr, unknown


def sdk_name_map():
    names = load_json(ROOT / "sdk" / "build" / "names.json", {})
    if not isinstance(names, dict):
        return {}
    return names


def classify_functions():
    index = load_function_index()
    sdk_names = sdk_name_map()
    sdk_names_by_addr = {
        addr: sdk_name
        for sdk_func, sdk_name in sdk_names.items()
        for addr in [addr_suffix(sdk_func)]
        if addr is not None
    }
    sources_by_name, sources_by_unit_addr, sources_by_addr, unmapped_sources = load_sources()

    functions = []
    source_hits = set()

    for name, info in sorted(index.items()):
        unit = unit_from_module(info.get("module", "unknown"))
        addr = addr_suffix(name)
        source = sources_by_name.get(name)
        if source is None and addr is not None:
            source = sources_by_unit_addr.get((unit, addr))
        if source is None and addr is not None and len(sources_by_addr.get(addr, [])) == 1:
            source = sources_by_addr[addr][0]

        if source is not None:
            category = source["category"]
            path = source["path"]
            source_hits.add(path)
        elif name in sdk_names or addr in sdk_names_by_addr:
            category = "sdk_identified"
            path = None
        else:
            category = "named_only"
            path = None

        functions.append({
            "name": name,
            "unit": unit,
            "size": int(info.get("size", 0)),
            "mode": info.get("mode"),
            "category": category,
            "source": path,
            "sdk_name": sdk_names.get(name) or sdk_names_by_addr.get(addr),
        })

    mapped_paths = {f["source"] for f in functions if f["source"]}
    unknown_sources = [s for s in unmapped_sources if s["path"] not in mapped_paths]
    for name, source in sorted(sources_by_name.items()):
        if source["path"] not in mapped_paths and name not in index:
            unknown_sources.append(source)

    return functions, unknown_sources


def summarize(functions, unknown_sources):
    counts = Counter(f["category"] for f in functions)
    sizes = Counter()
    units = defaultdict(Counter)

    for func in functions:
        sizes[func["category"]] += func["size"]
        units[func["unit"]][func["category"]] += 1

    total_functions = len(functions)
    total_code = sum(f["size"] for f in functions)

    return {
        "total_functions": total_functions,
        "total_code_bytes": total_code,
        "counts": dict(sorted(counts.items())),
        "code_bytes": dict(sorted(sizes.items())),
        "unknown_source_files": len(unknown_sources),
        "units": {unit: dict(counter) for unit, counter in sorted(units.items())},
    }


def write_markdown(summary):
    counts = summary["counts"]
    sizes = summary["code_bytes"]
    total_functions = summary["total_functions"]
    total_code = summary["total_code_bytes"]
    rows = []
    labels = {
        "c_decompiled_matched": "Real C-decompiled matched functions",
        "asm_stub_matched": "Inline ASM / ASM stub matched functions",
        "sdk_identified": "SDK/library byte-match identifications",
        "named_only": "Named but not decompiled",
        "unknown_or_needs_review": "Unknown or needs review",
    }

    for category in labels:
        count = counts.get(category, 0)
        code = sizes.get(category, 0)
        pct = (100.0 * count / total_functions) if total_functions else 0.0
        code_pct = (100.0 * code / total_code) if total_code else 0.0
        rows.append(f"| {labels[category]} | {count} | {pct:.1f}% | {code} | {code_pct:.1f}% |")

    lines = [
        "# Progress audit",
        "",
        "Generated by `python tools/audit_progress.py`.",
        "",
        "| Category | Functions | Function % | Code bytes | Code % |",
        "|---|---:|---:|---:|---:|",
        *rows,
        "",
        f"Unknown source files needing review: {summary['unknown_source_files']}",
        "",
        "Only `c_decompiled_matched` should be counted as real C decompilation progress.",
        "ASM stubs and SDK/library identifications are useful, but they are tracked separately.",
        "",
    ]
    return "\n".join(lines)


def main():
    functions, unknown_sources = classify_functions()
    summary = summarize(functions, unknown_sources)
    report = {
        "summary": summary,
        "functions": functions,
        "unknown_sources": unknown_sources,
    }

    BUILD_DIR.mkdir(exist_ok=True)
    (BUILD_DIR / "progress_audit.json").write_text(
        json.dumps(report, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    (BUILD_DIR / "progress_audit.md").write_text(
        write_markdown(summary),
        encoding="utf-8",
        newline="\n",
    )

    c_count = summary["counts"].get("c_decompiled_matched", 0)
    asm_count = summary["counts"].get("asm_stub_matched", 0)
    sdk_count = summary["counts"].get("sdk_identified", 0)
    print(
        "progress_audit -> "
        f"C={c_count}, ASM={asm_count}, SDK={sdk_count}, "
        f"total={summary['total_functions']}"
    )


if __name__ == "__main__":
    main()
