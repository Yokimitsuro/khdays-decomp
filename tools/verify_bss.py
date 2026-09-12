#!/usr/bin/env python3
"""Verify a source that DEFINES zero-initialised globals of its module's .bss and receipt the range.

    python tools/verify_bss.py <source.c> <symbol> [--receipt]

Why this exists (2026-09-12, ov011): mwcc addresses a global defined in the same
translation unit with `= 0` section-relative (`ldr rX,=.bss ; ldr rY,[rX,#off]`)
and treats such a SCALAR global as a different alias class from aggregates, so a
load of it may move above stores to a local struct. Several ROM functions can only
be reproduced that way (Ov011_Mode2Teardown, Ov011_InitTitleTileSurface,
Ov011_CreateTitleObjects). The code of such a function is verified byte-exact by
verify_idx.py as usual; what this tool proves is the DATA side: the compiled
object's .bss is relocation-free, its first global symbol is <symbol> (the address
symbols.txt gives it is the section base), every global it defines lies inside
the module's .bss range, and the emitted size fits that range. On success with
--receipt it writes build/data_receipts/<symbol>.json with section "bss", which
gen_delinks.py turns into a `.bss start:.. end:..` claim so dsd links the source's
own .bss at the right address instead of a delinked gap.
"""
import hashlib
import json
import os
import re
import sys
from datetime import datetime, timezone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from match import compile_c  # noqa: E402

RECEIPTS = os.path.join(ROOT, "build", "data_receipts")


def module_of(symbol):
    m = re.match(r"(?:data|func)_(ov\d+)_", symbol)
    return m.group(1) if m else "main"


def module_bss_range(unit):
    """(.bss start, end) from the module header of its delinks.txt."""
    path = (os.path.join(ROOT, "config", "arm9", "delinks.txt") if unit == "main"
            else os.path.join(ROOT, "config", "arm9", "overlays", unit, "delinks.txt"))
    with open(path, encoding="utf-8") as fh:
        for line in fh:
            m = re.match(r"\s+\.bss\s+start:0x([0-9a-f]+)\s+end:0x([0-9a-f]+)\s+kind:bss", line)
            if m:
                return int(m.group(1), 16), int(m.group(2), 16)
    raise SystemExit("no .bss header line for module " + unit)


def symbol_address(unit, symbol):
    path = (os.path.join(ROOT, "config", "arm9", "symbols.txt") if unit == "main"
            else os.path.join(ROOT, "config", "arm9", "overlays", unit, "symbols.txt"))
    with open(path, encoding="utf-8") as fh:
        for line in fh:
            m = re.match(r"(\S+)\s+kind:bss(?:\([^)]*\))?\s+addr:0x([0-9a-f]+)", line)
            if m and m.group(1) == symbol:
                return int(m.group(2), 16)
    raise SystemExit("%s is not a bss symbol of %s" % (symbol, unit))


def bss_of(o_path):
    """(.bss size, {global symbol: offset}) of one compiled object; None if it has no .bss."""
    from elftools.elf.elffile import ELFFile
    with open(o_path, "rb") as stream:
        elf = ELFFile(stream)
        bss = None
        bss_index = None
        for i, section in enumerate(elf.iter_sections()):
            if section.name == ".bss":
                bss, bss_index = section, i
        if bss is None:
            return None
        for section in elf.iter_sections():
            if section.name in (".rel.bss", ".rela.bss") and section.num_relocations():
                raise SystemExit(".bss carries relocations; only zero-initialised scalars are supported")
        symtab = elf.get_section_by_name(".symtab")
        globals_ = {}
        for sym in symtab.iter_symbols():
            if sym["st_shndx"] == bss_index and sym["st_info"]["bind"] == "STB_GLOBAL" and sym.name:
                globals_[sym.name] = int(sym["st_value"])
        return int(bss["sh_size"]), globals_


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if len(args) != 2:
        raise SystemExit(__doc__)
    cpath, symbol = args
    receipt = "--receipt" in sys.argv
    unit = module_of(symbol)
    base = symbol_address(unit, symbol)
    lo, hi = module_bss_range(unit)
    o = compile_c(cpath, "--thumb" in sys.argv)
    found = bss_of(o)
    if found is None:
        raise SystemExit(">>> DIFIERE <<< the object defines no .bss")
    size, globals_ = found
    if globals_.get(symbol) != 0:
        raise SystemExit(">>> DIFIERE <<< %s is not the first (offset 0) global of the object's .bss: %s" % (symbol, globals_))
    if not (lo <= base and base + size <= hi):
        raise SystemExit(">>> DIFIERE <<< .bss 0x%08x-0x%08x does not fit the module's 0x%08x-0x%08x" % (base, base + size, lo, hi))
    for name, off in sorted(globals_.items(), key=lambda kv: kv[1]):
        m = re.match(r"data_(?:ov\d+_)?([0-9a-f]{8})$", name)
        if m and int(m.group(1), 16) != base + off:
            raise SystemExit(">>> DIFIERE <<< %s sits at 0x%08x, its name claims 0x%08x" % (name, base + off, int(m.group(1), 16)))
    print(">>> MATCH <<< .bss %d bytes @0x%08x-0x%08x, globals %s" % (
        size, base, base + size, ", ".join("%s+0x%x" % (n, off) for n, off in sorted(globals_.items(), key=lambda kv: kv[1]))))
    if receipt:
        os.makedirs(RECEIPTS, exist_ok=True)
        rel = os.path.relpath(os.path.abspath(cpath), ROOT).replace(os.sep, "/")
        with open(cpath, "rb") as fh:
            digest = hashlib.sha256(fh.read()).hexdigest()
        info = {
            "schema_version": 1,
            "symbol": symbol,
            "source": rel,
            "source_sha256": digest,
            "verified_at": datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds"),
            "module": unit,
            "section": "bss",
            "start": base,
            "end": base + size,
            "size": size,
            "relocs": 0,
        }
        path = os.path.join(RECEIPTS, symbol + ".json")
        with open(path, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(info, fh, indent=2)
            fh.write("\n")
        print("receipt: " + os.path.relpath(path, ROOT))


if __name__ == "__main__":
    main()
