#!/usr/bin/env python3
"""Rewrite stale bare `SYMBOL_0xADDR` references inside a caller's file
to the overlay-scoped `SYMBOL_ovNN_0xADDR` that its own overlay owns.

Needed because apply_names disambiguated symbol definitions (see
sdk/apply_names.py) but callers of those symbols — which live in other
files scattered across overlays — still hold the old bare name.
Idempotent.
"""
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

# Build (base, addr) -> {ovNN: unique_stem} from every existing .c file
# whose stem carries an _ovNN_ disambiguation suffix.
STEM_RE = re.compile(r"^(?P<base>[A-Za-z_]\w*)_(?P<ov>ov\d+)_0x(?P<addr>[0-9a-fA-F]{8})$")
disambig = defaultdict(dict)
for p in list((ROOT / "libs").rglob("*.c")) + list((ROOT / "src" / "overlays").rglob("*.c")):
    m = STEM_RE.match(p.stem)
    if m:
        disambig[(m.group("base"), m.group("addr").lower())][m.group("ov")] = p.stem


OV_IN_PATH_RE = re.compile(r"[/\\](ov\d+)[/\\]")
touched = 0
for c_file in list((ROOT / "src").rglob("*.c")) + list((ROOT / "libs").rglob("*.c")):
    m = OV_IN_PATH_RE.search(str(c_file))
    if not m:
        continue
    caller_ov = m.group(1)
    text = c_file.read_text(encoding="utf-8", errors="replace")
    new_text = text
    for (base, addr), by_ov in disambig.items():
        target = by_ov.get(caller_ov)
        if not target:
            continue
        old = f"{base}_0x{addr}"
        if old == target:
            continue
        if old in new_text:
            new_text = re.sub(rf"\b{re.escape(old)}\b", target, new_text)
    if new_text != text:
        c_file.write_text(new_text, encoding="utf-8", newline="\n")
        touched += 1

print(f"touched {touched} files")
