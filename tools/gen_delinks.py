#!/usr/bin/env python3
"""Regenerate a module's delinks.txt FILES section from src/ tree.

For each function in symbols.txt that has a matching source file under
src/{auto,calls} or src/asm_stubs/{auto,calls}, emit a FILE entry with the
function's exact .text range and mark it 'complete' so dsd lcf uses the
compiled object from build_path (not the delinked gap).

Unmatched functions are left out of FILES; dsd will emit them as
`_dsd_gap@MODULE_N.o` containing the raw original bytes.
"""
import hashlib
import json
import os
import re
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _discover_src_roots():
    """Kept in sync with tools/audit_progress.py._discover_src_dirs."""
    subs = ["auto", "calls", "asm_stubs/auto", "asm_stubs/calls"]
    out = [ROOT / "src" / s for s in subs]
    ov_root = ROOT / "src" / "overlays"
    if ov_root.exists():
        for ov in sorted(ov_root.iterdir()):
            if not ov.is_dir(): continue
            for s in subs:
                out.append(ov / s)
    libs_root = ROOT / "libs"
    if libs_root.exists():
        for top in sorted(libs_root.iterdir()):
            if not top.is_dir(): continue
            for mod in sorted(top.iterdir()):
                if not mod.is_dir(): continue
                for s in subs:
                    out.append(mod / s)
    return out


SRC_ROOTS = _discover_src_roots()

SYM_RE = re.compile(
    r"(\S+)\s+kind:function\((arm|thumb),[^)]*size=0x([0-9a-fA-F]+)[^)]*\)"
    r"\s+addr:0x([0-9a-fA-F]+)"
)

def _load_known_mismatches():
    """Files whose current C decomp doesn't reproduce the delink baseline
    byte-for-byte. Keeping them out of delinks.txt means dsd fills the gap
    with the original bytes, so the built overlay stays byte-exact.
    Regenerate with `python tools/refresh_mismatches.py`.

    Set KHDAYS_NO_EXCLUDE=1 to force including everything (used by
    refresh_mismatches to produce a per-file delinked baseline for every
    candidate before deciding which are broken)."""
    if os.environ.get("KHDAYS_NO_EXCLUDE") == "1":
        return set()
    # Prefer the freshly-regenerated build copy; fall back to the committed
    # config copy so a fresh clone / wiped build dir keeps the exclusions.
    for p in (ROOT / "build" / "known_mismatches.txt",
              ROOT / "config" / "arm9" / "known_mismatches.txt"):
        if p.exists():
            return {ln.strip() for ln in p.read_text().splitlines()
                    if ln.strip()}
    return set()


KNOWN_MISMATCH = _load_known_mismatches()


def load_symbols(symbols_path):
    """Return list of (addr, size, name, mode) sorted by addr."""
    out = []
    with symbols_path.open(encoding="utf-8") as f:
        for line in f:
            m = SYM_RE.match(line)
            if m:
                out.append((
                    int(m.group(4), 16),
                    int(m.group(3), 16),
                    m.group(1),
                    m.group(2),
                ))
    out.sort()
    return out


def index_sources():
    """Map function name -> src/ path (posix, relative to ROOT)."""
    index = {}
    for root in SRC_ROOTS:
        if not root.exists():
            continue
        for p in sorted(root.glob("*.c")):
            index[p.stem] = str(p.relative_to(ROOT)).replace("\\", "/")
    return index


def read_module_header(delinks_path):
    """Return the current module-header lines (before the first blank line)."""
    header = []
    with delinks_path.open(encoding="utf-8") as f:
        for line in f:
            if line.strip() == "":
                break
            header.append(line.rstrip("\n"))
    return header


def gen_files_block(symbols, src_by_name):
    """For each named function with a source file, emit a FILE entry.

    Returns (blocks, matched_count, gap_count).
    Adjacent functions from the same source file are grouped into one range.
    """
    blocks = []
    matched = 0
    gap = 0
    file_modes = {}
    for addr, size, name, mode in symbols:
        src = src_by_name.get(name)
        if src is None or src in KNOWN_MISMATCH:
            gap += 1
            continue
        end = addr + size
        blocks.append(
            f"{src}:\n"
            f"    complete\n"
            f"    .text       start:0x{addr:08x} end:0x{end:08x}\n"
        )
        file_modes[src] = mode
        matched += 1
    return blocks, matched, gap, file_modes


def unit_of(module_dir):
    """config/arm9 -> main, config/arm9/itcm -> itcm, .../overlays/ov006 -> ov006."""
    rel = module_dir.relative_to(ROOT / "config" / "arm9")
    if rel == Path("."):
        return "main"
    return rel.parts[-1]


