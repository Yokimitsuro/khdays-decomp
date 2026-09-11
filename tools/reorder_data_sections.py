#!/usr/bin/env python3
"""Put a compiled object's initialized-data sections in ROM address order.

    python tools/reorder_data_sections.py <object.o> [more.o ...]

Why this exists (issue #6, 2026-09-11)
--------------------------------------
mwccarm emits every global data definition as its own `.rodata`/`.data`
section and orders those sections by its own rule, not by source order. dsd's
linker script names an object once per section name, `foo.o(.data)`, and mwld
lays every input section of that name down in section-header order, so a file
that defines several globals lands scrambled inside the range it claims.
Measured on this tree: 350 of 410 multi-global data objects come out of address
order, and no permutation of the source produces the ROM order when the sizes
are not monotone in address order, which is the common case. gen_delinks.py
assumes "a source owns a contiguous run and defines its symbols in address
order"; tools/_run_mwcc.py calls reorder() after every compile, which makes
that assumption true by construction.

Where the address of each symbol comes from, in this order:

  1. the module's committed config/**/symbols.txt (canonical, in git);
  2. the address embedded in a data_ADDR / data_ovNNN_ADDR name;
  3. build/data_receipts/<sym>.json, the verification receipt (git-ignored).

A section whose symbols cannot all be placed is left as emitted and reported.

What it does
------------
Section headers of the same name are permuted so their order follows the
symbols' addresses; inside a section holding several symbols the symbol
chunks are moved so each sits at (its address - the section's lowest address).
The file keeps its size: headers, st_shndx/st_value and r_offset/r_addend are
patched in place. An object that needs no change is not rewritten.

Written by iwngymn for issue #6; the address lookup was widened here so a
fresh clone without receipts still gets correct data layout.
"""
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RECEIPTS = ROOT / "build" / "data_receipts"
CONFIG = ROOT / "config" / "arm9"
DATA_SECTIONS = {".rodata", ".data", ".ctor"}

SHT_PROGBITS, SHT_SYMTAB, SHT_RELA, SHT_REL = 1, 2, 4, 9
STT_SECTION, STT_FILE = 3, 4
SHN_LORESERVE = 0xFF00
SHDR = struct.Struct("<IIIIIIIIII")   # name type flags addr offset size link info align entsize
SYM = struct.Struct("<IIIBBH")        # name value size info other shndx

NAME_ADDR = re.compile(r"^data_(?:ov\d{3}_)?([0-9a-f]{8})(?:_\w+)?$")
SYM_LINE = re.compile(r"^(\S+)\s+kind:\S+.*?\baddr:0x([0-9a-fA-F]+)")

_symbols_cache = {}


def module_of(path):
    """Owning module of an object, from its path: an overlay, or main."""
    m = re.search(r"[\\/]overlays[\\/](ov\d{3})[\\/]", str(path))
    return m.group(1) if m else "main"


def symbols_of(module):
    """name -> address for one module's committed symbols.txt (cached per process)."""
    if module in _symbols_cache:
        return _symbols_cache[module]
    files = ([CONFIG / "overlays" / module / "symbols.txt"] if module != "main"
             else [CONFIG / "symbols.txt", CONFIG / "itcm" / "symbols.txt", CONFIG / "dtcm" / "symbols.txt"])
    table = {}
    for f in files:
        if not f.is_file():
            continue
        for ln in f.open(encoding="utf-8", errors="ignore"):
            m = SYM_LINE.match(ln)
            if m:
                table[m.group(1)] = int(m.group(2), 16)
    _symbols_cache[module] = table
    return table


def receipt_addr(name):
    p = RECEIPTS / (name + ".json")
    if not p.is_file():
        return None
    try:
        return json.loads(p.read_text(encoding="utf-8")).get("start")
    except (OSError, ValueError):
        return None


def address_of(name, module):
    addr = symbols_of(module).get(name)
    if addr is not None:
        return addr
    m = NAME_ADDR.match(name)
    if m:
        return int(m.group(1), 16)
    return receipt_addr(name)


