#!/usr/bin/env python3
"""Verify a reconstructed initialized-DATA symbol byte-for-byte against the ROM.

The DATA counterpart of verify_idx.py. Ground truth is build/data_index.json, built
by tools/index_data.py from the delinked objects. Relocated words are masked on both
sides and the relocations are then compared by resolved target address, so two
spellings of one address agree and two different addresses do not.

    python tools/verify_data.py <source.c> <symbol> [--receipt]

A verified symbol may be written to build/data_receipts/<symbol>.json with --receipt.
That receipt is the only thing allowed to advance DATA progress: there is no manual
matched flag, and a receipt records the exact range, section, size and the digest of
the source that produced it, so it can be re-checked rather than trusted.
"""
import hashlib
import json
import os
import sys
from datetime import datetime, timezone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX_PATH = os.path.join(ROOT, "build", "data_index.json")
RECEIPTS = os.path.join(ROOT, "build", "data_receipts")
DATA_SECTIONS = (".rodata", ".data", ".ctor")


def load_symbol_addresses():
    out = {}
    for dirpath, _dirs, files in os.walk(os.path.join(ROOT, "config")):
        if "symbols.txt" not in files:
            continue
        with open(os.path.join(dirpath, "symbols.txt"), encoding="utf-8", errors="replace") as fh:
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


def extract(o_path, name):
    """Bytes, section and own relocations of one data symbol in a compiled object."""
    # Local import so the module can be imported without pyelftools; CI runs the
    # unit tests with a bare interpreter.
    from elftools.elf.elffile import ELFFile

    elf = ELFFile(open(o_path, "rb"))
    sections = {}
    for i, section in enumerate(elf.iter_sections()):
        if section.name in DATA_SECTIONS and section["sh_size"]:
            sections[i] = (section.name, section.data())
    symtab = elf.get_section_by_name(".symtab")
    if symtab is None:
        return None

    relocs = {}
    for section in elf.iter_sections():
        if not section.name.startswith((".rel.", ".rela.")):
            continue
        target = "." + section.name.split(".", 2)[-1]
        if target not in DATA_SECTIONS:
            continue
        relocs[target] = {
            rel["r_offset"]: (
                symtab.get_symbol(rel["r_info_sym"]).name,
                rel.entry.get("r_addend", 0),
                rel["r_info_type"],
            )
            for rel in section.iter_relocations()
        }

    for sym in symtab.iter_symbols():
        if sym.name != name:
            continue
        try:
            shndx = int(sym["st_shndx"])
        except (TypeError, ValueError):
            continue
        if shndx not in sections:
            continue
        sec_name, blob = sections[shndx]
        start = sym["st_value"]
        end = start + sym["st_size"]
        own = {
            off - start: triple
            for off, triple in relocs.get(sec_name, {}).items()
            if start <= off < end
        }
        return blob[start:end], sec_name.lstrip("."), own
    return None


def target_of(name, addend):
    base = SYM_ADDR.get(name)
    return None if base is None else base + addend


REFUSED = "refused"
DIFFERS = "differs"
MATCH = "match"


def _repo_path(path):
    """Repo-relative when the source lives in the tree, absolute when it does not
    (a scratch file on another drive has no relative path on Windows)."""
    try:
        return os.path.relpath(path, ROOT).replace("\\", "/")
    except ValueError:
        return os.path.abspath(path).replace("\\", "/")


_COMPILED = {}


def compiled(cpath):
    """Compile once per file per process. A file of 48 string symbols would otherwise
    pay 48 mwcc runs to prove the same object."""
    from match import compile_c

    key = os.path.abspath(cpath)
    if key not in _COMPILED:
        _COMPILED[key] = compile_c(cpath)
    return _COMPILED[key]


def symbols_in(cpath):
    """Every initialized-data symbol the file defines, in address order where known."""
    from elftools.elf.elffile import ELFFile

    elf = ELFFile(open(compiled(cpath), "rb"))
    sections = {
        i for i, s in enumerate(elf.iter_sections())
        if s.name in DATA_SECTIONS and s["sh_size"]
    }
    symtab = elf.get_section_by_name(".symtab")
    out = []
    for sym in symtab.iter_symbols():
        if not sym.name or not sym["st_size"]:
            continue
        try:
            if int(sym["st_shndx"]) in sections:
                out.append(sym.name)
        except (TypeError, ValueError):
            continue
    return sorted(set(out))


