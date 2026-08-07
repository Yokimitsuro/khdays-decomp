# ov024 — MobiClip video decoder (Actimagine)

The `mv/*.mods` cutscene codec. Symbols were stripped from the ROM, hence no string hints.
ov012 (7,904 B) is only the player scene wrapper and enters ov024 at `func_ov024_02084df4`.

## ★★ The video decoder is a 26 KB ITCM-resident blob — not a normal function

**This is why the video codec could never be found in the code section.** `func_ov024_02085154`
(the decoder init, 1452 B) does at +0x184:
```
bl  func_ov024_02086620      ; returns a pointer
str r0, [r4, #0x38]          ; ctx+0x38  <- called later via `blx r1` in MobiClip_ReadFrame
```
and `func_ov024_02086620` is a **relocator**, not a decoder:
```c
if (cache == 0) {                          /* not yet relocated */
    if (arena_free < 0x659c) return static_blob;      /* fallback: run in place */
    cache = arena_ptr;
    MIi_CpuCopyFast(static_blob, arena_ptr, 0x659c);  /* Nitro order: (src, dst, size) */
    arena_ptr  += 0x659c;
    arena_free -= 0x659c;
}
return cache;
```

| fact | value |
|---|---|
| blob source | `data_ov024_0208c8c4` (reloc +0x78 of 02086620) |
| blob size | **0x659c = 25,996 B** (pool +0x74) |
| blob end | 0x0208c8c4 + 0x659c = **0x02092e60** |
| arena descriptor | `data_ov024_0209bb30` (reloc +0x70) |
| copier | `MIi_CpuCopyFast` (reloc +0x30) |

So **0x0208c8c4 – 0x02092e60 is the video decoder, copied into fast memory (ITCM, 32 KB on DS —
26 KB fits) and executed from there**. It is position-independent code. This resolves several
loose ends at once:
- the code section is only 18.7 KB because ~26 KB of the "51 KB of tables" is actually code;
- `func_ov024_02092e60_unk` is **not** a function inside the table region — it sits exactly at the
  blob's end boundary (⚠ an earlier note here called it "the scale/filter stage"; it *is* called
  from `MobiClip_EmitFrame` with the scale args, but it is adjacent to the blob, not part of it);
- no `str rX,[rY,#0x38]` with a literal ctx base exists anywhere else.

`func_ov024_0208670c` is the same relocator for the 768-byte saturation table (0x300), with
`data_ov024_0209352c` as the static fallback — which is how ctx+0x54 gets its pointer, and an
independent confirmation that the pattern is read correctly. `0208669c` and `0208677c` are two
more of these getters.

### ★ The cache layer — all four getters matched (2026-07-16)

All four are **byte-exact** now, and they are one shape: a lazy cache that copies a const
`.rodata` payload into a bump arena on first use, remembers the carved pointer in its own slot,
and **falls back to the `.rodata` original uncached when the arena is full**. The payloads are
read-only, so either address works — the copy is purely a speed play for per-pixel indexing.
For the port this means *nothing depends on the copy happening*; the fallback path is the
semantics.

There are **two independent arenas**, not one — the descriptor at `data_ov024_0209bb30` holds
both, and the (already matched) initialisers corroborate the split exactly:

| slot | meaning |
|---|---|
| +0x00 | cached sat5 table (data arena) |
| +0x04 | cached decode table (data arena) |
| +0x08 | cached **code** blob (code arena) |
| +0x0c / +0x10 | **data** arena remaining / cursor — init `func_ov024_020865f8` (also clears +0x00/+0x04/+0x20) |
| +0x14 / +0x18 | **code** arena remaining / cursor — init `func_ov024_020865d8` (also clears +0x08) |
| +0x20 | cached clamp8 table (data arena) |

The code blob gets its own arena because it is *executed*; the three tables share the data arena.

### ★★ Which arena is which — SETTLED by `func_ov024_0208455c` (matched 2026-07-16)

The reservation function pins it by arithmetic, no guessing: **arena id 3 = ITCM, id 4 = DTCM.**