def merge_interleaved(buf, shdrs, names, syms, by_sec, path, log):
    """Merge same-named data sections whose address ranges interleave.

    Returns (buf, shdrs, syms) with the merge applied, or None when nothing
    interleaves. The first section of each merged group receives one blob laid
    out by address, appended at the end of the file; the others keep their
    headers with size 0. Symbols move to the first section at (addr - base);
    relocations into any merged section are retargeted and their offsets, and
    section-symbol addends, remapped. Only groups whose symbols tile their run
    exactly, with no gap and no overlap, are merged; anything else is reported
    and left as emitted."""
    groups = {}
    for idx, entries in by_sec.items():
        groups.setdefault(names[idx], []).append(idx)
    plan = {}                                       # first idx -> (members, base, span, chunks)
    for name, members in groups.items():
        if len(members) < 2:
            continue
        ranges = []
        for idx in members:
            if any(a is None for _, a in by_sec[idx]):
                ranges = None
                break
            lo = min(a for _, a in by_sec[idx])
            hi = max(a + s[2] for s, a in by_sec[idx])
            ranges.append((lo, hi, idx))
        if not ranges:
            continue
        ranges.sort()
        # Merging is not only for interleaved pools. mwld aligns every input
        # section to the lcf's ALIGNALL(2), which THUMB code needs, so a one-byte
        # global at an odd address followed by another section gets a padding
        # byte the ROM does not have (ov008_tables_0208ee84: two bytes of drift).
        # The delinked original is one section per name, so one merged section
        # is the faithful shape whenever the symbols tile a single run.
        chunks = sorted((a, s[2], idx, s) for idx in members for s, a in by_sec[idx])
        base = chunks[0][0]
        span = max(a + sz for a, sz, _, _ in chunks) - base
        tiled = sum(sz for _, sz, _, _ in chunks) == span and all(
            chunks[i][0] + chunks[i][1] == chunks[i + 1][0] for i in range(len(chunks) - 1))
        total = sum(shdrs[idx][5] for idx in members)
        if not tiled or total != span:
            interleaved = any(ranges[i + 1][0] < ranges[i][1] for i in range(len(ranges) - 1))
            if interleaved:
                print(f"reorder_data_sections: {path.name}: {name} sections interleave but their "
                      f"symbols do not tile one run (span {span}, sections {total}); left as emitted",
                      file=log)
            continue
        plan[min(members)] = (sorted(members), base, span, chunks)
    if not plan:
        return None

    buf = bytearray(buf)
    shdrs = [list(h) for h in shdrs]
    syms = [list(s) for s in syms]
    sec_sym = {}                                    # section idx -> its STT_SECTION symbol index
    for n, s in enumerate(syms):
        if (s[3] & 0xF) == STT_SECTION and s[5] not in sec_sym:
            sec_sym[s[5]] = n
    for first, (members, base, span, chunks) in plan.items():
        # old (section, offset) -> new offset in the merged section, per chunk
        remap = {}                                  # idx -> [(old_off, new_off, size)]
        blob = bytearray(span)
        for a, sz, idx, s in chunks:
            off = shdrs[idx][4] + s[1]
            blob[a - base:a - base + sz] = buf[off:off + sz]
            remap.setdefault(idx, []).append((s[1], a - base, sz))
        # append the blob and point the first section at it
        while len(buf) % 4:
            buf.append(0)
        new_off = len(buf)
        buf += blob
        shdrs[first][4] = new_off
        shdrs[first][5] = span
        for idx in members:
            if idx != first:
                shdrs[idx][5] = 0

        def moved(idx, o):
            for old, new, sz in remap.get(idx, ()):
                if old <= o < old + sz:
                    return o - old + new
            raise ValueError(f"{path.name}: offset 0x{o:x} of section {idx} is outside every symbol")

        for s in syms:
            if s[5] in members and (s[3] & 0xF) not in (STT_SECTION, STT_FILE):
                s[1] = moved(s[5], s[1])
                s[5] = first
        first_secsym = sec_sym.get(first)
        for h in shdrs:
            if h[1] not in (SHT_REL, SHT_RELA) or h[7] not in members:
                continue
            ent = 12 if h[1] == SHT_RELA else 8
            target = h[7]
            for off in range(h[4], h[4] + h[5], ent):
                r_offset, r_info = struct.unpack_from("<II", buf, off)
                struct.pack_into("<I", buf, off, moved(target, r_offset))
            h[7] = first
        for h in shdrs:
            if h[1] != SHT_RELA:
                continue
            for off in range(h[4], h[4] + h[5], 12):
                r_offset, r_info = struct.unpack_from("<II", buf, off)
                sym = syms[r_info >> 8]
                if (sym[3] & 0xF) == STT_SECTION and sym[5] in members and sym[5] != first:
                    r_addend, = struct.unpack_from("<i", buf, off + 8)
                    r_addend = moved(sym[5], r_addend)
                    if first_secsym is None:
                        raise ValueError(f"{path.name}: no section symbol for merged section {first}")
                    struct.pack_into("<I", buf, off + 4, (first_secsym << 8) | (r_info & 0xFF))
                    struct.pack_into("<i", buf, off + 8, r_addend)
                elif (sym[3] & 0xF) == STT_SECTION and sym[5] == first:
                    r_addend, = struct.unpack_from("<i", buf, off + 8)
                    struct.pack_into("<i", buf, off + 8, moved(first, r_addend))
    return buf, shdrs, syms


