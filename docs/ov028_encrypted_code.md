# ov028 encrypted/self-modifying code (anti-tamper) — why ov001 can't reach 100% matched C

> **2026-07-19 — this is DS Protect 1.10**, a commercial anti-piracy library used by 300+ DS
> titles, not game code. Identified via the decomp.me community and verified here by
> decrypting the bodies with `tools/dsprot_decrypt.py`: the plaintext maps line for line onto
> the public decompilation at <https://github.com/taxicat1/dsprot> (branch `1.10`), down to
> the literal `0x320` obfuscation offset visible in each prologue.
>
> The eight encrypted symbols are, in address order, `MACOwner_IsBad`, `ROMTest_IsBad`,
> then `DSProt_Detect{Flashcart,NotFlashcart,Emulator,NotEmulator,Dummy,NotDummy}`. It also
> explains two long-standing puzzles: the `0x88888889` reciprocal is `i % 15 == 0` in the key
> derivation, and `0208a994` needs mwcc 1.2 sp4 because it is third-party precompiled
> middleware. The same pattern appears in nine overlays.
>
> **None of this changes the section classification below.** The bodies are still encrypted in
> the static ROM, so the region stays `.rodata`. See the skill's `references/ov028-dsprotect.md`.

## Summary

`config/arm9/overlays/ov028/delinks.txt` marks `0x0208abd0..0x0208b568` (2456 bytes)
as `.rodata`. This is **correct**, even though ten ARM function prologues live there.
The region is **self-decrypting anti-tamper code**: in the static ROM the bodies are
encrypted (they do not decode as valid ARM), and are only turned into real
instructions at run time inside a protected block. `dsd delink` rightly refuses to
disassemble it (`IllegalIns` at `0x0208ac00`).

Do **not** rewrite the section as `.text` — it breaks `dsd delink` and cannot be
matched to C. It was tried and reverted; the build is byte-exact as-is (`dsd check`
306/306, `ninja` mismatches=0). The encrypted bytes are reproduced verbatim from the
ROM blob.

## The scheme

Each protected function has this shape:

```
push {r4..lr}; sub sp,#0x80            ; real prologue (decodes fine)
...set up pointers...
push {r0-r7}
mov  r0,#6
add  r0,pc,r0,lsl#1                    ; r0 = &encrypted_body
bl   0x0208a7e0                        ; DECRYPT routine
pop  {r0-r7}
b    <past the encrypted block>
<~40 words that do NOT decode as ARM>  ; encrypted body
mov  r0,pc; sub r0,r0,#0x14
bl   0x0208a8ac                        ; RE-ENCRYPT routine
pop  {r4..pc}                          ; real epilogue
```

The decryptor at `0x0208a7e0` (already in the repo as an `asm` stub,
`src/overlays/ov028/asm_stubs/calls/func_ov028_0208a7e0.c`) is a 16-iteration loop
using the magic constant `0x88888889` (reciprocal divide by 15) and an XOR with
`0xff`, ending in `DC_FlushRange` + `IC_InvalidateRange` — it flushes the data cache
and invalidates the instruction cache because it has just rewritten code the CPU is
about to execute. `0x0208a8ac` re-encrypts on the way out.

## Blast radius

- **6 encrypted target functions** in ov028: `0x0208b040`, `b120`, `b200`, `b2e0`,
  `b3c0`, `b490` (the ten prologues starting at `0x0208abd0` are the whole family;
  these six are the ones called cross-overlay).
- **17 `module:none` relocations** across the whole project — every one points at one
  of those six. Callers span **five overlays**: ov000, ov001, ov004, ov005, ov023.
  `dsd` leaves the `bl` raw with no reloc because the target is not attributable code.
- The `0x88888889` decrypt/encrypt stub pattern appears in **nine overlays**
  (ov005, ov028, ov039, ov058, ov078, ov095, ov115, ov116, ...), i.e. the anti-tamper
  subsystem is used game-wide, not just here.

## Consequence for ov001 (RESOLVED 2026-07-10 — the encryption never blocked the link)

`func_ov001_0204ce40` (`ov001_CreateMainAndSubHeaps`, a heap bootstrap — NOT sound
related) calls five of these encrypted ov028 functions (`0x0208b490`, `b200`, `b040`,
`b120`, `b2e0`). The earlier conclusion here — "it cannot be compiled to linkable
matched C because those callees are not code in the static image" — was **wrong**.

A `bl` does not need its target to be *code*; it needs an **address**. dsd resolves a
relocation via `first_at_address()`, which accepts any symbol kind. Those six ov028
entry points simply had no symbol (they sat unnamed inside the `data_ov028_0208af30`
blob), so dsd emitted the calls as `module:none` — an analysis gap, not a property of
the binary. Naming the six addresses as `kind:data(any)` symbols (which auto-size, so
**not one byte moves**, and the region stays `.rodata`) lets dsd resolve all 17
cross-overlay relocs to `module:overlay(28)`. mwld then emits a plain `bl` to an
`STT_OBJECT` symbol in `.rodata` — no veneer, no decryption. The encrypted 2456-byte
block is reproduced verbatim from the ROM, exactly as before.

The literal-pool `0x1c` was likewise not an "absolute lock-id" mystery: it is
`FS_OVERLAY_ID(ov028)` = 28 = ov028's own id, the stock NitroSDK idiom, and dsd already
emits `OVERLAY_28_ID = 28` into `arm9.lcf` with a first-class `kind:overlay_id`
relocation (which must *stay* `module:none` per dsd's rules).

**ov001 is now 8/8 — the third 100% module (after ov290, ov300).** The same fix
resolved the other 12 `module:none` relocs (ov000/ov004/ov005/ov023), so those callers
are now decompilable too. See `staging/ov001/README.md` for the end-to-end evidence
(object match, `dsd delink` exit 0, an isolated mwld link byte-identical to the ROM).
