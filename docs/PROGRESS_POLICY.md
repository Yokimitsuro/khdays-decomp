# Progress policy

This project separates progress into several categories so contributors and
external trackers can see what has actually been decompiled into C.

## Real C decompilation

A function counts as real C decompilation only when it is implemented in C and
passes byte-exact verification against the original code.

## ASM stubs

ASM stubs, inline ASM, or placeholder assembly may be used temporarily while the
project is being bootstrapped.

These functions may match the original bytes, but they do not count as
C-decompiled progress.

## SDK identification

SDK/library functions identified through byte matching are useful for naming and
understanding the binary, but they are tracked separately from game-code
decompilation.

## Named-only functions

A function may have a known or provisional name before it has a real C
implementation. Names are useful for research, but they do not count as
C-decompiled progress.

## Initialized DATA

The public report inventories initialized `.rodata`, `.ctor`, and `.data`
section bytes from the checked-in module maps. BSS is excluded because it has
no stored ROM bytes. DATA begins at 0% and advances only after byte and
relocation verification; symbol names, extraction, `incbin`, embedded opcodes,
or preserving an original binary blob do not count as reconstruction.

`tools/index_data.py` builds the ground truth from the delinked objects and
`tools/verify_data.py` proves one reconstructed symbol against it, masking
relocated words and then comparing relocations by resolved target address so
that two spellings of one address agree and two addresses do not. A symbol whose
delinked objects disagree about their relocation targets is reported ambiguous
and refused rather than certified. Verified symbols leave a receipt, and the
report re-runs every receipt instead of trusting it, so an edited or deleted
source stops counting by itself. Bytes are attributed per module as well as per
address, because overlays are loaded over one another and share addresses.

A checkout without a delinked build has nothing to verify against, so it
honestly reports zero matched DATA bytes.

Verified DATA also enters the build. `gen_delinks.py` turns receipts into
`.rodata`/`.data` ranges on the owning source file, merging adjacent symbols
into one range and re-checking the source digest first, so an edited file drops
back out of the link instead of poisoning it. A source therefore has to own a
contiguous run and define its symbols in address order, because the linker
places one section image at the declared start.

Payloads stored in a data section but executed at runtime are classified
separately. In particular, ov024's `0x659c`-byte MobiClip decoder payload is
reported as `MobiClip executable payload` until its internal code and constant
tables are carved and verified. Keeping the payload visible in the denominator
does not claim that it is ordinary game DATA or decompiled source.

## Why this matters

The goal is to keep progress reporting honest and useful for contributors and
external project trackers such as decomp.dev. Byte-exact matching remains the
technical verification gate, but public C progress only counts real C
implementations.

## decomp.dev matching coverage

The primary `YKGP_report` artifact reports byte-exact matching coverage, not
pure-C completion. In addition to real C it includes only the sources listed in
`config/arm9/report_asm_matches.json`: the individually authorized CLZ exceptions
and the verified canonical SDK assembly completing ITCM. This is not permission
to count other game stubs, inline assembly, or SDK identifications as complete.

Each entry records its source hash, target hash, mode, and verified size. Source
hashes normalize line endings so Windows and CI agree. Changes invalidate the
attestation and stop report generation until `python tools/verify_report_asm.py`
passes byte and relocation verification again. Adding a game entry also requires
the explicit single-CLZ authorization in `config/arm9/asm_exceptions.json`.

Thus ov002, ov003, and ITCM can report 100% matching while the unchanged C audit reports
1477/1478, 27/28, and 129/154 real-C functions respectively. `PROGRESS.md`, `README.md`,
and `build/report_c.json` continue to exclude every ASM source from real C.
The workflow uploads `report_c.json` with `YKGP_progress_audit` for comparison.
Both reports use the same DATA inventory; their difference remains exclusively
the treatment of verified non-C code.
