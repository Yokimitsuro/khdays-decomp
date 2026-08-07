# Shape-family map & high-yield veins

Match ONE template by hand, fan out mechanically (`genfamily.py` for stub families,
`dedupprop.py` for byte-identical masked-hex twins, hand-template for structural
families). The `.c` symbol stays `func_ovNNN_ADDR`.

## The c634 handler vein (BIGGEST — ~1800 tractable, enemy/actor overlays)

`func_0203c634` is the state-machine slot-dispatch (`SetIndexedSlot`). Enemy/actor
node update-callbacks share a skeleton and END with a dispatch:

```c
void func_ovNNN_ADDR(int param_1) {
    int owner = *(int *)(param_1 + 4);
    /* ... body: guards, field updates, anim kicks, sub-calls ... */
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ovNNN_NEXT);
}
```

- 2nd arg is usually `*(signed char*)(param_1+0x20)`, but some pass a literal (0/1/2).
- 3rd arg (next-state callback) is often the constant `0` (reused from a `mov r2,#0`)
  — a handler with only the c634 reloc still has a valid `0` transition.
- Common hubs (extern `int f(int, …)`): **020c9264** (anim kick, `f(obj,anim,flag)`),
  **020c9ee8** (sub-anim restart), **020c5af8** (4-arg timer-arm
  `f(obj, id, mode, *(owner+8))`), **02031384** (sprite request, atomic-hpair),
  **020cab14** (spawn child), **020cdb50** (stack-out vector fetch).
- Busy guard idiom: `if (*(unsigned char*)(*(int*)(owner+4)+0xad) != 0) return;`.
- Latch idiom: `*(unsigned char*)(*(int*)owner+0x1c7) = K;` (sub-state).

### ★ The move-dispatcher sub-vein — GENERATE it, don't type it

208 near-identical "move dispatchers" (one per enemy/actor overlay). **Find them all with:
`sum(1 for _,s in relocs if s == 'func_0203c634') >= 6`** over `func_index.json` — that one
predicate is the whole census. As of 2026-07-16: 180 done, 28 open.

Three tools, in the order you should reach for them:

1. **`python tools/genmove.py func_ovNNN_ADDR [-w]`** — parses the reset block and emits the whole
   C. This is the default move: it matched 15/24 open dispatchers in one sweep, first try each.
   It **refuses** rather than guesses when the reset (or an arm) is not a shape it knows, and a
   refusal is real signal — that dispatcher carries extra code and needs a human. Validated by
   regenerating 8 hand-matched dispatchers byte-exact. If you teach it a new reset block, re-run
   that regression set before trusting it.
2. **`python tools/clonedispatch.py <src_c> <src_fn> <dst_fn>`** — when a *matched* dispatcher has
   a byte-identical twin in another overlay (same size, same reset, same case order), clones the C
   with the handlers remapped. Refuses unless all three agree.
3. **`python tools/dumpdispatch.py func_ovNNN_ADDR`** — the raw view, for when the other two
   refuse. Prints the reset block plus the case→handler map **in source order** (bodies follow
   source order, the table is index-ordered).

Rank leftovers by **bytes-per-arm**: ~39-42 = plain; ov236's 95 B/arm meant its cases carried real
code and it was not plain at all.

**Twin clusters are the multiplier.** Group the *open* ones by (size, reset tuple, case order) —
matching one rep per cluster gave 2-3 functions each. Do that grouping before picking singles.

**Still open (2026-07-16), all needing hand work:**
- dense-switch, 9 left: `ov185/186/187_*` (keep self in r5, `popeq`, pool load in the reset →
  they call something), `ov237_020cd554`, `ov245_020ccfa8`, `ov253_020cd2a4` + `ov253_020cedc4`
  (read +0x1c6 **directly**, `cmp #7` — a different dispatcher entirely, not the queued-move
  shape), `ov254_020cdccc`, `ov258_020cd748`.
### ★ The 19 "no jump table" ones are NOT dispatchers — they are the move CHOOSERS

The `>=6 c634 relocs` census catches both halves of the mechanism, and they are opposites:

| | move dispatcher | move chooser |
|---|---|---|
| `+0x1c7` (the queue slot) | **reads** it, then clears it to -1 | **writes** it |
| shape | dense jump table over `+0x1c6` | if-else chain, no jump table |
| c634 3rd arg | the handler for that move | `0` (just "run the queued move now") |

