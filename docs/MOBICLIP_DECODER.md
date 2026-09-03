# ov024 MobiClip decoder payload

## Scope and reproducibility

ov024 contains a position-independent executable payload inside its initialized
data range. The project does not distribute those original bytes. Contributors
with their own extraction can reproduce the local analysis file with:

```text
python tools/mobiclip_payload.py
```

The default output is
`scratch/mobiclip/data_ov024_0208c8c4.bin`; `scratch/` and `*.bin` are ignored.
For the currently supported ROM the helper verifies:

- overlay base: `0x02082960`
- payload range: `0x0208c8c4-0x02092e60` (end-exclusive, `0x659c` bytes)
- payload SHA-256: `5508ae5f765eb86e81b2ad8d76dccf6d4a30e3381d3e8b248fb8d4a6204b83f5`
- ARM trampoline word: `0xea0005ba`
- decoded entry: `0x0208dfb4` (`base + 0x16f0`)

## Confirmed static layout

The payload starts in ARM mode. Its first instruction branches over a compact
header to the frame decoder. The two words at offsets `+0x04` (`0x100`) and
`+0x08` (`0x9e`) are intentionally left unnamed until their semantics are
proven. The remaining header is two independent 16-entry tables of relative
ARM dispatch targets: luma at `0x0208c8d0` and chroma at `0x0208c910`. Each
offset is relative to the start of its own table. Separate `adr`/`ldr`/`add pc`
sequences at `0x0208c9b0` and `0x0208c9f0` prove the two bases.

The first two carved functions in the shared Ghidra program are:

- `0x0208c950`: `MobiClip_PredictMotionBlock`
- `0x0208dfb4`: `MobiClip_DecodeFrameCore`

`MobiClip_PredictMotionBlock` reads two encoded values through the routine
at `0x0208e93c`, combines them with state at `+0x3bc`, and selects interpolation
paths using the separate luma and chroma tables. `MobiClip_DecodeFrameCore` accesses the
bitstream cursor at `+0x00`, dimensions at `+0x04/+0x08`, decode tables at
`+0x3c/+0x40`, and quantizer/motion state beginning at `+0x3b4`. Direct callees
currently visible include `0x0208e928`, `0x0208e93c`, `0x02091218`, and
`0x0208cb70`.

The external call chain is also confirmed: `func_ov024_02086620` copies or
returns the payload and its caller stores the result at owner offset `+0x38`;
`func_ov024_020859d4` later invokes that pointer with the decoder state kept at
owner offset `+0x34`.

## Progress accounting and next analysis

The whole payload remains unmatched DATA. Extraction, Ghidra carving, names,
or preserving it as a blob do not increase progress. `tools/data_progress.py`
classifies it separately as `mobiclip_payload`; matched bytes will require a
source reconstruction plus byte-and-relocation verification.

The initial bit-reader and direct-callee targets described below are now
complete. Dynamic work should still capture the `0x454`-byte decoder state and
referenced frame buffers immediately before and after one frame so later
semantic C/C++ can be checked byte by byte.

## Recovered bitstream and P-frame core

The first static targets have now been identified and saved in the shared
Ghidra program. The register-oriented helpers use a private calling convention:
`r1` is the advancing `uint16_t` cursor, `r2` is the remaining-bit count, `r3`
is an MSB-aligned reservoir, and decoded Golomb values are returned in `r6`.

- `0x0208e8f8`: `MobiClip_ReadUnsignedExpGolomb`
- `0x0208e928`: `MobiClip_RefillBitReservoir16`
- `0x0208e93c`: `MobiClip_ReadSignedExpGolomb`
- `0x02091218`: `MobiClip_SetupQuantTables`
- `0x0208cb70`: `MobiClip_DispatchPFrameMacroblock`
- `0x0208cdc8`: `MobiClip_PredictMotion8x16`
- `0x0208d34c`: `MobiClip_PredictMotion16x8`
- `0x0208e364`: `MobiClip_AddPFrameMacroblockCoefficients`

The signed Golomb helper implements the standard odd/even `get_se_golomb`
mapping. The unsigned helper at `0x0208e8f8` shares the same CLZ-based prefix
decoder and subtracts one from the code number. Both tail into the 16-bit refill
helper when the local bit count becomes negative.

`MobiClip_SetupQuantTables` proves that state `+0x3b4` is the current quantizer.
For the valid six-bit stream range QP 12-53 it selects one of six base matrices using QP modulo 6 and
left-shifts it using floor(QP / 6). It builds the 8x8 table at state `+0x74` and
the 4x4 table at `+0x174`. This is the same algorithm and table family used by
FFmpeg's `setup_qtables` implementation of MobiClip.

The P-frame mode decoder uses three adjacent tables:

- `0x0208ca44`: 32-entry top-five-bit prefix-to-mode table
- `0x0208ca64`: ten offsets relative to the table base
- `0x0208ca8c`: ten VLC bit lengths

All ten relative destinations now have explicit DATA references and functions
in Ghidra. Modes 0-5 select predicted/reference-frame motion; mode 6 decodes an
intra macroblock, mode 7 decodes an intra macroblock with predicted modes, mode
8 uses two stacked 16x8 motion partitions, and mode 9 uses two side-by-side
8x16 partitions. The residual-mask table at `0x0208e324` maps an unsigned
Exp-Golomb value to six flags: four luma 8x8 blocks and two chroma blocks.

## Coefficients and inverse transforms

The coefficient path and its scratch layout are now statically proved:

- `0x02090860`: `MobiClip_DecodeRunLevelCoefficients`
- `0x0208e8a8`: `MobiClip_AddCoefficients4x4`
- `0x0208e6f0`: `MobiClip_AddPFrameBlockCoefficients`

