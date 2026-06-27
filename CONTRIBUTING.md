# Contributing

Thanks for helping decompile *Kingdom Hearts 358/2 Days*! The workflow is simple:
pick a function, write C that compiles to the **exact same bytes** as the
original, and open a PR.

## The one rule: byte-exact

A function is only accepted when it passes byte-exact verification. **How** you
arrive at the matching C does not matter — by hand, with scripts, or with any
tooling — as long as the verifier prints `>>> MATCH <<<`. The verification is the
quality gate, so this scales to many contributors in parallel.

## Claiming work

Functions are grouped by **module/overlay** (`ov000`, `ov030`, …). To avoid
duplicated effort, **claim a module before you start**:

1. Check [PROGRESS.md](PROGRESS.md) for a module that isn't finished (🟡/⬜).
2. Open or comment on a GitHub issue titled e.g. `Claim: ov030` and assign
   yourself. Un-claim if you stop working on it.
3. Work through that module's `func_*` functions and PR them.

Collisions are harmless: byte-exact verification means only a matching `.c` is
ever merged, so nothing breaks if two people overlap — claiming just saves
wasted effort. Use the project Discord / decomp.me for live coordination.

## Setup

You must provide your own legally-obtained copy of the game. Nothing
copyrighted is distributed here.

### Reference ROM

This project targets one specific ROM dump. If your `days.nds` doesn't match
these hashes, addresses won't line up and `dsd` extraction will produce a
different config.

| | |
|---|---|
| File | `days.nds` |
| Size | 268,435,456 bytes (256 MiB) |
| Region | EU (gamecode `YKGP`, maker `GD` = Square Enix) |
| SHA-1   | `6fae8f5bbe80114b4e2535260eab5f4d0fc8a844` |
| SHA-256 | `1ecf5e7a41a2ae48e7c5fd3f678e5a79e854d843f1a1fa3a952a41b14e51ec4f` |
| MD5     | `6eac99ad1f77920bdafbc71fd6418cc8` |

Verify with `sha1sum days.nds`. If your dump differs (e.g. a NA/JP region,
trimmed dump, or scrubbed copy), this project is not directly usable —
addresses in `config/`, `func_index.json`, and every committed `.c` were
computed against the EU dump above.

1. **Python deps:** `pip install capstone pyelftools ndspy`
2. **`dsd`** (DS extraction/delinking): download from
   [AetiasHax/ds-decomp releases](https://github.com/AetiasHax/ds-decomp/releases)
   → `tools/dsd.exe`.
3. **`mwccarm` 3.0 build 139** (CodeWarrior for Nintendo DS 2.0 SP2 compiler).
   The DS decomp community documents how to obtain it; for browser-based matching
   without a local install, [decomp.me](https://decomp.me) hosts it server-side.
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
   > Note: `--allow-unknown-function-calls` is required, otherwise `init` aborts
   > on a known analysis edge case.
6. Generate the candidate lists: `python tools/find_candidates.py` and
   `python tools/find_calls.py`.

## Decompiling a function

1. **Claim it** first (open an issue or claim it on the tracker) so nobody
   duplicates the work.
2. Get its data and the verify command:
   ```sh
   python tools/getcand.py func_XXXXXXXX
   ```
   It prints the mode, the disassembly (with callee names for functions that make
   calls), where to write the `.c`, and the exact `verify_cmd`.
3. Write your C to `src/auto/<name>.c` (no external calls) or
   `src/calls/<name>.c` (declare callees as `extern int func_X();`).
4. Run the printed `verify_cmd`. Iterate until `>>> MATCH <<<`.
5. Open a PR with just your new `.c` file(s).

## Contributing via decomp.me (no local setup)

Don't want to install the toolchain? Use [decomp.me](https://decomp.me) — it runs
the compiler in your browser.

1. Generate the scratch fields for a function:
   ```sh
   python tools/decompme.py func_XXXXXXXX
   ```
2. Open <https://decomp.me/new>, pick **Nintendo DS** and compiler
   **3.0 build 139 (MW 2.0sp2p4)**, then paste the printed flags, diff label,
   target assembly, and context.
3. Click **Create scratch**, write your C in the editor, and iterate to 100%.
4. Open a PR with the matching C (or just share the scratch link).

## Notes

- Some functions are hand-written assembly idioms (e.g. `ldm/stm` with
  writeback, branch-off-flags) that the compiler will not reproduce from C —
  leave those as-is.
- Compile flags are pinned in `tools/match.py`; don't change them.
- Keep C minimal and readable; rename symbols/struct fields in `config/` as you
  understand them.

## Scope reminder

This is a matching decompilation, not a port. Do not add ROM data, assets, or
any copyrighted material to the repository.