So `dumpdispatch`/`genmove` printing "no jump table found" is not a limitation to route around — it
is telling you this is a different function. Do **not** template a chooser off a dispatcher.

A chooser is the enemy's actual AI decision: acquire the target (`func_020cab14`), take the vector
to it, normalise for distance, compute the facing angle (`func_020050b4` = atan2), then roll
`RandNextScaled(0x65)` (a d100) and pick a move from the roll, the gap between the two collision
radii (`+0x80` each), and whether `VEC_DotProduct(toTarget, forward) > 0x200` — both are unit
vectors and Q12's 1.0 is 0x1000, so that is a wide ~82° cone, **not** a narrow aim check. Verified
on `func_ov206_020cde58` (2026-07-17). They are real decomps, not template fan-out — but they are
twinned, so one analysis pays several times.

★ **11 of the 19 call the RNG in the `add r0,r0,#0` / `adds r0,r0,#0` shape. That is NOT a blocker**
— it is cracked with `f(n) + (v - v)` (deferred-ties.md). An earlier revision of this file declared
them blocked; that was wrong, do not trust it if you see it quoted anywhere.

**Done**: ov208/209/268 (676 B, one analysis → three matches; ov208 is the worked rep — read it
first, the rest are the same shape).

**Open**: ov125/126 (756 B), ov200/201 (736 B), ov271_020d1048 (788 B), ov207/274/275 (576 B, the
rest of ov206's quad), ov210/211/282 (568 and 784 B), ov235. All need the `+ (v - v)` crack.

`ov206_020cde58` sits in `ov206/nonmatching/` at **576/576 bytes, 144/144 instructions** — the only
delta is one destination register in the radii sum (`add r1,r6,r2` vs `add r2,r6,r2`), an allocator
choice that resisted ~10 steering attempts. Its C is otherwise correct and is the template for
ov207/274/275; if anyone cracks that one register, four functions land at once.

**Re-run the tool for the function in front of you; never write from recollection or a summary.**
Twice now the tool was right and I was not: on ov236 it flagged case 8's body as oversized and I
wrote a comment explaining the warning away (it was restoring bit 0 of +0x1ae — exactly the 12
bytes I was short), and on ov255 I wrote the C from an abbreviated recollection of its output that
had dropped `case 3`, costing two iterations to rediscover a case the tool had printed. Its
outlier warnings mean **disassemble that body**, not "probably fine".

The trailing case has **no `b` to the tail** (it falls into the epilogue), so a body-size check
cannot see its end — that last case is the easiest one to lose.

### c634 structural families matched this vein (hand-template these)

- **latch-then-switch dispatch**: copy queued sub-state `+0x1c7 → +0x1c6`, `switch
  (*(s8)(obj+0x1c6)) { case 0/1/2: c634(self, 1, &cbK); }`, then reset `+0x1c7 = -1`.
  Variants: `-1` guard `return`s (reset after switch skipped) vs `beq tail` (reset
  runs even for -1); optional step before switch (`&=~0x10`, hw60 `&=~2`, release a
  partner, clear a linked `+0x4e0`).
- **hw60-reset multi-dispatch**: `*(u8)(obj+0x1c6)=V; *(s8)(obj+0x1c7)=-1; hw60->hi
  &= ~1; *(u16)(obj+0x1ae) &= ~1;` then 2-3 `c634(self, 0/1/2, &cb)` in a row. Optional
  lead step `*(owner+8|+0x18) = *(owner)+0xb0` or `= *(*(obj+0x390)+0x42c)+0x14`.
- **poll-branch-tick** (ov228/229/233): `if(CALL1(self)<0){c634(...,0);} else { if(*(owner
  +8))…; if(!busy){anim(obj,0x11,0); (*(u8)(owner+0x61))++;} if(*(u8)(owner+0x61)<3)
  return; c634(...,&cb);}`. `<0` guard forces bge-to-else; `<3` is unsigned (poplo).
  Variants: inner block sets `+0x61=0xff`, or calls a retire func, or a bigger finish.
- **accum-threshold-effect** (ov223/224/225/226/227, ~184B): `if(CALL1(self,0)<0){c634
  (...,0); return;} *(owner+0x5c) += frameDelta; if((*(u8)(owner+0x75)&2)==0 &&
  *(owner+0x5c)>=0x1650){ c5af8(obj,LIT,MODE,*(owner+8)); *(u8)(owner+0x75)|=2; }
  busyguard; latch 4; c634(...,0);`. Per-member: CALL1, LIT (pool@size-4), MODE.
- **partner-effect predicated** (~4 members, 116-132B): `int t=*(*(owner)+0x5ac);
  if(t){ int v=*(t+0x18c); *(owner+0xc)=v; if(v){ f(v,1); c5af8(obj,LIT,K,*(owner+8));
  CALL2(owner,1);}}` → mwcc emits `ldrne/strne/cmpne` predication cleanly.
- **signed-nibble state machine** (ov200/201/271, 192B): see codegen-cracks.md
  `struct nibs`; guard on `*(u8)(*(owner)+0x1c4)&0xa`, copy hi→lo, `switch(->lo)`
  dispatch, `->hi = -1` tail.
- **atomic-hpair sprite request**: `struct hpair{u16 a,b;} buf = *(struct hpair*)(&data
  [+OFF]); buf.a = *(u16)(*(owner)+2); func_02031384(4, &buf, 4);`. (TIE when an anim
  precedes it — halfword read order; see deferred-ties.md.)
- **stack-out-buffer resolve** (ov236/278): `int buf[3]; func_0202f384(buf, *(owner)+
  0xa0, &data_02042258); r=func_020050b4(buf[0],buf[2]);` writes r to two fields.
  Often combined with anim + `*30/20` div + `*(obj+0x3d4)&=~1`.

Individual c634 handlers (non-family) decode ~85% on the filtered set (skip
`blx`, `ldm`-arg-coalescing, hw60 `|=`, index-`lsl#2` loops, and the deferred ties).

## Other high-yield veins

- **c5c0 child-spawner** (~60 undone): `int *entry; func_0203c5c0(*(int*)(self+0x3c),
  A, B, cb1, cb2_or_0, &entry); *entry=self; entry[k]=…; *(int**)(self+0x214)=entry;`.
  The PURE 72B form (only `*entry=self`) is a r0/r1 entry-reload TIE; the 84B+ forms
  with a 2nd entry use match.
- **d15c object-constructors** (~60 carved): alloc+link+callback+init template
  `func_0203d15c(...)`. The auto-decoder lived in a session scratchpad and is GONE;
  re-derive it from a matched member if you need it again.
- **020c2f7c factory-registrar** (72 members, 24B, ARM tail-call): every member =
  `int f(void){ return func_ov107_020c2f7c(TYPE, (void*)&CTOR); }` where CTOR =
  this+0x18. Spans ov119..ov282.
- **Global accessors** (1-data-reloc small getters/setters, ~40 carved): pool word =
  `&symbol`; `extern int data_X;`. Double `ldr [r0]` = value is a pointer; single =
  base is `&data`. See codegen-cracks bitfield/guard entries.
- **Tiny cross-overlay veneers** (<20B): `return TARGET(args)` — ~100% match. ★★★ **PROVEN BIG
  2026-07-17: one 20-byte analysis covered 87 byte-identical functions (+77).** The shape:
  ```
  ldr ip,[pc,#4] ; ldr r0,[pc,#4] ; bx ip      ==      void f(void) { TARGET(&DATA); }
  ```
  a **void tail call** to a far/interworking target; the two pool words are the only difference
  between family members. Matched first try; all 87 verified.
  **Census for more**: same masked hex · size ≤ 20 · exactly 2 relocs. This vein is barely touched.
  ⚠ **`dedupprop` will NOT fan these out** — it skips any symbol not named `func_*` (its line 61),
  so it saw 2 candidates where there were 87. Generate the family yourself from the index: for each
  twin, `relocs[0][1]` is the target and `relocs[1][1]` is the data.
  ⚠ **They live in `libs/`, not `src/`** — put each `.c` next to its own `asm_stubs/` twin
  (`libs/nitro/snd/calls/…`), and delete that stub. See the `libs/` note in `state.md`.
  ⚠ **Their SDK names are junk.** 87 different veneers are all called `SNDi_UnlockMutex_0xADDR`
  while tail-calling different targets (one goes to `srand_0x0208875c`). The SDK identifier matched
  a *shape*, not a function. Say so in the file; do not propagate the name into Ghidra as truth.
- **THUMB base-object families** (ov000/002/005/006/009/025/026, verify `--thumb`):
  teardown (40B ×6), list-walk (52B ×5, `NNS_FndGetNextListObject`), bit-test-notify
  (44B ×5, `func_02032428`). THUMB tail-call thunks: 8B `ldr r3,[pc]; bx r3` =
  `int f(void){ return TARGET(); }`.
  - **element-release sweeps** (×7 each, DONE 2026-07-15): `SweepReleasePendingElements`
    (50B: items base@+0x10, count@+0x34, stride 0x30; free elems with +0x24 bit1 set)
    + `SweepFreeElementBuffers` (42B: base@+0x14, count@+0x38, stride 0x10; free elems
    with nonzero +0xc). Per-overlay local callee frees a heap alloc (`NNSi_FndFreeFromDefaultHeap`).
    Needed the struct-pointer/reload-per-iter crack (codegen-cracks Loops). More
    same-shape sweeps likely remain across these 7 overlays — masked-hex dedup them.
- **RemapCharCode00..17** jump-table value-switches (72 funcs ov005/008/025/026):
  `switch(code){case base..base+n: return k;} return code;` — emit cases in ROM body
  order, default `return code` (a constant default won't match).

## Masked-hex dedup (free twins)

Bucket undone funcs by `masked_hex` (zero the 4 bytes at each reloc offset). Match
one rep, then `dedupprop.py` copies its `.c` to every byte-identical twin
substituting per-overlay reloc symbols (in reloc-offset order). Run after each
batch. Twins that DIFIERE are the reg-alloc-tie class (the rep matched ITS overlay
by luck; the twin needs different regs).

## Semantic hubs & subsystems (for naming / understanding)

Entity/list manager at **0204c208** (MAIN); veneer arg-forward crack. **020c2f7c**
factory-registrar; **0203c634** slot-dispatch; **0203c5c0** child-spawn; **0203d15c**
constructor. ov028 = encrypted anti-tamper self-modifying blocks (do NOT reclassify
as .text). See memory `project_khdays_entity_manager_0204c208`, `semantic_hubs`.

## Combat-overlay c634 handler clusters (2026-07-15 — HUGE vein, many still open)
The enemy/attack overlays share BYTE-IDENTICAL c634 dispatch handlers across whole
overlay ranges. Masked-hex dedup finds 5-8-member families constantly. Matched this
session (all via `scan_fam` + per-twin reloc substitution + `dedupprop`-style fan-out):
- **ov004/005/008/009/025/026**: WalkRecordsAppendMatching, FindBestRecordAppend,
  BuildRecordNode, BuildTagTrackerNode, InitSubsystemObject (THUMB).
- **ov206-275**: TestEntitiesAgainstRect (stack-heavy hit-test, model locals as ONE
  struct to pin the frame).
- **ov137/138/158/159/160/246/247**: AimAtTargetAndDispatch (hw60 |=K + x*30/10 magic).
- **ov228/229/230/233/248/249**: PushLocalOffsetToOwner, PushOffsetTwiceAndReset,
  GuardedPushOffset, PushConstThenOffset, SetChargeFlagsAndDispatch — a whole push/charge
  state machine; func_ov107_020c0b90 takes a vec BY VALUE; func_ov107_020c9264 = 3 args.
- **ov221-227**: GuardedAimOrHandoff, ChargeTimerThenFire.
- **ov185/186/187**: AcquireAimTransform (some overlays have 2 members).
- **ov008/025**: FindMinListValue.
NEXT: keep scanning `size 24..320, members>=5, all-undone`; the ov221/228/137/206 clusters
still have 316-436B members open (func_ov137_020cd2d8 trig, func_ov206_020ccef4 hit-test,
func_ov221_020d34cc). Shared callees: func_0203c634 (dispatch tail), func_ov107_020cab14
(aim query, 2 args), func_ov107_020c0b90/020c9264/020c5af8/020c5c54, VEC_* / func_020050b4
(atan2). Route hw60 `->hi |= K` STANDALONE to the explicit form (see codegen-cracks);
data_02041dc8 block-copy-into-obj is a scheduling tie (nonmatching) but by-VALUE is fine.


---

## ApplyModeChange -- the actor mode-change entry point (~8 reps x 4 = ~32 funcs)

**DONE 2026-07-17: 9 reps, 33 functions matched.** The vein is CLOSED except one:
`func_ov039_020b3570` (792 B, x4) is parked in nonmatching/ at 792/792 with the instruction shape
already exact -- a 4-register rotation, next lever written into the file.
Note `func_ov030_020b3990` (836 B) has NO twins despite the family pattern -- dedupprop finds
none, and the two other 836 B functions in the ROM (ov043_020b3e24, ov062_020b6624) are unrelated
functions that merely share a size. Do not assume x4 without checking.

Every enemy overlay has one. Find them with:
`grep -rl "020521a4\|02052024" src/overlays/*/asm_stubs/calls/*.c`.
Reps live at `020b3xxx`; each has three byte-identical twins in the `020b5xxx` / `020b8xxx` /
`020bAxxx` bands (dedupprop fans them out for free).

**The template** (all seven matched off it):

```c
void func_ovNNN_ADDR(int self, int mode) {          /* TWO args -- there is no p3/p4 */
    int reached = -1;                                /* only if some arm rewrites the mode */
    switch (mode /* or mode - 0x2e / - 0x2f */) { ... each arm no-ops if +0x6bc == mode ... }
    func_ov022_020a384c(self, mode);                 /* hand the mode down */
    flag = 0;
    if (*(signed char *)(self + 0x2bb2) == 2) { flag = 1; }   /* ALWAYS before the branch */
    if (mode >= 0x2e) {                              /* the >= arm is ALWAYS written FIRST */
        ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
        func_ov002_02052024((void *)(self + UI), base + ST, mode, 2, ret);   /* 5 args */
        return;
    }
    func_ov002_020521a4((void *)(self + UI), base + ST, mode, flag);         /* 4 args */
    if (reached >= 0) { *(int *)(self + 0x6bc) = reached; }
}
```

Load-bearing rules, in the order they cost time:
1. **`020521a4` takes FOUR args, `02052024` takes FIVE.** See codegen-cracks.md -- this one bad
   assumption blocked the whole family for a day.
2. **The `>= 0x2e` arm is written first** in every member (ROM emits `blt`). Ditto any other
   two-arm tail (`if (kind != -1)` first in ov049).
3. **The loop flag is computed BEFORE the branch**, never inside the arm that uses it.
4. **Small conditional values are zero-init + one conditional set** (`flag = 0; if (x == 2)
   flag = 1;`), NOT a comparison -- except where the ROM shows the full `moveq/movne` pair, which
   IS the comparison form (`*(int *)(p + 0x118) = (mode == 0x30);` in ov049). Read which.
5. **Run `switchorder.py` first** -- the case source order is not 0,1,2,... (ov035 is 0, 1, 4, 2+3).
6. Guards are spelled `mode != *(int *)(self + 0x6bc)` in some members and the other way round in
   others. Two reversed compares and nothing else in a diff = read the operand order off the ROM.
7. A second `int p2 = self + 0x2ce4;` declared INSIDE a block is real (ov034): it makes mwcc
   rebuild the address rather than reuse the switch's copy, and re-issue the compare.
8. ov049 only: `i` must be declared BEFORE `loop`/`ret` (r4/r5/r6 = i/loop/ret), and `loop = 2`
   inside its 2-iteration loop is LIVE -- mwcc cannot prove the branch invariant, so the 2 gets
   hoisted out as `mov fp, #2` and feeds the next iteration's 020521a4 call.

## ov008/009/025 screen-state vein (data_02090f04 context) — CTXV volatile (2026-07-18)

HIGH YIELD. The ov008 (and twins ov009/ov025) title/menu screen functions share one global manager:
context = `data_02090f04[1] + 0x9000` (the `[1]` is `*(&data + 4)`). The retail compiler RE-LOADS
`data_02090f04[1]` for essentially EVERY field access (even within a call-free span); mwcc 3.0/139
CSEs it, coming up short by the missing reloads. Fix: read the context through a volatile macro so
every use reloads:
  #define CTXV (*(volatile int *)((char *)data_ov008_02090f04 + 4))
Use `*(T*)(CTXV + 0xNNNN)`. When only SOME accesses are CSE'd (mwcc caches within a span but the ROM
reloads across a call, or reuses a just-stored value), volatilise ONLY those (keep plain `data[1]`
for the shared-within-span reads) -- see func_ov008_0204f930 (3 selective) and func_ov008_02050548
(prologue only). When the ROM reloads everywhere, CTXV throughout (func_ov008_0204f1ac, func_ov008_
0204fbc8). Offsets fold as `+0x9000` (encodable add) + ldr displacement. Matched so far: ScreenTeardown
0204fbc8, WaitLoadAdvancePhase 0204f858, AllocWorkBufferInit 0204f930, CommitPage 02050548,
EnableBothHalves 0204f1ac (all x3). Many more remain in the 0x0204xxxx / 0x0205xxxx range.

## Familia `func_ov107_020c68ec` — destructores de actor (11 miembros, 100% casada 2026-07-19)

Se localiza por SIMBOLOS, no por forma: toda funcion cuyos relocs incluyan
`func_ov107_020c68ec` **y** `func_0203c7e8` y mida 60-260 B. Plantilla:

```c
void func_ovNNN_ADDR(char *self) {
    int i;
    func_0202a440(self + BINDER);           /* 0..N binders, cada uno opcionalmente */
    *(int *)(self + BINDER + 0xc) = 0;      /*   seguido de poner su back-pointer a 0 */
    func_0203c7e8(*(int *)(self + M));      /* modelos */
    func_ov107_020c9eac(*(int *)(self + E));/* handles de efecto */
    for (i = 0; i < N; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(long long) + BASE));
    }
    func_ov107_020c68ec(self);              /* destructor base compartido */
}
```

Tres detalles que deciden el match:
- **`i * sizeof(T)`, nunca `i * 8`.** Con la constante literal mwcc crea una induccion en bytes
  aparte (`add r5,r5,#8`) y sobran 8 bytes; con `sizeof` recalcula `add r0,rS,rI,lsl #3` como el ROM.
  `lsl #2` = `sizeof(int)`, `lsl #3` = `sizeof(long long)`.
- **`ldr r0,[r0, rI, lsl #3]` sin desplazamiento** = la tabla es un puntero:
  `*(int *)(*(char **)(self + OFF) + i * sizeof(long long))`.
- **Bucle de binders con dos punteros que avanzan** (`add r7,r7,#0x24` + `add r8,r8,#0x24`):
  hay que declarar DOS variables puntero y hacerles `+= 0x24` dentro del bucle. Con
  `self + i*0x24 + OFF` sale una sola induccion y faltan 4 bytes (ov259/ov252).

## Veta ov023 -- manejadores de comando del VM de script (~37, THUMB)

Se localiza con `python tools/callvein.py func_02020d10` (37 sin hacer, 0 casadas al abrirla).
Todos son `int cmd(int ctx, int args)` en THUMB, 46-200 B. Vocabulario fijo:

| llamada | significado |
|---|---|
| `func_02021980(ctx, (void *)(args + 8*k))` | lee el operando k como ENTERO |
| `func_02021994(ctx, (void *)(args + 8*k))` | lee el operando k como otra cosa (float/handle) |
| `func_02020d10(ctx, x)` | resuelve un handle de entidad -> id |
| `func_020219b4(ctx, args)` | paso por defecto cuando el comando cede el turno |
| `*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64` | **la tabla de entidades** (`sizeof(Entity) == 0x1a64`) |
| `func_0202bfcc((unsigned short)id)` | el nodo grafico de esa entidad |

`return 1` = comando terminado, `return 0` = vuelve a entrar el proximo frame.

★ **`(unsigned short)` como TIPO de la variable, no como cast de la expresion.**
`func_ov023_02084bac` sale 2 bytes largo con
`f(..., (unsigned short)func_02020400(...))` -- mwcc copia r0 a r2 y luego desplaza r2.
Con `unsigned short frame = func_02020400(...); f(..., frame);` desplaza r0 en su sitio como el ROM.
Probado tambien con `(int)` intermedio y doble cast: solo funciona la variable tipada.

## Veta SDK: las funciones con `OS_DisableInterrupts` (~61 sin hacer, 2026-07-19)

`python tools/callvein.py OS_DisableInterrupts`. Son secciones criticas del NitroSDK -- PXI, FS,
MI, SND, OS threads -- de 40 a 200 B y con la semantica PUBLICA y conocida, asi que casi todas
salen a la primera. 6/6 en la primera tanda (`OS_WakeupThreadDirect`, `SND_CountReservedCommand`,
`IsCommandAvailable`, `PXIi_TryLock`, `FS_FindArchive`, `MIi_DmaSetParams`).

Plantilla:

```c
int enabled = OS_DisableInterrupts();
... seccion critica ...
OS_RestoreInterrupts(enabled);
return x;
```

- `b` hacia adelante nada mas entrar en un bucle = `while` con el test abajo. Escribe el `while`
  normal; mwcc lo rota igual.
- Los registros del hardware van como **puntero volatil calculado una vez**
  (`volatile unsigned int *reg = (volatile unsigned int *)(0x040000b0 + ch * 12); reg[0] = ...`),
  no como casts sueltos -- ver la nota de convencion MMIO.
- ⚠ Estas funciones ya tienen su NOMBRE REAL en symbols.txt, asi que **no dejan deuda de naming**:
  no hace falta pasar por Ghidra a renombrarlas. Es la unica veta del proyecto de la que se puede
  decir eso.

## Script-VM command handlers ("VM emit") -- 19 members, 6 done, generator available

**Locator:** relocs contain `func_ov002_0207643c` AND >=4 of
`{func_02021948, func_02021980, func_02021994}`.

```python
VM={'func_02021948','func_02021980','func_02021994'}
hits=[k for k,v in IDX.items()
      if 'func_ov002_0207643c' in [s for _o,s in v['relocs']]
      and sum(1 for _o,s in v['relocs'] if s in VM)>=4]
```

Skeleton: fetch this command's operands from the descriptor array through the VM's
typed fetchers, assemble a parameter block on the stack, call the overlay's builder with
`(id, &params)`, post the result to `func_ov002_0207643c`, `return 1`.

`python tools/gen_vm_emit.py <func>` writes the C to `build/try/`. **It matches 12 of 19 outright; 14 of 19 are now done.**
The other 13 are bigger (88 vs 158, 104 vs 226 ...) because they carry branches and extra
calls -- the tool does not pretend otherwise, so a large size gap from it means "hand work",
not "tool bug".

Done: `ov002_0207d334`, `ov016_02081360`, `ov016_02080fa4` (= `Ov016_VmCmdCreateEntry`,
builder is `Ov016_CreateEntry`), `ov017_02080cb4`, `ov021_02080e30`, `ov015_020827a0`.
Remaining: `ov014_020807c4`, `ov014_02080664`, `ov015_020822b0`, `ov015_02082574`,
`ov016_020814b0`, `ov016_02081200`, `ov017_02080a6c`, `ov021_02080c98`, `ov002_0207d610`,
`ov002_0207d18c`, `ov002_0207ceac`, `ov002_0207d950`, `ov002_0207d004`.

### The three rules the generator had to learn (all general)

1. **`adds r4, #N` advances the descriptor BASE and it STAYS advanced.** Read as a one-shot
   offset it silently emits `descs` where the ROM means `descs + 8` -- a 2-byte diff that
   looks like anything.
2. **The builder id is truncated AT THE USE, not at the assignment.** `int id` + a
   `(unsigned short)` cast at the call matches; declaring `unsigned short id` reorders two
   instructions on every member that fetches the id early. Same family as the
   shift-splitting crack: **where mwcc applies a conversion follows where you WRITE it.**
3. **Emit the fetches in ROM order.** Some members fetch target/id FIRST and the operands
   after; a fixed operands-then-tail order costs bytes on exactly those.

### Refinements from the first NON-pure member (ov014_020807c4)

- **An operand can be OPTIONAL.** Each descriptor starts with a 16-bit type tag; tag 0 means
  absent, and the handler reads the tag itself and substitutes 0 instead of calling the fetcher.
  It must be a **ternary** -- the ROM shares ONE store between both arms, an if/else emits two.
- **Both `id` spellings are needed, and which one is readable off the ROM.**
  `unsigned short id` truncates at the ASSIGNMENT; `int id` + `(unsigned short)` at the call
  truncates at the USE. When code intervenes between the fetch and the use (a conditional here),
  the ROM truncates at the assignment. When the fetch is adjacent to the use, it truncates there.
  Same underlying rule as the shift-splitting crack: **mwcc applies a conversion where you WRITE
  it.**


### ⚠ The generator's width bug -- and why this class of bug is expensive

For a while gen_vm_emit.py classified every store that was not `strb` as a WORD, because the
store branch only listed `("str", "strb")`. Any parameter block with 16-bit slots got the wrong
widths and every field after them shifted. **Five members were blocked by that one word.**

The reason it cost so much: the tool did not fail. It produced C of the right SHAPE that missed
by 4 to 36 bytes -- which reads exactly like a codegen problem to steer in the source, not like a
bug in the reader. I re-derived and hand-checked several of those diffs before looking at the
tool.

★ **When a generator's output is consistently near-miss across MANY inputs, suspect the
generator, not the compiler.** A real codegen tie is specific to one function; a systematic
offset across a family is a reader bug. Same shape as the accsweep `[pc,#N]` bug earlier the same
day, and the same tell: plausible, consistent, and wrong.


### The generator's TWO structural blind spots (both now named)

1. **Constant-initialised fields are invisible.** It only emits slots written from a fetcher's
   return value. `func_ov002_0207ceac` stores a literal 0 to params+0x11 and came out 4 bytes
   short with every instruction otherwise right. **A SMALL, otherwise-inexplicable gap in a
   generated member is more likely a constant field than a codegen problem.** Position matters:
   that store sits between the last operand and the target/id fetches; moving it to the end costs
   4 bytes the other way.
2. **Optional operands are invisible.** A 16-bit type tag of 0 in the descriptor means "absent",
   and the handler substitutes 0 instead of calling the fetcher -- as a TERNARY, because the ROM
   shares one store between both arms.

`func_ov002_0207d950` (226 B, twelve operands) was hand-written and matched on the FIRST compile
because it is only those two wrinkles stacked plus the assignment-time `id` truncation. That is
the accumulated notes doing their job: nothing new had to be discovered.

**Still open (5):** `ov015_020822b0`, `ov015_02082574`, `ov021_02080c98`, `ov014_020807c4`-style
variants, `ov016`/`ov002` remainder. Two of them do not compile from the generator at all, which
is the honest signal that they carry control flow the skeleton does not model.

### The last member: `func_ov015_02082574` (460 B) -- OPEN, and characterised

**Not a park and not a tie** -- just a big transcription nobody has sat down and done. The shape
is known, which is the expensive part, so whoever picks it up starts from here:

- **Frame 0xC64**, built by SIX `sub sp,#0x1fc` plus a `sub sp,#0x7c` (THUMB cannot encode it in
  one). The header block lives high, reached via a pooled constant `0xc18` added to sp; the entry
  array starts at **sp+0x18**.
- **Two nested loops.** The header has a count byte at +4 and another at +5; the outer count
  gates the whole body (`bgt` at +0x46, else jump to the tail at +0x19e).
- The header stores a POINTER to the current entry back into itself at header+8
  (`str r4,[r0,#8]`), so the block is self-referential -- do not model it as a flat struct.
- **Entries are 7 bytes of `u8` fetched one at a time** (offsets +0 through +6 via seven
  `func_02021980` calls at descs +0x00,+8,+0x10,+0x18,+0x20,+0x28,+0x30, cursor advancing 0x38),
  followed by a **switch on entry[2]** with cases 0/1/2 that each fetch three `func_02021994`
  values into entry+8/+0xc/+0x10, and a default that skips.

So it is the entry-list shape of `Ov021_VmCmdEntryList` with a second level of nesting and a
wider per-entry payload. Expect the same two levers to be needed: the cursor advance pinned with a
temp, and `unsigned` reads where the ROM emits `lsrs`.

## ⚠ Un park BLOQUEA la propagacion a sus gemelas -- rescatar uno puede valer por dos

(2026-07-24.) `dedupprop.py` solo propaga desde un representante MATCHED, y no mira
`nonmatching/`. `func_ov008_02066a4c` estaba aparcada y su gemela byte-identica
`func_ov025_02098e9c` no existia en el arbol: en cuanto la primera salio de `nonmatching/`,
`dedupprop` encontro la segunda sola. **Corre `dedupprop.py` despues de CADA rescate de
`nonmatching/`, no solo despues de una tanda de familia.**
