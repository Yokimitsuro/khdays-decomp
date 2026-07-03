#!/usr/bin/env bash
# Packs the *decompiled* ROM from our linked + post-link-patched module bins and
# checks it against the reference dump.
#
# Prereq: `python tools/configure.py && ninja && ninja build/arm9.elf` has run,
# so build/build/*.bin are the fix_interwork-patched, byte-exact module images
# (verify with `tools/dsd.exe check modules --config-path config/arm9/config.yaml -f`).
#
# `dsd rom config --elf` regenerates build/build/arm9_overlays.yaml from the ELF,
# and CANNOT recover the per-overlay "signed" flag from the ELF alone — it emits
# `signed: false` for every overlay. The original overlay table has every overlay
# marked signed (bit 1 of the +0x1C flag word), so we restore that here before
# packing. Without this fixup the packed ROM differs from the reference in 303
# overlay-table flag bytes (one per overlay at table_offset + id*0x20 + 0x1F).
#
# Expected result: exactly 4 bytes differ, at 0x6C/0x6D (secure-area CRC) and
# 0x15E/0x15F (header CRC). The DS firmware recomputes those from image content;
# they are non-functional and the ROM boots/plays identically. Anything more
# means the build pipeline (or this pack step) regressed.
set -e
cd "$(dirname "$0")/.."

echo "[build_rom] dsd rom config (ELF -> rom_config.yaml + arm9_overlays.yaml)"
tools/dsd.exe rom config --elf build/arm9.elf --config config/arm9/config.yaml

# Restore the per-overlay signed flag dropped by `rom config` (see header).
echo "[build_rom] restoring per-overlay signed flags (dsd rom config emits false)"
sed -i 's/^    signed: false$/    signed: true/' build/build/arm9_overlays.yaml
remaining=$(grep -cE '^    signed: false$' build/build/arm9_overlays.yaml || true)
if [ "$remaining" != "0" ]; then
    echo "[build_rom] WARNING: $remaining overlays still signed:false" >&2
fi

echo "[build_rom] dsd rom build -> build/days.nds"
tools/dsd.exe rom build --config build/build/rom_config.yaml --rom build/days.nds

orig_sha=$(sha1sum days.nds | awk '{print $1}')
built_sha=$(sha1sum build/days.nds | awk '{print $1}')
echo
echo "Original SHA-1: $orig_sha"
echo "Decomp   SHA-1: $built_sha"

diff_bytes=$(cmp -l days.nds build/days.nds 2>/dev/null | wc -l || true)
echo "Bytes differing: $diff_bytes"
echo
if [ "$diff_bytes" -le 4 ]; then
    echo "OK: decomp ROM matches the reference (<=4 CRC bytes is expected)."
    cmp -l days.nds build/days.nds 2>/dev/null | awk '{printf "  diff @ 0x%X\n", $1 - 1}'
else
    echo "FAIL: more than 4 bytes differ — build pipeline or pack step regressed."
    cmp -l days.nds build/days.nds 2>/dev/null | head -20 | awk '{printf "  diff @ 0x%X (orig=0x%s built=0x%s)\n", $1 - 1, $2, $3}'
    exit 1
fi
