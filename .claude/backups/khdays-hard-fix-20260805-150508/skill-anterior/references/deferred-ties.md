# Deferred ties — do NOT retry (route to nonmatching/ or skip)

These are mwccarm-3.0/139 codegen behaviors that no C source form has been found to reproduce. If a
DIFIERE matches one, stop iterating on steers, run SKILL.md's **pre-park checklist**, and only then
route to `nonmatching/` (if it's a wired stub) or skip the candidate.

## ⚠ Read this before trusting anything below

**This file's own track record is poor, and its purpose — saving cycles — is exactly what makes it
dangerous.** A listed tie is a reason to stop trying *steers*; it is never a reason to skip the
checklist. Two corrections, both from real damage:

- **The RNG `add r0,r0,#0` entry was WRONG** and blocked ~155 functions. The census behind it
  grepped one of the pattern's two spellings and counted `asm_stubs` blobs as matches. It is now
  cracked (`f(n) + (v - v)`, below).
- **2026-07-17: FIVE functions filed under "regalloc swap" / "scheduling tie" / "register-coloring
  tie" were dropped ARGUMENTS** — `ov212_020ce0d4`, `ov115_020ce20c`, `ov256_020cd8f0`,
  `ov007_0204d23c`, `ov000_020593f4`. One had ten ruled-out variants; one had **25 mwcc builds**
  tried against it. A dropped *trailing* argument does not change the size, so it presents as a
  constant sitting in the wrong register — i.e. precisely as a register-allocation tie.

- **2026-07-21: BOTH ov010 parks fell**, and they were the most heavily defended entries this file
  ever had — between them all five build-lines, 25 builds, the -O/pragma matrix, an 81k-iteration
  AST permuter, the `register` axis and the struct-typing axis. `0204cac0` was a **non-void return
  type** (the ROM returns the loaded `ResFile *`, which reserves r0 and forces the surviving
  `offset` to r2 — declared `void`, no rewriting of the body can ever undo that). `0204cb3c` was
  **open-coded MMIO where the original called `static inline` helpers**. Every failed attempt on
  both had varied the BODY.

So: **"regalloc swap", "read-order", "scheduling tie" and "register-coloring tie" are NOT
diagnoses.** They are what a missing parameter, a dropped return type, or an open-coded inline
looks like. Before filing anything under them, run `python tools/audit_arity.py`, check the
callee's real arity in the tree, and ask the two signature questions:
**does this function return something?** and **was this block an inline helper?**

- **"No mwcc build reproduces it" is testable in one command, so it is never admissible untested:**
  `python tools/build_sweep.py <func>` compiles against all 27 builds in `tools/mwccarm/`. One of
  the five above had **25 builds** tried against it and was still a dropped argument — the sweep
  answers the build question, it does not answer the *is-my-C-right* question. Feed it only C whose
  size and instruction stream already match. See `references/tools.md`.

**Phrases like "unreachable", "no source form works", or a long list of ruled-out variants are not
evidence** — every one of the five above carried some version of that. And **when a listed tie turns
out to be wrong, fix the entry here**; leaving it costs the next session the same day it cost this
one.

## Instruction-selection ties

- **mvn-literal 0xffff**: mwcc emits `ldr rX,[pc]`+pool for `0xffff`, never
  `mvn rX,#0`. No C spelling works. (ov046/065/084/101 246B strh loop.)
- **fold-aggressive add+strb**: mwcc fuses `add r1,#0x100` + `strb [r1,#0x1c7]` into
  `strb [r1,#0x2c7]`. (ov219/220/239/276/285/286/139/140/204/205.) NOTE: the
  struct-field-forces-direct-strb crack (codegen-cracks.md) fixes the RELATED
  dispatcher case — try that first; the pure fold above is the residual tie.
- **pool-load of an ENCODABLE immediate** (`ldr r4,=0x1c`): means the source used a
  linker-absolute SYMBOL. The overlay-id case is SOLVED (`(u32)&OVERLAY_<n>_ID`
  inline). Other linker-absolute constants with no dsd symbol → nonmatching.
- ~~**hw60 `->hi |= K`**: adds a redundant lsl/lsr mask, +8B.~~ ★ CRACKED 2026-07-18
  (func_ov210_020d1584 x3): the `hi:8` **bitfield** `|=` adds a redundant 16-bit mask, but the
  explicit-shift form (the same one the `&= ~K` write-back uses, cf. func_ov123_020cd484) matches:
  `*hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | K) << 0x18) >> 0x10);` with
  `unsigned int h = *hw;`. So `|=` is not a tie — it's a "don't use the bitfield type" case. Now in
  codegen-cracks.md.
- ~~**`ldm`-args coalescing**: passing 3 consecutive struct fields as call args — the
  ROM uses `ldm`, mwcc uses 3 separate `ldr`. (ov199_020d4e64.)~~ ★ CRACKED 2026-07-17
  (func_ov198_020d184c x5): pass the vector as a **STRUCT BY VALUE**, not three `int` args. The
  callee still receives three register args (same ABI), but mwcc loads the source with one `ldm`
  matching the ROM. `f(state, aim[0], aim[1], aim[2], 0)` -> three `ldr`; `f(state, aimStruct, 0)`
  with `aimStruct` a 3-int struct -> `ldm`. Revisit ov199_020d4e64 with this.
- **consecutive-value equality → range-check**: `s==8 || s==7` (consecutive) →
  mwcc `(unsigned)(s-7)<=1` vs the ROM's `cmp #8; cmpne #7`. (020ceee4.) The
  double-negation crack helps for LONGER runs but not this 2-value case.

## Register-allocation / coloring ties (same insns, swapped regs)

- ~~**r0/r1 entry-reload** on the pure 72B c5c0 spawn (only `*entry=self`).~~ **CRACKED
  2026-07-18 — worth 24 functions.** The caller returns c5c0's result (`int f(...)` +
  `int rc = func_0203c5c0(...); ...; return rc;`), which keeps r0 live across the out-param load
  and forces it into r1 at zero instruction cost. Full entry in `codegen-cracks.md`.