| | code arena | data arena |
|---|---|---|
| memory | **ITCM** | **DTCM** |
| base | `OS_GetArenaHi(3) - 0x659c` = `0x02000000 - 0x659c` = **`0x01ff9a64`** | `OS_GetArenaLo(4)` |
| size | `func_ov024_020865c4()` = `0x659c` | `min(OS_GetDTCMAddress() + 0x4000 - OS_GetArenaLo(4), 0x2580)` |
| init | `020865d8` | `020865f8` |

Two independent confirmations fall out:
- `0x01ff9a64` is **exactly** the ITCM address the port byte-verified. Derived here from first
  principles rather than measured.
- `func_ov024_020865d0()` = `0x2580` = **`0x2100 + 0x300 + 0x180`** — the exact sum of the three
  data tables. The DTCM arena asks for precisely what it will hold, which cross-checks the payload
  identification above from the other direction.

`OS_GetDTCMAddress() + 0x4000` = end of the 16 KB DTCM, so the data arena is the free DTCM tail.

**ITCM is borrowed, not owned.** Before taking the top `0x659c` of ITCM, the reservation copies
whatever already lives there into the `.bss` save area at `MobiClip_WorkBlock + 0xd8`
(`02093b20..0209a0bc`) via `MIi_CpuCopy32`, so it can be handed back. A port that simply owns the
blob's memory is fine, but it should know the original restores ITCM.

Bookkeeping lives in `MobiClip_TcmReservation` (`0209ba48` == `MobiClip_WorkBlock + 0x8000`):
`+0xd8` ITCM code size, `+0xdc` ITCM code base, `+0xe8` = `MobiClip_TcmArenas` (the descriptor
above).

⚠ Both clamps in that function are a **MIN whose argument is evaluated twice**, so each getter is
`bl`-ed on both sides of the compare (`bl f; cmp; bcc; bl f; mov`). That is one value, not two —
do not misread it as two different quantities.

| getter | payload | size | verified content |
|---|---|---|---|
| `02086620` | `data_ov024_0208c8c4` | 0x659c | the PIC decoder code blob |
| `0208669c` | `data_ov024_0208a7c4` | 0x2100 (8448) | u16 decoder lookup entries |
| `0208670c` | `data_ov024_0209352c` | 0x300 (768) | `sat[i] = clamp((i-256) >> 3, 0, 31)` |
| `0208677c` | `data_ov024_020933ac` | 0x180 (384) | `clamp8[i] = clamp(i - 64, 0, 255)` |

Both table formulas were checked **entry-for-entry** against `dsd_extract/arm9_overlays/ov024.bin`,
not sampled. `020933ac` (the 8-bit clamp, 64-entry negative guard band) was previously
unidentified. The payloads are contiguous and the run cross-checks the blob length:
`0208a7c4 + 0x2100 = 0208c8c4`, `+ 0x659c = 0x02092e60` = the `func_ov024_02092e60_unk` boundary;
and `020933ac + 0x180 = 0209352c`.

⚠ **Reading these tables in Ghidra is misleading**: both open with a long zero run (0x41 bytes for
`020933ac`, 0x108 for `0209352c` — the guard bands), so a short `read_memory` looks like unbacked
BSS. They are genuinely `.rodata`: `delinks.txt` puts `.rodata` at 0x02087318–0x020938f0 and
`.bss` only from 0x02093a20, and `symbols.txt` types them `data(any)`. Dump from the extracted
`.bin` (file base = 0x02082960, size 0x110c0, ending exactly at `.bss` start) rather than trusting
a window of zeros.

**Codegen:** all four came out 8 bytes short at first because mwcc predicates the "no room" early
return inline (`ldrlo`/`poplo`) where the ROM branches to an out-of-line exit block after the copy
body. Writing the guard as `if (room) { copy } else { return src; }` instead of an early return
reproduces the ROM's layout exactly. See `codegen-cracks.md`.

**Method note:** the first scan for `str rX,[rY,#0x38]` returned zero hits because the mask
`0x0FFF0FFF` leaves the Rn field *in*, so it only ever matched `[r0,#0x38]`. The correct mask is
`0x0FF00FFF`. Zero hits from a buggy scan is not evidence of absence.

## Map (measured, not guessed)

