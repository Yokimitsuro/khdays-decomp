# ov028 encrypted/self-modifying code (anti-tamper) — why ov001 can't reach 100% matched C

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

## Consequence for ov001

`func_ov001_0204ce40` (sound-heap bootstrap) calls three of these encrypted ov028
functions (`0x0208b490`, `b200`, `b040`). It cannot be compiled to linkable matched C
because those callees are not code in the static image — the `bl`s are `module:none`.
This is a toolchain/format limit rooted in the game's protection, not a codegen tie.
ov001 is 7/8 matched; the 8th stays as its asm stub. The separate literal-pool `0x1c`
issue (an absolute lock-id symbol) is real but secondary and would only matter once
the callees were linkable.
