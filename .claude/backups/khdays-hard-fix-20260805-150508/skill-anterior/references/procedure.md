# Procedure — full workflow

## Toolchain detail

- Compiler: `mwccarm` 3.0 build 139 (CodeWarrior DS 2.0 SP2), patched license.
  Full collection in `tools/mwccarm/` (1.2 base..sp4, 2.0 base..sp2p4, 3.0_136
  [FLEXlm-locked] + 3.0_136_patched [runnable retail-era build], 3.0_patch4, dsi).
  If a codegen artifact looks impossible, sweep all generations before concluding.
  Per-file compiler overrides in `config/arm9/file_compilers.json` (e.g. ov028
  a994 = `1.2/sp4`); map a file to `3.0_136_patched` for the retail-era 3.0/136.
- Flags: `-O4,p -proc arm946e -interworking -lang c99 -enum int -char signed
  -inline on,noauto -Cpp_exceptions off -gccext,on`.
- Linker `mwldarm`; delink/config `dsd` = `tools/dsd.exe`.
- Ghidra MCP bridge (bethington/xebyte) at `:8080`, program `days.nds` open.

## Per-function loop (detailed)

1. **Candidate.** `build/func_index.json` `relocs` empty ⇒ reloc-free (easiest).
   Two sources: funcs routed to `src/overlays/ovNNN/asm_stubs/{auto,calls}/` (a stub
   file exists) or funcs in a raw asm blob gap (no per-func file — carve them).
2. **Ghidra first.** Rename symbol + params + locals semantically. NPE-on-endTx
   quirk: mutation applies anyway, verify by read-back.
3. **Write C** keeping `func_ovNNN_ADDR`.
4. **Verify byte-exact BEFORE wiring:**
   - `python tools/verify_idx.py <file.c> <name> [--thumb]` (reloc-aware; masks
     relocated words). This is the primary per-func gate.
   - reloc-free alt: `python tools/match.py <file.c> <hex> [--thumb]`
   - has relocs alt: `python tools/match.py <file.c> --obj <delink.o> --func <name>`
   - `python tools/getcand.py <func_name>` prints mode/kind/hex/verify_cmd.
   - Never chain `verify && commit` — a DIFIERE still commits. Check the result first.
5. **Wire in.**
   - asm_stub → real: **delete** `src/overlays/ovNNN/asm_stubs/{auto,calls}/func.c`
     and **create** `src/overlays/ovNNN/{auto|calls}/func.c` (calls/ if relocs,
     auto/ otherwise). Deleting the stub matters: gen_delinks `SRC_ROOTS` is
     last-wins and `asm_stubs/*` sorts AFTER `auto/*`, so a leftover stub overrides
     your real file (build stays byte-exact via the stub, but the match is inert).
   - blob-gap carve: just **create** the `auto|calls/func.c`. No stub to delete.
   - Write files LF (`open(...,'w',newline='\n')`) to avoid CRLF churn.

## Family-harvest loop (detailed)

1. `python tools/scan_fam.py <minsize> [--thumb]` — groups still-stubbed funcs by
   reloc-masked hex, ranked by family size. Attack the biggest non-deferred.
2. Match the template via the per-function loop.
3. `python tools/genfamily.py <template> --write` (ARM) or
   `python tools/genfamily_thumb.py <template> --write` (THUMB) — generates,
   verifies, and wires every sibling (deletes stubs). Dry-run without `--write`.
   **CRITICAL: genfamily deletes SIBLING stubs but NOT the template's own stub —
   you MUST `rm src/overlays/ovNNN/asm_stubs/{calls,auto}/<template>.c` by hand**
   (else it silently shadows the match). Audit: names present in BOTH a real
   calls|auto dir AND its asm_stubs sibling.
4. Name ALL members in Ghidra in one shot: `python tools/namefam.py <template>
   <NewName> "<plate>"` (or `tools/namefam_multi.py <NewName> "<plate>" <t1> <t2>…`).
   Writes `C:\Users\Yokimitsuro\ghidra_scripts\NameFam.py`; run via ghidra MCP
   `run_ghidra_script`. Quirk: ends with "No transaction is open" AFTER printing
   `named=N … SAVED_OK` — that IS success; check console output, not the error flag.
5. **`dedupprop.py`** (masked-hex twin propagation) after each batch — see tools.md.

## THUMB specifics

- `func_index.json` `mode` field is UNRELIABLE — detect THUMB by any reloc offset
  not 4-aligned. `getcand.py` mis-disasms THUMB as ARM; use `python tools/td.py
  <func>` (THUMB disasm + relocs) instead.
- Verify: `python tools/verify_idx.py <c> <name> --thumb`.
- Instruction diff: `python tools/tdiff.py <c> <name>` (THUMB) /
  `python tools/diffdis.py <c> <name>` (ARM).
- Ghidra usually has no function at THUMB gap addresses — NameFam.py createFunctions
  them automatically.

## Library / unmatchable → `nonmatching/`