| region | size | contents |
|---|---|---|
| 0x02082960 – ~0x02087318 | 18,770 B | **all 111 ARM/THUMB code funcs** (9 THUMB) |
| ~0x02087318 – ~0x02093a60 | ~51 KB | tables — **plus one function**, see below |
| beyond | 33,088 B | BSS = frame buffers |

`symbols.txt` lists **120 functions / 24 data / 8 bss**, spanning 0x02082960–0x0209bb30.

**`func_ov024_02092e60_unk` sits INSIDE the table region** (dsd flagged it `_unk`). It is real:
`func_ov024_02085ab8` calls it with a 9-field stack struct. It is the scale/filter stage that
fills the +0x68/+0x6c buffers which the colour converter then reads. Do not reclassify it as data.

## MODS container

Header of `mv/*.mods` (confirmed across 802/803/804.mods):

| off | type | meaning |
|---|---|---|
| 0x00 | char[4] | `MODS` (0x53444f4d LE) |
| 0x04 | char[4] | `N3\n\0` (0x000a334e LE) |
| 0x08 | u32 | frame count (802=4485, 803=839, 804=204) |
| 0x0c | u32 | width — always 256 |
| 0x10 | u32 | height — always 160 (letterboxed inside the DS's 192) |
| 0x14.. | | not yet identified |

### The version tag IS checked — and it changes the parsing

⚠ **Correction (2026-07-16).** An earlier note here claimed "nobody validates the magic", based on
a scan of all 616 built binaries for the constants 0x53444f4d / 0x000a334e returning zero hits.
The scan was accurate but the conclusion was wrong: **the check is byte-wise, so a 32-bit constant
scan cannot see it.** Never conclude "absent" from a search that could not have found it.

`func_ov024_020859d4` (the frame reader) does, confirmed in the disassembly:
```
02085a34: ldrsb r0,[r5,#0x8]      ; ctx+8
02085a38: cmp   r0,#0x4e          ; 'N'
02085a3c: ldrsbeq r0,[r5,#0x9]    ; ctx+9
02085a40: cmpeq r0,#0x33          ; '3'
```
The `MODS` word itself is never compared. The **`N3` version tag is**, and it gates real
behaviour:
```c
u16 hdr   = **(u16 **)(ctx + 0x34);        /* first u16 of the frame        */
int extra = (hdr & 0x8000) ? 4 : 0;
ctx[0xa4] = (hdr & 0x8000) ? 1 : 0;        /* flag exposed to the player    */
int n = (*(fn *)(ctx + 0x38))(ctx + 0x34); /* parse; returns bytes consumed */
*ptr += n;
if (ctx[8] == 'N' && ctx[9] == '3')
    *ptr += extra;                         /* N3-ONLY extra 4-byte advance  */
```
A port that ignores this desyncs on the first frame with bit 15 set.

`func_ov024_020859d4` also, per frame: copies a word from `frame + 0x3b4` into the per-frame array
at `ctx+0x64`, zeroes `ctx+0xcc`/`ctx+0xd0`, and advances **six** ring indices at `ctx+0xac..0xc4`
(wrapping at `ctx+0xa8`), then bumps the decoded-frame counter `ctx+0xa0`. Six ring indices for six
plane/stream arrays.

### Frame index entry format — `func_ov024_0208589c`

The container iterator. Guard is `ctx[0x26] != ctx[3]` = *current frame != frame count*. Each
index entry is one u32 split as:
```c
entry_size  = val >> 14;        /* 18 bits -- byte size; the reader adds 4 to skip the header */
entry_field = val & 0x3fff;     /* 14 bits -- multiplied by the u16 at ctx+0x1e               */
```
(mask 0x3fff read from the function's own literal pool). `ctx[0]` is an object with a vtable;
`+0x10` = read, `+0x14` = advance.

## ★ Colour conversion — `func_ov024_02086004` (1472 B, zero relocs)

**The codec is YCoCg, NOT YUV.** This is the single most important finding for the port: treating
it as YUV (R = Y + 1.402·V …) produces a colour cast because they are different colour spaces —
not a range or coefficient problem.

Proven from the disassembly. With `P = chroma[0] - 128`, `Q = chroma[0x80] - 128`, the function
computes exactly three table indices:

| index | shift | BGR555 field |
|---|---|---|
| `Y + P − Q` | ×1 | bits 0–4 → R |
| `Y + Q` | ×0x20 | bits 5–9 → G |
| `Y − P − Q` | ×0x400 | bits 10–14 → B |

which is precisely the YCoCg inverse `t = Y − Cg; R = t + Co; G = Y + Cg; B = t − Co`
with **P = Co, Q = Cg**. Bit 15 is set (`orr #0x8000`) as the DS alpha bit.

### Plane layout (confirmed independently by the caller's allocations)

`func_ov024_02085ab8` allocates:
```c
FUN_02083cf0(  height       << 8 );   /* luma  = height   × 256 */
FUN_02083cf0( (height >> 1) << 8 );   /* chroma = height/2 × 256 */
```
Chroma is **half height but full 256-byte rows**: each row is 128 bytes of Co followed by 128
bytes of Cg. That is why `chroma[0x80]` is the *other component of the same pixel*, not the next
row. The row advance corroborates it: luma `+= 0x200` (two 256-byte rows), chroma `+= 0x100`
(one Co row + one Cg row) per two luma rows.

### The saturation table — `data_ov024_0209352c`, 768 B

Located by shape (it is the **only** 768-byte non-decreasing 0..31 ramp in the overlay). All 768
bytes verified against the formula with **zero exceptions**:

```
tbl[0x100 + x] == clamp(x >> 3, 0, 31)      for x in [-256, 511]
```
The function holds `base = tbl + 0x100`, so a lookup is `tbl[base + chroma_term + Y]`; the ±256
padding absorbs chroma under/overflow without a branch.

### ★ 2×2 checkerboard dither — do not omit

Half the pixels get `Y − 4` before the lookup (−4 in the input domain = −½ LSB before the `>>3`).
Confirmed in the disassembly: **16 `sub rN,rN,#4` per 32 pixels**, arranged as

|  | x even | x odd |
|---|---|---|
| **y even** | Y | Y − 4 |
| **y odd** | Y − 4 | Y |

(`0x50 ldrb r4,[r0],#1` → no dither; `0x78 ldrb r4,[r0],#255` then `0x88 sub r4,r4,#4`; next row
`0x98 ldrb r4,[r0],#1` then `0xb0 sub r4,r4,#4`; `0xc0 ldrb r4,[r0],#-255` → no dither.)

### Reference implementation for the port

```c
static inline int sat5(int v) { return v < 0 ? 0 : (v > 248 ? 31 : v >> 3); }

/* luma:   height   × 256
   chroma: height/2 × 256, each row = 128 B Co then 128 B Cg
   dst:    BGR555, two pixels packed per u32                        */
for (int y = 0; y < height; y++) {
    const uint8_t *L = luma   + y * 256;
    const uint8_t *C = chroma + (y >> 1) * 256;
    for (int x = 0; x < width; x++) {
        int Co = C[x >> 1]        - 128;
        int Cg = C[0x80 + (x>>1)] - 128;
        int Y  = L[x] - (((x ^ y) & 1) ? 4 : 0);   /* checkerboard dither */
        int t  = Y - Cg;
        dst[y*stride + x] = sat5(t + Co)
                          | (sat5(Y + Cg) << 5)
                          | (sat5(t - Co) << 10)
                          | 0x8000;
    }
}
```

### Converter arg struct (decoder ctx + 0x3c)

| off in ctx | field |
|---|---|
| +0x3c | luma plane |
| +0x40 | chroma plane |
| +0x44 | dst (BGR555) |
| +0x48 | dst stride in **bytes** (caller writes `pixels << 1` → 16 bpp) |
| +0x4c | width |
| +0x50 | height |
| +0x54 | saturation table (→ `data_ov024_0209352c`) |

Other ctx fields seen: +0x10 width, +0x14 height, +0x68/+0x6c scaled luma/chroma buffers,
+0x9c frames-emitted counter, +0xa0 frame limit, +0xa8 ring size, +0xc4 ring index,
+0x5c/+0x60/+0x64 per-frame plane pointer arrays indexed by +0xc4.

### ★ Where the four cached payloads actually land — read off `func_ov024_02085154` (2026-07-16)

The decoder init settles the open question. ⚠ **The tables do NOT go into the converter arg
struct.** They go into a *separate* 0x454-byte decoder-state block allocated at **`ctx[0x34]`** —
the same block whose `[0]` is the bitstream cursor `MobiClip_DecodeAudioEntry` advances. The two
structs happen to both have live fields at +0x3c/+0x40/+0x44, which is easy to confuse.

| destination | value |
|---|---|
| `ctx + 0x38` | `MobiClip_GetDecoderCodeCached()` — the PIC blob, matching "invoked through ctx+0x38" |
| `ctx + 0x4c` / `+0x50` | width / height (copied from ctx+0x10 / +0x14) |
| `ctx + 0x54` | `MobiClip_GetSatTable5BitCached()` — **confirms the sat-table row above** |
| `ctx[0x34] + 0x04` / `+0x08` | width / height again, for the decoder block |
| `ctx[0x34] + 0x3c` | `MobiClip_GetDecodeTableCached()` — the 0x2100 u16 table |
| `ctx[0x34] + 0x40` | `data_ov024_020886c4` (.rodata, not previously mapped) |
| `ctx[0x34] + 0x44` | `MobiClip_GetClampTable8BitCached() + 0x40` |

**That `+ 0x40` bias is the proof of the clamp table's shape.** `clamp8[i] = clamp(i - 64, 0, 255)`,
so biasing the pointer past the 64-entry guard band makes `p[x] == clamp(x, 0, 255)` for
`x` in −64..319 — the decoder indexes it with a *signed* value directly, no offset in the inner
loop. Independent confirmation of the table identification.

**`0x14f8` confirmed a third time, from the allocation side:** the audio state array is
`MobiClip_Alloc(channels * 0x14f8)` (pool literal), and the init then writes the per-channel
stride field: `2` at `+0x14f4` of each block for coding 1, or at `+0x1cc` for coding 2 — stepping
the pointer by exactly 0x14f8 per channel.

**The MODS magic really is checked byte-by-byte** (`ldrsb`/`cmp` chain): `'M','O','D','S'` at
+0x4..+0x7, then `'N'` at +0x8 and `'2'` **or** `'3'` at +0x9, then a `u16 == 0xa` at +0xa. A
32-bit-constant scan cannot see this — see the negative-results rule in SKILL.md.

Pool literals in that function (all verified against the reloc list): `0x454` = the decoder block
size, `0x14f8` = channel stride, `0xc34` = a per-channel read length, `0x3fff` = the same entry
mask `func_ov024_0208589c` uses. Only `data_ov024_020886c4` carries a reloc.

## The audio channel block — stride 0x14f8 (from `func_ov024_02085c8c`, 2026-07-16)

`MobiClip_DecodeAudioEntry` (02085c8c) carves the per-channel state out of an array at `ctx+0x58`
with a **stride of 0x14f8** — and that number is a **pool LITERAL, not a data symbol** (the
function's only relocs are its five calls; check the reloc list before reading any pool word as a
global). So:

```c
chan = *(char **)(ctx + 0x58) + *(int *)(ctx + 0xd0) * 0x14f8;
```

This closes the loop with the transform below: `02086958` reads its stride from `ctx+0x14f4`,
i.e. the last field of its own 0x14f8-byte block. Channel index is `+0xd0`, wrapping at the
channel count `+0x1e` (which also clears the ADPCM first-entry flag `+0xa4`). `+0xcc`/`+0xc8` are
consumed/available counts.

Per-entry layout the dispatcher fills in before calling a decoder: `chan[0] = *cursor` (the
source), `chan[1] = dst`. The cursor itself is `*(int **)(ctx + 0x34)` and each coding advances it
by exactly what it read — 1: whatever `02086958` returns; 2: `0x28`; 3: `4` (state header, first
entry of a frame only) + `0x80` (nibbles); else `0x200` (raw PCM, copied straight to `dst`).

⚠ The ROM **re-derives** the channel pointer at every use (fresh `ldr +0x58` / `ldr +0xd0` / `mla`)
rather than keeping it live — model it as a `static inline`, not a local.

## `func_ov024_02086958` (2496 B) = AUDIO dequant + inverse transform -- PROVEN

Entry is at +0x810 (the `b` at +0 jumps the inline subroutines). The output stage settles it:

```
844: mov  r0, #0x80         ; 128 iterations
848: ldr  r5, [pc]          ; = +32767   (pool +0x9b8)
84c: ldr  r6, [pc]          ; = -32768   (pool +0x9bc)
850: ldr  r3, [r3, #0x4f4]  ; per-channel stride from ctx+0x14f4
854: ldr  r7, [r4], #4
858: cmp r7,r5 ; movgt r7,r5
860: cmp r7,r6 ; movlt r7,r6
868: strh r7, [r2], r3      ; 16-bit strided store
```
**Signed-16-bit saturation + strh + a channel stride = PCM.** Video pixels clamp to 0..255 and
store as bytes. Corroborated by the call chain: its only caller `02085c8c` dispatches four
codings (transform / 0x28 / IMA ADPCM / raw PCM 0x200), all yielding 256 samples per channel,
with ctx+0x1e = channel count and ctx+0xd0 = current channel.

⚠ The port's handoff claimed the opposite (that this is the video IDCT, on the grounds that the
blob has zero `mla` and "a transform kernel cannot exist without multiplies"). **That premise is
false** -- H.264-family integer transforms are add/shift only. Measured on the extracted blob:
mul=0, mla=0, but **706 `add/sub/rsb` with inline shifts** (`add r0,r0,r5,asr #1` etc), spread
across 26 of 156 prologues, with a family of four ~94-119-insn routines at 25-35% density
(0x020916ac, 0x020919fc, 0x020913bc, 0x02091534) that look like motion-comp filter variants.
Reply written to `khdays-port/data/re/mobiclip_blob_reply.md`.

### The dequant ramp and scan -- traced

```
820: lsr r6, r5, #9         ; r6 = header_u16 >> 9  (7 bits, 0..127)
824: cmp r6, #127           ; ==127 -> subroutine +0x920 ; else -> +0x960
; dequant/inverse-scan at +0x40:
48: rsb ip, r6, #127        ; ip = 127 - r6
4c: add r4, r4, ip, lsl #2  ; source starts at coefficient (127 - r6) of a 128-entry array
54: mov r1, #2              ; factor starts at 2
58: asr r2, r2, #4          ; coefficient 0 is NOT multiplied
78: mul ip, r2, r1          ; coefficient i * factor
7c: add r1, r1, #1          ;   factor ramps 2,3,4,5,... -- the running index, not a table
80: asr ip, ip, #4
```
**`r6` sets the first live coefficient.** The quantiser step is the running index, growing
linearly with frequency; the DC term is unscaled. The inline routine at +0x10 zeroes 512 B
(`stmia {4 regs}` x32) = the coefficient block clear.

Still open here: what +0x920 (r6==127) vs +0x960 select, and where the 128-entry source lives.
This is **audio** work -- it does not block the video path.

## The video decoder blob -- confirmed by the port

Byte-verified from a `cinematic.dst` savestate: the blob executes from **ITCM at 0x01ff9a64**,
26,012/26,012 bytes identical, ending exactly at 0x02000000 (flush against the ITCM top). The
saturation table is copied to **DTCM at 0x027e30e0**. Decoder ctx at **0x022a4700** (found by
searching main RAM for the `(512, 256, 160)` converter-arg signature -- one hit); every field
matches this document. The real luma/chroma planes are readable from main RAM at 0x022efe40 /
0x022f9e60 -- useful for validating a port decoder.

⚠ 0x027e30e0 is DTCM and 0x01ff9a64 is ITCM, **not** mirrored main RAM.

Extraction: ov024 = overlay file_id 24, BLZ-compressed -> 69,824 B (== ram_size), blob at
overlay offset 0x9f64, len 0x659c. Extracted copy: `khdays-port/data/re/mobiclip_blob.bin`.
Blob entry = 0x0208dfb4 (`b` at +0 over a blob-relative offset table at +0x04); 50 `push{..,lr}`
candidates. VLC candidates: 0x02091d14 (4428 B, 100% cover, heavy ldrb/ldr) and 0x02090674.

## Still open

- Rest of the core: 02085154 (1452 B, 18 relocs), 020846c0 (1108 B, 40 relocs) — bitstream/VLC
  and motion compensation are still unlocated.
- `func_ov024_02092e60_unk` — the scale/filter stage.
- MODS header fields past 0x14. Note `func_ov024_020834b0`'s `src` is an **already-parsed**
  header struct (mb dims + crop), not the raw file header — whoever builds it is unlocated.
- `func_ov024_02082f04` (720 B) turned out **not** to be codec: it is the movie **player scene
  tick**, living inside ov024 (root heap, button polling, fades). ov024 is not codec-only.


## MODS header — completed by the port (measured across all 46 `mv/*.mods`)

| off | meaning | values |
|---|---|---|
| 0x14 | encoder stamp (2 variants) | `0x0efc28f6` x37, `0x0efc29f1` x9 |
| 0x18 | audio coding | 3 on all 37 audio files, 0 on the 9 silent ones |
| 0x1a | channel count | 2 (stereo) wherever audio exists |
| 0x1c | sample rate | 22050 (35), 32728 (2 — the DS-native rate) |
| 0x20 | per-file size | varies |

`0x18 == 3` lining up with the type-3 = IMA ADPCM dispatch is **consistent, not traced**.
**9 of 46 files are video-only.**

`0x14` is measured but **not identified**: uncorrelated with sample rate (both variants occur
with rate 0 and 22050), uncorrelated with audio presence (the 9 `0x29f1` files and the 9 silent
files overlap in only 3), not a contiguous id batch (809, 810, 813, 825, 830, 838, 841, 843,
845), and constant per-variant regardless of frame count. Reads like an encoder build stamp with
a subset re-encoded later. No read of it has been traced in ov024.

⚠ **ffmpeg's `mods` demuxer does not expose MobiClip audio** (802.mods carries stereo @32728 per
its own header; ffmpeg reports video only). There is no external oracle for the audio path —
`func_ov024_02086958` is the only route.

