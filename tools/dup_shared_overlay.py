#!/usr/bin/env python3
"""Create per-overlay source-file duplicates for symbols that share an
address across multiple overlays.

Background: overlays like ov030..ov049 all contain a physical copy of the
same library-like function (e.g. SNDi_UnlockMutex at 0x020b3220). The
apply_names disambiguator produces one uniquely-named symbol per overlay
(SNDi_UnlockMutex_ov030_0x..., _ov031_..., ...) but only ONE source file
exists (the one that was there before disambiguation). Every overlay's
.bin needs its own compiled .o at that address, so `dsd delink` needs a
source per overlay per address.

This tool walks every disambiguated symbol group in the symbols.txt tree
and duplicates the existing source file to each missing per-overlay name.
Idempotent — running it twice is a no-op.
"""
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

SYM_RE = re.compile(
    r"^(\S+)\s+kind:function\((arm|thumb),[^)]*\)\s+addr:0x([0-9a-fA-F]+)"
)
# Matches disambiguated names like BASE_ovNN_0xADDR
DISAMBIG_RE = re.compile(r"^(?P<base>[A-Za-z_]\w*)_(?P<ov>ov\d+)_0x(?P<addr>[0-9a-fA-F]{8})$")


def load_symbols():
    """Return {symbol_name: overlay_id} for every disambiguated symbol
    (that is, whose name carries an _ovNN_ suffix matching the overlay it
    was defined in)."""
    out = {}
    for sym_txt in (ROOT / "config").glob("**/symbols.txt"):
        text = str(sym_txt).replace("\\", "/")
        ov_m = re.search(r"overlays/(ov\d+)/", text)
        if not ov_m:
            continue
        ov = ov_m.group(1)
        for line in sym_txt.read_text(encoding="utf-8", errors="replace").splitlines():
            m = SYM_RE.match(line)
            if not m:
                continue
            name = m.group(1)
            dm = DISAMBIG_RE.match(name)
            if dm and dm.group("ov") == ov:
                out[name] = ov
    return out


def find_existing_file(stem):
    """Return the .c path (if any) that matches this stem, searched in
    libs/ then src/overlays/."""
    for root in (ROOT / "libs", ROOT / "src" / "overlays"):
        matches = list(root.rglob(f"{stem}.c"))
        if matches:
            return matches[0]
    return None


def main():
    sym_to_ov = load_symbols()
    # Group by (base, addr) so we can see peer overlays for each shared code.
    groups = defaultdict(list)
    for name in sym_to_ov:
        m = DISAMBIG_RE.match(name)
        groups[(m.group("base"), m.group("addr").lower())].append(name)

    created = 0
    skipped = 0
    for (base, addr), names in groups.items():
        if len(names) < 2:
            continue
        # Find one existing source file among the peers.
        existing = None
        existing_name = None
        for name in names:
            path = find_existing_file(name)
            if path:
                existing = path
                existing_name = name
                break
        if not existing:
            skipped += len(names)
            continue
        src_text = existing.read_text(encoding="utf-8", errors="replace")
        for name in names:
            if name == existing_name:
                continue
            if find_existing_file(name):
                continue  # already present
            dst = existing.with_name(name + ".c")
            new_text = re.sub(rf"\b{re.escape(existing_name)}\b", name, src_text)
            dst.write_text(new_text, encoding="utf-8", newline="\n")
            created += 1

    print(f"created {created} per-overlay duplicate .c files")
    if skipped:
        print(f"WARNING: {skipped} shared symbols had NO existing source")


if __name__ == "__main__":
    main()
