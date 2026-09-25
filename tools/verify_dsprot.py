#!/usr/bin/env python3
"""Verify a DS Protect unit of ov028 against the ROM, encrypted ranges included.

The unit is built exactly as the build does it (tools/_run_mwcc.py: the library's own
compiler from config/arm9/file_compilers.json, then tools/dsprot_encode.py), and its code --
now in .rodata -- is compared word for word with the ROM image in build/data_index.json:

* words without a relocation must be identical (the encrypted ranges included);
* a relocated word must resolve to what the ROM holds: a pool word to the address of its
  symbol (+ addend), a `bl` to a branch whose target is the called symbol. The delinked ROM
  image only records relocations for pool words (dsd reads this region as data), so calls are
  checked by decoding the ROM's branch;
* every relocation the ROM image records must be one of ours.

    python tools/verify_dsprot.py <source.c> [--receipt]
"""

from __future__ import annotations

import hashlib
import json
import re
import subprocess
import sys
import tempfile
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
INDEX_PATH = ROOT / "build" / "data_index.json"
RECEIPTS = ROOT / "build" / "data_receipts"
COMPILERS = ROOT / "config" / "arm9" / "file_compilers.json"
MODULE = "ov028"

MATCH, DIFFERS, REFUSED = "match", "differs", "refused"
SYM_LINE = re.compile(r"^(\S+)\s+kind:\S+\s+addr:0x([0-9a-fA-F]+)")
R_ARM_ABS32, R_ARM_PC24, R_ARM_CALL, R_ARM_JUMP24 = 2, 1, 28, 29


def symbol_addresses() -> dict:
    table = {}
    cfg = ROOT / "config" / "arm9"
    for path in [cfg / "symbols.txt", cfg / "itcm" / "symbols.txt", cfg / "dtcm" / "symbols.txt",
                 cfg / "overlays" / MODULE / "symbols.txt"]:
        for line in path.read_text(encoding="utf-8", errors="ignore").splitlines():
            m = SYM_LINE.match(line)
            if m:
                table.setdefault(m.group(1), int(m.group(2), 16))
    return table


def build_object(source: Path, out: Path) -> None:
    rel = source.resolve().relative_to(ROOT).as_posix()
    compilers = json.loads(COMPILERS.read_text(encoding="utf-8"))
    cc = compilers.get(rel, "default")
    subprocess.run([sys.executable, str(ROOT / "tools" / "_run_mwcc.py"), str(out), str(source),
                    "--mode=arm", f"--cc={cc}"], check=True, capture_output=True, text=True)


def load_object(path: Path, addresses: dict):
    """(start, bytes, relocs{offset: (type, symbol, addend)}) of the unit's .rodata code."""
    import io
    from elftools.elf.elffile import ELFFile

    elf = ELFFile(io.BytesIO(path.read_bytes()))
    symtab = elf.get_section_by_name(".symtab")
    pieces = {}
    for sym in symtab.iter_symbols():
        if sym["st_info"]["type"] not in ("STT_FUNC", "STT_OBJECT") or not isinstance(sym["st_shndx"], int):
            continue
        section = elf.get_section(sym["st_shndx"])
        if section.name != ".rodata" or sym.name not in addresses:
            continue
        pieces.setdefault(sym["st_shndx"], []).append((addresses[sym.name] - sym["st_value"], sym.name))
    image = {}
    relocs = {}
    for index, bases in pieces.items():
        base = {b for b, _ in bases}
        if len(base) != 1:
            raise ValueError(f"symbols of one section disagree about its address: {bases}")
        base = base.pop()
        data = elf.get_section(index).data()
        for i, byte in enumerate(data):
            image[base + i] = byte
        for rel in elf.iter_sections():
            if not rel.name.startswith(".rel") or rel["sh_info"] != index:
                continue
            for r in rel.iter_relocations():
                sym = symtab.get_symbol(r["r_info_sym"])
                name = sym.name
                if sym["st_info"]["type"] == "STT_SECTION":
                    raise ValueError("section-relative relocation: name the target")
                addend = r["r_addend"] if r.is_RELA() else None
                relocs[base + r["r_offset"]] = (r["r_info_type"], name, addend)
    if not image:
        raise ValueError(f"{path.name}: no .rodata code with known addresses")
    start, end = min(image), max(image) + 1
    if len(image) != end - start:
        raise ValueError("the unit's sections do not tile one range")
    return start, bytes(image[a] for a in range(start, end)), relocs