## Runtime layout — confirmed by the port from `cinematic.dst`

- **Framebuffer = VRAM bank D**, `ctx+0x44 = 0x06600000`: 40,960/40,960 u16 with bit 15 set over
  exactly 512x160 (the whole frame carrying the DS alpha bit). No other bank shows the pattern.
- **Plane ring = 10 slots.** `ctx+0xa8 = 10`; `ctx+0x5c` -> array of 10 luma pointers,
  `ctx+0x60` -> array of 10 chroma pointers; slots are 0xF040 apart (40,960 luma + 20,480 chroma
  + 0x40 pad). `ctx+0xac..0xc0` are the **six decode** cursors, `ctx+0xc4` the **single emit**
  cursor.

### ★ The emit/convert order — settles what any savestate can show

`func_ov024_02085ab8` does, in this order:
```c
if (ctx[0xa0] <= ctx[0x9c]) return 0;
ctx[0x3c] = ring_luma  [ctx[0xc4]];      /* read the ring at the CURRENT index */
ctx[0x40] = ring_chroma[ctx[0xc4]];      /* (scale path: via 0x68/0x6c, only if param_4 != 0) */
ctx[0x44] = dst;  ctx[0x48] = stride << 1;
func_ov024_02086004(ctx + 0x3c);         /* CONVERT */
ctx[0x9c]++;
ctx[0xc4]++; if (ctx[0xc4] == ctx[0xa8]) ctx[0xc4] = 0;   /* bump AFTER */
```
So **ctx+0x3c/+0x40 are the conversion that already COMPLETED**, not a pending one — the emit
cursor is bumped after. With `ctx+0xc4 = 6`, bank D holds the conversion of **slot 5**.

