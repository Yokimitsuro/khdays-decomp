#!/usr/bin/env python3
"""Index every initialized-data symbol of the delinked objects: bytes + relocations.

This is the DATA counterpart of index_funcs.py. The ground truth is the same:
build/delinks/*.o, produced by dsd from the ROM. Each module's gap objects all carry
the module's complete .rodata/.data image, so the same symbol shows up many times;
the index keeps one copy and checks the duplicates agree.

    python tools/index_data.py

Writes build/data_index.json:

    "data_ov006_0205630c": {
        "hex": "...", "size": 152, "section": "rodata", "module": "ov006",
        "addr": 33776396, "relocs": [[off, "sym"], ...], "addends": {off: addend}
    }

Like index_funcs.py this MERGES: a symbol that already has reconstructed source no
longer appears in the gap objects, and dropping it would break re-verification.
"""
import glob
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DELINK = os.path.join(ROOT, "build", "delinks")
INDEX_PATH = os.path.join(ROOT, "build", "data_index.json")

DATA_SECTIONS = (".rodata", ".data", ".ctor")
# _dsd_gap@ov006_10.o -> ov006, _dsd_gap@main_3.o -> main
MODULE_RE = re.compile(r"^_dsd_gap@(?P<unit>[^_]+(?:_[a-z]+)*?)_\d+$")
# data_ov006_0205630c / data_0204c058 -- the address is part of the name.
#
# Anchored to the END on purpose. dsd also emits names like data_ov002_0207ef80_offsets,
# and those are ALIASES: a second name for the object already called
# data_ov002_0207ef80, at the same address and the same size. Matching them too gave two
# symbols one address, so the generators wrote two files covering the same bytes and the
# delink refused with "overlaps with previous file". Leaving them without an address is
# what keeps them out, and costs nothing, because the object they name is already indexed.
ADDR_RE = re.compile(r"_(?P<addr>0[0-9a-fA-F]{7})$")


def module_of(basename):
    match = MODULE_RE.match(basename)
    return match.group("unit") if match else basename


def address_of(name):
    match = ADDR_RE.search(name)
    return int(match.group("addr"), 16) if match else None


def load_symbol_addresses():
    """symbol -> address, so a reloc disagreement can be judged by target, not spelling."""
    out = {}
    for dirpath, _dirs, files in os.walk(os.path.join(ROOT, "config")):
        if "symbols.txt" not in files:
            continue
        path = os.path.join(dirpath, "symbols.txt")
        with open(path, encoding="utf-8", errors="replace") as fh:
            for line in fh:
                parts = line.split()
                if len(parts) < 2:
                    continue
                for token in parts[1:]:
                    if token.startswith("addr:"):
                        try:
                            out[parts[0]] = int(token[5:], 16)
                        except ValueError:
                            pass
                        break
    return out


SYM_ADDR = load_symbol_addresses()


def reloc_targets(relocs):
    """Relocations as (offset, resolved address), so aliases at one address compare equal."""
    return tuple((off, SYM_ADDR.get(sym, sym)) for off, sym in relocs)


def resolve(bucket):
    """Pick one variant of a symbol. Returns (entry, conflict).

    The freshest object wins, NOT the majority. build/delinks accumulates objects
    from earlier runs -- gap numbering shifts as functions get matched, so an old
    _dsd_gap@main_281.o survives beside the current _dsd_gap@main_282.o and still
    carries whatever the config said back then. Counting heads let 37 stale objects
    outvote the one dsd had just written, and reported a phantom relocation in the
    sine table as if the delink genuinely disagreed with itself.

    conflict is False when the objects agree, True when an older object was
    overruled, and the ranked variants when equally fresh objects disagree -- only
    that last case marks the entry ambiguous, because then there is no single target
    to verify a reconstruction against.
    """
    ranked = sorted(bucket.values(), key=lambda item: (-item[2], -item[1]))
    entry = ranked[0][0]
    if len(ranked) == 1:
        return entry, False
    newest = ranked[0][2]
    if any(item[2] >= newest for item in ranked[1:]):
        variants = [
            {"count": item[1], "relocs": item[0]["relocs"]} for item in ranked
        ]
        return dict(entry, ambiguous=variants), variants
    return entry, True


