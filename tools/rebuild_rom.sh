#!/usr/bin/env bash
# Rebuilds the ROM from the dsd config and compares against the reference dump.
#
# Expected behaviour: 4 bytes differ at offsets 0x6C/0x6D (secure-area CRC) and
# 0x15E/0x15F (header CRC). The DS firmware computes these from the actual
# image content and they're non-functional — the rebuilt ROM boots and plays
# identically. Anything more than 4 bytes of diff means something is broken
# in the build pipeline.
set -e
cd "$(dirname "$0")/.."

tools/dsd.exe rom build --config dsd_extract/config.yaml --rom built.nds

orig_sha=$(sha1sum days.nds | awk '{print $1}')
built_sha=$(sha1sum built.nds | awk '{print $1}')
echo
echo "Original SHA-1: $orig_sha"
echo "Rebuilt  SHA-1: $built_sha"

diff_bytes=$(cmp -l days.nds built.nds 2>/dev/null | wc -l || true)
echo "Bytes differing: $diff_bytes"
echo
if [ "$diff_bytes" -le 4 ]; then
    echo "OK: round-trip clean (<=4 CRC bytes is expected)."
    cmp -l days.nds built.nds 2>/dev/null | awk '{printf "  diff @ 0x%X\n", $1 - 1}'
else
    echo "FAIL: more than 4 bytes differ — something is broken in the build pipeline."
    cmp -l days.nds built.nds 2>/dev/null | head -10 | awk '{printf "  diff @ 0x%X (orig=0x%s built=0x%s)\n", $1 - 1, $2, $3}'
    exit 1
fi