def reorder(path, log=sys.stderr):
    """Rewrite `path` in place. Returns the number of sections changed."""
    path = Path(path)
    buf = bytearray(path.read_bytes())
    if buf[:5] != b"\x7fELF\x01" or buf[5] != 1:
        return 0                                    # not ELF32 little-endian
    e_shoff, = struct.unpack_from("<I", buf, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", buf, 0x2E)
    if e_shentsize != SHDR.size or not e_shnum:
        return 0
    shdrs = [list(SHDR.unpack_from(buf, e_shoff + i * SHDR.size)) for i in range(e_shnum)]
    shstr = shdrs[e_shstrndx]

    def cstr(tab, off):
        end = buf.index(b"\0", tab[4] + off)
        return buf[tab[4] + off:end].decode("ascii", "replace")

    names = [cstr(shstr, h[0]) for h in shdrs]
    symtab_idx = next((i for i, h in enumerate(shdrs) if h[1] == SHT_SYMTAB), None)
    if symtab_idx is None:
        return 0
    symtab = shdrs[symtab_idx]
    strtab = shdrs[symtab[6]]
    nsyms = symtab[5] // SYM.size
    syms = [list(SYM.unpack_from(buf, symtab[4] + i * SYM.size)) for i in range(nsyms)]
    module = module_of(path)

    # Address of every named data symbol, grouped by section.
    by_sec = {}
    for s in syms:
        stype = s[3] & 0xF
        if stype in (STT_SECTION, STT_FILE) or s[5] == 0 or s[5] >= SHN_LORESERVE:
            continue
        if names[s[5]] not in DATA_SECTIONS or shdrs[s[5]][1] != SHT_PROGBITS:
            continue
        by_sec.setdefault(s[5], []).append((s, address_of(cstr(strtab, s[0]), module)))

    changed = 0

    # 0. Interleaved pools. mwcc pools same-typed globals into one section, and
    #    two pools of one file can interleave in address space (ov002's gauge
    #    tables: eleven u16 arrays in one .rodata, nine u32 arrays in another,
    #    alternating in the ROM). No order of whole sections reproduces that,
    #    so when a name's sections interleave and their symbols tile one run
    #    exactly, they are merged into a single section laid out by address.
    merged = merge_interleaved(buf, shdrs, names, syms, by_sec, path, log)
    if merged:
        buf, shdrs, syms = merged
        changed += 1
        # Rebuild the per-section view over the merged layout.
        by_sec = {}
        for s in syms:
            stype = s[3] & 0xF
            if stype in (STT_SECTION, STT_FILE) or s[5] == 0 or s[5] >= SHN_LORESERVE:
                continue
            if names[s[5]] not in DATA_SECTIONS or shdrs[s[5]][1] != SHT_PROGBITS:
                continue
            by_sec.setdefault(s[5], []).append((s, address_of(cstr(strtab, s[0]), module)))

    # 1. Symbol order inside a section that holds several symbols.
    moves = {}                                      # sec index -> [(old, new, size)]
    for idx, entries in by_sec.items():
        if len(entries) < 2:
            continue
        if any(addr is None for _, addr in entries):
            print(f"reorder_data_sections: {path.name}: section {idx} {names[idx]} has "
                  f"symbols with no known address; left as emitted", file=log)
            continue
        base = min(addr for _, addr in entries)
        size = shdrs[idx][5]
        chunks = sorted((addr - base, s[1], s[2]) for s, addr in entries)
        ok = all(new + sz <= size for new, _, sz in chunks) and all(
            chunks[i][0] + chunks[i][2] <= chunks[i + 1][0] for i in range(len(chunks) - 1))
        if not ok:
            print(f"reorder_data_sections: {path.name}: section {idx} {names[idx]} addresses "
                  f"do not fit the section; left as emitted", file=log)
            continue
        if all(new == old for new, old, _ in chunks):
            continue
        off = shdrs[idx][4]
        old_data = bytes(buf[off:off + size])
        new_data = bytearray(size)
        for new, old, sz in chunks:
            new_data[new:new + sz] = old_data[old:old + sz]
        buf[off:off + size] = new_data
        moves[idx] = [(old, new, sz) for new, old, sz in chunks]
        changed += 1

    def remap_off(idx, o):
        for old, new, sz in moves.get(idx, ()):
            if old <= o < old + sz:
                return o - old + new
        raise ValueError(f"{path.name}: offset 0x{o:x} of section {idx} is outside every symbol")

    for s in syms:
        if s[5] in moves:
            s[1] = remap_off(s[5], s[1])

    # 2. Header order of same-named sections: placeable ones sorted by address,
    #    keeping their slots; the rest stay where they are.
    perm = list(range(e_shnum))                     # new index -> old index
    for name in DATA_SECTIONS:
        slots = [i for i in range(e_shnum) if names[i] == name
                 and i in by_sec and all(a is not None for _, a in by_sec[i])]
        order = sorted(slots, key=lambda i: min(a for _, a in by_sec[i]))
        for slot, old in zip(slots, order):
            perm[slot] = old
    old_to_new = {old: new for new, old in enumerate(perm)}
    if any(new != old for new, old in enumerate(perm)):
        changed += sum(1 for new, old in enumerate(perm) if new != old)

    # 3. Relocations: offsets follow their moved symbol chunk; a relocation
    #    against a section symbol carries the offset in its addend instead.
    for i, h in enumerate(shdrs):
        if h[1] not in (SHT_REL, SHT_RELA):
            continue
        target, ent = h[7], (12 if h[1] == SHT_RELA else 8)
        for off in range(h[4], h[4] + h[5], ent):
            r_offset, r_info = struct.unpack_from("<II", buf, off)
            if target in moves:
                r_offset = remap_off(target, r_offset)
            if h[1] == SHT_RELA:
                r_addend, = struct.unpack_from("<i", buf, off + 8)
                sym = syms[r_info >> 8]
                if (sym[3] & 0xF) == STT_SECTION and sym[5] in moves:
                    r_addend = remap_off(sym[5], r_addend)
                struct.pack_into("<i", buf, off + 8, r_addend)
            struct.pack_into("<I", buf, off, r_offset)

    if not changed:
        return 0

    # 4. Write back: symbols (with section indices renumbered), headers in the
    #    new order with link/info renumbered, and the string-table index.
    def renum(i):
        return old_to_new.get(i, i) if 0 < i < SHN_LORESERVE else i

    for n, s in enumerate(syms):
        s[5] = renum(s[5])
        SYM.pack_into(buf, symtab[4] + n * SYM.size, *s)
    for new, old in enumerate(perm):
        h = list(shdrs[old])
        if h[1] in (SHT_REL, SHT_RELA):
            h[7] = renum(h[7])
        if h[1] in (SHT_REL, SHT_RELA, SHT_SYMTAB) or h[6]:
            h[6] = renum(h[6])
        SHDR.pack_into(buf, e_shoff + new * SHDR.size, *h)
    struct.pack_into("<H", buf, 0x32, renum(e_shstrndx))
    path.write_bytes(bytes(buf))
    return changed


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    total = 0
    for arg in sys.argv[1:]:
        n = reorder(arg)
        total += n
        if n:
            print(f"{arg}: {n} section(s) reordered")
    print(f"{len(sys.argv) - 1} object(s), {total} section(s) reordered")
    return 0


if __name__ == "__main__":
    sys.exit(main())
