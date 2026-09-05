# ov024 MobiClip decoder payload

## Scope and reproducibility

ov024 contains a position-independent executable payload inside its initialized
data range. The project does not distribute those original bytes. Contributors
with their own extraction can reproduce the local analysis file with:

```text
python tools/mobiclip_payload.py
python tools/mobiclip_inventory.py
python tools/mobiclip_semantic_data_probe.py
python tools/mobiclip_control_metadata_probe.py
python tools/mobiclip_mods.py
python tools/mobiclip_frame_verify.py
```

The default output is
`scratch/mobiclip/data_ov024_0208c8c4.bin`; `scratch/` and `*.bin` are ignored.
For the currently supported ROM the helper verifies:

- overlay base: `0x02082960`
- payload range: `0x0208c8c4-0x02092e60` (end-exclusive, `0x659c` bytes)
- payload SHA-256: `5508ae5f765eb86e81b2ad8d76dccf6d4a30e3381d3e8b248fb8d4a6204b83f5`
- ARM trampoline word: `0xea0005ba`
- decoded entry: `0x0208dfb4` (`base + 0x16f0`)

The second command verifies the same hash and performs recursive ARM traversal
from the Ghidra-validated entries, direct branches and all relative dispatch
tables (including reserved zero slots and signed backwards offsets). Its current
exact split is:

- `0x5c2c` bytes / 5899 instructions of reachable ARM code;
- `0x0970` bytes in 39 embedded-data regions;
- `0x659c` classified bytes in total, with no uncovered byte.

The ignored output is `scratch/mobiclip/mobiclip_inventory.json`. The tool has
an explicit region audit and fails if control-flow discovery disagrees with the
proven data map. Computed writes to `pc` terminate a path, while continuations
synthesized through `lr` are seeded explicitly; this prevents inline dispatch
tables from being mistaken for conditional ARM instructions.

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

## Progress accounting and integration

The whole payload is now matched in the separate `mobiclip_payload` DATA
category. Extraction, Ghidra carving, names, or preserving it as a blob still
contribute zero by themselves; the counted source is the mnemonic ARM and
typed/symbolic DATA reconstruction in
`src/overlays/ov024/data/mobiclip_payload.s`, admitted only through the strict
executable-payload verifier and the real ov024 build.

A compiler probe also established the intended reconstruction route: the
project's MWCC can place ordinary C functions in a `.data` section with
read/write/execute flags while retaining function symbols. Therefore this
payload can be rebuilt as semantic C plus typed tables in its original section;
neither an `incbin`, inline opcodes nor a permanently opaque blob is required.
This is a capability result only and does not itself count any matched bytes.

`tools/mobiclip_semantic_data_probe.py` closes the compiler half for the
recovered constants. It generates ordinary C declarations in ignored scratch,
compiles them with MWCC into per-symbol `.mobiclip_semantic` sections, reads
the duplicate-named ELF sections by symbol, and compares each symbol directly
with the original payload range. Fourteen regions totaling 848 bytes match
exactly; every emitted section has ELF flags 7 (write, allocate, execute).

`tools/mobiclip_control_metadata_probe.py` closes the other 1568 embedded-data
bytes. MWCC rejects a C initializer of the form `target - table` as a constant
expression, so the tool emits symbolic tables with GNU `as`. Each non-reserved
entry carries `R_ARM_REL32`; the real project `mwldarm` resolves those symbols
at their retail addresses. The 25 linked region binaries then compare exactly
with the extracted payload, including 209 unique code targets, signed backwards
offsets, cross-table relative bases and reserved zero slots. Thus all `0x970`
embedded-data bytes now have
a semantic, reproducible byte proof. Those definitions are now interleaved in
the integrated source, and the resulting ov024 image passes the project module
checker byte for byte.

The initial bit-reader and direct-callee targets described below are now
complete. A DeSmuME run has also captured the complete `0x454`-byte decoder
state and all referenced frame buffers immediately before and after a real
P-frame. The semantic decoder reproduces that ARM execution byte for byte; the
replay details and commands are recorded below.

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

The two source tables are contiguous, independent 0x2100-byte objects:

- 0x020886c4: format variant 1
- 0x0208a7c4: format variant 0

Each contains 4096 little-endian uint16_t prefix entries followed by 256
residue bytes. In a packed entry, bits 0-3 are the total consumed bits
(including the coefficient sign), bits 4-8 are the level magnitude, bits 9-14
are the run, and bit 15 is last. MobiClip_DecodeRunLevelCoefficients recognizes
the seven-bit prefix 0000011 before the ordinary 12-bit lookup. Its next
selector bits choose level extension, run extension, or a full escape with a
one-bit last, six-bit run and signed 12-bit level. The level/run extension paths
apply the appropriate 64-byte residue quadrant before applying the sign bit.
This is now implemented independently in the semantic C++ and Python
references.