If a candidate resists and looks like prebuilt-library code (SDK/NNS), sweep ALL
compiler generations × opt levels first. Classic tell of linker-absolute source:
pool-load of an ARM-encodable immediate. If NO mwccarm reproduces it, the asm stub
STAYS (dsd keeps it byte-exact) and you write documented, semantically-equivalent C
in `src/overlays/ovNNN/nonmatching/<func>.c` (gen_delinks only scans
`auto|calls|asm_stubs`, so `nonmatching/` never touches the build). Name it in
Ghidra with the full explanation. Precedent: ov001_0204ce40 / SndAllocHeapBuffers.

Extern-name rule for the mono link: every extern in a matched `.c` must use the
CANONICAL exported name — semantic names for delinked libs (`NNSi_*`, `VEC_*`,
`MTX_*`, `OS_*`, `MI_*` — check `config/arm9/{,itcm/}symbols.txt` + delinks.txt for
the address), `func_ADDR` for game code. Never invent semantic externs for game
funcs; never `func_ADDR` an address a lib already exports by name. "Sum of symbol
sizes exceed section size" = duplicate symbols.txt entry — remove it.

## Git / commit rules

- Never add a `Co-Authored-By: Claude` trailer.
- Stage only `src/**.c` additions and `asm_stubs/**.c` deletions.
- Do NOT stage `config/**/delinks.txt` — regenerated by `configure`, left dirty by
  convention.
- Don't push / force-push without per-time authorization (routine hourly pushes are
  pre-authorized).

## The 306 build gate (EXACT — mono link gives a FALSE 193/113)

`dsd check modules` rebuilds each module from source and compares to
`build/build/*.bin`, which it treats as the REFERENCE. `ninja build/arm9.elf` (mono)
OVERWRITES those bins with mono-relocated images → corrupts the reference → false
113 "checksum failed" (the .text is still byte-exact). CORRECT gate:

1. Restore originals:
   `cp dsd_extract/arm9/{arm9,itcm,dtcm}.bin build/build/` and
   `for f in dsd_extract/arm9_overlays/ov*.bin; do b=$(basename $f .bin); cp $f build/build/arm9_$b.bin; done`
2. `python tools/configure.py && ninja`  ← DEFAULT `compile` target; do NOT run
   `ninja build/arm9.elf` (that is only the "does it all link / no Undefined" check).
3. `tools/dsd.exe check modules --config-path config/arm9/config.yaml -f`  → 306 OK.

Expect `DSD_OK=306 FAILED=0`. Just run the three steps above -- the old `bck2.sh`
wrapper lived in a session scratchpad and is gone.

## Progress / audit + hourly doc regen

- `python tools/progress.py` (run from `tools/`; imports `audit_progress`) rewrites
  `PROGRESS.md` and prints `C=…/23240, ASM=…, SDK=…, bytes=…/4728790`.
- Then hand-update `README.md`'s Status table: C matched funcs + bytes lines, ASM
  stubs, SDK, named-only (`23240 − C − ASM − SDK`), and the byte %. DONE-module list
  (ov001/028/290/300/302) — verify with `grep '^| DONE ' PROGRESS.md` before
  changing. Commit `PROGRESS.md` + `README.md` together.
- Do this every hour at/just before the push (user asked 2026-07-13).

## Shared C headers: asked and settled (2026-07-20) -- the rule stands, the REASON was wrong

The question came up directly: should the tree use shared headers for the struct definitions
instead of redeclaring them per file? Answer: **no. Ghidra types stay the data model, and the
per-file struct in each `.c` stays a codegen tool.**

But fix the justification, because the one written in SKILL.md is not true and a wrong reason is
what gets a settled rule re-opened:

- ❌ *"delinking rules out shared headers."* It does not. `#include` is resolved at compile time
  and delinking operates on object files; a header of pure typedefs cannot reach either.
- ✅ **The real reason: the struct in a matched `.c` is a STEERING TOOL, not a description of the
  object.** Its job is to make mwcc emit one specific instruction sequence -- force a `ldrh`+shift
  pair, pick a base register, get an offset split a particular way. Different functions touching
  the SAME object routinely need DIFFERENT shapes to reproduce their own codegen: one needs
  `int aWords[4]`, another needs `char pad[16]` at the same offset, a third needs a bitfield of a
  specific container width. A shared header would force one shape on all of them and cost matches.
- ✅ Second reason: a header creates a build-order dependency across ~14,000 files for zero
  byte-level benefit, and any edit to it would need the full 306 gate re-run to prove it changed
  nothing.

So the ~4,000 ad-hoc per-file declarations are **not** the defect they look like -- they are
per-function tooling. The defect was that there was no authoritative model anywhere, and **Ghidra
types are that model**: they cannot perturb codegen or the gate, and they pay off in every
decompilation that touches the object.

★ What this means in practice, unchanged: decode a layout -> create/extend the Ghidra type in the
same batch -> write whatever struct shape the `.c` needs to match. The two are allowed to differ,
and when they do, **Ghidra is the one that is right**.