def load_index():
    with open(INDEX_PATH) as fh:
        return json.load(fh)


def verify(cpath, name, index):
    """(status, message, info) for one reconstructed data symbol.

    Importable so the progress report can re-run the proof instead of trusting a
    receipt: a receipt records what was verified, never that it may be counted.
    """
    if name not in index:
        return REFUSED, "not in data_index: " + name, {}
    entry = index[name]
    if entry.get("ambiguous"):
        return (REFUSED,
                "%s is ambiguous in the delink: the objects disagree about its relocation "
                "targets, so there is no single target to verify against" % name,
                {})

    original = bytes.fromhex(entry["hex"])
    orig_relocs = {off: sym for off, sym in entry["relocs"]}
    orig_addends = {int(k): v for k, v in entry.get("addends", {}).items()}

    found = extract(compiled(cpath), name)
    if found is None:
        return DIFFERS, "%s is not defined in any initialized-data section of %s" % (
            name, os.path.basename(cpath)), {}
    mine, section, my_relocs = found

    if section != entry["section"]:
        return DIFFERS, "section %s != %s (const-ness of the reconstruction is wrong)" % (
            section, entry["section"]), {}
    if len(mine) != len(original):
        return DIFFERS, "size %d != %d" % (len(mine), len(original)), {}

    size = len(original)
    a = bytearray(mine)
    b = bytearray(original)
    for off in set(my_relocs) | set(orig_relocs):
        for k in range(4):
            if 0 <= off + k < size:
                a[off + k] = 0
                b[off + k] = 0
    if a != b:
        first = next(i for i in range(size) if a[i] != b[i])
        return DIFFERS, "byte diff @0x%X of %d (relocated words masked): got %02x want %02x" % (
            first, size, mine[first], original[first]), {}

    if set(my_relocs) != set(orig_relocs):
        return DIFFERS, "relocation offsets differ\n  mine=%s\n  rom =%s" % (
            sorted(my_relocs), sorted(orig_relocs)), {}
    for off in sorted(my_relocs):
        sym, addend, _typ = my_relocs[off]
        want_sym = orig_relocs[off]
        if sym == want_sym and addend == orig_addends.get(off, 0):
            continue
        mine_target = target_of(sym, addend)
        rom_target = target_of(want_sym, orig_addends.get(off, 0))
        if mine_target is None or rom_target is None or mine_target != rom_target:
            return DIFFERS, "reloc @0x%X points at %s%+d, ROM wants %s%+d" % (
                off, sym, addend, want_sym, orig_addends.get(off, 0)), {}

    addr = entry.get("addr")
    where = ("0x%08x-0x%08x" % (addr, addr + size)) if addr is not None else "address unknown"
    info = {
        "module": entry["module"],
        "section": entry["section"],
        "start": addr,
        "end": None if addr is None else addr + size,
        "size": size,
        "relocs": len(orig_relocs),
    }
    return MATCH, "%s %d bytes, %d relocs, .%s, %s" % (
        name, size, len(orig_relocs), section, where), info


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if len(args) != 2:
        raise SystemExit(__doc__)
    cpath, name = args
    write_receipt = "--receipt" in sys.argv

    status, message, info = verify(cpath, name, load_index())
    if status == REFUSED:
        print(">>> REFUSED <<< " + message)
        sys.exit(2)
    if status == DIFFERS:
        print(">>> DIFIERE <<< " + message)
        sys.exit(1)
    print(">>> MATCH <<< " + message)

    if write_receipt:
        os.makedirs(RECEIPTS, exist_ok=True)
        digest = hashlib.sha256(open(cpath, "rb").read()).hexdigest()
        receipt = {
            "schema_version": 1,
            "symbol": name,
            "source": _repo_path(cpath),
            "source_sha256": digest,
            "verified_at": datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds"),
        }
        receipt.update(info)
        path = os.path.join(RECEIPTS, name + ".json")
        with open(path, "w") as fh:
            json.dump(receipt, fh, indent=2)
        print("receipt: %s" % os.path.relpath(path, ROOT).replace("\\", "/"))
    sys.exit(0)


if __name__ == "__main__":
    main()