`MobiClip_AddCoefficients4x4` clears 16 coefficients, performs the separable
4x4 inverse transform, adds the prediction and clamps the reconstructed output.
`MobiClip_AddPFrameBlockCoefficients` selects either one 8x8 residual or as many
as four 4x4 residuals from its Golomb-coded mask; its 8x8 path clears 64
coefficients and performs the 8x8 inverse transform.

Consequently state `+0x1b4-0x3b3` is exactly 128 signed 32-bit scratch values.
The 8x8 path uses 64 coefficients followed by 64 intermediate values. The 4x4
path uses the first 16 coefficient values followed by 16 intermediate values.

## Intra prediction and motion interpolation

The main P-frame loop computes a component-wise median from the left,
upper-left and upper motion vectors and stores it at state offset 0x3bc.
MobiClip_PredictMotionBlock then reads two signed Exp-Golomb deltas in x/y
order, adds them to that prediction and records the resulting vector before
selecting its luma/chroma interpolation phases. Both steps are implemented in
the isolated C++ and Python references.

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

## Native frame layout and RGB555 presentation

Static tracing now confirms that the payload reconstructs native YCoCg rather
than planar YUV. The decoder owns six historical luma pointers at state offset
0x0c and six historical chroma pointers at offset 0x24. Every luma allocation
has a fixed 256-byte row stride. Each chroma row is also 256 bytes: Co samples
occupy bytes 0..127 and Cg samples occupy bytes 128..255, with one Co/Cg pair
shared by a 2x2 luma group.

The owner-side ring at offset 0x64 does not contain decoded-plane pointers. It
records the quantizer from decoder state offset 0x3b4 for each completed frame.
MobiClip_EmitFrame selects the current luma/chroma ring entries and calls
MobiClip_YCoCgToBgr555 at 0x02086004. Its inverse color equations are:

    R = clip5(Y + Co - Cg)
    G = clip5(Y + Cg)
    B = clip5(Y - Co - Cg)

The output is Nintendo DS RGB555 with bit 15 set. The hand-unrolled ARM routine
converts a 2x2 luma group per chroma sample and subtracts four from luma in a
checkerboard pattern: odd columns of the first row, then even columns of the
second. The semantic reference preserves this easy-to-miss bias.

The C++ and Python references now implement this complete presentation step.
The DeSmuME capture script records the native planes and the produced RGB555
surface around the converter, and the Python CLI compares every visible pixel
plus SHA-256 hashes while ignoring destination-row padding.

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

These fields and the carved functions are analysis evidence; the matched claim
comes from the independently verified source and integrated build. The
standalone semantic reconstruction decodes complete real streams and matches a
captured original-ARM P-frame. The production gate is now closed: ov024 and all
306 project modules pass, MobiClip contributes exactly 26012 matched DATA
bytes, and initialized-DATA progress is 94418/188336 bytes (50.13%).

## Semantic transform oracle

The isolated C++ reconstruction now includes the word-oriented bit reader,
unsigned/signed Exp-Golomb, the complete packed run/level VLC frontend and its
three escape forms, run/level placement and dequantization, packed quant/scan
construction, 4x4 and 8x8 inverse transforms, residual addition, byte clipping,
intra prediction, recursive motion compensation, complete I/P frame decode and
RGB555 presentation. Its allocation-free frame API takes caller-owned output,
history, coefficient-table and motion-workspace buffers, so it can serve both
host validation and the eventual Nintendo DS integration.

`tools/mobiclip_reference.cpp` and its header contain the first isolated C++
reconstruction and deliberately uses a general separable transform instead of
reproducing the ARM routine's sparsity specializations.

`tools/mobiclip_reference.py` implements the same semantics as a test oracle.
It accepts a JSON object with `size`, `coefficients` and an optional
`prediction` array:

```text
python tools/mobiclip_reference.py scratch/mobiclip/capture.json
```

The output contains the signed residual and, when a prediction was supplied,
the clipped reconstructed block. This is scaffolding for emulator comparison;
it neither embeds payload bytes nor advances DATA progress.

The Python oracle now also reconstructs complete I- and P-frames. It implements
all sixteen compact motion-mode VLC contexts, recursive 16/8/4/2 block
partitioning, six-frame history selection, half-pixel motion compensation,
intra macroblocks and both residual partition schemes. `tools/mobiclip_mods.py`
extracts a named `.mods` member from NitroFS into ignored scratch and validates
the N2/N3 header plus every packet boundary. `tools/mobiclip_frame_verify.py`
then decodes packets with the reconstructed oracle and compares planar YCoCg
byte-for-byte against the independent FFmpeg decoder, reordering the two MODS
chroma planes explicitly. The complete `mv/802.mods` stream matches exactly:
4485/4485 frames (178 I + 4307 P at 256x160), quantizers 17 through 27, and
53,895,145 consumed video bits were checked without a differing output byte.
Six more complete streams (`808` and all five localized `839_*` files) also
match, bringing the cross-stream total to 4859 frames (184 I + 4675 P). The
audio-free `839_*` packets prove the final-word edge case: frame entry adds the
same safe zero look-ahead used by the native caller/FFmpeg, while the standalone
bit-reader API remains bounds-strict.