def rom_image(start: int, end: int, index: dict):
    data = [None] * (end - start)
    relocs = {}
    for name, entry in index.items():
        addr = entry.get("addr")
        if entry.get("module") != MODULE or addr is None or entry.get("section") != "rodata":
            continue
        raw = bytes.fromhex(entry["hex"])
        if addr + len(raw) <= start or addr >= end:
            continue
        for i, byte in enumerate(raw):
            if start <= addr + i < end:
                data[addr + i - start] = byte
        for off, target in entry.get("relocs", []):
            if start <= addr + off < end:
                relocs[addr + off] = (target, int(entry.get("addends", {}).get(str(off), 0)))
    if any(b is None for b in data):
        raise ValueError(f"the DATA index does not cover 0x{start:08x}-0x{end:08x}")
    return bytes(data), relocs


def verify(source, index=None):
    source = Path(source)
    addresses = symbol_addresses()
    if index is None:
        index = json.loads(INDEX_PATH.read_text(encoding="utf-8"))
    try:
        with tempfile.TemporaryDirectory() as tmp:
            obj = Path(tmp) / (source.stem + ".o")
            build_object(source, obj)
            start, mine, relocs = load_object(obj, addresses)
    except (ValueError, subprocess.CalledProcessError) as exc:
        return REFUSED, f"build: {getattr(exc, 'stderr', '') or exc}", {}
    end = start + len(mine)
    try:
        rom, rom_relocs = rom_image(start, end, index)
    except ValueError as exc:
        return REFUSED, str(exc), {}
    for address in range(start, end, 4):
        o = address - start
        want = int.from_bytes(rom[o:o + 4], "little")
        got = int.from_bytes(mine[o:o + 4], "little")
        if address not in relocs:
            if got != want:
                return DIFFERS, f"word at 0x{address:08x}: 0x{got:08x} != ROM 0x{want:08x}", {}
            continue
        rtype, name, addend = relocs[address]
        target = addresses.get(name)
        if target is None:
            return REFUSED, f"relocation at 0x{address:08x} names {name}, which has no address", {}
        if rtype == R_ARM_ABS32:
            value = (target + (addend if addend is not None else got)) & 0xFFFFFFFF
            rom_value = want
            if address in rom_relocs:
                rom_target, rom_addend = rom_relocs[address]
                if rom_target not in addresses:
                    return REFUSED, f"ROM relocation target {rom_target} has no address", {}
                rom_value = (addresses[rom_target] + rom_addend) & 0xFFFFFFFF
            if value != rom_value:
                return DIFFERS, f"pool word at 0x{address:08x}: {name} -> 0x{value:08x}, ROM 0x{rom_value:08x}", {}
        elif rtype in (R_ARM_PC24, R_ARM_CALL, R_ARM_JUMP24):
            if (want >> 24) & 0x0F not in (0x0A, 0x0B) or (got >> 24) != (want >> 24):
                return DIFFERS, f"branch at 0x{address:08x}: 0x{got:08x} vs ROM 0x{want:08x}", {}
            offset = want & 0xFFFFFF
            offset = (offset - (1 << 24) if offset & 0x800000 else offset) << 2
            if (address + 8 + offset) & 0xFFFFFFFF != target:
                return DIFFERS, f"call at 0x{address:08x} reaches 0x{address + 8 + offset:08x}, not {name}", {}
        else:
            return REFUSED, f"unexpected relocation type {rtype} at 0x{address:08x}", {}
    missing = sorted(set(rom_relocs) - set(relocs))
    if missing:
        return DIFFERS, "ROM relocations the unit does not carry: " + ", ".join(f"0x{a:08x}" for a in missing), {}
    info = {"kind": "dsprot_encrypted_code", "module": MODULE, "section": "rodata",
            "start": start, "end": end, "size": end - start, "relocs": len(relocs)}
    return MATCH, (f"{source.name}: 0x{start:08x}-0x{end:08x} {end - start} bytes, "
                   f"{len(relocs)} relocations resolved, encrypted ranges exact"), info


def main() -> None:
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if len(args) != 1:
        raise SystemExit(__doc__)
    source = Path(args[0])
    status, message, info = verify(source)
    if status != MATCH:
        print((">>> REFUSED <<< " if status == REFUSED else ">>> DIFIERE <<< ") + message)
        raise SystemExit(2 if status == REFUSED else 1)
    print(">>> MATCH <<< " + message)
    if "--receipt" in sys.argv:
        RECEIPTS.mkdir(parents=True, exist_ok=True)
        receipt = dict(info)
        receipt.update({
            "schema_version": 1,
            "symbol": f"dsprot_{source.stem}",
            "source": source.resolve().relative_to(ROOT).as_posix(),
            "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
            "verified_at": datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds"),
        })
        path = RECEIPTS / f"dsprot_{source.stem}.json"
        path.write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8", newline="\n")
        print("receipt: " + path.relative_to(ROOT).as_posix())


if __name__ == "__main__":
    main()