def gen_data_block(unit, root=ROOT):
    """FILE entries for reconstructed initialized DATA that the verifier has proved.

    A range only enters the build on the strength of a receipt written by
    tools/verify_data.py or tools/verify_executable_data.py, and the receipt is
    re-checked against the source digest
    here so an edited file drops back out instead of poisoning the link. Ranges are
    merged per section: dsd places one section image at the declared start, so a
    source must own a contiguous run and define its symbols in address order.
    """
    root = Path(root)
    receipts_dir = root / "build" / "data_receipts"
    if not receipts_dir.is_dir():
        return [], {}, 0

    by_source = {}
    for path in sorted(receipts_dir.glob("*.json")):
        receipt = json.loads(path.read_text(encoding="utf-8"))
        if receipt.get("module") != unit or receipt.get("start") is None:
            continue
        source = root / receipt.get("source", "")
        if not source.is_file():
            continue
        digest = hashlib.sha256(source.read_bytes()).hexdigest()
        if digest != receipt.get("source_sha256"):
            continue
        key = receipt["source"]
        by_source.setdefault(key, []).append(
            (receipt["section"], receipt["start"], receipt["end"])
        )

    blocks = []
    modes = {}
    count = 0
    for source in sorted(by_source):
        lines = [f"{source}:", "    complete"]
        for section in sorted({item[0] for item in by_source[source]}):
            spans = sorted((s, e) for sec, s, e in by_source[source] if sec == section)
            merged = []
            for start, end in spans:
                if merged and start == merged[-1][1]:
                    merged[-1][1] = end
                else:
                    merged.append([start, end])
            for start, end in merged:
                lines.append(
                    f"    .{section:<10} start:0x{start:08x} end:0x{end:08x}"
                )
                count += 1
        blocks.append("\n".join(lines) + "\n")
        modes[source] = "arm"
    return blocks, modes, count


def write_text_retry(path, text, tries=8):
    """write_text con reintento sobre OSError.

    ⚠ En este equipo, abrir un fichero para escritura en E: falla de vez en cuando con
    `OSError: [Errno 22] Invalid argument`, sin patron (overlay distinto cada vez) y con exito
    inmediato al repetir. Es un filtro del sistema de ficheros -- antivirus, casi seguro -- no un
    problema del arbol. Sin este reintento tumbaba `configure.py` entero y el gate de 306 se caia
    ~7 veces entre el 18 y el 19 de julio de 2026; se diagnostico mal dos veces ("lo mata algo de
    fuera sin imprimir nada") porque el traceback iba a stderr y se leia el flujo mezclado.
    """
    for i in range(tries):
        try:
            path.write_text(text, encoding="utf-8", newline="\n")
            return
        except OSError:
            if i == tries - 1:
                raise
            time.sleep(0.05 * (i + 1))


def main():
    if len(sys.argv) < 2:
        print("usage: gen_delinks.py <module_dir>", file=sys.stderr)
        print("  e.g. config/arm9/overlays/ov000", file=sys.stderr)
        sys.exit(2)

    module_dir = Path(sys.argv[1]).resolve()
    delinks_txt = module_dir / "delinks.txt"
    symbols_txt = module_dir / "symbols.txt"

    header = read_module_header(delinks_txt)
    symbols = load_symbols(symbols_txt)
    src_by_name = index_sources()
    blocks, matched, gap, file_modes = gen_files_block(symbols, src_by_name)
    data_blocks, data_modes, data_ranges = gen_data_block(unit_of(module_dir))
    file_modes.update(data_modes)

    out = ["\n".join(header), ""]
    out.extend(blocks)
    out.extend(data_blocks)
    write_text_retry(delinks_txt, "\n".join(out).rstrip() + "\n")

    # Merge into the shared file_modes.json (configure.py reads it to know
    # which files need -thumb).
    modes_path = ROOT / "build" / "file_modes.json"
    all_modes = {}
    if modes_path.exists():
        all_modes = json.loads(modes_path.read_text(encoding="utf-8"))
    all_modes.update(file_modes)
    modes_path.parent.mkdir(exist_ok=True)
    write_text_retry(modes_path, json.dumps(all_modes, indent=2, sort_keys=True))

    print(
        f"{delinks_txt.relative_to(ROOT)}: "
        f"{matched} matched, {gap} gap ({len(symbols)} total)"
        + (f", {data_ranges} verified data range(s)" if data_ranges else "")
    )


if __name__ == "__main__":
    main()