But a decode cursor may already be re-writing that slot (the port observed
`ctx+0xac..0xc0 = 6,5,4,3,2,1` — one cursor sitting on slot 5), which is why slot 5 diffed
*worst* against bank D in their test and slot 6 best. **To byte-validate the converter, the
savestate must catch the decoder idle** — inside `02086004`, or on a frame where
`ctx[0xa0] == ctx[0x9c]`.

In that cutscene `ctx+0x68`/`+0x6c` are 0, i.e. `param_4 == 0` on every call: **the scale path
never runs and `func_ov024_02092e60` is not involved**.


## Blob map — first pass (decomp side, 2026-07-16)

Worked from the port's extracted `khdays-port/data/re/mobiclip_blob.bin` (blob base RAM
0x0208c8c4; `blob_off = RAM - 0x0208c8c4`).

### ★ The filter family IS motion-compensation interpolation — proven

The four routines picked out by shift-add density (0x020913bc, 0x02091534, 0x020916ac,
0x020919fc) are byte-wise averaging filters:

```
513c: ldr ip, [pc, #1092]      ; ip = 0x7f7f7f7f   <-- read from the pool at blob+0x5588
5144: ldrh r3, [r0, #-2]
5148: ldm  r0, {r4, r5, r6, lr}   ; 16 bytes = one row
514c: add  r0, r0, #0x100         ; next row -- the LUMA plane stride
5150: and  r3, ip, r3, lsr #1     ; (x >> 1) & 0x7f7f7f7f  = halve 4 packed bytes at once
5154: and  r4, ip, r4, lsr #1
...
5164: add fp, r3, r4, lsl #16 ; add fp, fp, r3, lsr #8 ; add r3, fp, r4, lsl #8   ; repack
```