def collect(o_path, variants):
    # Imported here, not at module scope: the pure-logic helpers above are unit-tested
    # in CI, which has no third-party packages installed.
    from elftools.elf.elffile import ELFFile

    try:
        elf = ELFFile(open(o_path, "rb"))
    except Exception:
        return
    module = module_of(os.path.splitext(os.path.basename(o_path))[0])

    sections = {}
    for i, section in enumerate(elf.iter_sections()):
        if section.name in DATA_SECTIONS and section["sh_size"]:
            sections[i] = (section.name, section.data())
    if not sections:
        return

    symtab = elf.get_section_by_name(".symtab")
    if symtab is None:
        return

    # offset -> (symbol, addend) per data section, so a symbol can claim the
    # relocations that fall inside its own range.
    relocs = {}
    for section in elf.iter_sections():
        if not section.name.startswith((".rel.", ".rela.")):
            continue
        target = "." + section.name.split(".", 2)[-1]
        if target not in DATA_SECTIONS:
            continue
        table = {}
        for rel in section.iter_relocations():
            sym = symtab.get_symbol(rel["r_info_sym"]).name
            table[rel["r_offset"]] = (sym, rel.entry.get("r_addend", 0))
        relocs[target] = table

    for sym in symtab.iter_symbols():
        if not sym.name or sym["st_shndx"] in ("SHN_UNDEF", "SHN_ABS"):
            continue
        try:
            shndx = int(sym["st_shndx"])
        except (TypeError, ValueError):
            continue
        if shndx not in sections or not sym["st_size"]:
            continue
        sec_name, blob = sections[shndx]
        start = sym["st_value"]
        end = start + sym["st_size"]
        if end > len(blob):
            continue

        own = {
            off - start: pair
            for off, pair in relocs.get(sec_name, {}).items()
            if start <= off < end
        }
        entry = {
            "hex": blob[start:end].hex(),
            "size": sym["st_size"],
            "section": sec_name.lstrip("."),
            "module": module,
            "addr": address_of(sym.name),
            "relocs": sorted((off, pair[0]) for off, pair in own.items()),
            "addends": {str(off): pair[1] for off, pair in sorted(own.items())},
        }
        key = (entry["hex"], reloc_targets(entry["relocs"]))
        bucket = variants.setdefault(sym.name, {})
        stamp = os.path.getmtime(o_path)
        if key in bucket:
            bucket[key][1] += 1
            bucket[key][2] = max(bucket[key][2], stamp)
        else:
            bucket[key] = [entry, 1, stamp]


def main():
    index = {}
    if os.path.exists(INDEX_PATH):
        with open(INDEX_PATH) as fh:
            index = json.load(fh)
        print("existing index: %d symbols (merged, never overwritten)" % len(index))

    before = len(index)
    variants = {}
    for o_path in sorted(glob.glob(os.path.join(DELINK, "*.o"))):
        collect(o_path, variants)

    superseded = 0
    ambiguous = 0
    for name, bucket in variants.items():
        entry, conflict = resolve(bucket)
        if conflict is True:
            superseded += 1
        elif conflict:
            ambiguous += 1
            print("AMBIGUOUS %s (%s): %s" % (
                name, entry["module"],
                " vs ".join(str(item["relocs"]) for item in conflict)[:160]))
        index[name] = entry
    if superseded:
        print("%d symbols read from the freshest object over an older one" % superseded)
    if ambiguous:
        print("%d symbols left ambiguous and cannot be verified" % ambiguous)

    with open(INDEX_PATH, "w") as fh:
        json.dump(index, fh)

    total = sum(entry["size"] for entry in index.values())
    by_section = {}
    for entry in index.values():
        by_section[entry["section"]] = by_section.get(entry["section"], 0) + entry["size"]
    print("indexed %d data symbols (+%d new), %d bytes" % (len(index), len(index) - before, total))
    for section in sorted(by_section):
        print("  %-8s %d bytes" % (section, by_section[section]))


if __name__ == "__main__":
    main()