This end-to-end semantic result is stronger than a transform-only synthetic
test. Together with the mnemonic-source gate and exact ov024 module build it
now supports the official MobiClip DATA claim.

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

The capture script also hooks MobiClip_DecodeRunLevelCoefficients at source
0x02090860 and ITCM 0x01ffda00. Its first hit writes
frame_NNNN_vlc_0001.json with the incoming/outgoing r1/r2/r3 state, the next 32
refill words, the selected packed quant/scan table and the final coefficient
block. Replay it with the matching locally extracted VLC table:

    python tools/mobiclip_reference.py ^
      scratch/mobiclip/captures/frame_0001_vlc_0001.json ^
      --vlc-table scratch/mobiclip/coefficient_table_0_0208a7c4.bin

The result independently reports both matchesRegisterState and
matchesCoefficients. The complete MODS comparison closes the portable semantic
path, and the nontrivial P-frame capture closes the original-ARM emulator gate.
The integrated ov024 build now closes the remaining production gate.

The same run also writes a frame_NNNN_color_0001.json manifest around the
owner-side color converter. Replay it directly:

    python tools/mobiclip_reference.py scratch/mobiclip/captures/frame_0001_color_0001.json

The report contains matchesObserved, mismatchCount, mismatchIndices and the
expected/observed visible-pixel SHA-256 values.

### Original-ARM P-frame replay

The retained local capture in `scratch/mobiclip/captures` is decoder call 31,
not the trivial first I-frame. It starts at bitstream address `0x0233d158`,
uses the ITCM payload at `0x01ff9a64`, and decodes a 256x160 P-frame. The ARM
decoder advances 3638 bits and returns 456 bytes after word rounding; its QP
changes from 26 to 27 and selects coefficient-table variant 0.

Replay the complete captured call with:

    python tools/mobiclip_capture_verify.py ^
      scratch/mobiclip/captures/frame_0001_manifest.json

The semantic result matches the ARM decoder's complete current luma and packed
native chroma planes, all persistent state fields, and the unchanged history
planes 1 through 5. The exact plane hashes are:

- luma: `c4e27198d0540a7a3bb68f1e1dce88f2581a1c8fa174aa791da039190a678607`
- native packed chroma: `4b764f5d1b553d6c46a3be45362f6d9fafe7e9d51717573ef063ca6f6c8a5ea0`

The same call supplies real VLC, 4x4 transform, 8x8 transform, and RGB555
sub-captures. All four replay exactly. RGB555 exposed the converter's
checkerboard `-4` luminance bias, which is now represented in both semantic
implementations; visible output on both sides hashes to
`f9acf1f031fe1378bb2f6e61e38eff711ef21245281d2b84f297d3253a61b232`.
The corrected C++ reference also compiles cleanly with the project's MWCC
3.0 patch 4 configuration. A native host harness then runs that C++ decoder on
the same captured P-frame and reports `lumaMatch=1`, `chromaMatch=1`,
`stateMatch=1`, and `bitsConsumed=3638`. A second streaming harness decodes all
4485 frames of `802.mods` with its real six-frame history rotation and matches
FFmpeg byte for byte: 178 I-frames and 4307 P-frames.

### Saved standalone Ghidra program

The raw payload has been imported into an isolated Ghidra project at
`scratch/mobiclip/ghidra/MobiClipPayload.gpr`; the shared `days.nds` program is
not opened or modified by this workflow. `tools/ghidra/MobiclipCarve.java`
recreates the carving from `mobiclip_inventory.json`, and
`tools/ghidra/MobiclipAudit.java` verifies the saved result in read-only mode.
The audited program uses `ARM:LE:32:v5t`, maps memory at
`0x0208c8c4..0x02092e5f`, and contains 5899 instructions (23596 bytes), 2416
defined DATA bytes and 257 discovered/seeded functions.

### Exact mnemonic assembly candidate

`tools/mobiclip_assembly_probe.py` renders every one of the 5899 carved ARM
instructions as a mnemonic with a stable address label. The 39 embedded DATA
regions are interleaved as named semantic/control tables; internal dispatch
entries use symbolic relative expressions and the only numeric words are
proved reserved zero entries. No payload bytes, `incbin`, `.inst` directives or
numeric opcode words are used for code.

The resulting `.rodata` is exactly `0x659c` bytes and hashes to
`5508ae5f765eb86e81b2ad8d76dccf6d4a30e3381d3e8b248fb8d4a6204b83f5`.
`tools/verify_executable_data.py` additionally passes the object through the
project MWLD partial-link path and proves that all bytes remain unchanged. The
generated source now owns `0x0208c8c4..0x02092e60` through ov024's normal
delink/build path. `dsd check modules -f` reports every module OK, and the
public report exposes `MobiClip executable payload` as 26012/26012 (100%).