**`0x7f7f7f7f` + `lsr #1` is the classic SIMD packed-byte halving idiom**, and the 0x100 stride is
the luma plane. This is half-pel interpolation, not a transform — it confirms the density reading
and settles that the 706 shift-adds are interpolation.

All four share one structure: **4 `ldm` / 3 `stm` / 4 row advances of 0x100**.

| RAM | size | halvings | prologue |
|---|---:|---:|---|
| 0x020913bc | 376 | 27 | push {r5, r6, lr} |
| 0x02091534 | 376 | **17** | push {r5, r6, lr} |
| 0x020916ac | 476 | 27 | push {r5, r6, fp, lr} |
| 0x020919fc | 460 | 27 | push {r5, r6, fp, lr} |

0x02091534 is the odd one (17 halvings) = a different filter variant. None of the four is reached
by any `bl` inside the blob — they are dispatched by table or computed branch.

### ⚠ The "offset table" at blob+0x04 is NOT established as one

The port's handoff read blob+0x04.. as an offset table of block-type entry points, on the grounds
that every value is < 0x659c and therefore blob-relative. **That inference does not hold**, and
three checks argue against it:

1. `+0x04 = 0x100` (256) and `+0x08 = 0x9e` (158) are plainly not offsets — they look like
   dimensions.