The run/level decoder reads packed VLC symbols through the active table at
state `+0x3b8`. An entry in the active quant/scan table stores the destination
coefficient index in its low byte and its inverse-quantization multiplier in
the upper bits. The decoder writes `level * (entry >> 8)` to that indexed
coefficient slot.

`MobiClip_AddCoefficients4x4` clears 16 coefficients, performs the separable
4x4 inverse transform, adds the prediction and clamps the reconstructed output.
`MobiClip_AddPFrameBlockCoefficients` selects either one 8x8 residual or as many
as four 4x4 residuals from its Golomb-coded mask; its 8x8 path clears 64
coefficients and performs the 8x8 inverse transform.

Consequently state `+0x1b4-0x3b3` is exactly 128 signed 32-bit scratch values.
The 8x8 path uses 64 coefficients followed by 64 intermediate values. The 4x4
path uses the first 16 coefficient values followed by 16 intermediate values.

## Intra prediction and motion interpolation

The predicted intra-mode path is carved as:

- `0x0208e5a0`: `MobiClip_DecodePredictedIntraMode`
- `0x0208e5f8`: `MobiClip_ProcessPredictedIntraBlock`
- `0x0208e97c`: `MobiClip_PredictDeltaPlane16x16`
- `0x0208ee8c`: `MobiClip_PredictDeltaPlane8x8`
- `0x02090058`: `MobiClip_PredictDeltaPlane4x4`

The 20-entry relative table at `0x0208e4dc` contains prediction modes 0-9 for
8x8 blocks followed by modes 0-9 for 4x4 blocks. The coefficient-mask tables
at `0x0208e6b8` and `0x0208e788` select direct 8x8 residuals or 4x4 sub-block
masks for intra and P-frame paths respectively.

All interpolation code through the end of the payload has also been classified
as executable ARM code. The luma table selects 16-byte-wide kernels for eight
horizontal phases and integer/half-pixel vertical phases. The chroma table does
the same for 8-byte-wide kernels. Additional width-4, width-2 and width-1
specializations use 16, 8 and 4 entry points. Literal `0x7f7f7f7f` masks at
`0x02091e4c`, `0x020925f8`, `0x02092af4` and `0x02092d88` prevent packed
averaging carries from crossing byte lanes.

## Partial decoder-state type

Ghidra now contains `/khdays/mobiclip/MobiClipDecoderState`, exactly `0x454`
bytes, plus the eight-byte `MobiClipMotionVector`. The currently proven fields
are:

| Offset | Field | Evidence |
| ---: | --- | --- |
| `0x000` | `bitstreamStart` | frame decoder initializes its local cursor here |
| `0x004` | `width` | 16-pixel macroblock loop bound |
| `0x008` | `height` | 16-pixel macroblock loop bound |
| `0x00c` | `lumaHistory[6]` | reference-frame selection |
| `0x024` | `chromaHistory[6]` | reference-frame chroma selection |
| `0x03c/0x040` | coefficient-table variants | selected by the frame header |
| `0x044` | `clampTable` | reconstruction clamp lookup |
| `0x048` | `formatVariant` | frame-header format/coefficient variant |
| `0x04c` | `predictionModes[0x28]` | prediction cache and border sentinels |
| `0x074` | `quantScan8x8[64]` | packed scan index and inverse-quantization multiplier |
| `0x174` | `quantScan4x4[16]` | packed scan index and inverse-quantization multiplier |
| `0x1b4` | `transformWorkspace[128]` | coefficient and inverse-transform scratch values |
| `0x3b4` | `quantizer` | absolute I-frame QP or P-frame delta result |
| `0x3b8` | `coefficientTable` | active table pointer |
| `0x3bc` | `predictedMotion` | median-predicted motion vector |
| `0x3c4` | `motion[18]` | per-column motion history and border slots |

These fields and the carved functions are analysis evidence, not matched DATA.
The remaining completion gate is a semantic source reconstruction checked
against emulator captures and an exact byte-and-relocation verifier. Until
that exists, the honest MobiClip and global DATA percentages remain zero.

## Semantic transform oracle

`tools/mobiclip_reference.cpp` and its header contain the first isolated C++
reconstruction: packed quant/scan unpacking, 4x4 and 8x8 inverse transforms,
residual addition and byte clipping. It deliberately uses a general separable
transform instead of reproducing the ARM routine's sparsity specializations.

`tools/mobiclip_reference.py` implements the same semantics as a test oracle.
It accepts a JSON object with `size`, `coefficients` and an optional
`prediction` array:

```text
python tools/mobiclip_reference.py scratch/mobiclip/capture.json
```

The output contains the signed residual and, when a prediction was supplied,
the clipped reconstructed block. This is scaffolding for emulator comparison;
it neither embeds payload bytes nor advances DATA progress.

`tools/mobiclip_capture.lua` is the matching one-shot DeSmuME capture script.
Create `scratch/mobiclip/captures`, load the script from DeSmuME's Lua window
and start a cutscene. The script hooks the stable call at `0x02085a20` and its
return at `0x02085a24`, accepting either the ITCM payload at `0x01ff9a64` or
the overlay fallback at `0x0208c8c4`. It writes:

- the complete decoder state before and after one frame;
- the compressed input window and all non-null luma/chroma history planes;
- one 4x4 and one true 8x8 transform capture containing coefficients,
  prediction bytes and observed reconstructed bytes.

Pass either transform JSON back to `mobiclip_reference.py`. The result includes
`matchesObserved` and exact `mismatchIndices`, which provides the intended
byte-level transform oracle without committing any game data.