- **self=r4/owner=r5 vs r5/r4** global swap (when the decl-order crack doesn't fix it).
- **node reg ip vs r3** (020ce448 — reschedules the following const stores).
- **struct-copy >16B ip↔lr swap**: mwcc's ldm!/stm! writeback colors src→ip,dst→lr;
  origins use the opposite. 4-word single ldm/stm copies are fine.
- **temp-reg r1/r2 vs r3** on double-load-across-branch wrappers (the `volatile` cast
  fixes the load COUNT but not the reg pick). (func_0201a284, 0201a124.)
- **const-1 store reg** (r1 vs r0) — 020ccdf4 residual.
- **★ N-values-2-registers spill ROTATION (decl order does NOT drive it)** — 2026-07-16,
  `func_ov024_02083368` (THUMB) and `func_ov024_02083600` (ARM). When more live values compete
  than there are free registers, mwcc picks *which* value spills and the whole assignment comes
  out as a rotation of the ROM's. 02083368: three handles, only r4/r7 free (r5/r6 hold the args)
  — ROM spills the LAST (h0→r7, h1→r4, h2→[sp]), mwcc spills the MIDDLE (h0→r4, h1→[sp], h2→r7).
  Same size, same instructions, same prologue, permuted regs.
  **The decl-order crack does not apply to THIS shape**: when the values compete for scratch
  registers and one must spill, the allocation follows FIRST USE, so reordering the decls (and the
  init statements) changes nothing. Tried both orders on both functions — identical diff.
  Diagnostic: if the first diff is a register field and the prologue is byte-identical, it's this.

  ⚠ **But do try decl order first — it is not dead.** `func_ov024_0208437c` (2026-07-16) was the
  same-looking symptom (three values rotated by one register: pending→r4:r5/i→r6 instead of the
  ROM's pending→r5:r6/i→r4) and swapping `unsigned long long pending; int i;` to
  `int i; unsigned long long pending;` matched it instantly. The distinction that predicts it:
  - values living in **callee-saved** registers across the whole function → decl order DRIVES it, try it.
  - values fighting over **scratch** registers with a spill (the 02083368/02083600 shape) → first-use
    wins, decl order is inert, route.

## ★ THUMB 0/1 boolean-return layout canonicalisation (2026-07-16, func_ov024_020833dc)

A comparison-fed `return 0/1` at the tail of a THUMB function: mwcc **canonicalises it and picks
the block layout itself**, ignoring the source form entirely. ROM wants
`cmp r0,r4 ; bge L ; movs r0,#0 ; pop ; L: movs r0,#1 ; pop` (return 0 inline); mwcc always emits
the mirror (`blt L ; movs r0,#1 ; pop ; L: movs r0,#0 ; pop`).

**Do not spend cycles — all four of these compile identically:**
`if (a >= b) return 1; return 0;` · `if (a < b) return 0; return 1;` · `return a >= b;` ·
`if (a >= b) goto L; return 0; L: return 1;` (goto defeats range-opt elsewhere, not this).

The ordinary "negate to flip which block is inline" crack does NOT apply to a 0/1 return, and the
"preset the flag" crack is ARM-predication-only (THUMB has no moveq/movne). Non-comparison-fed
`return 0`/`return 1` blocks earlier in the same function come out fine — it is specifically the
one fed by the final `cmp` that gets normalised.
Diagnostic: byte-exact everywhere, last branch is `blt` where the ROM has `bge` (or vice versa)
and the two `movs r0,#N` are swapped.

## ★ Divide-by-constant smull ordering (ov142/ov143 aim-and-rate families, 10 funcs)

`state[N] = (owner delta) * 0x1e / K` where the ROM emits the signed divide as:
```
mul   r3, r1, r0        ; x*30
lsr   r0, r3, #0x1f     ; sign bit -- BEFORE the smull
smull r1, r3, r2, r3    ; overwrites x*30 (r3 is both input and hi output)
add   r3, r0, r3, asr #s
```
The sign bit is computed first BECAUSE the smull reuses the input register (r3). mwcc schedules
the smull FIRST into fresh registers (preserving x*30), then the sign bit -- a permutation, same
instruction count, diff pinned at the `mul`. It is the smull's destination-register choice, fixed
by mwcc's divide-by-constant generator.

★ **The divide FORM is not the problem and is worth getting right anyway** (these vary per family):
- `/ K` (plain) emits the correct single `smull`. Read the magic to get K: 0x66666667 asr#1 = /5
  (ov142/ov143), asr#3 = /20 (ov182); 0x55555556 no-shift = /3 (ov195, which MATCHED because its
  division sits at the function head with different register pressure).
- Do NOT write `* 30 / K` as the algebraic `* (30/K)` -- and do NOT expand it manually as
  `((unsigned)v>>31) + ((long long)MAGIC * v >> shift)`: that makes mwcc treat MAGIC as a 64-bit
  constant and emit a full `umull`+`mla` 32x64 multiply (+2 instructions). Confirmed on ov143.
- Base is `*self` (the OWNER, self[0]), not `state` (self[1]) -- Ghidra prints `*param_1`.

So: the aim/atan2/scale body around it is byte-exact; only the smull ordering ties. When the
division is at the function HEAD (ov195) it can match; at the TAIL (ov142/ov143) it does not. Route
tail-division members to nonmatching, but SOLVE the body first so the file is one instruction away.

## Scheduler ties (same insns, 1-2 reordered)

- **guard-block fall-through operand hoist** (c0b90 family, ov166_020cdb50,
  ov115_020ce20c): ROM hoists the fall-through guard's leading loads above the `bne`;
  proven across 26 mwcc gens × 7 source forms × 6 pragmas. DO NOT retry.
- **unroll-by-4 clear-loop** (ov290/300_020cbf38): scheduler hoists the counter `sub`
  between the strb stores. Blocks the two overlays closest to 100%.
- **constant-materialization slot** (ov008_0205f944, and the 0x14000 fold vs
  `add r3,#0xf000` reuse in 020ce4e0): mwcc places a `mov`/immediate one slot off, or
  folds an encodable constant into a `cmp #imm` where the ROM reuses a live register.
- **counter-branch operand hoist** (020ce19c): ROM hoists `*(owner)` + `mov r2,#0`
  above a `>=N` branch.
- **atomic-hpair WITH a preceding anim** (020d032c/020d02c4): the two halfword reads
  come out in the opposite order (@0x24).
- **`base + i*4/8 + K` in-loop index vs SR** (ov000_020570d8 6-member family +
  ov000_02055d98 5-member family, ARM): ROM keeps `i` a live counter and recomputes
  the address conditionally in-loop (`add rN, base, i, lsl#2/3; ldr [rN, #K]`); mwcc
  3.0/139 strength-reduces `base + i*small + K` into walking pointer(s), spending
  extra callee-saved regs (+8..16B). Offset-arith SRs; the `((int*)(base+K))[i]`
  array-subscript crack either hoists `base+K` or splits into separate base pointers;
  nested `if(base){int*p=…;}` still SRs. BEFORE carving one of these, check the rep is
  not already in `nonmatching/` (02055d98 was pre-tied Jul 1). Whole family ties.
- **factored index-multiply** (ov000_02054e48 THUMB family, ov000/…): ROM computes
  `idx * 0x4030` as `(idx<<1) * 0x2018` (`ldr 0x2018; lsls #1; mov; muls`, +4B); mwcc
  3.0/139 always folds constant×constant to a single `ldr 0x4030; muls`. Tried raw
  `*0x30`/`*0x4030`, `(idx<<1)*0x2018`, materialized intermediate, and inline/variable
  array-subscript on a 0x2018-stride struct — all fold. → nonmatching/. Whole family
  ties identically.

## Loop / structural ties

- **loop strength-reduction / induction var** (ov008_0205da50, 020cdbfc): mwcc always
  makes a byte-offset induction var (`add ip,ip,#N`) where the ROM recomputes
  `add r2,r0,r3,lsl#N` each iter. The array-subscript form helps SOME loops but not
  these; also the `cmp r5,r5` max(0,x) clamp artifact (020ce310).
- **c0b90 struct-by-value stack marshal** (`sub r3,sp,#8` const-Vec3): the marshal
  itself matches, but the surrounding schedule ties.
- ~~**b9fc / 020c5c54 (stack-struct-spawn) / 02023eb4 (rand `add r0,#0` artifact)** and
  the `VEC_*`/`FX_*`/`MTX_*` fixed-point library funcs — treat as ties/skip.~~

  ★★★ **RETRACTED 2026-07-17, and it was the most expensive line in this file.** Every item that
  sentence named is cracked, and the corpus says so out loud. Counted over the whole tree
  (`asm_stubs` excluded), functions whose relocs touch that "skip" list:

  | symbol | UNMATCHED | already MATCHED |
  |---|---|---|
  | `func_01ffa724` (scale) | 875 | **347** |
  | `func_01ff8d18` (normalise) | 788 | **221** |
  | `VEC_Subtract` | 737 | **339** |
  | `VEC_Add` | 567 | **109** |
  | `02023eb4` (the rand artifact) | 503 | **438** |
  | `0203b9fc` | 212 | **419** |
  | `MTX_MultVec33` / `MTX_RotY33_` | 145 / 139 | **93 / 88** |
  | `func_ov107_020c5c54` (the stack-struct spawn) | 46 | **89** |

  **1,296 unmatched functions touch that list — and 1,303 MATCHED ones do too.** A class that is
  half matched is not a tie; it is a vein. `0203b9fc` and `020c5c54` are already matched MORE often
  than not, i.e. the line was telling people to skip work that was already routinely done.

  Note the file contradicted itself: the rand entry directly below has said "NOT a tie — it is
  SOLVED" since earlier the same day, while this line still listed `02023eb4` under skip. **When
  you crack something, delete the entry that says not to try it** — leaving the correction next to
  the wrong claim is not enough, because the wrong claim is the one that gets skimmed.

  What was actually true underneath: these functions build fixed-point vectors on the stack, and
  the SDK has an `inline` for most of that. Open-coding the maths gives shapes that never match,
  which is what the original observation really saw. The cracks are in codegen-cracks.md
  (`VEC_Set` fingerprint, `FX_Mul`, the Q12 radians→sin/cos conversion, the rand `+ (v - v)` copy).
  9 functions were matched off them in one afternoon — ov239, ov188×4, ov202/203×2, ov202/203×2 —
  several on the first compile.

  ★★ **The rand `add r0,r0,#0` is NOT a tie — it is SOLVED. Do not route around it.**
  *(2026-07-17. An earlier version of this note called it an unbreakable compiler-build tie and was
  wrong twice over; both mistakes are worth knowing.)*

  `func_02023eb4` is `long long RandNextScaled(unsigned mul)`: it advances the RNG and returns
  `(state * mul) >> 32` **in r0** — multiply-shift range reduction, so `mul = 0x65` is a d100.

  **The crack**: mwcc emits the copy for `f(n) + K` when `f` returns `long long` and `K` is an
  addend it cannot constant-fold. `+ 0` folds away; **`+ (v - v)` for any int local `v` does not**:
  ```c
  extern int func_02023eb4();                    /* K&R decl -- see the gotcha below */
  roll = func_02023eb4(0x65) + (v - v);          /* -> bl ; add r0, r0, #0 */
  if (func_02023eb4(2) + (v - v) == 0) ...       /* -> bl ; adds r0, r0, #0  (test fused in) */
  ```
  It was already in the tree: `func_ov137_020cd5a4` and 6 other matched functions use it. Comment it
  where you use it — it reads like a typo and a future cleanup would silently break the match.

  **Refinement (2026-07-17, func_ov169_020cda08): the `v` in `+ (v - v)` is not free -- pick one
  already live across the call.** The artifact does not load `v`, but mwcc still treats `v` as
  referenced, which can hold its register one instruction longer and perturb allocation UPSTREAM
  of the call. In ov169 using the distance `diff` for `+ (diff - diff)` kept diff's register alive
  and shifted the height-subtraction's register choice; using `counter` -- already live across the
  02023eb4 call -- matched, and `diff` was then scoped to die at its own block. Prefer a `v` whose
  natural live range already spans the call; if none, a fresh `int` declared right before the call
  works too. And still name it `*.c` for the K&R decl:

  **Confirmed (2026-07-18, func_ov200_020cf7d4 x3): when the function has no other locals, a bare
  uninitialized `int v;` at the top matches first-try** (plain-copy form `state[0x29] = rng(2) ? -1
  : 1` and the stored form `state[0xc] = rng(0xa01) + (v - v)`). With nothing else live there is no
  upstream allocation to perturb, so the "pick one already live" caveat above only bites when the
  function *has* competing live values. No-live-value functions: just declare `int v;`.

  **Gotcha**: with `extern int func_02023eb4();` the file MUST be named `*.c`. mwcc maps an unknown
  extension to C++, where `()` means *no* parameters, and the call then fails to compile.

  **Two lessons from getting this wrong:**
  - The artifact has two spellings — `add r0,r0,#0` and, when the result is tested against 0,
    `adds r0,r0,#0` (the copy and the test fused). A census grepping only the first found *zero*
    real-C users and "proved" a tie that does not exist. **Searching for one spelling of a
    two-spelling pattern is not evidence** — state the positive form first (SKILL.md).
  - Of the functions that do carry it, most that "match" are `asm_stubs` blobs, which verify
    trivially. When judging whether a pattern has ever been cracked, **filter asm_stubs out** or the
    answer is meaningless.

  Census with both spellings: 155 functions carry it (7 real C, 64 asm_stubs, 9 nonmatching,
  75 undone) — so it is a large vein, now open.

  ⚠ **The artifact is not always the instruction right after the `bl`.** In `func_ov125_020cd27c`
  the scheduler slips a `ldr` between the call and the `add r4, r0, #0`. Scanning only `bl+4` said
  "no artifact" and was wrong. Scan a window of ~3 instructions, and note that a roll feeding a
  *real* add (`base + rand(n)`) needs no trick at all — in ov125 only 3 of 5 rolls wanted it.
- **dead register copy** (`mul; mov ip,r0; add r0,ip,#K` with ip never re-read) —
  unsteerable. (func_ov022_020889cc.)
- **dead-`bne` artifact** (020ce61c) — a compiler quirk hard to reproduce from clean C.
- **BLX** (indirect/interworking) — the reloc mask doesn't fully neutralize BL vs
  BLX mode-switch; the x33 THUMB 5-call-spawn siblings tie deterministically @0x16.

## Working filter for candidate scans

Skip: `blx`, `ldm` (arg coalescing), `mla`/`lsl #2` in body (index-loop SR), a
`ldrh [+0x60]` followed by `orr #K` (hw60 `|=`), `02031384` + a preceding anim
(atomic-hpair order), and the tie hubs `0203b9fc/020c0b90/020c5c54/02023eb4/
01ffa724/VEC_/FX_/MTX_`. See the ready snippet in tools.md.

**Append new ties here as you confirm them** — a proven tie saved is hours saved.

## if-conversion of `call() && cheap_compare` (ov000 BuildTagTracker sibling 02056354)
mwcc 139 predicates an outer `if (func(...) && k.c != target)` — emits
`cmp r0,#0; ldrhne …; cmpne …; beq tail` (292B) — where the ROM keeps two
independent branches `cmp; beq tail` then `teq; beq tail` (296B, uses `teq`).
Tried: nested `if(A){if(B){}}`, flag-declared-first, and explicit `goto tail`
early-exits. None defeats the if-conversion. Symptom: your version is SMALLER than
the ROM and shows `ldrhne`/`cmpne` where the ROM shows a standalone `teq`. 8-member
family ov000/002/005/006/008/009/025/026 (func_ov000_02056354 + peers) → nonmatching.

## if-conversion of a bounds-checked table lookup (Archive_LoadFile func_0201ef9c)
`if (c >= 0 && c < 0x80) c = toupper_tbl[c];` — mwcc 3.0 predicates the 2-instr load
block as `cmp c,#0x80; ldrlt tbl; ldrblt c,[tbl,c]` (520B) where the ROM branches over
it `cmp c,#0x80; bge skip; ldr; ldrb` (524B). mwcc branches large skips, predicates
≤2-instr ones; the ROM branched a 2-instr block. Resisted nested-if, De Morgan
(`if(c<0||c>=0x80){}else{...}`), reversed operand order, and `unsigned c`+`-1<(int)c`
(that last one branches the load but rewrites cond1 as `sub;cmp;ble` AND breaks the
flush region). Confirmed a tie across 3.0_136_patched and 3.0_patch4. Everything else
in the 524B function (double-buffered async decompressor loop, both paths) matches.

## c634-handler + vec3-copy "load-early/store-late" regalloc tie (2026-07-15)
- **Family**: 10 members, 176B, reloc @160=`func_0203c634` @168=`data_02041dc8`(vec3)
  @172=per-ov cb. Members: func_ov137_020cedac, ov138_020d29ec, ov158_020cee30,
  ov159_020d4890, ov160_020cefd8, ov228_020d25d8, ov229_020d6218, ov233_020d0728,
  ov246_020d1fb0, ov247_020d3dd0.
- Shape: `obj=*(self+4)`; A=*obj; **clear hw60 bit8** (`((struct hw*){lo:8,hi:8})->hi &= ~1`
  — the bitfield form is REQUIRED, gives the extra u16-trunc `lsl#0x10;lsr#0x10` that the
  explicit `& ~1` mask omits, +8B); **A->hw60 hi |= 0x82** (explicit
  `(v&~0xff00)|((((v<<0x10)>>0x18|0x82)<<0x18)>>0x10)`); clear bit0 of low byte of
  `*(A+0x388)+8` (struct b8); **stage vec3 `*(vec3*)(obj+2)=data_02041dc8`**; dispatch
  `func_0203c634(self, *(s8*)(self+0x20), &cb)`.
- **TIE**: logic-perfect & byte-count-exact (176==176) but the ROM **hoists the vec3 `ldm`
  load to the top and holds r0-r2 live across the body** (pushes {r3-r7,lr}); every C form
  (copy-last, copy-first, precomputed dst ptr, `struct vec3 tmp` local) either loads late
  (push {r4,lr}) or spills the local (196B). Pure mwcc scheduler/regalloc choice — no C form
  reproduces load-early/store-late. Template routed to ov138/nonmatching/. Do NOT re-chase.

## Forward-dispatch block-layout tie (2026-07-15)
Multi-way `if(x==A)/else if(x==B)/else` where the ROM lays out **all case blocks AFTER the
dispatch** reached by forward `beq`/`b` (dispatch: `beq caseA; ...; beq caseB; b default;`
then A,B,default blocks, each ending `b end`). mwcc (our build) instead **inverts and inlines**:
`bne skipA; A; ... ` OR folds `if(x==B) goto b; goto d;` into `bne d; b b`. No C form reliably
reproduces the ROM's non-inverted forward dispatch: bare if-gotos fold the last `goto`, `switch`
reorders the compare chain, if/else-if inlines. Hit in **func_02023adc** (obj state-machine
dispatcher: also base r5-vs-r8 regalloc) and **func_02020928** (BootTask_Construct scene select:
otherwise byte-exact incl. K&R `func_02020a78()` 1-vs-2 arg trick + `*(int*)0x027ffc20` abs const;
only the 2nd `beq c;b d` vs `bne d;b c` differs). Both routed to nonmatching. Do NOT re-chase the
layout; if a future mwcc flag flips block ordering, revisit.

## func_ov000_0204df98 phase-1 counter bump — r1/r2 scratch tie (2026-07-15)
`if (++*(unsigned char*)(h+0x4c52) < 3)` inside a switch case: ROM keeps the live
compared value in r0, the base pointer (h+0x4000) in r1, and the increment temp
(old+1, stored) in r2. Inline gives base=r0/value=r1; a named base pointer moves the
value to r0 but flips base/temp to r2/r1. No C form reproduces the exact base=r1/temp=r2
pairing without adding/removing an instruction. Everything else in the 76-instr function
matches. Routed to nonmatching/.

## func_ov000_02054e7c — return-1 tail-merge (2026-07-15)
Two identical `return 1;` exits (an early guard and a deep reload path). Our mwcc
3.0/139 tail-merges them into one shared `movs r0,#1; pop` (-2 THUMB instr); the retail
build emits both separately. No source structure (guard-first, guard-last, r>=0 wrapper)
prevents the merge. Same version-difference family as the pool-dedup tie. -> nonmatching/.

## Phantom-arg register coalescing (THUMB, held big-offset base)
When a function holds a large struct offset (e.g. 0x4624) in a register and reaches
fields via `add/sub` deltas, and one of those derived offsets (`O-0xe`) is ALSO passed as
a call argument, the ROM's mwcc allocates the arg register (r2) to that offset's scratch use
and destroys the O-holder (`sub r0,#0xc`) on the final store, so the arg is already in r2 at
the call (no recompute). Our mwcc keeps O in the arg register and recomputes `O-0xe` before
the call (+1 `subs`, +4 bytes). Neither offset-variable reuse, a single reassigned offset
var, nor extracting the arg into a named local reproduces the coalescing.
Example: func_02032388 (object-node init) — whole structure matches, +4 B only. -> nonmatching/

## Tie classes seen in the ov006/ov008 title-menu sweep (2026-07-16)
Most small-to-medium ov008 funcs that don't match fall into one of these. Recognise the class
from the diff BEFORE burning iterations; if it's one of the first four, route to nonmatching.

- **CSE of a cheap masked/added value.** The ROM holds the raw value in a callee-saved reg and
  RE-computes `x & 0xffff` / `id + 0x3bd5` (as `add #lo; add #hi`) before each of two calls,
  because the call barrier + register pressure defeats caching; our mwcc caches the computed sum
  (-4/-8 B). No C form reliably forces the recompute. (func_ov006_02053cdc & twin func_ov008_0206abb8;
  func_ov008_0206fa1c.)
- **Frame-arg-home.** When a parameter's ADDRESS is taken (`&param_4` passed to a callee), the ROM
  homes all incoming args with `push {r0,r1,r2,r3}` and points into that block; our mwcc reserves a
  separate local slot (`sub sp; str r3,[sp,#..]`), +4/-4 B. (func_ov008_0204d6a8, func_ov008_02082ecc.)
- **Register-number swap (r4↔r5, r8↔r9).** Structure byte-identical; two overlapping-lifetime
  pointers get opposite registers. SOMETIMES fixable by swapping the C declaration order of the two
  locals (works when they're plain `base+const` pointers — func_ov008_02084324 matched this way);
  often not (func_ov006_0204f9b0 / twin func_ov008_0207b70c: option-table vs fallback-string; +/-4 B).
- **Read-order scheduling.** Two independent loads (`a=p[0]; b=p[1];`) get reversed by the
  scheduler (ROM `ldrh r2,[p]; ldrh r1,[p,#2]`; ours swaps). Batching them into locals moves the
  reads together but not always in the ROM's order. (func_ov008_0204ec34, func_ov008_0205714c.)
- **switch-vs-if tail-merge.** A compare-chain switch where every case `break`s to a shared
  `return`/commit compiles with an explicit `b default`; an `if/else-if` folds the no-match
  fall-through (-4 B), and a `switch()` on sparse cases makes mwcc emit a jump table instead
  (+bigger). (func_ov008_02067484, func_ov008_0204eb88.)
- **Boolean-gate fusion.** A multi-field null gate (`if (a==0 && b==0 && c==0) return;` where b,c
  are conditionally loaded) the ROM fuses into conditional loads + a conditional early-return
  (`cmp; ldreq; cmpeq; popeq; cmp; ldrne; cmpne; beq`); a faithful structural transcription
  over-expands by 20-70 B. Ghidra shows these as `bVar3 && ...` chains. (func_ov008_020597c4,
  func_ov008_02073d88 & twin func_ov008_02073df0.)

## Twin heuristic + dedup (high-yield process)
ov008 functions very often have a byte-different TWIN in ov006 (same shape, different globals/relocs)
— e.g. 02053cdc↔0206abb8, 0204f9b0↔0207b70c, 020597c4↔02073d88↔02073df0. If the twin was a tie, the
other is too; if it matched, reuse the exact technique. And run `dedupprop.py` after EVERY batch:
it propagates byte-IDENTICAL twins (same masked hex) to other overlays for free — this session it
yielded 19 then 4 matches across ov008/ov009/ov025 for zero analysis.

## Phantom-arg size blow-up (diagnosis, not a tie)
If a written function is MUCH larger than target (e.g. 128 vs 100), suspect a wrong arg count: a
function declared with too many params makes mwcc save/restore the extra params across the first
call (`push {r4,r5}` + `mov r4,r3; mov r5,r2` + per-call `mov r2,r5; mov r3,r4`). Check the ROM
disasm at the call: if only r0/r1 are set before the `bl`, the extra args are garbage leftovers —
declare the REAL (smaller) arg count. (func_ov008_02063790 is 2-arg, not 4; fixed -32 B instantly.)
Corollary: medium funcs WITH calls (100-250 B, 4+ relocs) match far more reliably than tiny
reloc-free leaf accessors, where a single-instruction tie IS the whole function.

## ★ The ctx-CSE / global-address rematerialisation tie (PERVASIVE — route on sight)

**Recognition (2026-07-16, hit ~6× in one session):** a function reads a *global context pointer*
(`data_ov008_02090f04[1]`, `data_ov006_02056664`, `data_ov006_020565e4`, `data_ov008_02090fac`, …)
at **two or more points separated by a call**. The ROM reloads `&global` from the literal pool at
each use; mwcc caches it in a callee-saved register (adding a push, sometimes a stack slot) and folds
the reloads. Diff signature: **mine is SMALLER by 4 B per folded reload**, and mine's `stmdb` mask
has extra callee-saved regs vs the ROM's.

Not steerable: reordering, extra locals, inlining the RMW, and `(int)&g + off` vs `g + off` forms
all leave the CSE in place. Almost certainly a compiler-version artifact (see
`reference_mwcc_build_hunt` — retail is likely mwcc 3.0 ≥140, ours is 139).

**Rule: if the ctx global is used on both sides of a call and the size is short by a multiple of
4 B, route to `nonmatching/` immediately — do not iterate.**
Corollary that DOES match: the same shape matches fine when the ctx is used only *once*, or only
*before* the first call, or when the base is a `param + offset` instead of a global.

## Dead-narrowing tie (`uint >> 16` then u16 cast)

The ROM emits `lsr#16; lsl#16; lsr#16` (truncating a value it already knows is 16-bit); mwcc elides
the redundant `lsl/lsr` pair because it tracks the range. Mine is 4 B short. No C form
(`(unsigned short)x`, `x & 0xffff`, u16 local) re-introduces the dead narrowing. (ov008 0207350c.)

## ⚠ RETRACTED 2026-07-16: "r1/r2 register-allocation tie in an MMIO block"
Previously filed as a tie (ov006 0205454c). **It is not a tie.** It is the absolute-vs-derived
MMIO addressing knob — see the bidirectional entry in codegen-cracks.md. ov006 0205454c matched
byte-exact once the sub-BG1 register was written as its own absolute constant instead of as
`bg1[0x800]`.

Before routing ANY MMIO-heavy function to nonmatching/ on register-allocation grounds, flip each
address in the block absolute↔derived. Only the *value*-vs-*address* rematerialisation choice
(which value the allocator keeps live across a call, e.g. ov000 0204ef84's last instruction) is a
genuine tie.

## Instruction-scheduling tie (route on sight)

Symptom: **same size, same instruction count, same semantics** — only *where* mwcc places an
independent instruction, and the register numbering that falls out of it. Not steerable.

Seen 2026-07-16:
- ov024 `020835d8` (32 B): mwcc emits the interworking tail call correctly
  (`ldr r12,[pool] ; bx r12` — the callee is THUMB) but places the `ldr` two instructions later
  than the ROM, which hoists it between the two stores and therefore needs `r2` rather than `r1`
  for the constant 1.
- ov024 `02082c44` (84 B): the ROM materialises BOTH constants first (`mvn r3,#0 ; mov r2,#0`)
  then does both stores; mwcc interleaves (`mvn r2,#0 ; str ; mov r1,#0 ; str`). Hoisting them
  into explicit locals does not move it.

**Tell it apart from a real crack:** if the size matches and the diff is only operand registers
plus one instruction's position, it is scheduling — stop. If an *instruction* is present/absent,
or an encoding differs (`tst` vs `ands`, `blt` vs `bge`, `lsr` vs `asr`), check
`codegen-cracks.md` first — several of those ARE steerable.


---

## The register-CHOICE residue class (observed 2026-07-17, four functions)

**Not a verdict -- an observation, recorded so the next session compares the four instead of
finding a fifth.** Everything in this file is a prior, and this entry least of all: it is one
day's pattern.

Four functions this session ended in the same place: **the instruction shape is exact, the
instruction COUNT is exact, and only which register a value lands in differs. In each, the two
choices cost the same, and no C-level lever moves mwcc off its pick.**

| function | ROM | mwcc | size |
|---|---|---|---|
| `func_ov039_020b3570` | flag=r5, id=r6, quiet=r7, ret=sl | flag=sl, quiet=r5, ret=r6, id=r7 | 792/792 |
| ~~`func_ov029_020b2ee0` (THUMB)~~ | **SOLVED 2026-07-20 — see below, and be suspicious of the rest of this table** | | |
| `func_ov301_020cbfc4` | uVar4=r3 (scratch), iVar1=r6, 0x17=r5 | uVar4=r6, iVar1=r7, 0x17=lr | 408/408 |
| `func_ov020_0207fac8` (THUMB) | p=r1, temp=r2 | p=r2, temp=r1 | 60/60 |

★★★ **RETRACTED for `func_ov029_020b2ee0` (2026-07-20): it was never a register-allocation tie.**
It matched with plain array indexing -- `table[group].field` instead of
`(T *)((char *)table + (group << 4))` -- plus **duplicating** the lookup rather than caching it in
a local, plus spelling the hook call as the nested array it is. Full recipe in
`codegen-cracks.md` ("ARRAY LOOKUPS").

**Why this one should change how you read the WHOLE table.** Its park was among the best-evidenced
in the project: ~19 source spellings, all 12 mwcc builds on the 2.0/3.0 line, 10 extra flag sets
from decomp.me's NDS presets, and an explicit "STRUCT TYPING: six formulations tried, none match".
That last line was the fatal one — **it had already tried plain indexing, but kept the cached
pointer, so it only ever applied half the idiom and then recorded the whole axis as closed.**
The lesson generalises past this function: when a write-up says "N formulations tried", ask whether
the N were really independent, or whether one unexamined decision rode along in all of them.
The remaining rows here have not been re-tested against the array-lookup crack.

Between them ~40 spellings are ruled out in-file (declaration order swept exhaustively on two of
them -- 48 and 40 compiles -- statement order, index-vs-offset, explicit temps, inlined
expressions, parameter counts). **Read the individual files before touching any of these**; each
carries its own checklist and its own next lever.

What is *not* shared: ov301 and ov029 look like "the ROM spends a scratch register / a free stack
slot where mwcc reaches for callee-saved", but ov020's two registers are BOTH scratch and both
free, and ov039's are all callee-saved. So the tidy story ("mwcc 3.0/139 prefers callee-saved")
does not survive its fourth case. **Do not write that story down as fact** -- it is exactly the
kind of tidy explanation that cost a day on `func_ov046_020b3508` (see the phantom-argument entry
in codegen-cracks.md).

What IS shared is only this: **a tie-break that is invisible from the source, in a spot where
mwcc's cost model sees no difference.** That is consistent with the `mwcc build hunt` hypothesis
(retail is likely 3.0 build >=140, which we do not have) -- and it is also consistent with a
C-level lever nobody has found. **The honest state is: unknown, and not worth more per-function
compiles.**

### The corpus query has now been RUN, and it splits the class

Two sweeps over every matched real-C function (asm_stubs excluded -- they verify trivially and
would make the counts meaningless):

**1. Does mwcc ever spill into the free r3 push slot instead of taking a callee-saved register?**
Positive form: prologue `push {r3,...}` with NO `sub sp`, a store to `[sp,#0]`, and a LATER RELOAD
from it -- the reload is what separates a spill from an outgoing 5th argument, since nobody reads
an outgoing arg back.
> **YES -- 46 of the 4,552 matched real-C functions with that prologue do exactly this.**
> `func_ov000_02055a24` (THUMB, 29 instr) is the clearest: two passes over the same array, `base`
> must survive the first loop for the second, so mwcc spills the loop counter `i` to `[sp]` and
> reloads it every iteration. `func_ov000_020561b4` even reloads predicated (`ldrne r0,[sp]`),
> which cannot be argument setup.

So **spilling to that slot IS reachable from C** -- mwcc does it when register pressure forces it.
The ov029 write-up's old framing ("make mwcc prefer spilling") was asking for something mwcc
already does routinely; what it actually needed was pressure.

**2. Does the ROM ever park a value in ip (r12) in THUMB?**
Positive form: `mov ip, rN` followed later by `mov rN, ip`.

I ran this twice and **the first run was a false negative -- worth reading as a worked example of
the rule it broke.**

*First run:* searched the 693 matched real-C THUMB functions. Found **0**. I concluded the ROM's
compiler never parks values in ip, and therefore that ov029's C -- which produces an ip-park --
had to be wrong. **That conclusion was false.**

*Why it was false:* **ip is CALLER-SAVED.** It cannot hold a value across a call. So for ip to be
usable at all you need every low register full AND a value that needs a register but does NOT
cross a call. That combination is rare, and it is absent from the matched corpus because the
matched corpus is mostly small, simple functions. The search could not have found the thing.
This is precisely the skill's "state the positive form and confirm your search could match it"
rule, broken by the person who had just quoted it two commits earlier.

*Second run, over EVERY THUMB function in the ROM* (2,208 of them, mode taken from symbols.txt's
`kind:function(thumb)` rather than guessed -- matched or not, the ROM's bytes are the ROM's bytes):
> **35 THUMB functions in the ROM DO park a value in ip.** `func_02025aac` (2,034 B),
> `func_020262bc` (1,928 B), `func_ov002_0206b0f8` (964 B), and 32 more -- all big functions, none
> matched yet, which is exactly why the first search missed them.

**So the ROM's compiler uses ip. ov029's ip-park is not anomalous, and the C is not indicted.**

What the two runs DO establish, which is the useful residue:
- mwcc spills to the free r3 slot when a value crosses a call and no callee-saved register is
  free (46 cases). It is not reluctant to spill; it spills when it is genuinely out.
- Both compilers use both mechanisms. In `func_ov029_020b2ee0` the choice is: `off` crosses the
  0201e470 call (so ip is useless for it -- it must be callee-saved or spilled) while `entry` does
  not (so ip works for it). The ROM keeps `entry` low and spills `off`; mwcc gives `off` the
  callee-saved r7 and evicts `entry` to ip. **Both are legal, both cost 47 instructions, and
  mwcc's is arguably the smarter of the two.** That is a real tie-break, not a bug.

So ov029 goes back into this class rather than out of it -- but with its mechanism understood
instead of hand-waved. ov039/ov301/ov020 are ARM or all-scratch cases where ip never enters and
stay open on their own terms. **The class is still not one thing, and the build story is still
neither confirmed nor refuted.** Two confident conclusions have now died here in two days; the
next one should be a measurement, not a story.

---

## ldm load-coalescing tie: "load vec3 + offset one field + store to a stack local passed by &"

Confirmed 2026-07-18 on `func_ov185_020ced78` x3 (ov185/186/187), size-exact +8B. Shape: build a
local `struct vec3 v` from `*(state[0x11])` with one component offset (`v.y = p->y + 0xc00`), then
pass `&v` to a callee (`020c5c54`). The ROM loads the source with a single `ldm r0,{r0,r2,r3}`,
patches Y in-register, and stores the three words individually (`str` y,z,x to `[sp,#*]`). mwcc
instead reuses r0 and emits **three separate `ldr`** (one instr more), OR — if you write it as a
struct copy — `ldm; stm; ldr; add; str` (a full block copy plus a reload, two instrs more).

Ruled out (none force the load-multiple):
- field-by-field, both `x/y/z` and `y/z/x` store orders → 3× `ldr`;
- `v = *p; v.y += 0xc00;` → `ldm`+`stm`+reload (block copy, +2);
- intermediate `struct vec3 t = *p;` → mwcc materializes `t` on the stack (worse, +5);
- temps-first `int a=p[0],b=p[1],c=p[2];` → splits into `ldmib`+`ldr` (b is the modified one);
- `int v[3]` array with the same assignments → still 3× `ldr`.

It is a pure register-allocation choice: the ROM keeps all three source words live at once (so `ldm`
pays) because r1 is pinned to `&v` early; mwcc prefers to reuse r0 and store as it goes. No C form
observed flips it. **Park after the checklist** (verify the callee arity/by-pointer, the offset, and
that every value is exact — here they were). If a future session finds the C form that emits `ldm`
here, delete this entry.

---

## c634-after-zero-store arg-materialisation tie (2026-07-18)

When a `func_0203c634((int)self, idx, cb)` tail immediately follows a `state[N] = 0` store (the store
uses r0 for the `#0`), the ROM materialises the OTHER two args first (`ldrsb r1,[self,#0x20]`;
`ldr r2,=cb`) and defers `mov r0, self` to LAST; mwcc sets `r0 = self` FIRST. Same instructions,
one swap, size-exact. Seen on `func_ov235_020d1b98` and `func_ov235_020d1c20` (x3 each).

★ **Precomputing the idx into a local `signed char idx = *(signed char*)(self+0x20);` before the c634
call fixes it SOMETIMES** — it matched the sibling `func_ov235_020d1b98`'s c634 swap but NOT
`020d1c20` (the register pressure coming out of the preceding `b9fc(...,2,0)` calls differs). Also
tried: precompute cb, cache `int s=(int)self`, precompute idx before the store — none reliably flip
it. Try the idx-precompute first; if it doesn't take, park. (When c634 follows a *call* instead of a
store, r0 is already clobbered and mwcc's canonical r0-first order matches the ROM — no tie.)

## struct-copy load-hoist tie (2026-07-18, func_ov245_020ced68)

A `*(struct vec3*)(dst) = data_const;` copy sitting among several hw60/byte RMW blocks: the ROM loads
the const vec (`ldm`) early, HOLDS it in r0-r2 across all the RMW work (so it pushes r4,r5,r6 for the
RMW scratch), and commits the `stm` LAST. mwcc keeps the `ldm`/`stm` adjacent — copy-last -> both late
(no hoist, pushes only {r4,lr}); copy-first -> both early; a local `struct vec3 tmp` spills (+20B);
a C99 compound literal spills too. No C form splits the load from the store the way the ROM scheduler
did. Size-exact. Distinct from the ov185 `ldm` load-coalescing tie above (that one is 3×ldr vs ldm on
a *field-offset build*; this one is a whole-struct copy the ROM *defers*).

## 2-halfword struct-copy read-order tie at a non-zero offset (2026-07-18)

A `struct { unsigned short a, b; }` copied from a data symbol at a NON-ZERO offset (e.g.
`data_020d182c + 0x10` in func_ov200_020d0008, `+4` in func_ov200_020cfda0): the ROM batches the copy
reading the HIGH halfword first (`ldrh r2,[base,#off+2]; ldrh r0,[base,#off]; strh r2,[sp,#2]; strh
r0,[sp]`); mwcc reads the LOW halfword first. Identical result (sp[0]=+off, sp[2]=+off+2), swapped load
order -> a 4-byte diff. Tried: struct copy `s = *(struct h2*)(base+off)`, struct-member copy
(`struct{char pad[off]; h2 hh;}`), pointer-to-member, C99 array-index `arr[k]`, explicit reverse-order
field copy -- none read the high halfword first at a non-zero offset. ★ A BASE-symbol h2 copy DOES read
high-first and matches (func_ov210_020d1af4, `scratch = data_020d46ec`), so the tie is specific to the
offset. If a future session finds the C form (or a way to alias the +off address as its own symbol),
delete this entry. Otherwise park; it is a 4-byte residual on otherwise byte-exact functions.

## ~~caller-return-reservation reload coloring (r0 vs r1) at c5c0/spawn out-params~~ — **CRACKED, ENTRY WRONG**

★★★ **This entry was WRONG and it is the most instructive one in the file. Both named functions
(`func_ov235_020d1a34`, `func_ov119_020cf7b0`) now match**, along with 22 more of the same vein.
The fix is one line: **the caller returns the call's result** — `int f(...)` and
`return rc;`. See `codegen-cracks.md`.

Read what the entry below actually says: *"The ROM keeps r0 reserved as the spawn call's discarded
return value"*. **It had the mechanism exactly right and parked anyway**, because the levers it
tried — including "declaring the callee non-void" — all varied the **callee**. The one thing never
varied was the **caller's own signature**, which is where a reserved return value comes from. And
`func_ov119_020cf7b0`'s parked source additionally referenced two callbacks that do not exist in
the ROM (`020cf800`/`020cf7fc` vs the real `020cf848`/`020cf804`) — `verify_idx` prints
`orig = {...}` with the true symbols, so that had been visible on every run.

**Lesson: having the right mechanism is not having the right fix.** A correct diagnosis makes a
park note *more* persuasive and can still be one untried axis away. "Don't re-attempt" (which this
entry said, in bold) is the sentence that costs the most when the entry is wrong.

Original text, kept for the record:

## caller-return-reservation reload coloring (r0 vs r1) at c5c0/spawn out-params (2026-07-18)

A spawn helper with a stack out-param -- `f(scene, kind, size, cb, cb2, &out); out[0]=a; out[1]=b;`
(the func_0203c5c0 family) -- reloads `out` from its stack slot once per store because it is
address-taken. The ROM colors that reloaded pointer r1 (`ldr r1,[sp,#N]; str r5,[r1]` x2); mwcc 3.0/139
colors it r0. Reload COUNT and everything else match; only the register field differs (a 1-byte diff).
The ROM keeps r0 reserved as the spawn call's discarded return value and reloads into r1; 3.0/139 frees
r0. Tried: int*/struct* out, cast stores, `out=0` init, declaring the callee non-void, temp-pointer
copy (collapses to ONE reload -> wrong count). No C form flips r0->r1. This is a retail-build
(likely mwcc 3.0 >=140) property, same family as the ov119 lr<->ip and ov235 ip<->r4 struct-copy
colorings. Park; it blocks the whole spawn x3 family (nonmatching reps don't propagate). First seen
func_ov235_020d1a34.

  UPDATE (2026-07-18): the tie tracks the **2-saved-param** spawn shape (self+arg both saved, out
  reloaded twice for two stores). The **1-saved-param** c5c0 spawn (func_ov124_020d14b0) colours the
  reload r0 in BOTH ROM and mwcc and MATCHES. So: 1-param c5c0 spawns -> match (r0); 2-param c5c0
  spawns with the `out[i]=x; out[j]=y` double-reload -> park (ROM r1, mwcc r0). Don't re-attempt the
  2-param ones. Seen: func_ov235_020d1a34, func_ov119_020cf7b0.

## inlined struct block-copy (ldmia/stmia) src/dst scratch coloring — RECURRING (2026-07-18)

Any inlined multi-word struct assignment `*(blkN*)dst = *(blkN*)src` that mwcc lowers to ldmia/stmia
block copies: the ROM colors the SOURCE pointer -> lr and DEST -> ip; mwcc 3.0/139 colors SOURCE -> ip,
DEST -> lr. Size and all else match; only the two pointer registers swap (a few bytes). The choice is
INDEPENDENT of source form -- tried inline assignment, explicit src/dst locals (both decl orders),
temp-pointer, negative-offset alias, struct-vs-cast, simple base+offset vs deref source (~8 variants
across ov119_020cbfc4 and ov244_020cd68c). Both order source-first; they just grab a different scratch.
This is a compiler-version property (retail grabs lr-first, 3.0/139 grabs ip-first). ★ When a
"publish/copy transform" function is byte-exact except two ldmia/stmia pointer registers, it is THIS
tie -- park immediately, don't re-iterate. Seen: func_ov119_020cbfc4, func_ov244_020cd68c. (Word-by-
word copy avoids ldmia but is bigger -> size mismatch, so not an escape.)

## message-handler spawn-setup scheduling/coloring (2026-07-18)
The ov208/210 message handlers (kind-5 dispatch) end each switch case with a spawn call whose args are
built from a ternary base + a slot index `self + msg[3]*8 + off`. The ROM interleaves the slot-index
`add r1,r6,r1,lsl#3` BETWEEN the ternary's `ldreq/ldrne` and colours the base -> r0 (then `add r3,r0,#4`
for the owner arg); mwcc 3.0/139 colours the base -> r2 and schedules the index/`str [sp]`/`mov #1`
setup in a different order. Same result; a few bytes of spawn-setup scheduling. Not steerable by
inlining base+4 or reordering. Seen func_ov208_020d03e8 (also a 3rd-pack r7/ip tie) and func_ov208_
020d39d8. These handlers get VERY close (size-exact, only the spawn setup ties) -- park them but keep
the reconstruction; a future session with fresh register-pinning ideas can finish the class.

## Sub-header locate: `hdr==0 || hdr[1]==0` guard -- if-conversion tie (mwcc 3.0/patch4)
func_ov005_02050d64 (x3 ov005/008/025 -- the coordinate-resolver twin of the BuildPanelIdSummary
menu family). A resource sub-header locator appears twice: `if (hdr==0 || *(u8)(hdr+1)==0) p=0; else
p = hdr + *(u16)(hdr+6) + 4;`. The ROM BRANCHES each condition to a shared out-of-line `mov r,#0`
(`cmp; beq Z; adds; beq Z; ldrb; cmp; bls Z; ...compute...; b DONE; Z: mov r,#0; b DONE`), with the
count test as unsigned `bls`. patch4 ALWAYS if-converts the two-condition guard into a predicated
chain (`adds; ldrbne; cmpne; moveq r,#0; beq`), collapsing the out-of-line block -- 200 vs 236 bytes.
Everything else in the function (02017088 lookup, the `(cmd & 0x1c000000)==0x14000000` GX-command
classification picking base+0x18 vs base+8, the `(unsigned short)` zero-extends, the `(x<<15)>>16`
half-scale gated on the coord flag bit0, and both output stores) matches exactly. Ruled out on the
predication axis: zero-first if/else, compute-first if/else, per-condition `goto` (mwcc re-merges the
two gotos), inlined `static inline locate()`, and -O2,p/-O3,p/-O4,p (all give 200). The `bls` is the
tell -- retail branches where patch4 predicates, i.e. a compiler-BUILD difference (retail >=140
hypothesis), NOT a C-form we can reach. Do NOT retry without a newer mwcc. Semantics/readable C are in
src/overlays/ov005/nonmatching/func_ov005_02050d64.c.

## Constructor `size2` spill vs callee-saved -- definition-order allocation tie (mwcc 3.0/patch4)
func_ov228_020d2078 (x3, an object constructor). A value read early and used once late (here
`size2 = data_2cd8`, consumed only at the 2nd 020c9440 call, live across the whole first
subitem-creation block) forces a choice: keep it in a callee-saved register, or spill it. The ROM
SPILLS it -- `push {r3,r4,r5,lr}` (r3 = alignment padding that doubles as the spill slot),
`str r2,[sp,#0]`, later `ldr r1,[sp,#0]` -- and keeps `self` in r5. patch4 instead parks size2 in
callee-saved r5 and bumps `self` to r6 (`push {r4,r5,r6,lr}`, `mov r1,r5` at the use), which renames
the self base register in EVERY self-relative access. Net: mine is 344, ROM 348 (the one extra insn is
the `str [sp,#0]` spill), plus a pervasive r5<->r6 byte diff. Everything else matches, including both
bitfield RMWs (see codegen-cracks "explicit hi-byte insert"). Ruled out: size2 as an early local
(self->r6), inlining at the use site (self->r5 but no spill, 340 bytes), dropping the result temp.
The allocator picks by DEFINITION order, not usage priority -- the ROM's opposite choice is a
compiler-BUILD difference (retail >=140). Do NOT retry without a newer mwcc. Reconstruction in
src/overlays/ov228/nonmatching/func_ov228_020d2078.c.

Also banked in codegen-cracks.md: the u16 high-byte `hi |= K` RMW must be written EXPLICITLY, not as a
`unsigned short hi:8` bitfield -- the short-container bitfield adds a redundant `lsl#16;lsr#16` mask.

## ★ SALIDA UNICA vs epilogo predicado (`bne <fin>` vs `popne`) -- NO se ataca desde el fuente

El ROM salta a un `pop` compartido; mwcc emite `popne`/`popeq` en cada guarda. Visto ya en TRES
funciones de familias distintas:
- func_ov048_020b359c (12 B)
- func_ov036_020b35f8 (parte de sus 33 B)
- func_ov047_020b3630 (parte de sus 33 B)

Formas probadas y descartadas (2026-07-18/19):
- cadena `if (...) { ... }` con salidas naturales
- `else if` encadenado
- `else { if (...) {...} }` anidado
- guarda invertida con `return` temprano dentro de la rama
- variable "done" para forzar un punto de union
- ★ **forma anidada con salida unica REAL**: `if (a()==0 && b()==0) { ...; if (c()==0) { ...; } }`
  -- deja los `popne` exactamente igual.

El ultimo es el que cierra la cuestion: **la estructura del control de flujo en C no lo cambia.**
mwcc convierte cualquier salida en epilogo predicado cuando el epilogo es una sola instruccion.
Si aparece un crack, sera por otra via (¿un epilogo mas largo? ¿mas registros salvados?), no
reescribiendo los `if`. **No gastes mas compilaciones en reordenar las guardas.**

## Clase `WM_EndKeySharing_0x020b15a4` (r7/sb) — sexta familia, y ahora con el compilador descartado

`func_ov043_020b5274` (88 B, ARM) es la cabeza de una familia de **26 miembros** (ov030..ov062) y
cae en esta clase. Aportacion nueva del 2026-07-19: ademas de la busqueda sobre el fuente
(360 ordenes de declaracion x 4 formas de bucle x tipos x aridad 2/3), se probaron **los 27
compiladores** con `tools/allcc.py` — las 1.2 dan otro tamaño y **todas** las 2.0/3.0/dsi dan el
**mismo** residuo de 14 bytes. El eje del compilador esta cerrado para esta clase.

⚠ Esto la asciende de "empate probable" a "empate medido", pero **sigue sin autorizar a aparcar
por analogia**: la checklist previa al park (modo, aridad, constante en registro raro, releer el
diff) es lo que separo esta de las cinco de 2026-07-17 que resultaron ser argumentos perdidos.

## ★ CLASE TRANSVERSAL: "el ROM salta el registro libre mas bajo"

Descubierta el 2026-07-19 al aparcar cuatro familias seguidas y darse cuenta de que **el residuo
tiene la misma forma en las cuatro**: el codigo es instruccion por instruccion identico y lo unico
que cambia es que mwcc coge el registro libre mas bajo y el ROM coge el siguiente.

| funcion | miembros | residuo | ROM | mwcc |
|---|---|---|---|---|
| `func_ov043_020b5274` | 26 | 10 B | permutacion de r4..sb | otra permutacion |
| `func_ov035_020b39a8` | 20 | 8 B | (planificacion, otra clase) | |
| `func_ov181_020cd1e0` | 10 | 2 B | target=r7, owner=r6 | target=r6, owner=r7 |
| `func_ov134_020cc448` | 8 | 20 B | valor en r1, src=lr | valor en r0, src=ip |
| `func_ov038_020b4940` | 8 | 13 B | bloque en r1/r2 | bloque en r0/r1 |

**Son ~64 funciones bloqueadas por UNA pregunta.** Lo que ya esta descartado en las cinco:
permutaciones del orden de declaracion (120 y 360 exhaustivas en dos de ellas), formas del bucle
y del guard, tipos de los punteros, aridad de los callees, helpers `inline`, y **los 27
compiladores de `tools/mwccarm/`** (`tools/allcc.py`) -- todas las 2.0/3.0 dan el mismo residuo.

**Pista concreta, de `func_ov181_020cd1e0`:** alli el ROM le da el registro BAJO a la local con
MENOS usos (owner, 1 uso -> r6) y el ALTO a la de mas usos (target, 2 usos -> r7); nuestra build
reparte por orden de definicion. Si esa regla se confirma en otra funcion de la tabla, hay una
palanca de fuente (cambiar el numero de usos) y se desbloquean las cinco familias de golpe.

⚠ **No aparques nada nuevo por parecerse a esta entrada sin pasar antes la checklist previa al
park.** Cuatro de las cinco entradas de arriba llegaron aqui DESPUES de encontrarse arreglos
reales (unsigned char, offset partido, orden de los ceros, bitfield sin `& 1`) que las bajaron de
40-48 bytes a menos de 20. El parecido de la firma es el ULTIMO paso, no el primero.

## FAMILIA: bucle de slots con offset de stride grande (ov002, 2026-07-19)

Tres funciones con la MISMA rotacion de registros, byte-exactas en tamaño:
`func_ov002_02078f60` (72 B), `func_ov002_02077e68` (76 B) — y `func_ov002_02076534` (52 B), que SI
caso porque su stride era 4.

Forma:
```c
for (i = 0; i < 0x18; i++) {
    if (func_ov002_0207285c(i) >= 0) {
        node = *(char **)(world + off + 0xc4);
        while (node != 0) { next = *(char **)node; ...; node = next; }
    }
    off += 0x184;
}
```
El ROM reparte i->r6, off->r5, next->r4; mwcc r4/r6/r5. Probados cuatro ordenes de declaracion en
cada una.

**Por que no se arregla como la de stride 4:** alli `off` desaparece escribiendo el acceso como
indice de array (`tabla[i]`) y con eso el reparto cae solo. Con stride 0x184 haria falta una struct
de ese tamaño para poder indexar, y no la tenemos mapeada.

⚠ **Son un solo empate, no tres.** Si alguien encuentra la forma buena, valen las tres a la vez;
no las ataqueis de una en una.

# ===== CENSO DE PARKS DEL 2026-07-19: 13 funciones, TRES clases =====

Todas tienen **el tamaño exacto y las mismas instrucciones** que el ROM. No son errores de
lectura ni de semantica: la logica esta bien y verificada. Agrupadas para que nadie repita el
barrido funcion por funcion.

## Clase A — permutacion o rotacion de registros (9 funciones)

`CARDi_LockResource`, `func_ov002_0205e3e4`, `func_ov002_02077e68`, `func_ov002_02078f60`,
`func_ov002_02079224`, `func_ov023_0208632c`, `func_ov026_02085aa4`, `func_ov026_020866a8`,
`func_ov026_02089780`.

Sintoma: dos o tres registros intercambiados, todo lo demas identico. Ya probado en todas: ordenes
de declaracion (hasta seis por funcion), variables intermedias, tipos de parametro.

★ **Experimento HECHO (2026-07-19). Resultado NEGATIVO y util.** Pasadas por `tools/allcc.py`
(27 builds) dos funciones representativas, `func_ov002_02079224` (THUMB, 1 registro) y
`func_ov026_02089780` (ARM, 2 registros):

- **TODOS los builds 2.0 y 3.0 dan EXACTAMENTE el mismo residuo** (2 y 16 bytes respectivamente).
- Los 1.2 salen peor o no compilan; los `dsi/*` mucho peor (10 bytes en la primera).
- 3.0_136 no compila (le falta el parche de licencia).

O sea: **la version del compilador NO explica la clase A.** Todas las builds de la era correcta
reparten los registros igual, y ninguna coincide con el ROM. Deja de sospechar del compilador para
estas y **no repitas el barrido** -- son 27 compilaciones por funcion y ya esta contestado.

Lo que queda por probar en clase A (por orden de coste):
1. Los NIVELES de optimizacion (`-O3,p`, `-O4,s`) en la misma build, que allcc.py NO varia.
2. Que el fuente original declare las variables en un ambito distinto (dentro del bucle en vez de
   arriba), que es un eje que no he tocado sistematicamente.

## Clase B — planificacion: una instruccion adelantada o retrasada (3)

`CARDi_UnlockResource`, `OS_WaitIrq`, `func_0200ea64`.

Sintoma: mwcc mete una operacion en un hueco de carga-uso, o adelanta el calculo de un puntero por
encima de una salida rapida. El ROM agrupa donde mwcc intercala.

★ **Experimento HECHO (2026-07-19) con `tools/allopt.py` (nuevo). Resultado NEGATIVO.**
Probados los 13 niveles (`-O0..-O4` x `p`/`s`) en `OS_WaitIrq` y `func_0200ea64`:

- `-O3` y `-O4` son **identicos** entre si y con `-O4,p`, en las dos funciones y con los tres
  sufijos (`p`, `s`, ninguno). El sufijo de velocidad/tamaño **no cambia nada** aqui.
- `-O2` difiere un poco (peor), `-O1`/`-O0` cambian el tamaño.

O sea: **el nivel de optimizacion tampoco explica la clase B.** Con A (build del compilador) y B
(flags) descartados, lo que queda es que el FUENTE original tenga una forma que no he probado.

⚠ **Aviso sobre la metrica:** la distancia enmascarada que imprimen `allopt.py`/`bytedist.py` NO
mide "lo cerca que estas" cuando hay codigo DESPLAZADO -- una sola instruccion movida hace que
todos los bytes siguientes cuenten como distintos (`func_0200ea64` sale con 107 bytes de distancia
y esta a UNA instruccion). Usalas para comparar variantes entre si, nunca como medida absoluta;
para eso esta `diffdis.py`.

## Clase C — donde se materializa un valor compartido (2)

`OS_CreateThread` (el cero de dos campos), `func_0200c4fc` (el bool de exito).

Sintoma: el ROM saca la constante a un registro ANTES del store que libera el registro obvio; mwcc
espera. En `func_0200c4fc` ademas `tst #0xff` frente a `cmp #0`, que apunta a un tipo de ancho byte
que no he sabido reproducir sin añadir un enmascarado.

★ **Experimento HECHO (2026-07-19), y funciono a medias.** Buscando funciones ya casadas con
`tst rX,#0xff` aparece `func_ov002_02053790`: el `tst` viene de un **`& 0xff` EXPLICITO en la
condicion**, no de un tipo de ancho byte.

    if ((ok & 0xff) == 0) { ... }      /* -> tst r0,#0xff   */
    unsigned char ok;                   /* -> and r0,#0xff de mas, +4 bytes (pista falsa) */

Con eso `func_0200c4fc` pasa de tres diferencias a UNA: el orden de los dos `mov` condicionales
(`movlt`/`movge`). Probadas siete formas de escribir el bool; mwcc las normaliza todas a
movge-primero. `OS_CreateThread` no se beneficia (su problema es otro: donde materializa el cero).

★ **Lo que falta ahora:** solo el orden de los dos `mov`. Busqueda HECHA (2026-07-19):
**CERO funciones casadas en todo el proyecto tienen `movlt rX,#0` seguido de `movge rX,#1`.**
(Busqueda sobre todas las de auto/ y calls/ de menos de 600 B, modo ARM, que es donde vive ese par.)

O sea: no es que se me olvide como se escribe, es que **ese orden no se ha reproducido nunca
aqui**. Deja de buscarlo en el arbol; el siguiente paso util es `tools/allcc.py` sobre esta funcion
-- si otro build de mwcc emite el par al reves, la explicacion es el compilador y no el fuente.

---
**Regla que sale de este censo:** cuando una funcion llegue a "tamaño exacto, mismas instrucciones",
mirar PRIMERO si encaja en una de estas tres clases y anotarla ahi, en vez de escribir un park
nuevo. Trece write-ups individuales cuestan mas de leer que tres clases con un experimento cada una.

## Clase D (nueva, 2026-07-19) — reutilizacion de una constante del pool

`func_ov002_02079adc` (88 vs 84). Dos offsets grandes que se diferencian en poco (0x1c2 y 0x1ce):

    ROM   ldr r0,=0x1c2 / strb / ldrb / cmp / adds r0,#0xc / strb    (reusa y suma)
    mwcc  ldr r0,=0x1c2 / strb / ldrb / cmp / ldr r0,[pc,..] / strb  (recarga del pool)

Probado: `self[0x1ce]`, `self[0x1c2 + 0xc]`, puntero `p = self + 0x1c2` con `p[0xc]`, y variable de
indice `int off = 0x1c2` con `off + 0xc`. mwcc recarga en las cuatro.

No encaja en A (registros), B (planificacion) ni C (materializacion de un valor): aqui el problema
es que mwcc no reutiliza una constante que ya tiene en un registro. Si aparece otra igual,
agruparla aqui.

## 4-byte halfword-pair copy: high-first ONLY at source offset 0 (2026-07-20)

mwcc 3.0/139 copies a `{u16,u16}` struct high-halfword-first when the source is at offset 0
and low-first at ANY non-zero offset.  Measured by taking func_ov123_020cce74 (matches,
emits high-first) and moving only its offset:

    *(pair *)&data          -> high-first      ((pair *)&data)[1]        -> low-first
    *(pair *)(data + 8)     -> low-first       tbl.p (struct member)     -> low-first
    pairs[2] (array)        -> low-first       *(pair *)((char*)&data+8) -> low-first

So a function whose ROM copy sits at a non-zero offset AND is high-first has no known
spelling on this compiler: func_ov117_020cd494 (x5, 4 instructions) and
func_ov141_020cd2b0 (x7) are both parked on exactly this.

Retracts the earlier theory that the reversal "depends on a later partial overwrite".  That
came from func_ov131_020cdf20, which copies at offset ZERO and merely happens to have an
overwrite after it.  When two candidate causes co-occur in one example, vary them
separately before writing either into a note.

## Pool-loaded SMALL ENCODABLE immediate -- no C form reproduces it (2026-07-20, MEASURED)

Symptom: the ROM does `ldr rX,[pc,#N]` where the pool word holds a small value like 12, 11 or
0x18 -- values `mov` encodes directly -- and keeps it in a callee-saved register across calls.
mwcc always emits `mov rX,#12`. In ARM the instruction counts match, so the diff is exactly the
**+4 bytes of the pool entry**.

**This is a CLASS, not a one-off:** five `# DEFER` entries in ov000's worklist alone
(0204f404, 0205a4d4, 02054b1c, 0205a554, 0204f47c) plus func_ov023_020829c4.

**Measured -- do not re-grind the SOURCE axis.** Six spellings against a minimal reproducer
(`f(0,12); f(0,12);`), in both ARM and THUMB:

    literal 12 .................... mov
    static const int K = 12 ....... mov
    local const int K = 12 ........ mov
    enum { K = 12 } ............... mov
    used 4x / across a branch ..... mov
    static const volatile int K ... pool load of the ADDRESS + deref (two loads, wrong shape)
    extern const int K ............ pool load of the ADDRESS + deref, held in r4 (closest, still wrong)

The detector was proven positive by the last two rows, so this is a real negative and not a
search that could not have found it.

### The build axis is now CLOSED too (swept 2026-07-20)

**26 of 27 mwccarm builds: zero pool loads.** Every 1.2, 2.0, 3.0 and dsi build emits
`mov rX,#0xc` for the reproducer. (3.0_136 is the unpatched-licence binary and does not compile;
3.0_136_patched does and behaves like the rest.) Optimisation level swept as well -- `-O0` through
`-O4`, plus `-O4,p`, `-O4,s` and `-Os`: identical output, no pool load at any level.

So **both axes a park note would normally rest on are measured and closed**: no C spelling and no
compiler configuration reproduces it. What remains is that the constant in the ORIGINAL source was
probably not a plain literal at all -- the closest behaviour found was `extern const int K`, which
pool-loads the symbol's ADDRESS and derefs it while holding the value in a callee-saved register.
That is +8 rather than +4 and the wrong instruction shape, but it is the only construct that gets
the register discipline right, and it points at these constants having lived in another
translation unit.

**Do not re-run the source sweep or the build sweep.** If this class is attacked again, the
untested axis is the SHAPE of the original declaration, and it needs one of the five functions'
actual C to work against -- the lane deferred them without leaving a mismatching `.c`, so that has
to come from the lane.

---

## ★★★ RETRACTED 2026-07-22: the "x5 @120B" family is NOT the 02054d3c strength-reduction tie

`references/state.md` carried this, twice, as a do-not-touch:

> **NOT** the x5 @120B group (`ov005_0204e400 ... ov008_02054cc4`) -- that IS the 02054d3c
> strength-reduction tie, it will not match.

**All six matched** (ov000/005/008/009/025/026, 120 B, 2 relocs). The lever was arity:
`func_02032634` takes THREE arguments. Nothing to do with loop strength reduction.

The failure mode is worth naming, because it is not the usual one. This was not a park note that
over-generalised from its own attempt -- it was a claim about a WHOLE FAMILY, inferred from a
*sibling* function's tie and never tested on the family itself. That is strictly worse than an
over-confident park: it fences off N functions on the evidence of one, and it reads like settled
fact because it appears in the "fresh veins" section rather than in a park header.

**Rule: a tie is a property of a FUNCTION you measured, never of a family you did not.** If you
want to warn about a family, say which member you tested and leave the rest explicitly open.

## ★★ THE BEST RESCUE QUEUE IN THE TREE: `python tools/audit_arity.py`

Run it over `nonmatching/`. On 2026-07-22 it reported **8 of 416 parked files with an arity
disagreement**, and the first one attacked matched **on the first compile**:

- `func_ov002_02079224` -- `func_020235d0` declared with 1 parameter, **49** call sites in the tree
  pass 2. Its park note said *"the ROM loads the type byte in r1 and leaves r0 free for the result;
  mwcc loads it in r0 and overwrites it. Blocked class."* That is the arity signature verbatim:
  r1 still holds the type byte at the `bl` and nothing writes it in between.
- `func_ov002_0205e3e4` -- `func_ov002_0205bff4` declared 1, tree uses 2. Still parked at 2 bytes,
  **but its C was wrong**: the missing argument is the REMAINDER of the `_s32_div_f` call on the
  line above (`self[4] % 6`), which the old C invoked and discarded. The divide block now matches.

Still open on that list, in rough order of signal strength:
`src/nonmatching/func_02020928.c` (`func_02020a78`: no prototype, called with 1, tree uses 2 x11);
`ov107/func_ov107_020c7b70.c` (`func_0203bfb4`: declared 3, tree uses 2 x8);
`ov000/func_ov000_02054e48.c` (`func_02020904` declared 1 vs 0; `func_ov000_020549fc` 2 vs 3);
`ov008/func_ov008_02077908.c` (`func_ov008_02074758` 2 vs 1);
`ov003/func_ov003_0204d98c.c` (**four** disagreements, incl. `func_02024a6c` 3 vs 5);
`ov003/func_ov003_0204cba0.c` (`func_0202e4f4` 4 vs 2).

## ★ CLASE ABIERTA: constante pequena que la ROM saca del POOL y mwcc emite como `movs` (2026-07-22)

**Dos instancias independientes, mismo residuo exacto de 4 bytes** (la ROM tiene una palabra de
pool de mas; el codigo mide igual porque `ldr rX,[pc,#N]` y `movs rX,#imm` ocupan 2 bytes en THUMB):

- `func_ov002_0206a418` / `func_ov002_0206a46c` — almacenan **0x17 / 0x18** (ids de overlay 23/24)
  en un campo y luego los releen para pasarlos al loader.
- `func_ov022_02083bd8` — pasa **0x6a** como segundo argumento a `func_0201e4a8`.

Todas estas constantes **caben en un `movs` de THUMB** (0-255), asi que no hay razon de encoding
para el pool.

**Descartado hasta ahora** (8 variantes): `long` / `0x17L`, `const int` local, `enum` con
`-enum int`, campo `volatile`, campo `unsigned`, setter `static inline`, **tipo puntero** en el
campo y en el parametro (`(void *)0x6a`), y decimal en vez de hex.

**Ideas sin probar:** constante usada dos veces en la funcion (forzando CSE al pool); `static const`
a nivel de fichero; constante de coma flotante/fixed convertida; que la constante venga de una
macro que expande a algo con un cast raro.

⚠ **NO es un empate de register allocation** — las instrucciones y los registros coinciden. Es una
decision de materializacion de constantes, y como se repite en dos overlays sin relacion, **crackear
una crackea las tres**. Vale la pena atacarla cuando haya presupuesto: es la unica clase que ha
aparecido dos veces sin ceder.

## ★ SEGUNDA CLASE ABIERTA: `adds rX,rX,#0` donde mwcc emite `cmp rX,#0` (2026-07-22)

`func_ov181_020ccf18` **y sus cinco gemelas byte-identicas** (ov182/183/184/250/251, 76 B). Todo
coincide salvo **una instruccion**: la ROM pone flags sobre el resultado de una llamada con
`adds r0,r0,#0` (un ADD que actualiza flags) antes de un ternario `mvnne`/`moveq`; mwcc emite
`cmp r0,#0`. **Crackearla vale 6 funciones.**

Descartado: `!= 0` explicito, truthiness, `if/else` en vez de ternario, retorno `unsigned`,
retorno `signed char`, `+ 0` explicito en la expresion. (`long long` desborda el tamano.)

Es la **misma naturaleza** que la clase de la constante del pool: una decision de
**materializacion**, no un empate de register allocation. Las dos clases juntas bloquean 9
funciones conocidas.

## Residuos anotados de la cola de parks (2026-07-22)

Para no repetir trabajo — todas en `build/try/`, con el eje ya descartado:

| funcion | residuo | ejes descartados |
|---|---|---|
| `func_0200dcf0` | 1 reg | bucle de espera; la direccion debe quedarse en registro. do/while, while, `volatile` retenido |
| `func_ov002_0205e1b8` (+gemela) | 1 reg | orden de las dos cargas de pool; orden de declaracion |
| `func_0201a284` | 4 B | la ROM lee la MISMA ranura dos veces; mwcc hace CSE. `volatile` corrige el tamano pero no el registro |
| `func_ov024_02083414` | 1 rama | las dos orientaciones del `>=`/`<` |
| `func_ov022_0209be44` | 8 B | la ROM descompone un mismo offset 0x2c20 por **dos rutas distintas** |
| `func_ov008_02051168` | 1 reg | la ROM reutiliza el registro de argumento recien liberado |
| `func_ov008_02072fe4` | 4 B | le sobra un `add r0,r0,#0` sin origen aparente |
| `func_ov008_0204eb88` | ±4 B | la ROM tiene test-contra-0 **y** `cmp`/`cmpne`; switch+guarda = +4, if-chain+guarda = -4, switch sin guarda = -8 |
| `func_ov006_0204e35c` | 1 reg | la ROM prepara el retorno 0 antes de tocar la global |
| `func_ov008_0205b720` | 4 B | la ROM calcula `id << 8` una vez; atarlo a un local no lo recupera |
| `func_ov119_020ce610` (+gemela ov272) | scheduling | la ROM guarda el 0 antes de cargar el literal; mwcc iza la carga del pool |
| `func_02034428` | 2 B corta | — |
| `func_ov022_020b02a4` | 2 B larga | — |
| `func_01fffac0`, `func_ov022_02086ec0` | 1 reg | — |

## Residuo medido: `func_ov008_0205ca8c` / `func_ov025_0208f020` (124 B, par dedup)

Tabla de saltos sobre `opcode - 0x13` en rango 0..8. Casos 0x13/0x14/0x15/0x1b limpian la ranura y
devuelven 1; 0x16..0x1a y el default caen a `func_020343cc`. La estructura, la tabla y los casos
son **correctos** — sale **132 vs 124**.

Los 8 bytes son **dos `mov r0,#1` que la ROM iza**: materializa el 1 UNA vez, justo antes del
`cmp`, y las dos vias de limpieza (una predicada con `popeq`, otra al final) lo comparten. mwcc lo
hunde en cada bloque.

Probado sin efecto: `int done = 1` como inicializador, `default:` explicito en el switch, listar
tambien los casos 0x16..0x1a con `break`, y dos constantes separadas (`done`/`none`) para que el 0
del store salga por r1 como en la ROM.

⚠ **Un `goto` a un bloque de limpieza compartido NO es la respuesta**: la ROM tiene DOS bloques de
limpieza distintos, solo comparte la constante. Es izado de constante, no fusion de bloques.

## Residuos de la cola de parks — segunda tanda (2026-07-22)

| funcion | residuo | ejes ya descartados |
|---|---|---|
| `func_ov033/035/039/041_...` (4, familia emisores) | 1 instr de scheduling | **tamano ya correcto** tras poner el byte de estado `unsigned`. La ROM calcula el argumento `anchor` ANTES de cargar el literal de pool del descriptor; mwcc iza la carga. Probado: `&`-de-struct, locales pre-atados, inline |
| `func_ov231_020ccc48` (+gemela, 272 B) | 16 B de mas | selector de punto de spawn con **Vec3 por VALOR** (la ROM lo escribe bajo `sp` con `stm` y recarga dos palabras en r2/r3). Estructura correcta |
| `func_ov022_02090f14` | `ble` vs `beq` | la ROM compara el contador con `ble` (con signo) tras un `ldrb` sin signo; mwcc sabe que un `unsigned char` no es negativo. `signed char` convierte la carga en `ldrsb`. 3 formas |
| `func_ov022_020911a8` | 4 B | el kind 0 se PRUEBA primero pero su bloque va el ULTIMO. Anidar el kind 1 dentro del brazo no-cero da el orden pero pierde 4 B |
| `func_ov022_020ad7f0` | 1 instr izada | **tamano correcto**. La ROM reconstruye la direccion de la entrada DENTRO de la rama de copia; atarla a un local la iza sobre el `tst`. 3 formas |
| `func_ov022_0209b078` | 4 B corta | 5 slots de sample; `(unsigned short)i` y `(short)bank` ya correctos |
| `func_ov022_020b0ba8` | ver nota | con `char*` + `i*0x80` sale **80** (8 de mas); con **indice de struct** sale el **tamano correcto (72)** pero mwcc reduce el indice a un walker y pierde el `add r2, lr, ip, lsl #7`. El count tambien quiere r4 (callee-saved) y sale en r2 |
| `func_ov025_020829f8` | 1 instr predicada | la ROM materializa el 0 **incondicionalmente** entre el `tst` y el `popne`, compartido con el `moveq` final; mwcc lo predica. 3 formas incl. variable de resultado compartida |

## ★ CLASE: la ROM carga un literal del POOL antes/despues que mwcc (2026-07-22)

Tres sitios independientes con el mismo sintoma, todos con **tamano correcto** y solo el orden de
una carga `ldr rX,[pc,#N]` movido una o dos posiciones:

- `func_ov033/035/039/041_...` (familia emisores, 4 funciones): la ROM calcula el argumento
  `anchor` **antes** de cargar el literal del descriptor; mwcc iza la carga del pool.
- `func_ov002_0205e1b8` (+gemela): la ROM carga **las dos** palabras de pool (direccion de la
  global y offset 0x4a4) antes de desreferenciar; mwcc intercala el deref.
- `func_ov119_020ce610` (+gemela): la ROM guarda el 0 antes de cargar el literal; mwcc iza la
  carga.

**No es orden de declaracion** — probados 3-4 ordenes en cada uno. Tampoco es el tipo del simbolo
(`&`-de-struct, array vs puntero). Parece una decision de **scheduling de cargas de pool** que
depende de algo que aun no se ha identificado. Nueve funciones bloqueadas entre las tres.

## ★ CLASE: `ble` (con signo) sobre un contador cargado con `ldrb` (2026-07-22)

Dos funciones bloqueadas por lo mismo (`func_ov022_02090f14`, `func_ov022_020912d8`), las dos con
**todo lo demas ya correcto**:

```
ldrb r0, [r6,#0x19]     <- carga SIN signo
cmp  r0, #0
ble  <salir>            <- comparacion CON signo
```

mwcc sabe que un `unsigned char` no puede ser negativo y emite `beq`. Descartado: `unsigned char`,
`int` (cargado del campo unsigned), bitfield `unsigned char : 8`, `signed char` (convierte la carga
en `ldrsb`), y la forma `for` vs `do/while` vs guarda explicita.

Algo hace que el compilador original **no** propague el rango del `ldrb` a la comparacion. Sin
identificar.

## Familia de rango 0x1a0 / 0x1c8 / 0x1c9 / 0x201 (2026-07-22)

`func_ov008_0208b7a8` (72 B) y `func_ov008_0208a5e8` (88 B) prueban **los mismos cuatro ids**
(1, 0x1a0, 0x1c8, 0x1c9) con la misma division de rango, una devolviendo la pertenencia y la otra
el complemento mas un tope en 0x201.

Las dos quedan a **4 bytes** y por el **mismo motivo**: la ROM pone el bloque ALTO despues del
`bgt` (salto hacia delante) y el bloque BAJO fisicamente primero; mwcc invierte el layout.
Probado en las dos: `if (id > 0x1a0){...}` primero, `if (id <= 0x1a0){...}` primero, `if/else`,
y `goto` a una etiqueta comun (esta ultima es la mejor: 84 vs 88 y 76 vs 72).

Crackear una crackea las dos.

## `orr rD, rN, #0` donde bastaria `mov` -- sigue abierto

`func_ov008_0205b720`: la ROM copia el id con `orr r1,r5,#0` antes de desplazarlo; mwcc hace el
`lsl` directo desde el registro fuente y sale 4 bytes corta. Probado: local intermedio, local
`unsigned`, peticion entera en variable, callees declarados `(void)` como en el hermano
`func_ov008_0205b770` **ya matcheado**, y el truco `| (pad - pad)` que si funciono para
`adds rX,rX,#0` en la familia SpawnHook (aqui mwcc lo pliega y desaparece el `orr`).

## Clase abierta: la copia del objeto va ANTES de la extension de signo

Tres funciones, todas con la firma `(objeto, short)` y un bucle:
`func_ov048_020b4050`, `func_ov022_0208a8bc`, `func_ov022_020914a0`.
En las tres el stream es identico y el tamaño exacto; el unico residuo es el arranque:

```
ROM :  mov r6, r0          ; copia el objeto fuera de r0
       lsl r0, r1, #0x10   ; ...y usa el r0 liberado como temporal del shift
       asr r8, r0, #0x10
mwcc:  lsl r1, r1, #0x10   ; desplaza el parametro EN SITIO
       mov r7, r0          ; y copia el objeto despues
       asr r6, r1, #0x10
```

Descartado en las tres: todos los ordenes de declaracion, el cast fuera del bucle, el cast
inline en cada call site, el cast como sentencia dentro del bucle (para que lo hoistee), y
`short` en el parametro (que no genera extension ninguna).
**Si cae una, caen las tres.** Es lo mismo que la clase del literal del pool en r0 vs r1/r2:
mwcc siempre prefiere el registro bajo libre, la ROM reserva r0.

---

## ★★★ RETRACTADO 2026-07-23 -- cinco entradas de esta lista han casado

Las cinco estaban descritas aqui como empates y ninguna lo era. Se corrigen en su sitio? No: se
retractan en bloque, porque el patron comun es mas util que las cinco filas.

| funcion | lo que decia la ficha | lo que era de verdad |
|---|---|---|
| `func_ov008_02072fe4` | "ningun C reproduce el `add r0,r0,#0`" | el idiomatico `(char *)0 + x`, ya catalogado |
| `func_ov008_0204eb88` | "tail-merge tie" | un `if` de no-cero ENVOLVIENDO un switch de dos etiquetas |
| `func_ov008_0205714c` | "scheduling tie, las dos cargas independientes al reves" | era una copia de struct, no tres asignaciones |
| `func_ov002_02079adc` | "reutilizacion de constante del pool (clase nueva)" | un indice mutado (`off = off + 0xc`) |
| `func_ov008_02077908` | "los dos valores son simetricos en el clamp" | lo son; hacian falta DOS cambios de orden a la vez |

**La leccion transferible es la ultima.** Esa ficha probaba dos ordenes de declaracion y un
inline, cada uno por separado, y todos daban el mismo residuo -- que es exactamente lo que parece un
empate. Hacian falta el orden de las CARGAS y el orden de las DECLARACIONES *a la vez*.
Cuando un eje "no mueve nada", comprueba si hay un segundo eje que lo esta enmascarando antes de
escribir que el eje esta descartado.

Y ademas: `func_02023c60` llevaba "empate probado en las 27 builds" y cayo con una asignacion
encadenada; `func_0200dc70` decia que los contadores frescos estaban descartados "en los dos ordenes
de declaracion" cuando hay seis.

## ⚠ RETRACTADA 2026-07-24: "constructor size2 spill" (func_ov228_020d2078)

La entrada decia que el derrame de `size2` a la pila era "definition-order vs usage-priority
allocation, i.e. a compiler-BUILD difference (retail >=140 hypothesis), not a reachable C form".
Es alcanzable: `volatile int size2;` produce el `str [sp]` / `ldr [sp]` de la ROM y arregla el
push. La funcion pasa de 340/348 a **348/348 exacto** con 27 diferencias de planificacion.
Misma palanca en `func_ov221_020d4020` (500 -> 504 exacto, 5 diffs) y, en la direccion contraria
-- forzar la RELECTURA de un parametro en vez del cacheo --, en `func_02034fc4` (90 -> 100
exacto, 6 diffs). Ver codegen-cracks.md, "volatile = no lo guardes en un registro".

## 2026-07-30 — two epilogue ties on Slot_Spawn's frontier (build/try/)

Both are byte-close near-misses kept in `build/try/` (NOT parked/nonmatching).
The main logic of each is byte-exact; only a trailing epilogue diverges.

### func_020329e8 — Slot_AllocFromPool (148B, build/try/329e8.c) — REGISTER-COLORING tie
Doubly-linked-list allocator: pop free-list head (base+0xb46e4), splice onto
active-list (base+0xb46e8), stamp state (flag@+0xb47b4 ? 5 : 1) and a 24-bit
rolling seq id (data_020429e8). base = *data_0204c234.
- **Instructions 0-28 (the entire splice) BYTE-EXACT.** Only the 5-instr seq-id
  tail differs: ROM holds the counter `c` in r2 and reuses r2 for the mask
  (`bic r2,r2`); mwcc colours `c` into r3, so it stores the counter before the
  bic. Diff first appears at 0x75. Single r2/r3 swap.
- The winning structure: type the pool as a struct BASED AT `base` with the
  list heads as fields at +0xb46e4/+0xb46e8 (huge `char pad[0xb46e4]`), so each
  field access forces `add rX, ip, #0xb4000` + small-imm (matches the ROM's
  recomputation) instead of caching a sub-base (140B, too short) or pooling the
  full 0xb46e4 offset as an index reg (156-164B, too long). flag = `unsigned
  char` → ldrb (signed char gives ldrsb). ~14 variants; 0-28 pins the allocator
  state so the tail colour can't be steered.

### func_02012354 — object rebuild/refresh (240B, build/try/12354.c) — GUARD-PREDICATION tie
9 sequential calls; guard, two func_02011c7c (1st discarded), func_020118c4 +
cache@+0x30, func_0201231c seed, mode 0/2/else transform dispatch, then a tail
guarded by two checks.
- **Instructions 0-39 (all calls + the whole dispatch) BYTE-EXACT.** Only the
  two trailing guards `(*(sheet+0xc)!=0)` and `(*(param_1+0x38)!=-1)` differ.
- ROM emits each guard as an UN-COMBINED materialised boolean
  (`cmp; movne #1; moveq #0; cmp #0; popeq`) short-circuited by two separate
  popeq (240B). mwcc build 139 instead: collapses to a compact short-circuit
  (`&&`/nested-if/separate-`==`-returns all → 208B); or when forced to
  materialise via `!!`/ternary, EITHER combines the two tests into one popeq
  (both-bools-upfront → 232B) OR materialises guard 1 and predicates guard 2
  (`ldrne/mvnne/cmpne` → 220B). ~24 variants (&&, ||, nested, separate returns,
  !!, ternary, upfront vs short-circuit bool locals, volatile, goto, order
  swap) — NONE reproduces "short-circuit + two materialised branches".
- **Open lever for next session:** find what makes mwcc emit a materialised
  boolean for a 2nd guard in its own basic block (not predicated, not combined).
  The `!!x == 0` idiom reliably materialises the FIRST guard; the blocker is the
  SECOND always folding/predicating.

## 2026-07-30 — func_0201292c BgExtPltt_Upload (build/try/1292c.c) — SR / param-colour tie

BG extended-palette upload with GX/GXS function pointers + an indexed per-block
loop. **Structurally byte-exact, 2 words over (312 vs 304).**

⭐ **STRUCT CRACK CONFIRMED AND EXTENDED (codegen-cracks line 2177).** Typing the
two descriptor params as structs (BgPlttSrc @0/8/0xc, BgPlttReq count@0/table@4)
instead of raw `int*` / `param_2[3]` indexing was the breakthrough on a
reload-per-iter loop: it fixed a FUNCTION-POINTER spill (the ROM keeps `load` in
fp; raw-cast mine spilled all three fps to a 4th stack slot, pushing r3 for
alignment) AND corrected the param register colouring (param_2->sl, param_3->sb).
Push dropped from 10 regs to the ROM's 9. So the crack isn't only about base+imm
addressing — it relieves enough pressure to change which values get registers.
Also: `switch(format)` gives the ROM's branchy block-size dispatch (if-else-if
predicates it, −2 words).

**Residual tie:** the ROM computes the per-block dest `mla blocksize,i,data` fresh
each iter (i stays live from the `table[i]` index); mwcc build 139 strength-reduces
`blocksize*i` into a 2nd induction variable (`mov r7,r5` + `add r7,r7,r8`), +2
words. Root: param_1 colours r5 (mine) vs r4 (ROM); the ROM recycles param_1's
dead register for `data` (feeding the mla), mwcc recycles it for `i`. ~20 variants
(operand order, int vs ptr arithmetic, explicit offset locals, data hoist, decl
order, register, vram-in-branch, DC_Flush position) — none flips the colouring.
Next-session lever to try: force `data` (param_2->data) into param_1's freed
register, or increase pressure so mwcc drops the induction variable.

## 2026-07-30 (iter 3) — func_02012f54 BgCharVram_Upload (build/try/12f54.c) — symmetric w<->h colour tie

Char/BG VRAM upload setup: per-screen char-block table lookup, DISPCNT-derived
base, two tile-count limits from func_020149c4, min-clamp, 10-arg call to
func_02013484. **Byte-exact except a symmetric w<->h register swap (9 insns).**

Cracks that WORKED to get here (all instr 0-17 byte-exact):
- compute the tile offset `(tileWord & 0x1f00) >> 8` into a LOCAL before the
  base if/else, so mwcc hoists it ahead of the branch (matches the ROM).
- compute `w = uw>>3` and `h = uh>>3` BEFORE the func_020149c4 call; then the
  w-clamp recomputes `uw>>3` (barrel, uw survives in a callee-saved reg) and the
  h-clamp compares the stored `h` (uh dies in scratch). This asymmetry is what the
  ROM does; computing w/h after the call forces both uw and uh to survive (+regs).
- shifts on UNSIGNED values (`unsigned int uw = *param_2; uw>>3`) give `lsr`; the
  base bit-extract `(dispcnt & 0x38000000) >> 27` on the volatile-unsigned read is
  also lsr; the tile `(tileWord & 0x1f00) >> 8` is a signed int shift = asr.

Residue: the ROM reads src->h (offset 2) before src->w (offset 0) and colours
w->r5 / h->r6; mwcc build 139 reads the ascending [r7] (offset 0) first and
colours w->r6 / h->r5. Pure symmetric swap of two free callee-saved registers.
~16 variants (compute/read/clamp/decl order, struct typing, w-after-dest) — mwcc
always schedules the ascending load first. Next lever: force the descending field
read, or an asymmetry that makes src->w's derivative claim r5.
