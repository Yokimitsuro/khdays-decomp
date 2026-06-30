# Contributing

Thanks for helping decompile *Kingdom Hearts 358/2 Days*! The workflow is simple:
pick a function, write code that compiles to the **exact same bytes** as the
original, and open a PR.

## The one rule: byte-exact

A function is only accepted when it passes byte-exact verification. The verifier
must print `>>> MATCH <<<`. This is the quality gate for merging matching work.

Byte-exact matching is not the same thing as public C decompilation progress.
Inline ASM stubs can match the original bytes, but they are not counted as real
C decompilation. See [docs/PROGRESS_POLICY.md](docs/PROGRESS_POLICY.md) for the
reporting policy.

## What counts as decompiled progress?

Only real C code that passes byte-exact verification counts as C-decompiled
progress.

Inline ASM, ASM stubs, `NON_MATCHING`, or placeholder code can be useful while
researching a function, but they must be labeled clearly and must not be counted
as real C decompilation.

SDK/library functions identified through byte matching are useful for naming and
understanding the binary, but they are tracked separately from game-code
decompilation.

When contributing a function, please specify whether it is:

- real C matched
- non-matching C
- inline ASM placeholder
- SDK/library identification
- symbol/name-only improvement

## Claiming work

Functions are grouped by **module/overlay** (`ov000`, `ov030`, ...). To avoid
duplicated effort, **claim a module before you start**:

1. Check [PROGRESS.md](PROGRESS.md) for a module that is not finished.
2. Open or comment on a GitHub issue titled e.g. `Claim: ov030` and assign
   yourself. Un-claim if you stop working on it.
3. Work through that module's `func_*` functions and PR them.

Collisions are harmless: byte-exact verification means only matching code is
merged, so nothing breaks if two people overlap. Claiming just saves wasted
effort. Use the project Discord / decomp.me for live coordination.

## Setup

You must provide your own legally-obtained copy of the game. Nothing
copyrighted is distributed here.

### Reference ROM

This project targets one specific ROM dump. If your `days.nds` does not match
these hashes, addresses will not line up and `dsd` extraction will produce a
different config.

| | |
|---|---|
| File | `days.nds` |
| Size | 268,435,456 bytes (256 MiB) |
| Region | EU (gamecode `YKGP`, maker `GD` = Square Enix) |
| SHA-1 | `6fae8f5bbe80114b4e2535260eab5f4d0fc8a844` |
| SHA-256 | `1ecf5e7a41a2ae48e7c5fd3f678e5a79e854d843f1a1fa3a952a41b14e51ec4f` |
| MD5 | `6eac99ad1f77920bdafbc71fd6418cc8` |

Verify with `sha1sum days.nds`. If your dump differs, this project is not
directly usable; addresses in `config/`, `func_index.json`, and committed source
were computed against the EU dump above.

1. **Python deps:** `pip install capstone pyelftools ndspy`
2. **`dsd`** (DS extraction/delinking): download from
   [AetiasHax/ds-decomp releases](https://github.com/AetiasHax/ds-decomp/releases)
   and place it at `tools/dsd.exe`.
3. **`mwccarm` 3.0 build 139** (CodeWarrior for Nintendo DS 2.0 SP2 compiler).
   Place the binaries under `tools/mwccarm/3.0_patch4/`.
4. **`arm-none-eabi-as`** (Arm GNU Toolchain / devkitARM) on PATH.
5. **Extract your ROM** with `dsd`:
   ```sh
   tools/dsd.exe rom extract --rom days.nds --output-path dsd_extract/
   tools/dsd.exe init --rom-config dsd_extract/config.yaml --output-path config/ \
       --build-path build/ --allow-unknown-function-calls
   tools/dsd.exe delink --config-path config/arm9/config.yaml
   tools/dsd.exe dis --config-path config/arm9/config.yaml --asm-path asm/
   ```
6. Generate the candidate lists: `python tools/find_candidates.py` and
   `python tools/find_calls.py`.

## Verifying the full ROM round-trip

To confirm your setup is complete and that the project as a whole still rebuilds
the original game, use:

```sh
bash tools/rebuild_rom.sh
```

Expected output is **4 bytes differ**: the secure-area CRC at `0x6C/0x6D` and
the header CRC at `0x15E/0x15F`. Anything more than 4 bytes means something is
broken in the extraction or build configuration.

## Decompiling a function

1. **Claim it** first so nobody duplicates the work.
2. Get its data and the verify command:
   ```sh
   python tools/getcand.py func_XXXXXXXX
   ```
3. Write C to `src/auto/<name>.c` for no external calls, or
   `src/calls/<name>.c` when the function calls other functions.
4. Run the printed `verify_cmd`. Iterate until `>>> MATCH <<<`.
5. Open a PR with just your new source file(s).

Good first targets:

- small leaf functions
- functions with simple arithmetic
- getters/setters
- simple state checks
- wrappers that can be expressed in C without inline ASM

Avoid as first targets:

- large gameplay functions
- functions relying on unknown structs
- functions with complex overlays
- functions that only "match" by copying assembly

## Contributing via decomp.me

Do not want to install the toolchain? Use [decomp.me](https://decomp.me); it
runs the compiler in your browser.

1. Generate the scratch fields for a function:
   ```sh
   python tools/decompme.py func_XXXXXXXX
   ```
2. Open <https://decomp.me/new>, pick **Nintendo DS** and compiler
   **3.0 build 139 (MW 2.0sp2p4)**, then paste the printed flags, diff label,
   target assembly, and context.
3. Click **Create scratch**, write C in the editor, and iterate to 100%.
4. Open a PR with the matching C, or share the scratch link.

## Notes

- Some functions are hand-written assembly idioms that the compiler will not
  reproduce from C. Leave those clearly labeled as ASM stubs until a better
  representation is found.
- Compile flags are pinned in `tools/match.py`; do not change them casually.
- Keep C minimal and readable; rename symbols/struct fields in `config/` as you
  understand them.

## Scope reminder

This is a matching decompilation, not a port. Do not add ROM data, assets, or
any copyrighted material to the repository.
