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

from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DELINK = os.path.join(ROOT, "build", "delinks")
INDEX_PATH = os.path.join(ROOT, "build", "data_index.json")

DATA_SECTIONS = (".rodata", ".data", ".ctor")
# _dsd_gap@ov006_10.o -> ov006, _dsd_gap@main_3.o -> main
MODULE_RE = re.compile(r"^_dsd_gap@(?P<unit>[^_]+(?:_[a-z]+)*?)_\d+$")
# data_ov006_0205630c / data_0204c058 -- the address is part of the name
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


def collect(o_path, variants):
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
        if key in bucket:
            bucket[key][1] += 1
        else:
            bucket[key] = [entry, 1]


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

    ambiguous = 0
    for name, bucket in variants.items():
        ranked = sorted(bucket.values(), key=lambda item: -item[1])
        entry = ranked[0][0]
        if len(ranked) > 1:
            # The objects of one module disagree about this symbol's content or about
            # where its relocations point, and the targets are genuinely different
            # addresses rather than two spellings of one. Keep the majority image but
            # refuse to certify it: a reconstruction cannot be proved against a target
            # the delink itself does not agree on.
            ambiguous += 1
            entry = dict(entry, ambiguous=[
                {"count": count, "relocs": item["relocs"]} for item, count in ranked
            ])
            print("AMBIGUOUS %s (%s): %s" % (
                name, entry["module"],
                " vs ".join(str(item["relocs"]) for item, _ in ranked)[:160]))
        index[name] = entry
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