2. The values that *are* in blob range land on **function TAILS, not entries** — checked 3/3:
   `0x49e8` -> `strb; strb; mov pc,lr`; `0x4a04` -> `subs r2,r2,#1; bne; mov pc,lr`;
   `0x4c20` -> `subs r2,r2,#2; bne; pop {r5,r6,pc}`.
3. **The entry does not read it.** blob+0x16f0 (RAM 0x0208dfb4) takes the *frame struct* in r0 and
   reads `[r0]` (bitstream), `[r0,#4]`, `[r0,#0x3c]`, `[r0,#0x3b4]`, `[r0,#0x3c4]` — never
   blob+0x04. The `b` at blob+0 jumps the region and nothing here touches it.

Unresolved oddity worth keeping: **four table values sit exactly 0xc before a `push` prologue**
(0x4aec/0x4af8, 0x4c64/0x4c70, 0x4ddc/0x4de8, 0x512c/0x5138) — and 0xc is exactly the length of
the `subs/bne/mov pc,lr` tail. That is either a real base-plus-delta dispatch or a coincidence of
uniform function tails. **Not resolved.** Resolving it needs the code that reads the region, or
the ITCM trace.

### Blob entry — blob+0x16f0 (RAM 0x0208dfb4)

```
16f4: ldr  r1, [r0]        ; r0 = frame struct; r1 = bitstream ptr
16fc: ldrh r3, [r1], #2    ; read a u16, advance
1700: lsl  r3, r3, #16
1704: adds r3, r3, r3      ; test the top bit via carry
1708: bcs  0x181c
173c: ldr  ip, [r0, #4]    ; zero-fill loop over (ctx[4] + 32) bytes in 16-byte steps
```
