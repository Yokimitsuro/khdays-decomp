#!/usr/bin/env python3
"""Patch .text section sh_addralign from 4 to 2 in every .o under
build/src/ and build/delinks/. Working theory: mwld pads per-file
.o inputs to their sh_addralign, which forces THUMB functions
starting at 2-aligned-but-not-4-aligned offsets to shift, breaking
byte-exact reproduction of the original layout.
"""
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def patch_o(path):
    data = bytearray(path.read_bytes())
    # Parse ELF32 header
    if data[:4] != b"\x7fELF" or data[4] != 1:
        return False
    e_shoff = struct.unpack_from("<I", data, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", data, 0x2e)[0]
    e_shnum = struct.unpack_from("<H", data, 0x30)[0]
    e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]
    # Section header string table
    strtab_off = e_shoff + e_shstrndx * e_shentsize
    strtab_start = struct.unpack_from("<I", data, strtab_off + 0x10)[0]
    changed = False
    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_name_off = struct.unpack_from("<I", data, sh_off)[0]
        # read null-terminated name
        end = data.index(b"\x00", strtab_start + sh_name_off)
        name = data[strtab_start + sh_name_off:end].decode()
        if name == ".text":
            # sh_addralign at offset 0x20 in section header
            align = struct.unpack_from("<I", data, sh_off + 0x20)[0]
            if align == 4:
                struct.pack_into("<I", data, sh_off + 0x20, 2)
                changed = True
    if changed:
        path.write_bytes(data)
    return changed


def main():
    n = 0
    build = ROOT / "build"
    # Walk every .o under build/ except build/build/ (final linker output).
    for p in build.rglob("*.o"):
        if p.parts[len(build.parts):len(build.parts) + 1] == ("build",):
            continue
        if patch_o(p):
            n += 1
    print(f"patched sh_addralign 4 -> 2 in {n} .o files")


if __name__ == "__main__":
    main()
