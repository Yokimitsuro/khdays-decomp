# 2026-08-05 (sound system - func_02032f5c leaves): char* global convention + near-matches

FINDING: the sound global is declared `extern char *data_0204c234;` (a char POINTER), accessed as
`char *base = data_0204c234;` then byte-offset - NOT `int base = *(int*)&data_0204c234`. Confirmed
from the matched func_02032d10 / func_02032af0. Region base = data_0204c234 + 0xb4000 (or +0xb4718
for the channel state). Use this convention for all sound leaves.

func_02032f5c (1132B sound state machine) unresolved callees now all NEAR-MATCH (structurally/
instruction-shape exact, residue = ARM register allocation + occasional codegen fusion), in build/try/:
- func_02032c40 (ring dequeue, SIZE-MATCHED; base lr vs r4)
- func_02032a7c (list unlink, 124 vs 116; base+0xb4000 register reuse in first if)
- func_02032870 (event aging scan, 180 vs 184; INSTRUCTION-SHAPE EXACT; fused (x&0x1f)<<16>>14 +
  register naming)
RECURRING PATTERN across these ARM leaves: mwcc picks different registers than the ROM for the
long-lived base/globals (lr vs r4, r0 vs r1/ip). char* convention did NOT fix the naming. Needs a
systematic lever still unknown. Compiler confirmed = 3.0_patch4 (gate compiler).

Other near-matches (THUMB, from the action VM): func_020218a4 (struct, return-schedule), func_020221a0,
func_02022448. func_020218a4's struct fix proved these are source-shape-solvable.
# 2026-08-05 (action handler table COMPLETE except 2 build ties): +3 matched

Handler table data_020425ec is now fully real C except func_020221a0 and func_02022448 (both
store/branch-layout ties, best forms in build/try/, awaiting exact retail compiler).
Matched + integrated + gate 306/0 + pushed this session:
- func_02021f7c Game_ActionLoadArenaResource (352B)
- func_020221f8 Game_ActionSetBranchTarget (68B, auto/)
- func_020222bc Game_ActionSetupNamedCall (104B) - reads 2 int operands + optional strncpy'd name
- func_0202237c Game_ActionEnqueueCmdIfChanged (96B) - debounced enqueue by id-set, last-id global data_020425e8

NEW FRONTIER (VM core, direct dependency of the handlers): func_020218a4 = ScriptVm_ResolveOperand
(164B) - operand addressing-mode decoder (modes 8/4/0x80-family, GameState field reads into the
0x578 scratch slot). IN-INVESTIGATION in build/try/func_020218a4.c: fully correct except a
~5-instruction store-block schedule residue in the 0x80 branch (mwcc materialises state+0x578 early
and reuses it as the strh base; ROM uses offset addressing + late materialisation). ~18 forms tried.
NOT parked - keep iterating.

Other VM-core deps still BLOB-GAP: func_02032f5c (1132B, called by func_02022448).
# 2026-08-05 (action-command handler table): func_02021f7c MATCHED (Game_ActionLoadArenaResource)

Frontier = MAIN gameplay tick -> action-command handler table data_020425ec (dispatched by
Game_RunActionScript/func_02020e58). Enumerated the table's handler pointers via relocs; earliest
unresolved handlers were func_02021f7c, func_020221a0, func_020221f8, func_020222bc, func_0202237c,
func_02022448 (rest already real C).

MATCHED + integrated (src/calls/, gate DSD_OK=306 FAILED=0, committed):
- func_02021f7c = Game_ActionLoadArenaResource (352B THUMB, 15 relocs). Loads a message container
  ("3:" path) or resource slot ("N:" path) into the arena at state+0x594 via func_0201ed3c,
  records 4-rounded consumed size into the next entry slot. Cracks: func_0201ed3c prototypeless
  (variadic-in-use; "3:" passes 3 args, "N:" 4); cmd is s16 (ldrsh); entry stride 0x48; arena
  offset 0x594 kept in one reg so 0x590 = 0x594-4; operand test written !=0 for branch orientation.
  Ghidra: renamed + prototype (state, cmd); func_0201ed3c left unnamed (shared hub, not decompiled).

IN-INVESTIGATION (build/try/func_020221a0.c, NOT parked): func_020221a0 (62B THUMB, reloc-free) -
callback-slot handler. Down to an 11-byte / 5-instruction residue (scratch reg r1 vs r2 + one
add/ldr order), byte-identical through the mul. ~40 source-shape experiments + 27-build sweep:
INVARIANT and build-sensitive (2.0 builds 11 vs 13, none reach 0). Blocker = exact retail compiler
(3.0/>=139) absent from tools/mwccarm. Awaiting user decision per assigned-function blocker rule.

NEXT frontier after 221a0: func_020221f8 (68B), func_020222bc (104B, 5 relocs), func_0202237c
(96B, 5 relocs), func_02022448 (22B) - the remaining unresolved handlers in data_020425ec.
# PC port play-order frontier

## 2026-08-01 (action system): 4 matched (turn handler + object-init command chain)

Frontier moved up from Game_UpdateObjectMotion to the action-command/object subsystem. Matched and
integrated this fire (all src/calls/, gate pending):
- func_020225f0 Game_ActionTurnHandler (98B THUMB) - turn action-slot handler, cancel-sentinel twin
  of func_020226d4; recursion was actually calls to func_020219b4.
- func_0201eea8 Obj_IsIdFree (176B ARM) - object-id availability check over the registry
  data_0204bc1c (hashed scan via func_02020400 64-bit divide); registry base held in one reg.
- func_020220dc Game_ActionInitObject (108B THUMB) - action command that (re)inits the actor's
  object slot; CRACK: command pointer typed short* to keep it in a callee-saved reg across calls
  (int spills it) - recorded in codegen-cracks.md.
- func_02021ef4 Game_PushObjectSlot (136B THUMB) - appends a 0x48-byte slot entry, resolves a
  'CAKP' archive member (func_020255d4) or inline payload.
Callees named: func_020255d4=Archive_GetMember (already), func_02021948=ByteCode_ResolveOperand.

MATCHED 2026-08-01: func_02025464 = Obj_RelocateSections (200B ARM) - CRACKED with four stacked
levers (struct sections[8] base + `while` guard for bls + pointer-arith add order + branch-tail
empty-slot); full worked example in codegen-cracks.md. RelocState Ghidra struct created. The
Game_ActionInitObject command chain (func_020220dc -> func_02021ef4 / func_02025464 /
func_02021948) is now fully real C. NEXT frontier: other action-command handlers in the dispatch
table data_020425ec, or func_02020ab4 (operand sub-index helper, still unresolved) - verify the
earliest unresolved on the gameplay tick.

--- superseded in-progress note (kept for the crack history) ---
former IN-PROGRESS (build/try/25464.c): func_02025464 (200B ARM) - the object relocator
(fixes up 8 sections of relative offsets to absolute pointers in a loaded 'KAPH' object,
0x4850414b; per-entry ptr relocation + optional func_02025138 dispatch for section 7).
func_02025138 is 1-arg (Ghidra's 4 args phantom); func_02025464 is 2-arg. DOWN TO 3 REAL DIFFS
(byte @0x30) - essentially matched modulo mwcc canonicalization. The winning shape:
- Model param_1 as `struct RelocState { int tag; int relocated; int sections[8]; }` and access
  `state->sections[iVar4]` (NOT `param_1[iVar4+2]`). This makes mwcc emit `add rBase, state,
  iVar4, lsl#2; [rBase, #8]` as ONE callee-saved per-iteration base (r4) - fixing both the outer
  strength-reduction (advancing r6+=4, form was 196) AND the register split (array form put the
  outer base in scratch r2, form was 200). The struct is the mandate anyway.
- Inner loop `((int*)state->sections[iVar4])[uVar5+1]` = one induction var + shift.
- `if (state->sections[iVar4] != -1) {big} else {=0}` (flipped) so the set-zero is the beq tail
  block, matching ROM's branch-not-predicate.
REMAINING 3 DIFFS (all mwcc canonicalization, NOT steerable by source order - swap tested, no
change): (1)(2) the two `(int)state + <loaded>` adds emit `add r0, r1(loaded), r8(state)` where
ROM has `add r0, r8(state), r1` - commutative operand order, struct-member access canonicalizes the
loaded value as Rn where int*-index would give state as Rn (but int*-index reintroduces the split);
(3) the count guard emits `beq` where ROM has `bls` (both == 0 unsigned; ROM merges the guard with
the do-while's unsigned back-edge). NEXT: find the source form giving both the unified struct
addressing AND state-as-Rn add canonicalization; or confirm whether this is a genuine mwcc-build
canonicalization tie. Best form in build/try/25464.c.

## 2026-08-01 (MAIN tick chain): func_02021294 MATCHED (Obj_PrepAltTransform)

216B THUMB, DONE and integrated (src/calls/). Game_UpdateObjectMotion state-1 pre-commit: builds a
base position (anchor entry func_0202bfcc+VEC_Add, or own obj+0x94 when obj[0xfc]==0x40), stores it
(func_0202e5d8 -> Transform_SetBasePos), dispatches (func_0202e4f4 = DispatchWithReentrantScratch),
and conditionally rotates obj+0x6c about obj+0x60 via func_0202119c=MTX_MakeRotXY43.
Cracks: VecFx32 struct copy (ldm/stm); anchor test `if (obj[0xfc] != 0x40){anchor} else {own}`;
**func_0202e4f4 is 2-arg here** - Ghidra invented param_3/param_4 from leftover r2/r3 that are the
block-copy's advanced pointers (its body ignores param_3 and dead-stores param_4); the first spin
angle negated EAGERLY into a local before VEC_Subtract (held while the 2nd negates inline at the
call). Both DAT literals are pool (0x6a4000 -> obj+0x5c, 0x19a -> obj+0x58).

Two matches committed this fire (func_02021418 last fire's carry + func_02021294), pending push
after 06:02 + fresh gate. Game_UpdateObjectMotion (func_020217d4) callees now ALL real C
(func_02021294, func_02021418, func_02023cc0, func_0202e53c, func_02021294, plus the SDK VEC/MI).
NEXT frontier: back up the tick to Game_RunActionScript's other spokes / the ov002 gameplay
constructor cluster - verify which handler is the earliest unresolved.

## 2026-08-01 (MAIN tick chain): func_02021418 MATCHED (Obj_StepMotionTransform)

954B THUMB, DONE and integrated (src/calls/). The r0<->r1 register tie in the sin/cos tail (see the
prior note, now resolved) was SOLVED: the table index must be a local i2 ASSIGNED AFTER the
obj[0xc] store, accessed byte-offset - `int i2; obj[0xc]=local_78; i2=(angle>>4)*2;
obj[1]=*(short*)((char*)data_0203d210 + i2*2); obj[2]=*(short*)(...+ (i2+1)*2);`. The deferred
assignment keeps i2 a shared CSE (so both offsets derive from one (angle>>4)*2, matching ROM) while
scheduling the shift AFTER the literal pool, which is what pins base->r1 / values->r0. Hoisting i2
to the block head computed it before the pool; folding to (angle>>4)*4 broke the CSE; the FxSinCos
struct form loaded base twice. Crack recorded in codegen-cracks.md.
Callees named: Anim_GetBlendFactor (0202136c), Anim_InterpEased (02021208), MTX_MakeRotXY43
(0202119c); ArrayEntryPtrD0_c208 (0202bfcc) and ScaleAroundPivot (02021404) already named.
data_0203d210 is the global {s16 sin, s16 cos} angle table shared by 1028 funcs (short[], entry
stride 4). AnimObject Ghidra struct created (decoded SRT fields).

NEXT frontier (MAIN gameplay tick): Game_UpdateObjectMotion's remaining callees - func_02021294
(state 1 pre-commit) and func_0202e53c (delta-transform builder in the default case). Verify their
status; then continue the tick body from Game_RunActionScript's other spokes.

## 2026-08-01 (MAIN tick chain): func_02023cc0 MATCHED (Camera_CommitMatrices)

MAIN gameplay-frame spine, NOT the ov002 constructor lane below. Chain:
Game_RunActionScript (func_02020e58) -> Game_UpdateObjectMotion (func_020217d4, matched last fire)
-> func_02023cc0 (state-0 "commit base transform block"). func_02023cc0 = Camera_CommitMatrices:
builds the projection matrix (func_02004d60 = Camera_BuildProjectionMtx) + look-at view matrix
(func_01ff9c04 = MTX_LookAt, confirmed by decompile: from-target forward, cross w/ up, -dot
translation) and caches eye/up/target into the global camera state data_02047394/475ac/b8/c4.

CRACK (the ~40-experiment residue from prior fires, now solved): the 176B ARM body was a whole-block
list-scheduler tie - the two look-at address computes (add +0x2c/+0x14) and the view-matrix pool
load kept reordering by ~7 instructions vs ROM. NOT fixable from the copy block itself (every
in-body lever gave the same schedule). The lever was the FRONT call: func_02004d60 must take the
four projection words as SEPARATE SCALAR ARGS, not a 16-byte struct-by-value. mwcc schedules the
whole basic block, so the struct-by-value ldm-into-r0-r3 perturbed the downstream copy block.
Lesson: when an in-body copy/scheduler residue will not move, vary the ARG STRUCTURE of the
PRECEDING call - the block scheduler is global. Recorded in codegen-cracks.md.

TOOLING: verify_idx.py now adds RELA r_addend for data relocs, so struct-field globals
(data_X.fieldN -> data_X+off) verify against the ROM's standalone symbol at that address. This
unblocks the mandatory struct-first form for any function writing global struct fields.

NEXT (this chain): func_02021418 (954B THUMB, 32 relocs) - the motion-step in Game_UpdateObjectMotion
default case; blob-gap, no file yet (carve). Then the remaining Game_UpdateObjectMotion callees
already matched (func_0202e53c, MI_CpuCopy8, VEC_Add, func_02021294).

## 2026-08-01 (fire 5): func_ov002_020692a8 IN-PROGRESS (build/try/692a8.c, NOT parked) - no new match

Worked the ov002 gameplay-updater dep func_ov002_020692a8 (292B THUMB). Closest candidate = 280
vs 292 (12 short). RESOLVED sub-problems: the 64-bit divide (Ov002_GetTimeoutTicks()<<6)/0x82ea is
signed long long -> _ll_sdiv; the state==0||3 guard needs the bVar4 bool materialisation (not
direct beq/return); the entry head fields are u16 (ldrh). REMAINING RESIDUE (the whole 12 bytes):
the entry read-cursor and write-cursor are the SAME address (data_0204c678 + i*0x104) and ROM keeps
BOTH in registers (r7 read, r5 write, buf r6, i r4, fp spilled to sp[0], sub sp #0x1c); mwcc CSEs
them into ONE spilled pointer and spills a cursor instead of fp (sub #0x20 + push r3). Two-
induction-pointer-same-address / register-spill artifact (mla/CSE family, same class as the c010/
bd50/02069454-solved items). ~14 experiments tried (int/u16/short + signedness, one vs two vs
struct-array cursors, declaration order, wr=rd init, register hints) - none flip the spill; two
explicit pointers (280) beats one (264) and struct-array (264). NEXT: force mwcc to keep two entry
cursors in registers and spill fp/flags instead (69454 was cracked with char*+volatile - a related
lever worth trying on the cursors here).

ov002 delinks unchanged 856/622; C=16002. Sibling deps done: 020693e0, 02069454, 0206fb84, and the
whole dispatcher handler chain. Constructor func_ov002_020679d4 (968B) still the top of the cluster.

## 2026-08-01 (fire 4 cont.): 02069454 CRACKED + 02068e68 teardown matched (4 total this fire)

func_ov002_02069454 (Ov002_TickSessionRequest, 236B THUMB) is DONE - the mla/CSE counter residue
was solved with `char *base` (forces [base,off] addressing) + `volatile` on the heap+0x8da0 retry
counter (forces re-load and address re-derivation each access, matching ROM). Committed.

func_ov002_02068e68 (Ov002_TeardownGameplayScene, 276B THUMB) matched: gameplay-scene teardown
handler returned by Ov002_TickGameplayState. It is void(void) - Ghidra's param_1..4 were all
PHANTOM (leftover regs); func_02020cf8 takes -1 (mvn, not 0xff) and returns a u64 fed straight
into func_0202ded8 with NO arg setup (so func_0202ded8 is effectively 2-arg here), func_ov002_0206bbb8
is 3-arg (Ghidra's 4th dropped), and the final -1 test uses an else-first branch. Committed.

This fire (all deps of func_ov002_020679d4): 020693e0, 0206fb84, 02069454, 02068e68. ov002 delinks
856 matched / 622 gap. Cracks recorded in codegen-cracks.md: switch source-order-from-jump-table,
char*+volatile for multi-access counter CSE, and the phantom-param / -1-via-mvn / u64-return-no-setup
teardown patterns.

NEXT frontier: the constructor func_ov002_020679d4 itself (968B) and its remaining direct deps
func_ov002_020692a8 (292B). Handler chain (02068d54/dc4/e34/e68/fc4/058, 693e0, 69454) now real C.

## 2026-08-01 (fire 4): two more gameplay-session deps matched; 02069454 blocked on mla/CSE

Matched + integrated (committed, NOT yet pushed - <1h since last push):
  - func_ov002_020693e0  Ov002_PollSessionReady    (116B THUMB) -- session readiness gate for TryAdvancePhase
  - func_ov002_0206fb84  Ov002_BuildSessionCommand (524B ARM)   -- 27-case kind->len switch (source-order crack)
ov002 delinks 854 matched / 624 gap. 02068e34 was already done (peer/earlier).

IN-PROGRESS (build/try/69454.c, NOT parked): func_ov002_02069454 (236B THUMB, session per-frame
updater, sibling of PollSessionReady). ALL fields/branches match; RESIDUE is the counter block at
heap+0x8da0: ROM keeps 0x8da2 (handle offset) in r1 and derives 0x8da0 via `subs #2` on EACH access
([r4,offset] addressing, confirmed ldrh unsigned via disasm); mwcc CSEs base+0x8da0 into a full
pointer, dropping ~3 recompute instrs (224 vs 236). mla/CSE-class address-caching residue - same
family as the c010/bd50 mla open items. ~12 experiments (u8/u16/short counter, explicit re-read,
+=, cached temp, volatile=228). NOT yet cracked; needs a way to force [r4,offset] re-derivation.

Remaining ov002 gameplay-constructor cluster gaps: func_ov002_020679d4 (968B constructor),
func_ov002_02068e68 (276B), func_ov002_020692a8 (292B). Shared helper Ov002_BuildSessionCommand
now resolved unblocks reading several session functions.

## 2026-07-31 (fire 3, 6 matches total): dispatcher handlers landed

Ov002_TickGameplayState + two of its returned handlers are now real C:
  - func_ov002_02068d54  Ov002_RunPendingCallbacks (112B THUMB) -- flush 2 ctx callbacks -> 02068dc4
  - func_ov002_02068dc4  Ov002_TryAdvancePhase     (112B THUMB) -- readiness gates -> 02068e34
Both cracked with the "latch the return handler in a var before the last call so it survives in a
callee-saved reg" pattern; 02068dc4 needed the result declared BEFORE the base to land it in r4
(same r4/r5 lever as 0206a230). blk computed before a busy-flag guard fills the load-delay slot.

ov002 delinks now 852 matched / 626 gap. NEXT frontier: func_ov002_02068e34 (next handler in the
chain, returned by TryAdvancePhase), then func_ov002_02068fc4's peers, then the constructor
func_ov002_020679d4 itself. Also still open: func_ov002_02069540 helper family and the remaining
Tick* handlers (02068058 done).

Fire summary (6 byte-exact, all deps of func_ov002_020679d4): 6e640, 67d9c, 67f78, 69b70, 68d54,
68dc4. Cracks recorded in codegen-cracks.md: struct-array strength reduction, dropped-arg in r0,
switch fall-through/shared-r6 epilogue, int-vs-u8 accumulator, for-init comma order, latch-return-
before-call, and the char*/decl-order r4/r5 levers.

## 2026-07-31 (fire 3, 4th match): func_ov002_02069b70 (Ov002_RefreshSlotOccupancy, 148B THUMB)

Refreshes per-slot occupancy GameState flags (0x2001..0x2004) + cached count via
Slot4_GetIfOccupied and the CARD rom accessor. Byte-exact, committed e5c2ddc4e. Two more
cracks (codegen-cracks.md): int (not u8) for a loop accumulator stored to a byte only at the
end; and for-init comma order (index first) to control which of two 0-inited loop vars gets
the movs vs the copy. ov002 delinks now 850 matched / 628 gap.

The ov002 gameplay-constructor (func_ov002_020679d4) direct-dependency cluster is now almost
fully real C. NEXT frontier = the handlers Ov002_TickGameplayState returns
(func_ov002_02068d54 / 02068fc4 / 02068dc4 / 02068058) and its helpers (func_ov002_02069540,
func_ov002_0206ba28), then the constructor func_ov002_020679d4 itself.

## 2026-07-31 (fire 3 cont.): three more gameplay-frontier deps matched (hard residues cracked)

All direct deps of the ov002 gameplay constructor func_ov002_020679d4, byte-exact + integrated:
  - func_ov002_0206e640  Ov002_SelectTableEntry     (144B THUMB) -- struct-array strength reduction
  - func_ov002_02067d9c  Ov002_UpdatePendingRequest (152B THUMB) -- dropped arg to func_02031440(slot)
  - func_ov002_02067f78  Ov002_TickGameplayState    (224B THUMB) -- switch fall-through + shared r6 epilogue

CRACKS THIS FIRE (all in codegen-cracks.md): (1) struct-array form fixes walk-vs-multiply /
preheader placement; (2) a value kept in r0 across a call is usually a DROPPED ARGUMENT, not a
register tie -- func_02031440 takes the slot; (3) a 3+-way state dispatch that shares one
return-in-r6 epilogue is a `switch` with fall-through, NOT nested if/else-if (nested ifs give each
arm its own pop). Also: NNSi_FndGetCurrentRootHeap() returns the SAME base as *data_ov002_0207fa00
(the root heap IS the ov002 root context); SetGameMode + command args are unsigned char.

Ov002_TickGameplayState is the main per-frame gameplay dispatcher: it returns the next handler
(func_ov002_02068d54 / 02068fc4 / 02068dc4 / 02068058) or NULL. Those four handlers + func_02020e58,
func_ov002_02069540, func_ov002_0206ba28 are the next frontier. Remaining constructor-cluster gaps:
func_ov002_02069b70 (148B). ov002 delinks now 849 matched / 629 gap.

## 2026-07-31 (fire 3): func_ov002_0206e640 RESOLVED (was the in-progress residue)

func_ov002_0206e640 -> Ov002_SelectTableEntry (144B THUMB) is now byte-exact, integrated,
committed (a5f89abe5). The preheader-placement / walk-vs-multiply residue was solved by the
STRUCT-ARRAY form (see codegen-cracks.md "RESOLVED"): model the walked table as
struct{u32 count; Entry entries[];} with sizeof(Entry)==stride(0x3c) and index it as an array;
mwcc then strength-reduces to the exact two-pointer walk with inits in the post-guard preheader,
no multiply. Created the Ghidra type Ov002SelectEntry (0x3c) in the same batch. Final diff was a
single else-inline flip on the payload byte-select. ov002 delinks now 847 matched / 631 gap.

LIKELY REUSE: the same struct-array fix probably closes the other mla-vs-walk parks (ov008 c010,
bd50). Try it there next time those are on the frontier.

## 2026-07-31 (later fire): OV002 GAMEPLAY BOOTSTRAP -- 6 clean deps of func_ov002_020679d4 matched

Pivoted to the ov002 gameplay milestone (Scene 2) after the ov008 menu range proved residue-dense.
The gameplay-frontier func_ov002_020679d4 has a cluster of context/record-init callees, all CLEAN
transcriptions. Matched + integrated + pushed this fire (origin/main @ 8a1687b51):
  - func_ov002_0206e718  Ov002_SetLazyClassEnabled       (88B ARM)   -- bic-#1 flag toggle
  - func_ov002_020697e8  Ov002_InitContextRecord         (92B THUMB) -- resets ctx+0x8bcc block
  - func_ov002_0206a230  Ov002_InitHandleRecord          (76B THUMB) -- resets ctx+0x8d14 (char* base crack)
  - func_ov002_0206b910  Ov002_StreamFormattedLine       (108B ARM)  -- descriptor pack + stream
  - func_ov002_02069240  Ov002_InitPlayRecord            (104B THUMB)-- ctx+0x8ba8 + GameState fields
  - func_ov002_02069c24  Ov002_InitStateRecord           (128B THUMB)-- ctx+0x8c94, chains 02069c04
  - func_ov002_02069c04  Ov002_SetStateRecordStage       (32B THUMB) -- promoted auto/->calls/ (named)
Gate iter89: 306 OK / 0 FAILED. ov002 delinks now 846 matched / 632 gap.

RECORD-INIT SIBLING MAP (sub-blocks of the ov002 root context @ *data_ov002_0207fa00):
  +0x8ba8 InitPlayRecord | +0x8bcc InitContextRecord | +0x8c94 InitStateRecord | +0x8d14 InitHandleRecord
  +0x8d84 = record touched by func_ov002_0206e640 (search-and-fill).

TWO NEW CRACKS this fire (see codegen-cracks.md): (1) type the context base as `char *` (not int)
to fix the r4/r5 callee-saved swap when ctx + a derived pointer both stay live; (2) use SIGNED
short/int lvalues for -1 stores so mwcc reuses ONE 0xffffffff register across strh/str/strb widths.

IN-PROGRESS (build/try/6e640.c, NOT parked): func_ov002_0206e640 (144B THUMB search loop) -- byte-
identical from the loop guard onward; only the two induction-pointer inits sit before the guard
instead of in the post-guard preheader. mwcc preheader-placement / strength-reduction residue (same
family as mla-vs-walk). Full lever notes in codegen-cracks.md. NEXT: retry 6e640 with a fresh
strength-reduction idea, or continue clean deps of func_ov002_020679d4.

## 2026-07-31: MENU CLEAN FUNCTIONS EXHAUSTED -- remaining ov008 gaps are residue/complexity-dense

Investigated three ov008 menu gaps this fire, ALL turned out residue-heavy (no match):
  - func_ov008_0205bd50 (SRT transform loader from a resource dict, 336B, dep of c010): SIZE-EXACT,
    a single register coin-flip -- piVar2 lands in r1 (ROM, `mla r1,r0,r2,r1` accumulates into the
    base reg) vs r0 (mine). Tried ~6 forms (multiply order, `p += stride*index`, base-first
    accumulate, in-place). No matched-corpus SRT loader exists as real C (all MTX_Identity33_ users
    are asm_stubs), and the 5 in-place-mla matched funcs use it for a different (Q-format multiply)
    computation. HELD build/try/bd50.c -- the closest, a778-class 1-register residue.
  - func_ov008_0205b988 (page/threshold scorer, 148B): ALREADY a prior-session residue
    (build/try/b988.c, size-exact, base-CSE/scheduling register cascade).
  - func_ov008_020570c0 (cursor-match bool, 140B): +40 bytes -- the b bit-test must NOT be
    materialised; the ROM chains the `lsrs` flags through `ldrbeq`/`cmpeq`/`addeq` (b flags survive
    the i++), and `1 << i` uses a cached `1` in r4. Needs the flag-chaining rewrite; HELD
    build/try/570c0.c.

STRATEGIC READ: the ov008 main-menu cluster's CLEAN transcriptions are all matched (a138, a1fc,
a684, b19c, a8e0, b230, ab5c, af54); what remains in the menu address range is dense with register/
scheduling coin-flip residues (a3dc, c010, a778, bd50, b988) -- grinding them one-per-fire yields no
matches (this fire, the a778 fire, the c010 fire). NEXT FIRE OPTIONS: (1) pivot to the next play-
order MILESTONE -- ov002 gameplay bootstrap (func_ov002_020679d4 area) -- and find CLEAN functions
there, per the a3dc precedent of not grinding residues; or (2) crack bd50's single-register mla
coin-flip with a fresh idea (it is the closest). Do NOT keep opening menu-range gaps blindly -- they
are residue-dense. The residues are all size-exact and preserved in build/try/, ready to integrate
the instant their register/scheduling coin-flip is cracked.


## 2026-07-31: MAIN-MENU STATE MACHINE COMPLETE (except 2 preserved residues)

Ov008_MainMenu_StateTick (b230) and ALL its state deps are now real C: state 0
(GetCtxObject95c0, a8e0, a84c, a8c4, b19c, InitObjectWithList, c564, layout load) and
state 1 (ab5c=Ov008_MainMenu_SetupToolbar, ada4, af54=Ov008_MainMenu_SetupTextSurfaces) +
DrawMenuPanels. TWO residues remain, both SIZE-EXACT and preserved in build/try/ (NOT parked):
  - func_ov008_0205c010 (menu object initializer, 1096B) -- mla-vs-walk strength-reduction.
  - func_ov008_0205a778 (list-count/average, 212B) -- register-coloring rotation.
This fire matched func_ov008_0205ab5c (584B) and func_ov008_0205af54 (584B) as clean
transcriptions -- the a3dc precedent (preserve residues, match clean deps) working again.

FRONTIER NEXT: the main-menu tick setup is done. Derive the next milestone from what runs
after state 1 -- the menu's per-frame INPUT/navigation update and the cursor, then the
menu->gameplay transition (ov002 bootstrap). Re-run the port-frontier algorithm: find the
callers of the menu scene handler / the input dispatcher, confirm vs Ghidra, pick the earliest
unresolved. The c010/a778 residues can also be retried with a fresh codegen idea (c010: the
mla-from-invariant-base steer; a778: the register-keyword form got count/sum matching, only the
listp/const3 r4/r5 swap resists).


## 2026-07-31: MENU STATE-0 FRAMEWORK -- a8e0 MATCHED (display/GX setup)

func_ov008_0205a8e0 = Ov008_MainMenu_SetupDisplay (636B ARM, 22 relocs, byte-exact, commit
67e019697) -- the video hardware setup called from Ov008_MainMenu_StateTick state 0. VRAM banks,
DISPCNT main/sub, DISP3DCNT + G3X clear colour, POWCNT1 bit15, BG char/screen-base + priority
registers, sub scroll regs, sub BG0 screen clear. MATCHED near-first-try using the DisplayRegisters
volatile-pointer convention from sibling func_ov008_02067c04 -- the struct reproduced the ROM's
base-register reuse exactly; the ONLY fix was a misread pool mask (0xffffcffd, held in a local and
reused >>0x11 as the clear-colour arg). LESSON: for menu MMIO display-setup funcs, copy the
02067c04 DisplayRegisters struct + const register pointers and it matches with near-zero regalloc
fighting; the risk is purely the mask CONSTANTS -- read them from the pool with read_memory, do not
eyeball.

UPDATE (same fire): a84c was ALREADY real C (calls/, prior session, `unsigned short i` form) -- the
frontier list here was stale; always re-check src/ before selecting. b19c MATCHED:
  func_ov008_0205b19c = Ov008_MainMenu_InitObjectListRetry (148B ARM, byte-exact FIRST TRY, commit
  27c6f2c). Alt object-list build: copies 3-word params (ldm/stm), retries ov008_InitObjectWithList
  up to 12x shifting the 2nd word high byte by 0x100, returns when b6e8(GetCtxField967c()) succeeds.
  ov008_InitObjectWithList is 2 args here too (r2/r3 phantoms), consistent with b230.

IN PROGRESS (build/try/c010.c, NOT parked): func_ov008_0205c010 = the menu object initializer
(1096B, 49 relocs, high-reloc). NOW SIZE-EXACT (1096==1096); only size-neutral register/form diffs
remain. The transform-loop +8 was closed by short-lived struct-array pointers
(`MenuSlot *d = &((Arr108 *)obj)->s[i]; Slot40 *sp = &((Arr40 *)obj)->s[i];` then Vec3 copies at
byte offsets +0x640/+0x634 from d and +0x40/+0x70 from sp) -- and that change also made `owner`
land in r4 (matching the ROM), so the r4/r5 issue is GONE. REMAINING (size-neutral byte diffs):
the RegisterSeqAndInit loop and the transform loop both emit a strength-reduced pointer WALK
(base += 0x108) where the ROM keeps the loop counter and does `mla r0, i, 0x108, base`. mwcc
strength-reduces `base + i*stride` to a walk because `obj` is loop-invariant; the ROM does not.
The one matched exemplar that keeps the mla (func_ov008_02052528, `entry->items[j]`) has its base
RELOADED each outer iteration AND an early `break` in the inner loop -- both defeat the walk.

EXPERIMENT LOG (this axis, ~16 forms across 3+ fires, ALL reduced to a walk): word index
`obj[i*0x42+N]`; byte cast `(char*)obj + i*0x108`; derived int; MenuSlot[i] via intermediate
pointer; struct-member `((MenuObj*)obj)->slots[i]`; struct-array short-lived pointer (this DID fix
the transform-loop SIZE via ldm/stm but the base is still a walk); variable stride `int
stride=0x108; i*stride`. Corpus mla-from-counter exemplars all have a NON-invariant base or nested
loops: 02052528 (base reloaded + break), 02079ae4 (nested `for j=i+1`), 0206836c/0207966c (to
re-read). Power-of-2 strides DO resolve to a shift when accessed as a single struct-array element
(the tween loop's `((TweenSlot*)(obj+0x49e))[i]` gave `add r0, sl, i, lsl #5`) -- but the transform
loop mixes a 0x108 (non-pow2) dest and 0x40 source and both walk.
HYPOTHESIS FOR NEXT FIRE: the ROM keeps mla because its base is effectively non-invariant, OR the
source used a form where the loop counter is the sole survivor. Concrete next steps: (1) fix the
corpus disasm scan (it aborted on an uncompilable calls/ file) and find a SIMPLE single loop with
an INVARIANT base that still emits mla -- if none exists in 12k funcs, the c010 form needs the
non-invariant-base trick; (2) try reloading a base pointer inside the loop; (3) build_sweep to
CONFIRM 3.0/139 is the build (compiler-is-correct, but the sweep is the one cheap park-rationale
test). c010 is SIZE-EXACT and every other axis matches -- this is the single open steer.
(prior note kept for context:) was +8 bytes (was +36). This fire fixed: the transform-copy loop
(two 3-word copies -> `*(Vec3 *)(obj + i*0x42 + N) = *(Vec3 *)(obj + i*0x10 + M)` gives ldm/stm) and
the tween loop (`((TweenSlot *)(obj + 0x49e))[i]` with TweenSlot = 8 words 0x20 -> `add r0, sl, i,
lsl #5`, power-of-2 stride resolved). REMAINING +8 = the transform loop STILL builds two induction
accumulators (r6=i*0x42 dest via `mla r1,i,0x108,obj` in ROM; r7=i*0x10 source via `add r8,sl,i,
lsl #6` in ROM) -- each accumulator adds its own `add rN, #stride` (2 instr = +8). mwcc strength-
reduces `i*0x108` and `i*0x40` no matter the form tried (word index, byte cast, MenuSlot[i] struct
array -> pointer-walk, derived int, struct-member-of-MenuObj -> pointer-walk). The FIRST
RegisterSeqAndInit loop has the same mla-vs-walk (size-NEUTRAL there, so not counted in the +8) plus
owner in r5 vs ROM r4 (size-neutral). NEXT ATTEMPT: corpus-grep found 14 matched ov008 funcs with
`mla` in loops (func_ov008_02053470 mla comes from `*(u16*)(node+0xa) * 0xa0 + base` = a LOADED
multiplicand, not the loop counter; func_ov008_0205cc04 `mla sb,r8,r6,sb`) -- READ those C forms to
find what makes mwcc emit `mla i, stride, base` for a plain loop counter instead of reducing. The
mla-forcing for a loop-counter index is the one open steer; everything else in c010 matches.

(original note:) Structure is byte-exact EXCEPT the induction codegen of two loops:
mwcc strength-reduces `i*0x108` (slot stride) to an accumulator, while the ROM keeps `i` (shared
with table[i]) and recomputes the node via `mla r0, i, 0x108, base` -- 4 mla with 4 stride-register
copies (fp/r4/r5/r6). Currently +20 bytes. ALREADY FIXED: the 9 dict-lookup blocks (a1fc two-step
addne/moveq form), the story-flag gate (write `if((int)flags >= 0x5e) idx += 0x400` for all four,
consts 0x5e/0xc1/0x12b/0x160, so mwcc emits `cmp #0x5e; addge`), the final 3-word field copies
(cast to a 3-word struct -> ldm/stm). REMAINING: force mla-not-accumulator in the RegisterSeqAndInit
loop (obj+0x590 + i*0x108, four calls) and the tween loop (obj + i*0x20 + off); neither the array-of-
structs nor the derived-int `i*0x108` form stopped the reduction -- needs the section-5/6 crack
(short-lived pointer per branch / second-order-derived index). Also owner lands in r5 vs ROM's r4
(size-neutral, will likely fall out once the loop regs settle). Pool: MemSet size 0x13f8, tag table
data_0208f050 (0xc int tags), 9 ResDict names (f0e0/f090/f0c0/f0b0/f100/f0d0/f080/f0a0/f0f0 at
obj+0xf/0x1f/0x2f/0x3f/0x4f/0x5f/0x9f/0x8f/0xcf), threshold 0x12b.

STRATEGY VINDICATED: func_ov008_0205ab5c = Ov008_MainMenu_SetupToolbar (584B, byte-exact, commit
3146b924d) -- a CLEAN transcription that matched after ONE arity fix (func_ov008_0205a778 is passed
obj even though its body ignores it -- the caller still emits `mov r0, r4`). This is the a3dc
precedent working: preserve the residues (a3dc/c010/a778), match the clean functions. Also learned:
func_ov008_02054678 = 3 args (ctx, name, id); the ROM's 4th is r3 left over from the template ldm.

NEXT (clean, fully scoped): func_ov008_0205af54 (584B, 29 relocs). Copies THREE TileSurfaceCfg
(10-word/0x28) structs from templates data_0208ee5c (local_3c @sp+0x64), data_0208ee0c (local_64
@sp+0x3c), data_0208ee34 (local_8c @sp+0x14); patches pPixels (idx8) = Ov008_GetCtxBlock968c() and
nVramTarget (idx6) = Ov008_ResetEntry(9) across all three; Set_5c4c(param_1+0x14f4, data_0209032c,
iVar4, iVar6) [4 args]; 3x TileSurface_InitAndUpload4bpp(param_1+0x1420/0x145c/0x1498, &cfg) [2
args]; Text_DrawDirectional (7 args, 2 on stack: str r1,[sp]; args 0x8e,2,1,DAT_b18c=0x821,
DAT_b190=data_02090344,dir); EnqueueObjGfxCommand; a story gate GameState_GetField(0,9) >= 0x165
picks uVar7 0/4; Veneer_0205665c + Ov008_RemeasureTextField + Text_DrawWithShadow (6 args, 2 stack);
then if mode!=0 && GetCtxObject9634(): a second Set_5c4c(&stack, data_02090348,3,1) + FindMinListValue
+ GetVarRecordByIndex + Text_DrawWithShadow; Ov008_MarkSlotUsed(9). TileSurfaceCfg exists in-tree
(ov000). Resolve the struct-copy pattern (ldm/stm vs field) and the 7-arg Text_DrawDirectional stack
layout from the disasm before writing.

SECOND RESIDUE PRESERVED (build/try/a778.c, NOT parked): func_ov008_0205a778 = counts menu list
objects with (obj[0x18]&3)!=0, sums GameState_GetField(obj[2]*3+0x2a4c, 3), returns
(sum*100)/(count*3) & 0xffff via func_02020400 (u64 divide). 212B, SIZE-EXACT; the ONLY diff is a
register-coloring ROTATION: ROM r4=listp(&list), r5=const3, r6=count, r7=sum, r8=node; mine
r4=const3, r5=count, r6=sum, r7=node, r8=listp. mwcc colors the stack-address (&list) LAST (r8); the
ROM colors it FIRST (r4), rotating everything up by one. Tried (all keep listp in r8): explicit
`int listp=(int)list` cache, listp defined first, u16 count/sum (adds 4B -- wrong), while vs for.
`register int listp=(int)list` + `register int three=3` got MUCH closer -- count/sum now colour
r6/r7 (matching ROM) and listp moves r8->r5 -- but the FINAL swap resists: mwcc colours the hoisted
const `3` in r4 and the &list cache in r5, the ROM does the opposite (listp=r4, three=r5). Neither
declaration order nor register order flips that last pair. This is an a3dc-class allocator residue. It's a DEP of ab5c (returns uVar5 for ab5c's divide loop),
but ab5c only needs a778's PROTOTYPE (u32) -- so ab5c is matchable with a778 preserved.
Templates: p = data_ov008_0208ede0 (3 words); InitObjectWithList is 2 args (consistent).

STRATEGY (a3dc precedent, works): the ov008 menu-object cluster mixes CLEAN transcriptions (a138,
a1fc, a684, b19c, a8e0, b230 -- all matched) with register/mla codegen residues (a3dc, c010, a778 --
all size-exact, preserved in build/try/, NOT parked). Match the clean ones (ab5c, af54 next), keep
the residues in build/try/ for a fresh-insight crack. Do NOT grind a residue for a whole fire.

## 2026-07-31: MAIN-MENU STATE DISPATCHER reached -- b230 + a684 MATCHED (this fire: 9c88, a684, b230)

Advanced past the scene-construction path (now complete except the a3dc register residue)
to the MENU STATE DISPATCHER milestone.
  - func_ov008_0205a684 = Ov008_Menu_RenderScenePanels (244B ARM, byte-exact FIRST TRY, commit
    4aff263b3). Per-frame render+submit of the scene's two panel widgets (slots 0x140->0x1b8/0x150,
    0x144->0x31c/0x180): update node, RenderNode, per active slot get anim frame + WidgetScrollCommit
    + optional MTX_ScaleApply43 (fx32 0x64000) when scene state==0xd + SetMatrix43 + SubmitObjectGfx.
    This CLOSED Ov008_Menu_AdvanceIntoPanel: all its callees are now real C.
  - func_ov008_0205b230 = Ov008_MainMenu_StateTick (360B ARM w/pool, byte-exact, commit ea4398086)
    = THE main-menu scene (0x13) per-frame state machine, called via the scene state-handler table
    (no direct caller -- it IS the "menu STATE DISPATCHER / per-frame tick" milestone). State 0 =
    first-time setup (ctx type -> obj[0x538]; object-list init from data_0208edd4 template w/
    slotCount 8 + listSize 7|3; layout resource for tag 0x13; variant gated on GameState_GetField(0,9)
    >= 0x165); state 1 = second-phase setup + 64-bit entry tick at obj[0x535]; always DrawMenuPanels.
    CRACKS: (1) outer state test = switch (forward-jump dispatch, cmp0/beq;cmp1/beq;b default);
    (2) the a84c and GetCtxField967c if-tests written `!=` with SWAPPED bodies so mwcc lays the else
    block inline and jumps to the then block -- the ROM's layout; `== 0` gives the opposite. Struct
    Ov008ObjListInitParams {int f0; int slotCount; int listSize} created + pool slot 0205b390 typed.

FRONTIER NOW: the main-menu state dispatcher (b230) is matched; its UNRESOLVED per-state deps are
the object/class framework that ticks the states (vertical-slice priority 3), all in ov008:
  state 0: func_ov008_0205a8e0, func_ov008_0205a84c, func_ov008_0205a8c4, func_ov008_0205b19c,
           func_ov008_0205c010, func_ov008_0205c564
  state 1: func_ov008_0205ab5c (-> func_ov008_0205a778), func_ov008_0205af54,
           func_ov008_0205a8e0 (shared), func_ov008_0205a8c4 (shared)
Pick the earliest by dependency: a8e0 (608B, state-0 first unresolved call after GetCtxObject95c0,
0-arg init -- verified 0-arg from b230's disasm) or a84c (68B, query returning 0/1). a8e0 is
earliest by call order but large; a84c is the small leaf. Verify each against Ghidra
callers/callees before selecting.

SCOPED 2026-07-31 (a8e0 = the menu DISPLAY/GX setup, 608B ARM, 22 relocs, mode arm): configures
VRAM banks (GX_SetBankForTex/OBJ/BG/SubBG/... SDK calls), DISPCNT (REG_DISPCNT masks 0x10, 0x1b00,
0x1f00), OBJ ext palette load (GX_BeginLoadOBJExtPltt 0x10), G3X_SetClearColor, and menu-specific
BG/OBJ PRIORITY registers via DAT pool pointers 0205ab40..0205ab58 (hardware/reg bases -- MMIO).
NOT platform-replaced (the BG/OBJ priority writes are menu layout semantics, not pure bring-up).
NEEDS the MMIO volatile-pointer convention: held `volatile u16 *` / DisplayRegisters-struct pattern
exactly like siblings func_ov008_020590b4 and func_ov008_02067c04 (see those + reference
mmio_volatile_convention) -- raw casts will mismatch. Bit-mask writes are `*p = *p & MASK | BITS`
(read-modify-write) with specific masks (0xcfff|8, 0x43|0x600/0x700/0x98/0x184/0x28c/0x384,
0xfffc|1/2/3, 0xffffe0ff|0x1b00/0x1f00). Callees resolved: GX_* SDK, G3X/G2S, MIi_CpuClearFast,
func_02010e80/f08/011134/011174/0201133c, func_ov008_02050c8c(0). 22 reloc-masked bl's hide most
scheduling noise -> the risk is the MMIO pointer/struct shape + mask exactness, not regalloc.
This is a big MMIO match; give it a full fresh fire. The a3dc register residue (Ov008_Menu_InitSceneObject)
remains preserved in build/try/a3dc_best.c -- confirmed unsteerable (31 experiments, no template in
12k funcs), NOT parked, integrate the instant the sceneId register falls.

## 2026-07-31: SCENE-OBJECT INIT PATH (0205a3dc constructor deps) -- 3 MATCHES (a138, a1fc, 9c88)

Frontier = the ov008 menu SCENE-OBJECT constructor Ov008_Menu_InitSceneObject (func_ov008_0205a3dc,
588B). The constructor itself has a documented sceneId r1/r3 register-allocation residue (~31
experiments, candidate preserved in build/try/a3dc_best.c -- NOT parked). Its DIRECT DEPENDENCIES
are now real C:
  - func_ov008_0205a138 = Ov008_Menu_LoadSceneText (140B, commit 2b8a82f60, PUSHED) -- builds the
      msg-container name from SceneParam[sceneId].f0, opens msg unit 0xe into obj+0x1b4, loads the
      character weapon into obj+0x4d4. OS_SPrintf 4th arg is a pass-through phantom; func_02024ee8
      is 2-arg.
  - func_ov008_0205a1fc = Ov008_Menu_BindScenePanels (480B, commit 68f647777, LOCAL/unpushed) --
      3 near-identical blocks (SceneParam name1/2/3), each: dict lookup (obj+0x5c +0x40), store idx
      at obj+0x148/0x14c + flag obj+0x140/0x144, then clear (c78) + init (c88) + summary (eb0) the
      panel sub-object at obj+0x1b8 (names 1,3) or obj+0x31c (name 2). Non-zero-branch-first dict
      test -> addne/moveq. struct SceneParam {int value; char name1[0x10]; name2; name3;}.
  - func_ov008_02059c88 = Ov008_Menu_InitPanelSubObject (336B, THUMB, commit PENDING this fire) --
      panel sub-object init: packs a resource descriptor from resBase, registers the sprite seq,
      loads the layout archive variant chosen by sceneId/slot. TWO CRACKS: (1) both scene switches
      must emit the {4,9,0xf} case body BEFORE the {2,0x13} body (source case order drives emission
      order; last body falls through); (2) each variant test written as if/else (true-branch-first)
      not ternary, so mwcc emits `cmp; bne; =0; b; =1` instead of `beq`/reversed. Both in
      codegen-cracks.md.

FRONTIER NOW: remaining direct deps of Ov008_Menu_BindScenePanels/InitPanelSubObject still to
confirm as real C -- func_ov008_02059c78 (panel clear) and func_ov008_02059eb0 (panel summary
build). After those, revisit the 0205a3dc constructor residue and the sibling sub-scene setup
funcs (0205a684, 0205a778, 0205a8e0, 0205ab5c, 0205af54). Confirm each against Ghidra
callers/callees before selecting; do NOT default to address order.

## 2026-07-31: SHARED-CONTEXT (data_ov008_02090f1c / +0x5c6 bitfield) FAMILY -- 5 MATCHES in one fire

Swept the 17 ov008 funcs that reference the shared menu-context global data_ov008_02090f1c
(the +0x5c6 status halfword is a 16-bit BITFIELD). Matched 5 clean this fire, all pushed except
the last (bf0cb190f, waits for next hourly gate):
  - func_ov008_02058a28 = Ov008_Menu_AdvanceIntoPanel (184B) -- one-shot advance into sub-scene 8
  - func_ov008_02058ae0 = Ov008_Menu_CommitEnterSubScene8 (204B) -- confirm/commit sub-scene 8
  - func_ov008_020579a8 = Ov008_Menu_UpdateDirectionalPrompt (284B) -- prompt-state + text redraw
      (direct dep of the two above)
  - func_ov008_02057b7c = Ov008_Menu_PositionSelector (252B) -- move selector entry 0x15
  - func_ov008_02057c78 = Ov008_Menu_ToggleDetailPanel (736B) -- enter/leave detail panel (calls
      Ov008_Menu_PositionSelector)

THREE NEW CODEGEN CRACKS (all written up in references/codegen-cracks.md), each unblocking a class
of "physical register coin-flip" residues the way the bitfield unblocked 56988-style ties:
  1. A `(x<<(31-n))>>31` bit test is a BITFIELD access `f->bN`, not a manual shift -- only the
     bitfield IR colours the CSE'd container into the field register like the ROM.
  2. For a load + preserved-copy pair, mwcc colours locals by DECLARATION order (1st->r4, 2nd->r5);
     declare the preserved copy first so the ldrh targets the working reg directly.
  3. K&R (unspecified-arg) declaration lets one callee be called with different arg counts at
     different sites; caching a global base in a local keeps it in one reg across a store pair.

UPDATE 2026-07-31: func_ov008_020574c0 (1256B) MATCHED = Ov008_Menu_RefreshSlotPanel
(commit 932311daa, local, unpushed). It was the harder of the two setup dispatchers; the
register allocation over the correct structure needed three coloring cracks (two-step mask
compute, slot-loop fall-through orientation, byte-load decl order) -- all written up in
codegen-cracks.md. Path was 66 -> flip loop -> 22 -> two-step mask -> 8 -> swap decls -> MATCH.

UPDATE 2026-07-31: func_ov008_02057f58 (1512B) MATCHED = Ov008_Menu_RefreshSubitemGrid
(commit 49f964bc0). The LARGEST function in ov008, and the LAST member of the shared-context
(data_ov008_02090f1c) family -- so the entire menu-tick setup path (both dispatchers,
RefreshSlotPanel 020574c0 + RefreshSubitemGrid 02057f58, and all sub-scene handlers) is now
100% real C. Closed after ~6 fires on a 1-instruction residue; the crack was `unsigned int
flags[7] = {0};` (aggregate initializer -> held-base zeroing, matching the ROM) + bVar4
branch orientation + early bool normalisation. All in codegen-cracks.md.

FRONTIER NOW: the shared-context menu-tick family is exhausted. Next iteration must re-derive
the frontier: sweep the CALLERS of the two setup dispatchers (the menu tick / state dispatcher)
and pick the earliest unresolved function in the ov008 main-menu tick path, or the next
menu->gameplay transition dependency. Do NOT default to address/size order -- read game-flow.md
+ this file and confirm against Ghidra callers/callees before selecting.

## 2026-07-31: MATCH func_ov008_0206e720 = Ov008_Menu_SetupStateEntry (byte-exact 248B) -- vein change paid off

FIRST-TRY byte-exact match after switching veins (per feedback_match_rate_too_low): picked the
HIGH-RELOC clean profile (248B, 17 relocs) instead of the register-heavy dispatchers. With 17
reloc-masked bl's the scheduling/regalloc noise is hidden, so a straight Ghidra transcription
matched immediately. Menu state-entry UI setup: queries a status record (func_ov008_02055c24 out
-param, gate halfword st[2]); if ready, hides toolbar entries 0x29/0x51, fires the object inner
vtable + enqueues its gfx (ctx+0x64), shows entry 0x80 + the optional ctx+0x54 slot, releases and
re-shows entry 5, records state at ctx+0x14. Key read: func_02030158/func_020300f8 take only r0
(ctx+0x64) -- Ghidra's extraout_r1/param_4 there are artifacts; declare them 1-arg. Ghidra renamed
Ov008_Menu_SetupStateEntry + prototype; delink auto-generated (gen_delinks).

LESSON (reinforced): on a frontier of register/scheduling-residue functions, the HIGH-RELOC medium
functions are the ones to pick -- the reloc-masked bl's dominate and hide the codegen noise. The
register-heavy dispatchers (56988, 02062d00, 71ebc, all in build/try) are the exception, not the rule.


## 2026-07-31: VEIN CHANGE (per feedback_match_rate_too_low) -- ov008 menu-confirm handler

After ~11 fires stuck on register-heavy ov008 dispatchers (56988 physical-coloring coin-flip;
02062d00 +24 register-pressure -- both left in build/try, documented, NOT parked), applied the
user's own standing feedback (change vein when stuck) and picked a fresh high-yield profile:
undone ov008 funcs 60-260B with >=3 relocs, ranked by matched-caller count.

SELECTED func_ov008_02071ebc (260B, 13 relocs) = a menu-item CONFIRM handler: validates the
current selection (state 1e78 branches: GameState field >=2, or ctx-object checks + IsField8LeField57
/ helper_6fb2c), and if not blocked dispatches two handlers (0x35cd/0x35df), SetGlobalConfig(2),
PlaySound(0,1); else PlaySound(0,4). Two real fixes landed: the GameState result test is `>= 2`
(cmp #2; movhs) not `> 1`; and the inner branch is inverted so the IsField8LeField57 path is the
fall-through. Now SIZE-EXACT 260/260, build/try/71ebc_e.c, with ONE scheduling diff: mwcc places
the fb34 arg2 setup (`mov r1,r5`, e->r1) AFTER the `cmp/beq` while the ROM hoists it before (fills
the load-use slot after `ldr param_1[0x10]`). 6 source forms tried; the arg-hoist is scheduling.
This is dramatically closer than the register grinds (1 instr vs +24) -- the vein change worked.
NOT parked; selected; best build/try/71ebc_e.c.


## 2026-07-31: FRONTIER CORRECTION + IN PROGRESS func_ov008_02062d00 (792B) -- build/try/62d00_b.c @ 820

Selection fix: func_ov008_02056988 (the sprite-position leaf) had been picked over its CALLER
func_ov008_02062d00 by tractability/size -- which the rules forbid ("no trabajes por facilidad,
tamano"). Per selection priority #4 (frontier function) > #5 (its dependency) and the vertical-slice
order (state/tick #2 before sprite-position helper #6/#9), the correct pick is func_ov008_02062d00,
the menu page/state refresh (Ov008 menu tick): copies two tag tables to a contiguous stack array,
fires tag-tracker callbacks per state (1e78) case 2/3, sets the highlight object's visibility, runs
an 8x5 grid loop building per-slot entries (each 0x28 B at ctx+0x10a0) via func_ov008_02056988,
walks the NNS highlight list (ctx+0x19b8) setting +0x10be halfwords, records the page (ctx+0x18),
Ov008_RebuildGridHits, then func_ov008_0206245c + PlaySound(0,2). 56988 stays in build/try as a
still-unmatched callee (referenced by reloc; does not block 02062d00's byte match).

Status: build/try/62d00_b.c, semantically complete (transcribed from a clean Ghidra decompile,
callee arities verified), **820/792 (+28)**. Residue is register pressure: my transcription keeps
more locals live than the ROM (which spills only slot+row), so mwcc pushes one extra callee-saved
(push r3, sub #0x3c vs ROM's push {r4..} sub #0x38) and the stack tables land at sp+0x24 not +0x20.
Ghidra's `uStack_28 = param_4` is an artifact -- the ROM never stores param_4 (removing that store
took 828->820). Next: cut live-local count to match the ROM's slot+row-only spill set. UPDATE (fire): REAL fix found -- the grid flag byte is UNSIGNED (ROM uses `ldrb ...,#0xe88;
  cmp r0,#0xff`), not `*(char*)==-1` (Ghidra signedness trap); the signed form made mwcc hoist -1
  into a register (`mvn r4,#0`). Fixing to `*(unsigned char*)==0xff` dropped 820->816. Confirms
  02062d00 has findable issues (NOT a coin-flip). Remaining +24: mwcc emits `mul page,#0xa0`+spill
  for `page*0xa0+ctx` where the ROM uses `mla r8,page,#0xa0,ctx` and holds nodebase in r8 across the
  inner loop; mine spills it (one extra live value). Best now build/try/62d00_h.c (=g+nodebase hoist).


## 2026-07-31 (cont'd): func_ov008_02056988 now SIZE-EXACT (236/236) -- build/try/56988_i.c

Advanced from 220 to size-exact. Two more cracks landed:
  - The inner cell() guard must be a NESTED if/else (computing block taken, `else` sets 0), NOT an
    early return -- the early-return form predicates the short body (`ldrhne/addne`), the if/else
    form BRANCHES like the ROM (crack: codegen-cracks predicate-vs-branch, 204->220->236).
  - `s` (the e[8]/e[0x18] select) must be INLINED into the `lr` cast via a ternary, not a named
    local -- as a named local it took an extra callee-saved (push {r3,r4,r5,lr}); inlined, the
    prologue drops to the ROM's `push {r4,lr}`.
Residue (size-exact, ~register/schedule only): (1) cellB lands in `lr`, ROM uses `ip`; (2) the
inner base[1] guard emits an extra `moveq r3,#0` before the branch where the ROM shares one
out-of-line `mov r3,#0` exit for both guards; (3) the tail halving folds one `lsr` into the add
(`add r1,r1,r2,lsr#16`) where the ROM keeps two separate `lsr`. All three are register-allocation
/ instruction-scheduling driven on an otherwise byte-for-byte instruction stream. NOT parked; best
form build/try/56988_i.c. Next: force cellB into ip and the shared single-exit for the guards.
  UPDATE (next fire): 6 more forms tried (||, goto-shared-exit, register cellB, decl/operand order,
  u16 t) -- none move the residue. Pre-park checklist clean: func_02017088 arity=1 (confirmed by matched
  sibling func_020255f0), return genuinely void, no aliasing (int addresses throughout). Residue is
  register-allocation + scheduling on a correct size-exact stream (cellB wants ip not lr; the inline
  cell-guard emits a redundant moveq; the halving folds one lsr). Still SELECTED, best 56988_i.c.

## 2026-07-31: IN PROGRESS func_ov008_02056988 (236B ARM) -- earlier @ 220/236 (superseded above)

Direct dependency of the ov008 menu state/cursor-refresh frontier (func_ov008_02062d00 calls it).
Computes a screen position from two animation "cells": cellA from base e+0x3c, cellB from the
dynamic base e+e[0x34], each via an inlined helper cell(base) = base + base[6] + 4 guarded by
base != 0 && base[1] != 0; then out[0] = *cellA + ((e[8] or e[0x18]) & 0xffff) and
out[4] = ((cellB[0]>>1) + ((e[0x2c]&0xffff)>>1)) & 0xffff, skipped when cellB[2]&1. The 0x1c000000
mask on *cellA picks e[0x18] vs e[8]. func_02017088 returns the entity e.
Two levers already found:
  - `e` must be an INT address, not a pointer: as a pointer mwcc proves `e+0x3c != 0` and drops the
    ROM's null checks (32 B short); as int the `!= 0` guards survive.
  - cell() must be a `static inline` helper with the guards as EARLY RETURNS -> the ROM's verbose
    multi-`mov r,#0` / shared-tail branch form (204 -> 220).
Remaining 16 B: mwcc PREDICATES the inner `base[1]!=0 -> value` body (ldrhne/addne) where the ROM
BRANCHES (bls to a shared mov r,#0), and mwcc spends one extra callee-saved (push {r3,r4,r5,lr} vs
ROM {r4,lr}). Next: defeat the inner-check predication (branch-vs-predicate crack) and drop the
extra callee-saved. NOT parked; best form is build/try/56988_d.c.

## 2026-07-31: MATCH func_02032388 = ObjNode_InitFromDesc (byte-exact 160B, THUMB) -- park rescue

Direct dependency of Ov008_Menu_SetupSprites (func_ov008_0207f614 calls it to build each menu
sprite object) -- selection priority #5, so it outranked the other ov008 frontier builders.
It was PARKED in nonmatching/ as "a THUMB register-allocation tie -- no C form reproduces the
coalescing (+4 bytes)". The park was WRONG: it was the skill's #1 park mistake, a bad callee arity.

func_02031d90 takes TWO args (obj, resName) -- its real definition already existed in
src/calls/func_02031d90.c (allocates a 0x64 Node, loads a sprite resource via func_02031c58 =
SpriteRes_Load, links it into obj's child list at +0x4620). The park declared it 4-arg
(obj, name, off, v). That forced mwcc to rematerialise the store offset o-0xe into r2 as a phantom
3rd arg right before the bl (+2 B), and shoved the persistent base offset `o` out of r0 into r2,
which in turn cost the o-0xc store an extra copy (+2 B) = the whole +4 residue. The r2/r3 live at
the ROM's call are just the leftover offset/value of the obj[+0x4616] store, not arguments.
Declaring func_02031d90(void*, char*) 2-arg -> instant byte-exact 160/160. A one-line
`grep -rh func_02031d90( src/` would have found the arity and never parked it.

ObjNode_InitFromDesc(obj, desc): zero-fills the 0x4a38 object node, stamps type=desc[1] at +0x4604
(sub-code 0x12/0x22 at +0x4608 for type 1/2), seeds the anim/state block at +0x4624, mirrors
desc[2]/desc[3], and if desc[0] (resource name) is set, Obj_LoadResourceNode(obj, desc[0]).
Ghidra: renamed ObjNode_InitFromDesc + Obj_LoadResourceNode, both prototypes set (2-arg fixed).
Deleted the nonmatching/ twin; delink auto-generated by gen_delinks (src/calls/).

## 2026-07-31: MATCH func_ov008_0207f614 = Ov008_Menu_SetupSprites (byte-exact 640B)

2nd ov008 main-menu match. Port-required: sets up the menu's sprite/OAM cells on page change (first
visible menu frame, vertical-slice #4/#9). Resets + zero-clears two adjacent OAM cell buffers
(SpriteMgr.bufA @+0x54, bufB @+0x4a8c, each 0x4a38 = 19000 B; note 0x54+0x4a38 == 0x4a8c), then a
15-way `switch(id)` jump table registers cells (func_02032388) and commits them (func_0203243c) with
handles `(((mgr->cellSrcN + 0x8000) & 0x00fffffc) << 7) | 0x80000000 | slot`. Pages {8,9,12,>14} do
nothing.

Two match levers (both 1st-structure, size-exact on try #1):
  1. CASE-BLOCK ORDER = SOURCE ORDER. mwcc lays out switch case bodies in the order the labels first
     appear in the source, NOT by case value. ROM order is A(0,1,2,3,10,11) then B(13,14) then
     C(4,5,6,7); writing C before B put the jump-table targets 8 bytes off (first diff @0x80). Reorder
     the `case` groups to A,B,C and the table + block layout aligned.
  2. func_0203243c(region, HANDLE) is 2-ARG. ROM computes the gate handle into r1 (`orrs r1,r0,#tag`)
     and keeps it live to the `bl` -- because the handle is BOTH the zero-gate (`beq`) AND the 2nd
     arg. Calling it 1-arg left the handle dead in r0 (`orrs r0,...`), 3 bytes off. Fix: declare
     `unsigned int h = ...; if (h != 0) func_0203243c(region, h);` -> h lands in r1 = arg2. The
     `!= 0` test is provably-true (bit31 forced) but mwcc doesn't range-prove it, so the `orrs;beq`
     stays -- matches ROM. Data-reload pattern: `data_ov008_02090fa4` is a `SpriteMgr *` global read
     fresh each access (opaque calls between uses prevent caching) -> ROM's repeated `ldr r0,[r1];
     ldr r0,[r0]`; using `extern SpriteMgr *g;` with direct `g->field` reproduces it.
  Ghidra: renamed Ov008_Menu_SetupSprites(int id); created SpriteMgr + OamReq structs; set
  func_0203243c(void*,uint) prototype; typed the pool slot @arm9_ov008::0207f888 as SpriteMgr*.
  Wired delink (gap 0x0207f614-0x0207f894) in ov008/delinks.txt; file in src/overlays/ov008/calls/.

DEFERRED (frontier-priority correction, NOT parked): func_ov008_0206cdb4 (menu scrollbar/arrow
update, 208B) held at 200/208 in build/try/6cdb4_f.c -- SCHEDULING RESIDUE, documented class. ROM
computes the arrow-visibility bool BEFORE FindEntryById and holds it in a callee-saved reg
(`cmp;movgt r8,#1;...;mov r2,r8`), +1 mov/block x2 = 8 B; mwcc 139 -O4,p always SINKS it (the bool's
only input `pos` is live to the final call -> always rematerializable, so the scheduler computes it
late straight into r2, the optimal/shorter form). 8 source variants (inline vs separate FindEntryById,
both-early, separate vars, arg-eval order) all give the identical vis-late form. Was mis-selected over
higher-priority setup code; 0207f614 was the correct play-order pick (setup > cosmetic scrollbar).

## 2026-07-31: MATCH func_ov008_02063018 = Ov008_Menu_ChangePage (byte-exact 260B) -- first ov008 match

First byte-exact match on the ov008 main-menu frontier. Menu page-switch: struct-copies the
per-page tag table (PageTags = two u32[8]) to the stack, switches the visible page
(func_ov008_0205ea88), marks the head list object's bit, fires the tag-tracker callback
(func_ov008_0205589c) for the outgoing page (a[ctx->0x70]) and incoming page (b[page]), records
new page/state (ctx +0x70/+0x74/+0x9c), refreshes widgets; returns (ctx->0x78 != 0).
Match lever: `int ret = 1;` at the TOP + `if (ctx->0x78 == 0) ret = 0;` -- giving the return bool a
long live range in r5 so the const-table copy pointer is forced into `ip` (ROM's `ldr ip,[pc]; ldm
ip!`), not r5. Wrong ordering (`ret = (ctx->0x78 != 0)` late) put the copy pointer in r5 -> 1-byte-off
cascade. Callees were already named (Ov008_SwitchPage/GetCtxBlock9500/FindEntryByTag/TagTracker...).
Ghidra: renamed Ov008_Menu_ChangePage(ctx,page) + created PageTags struct + comment.

Frontier selection method (call-graph, not address): ranked the 119 undone ov008 funcs reachable
from matched code by matched-caller count; the most central are func_ov008_02063790 (1308B, 5),
func_ov008_0207f614 (640B, 5, menu OAM/sprite-state setup, Ghidra-analyzed), func_ov008_0207dfec
(4512B, 5), func_ov008_02062d00 (792B, 4). NEXT ov008 menu targets from that list.

## 2026-07-31: SP FRONTIER ADVANCE -- ov000 complete; next milestone = ov008 main menu

Frontier re-confirmation (port-first algo). Verified against the tree:
- MAIN boot/runtime framework: fully matched (main-sequence funcs 020027f0/020285f0/02023f58/
  02024e34/02003a20 + InstantiateClass/RunClassConstructor/StoreGlobalPairAt10 all INTEGRATED).
- MAIN text-render chain: matched (func_0201449c Text_AlignAnchor + neighbours + callers).
- Scene 1 = ov000 (logo/title/menu levels/Load screen): **261/261 functions matched -- COMPLETE.**
- Message-queue (data_0204c230/c22c) = wireless MULTIPLAYER subsystem, NOT the SP critical slice;
  send/recv path matched + fully typed; only the 2 blocked allocator/scheduler funcs remain
  (func_02031384 AllocSlot -- genuine blocker proven across 38 source + 27 builds + 6 opt levels +
  0/15965 corpus; func_02030e7c Init). Both documented in build/try, escalated in dudas.md, NOT
  parked; they do not gate the SP slice.

NEXT SP MILESTONE (earliest unresolved in play order): **ov008 = main menu / configuration
(Scene 0x13)**, 340/1223 undone. Then ov002 = gameplay (Scene 2), 638/1474 undone. (ov006 char
select = Mission Mode/multiplayer, 23 undone -- a side branch, lower priority.)
Next step: identify the ov008 menu SCENE CONSTRUCTOR + state dispatcher (vertical-slice #1-2) via
the scene table / class descriptor (NOT by address), Ghidra-first, then match. ov008 funcs live in
the arm9_ov008 overlay address space (prefix `arm9_ov008::` for Ghidra).


## 2026-07-31: MATCH func_02030b58 = MsgQueue_RecvDispatch (byte-exact 372B, integrating)

Byte-exact (372B, 4 relocs: func_02030788, func_02031258=SendGate, func_020314a4=MarkSlotReceived,
data_0204c22c). The receive-side dispatcher, downstream of SendGate. Reads the rx header byte
{kind:2, ch:3, hi:3}: kind 2 -> ack (MarkSlotReceived); kind 1 -> data (seq check vs the channel's
recv counter, invoke the channel handler via the ctx+0xc function-pointer table (blx), bump the
counter at ctx+0x60 wrapping at 0xffff, then re-ack via SendGate). ctx = data_0204c22c (the RECEIVE
ctx, distinct from data_0204c230 send pool).

Winning source shape (levers, on top of the earlier iters' 356->388 exploration):
  1. switch(kind) 3-way (ROM beq-chain; case 2 laid out at the end).
  2. rx header AND ack header as bitfield structs {kind:2,ch:3,hi:3} -> clean 2-bit kind extract
     `(hb<<30)>>30` (not `and #3`).
  3. ★ ack packet built as a stack STRUCT VALUE (AckMsg msg; msg.kind=2; ...), NOT via a
     (AckMsg*)&local cast: a pointer cast forces `add rX,sp,#0`; a struct value writes [sp,#off]
     directly like ROM. And do NOT init it from a param -- param_4's `local_10=param_4` is a DEAD
     store (byte0 is fully overwritten by the 3 field writes), which ROM elides; the real signature
     is just (unsigned char *msg, int size).
  4. ★ ctx = data_0204c22c used DIRECTLY (one deref: `int *ctx = data_0204c22c`), not
     `*data_0204c22c` (that adds an extra ldr).
  5. wrap-check recomputes the counter address with a DIFFERENT grouping than the increment
     (increment `ctx + 0x60 + ch*2` -> base ctx+0x60; wrap `ctx + ch*2 + 0x60` -> base ctx+ch*2),
     with `ch = m->ch` re-read (the increment store aliases *param_1 so mwcc reloads).
  6. ack-gate written `seq <= counter` (decompiler's operand order) -> `cmp seq,counter; pophi`,
     not `counter >= seq` (which gives the swapped `poplo`).
  ldrh vs ldrsh: all seq/counter loads are `unsigned short` (ROM uses ldrh).

Ghidra (same batch): FUN_02030b58 -> MsgQueue_RecvDispatch(msg, size), plate comment; created
RxHdr (1B), AckMsg (4B) packed-bitfield types. Saved.

MESSAGE-QUEUE SUBSYSTEM now nearly complete: matched Enqueue, GetHeap, MarkSlotReceived, Contains,
ResendForPeer, SendGate, RecvDispatch (+ f58/10e8/1574/158c/01fffbf4 earlier).

func_02031384 (AllocSlot, 188 ARM): SELECTED, best = build/try/31384_best.c, NOT parked.
★ 2026-07-31 (3rd pass) BREAKTHROUGH: the residue was NOT pure coloring -- it was ADDRESSING.
The old size-exact 188 form used folded offsets (`blk+0x744` for seq, `ctx+0xd0+idx*0x34+4` for the
copy dest), which was size-exact only by coincidence (extra adds balanced a wrong coloring) and put
the pooled-0 in r6. Rewriting blk-relative with ROM's exact base+offset SPLITS -- seq base
`blk+0x700` accessed at `[+0x44]` (0x744 is not a valid ARM immediate, so the split is FORCED),
states `blk+0xc4`, copy dest `state+4`, and the handle store RE-INDEXED as `entries[idx*6]` not the
cached slot ptr (confirmed against the Ghidra decompile, which now uses the MsgQueueCtx/MsgSendSlot
structs) -- FLIPS the pooled-0 into lr, matching ROM. Now 180/188 (2 short).
The Ghidra decompile is the reference: `uVar2 = DAT_02031438` (the pooled 0) assigned at the top and
used at `slot->peer` is what holds it in lr; the handle is `ctx->sendSlots[idx].handle` (re-index)
while size/type/peer use the cached `slot`.
REMAINING (2 instrs = 8B short): my CORRECT source emits 180; ROM has 188 with TWO redundant mwcc
copies the clean C doesn't -- a dead `mov r5,lr` (pooled-0 copied to r5, then r5 reused for
0x80000000) and `mov r0,r7` (seqbase copied to r0 for the wrap instead of reusing the held reg).
Forcing the wrap copy via a recompute reaches 184 but reshuffles the coloring (pooled-0 leaves lr):
the two requirements (pooled-0 in lr + the wrap copy) conflict under mwcc's allocator (whack-a-mole).
best=31384_best.c is the blk-relative/re-indexed form (pooled-0 in lr, correct addressing, 180).
Next axes: find the source construct that makes mwcc emit the two redundant copies WITHOUT recompute
(a live-range/pressure nudge that keeps the pooled-0 in lr), or accept as an mwcc coalescing regime
difference pending user input (NOT parked meanwhile).

★ 2026-07-31 (4th pass) -- SIZE-EXACT 188 achieved with the correct structure. The winning model
is a struct ANCHORED AT BLK (base+0xc), not base: `MsgSendBlk {u32 freeMask; MsgSendSlot
sendSlots[32]; MsgSendSlotState sendStates[32]; u32 seq;}` with `blk=(MsgSendBlk*)(data_0204c230+0xc)`.
That makes mwcc pick blk (base+0xc) as the base register (freeMask at [blk,#0]) exactly like ROM,
gives the seq split `[blk+0x700, #0x44]` for free (0x744 not a valid ldrh offset), and reproduces
ROM's wrap copy `mov r0,r7`. Adding a named `MsgSendSlotState *st = blk->sendStates + idx;` and
copying to `st->rest` separates the `+4` (mla; add #4) and reaches 188 byte-for-byte in SIZE.
best=31384_best.c is now this 188 size-exact form (was 180). Ghidra decompile is the exact
reference (MsgQueueCtx/MsgSendSlot/MsgSendSlotState typed): pooled-0 = `DAT_02031438` held and used
at slot->peer; handle store re-indexed `sendSlots[idx].handle`.
REMAINING (size-exact, register-allocation cascade): the two 188 forms put the pooled-0 in r4 and
drop sl (push {r3,r4-sb,lr}), where ROM keeps it in lr, uses sl, and has the dead `mov r5,lr`. The
lr placement and the state `+4` separation are COUPLED under mwcc: the fold keeps pooled-0 in lr but
is 1 short (184); separating it reaches 188 but shifts pooled-0 to r4. ~30 variants total across 4
passes. This is now a genuine mwcc register-allocation cascade on a SIZE-EXACT, correct-structure
function -- the residue is which physical registers, plus one redundant dead copy mwcc emits for
ROM's build but not for ours. NOT parked; best form preserved.
★ 2026-07-31 (5th pass) -- GENUINE-BLOCKER state (~37 variants + build_sweep). This pass: held
`entries` explicit (entries took lr, pooled-0 -> r4); state ptr computed EARLY/held (pooled-0 -> ip).
Every variant gives a DIFFERENT allocation; none matches ROM's (pooled-0 in lr + sl used + dead
`mov r5,lr`). build_sweep on the size-exact form: NO build of the 27 reproduces it -- the 2.0/*
(= real 3.0 114-139, our 139 range) all give "117 off", dsi size 184, 1.2 size 196-204. So no
available build flips it and (per the user) 139 is correct => a source form not found in 37 tries.
Assigned-function "genuine blocker after >=30 experiments": best in build/try/31384_best.c (188
size-exact, correct structure), decision escalated in dudas.md. STAYS SELECTED, NOT parked. Do NOT
re-run the same coloring axes -- await the user, or the one structural angle left: force
blk/slot/idx/seqbase/states/pooled-0 all simultaneously live so mwcc uses 7 callee-saved + lr like ROM.
★ 2026-07-31 (6th pass) DECISIVE: GREP'd all 15,965 matched real-C functions for the exact missing
artifact -- a `ldr lr,[pc]` (pooled const in lr) followed by a dead `mov rX,lr` copy. ZERO
occurrences. So no source template for it exists anywhere in the corpus, no build of 27 reproduces
it (build_sweep), and 38 source variants don't trigger it. Overwhelming evidence this specific
register-coalescing artifact is outside our toolchain's reproducible set for this function. STAYS
SELECTED in build/try/31384_best.c (188 size-exact, correct structure), NOT parked; escalated in
dudas.md. Stop grinding this axis -- await the user.
★ 2026-07-31 (7th pass) opt-level axis ELIMINATED: compiled the best form at -O0/-O1/-O2/-O3/-O4
(+/- ,p). -O2/-O3/-O4 all give size-exact 188 with the SAME 117 bytes differing (identical register
cascade); -O0=260, -O1=192 (wrong size). So it is not an opt-level difference either. func_02031384
is now a genuine blocker proven across EVERY cheap axis: 38 source variants + 27 builds + 6 opt
levels + 0/15,965 corpus template for the dead-copy artifact. Nothing cheap left to test.
★ FRONTIER RE-CONFIRMATION (port-first algo step 6): the message-queue (data_0204c230 send /
data_0204c22c recv) is the WIRELESS MULTIPLAYER message system -- it runs on CARD_GetResultCode,
peer ids, session state and localPlayerIndex. It is a MAIN runtime subsystem but NOT on the
single-player boot->logo->title->menu->gameplay critical slice. Its send/recv path is matched +
fully typed (7 funcs + MsgQueueCtx/MsgSendSlot/MsgSendSlotState/MsgHdr/RxHdr/AckMsg/RecvCtx), so it
is port-COMPLETE except the 2 blocked allocator/scheduler funcs. Per port-first, the frontier now
returns to the earliest unresolved SINGLE-PLAYER milestone (boot/logo/title/menu), NOT more
message-queue. func_02031384/func_02030e7c remain documented blockers in build/try, awaiting the
user; they do not gate the SP port slice.

func_02030e7c (Init, 220 THUMB, scheduler artifact) also remains size-exact in build/try.

After the message-queue subsystem: advance the port frontier to the next runtime-framework
consumer or the earliest unresolved boot/scene dependency (re-derive from callers of the matched
message-queue funcs and the scene backbone, not by overlay number).

## 2026-07-31: MATCH func_02031258 = MsgQueue_SendGate (byte-exact 300B, integrating)

Byte-exact (300B, 4 relocs: CARD_GetResultCode, MI_CpuCopy8, func_02030d2c, func_02030fdc=Enqueue).
The send gate that ResendForPeer/Enqueue funnel through: routes by session state
(CARD_GetResultCode) and message type -- state 2 + type 3/0x12 -> pack header + local dispatch
(func_02030d2c), state 3 -> whitelisted enqueue, else -> unconditional enqueue.

Winning source shape (levers, in order of discovery):
  1. switch(rc) for the CARD-state dispatch (NOT if/else-if): ROM tests ==2 and ==3 up front then
     branches to separate blocks -- the sparse-switch compare chain, not an if-else (which
     interleaves the first block between the tests and forces a reload).
  2. header packed as bitfield struct {u16 f0:1, type:5, size:10} -> the two RMW field writes give
     ROM's `bic #0x3e` (type mask ~0x3e, valid imm) and pool-loaded `0xffff003f` (size mask ~0xffc0,
     invalid imm). A flat mask on the type field lets mwcc drop the redundant &0xffff that ROM keeps.
  3. ★ size param typed `unsigned short` (not uint): a uint->ushort bitfield write inserts a
     redundant halfword narrow (`<<16>>16`, +8B); a ushort source writes the field clean
     (`param<<22>>16`). All callers already pass a u16 size, so the signature is honest.
  4. ★ header accessed via INLINE `(MsgHdr *)buf` casts, NO named pointer variable: a named `h`
     used for the dispatcher arg after the MI_CpuCopy8 call makes mwcc hold it in a callee-saved
     reg (shifting every param up one register); inline casts let mwcc rematerialise the cheap
     sp+0 pointer for func_02030d2c instead (ROM: `add r0, sp, #0`), keeping params in r7/r6/r5.
  5. 20-case inner switch(type) for the state-3 enqueue whitelist -> the `addls pc,pc,type,lsl#2`
     jump table.

Ghidra (same batch): FUN_02031258 -> MsgQueue_SendGate(int msgType, u16 *payload, u16 size), int ret,
plate comment; created MsgHdr bitfield type {f0:1,type:5,size:10} = 2 bytes (needed
setPackingEnabled(True) -- unpacked u16 bitfields bloat to 4). Saved.

NEXT FRONTIER: func_02030b58 (receive dispatcher) -- SELECTED, IN PROGRESS in build/try
(30b58_best.c = 364 of 372, 8 short, NOT parked). Structure fully decoded: rx header 2-bit kind
(2=ack->MarkSlotReceived, 1=data), seq check, handler dispatch via the ctx+0xc function-pointer
table (blx), per-channel recv counter bump at ctx+0x60 (wrap 0xffff), then re-ack via SendGate.
ctx = data_0204c22c used directly (ONE deref). Levers found: switch(kind) + function-scope
local_10=param_4 (avoids an extra callee-saved push), rx+ack headers as {kind:2,ch:3,hi:3}
bitfields. Remaining 8B: ldrh-vs-ldrsh on the seq/counter loads (use unsigned short), the
wrap-check address recomputation grouping (forcing it overshot to 380 -> net ~2 instrs not 4),
and the str[sp] (local_10) placement. See the header comment in build/try/30b58_best.c.
Also still size-exact in build/try (allocator/scheduler artifacts): func_02030e7c (Init 220 THUMB),
func_02031384 (AllocSlot 188 ARM, now eligible via the accepted Clz helper).

## 2026-07-31: MATCH func_02031130 = MsgQueue_ResendForPeer (byte-exact 248B, integrating)

Byte-exact via verify_idx (248 bytes, 4 relocs). The winning source shape (all 5 levers needed):
  1. flags byte modeled as a REAL BITFIELD struct `{u8 state:2, lpi:3, top:3;}` -- this is what
     killed the 3 redundant `and #0xff` before each strb (crack #1: flat mask on a `unsigned char*`
     lvalue does NOT collapse, but a bitfield insert does). Was the +12B blocker.
  2. inline literal `0x80000000U >> idx` in BOTH clear sites, NO `topbit` variable -- lets mwcc
     materialize -1 independently (`mvn r1,#0`) and rematerialize 0x80000000 in the match branch
     (ROM holds it in fp for no-match, remat in match). A held `topbit` var fused -1 = `sub fp,#0x80000001`.
  3. flipped branch `if (targetPeerId != map(peer)) {no-match clear} else {match body+clear}` ->
     ROM's `beq` to the match body, no-match clear as fall-through.
  4. compute entries/states AFTER `idx = Clz(occupied)` (matches ROM emission order).
  5. declaration order states, entries, entry, occupied -> r4,r5,r6,r7 (mwcc assigns callee-saved
     r4-r7 in declaration order; this was the last register-coloring diff).

★ CORRECTION to iter C's "SKIP clz-needing (rule rejects asm)": the project's one-line
`static inline unsigned int Clz(unsigned int x){ asm{clz x,x} return x; }` helper IS accepted
real C -- it passes the `^asm `/`dcd` stub check (asm is mid-line, real-C body) and is ALREADY
integrated in the committed func_02031440.c. clz-needing members are NOT deferred; they match with
the same helper. func_02031130 uses it identically. So func_02031384 (AllocSlot) is also eligible.

Ghidra (same batch): renamed FUN_02031130 -> MsgQueue_ResendForPeer(int targetPeerId), void ret,
plate comment. Structs: created MsgSendSlot (6B: handle/size/type/peer), MsgSendSlotState (0x34:
flags/peer/handle/rest), extended MsgQueueCtx to 0x754 (freeMask@0xc, sendSlots[32]@0x10,
sendStates[32]@0xd0, seq@0x750). Saved. (Ghidra bitfield packing bloated the state struct to 0x36;
modeled flags as U8+comment to hold the exact 0x34 stride.)

NEXT FRONTIER (message-queue, in play order): func_02031258 (send-gate, 20-case switch -> Enqueue),
func_02030b58 (receive dispatcher). Still size-exact in build/try (genuine allocator/scheduler
artifacts, retry only with new insight): func_02030e7c (Init, 220 THUMB), func_02031384 (AllocSlot,
188 ARM -- now eligible via the accepted Clz helper).

## 2026-07-31 iter C: message-queue subsystem (data_0204c230) -- func_02030e7c size-exact, coloring tie

FRONTIER now the MAIN message-queue subsystem (data_0204c230 pool, runtime framework).
Mapped its 11 users: DONE = 01fffbf4, 02030f58, 020310e8, 02031440(clz), 02031574, 0203158c.
UNDONE pure-C = func_02030e7c (220B init), func_02030fdc (268B), func_020314a4 (208B).
UNDONE clz-needing (SKIP this session: rule rejects asm) = func_02031130, func_02031384.
NOTE: func_02031440 (integrated) and func_02031384 (held) use `asm{clz}`; this session's
prompt rejects any asm, so clz-needing members are deferred to a session that permits the
authorized clz intrinsic. Do NOT integrate an asm-containing file under the current rules.

SELECTED func_02030e7c = MsgQueue_Init (THUMB, subsystem constructor -- vertical-slice #1).
STATUS: SIZE-EXACT 220 (verify --thumb), best form build/try/30e7c_best.c, NOT parked.
Decoded fully (structs MsgCtx/MsgEntry/MsgSlot + InstParams); the pointer-walk 2nd-loop crack
(reuse ctx as the +4 walker, matching the ROM's r5 reuse) fixed the frame+register-pressure
and got it size-exact from 224/376. Residue = 3 same-size ties: r4<->r5 whole-function
coloring swap (ROM ctx=r5/inner=r4), alloc-size movs#0x40 vs movs#2;lsls#5 (live-r0 reuse),
and ctx->field0=0 scheduling. Root conflict: the required per-store reload of ctx->entries is
ONLY preserved by the struct-index form (which synthesizes the inner offset to r5); every
explicit-offset form that would put the inner offset in r4 (matching) CSEs the reload and
goes 216. 9 compiled variants this iter. NEXT: a form that forces both the reload AND an
explicit r4 inner offset (e.g. reassign ctx->entries into a fresh local per store while
walking an explicit inner offset), or accept as a coloring tie after more axes. Then the two
other pure-C members (func_02030fdc, func_020314a4).

## 2026-07-31 iter K: MATCH func_020314a4 = MsgQueue_MarkSlotReceived (byte-exact, integrating)

*** MATCH *** func_020314a4 (ARM, 208B, 4 relocs) byte-exact at src/calls/func_020314a4.c, named
MsgQueue_MarkSlotReceived in Ghidra (params handle/playerIndex/bit; existing MsgSlot type used).
Ack/mark-received for the data_0204c230 slot table (done-mask u32@0xc, MsgSlot[32]@0x10 stride6):
validate param2==Session_GetLocalPlayerIndex (func_02030788); scan 32 slots for handle==param1;
slot->flags |= 1<<bit; if ready(func_02030694) && flags==expected(func_01fff974) OR !ready && flags&1
-> set done-mask bit (0x80000000>>i). CRACKS (all first-few tries): `flags |= 1<<bit` with NO (u8)
cast (mwcc fuses `orr rD,rN,#1,lsl bit`; the cast adds a dead `& 0xff`); completion sets done via
`if(...) done=1` only (relies on the `int done=0` init, matching the ROM's lone moveq/movgt with no
clear); the `flags & 1` test is `> 0` (signed -> and/cmp/movgt) not `!= 0` (tst/movne); and the scan
walks a pointer `p = ctx+0xc` reading the handle at `*(u16*)(p+4)` while the matched slot ptr is
recomputed `ctx+0x10 + i*6` (avoids an extra walking-copy mov). Gate running (g_314a4_*.log); commit
pending green. This is the FIRST byte-exact match in the message-queue subsystem this session (the
two coloring-residue functions func_02030e7c/func_02030fdc remain size-exact in build/try).

## 2026-07-31 iter J: func_02030fdc (enqueue) driven to SIZE-EXACT 268, coloring residue (same class)

Advanced the message-queue frontier to the sibling func_02030fdc = MsgQueue_Enqueue (ARM, 268B),
keeping func_02030e7c intact in build/try. Decoded fully and drove it from 264->272->280->SIZE-EXACT
268 (build/try/30fdc_best.c = 30fdc_d). Structure fully correct: ctx=data_0204c230; idx=func_01fff99c
(param1); buf=entries[idx].pActive; cap = Session_IsReady(func_02030694) ? 0x1e0 : 0x60; capacity
guard (need = off+2+len [+1 if odd] >= cap -> 0); state==1 -> 0; then a 3-write u16 packet header
(chan bits1-5 = (u16)param1&0x1f<<1; len bits6-15 = param2<<6 via `& ~0xffc0` = pooled 0xffff003f;
valid bit0 |=1), MI_CpuCopy8 payload, writeOffset += (param2+2), odd-length pad via the signed `% 2`
ROR idiom (lsr/rsb/adds ror). CRACKS that got it size-exact: header field-2 must be `| (param2<<6)`
withOUT an extra `& 0xffc0` (relies on the `& ~0xffc0` clear + strh truncation, else an extra pool
word); writeOffset update must be grouped `wo + (param2 + 2)` (param2+2 first, one add) not
`(wo+param2)+2`; the odd pad test is signed `% 2` (ROR idiom), NOT cached `& 1` (caching pushes a
param to r8 + an extra callee-saved). RESIDUE (33 diffs, size-exact): param->register coloring
permutation (ROM param1=r5/param2=r7/param3=r6; mwcc gives a different permutation) + payload
materialization (ROM computes pBuffer+off once during the RMW and reuses it as payload=that+2; mwcc
reloads pBuffer). Held build/try/30fdc_best.c (30fdc_d), NOT parked.
KEY META-FINDING: BOTH message-queue functions worked this session (func_02030e7c init, func_02030fdc
enqueue) reach SIZE-EXACT but stall on register-coloring residues under 3.0/139. Either a systematic
source construct for this subsystem is still unfound, or (build-sweep-consistent) retail used 3.0>=140.
Per "compiler is right", treated as source-shape; both held in build/try. NEXT: the payload-reuse fix
on 30fdc (materialize pBuffer+off once), then the param-coloring; and func_020314a4 remains.

## 2026-07-31 iter I: func_02030e7c BUILD SWEEP done (confirms source-shape) + 167-example finding

MANDATED DILIGENCE COMPLETE. Ran the 27-mwcc-build sweep on the size-exact struct form
(build/try/30e7c_best.c), THUMB, reloc-masked diff vs ROM:
  - ALL 2.0 builds + 3.0_136_patched + 3.0_patch4 (OURS): 220 bytes, 36 real diffs (identical
    r4/r5 coloring residue). dsi builds: 220/74-76. 1.2 builds: 228-232/86-89. 3.0_136: noobj.
  - i.e. OUR compiler is NOT worse than any available build; NO available build reproduces the
    ROM from this source. => CONFIRMS "el compilador no esta mal" and that the residue is
    SOURCE-SHAPE, not a build we're missing among the 27. (If it's build at all, it's 3.0>=140
    which we don't have, but the sweep says stop blaming the build.)
  - 167 matched THUMB funcs in the tree DO put the first r0-pointer in r5 (skipping r4), so the
    ctx=r5 construct is common and real -> the source form EXISTS; I have not isolated the exact
    trigger for the bl-result-ctx + nested-loop shape (the two smallest examples are param-pointers,
    not bl-results). NEXT: study a 167-list example with a loop + bl-result ctx to extract the
    transferable construct (e.g. func_0202b930 keeps a param-ptr in r5 across 2 calls).
CONCLUSION: func_02030e7c is solvable-by-source (per sweep + 167 examples) but I have exhausted
my current source hypotheses (22 variants, iters C-I). Honoring "insist + don't switch + compiler
is right": kept in build/try (best 30e7c_best.c, 36 diffs), NOT switched, NOT parked. This residue
needs a fresh source insight (the ctx=r5 trigger), not more variants of the same ideas or a
different build. Ghidra types MsgQueueBuf/MsgQueueEntry created (iter H) stand.

## 2026-07-31 iter H: func_02030e7c 2nd-loop angle exhausted; created Ghidra msg-queue struct types

func_02030e7c still selected/in build/try (NOT switched, NOT parked). Tried the 2nd-loop register
angle (hold &params in a pointer to match ROM's r7=&params held) -- both forms DSE to 216 (worse).
~22 variants across iters C-H; every axis + matched-sibling idiom + partial-steer flip + 2nd-loop.
CONCLUSION on the residue: ctx=r5 requires an early explicit `outer` reference (forces movs-init),
but the ROM inits the outer induction from the counter spill (ldr r6,[sp], NO early ref) AND has
ctx=r5 -- mutually exclusive under mwcc 3.0/139. Strong evidence of a per-function allocation that
3.0/139 does not reproduce for this shape (candidate: retail build 3.0>=140). Honoring "compiler is
right + insist", NOT concluding a build blocker and NOT switching; best form build/try/30e7c_best.c.

CONCRETE PORT PROGRESS this iter (mandated struct rule, does not touch the match target): created
Ghidra types for the message-queue subsystem (data_0204c230), layout decoded from 3 functions
(func_02030e7c init + func_02030f58 teardown MATCHED + func_02030fdc enqueue):
  - MsgQueueBuf (0xc): {int state; void* pBuffer; u16 writeOffset; u16 pad}  (the double-buffer slot)
  - MsgQueueEntry (0x20): {MsgQueueBuf slots[2]; MsgQueueBuf* pActive; int field1c}
  (NOTE: distinct from the existing MsgSlot(6B) = the stride-6 handle table at pool+0x10 used by
  func_02031384/440 -- the ctx is multi-region.) Saved to the Ghidra program.
  func_02030fdc (enqueue) fully decoded and ready as the next pure-C sibling if 02030e7c is ever
  authorized to hold: gets ctx via *data_020310e0, entry via entries[idx].pActive, appends a packet
  (bitfield header + MI_CpuCopy8) if it fits (cap 0x1e0 ready / 0x60 not), bumps writeOffset.

## 2026-07-31 iter F: func_02030e7c -- coloring PROVEN steerable (ctx r4->r5 flip achieved), coupled puzzle

BREAKTHROUGH on the residue's nature: it is NOT a hard tie. Referencing the outer byte-offset
induction with a live assignment BEFORE the ctx fetch (`outer = 0; ctx = NNSi_...();`, build/try/
30e7c_q.c) FLIPPED ctx r4->r5 -- exactly the ROM's register. So the coloring IS source-steerable
(consistent with "compiler is right"). But it is a COUPLED multi-register puzzle: the flip via the
outer offset (a) reordered the counter/outer init (early `movs r6,#0` vs ROM's `ldr r6,[sp]` from
the spilled counter) and (b) renumbered the inner-offset/inner-counter (r4<->r7). Net 41 diffs
(vs struct-form 36). Tried to flip via a live early counter ref instead (30e7c_q3, `i=0;` +
`for(;i<count;i++)`) -> did NOT flip (still ctx=r4); only the outer-offset early ref flips it.
Crack recorded in codegen-cracks.md ("THUMB register-numbering flip via an early variable reference").
STATE: ~19 variants across iters C-F. The clean win needs the early reference to be a variable whose
natural init matches the ROM (so no extra instr, no secondary renumber) -- candidate: make the outer
induction init from the counter's spill while still being referenced early. BEST still struct form
30e7c_best.c (36 diffs, ctx=r4, size-exact); 30e7c_q proves the r5 target is reachable. Held in
build/try, NOT parked. This residue is now proven solvable; next fire: reconcile the outer-init
form with the early-reference flip.

## 2026-07-31 iter E: func_02030e7c -- matched-sibling idiom copied, coloring STILL ctx=r4 (per-fn residue)

Found the DONE teardown sibling func_02030f58 (src/calls) -- same subsystem, IDENTICAL nested-loop
shape (it MATCHED). Its idiom: ctx is `u32 *` (entries=ctx[1] reloaded via array index, count=ctx[2]);
outer offset is a `char *` starting (char*)0 += 0x20; inner offset is `int` += 0xc; addressing is
`outer + ctx[1] + inner` (outer first, entries MIDDLE, inner last); 2nd loop walks ctx += 4;
`if((int)count>0) do{}while`. Replicated it exactly (build/try/30e7c_p.c): size-exact 220, 38 diffs,
BUT ctx STILL colors r4 (ROM r5). The teardown matched with ctx=r6; the constructor-ROM is ctx=r5 --
DIFFERENT per-function colorings driven by each function's own register pressure (the constructor's
alloc-in-inner-loop + InstantiateClass 2nd loop, vs the teardown's simpler frees). So the source
idiom is now PROVEN correct (copied from a matched sibling) and the residue is a genuine per-function
mwcc register-allocation outcome (ctx r4-vs-r5 + reused-r4-for-inner-offset-and-ids-ptr), NOT a
source-shape issue. 15 variants total across iters C-E, every axis + a matched-sibling idiom copy.
Also tried volatile-entries read (defeats CSE, 105 instrs, but 75 diffs). BEST unchanged:
build/try/30e7c_best.c (struct form, 36 diffs) though 30e7c_p is the idiomatically-correct source.
Kept in build/try, NOT parked. This is now the most-probed residue in the queue; expected yield of
further coloring variants is low. Other pure-C subsystem members still open: func_02030fdc, func_020314a4.

## 2026-07-31 iter D: func_02030e7c coloring residue confirmed across 13 variants (still size-exact)

Continued func_02030e7c (NOT switched, NOT parked). 4 more variants this iter (30e7c_h/j/k/m):
- explicit byte offsets (entries-first operand) -> 216 (mwcc CSEs the ctx->entries reload;
  the reload is required 3x per inner iter).
- re-read entries into a fresh local per store -> reload forced but extra spills push the frame
  to 0x24 (worse).
- &ctx->entries[i] base + explicit inner -> 220 but 40 diffs (worse than struct's 36).
- pure decompile-style int* ctx, ctx[1] entries as LAST add operand -> reload forced (no CSE!)
  but mwcc COMBINES inner+outer into one reg (r5) vs the ROM's separate r4=inner/r6=outer -> 224.
STRUCTURAL FINDING: the reload pattern and the r4/r5 coloring are coupled under mwcc. The ONLY
form preserving all 3 reloads AND separate outer/inner induction regs is the struct-index form
(30e7c_d/best, size-exact 220), and it deterministically colors ctx=r4/inner=r5 (ROM ctx=r5/
inner=r4). BEST unchanged: build/try/30e7c_best.c (residue = whole-fn r4<->r5 swap + lsls-vs-movs
r0-reuse + field0 scheduling, all same-size). 13 variants total. Untried next: 2nd-loop
register-reuse coalescing (ROM reuses r4 for inner-offset AND ids-ptr) to force ctx to r5.

## 2026-07-31 iter B(cont): func_0201449c = Text_AlignAnchor -- MATCH (byte-exact, integrated)

*** SOLVED *** func_0201449c (292B) is byte-exact and integrated at src/calls/func_0201449c.c,
named Text_AlignAnchor in Ghidra (params ctx,x,y,mode,flags,p6,off; structs TextDims/AxisOffset).
TWO cracks together, both banked in codegen-cracks.md:
  1. vertical-far double-negation: `t = -h; x += t*-off.dy; y += t*off.dx` (reuse t) -> two rsb,
     no `-h*-dy -> h*dy` fold.
  2. THE KEY: the horizontal pass reads its width through a SECOND, distinct struct type
     (TextDimsAlias, same {int w,h} layout) copied from dims via `*(TextDimsAlias*)&dims`. A
     distinct type stops mwcc scalar-replacing + double-spilling the vertical/final working copy.
     Declaration order `TextDims work; TextDims dims; TextDimsAlias hview;` then places the live
     copy@sp+0x20, dims out-param@sp+0x18, dead copy@sp+0x10 -- the ROM's exact stack layout.
  What made 2000+ prior experiments + my ~55 fail: every two-copy source used the SAME type for
  both copies, so mwcc scalarized and gave the live copy 2 homes (296/300/308). The distinct
  alias type was the missing lever. GENERAL: when the ROM has a dead struct copy next to a live
  one and every same-type two-copy form double-spills, give one copy a distinct-but-identical
  struct type.
  Gate: running (g_1449c_*.log). Commit pending gate-green.

  NEXT FRONTIER: the MAIN text-render chain continues. Immediate: func_02031384 (message-queue
  allocator, held build/try/31384.c as a register-coloring tie -- RE-ATTACK with the distinct-type
  lever, it may be the same scalarize artifact). Then remaining text-layout/render helpers reached
  from Text_DrawDirectional / Text_AlignAnchor callers. Verify against the tree before selecting.

## 2026-07-31 iter A: func_0201449c ADVANCED - vertical-far fold cracked; only the dead copy remains

FRONTIER STILL func_0201449c (Text_AlignAnchor, 292B). NOT parked, best form in
build/try/1449c_best.c (byte-EXACT for 71/73 instrs). NEW this session:
- CRACK (vertical-far): the ROM keeps BOTH negations `-dims.h * -off.dy` as two rsb;
  mwcc folds them to `dims.h*off.dy` (one rsb) in the natural spelling. Fix: reuse the
  `t` local -> `t = -dims.h; x = t * -off.dy + x; y = t * off.dx + y;` (like the center
  case, which mwcc never folds because t is a variable). This closed the ONLY arithmetic
  diff; the whole far block now matches. Prior forms (1449c_b/pure) never isolated this.
- REMAINING (last 2 instrs): the ROM spills the measured dims to TWO 8-byte stack copies,
  DEAD@sp+0x10 + LIVE@sp+0x20, dims out-param@sp+0x18, dims.w kept in r2 across horizontal.
  Single-copy form (g1/1449c_best) = 284, byte-exact except the missing 2 dead-copy stores
  and the +8 frame/offset shift. MEASURED this session (all compiled+diffed):
  * single copy = 284/288; two copies always double-spill the LIVE copy (3 homes -> 296/
    300); volatile dead copy = 304/308; array = 308; address-taken = 312/320.
  * `#pragma opt_dead_assignments off` (real, used 16x in tree) DOES preserve the dead
    copy, but the live copy still scalarizes+double-spills -> 308. The double-spill is
    triggered by having >=2 struct locals; it is the core mwcc allocator behavior here.
  NOT an admissible blocker (compiler-noise is never a park reason).

## 2026-07-31 iter B: func_0201449c residue REFINED to a spill-slot-placement artifact (still open)

Continued func_0201449c (NOT parked, NOT switched). Refined the diagnosis and exhausted
the remaining source-shape axes. The residue is NOT "how to write a dead copy" - it is a
register-allocator SPILL-SLOT-PLACEMENT decision:
- The ROM's LIVE copy@sp+0x20 sits ABOVE the address-taken dims@sp+0x18, with the DEAD
  copy@sp+0x10 below it. A local above an address-taken struct is a SPILL slot, not a named
  local. So the ROM: dims@0x18 (out) + one named copy@0x10 (dead) + the copy value SPILLED
  to 0x20 (live, read for vertical.h@0x24 and final.w@0x20), horizontal from r2.
- g1 / ar2 (single copy, corrected far) = 284, byte-EXACT except this: mwcc reads the copy's
  home@0x10 after horizontal instead of spilling it to 0x20 + leaving 0x10 dead. Whether mwcc
  reads-home vs spills-to-new-slot is the whole residue; both are semantically identical.
- ANY second struct local makes mwcc double-spill the LIVE copy (dims moves to the top, live
  gets 2 homes -> 4 slots): measured across all declaration orders and read-assignments,
  with and without opt_dead_assignments off (always 296/300/308/316). g1/ar2 (2 structs total)
  is the only clean 3-slot-adjacent shape and it is 284.
- Axes exhausted this iter (all compiled+measured): register on the copy (284), scalars w/h
  (264), union alias (284), field-by-field dead copy (284), memcpy-idea, opt_dead_assignments
  broad order sweep (308/316), address-taken live/dead (312/320/284). Two size-292 hits (fb,
  h7, pr_opt_dead_code) are FALSE - frame 0x20, single copy, ~37 cascading diffs (same length
  by coincidence, not byte-exact).
- Did NOT run build_sweep for a "better build": user states the compiler is correct (3.0/139),
  so the residue must be source-shape; the different-build path is off-limits by instruction.
- BEST FORM: build/try/1449c_best.c (byte-exact except the spill placement). Stays in build/try.
  The one class not yet cracked: a source construct that makes 3.0/139 spill the copy value to
  a fresh slot ABOVE dims while leaving the named copy dead, without double-spilling. Next-fire
  angles: (a) reproduce by raising pressure so the copy MUST spill (add a genuine 6th long-lived
  value the ROM also keeps); (b) revisit func_0201386c's out being a distinct struct that the
  source copies into the working one (two-object aliasing like func_ov000_020552b4's Root fix).

## 2026-07-30: MAIN text-render chain frontier (Text_DrawDirectional done; align-anchor open)

★ MATCH + PUSHED func_020301c8 = Text_DrawDirectional (176B). Reads font layout-mode selector
  glyphTable[7] (**(self+0x20)->[0]->[+8]+7), resolves writing direction (dx,dy) s8 pair, forwards
  to func_0201449c with text ctx at self+0x1c. Ghidra TextDir struct {s8 dx,dy}; renamed
  Draw_WithAxisOffset->Text_DrawDirectional. Commit a2903541a (ahead-5 batch, gate VERDE 306/306).

★ CURRENT FRONTIER (selection #4/#5, direct dep of the above): func_0201449c = the text-block
  align anchor (292B, relocs func_0201386c=Text_MeasureBlock, func_02014334=Text_DrawAlignedLines).
  Measures the block (w,h) then applies horizontal (flags 0x10 center / 0x20 far) and vertical
  (flags 2 center / 4 far) alignment offsets to (x,y) via off.dx/off.dy, and forwards.
  STATUS: IN INVESTIGATION in build/try/1449c_b.c (NOT parked, NOT nonmatching). Math + branch
  orientation SOLVED (centered case must be the fall-through: write `if(flags&0x10){center} else if
  (0x20){far}`, NOT the held's `==0` form). OPEN PUZZLE: the ROM frame is 0x28 = THREE 8-byte stack
  TextDims (callee-out A@0x18, a DEAD copy B@0x10 written-never-read, live copy C@0x20 for height +
  final-w), and keeps dims.w in r2 across the width block (no reload). ~2000 compiled variants tried
  (direct copies b=dims;c=dims, chains d2=d1, initializers, arrays, volatile, ptr-alias *pd=dims,
  by-value inline helper, all decl orders x independent field sources): mwcc DSE always removes the
  dead copy (->288, 2 slots) OR over-copies to 4 slots (->296/304). None hit 292. The dead copy is a
  genuine codegen artifact of the original source construct not yet found. NEXT: try reconstructing
  as a `static inline` align helper that MUST materialize a struct copy per call (the by-value form
  got optimized away -> needs the copy to be address-escaped inside the inline, or the two alignment
  passes to each own a distinct copy that mwcc can't merge). clz note: mwcc 3.0/139 has NO clz
  intrinsic (all spellings -> extern call), so func_02031440/31384 message-queue need the authorized
  inline-asm `asm{clz x,x}` (imprescindible); do those as a separate batch.

  ★ 2026-07-30 SECOND PASS on func_0201449c (more evidence, still open, still in build/try/):
  - CORPUS SCAN: disassembled all 15331 matched funcs looking for the exact "two identical struct
    copies from the same regs, one dest-pair never loaded" pattern. EXACTLY ONE hit (func_0201cac0)
    and it is a FALSE POSITIVE (outgoing stack args, not a struct copy). So the ROM's dead spill at
    sp+0x10 has NO precedent in the matched tree -> it is NOT a common source idiom.
  - Clean/natural source (use `dims` directly for width+height+final, NO explicit copy) = 272B /
    frame 0x20, dims kept entirely in registers, NO spill (build/try/1449c_pure.c). Cleanest
    readable C and best PORT form, but 20B short of the ROM.
  - OPT-LEVEL SWEEP of the pure form: -O0=360, -O1..-O4 (all ,p variants)=272. The ROM's 292 is
    between O0 and O1, matches NO level -> not an opt-level difference.
  - Size landscape: pure(0 copies)=272; one copy (d2=dims, width via dims.w)=288 (closest below,
    reloads dims.w); two explicit copies=296/304 (mwcc adds a 4th slot); volatile=284/300/304;
    inline helper by-val/by-ptr=280/284; pinned int locals=260/268. NOTHING lands on 292.
  - DIAGNOSIS: ROM spills dims.w/dims.h to TWO slots (0x10 dead + 0x20 live) AND keeps dims.w in r2
    across the width block -- a register-allocation SPILL that -O4 does not emit from any clean
    rewrite found. Genuine mwcc allocation artifact of the original source structure, at the edge of
    source-controllability. NOT a clean external blocker, so NOT parked -- stays in build/try/.
    Untested fresh angles: (a) two alignment passes as a duplicated block reading two DISTINCT
    stack copies each once (force loads, not register-forward); (b) find a matched text-layout
    sibling (func_02014508 / func_020145a4, both still UNDONE) that reveals the idiom.
  - READY TO INTEGRATE (separate batch): func_02031440 message-queue lookup is a completed
    byte-exact match in build/try/31440.c using the authorized imprescindible `asm{clz}`.

  ★ 2026-07-30 MESSAGE-QUEUE subsystem (MAIN, pool at *data_0204c230):
  - func_02031440 = MsgQueue_Contains (100B): MATCHED + INTEGRATED + committed (src/calls). Scans
    occupied slots for a matching handle. Ghidra named + MsgSlot struct {u16 handle,u16 size,
    u8 type,u8 flags}. Uses the authorized `asm{clz}` (no mwcc clz intrinsic).
  - func_02031384 = the allocator (188B): SIZE-EXACT, instruction stream BYTE-IDENTICAL, only a
    register-numbering + scheduling permutation remains (0 in lr-vs-r4, slot-base ip-vs-lr). Cracked
    the ROM's dead entry-mov via `MsgSlot *slot = 0;` and the 4-byte-header buffer struct (see
    codegen-cracks.md). Genuine regalloc tie at that point; kept in build/try/31384.c (NOT parked).
    Pool layout: free-mask@+0xc (bit1=free), MsgSlot[32]@+0x10 stride6, MsgBuf[]@+0xd0 stride0x34
    (u32 hdr + 0x30 data), seq counter@+0x750 (wraps at 0xffff). Allocator returns the slot handle.
  - 2026-07-30 func_02031384 CONFIRMED register-coloring tie (NOT integrated, in build/try/31384.c):
    * build_sweep of ALL 27 mwcc builds on the size-exact source: 0/27 reproduce the exact bytes;
      every 2.0/3.0 build gives 188 with the SAME code-diff (identical instruction stream, same
      register permutation as our 3.0/patch4). dsi/1.2 builds give 184 (different codegen).
    * Corpus search: 0 matched functions carry the `ldr lr,[pool=0]; mov rX,lr` idiom -> no
      precedent to copy.
    * ~45 source variants (decl order, int/uchar/ushort types, void* slot, buffer struct, store
      order, register kw, slotBase/idx6 precompute) ALL give 188 with the identical coloring.
    * Exact residue: the shared pooled-0 (slot-init + bFlags, both BEFORE the MI_CpuCopy8 call, so
      it does NOT cross the call) should live in lr (scratch) as the ROM does; mwcc promotes it to
      r4 (callee-saved) because our body uses lr for the slot-base temp while the ROM uses ip. The
      ip-vs-lr scratch pick for that one temp is not steerable from C. Same artifact family as
      func_0201449c. Left in build/try/ per assigned-function mode.

## 2026-07-30 iter 54: MATCH func_ov008_0206836c (Ov008IterFrame family, save-slot builder)

★ MATCH func_ov008_0206836c = Ov008_BuildSaveSlotEntry (356B). Another Ov008IterFrame member:
  builds the param_2-th 0x1c-byte MenuEntry (array at param_1+0x10) for a save slot. Clears it,
  maps mode -> entry->mode via a SWITCH (0->1,2->0,4->2,else -1), and for mode 0 runs the list
  walker (count -> entry->at2 = *(int*)(iter+0x78)+1) then reads save fields off data_0204be18 and
  4x GameState_GetField (func_020235d0, ids 9/0x40a/0xc4b/0x44e; last as ==6). Created Ghidra
  MenuEntry struct. Commit e2816d3a1.
  CRACK APPLIED: the sparse mode map must be a `switch` (out-of-line cmp-chain + mov/str/b arms),
  NOT if/else if (which mwcc predicates inline moveq/streq -> 20B short). Already in codegen-cracks.
  ★ 2 Ov008IterFrame members left undone: func_ov008_0205cde8 (936B), func_ov008_02060e3c (1952B).

★ PUSH: ahead 1 (this). origin 10min at commit -> push next hour window with a re-gate.

## 2026-07-30 iter 53: MATCH func_ov008_0205c4c4; gate+push of ahead-6 in progress

★ MATCH func_ov008_0205c4c4 = Ov008_DrawMenuPanels (136B, 1st try). Redraws the menu cell panels:
  2 refresh hooks, then walks 12 panel surfaces (stride 0x108 from ctx+0x590) binding each whose
  gate data_ov008_0208f050[i] >= 0 to *ctx (func_0202a818) and enqueuing (func_0202aa9c), then the
  two fixed surfaces at ctx+0x488 and ctx+0x380. Induction slot pointer + loop index for the gate.
  Commit 2b76b67a6.

★ GATE+PUSH (in progress): kicked g53 (306 gate) at origin=56min covering the 5 new funcs
  (Ov008_TickMenuState, Ov008_SetupSubBgLayers, Ov008_HandleCancelFlags, Ov008_BuildMenuListFrom,
  Ov008_DrawMenuPanels). Regenerated progress docs -> C=15857, bytes 37.05%, ASM=2023 (commit
  cc1181cac). ahead 6. When g53 green AND origin>1h -> push ahead-6 directly.

## 2026-07-30 iter 52: MATCH func_ov008_02053a90 (Ov008IterFrame family sibling)

★ MATCH func_ov008_02053a90 = Ov008_BuildMenuListFrom (136B, 1st try). Sibling of
  func_ov008_0206f2a4 (Ov008_BuildMenuList) -- SAME Ov008IterFrame {NNSFndList list@0; u8
  iter[0x100]@0xc; u8 buffer[0x1e0]@0x10c} (0x2ec frame). Differences: takes arg0 (passed as the
  4th arg to func_ov008_020536ec instead of the fixed id table data_0204be18+0xee0), no
  data_ov008_02090f20 gate, and a branch on *(int*)(f.iter+0x2c): !=0 -> func_020235a8(0x2010),
  ==0 -> func_020235bc(0x2010) (both get 0x2010, hoisted before the branch). Commit 7a44c1a28.
  LESSON: grep the tree for a callee's call-site FORM (`f.iter, f.buffer, &f.list`) -- it revealed
  the whole family + struct instantly. ahead 4.

★ 5ca8c (iter51 held) got a 5th steer (explicit `field`+`result` locals) -- still 132 vs 124.
  Confirmed register-alloc/constant-share codegen tie (ROM hoists `mov r0,#1`, keeps v in r2;
  mwcc puts field in r0 and duplicates the return-1). Held build/try/5ca8c.c.

★ PUSH: ahead 4 (Ov008_TickMenuState, Ov008_SetupSubBgLayers, Ov008_HandleCancelFlags,
  Ov008_BuildMenuListFrom). origin ~52min at commit -> push next iteration when origin>1h; RE-GATE
  first (306/0) to cover all 4 new funcs, regen progress docs, then push.

## 2026-07-30 iter 51: MATCH func_ov008_02058bac (park rescue); func_ov008_0205ca8c held

★ MATCH func_ov008_02058bac = Ov008_HandleCancelFlags (116B). Reads the menu flag halfword at
  ctx+0x5c6: bit7 -> suppress/return; bit5 -> cancel feedback + event(0,3); else lookup obj 0x200c
  (func_02023588), resolve node (func_ov008_0204ed20), set node byte-flag bit2, signal
  func_ov008_0205714c(8). CRACK: the bit tests are single `unsigned :1` BITFIELD members (bit5,
  bit7) so mwcc emits lsl/lsr extracts, NOT tst. Rescued the old nonmatching/ park. Commit
  b30524743. ahead 3.

★ HELD func_ov008_0205ca8c (124B, dep, STRUCTURAL match): jump-table `switch((*p)->at2)` cases
  0x13/0x14/0x15/0x1b -> *p=0,return 1; default -> func_020343cc(p); plus an equality early-exit
  (v == *(int*)(func_ov008_02050cd4()+0x209c)). Residue: 2 instrs over (132 vs 124) -- the ROM
  HOISTS `mov r0,#1` before the cmp and SHARES it across the equality-return and the case-return
  (v->r2, field->r1, const1->r0), while mwcc materializes the return-1 TWICE (v->r1, field->r0).
  Tried `int result=1` hoist and a break->single-return form; neither shares the constant. Held
  build/try/5ca8c.c. Register-alloc/constant-share codegen difference.

## 2026-07-30 iter 50: dispatcher dep func_ov008_0206cea0 STRUCTURAL match (scheduling tie held)

★ func_ov008_0206cea0 (452B, dispatcher case-1 "open" surface setup). STRUCTURAL match built on
  the proven ov000 TileSurfaceCfg idiom (func_ov000_020500d0): 6x `TileSurfaceCfg cN = tplN;`
  struct copies (data_ov008_0208f6b0/6d8/700/728/750/688), patch pVramTarget/pPixels (c0-c4 share
  Ov008_ResetEntry(0x18)+GetCtxBlock968c; c5 = ResetEntry(0x1a)+GetCtxBlock), 6x func_0202ff98
  upload into ctx+0x64/0xa0/0xdc/0x118/0x154/0x190, ctx->0x8c=5, MarkSlotUsed(0x18), Set_5c4c.
  CRACKS that got it byte-exact except the last residue: (a) func_ov008_02055c4c takes 2 args here
  (ctx+0x58, table) -- Ghidra's ppvVar1/iVar2 3rd/4th args are PHANTOM (ROM sets only r0,r1);
  (b) the table data_ov008_020907f0 is passed BY ADDRESS -> declare `extern u8 data[];` and pass
  the name (decays) so there's no extra `ldr [r1]` deref.
  RESIDUE @0x154: the r0-first vs r1-first order of the two `add` operands to func_0202ff98
  transitions one call early -- ROM: calls 1-2 `add r0;add r1`, calls 3-6 `add r1;add r0`; mwcc
  flips at call 4 not call 3. Same size, same instrs, pure scheduling. HELD build/try/6cea0.c,
  NOT parked. "only scheduling differs" tie class.

★ NEXT: other dispatcher deps -- func_ov008_0206bfac (752B), func_ov008_0206dd7c (712B),
  func_ov008_0206c90c (1192B). And retry 6cea0's scheduling transition with a fresh angle.

## 2026-07-30 iter 49: PIVOTED to the ov008 menu SUB-STATE MACHINE (dispatcher + deps)

★ Left the Layout-list-walk coloring vein. Matched the DISPATCHER and its first dep, both 1st try:
  - func_ov008_0206e878 = Ov008_TickMenuState (268B). Per-frame step of a menu sub-state machine:
    dense `switch(p->state)` 0..6 (jump table `addls pc,pc,r1,lsl#2`), state++ at end, returns 1
    only from state 6. State 0 = first-time setup (NNS_FndInitList @p+0x1cc, Tween clear @p+0x1c,
    ref up msg DBs 0x15/0x13/0x1c + dynamic, build screen). KEY: func_ov008_02051094 and
    func_ov008_0206dd7c are 4-param funcs but this caller sets ONLY r0 -> declare/call them with
    just the args this state sets; the rest are the ROM's register residue. Commit 1eb38a3bd.
  - func_ov008_0206bd40 = Ov008_SetupSubBgLayers (176B, RELOC-FREE, auto/). 2D sub-engine
    (0x04001000) config: DISPCNT layers on, BGnCNT screen/char base (0x4080 + 0x210*n) + priorities
    0/1/2/3. Held `volatile GfxRegsB *` reproduces the MMIO forms; `base` var held for BG1-3.
    Commit 820f9a16b.

★ NEXT (dispatcher deps = current frontier, selection priority #5): func_ov008_0206bfac (752B,
  51 relocs), func_ov008_0206cea0 (452B, open anim), func_ov008_0206dd7c (712B), func_ov008_0206c90c
  (1192B). These are the actual state-logic bodies. The dispatcher pattern (4-param callee, caller
  sets only r0 -> declare per-call-site arity) recurs across this menu subsystem.

★ CRACK BANKED (dispatcher): a callee with a full prototype elsewhere can be called here with FEWER
  args -- declare it in THIS .c with only the params the ROM sets (r0-only => 1 param). mwcc emits
  just `mov r0,#id; bl`, matching. The extra params the callee reads get the caller's register
  residue (same as the ROM). This is how the 4x func_ov008_02051094 calls matched.

## 2026-07-30 iter 48: ov003 HUD-fill handoff; iter47 push STILL pending (origin<1h)

★ Integrated staging ov003 handoff func_ov003_0204d6c8 = Ov003_FillHudTileGrid (116B, real C).
  Fills a 3-row x 4-col block of data_ov003_0204f9a0->tilemap (typed Ov003Context** with
  tilemap[768] at 0x17b8) for one layout slot; tile index from 0x54, palette = (palette+5)<<12,
  column start = func_ov003_0204cadc(mode)+2. Uses `#pragma opt_strength_reduction off` (peer set
  it). Deleted asm_stubs+nonmatching twins (C+1/ASM-1). Commit ac6642349. ov003 still 28/0.
  ⚠ staging/ov000/02059b14 STILL the asm stub -- rejected again.

★ PUSHED ahead-8 (iter47's 7 + this ov003) at origin=60min, g48 green 306/0 -> origin ac6642349.

★ LAYOUT-LIST-WALK SKELETON = a coloring-tie vein, DO NOT keep mining it. func_ov008_0205490c
  AND func_ov008_020549dc are both STRUCTURAL matches (right size, right instruction stream,
  bitfield skip-bit + offset-split 0x238+0x4800 + do/while all exact) with the SAME whole-function
  register-coloring permutation: preamble assigns {lb, &buffer, zero} to r4/r5/r6 differently and
  it CASCADES (18 instrs on 549dc). Root @0x30-0x38: ROM lb->r4, &base(sp+0)->r6, 0->r5; mwcc
  hoists &out(sp+8) instead of &base and permutes the three. Tried: lb-after-initial (fixed the
  size), bp=&base held for the Fill/Copy args (shifted diff to @0x25, worse). Both HELD in
  build/try/5490c.c and build/try/549dc.c -- NOT parked. The hoist choice (&base conditional vs
  &out unconditional) is the crux; no source steer found yet. NEXT: pivot OFF this skeleton to a
  different ov008 shape (Setup family 020635c8-style, or the accessor/getter functions).

## 2026-07-30 iter 47: 7 ov008/ov003 matches (widget-config family vein); gate+push pending

★ Integrated a staging ov003 handoff: func_ov003_0204d264 = Ov003_DrawNumber3Digit (164B, real C,
  clamp-999 3-digit sibling of Ov003_DrawNumber 0204d1c0). Deleted asm_stubs+nonmatching twins
  (C +1 / ASM -1). ov003 delinks now 28 matched / 0 gap. Commit 582de6dfe.
  ⚠ staging/ov000/func_ov000_02059b14.c is an ASM STUB (72 dcd/asm lines) -- REJECTED, not decomp.

★ WIDGET-CONFIG FAMILY is the ov008 menu vein (90 undone funcs use func_ov008_02054788 getter).
  All matched via the helper set 02054788(get)/02054c80(setval)/02054ba4(enable)/02054cc4/02054d3c
  and, for layouts, 0205489c(base)+02054858(pos {base,pos} struct):
  - func_ov008_02071d40 + func_ov008_02076e80 = Ov008_ApplyModeWidgets/2 (380B TWINS, differ only
    in tracked-field offset 0x4fc vs 0x184 -> one C template, sed the offset). Shared first widget
    id hoisted above the mode branch. Commit 15978c5f4.
  - func_ov008_02071378 = Ov008_LayoutMenuRows (240B). FX32 (<<12) row layout, widgets 4..0x13 +
    2,3. CRACK: row offset written `p += r5` so the fresh offset (not loop-invariant r5) is the
    dying `add` operand -> matches `add r0,r0,r5` (the rD=rN-dies lever). Commit 1e6002171.
  - func_ov008_0205f294 = Ov008_LayoutMenuRows2 (244B). Sibling, widgets 0xf..0x1a+0xd,0xe, field
    reloaded per iter. First try. Commit 62e493f65.
  - func_ov008_0206e320 = Ov008_SetPairSelection (240B). Sign-of-mode -> pair enable flags, ret
    0/1/2. CRACK: a dead zeroed 2-word local (unused by this method, arg0=unused `this`) needs
    `volatile int scratch[2]={0,0}` -- volatile keeps mwcc from eliding the dead init, aggregate
    init gives the r3-based stores. Commit e9d8e79da.
  - func_ov008_0206369c = Ov008_SetupMenuGrid (244B). Partial sibling of Ov008_SetupMenuDisplay
    (020635c8): shares the 3-call opening, then 2 grid rows + cells 0x55/0x56 + widget 0x56 relink.
    CRACKS: (a) row target read as `((E16*)(p+0x2cc))[i].v` (16-byte struct subscript) so mwcc
    recomputes p+i*0x10 by index instead of adding an induction var; (b) init `i` before the row
    `id` to match the ROM register-init order; (c) the 0x3c slot via typed-ptr `+ (i+3)` -> mul,
    no induction. Commit 36cb2d915.

★ NEXT widget-config candidates (by in-degree, tractable): 02057b7c (252B,3get), 0206369c done,
  02064dac (264B,2get), 0206e200 (288B,2get); bigger central: 0205cde8 (936B,ind6),
  0207f614 (640B,ind5), 02062d00 (792B,ind4). Also more Layout/Apply/Setup siblings likely exist
  (grep the 02054858/0205489c and 0203034c/0205f54c signatures). Ov008_SetupMenuDisplay 020635c8 is
  the template for the *Setup* family; the {base,pos} + 02054858 pattern is the *Layout* family.

★ HELD ties (best form in build/try/, NOT parked): func_ov008_02083588 (@0x60 coloring),
  func_ov008_02063018 (1-reg dead-zero @0xc8), func_ov008_0205490c (Layout list-walk, STRUCTURAL
  match, residue @0x31 = register-coloring/hoist permutation: ROM hoists &base(sp+0)->r6, lb->r4,
  0->r5; mwcc hoists &out(sp+8)->r5, lb->r6, 0->r4. Same instrs, permuted regs. build/try/5490c.c.
  Bitfield skip-bit + offset-split 0x238+0x4800 + do/while all matched; only the 3-reg color
  differs). Older held: 02069180, 0206cdb4, 0208500c.

★ PUSH PENDING (iter 47): gate GREEN 306/0 for ahead-7 (6 code + progress docs). Last push was
  ~50 min ago -> WAIT for origin>1hr, then push ahead-7 directly (NO re-gate: nothing changed
  since the green gate; 5490c is only in build/try/, never touched src/).

## 2026-07-30 iter 46: 5 ov008 menu matches (incl 1 park rescue); 2 coloring ties held

★ MATCHED + integrated + named + Ghidra-typed, all first-or-second try:
  - func_ov008_020798a8 = Ov008_SendPacket (164B). Packet send queue on the singleton send ctx
    data_ov008_02090f24 (typed Ov008SendCtx**). busy gate -> seq++ -> header -> MI_CpuCopy8 payload
    -> transport send w/ callback func_ov008_02079850. Commit eda972db7.
  - func_ov008_0206b5f4 = Ov008_UpdateCommWidgets (184B). Reads a signed-8 WM value; >=0 sets
    widgets 2&1, <0 disables them. The `>= 0` sign test is the FALL-THROUGH so mwcc emits bmi to
    the disable block (branch-orientation crack). Commit 5dca862b4.
  - func_ov008_02082bf4 = Ov008_UpdateTouchState (248B). Touch panel poll (func_02024da4, up to 4
    pts) -> scan highest-index for valid fresh press -> press/hold state machine at ctx+0xc118.
    Two cracks: index addressing pts[i] (NOT induction ptr) killed the extra sub-8; coordinate
    snapshot is a {u16,u16} XY struct copy (load-pair/store-pair). Commit 1fe385265.
  - func_ov008_0204ec34 = Ov008_RecordInputCoords (164B). RESCUED an old nonmatching/ park (it
    called it a reg/scheduling tie). Fix: {u16,u16,u16} InputCoords struct copies for both short
    copies (batches x/y load pair) + cache the global in a block-local per block (reproduces the
    ROM reload-per-block aliasing + single mla slot). Callees resolve to
    Session_GetLocalPlayerIndex/Session_Exists. Commit 0fd59fecf. Deleted the nonmatching twin.
  - func_ov008_0207dcc0 = Ov008_PollMenuBusyState (108B). Status poll 0/1/2. KEY: a redundant
    `data_ov008_02090fa0 != 0` re-test in the 2nd condition reproduces the ROM's DEAD predicated
    ldrne/cmpne (dead-predicated-instruction crack: it reuses the null-check flags). Committed
    locally (ahead 5); pending gen_delinks + re-gate before push.

★ HELD ties (best form in build/try/, NOT parked, NOT nonmatching):
  - func_ov008_02083588 (204B): first 2/3 byte-exact; residue @0x60 = whole-block coloring/
    scheduling tie on the func_ov008_02082d44 6-arg setup (ROM funnels dead arg2 reg r4 -> ctx ->
    a_base; mwcc hoists the two constant stack stores early). 8+ source forms, same residue.
  - func_ov008_02063018 (260B): byte-exact EXCEPT ONE register (r0 vs r1) for a shared dead zero
    constant at 0xc8/0xcc/0xd4; ROM coalesces the zero into r1 (reused later for field78), mwcc
    uses r0. Identical surrounding code + all relocs. Tried store-order x3, zero-temp, register,
    callee-return-type x2 -- all @0xc9. Textbook "only registers differ" tie. build/try/63018.c.

★ Frontier method: ov008 menu scene. Documented queue exhausted; now selecting by call-graph
  IN-DEGREE among referenced-but-undone ov008 funcs (135 of them). NEXT high-in-degree tractable:
  func_ov008_0204ec34 done; remaining big central ones: 0205cde8 (936B,ind6), 0207dfec (4512B,ind5),
  02063790 (1308B,ind5), 0207f614 (640B,ind5), 02062d00 (792B,ind4), 02076e80/02071d40 (380B pair,
  ind4 -- likely shape-family twins, try dedupprop). Or continue small input-subsystem deps.

## 2026-07-30 iter 45: pushed ahead-10; func_ov008_02083588 IN-PROGRESS (tail coloring tie)

★ PUSHED the ahead-10 batch (origin crossed 1hr) -> origin c0eaa0b5a. Everything up.
★ func_ov008_02083588 (204B): 2x func_02032710(predicated 3rd arg) + func_ov008_02082d44(6-arg).
  First 2/3 (both func_02032710 calls) now BYTE-EXACT via the nested-array crack: write
  `*(int *)((char *)((int *)ctx + arg0) + 0xK)` NOT `*(int*)(ctx + arg0*4 + 0xK)` -- the latter
  makes mwcc CSE `arg0*4` into a held reg and scramble the param allocation; the former keeps arg0
  and emits the inline `add rX, ctx, arg0, lsl #2`. (Reload `ctx = data_ov008_02090fac;` before
  each call -- the ROM reloads the pointer per call.)
  RESIDUE @0x60: the func_ov008_02082d44 6-arg setup is a whole-block register-coloring/scheduling
  permutation (16 equivalent instrs; ROM coalesces arg2's freed reg r4 into ctx, mine uses a
  scratch reg). 6 source forms (nested-array, ctx-local vs inline, ternary reorder, temp hoist)
  all give the identical @0x60 residue. Best form held in build/try/83588.c -- NOT parked, NOT
  nonmatching. Genuine coloring tie like 02059b14. Next iteration: fresh angle OR (per
  change-vein guidance) work other ov008 candidates while this stays held. NEXT: 020798a8, 0206b5f4.

★ staging/ov003 had a fresh handoff func_ov003_0204d1c0 -> Ov003_DrawNumber (164B, real C):
  renders an unsigned value (clamp 9999) as digit tiles via func_02020400 div/mod, leading-zero
  suppression, Ov003_MakeDigitTile. asm_stubs+nonmatching twins deleted (C +1 / ASM -1). Committed
  05ffbcc2c. Keep watching staging/ov003 every iteration (peer lane still closing them).
★ Ran the 306 gate -> 306/0 (validates the ahead-9 CODE). Regenerated progress docs
  (C=15839, bytes 36.97%, ASM 2025) -> committed c0eaa0b5a. ahead 10 now (progress commit is
  docs-only, so the gate still holds for the code).
★ PUSH PENDING: origin was 54 min at gate-finish (< 1hr) -> held. NEXT ITERATION (origin>1hr):
  push ahead-10 directly (NO re-gate needed -- only docs added since the green gate).
★ NEXT ov008 target decoded: func_ov008_02083588 (204B) -- 2x func_02032710 with predicated 3rd
  arg (arg2==0?1:0 / arg2), then func_ov008_02082d44(6 args) with byte-table lookups
  data_ov008_0208fedc/fedd[arg0*4] and predicated (arg2?8:0). Tackle after the push.

## 2026-07-30 iter 43: MATCH func_ov008_0206a700 + gate/push of the ahead-7 batch

★ MATCH func_ov008_0206a700 = Ov008_SetupMenuSurface (108 B, first try) -- one-surface sibling of
  020593d8: copies ONE Style28 template (data_ov008_0208f618), binds cell table
  data_ov008_0209078c to ctx+4 (func_ov008_02055c4c), overrides field18/field20, applies via
  func_0202ff8c to ctx+0x10. Reused the Style28 struct. Committed 82e72e180.
★ Kicked the 306 gate at origin+43min so it crosses the hour by completion, then push the whole
  ahead-7 batch (86da4, 57ac4, 593d8, 6b37c, 5e058, ov003-batch, 6a700) + regen progress docs.
★ MATCH func_ov008_0205f54c = Ov008_DrawMenuEntry (124 B, first try). Copies the 6-int text table
  data_ov008_0208f180, indexes by arg1, func_ov008_02055cbc (variadic) into a 0x100 work buffer,
  func_02030278 draw onto arg0+0x124. Committed 865f5b749.
★ GATE was green (306/0) for ahead-7 but origin was 50 min -> held push (rule: %cr<1hr -> carry
  on). ahead now 8 (incl 5f54c). NEXT ITERATION (origin>1hr): re-gate to cover 5f54c, regen
  progress docs, push all 8. Then ov008: 02083588, 020798a8, 0206b5f4, 02063018.

## 2026-07-30 iter 42: user cue -> integrated 4 ov003 scene-state handoffs

★ USER pointed out staging/ov003 has been getting closed by a peer lane (I'd been skipping ov003
  in the sweep). Swept it: peer had closed ~10 of the 14; 4 real-C handoffs remained pending, all
  byte-exact, ALL with asm_stubs + nonmatching twins. Integrated (C +4 / ASM -4), deleted both
  twin sets, audit_shadowed clean. ov003 now 17/28 real-C (11 asm-stubs remain incl the cba0/d98c
  giants). Committed 6ee14b1f8. Names: Ov003_SceneStateEnter(0204e6b8, 612B) /
  SceneStateActive(0204f08c, 688B, input+GFX+transition) / SceneStateFadeOut(0204f33c, tile flush
  + fade countdown) / SceneStateFadeIn(0204f69c, 16-step fade). ov003 = a scene state machine.
  LESSON: do NOT keep `grep -v ov003` on the staging sweep -- peer lanes close functions there too.
★ ahead 6 (86da4, 57ac4, 593d8, 6b37c, 5e058, ov003-batch); origin 36 min -> gate+push next window.

## 2026-07-30 iter 41: MATCH func_ov008_0205e058 (tile-slot upload/draw)

★ MATCH func_ov008_0205e058 = Ov008_UploadTileSlot (156 B, first try). Uploads tile slot arg1
  (0x800 B) via MIi_CpuCopyFast (src/dst both indexed by arg1*0x800 -> `add rX, base, arg1, lsl
  #11`), guard `if(arg2==0) return`, predicated `strge` latch of fieldcc when func_02013814(...)
  >= 0x52, then func_02030278 6-arg draw. Held buf->field20 across two calls; all first-try.
  Committed 34a9ac9ae. ahead 5 (86da4, 57ac4, 593d8, 6b37c, 5e058); origin 24 min -> gate+push
  next window (crosses 1hr).
  NEXT ov008 straight-line: 0206a700, 0205f54c, 02083588, 020798a8, 0206b5f4, 02063018.

## 2026-07-30 iter 40: 2 ov008 matches + refreshed candidate list

★ Re-scanned undone ov008: 97 medium call-seq candidates remain (br<=1, 100-264B, 4+ relocs).
  Scan snippet lives in this iteration's shell history; top straight-line picks by fewest branches.
★ MATCH func_ov008_020593d8 = Ov008_SetupMenuSurfaces (236 B, first try). Copies two 0x28-byte
  style templates (data_ov008_0208e974/99c) to stack locals, overrides field18/field20 of each,
  applies via func_0202ff8c to arg0+0x10/arg0+0x4c, draws a cell, flushes. Struct-copy from a
  global (Style28 s = data_...) emits the ldm/stm; reverse-decl stack layout matched. Committed 4c0e27251.
★ MATCH func_ov008_0206b37c = Ov008_MoveMenuCursor (124 B). Cursor move by delta; wraps via
  func_02020400 (returns quotient/remainder as u64, remainder = high word / `>>0x20`). CRACKS:
  (a) reuse the arg0 PARAM as the wrapped local so mwcc coalesces arg0->wrapped into r7 (fixed a
  callee-saved reg mismatch); (b) `(u16)ctx->field0` to force ldrh where an s16 field is read
  unsigned. Committed 156baa94b.
★ ahead 4 (86da4, 57ac4, 593d8, 6b37c); origin 20 min -> gate+push next window.
  NEXT ov008 straight-line: 0205e058, 0206a700, 0205f54c, 02083588, 020798a8, 0206b5f4.

## 2026-07-30 iter 39: MATCH func_ov008_02057ac4 (menu value draw)

★ MATCH func_ov008_02057ac4 = Ov008_DrawMenuValue (184 B, first try). Draws a computed value onto
  the surface at arg0+0x4c: null guards, reads func_ov008_02057328(obj->fieldC), predicated u16
  store to arg0->field5c4 when >=0 (mwcc `movs`/`strhpl`), cue-0x200c ternary (0x20/idle vs -1),
  then builds a cell and renders (func_02030158 / func_02030278(..,0x56,0,2,cell,1) / func_020300f8).
  Confirms the whole straight-line/guard vein is reliable. Committed e28a0618d. ahead 2 (86da4, 57ac4).
  NEXT: the ov008 straight-line candidate list is now exhausted -- next iteration, re-scan ov008
  asm_stubs/blob-gap for more medium call-sequence funcs (candidate-scan snippet), and keep
  sweeping staging/ov002 for gameplay handoffs.

## 2026-07-30 iter 38: pushed 11-item batch + 3 more ov002 handoffs + 86da4 match

★ PUSHED (gate 306/0, origin was 63 min): the whole accumulated batch -- 6f2a4, 6a9a8, 6aa6c,
  the two ov002 handoff batches (8 funcs), and regenerated progress docs (C=15827, bytes 36.91%).
  origin now 76ce316a5.
★ Integrated 3 more ov002 handoffs (verified real C, blob-gap): 0206e5fc Ov002_RequestMode,
  0206f5c0 Ov002_GetStartTicks, 0206f630 Ov002_GetEndTicks (the last two: (msField*33514)>>6,
  u64). 0206e5fc had no Ghidra function -> create_function then rename. Committed 9f614a792.
★ MATCH func_ov008_02086da4 = Ov008_SetupMenuScreen (216 B). Menu-screen init (display region +
  0x400 buffer clear + flag + 8-entry register loop + widget-6 disable). NEW CRACK (in
  codegen-cracks.md): force `ptr+A` base + `+B` split via `(u8 (*)[B])(ptr+A) + n` -- stops mwcc
  folding ctx+0x728 and avoids the held-pointer hoist. Committed 77c7e5166. ahead 1.

## 2026-07-30 iter 37: ov002 gameplay-bootstrap handoffs integrated + 6aa6c twin

★ NEW FRONTIER SIGNAL: staging/ov002/ received 5 verified real-C handoffs (gameplay bootstrap =
  scene 2, the milestone after the ov008 menu). All byte-exact, all blob-gap carves (C +5, ASM 0),
  integrated into src/overlays/ov002/calls/ + named in Ghidra. Committed 2626d8d37:
  - 0206a418 Ov002_EnterOverlay23 / 0206a46c Ov002_EnterOverlay24 (load overlay + run its hook via
    data_ov002_0207fa00->pOverlayHook; ov024 = the MobiClip movie player)
  - 0207669c Ov002_SetActiveMaskBit (data_ov002_0207fa20.pTable->dwActiveMask |= 1<<bit; -1 on 0xffff)
  - 02076d24 Ov002_TriggerEntryActive / 02076d68 Ov002_TriggerEntrySecondary (func_020235d0(key,kind)
    &1 eligibility -> owner->pOnActive / pOnActiveSecondary callback)
  => ov002 is now a live frontier. The documented gameplay entry func_ov002_020679d4 is the next
  constructor to confirm; watch staging/ov002 for more peer handoffs each iteration.

★ MATCH func_ov008_0206aa6c = Ov008_CancelMenuSelection (196 B, first try) -- TWIN of 0206a9a8:
  identical except it INCREMENTS the count (`(p+1)[p[0]] += 1`) and swaps the unavailable-path
  order (refresh before cue). Committed 2ad0d991a.

★ ahead 4 (6f2a4, 6a9a8, ov002-batch, 6aa6c); origin 48 min -> gate+push next window.
  NEXT ov008: 02086da4, 02057ac4. Permuter still stopped (mwcc=0).

## 2026-07-30 iter 36: MATCH func_ov008_0206a9a8 (menu selection confirm)

★ MATCH func_ov008_0206a9a8 = Ov008_ConfirmMenuSelection (196 B). Confirms the highlighted item
  (ctx->sel@0x4c): resolves via func_ov008_02069bc8, gates on two stride-0x14 byte tables
  (data_ov008_0209059d/9e[sel*0x14]), backs up the 0x34 selection block, decrements the item
  count and recomputes via func_ov008_0206a76c. Committed 1e8ae88b8.
  CRACK: the original holds ONE base pointer p = &ctx->sel (r6) reused for MI_CpuCopy8 src AND
  the count accesses (counts run right after sel). `ctx->counts[ctx->sel]` re-bases on r5 (ctx)
  and comes out 4 B short + no r6; the fix is an explicit `s16 *p = &ctx->sel` and the ROM's own
  addressing groupings: `(p+1)[p[0]]` for the decrement, `*(p+p[0]+1)` around the call. mwcc
  compiles those two groupings to the two different addressing modes the ROM uses per context.
  ahead 2 (6f2a4, 6a9a8) -- pushed once this hour already; gate+push next window.
  NEXT ov008 candidates: 0206aa6c, 02086da4, 02057ac4.

## 2026-07-30 iter 35: peer permuter conflict on 02059b14 (RESOLVED by user)

⚠ A peer/parallel lane was running decomp-permuter (66 workers + 47 orphan mp-spawn python)
  from `staging/_codex_tools/decomp-permuter/` on `func_ov000_02059b14`, saturating all 28 cores
  -- this is why a 306 build crawled for 12 min. Permuter state lives in
  `staging/_codex_work/func_ov000_02059b14/permuter_case/` (base.c, output-40-1/, etc).
  Its BEST score was 40 (iter ~95k, not converging) -- WORSE than my hand version
  `build/try/59b14.c` (byte-exact except one instruction's schedule, ~score 2-4). So the permuter
  will not beat the hand analysis here. User authorized stopping it to reclaim CPU; I killed only
  the RUNNING processes (permuter main + workers + their mwcc), preserved the Ghidra MCP bridge
  and all on-disk permuter files (peer can resume). Then re-ran the gate at -j 20.
  LESSON: before blaming my own gate loop for a slow/runaway build, check the process PARENT
  (`Get-CimInstance Win32_Process ... ParentProcessId`) -- a peer permuter looks like a runaway.
  And use `-j 20` not `-j 4` (machine has 28 cores; -j 4 alone made the gate ~4x too slow).

## 2026-07-30 iter 34: PUSHED batch + 2 ov008 MATCHES + ov000 milestone

★ MILESTONE: ov000 (boot/logo/title/menu) is 260/261 byte-exact -- the whole earliest-play
  overlay is decompiled; only func_ov000_02059b14 remains (characterized scheduler tie, held).
★ GATE 306/0 (after absorbing transient MWCC flakes with `ninja -k 0 -j 4` loop) + PUSHED the
  ahead-3 batch (5b438, 635c8, 658bc). origin now at 6320b8f7d.
★ MATCH func_ov008_020878c4 = Ov008_RefreshPanelDisplay (212 B, first try) -- menu panel rebuild
  from *data_ov008_02090fac; guarded widget re-apply + list-cell append + 4 surface closes +
  scroll resets + 2 sub-panel teardowns. Committed 8f82b6d7c.
★ MATCH func_ov008_02058984 = Ov008_InitPanel (128 B) -- binds the panel global to arg0, copies a
  resource handle to the out-param. KEY CRACK (skill axis #5): the ONLY diff was &data in r0 vs
  r1; fixed by realizing func_02030788()'s RETURN is passed to func_020315c0() (tree already had
  `func_020315c0(func_02030788())`), so it stays live in r0 across the `data=arg0` store, forcing
  &data into r1. Captured it in a local so the store lands between the two calls. Committed 9c0fff970.
★ ahead 2 (878c4, 58984) UNPUSHED -- pushed once this hour already; gate+push next window.
  NEXT: more ov008 straight-line/guard candidates (0206a9a8, 0206aa6c, 0206f2a4, 02086da4, 02057ac4).

## 2026-07-30 iter 33: IN-PROGRESS func_ov000_02059b14 (ov000 list-scene row renderer)

★ SELECTED (port-first: ov000 = boot/logo/title/menu, earliest milestone). Staging file
`staging/ov000/func_ov000_02059b14.c` was an ASM/dcd STUB (rejected as decomp) but carried a
good struct scaffold. DECOMPILED it into real C -- best form in `build/try/59b14.c`:
  - ctx = NNSi_FndGetCurrentRootHeap(); inits primarySurface(0x94)+rowSurface(0xd0) via
    func_02030158; 10-row loop drawing row->textHandle (02059968, x=0x18,y=i*16+0x13,color=2,
    flags=0x209) + row->glyphRun (020599bc, x=0xd0, depth=4), u16 counter, row++ (stride 0x18);
    then special draw (specialTextHandle@0xd114, x=0xfa,y=2,flags=0x821); then selectedRow draw
    (rows[selectedRow].textHandle x=0x38 y=0x3b, .glyphRun x=0xd0 y=0x90); teardown 020300f8 x2;
    transferFlags(0x966c) |= 9.
  - STATUS: size-EXACT 324 B, byte-exact EVERYWHERE except ONE local instruction cluster at
    0xC0. ROM schedules the `rows` base formation (`add r0,r8,#0x670; add r5,r0,#0x9000`) EARLY
    (both adds adjacent, before the s16 index load), plus color-store before the flags pool-load;
    mwcc defers `add r5` and hoists the flags pool-load. Reconverges immediately after
    `ldr r1,[r5,r4]`. NOT arity/return (6-arg 02059968 + 5-arg 020599bc confirmed by the [sp]
    stack stores; both void). ~16 experiments (every address-expr form, base materialization,
    register hints, decl order, index type, inline-vs-pointer, shared/reused base) + corpus
    analysis all give the IDENTICAL residue. Corpus shows the base-EARLY form is the *fused*
    smlabb single-access shape (func_ov000_02059c58, 0205a3e0); the target legitimately uses the
    two-access `smulbb`+separate-base shape, which mwcc schedules base-late here.
  - Genuine mwcc arg-scheduling tiebreak. NOT parked, NOT moved to nonmatching, staging stub
    untouched. Stays SELECTED in build/try/59b14.c; next iteration resumes here (fresh angle:
    maybe a different call-arg framing or temp-lifetime lever not yet tried).

## 2026-07-30 iter 34: 02059b14 continued (18 experiments total) + SIBLING confirmation

★ Read matched siblings `func_ov000_02059c58` / `0205a3e0` (SAME struct = `Ov000SceneContext`,
  NOT my rival `Ov000ListSceneContext` -- align the name when it matches). Both access
  `&context->transferEntries[context->selectedRow]` via a pointer local -> CONFIRMS my `sel`
  idiom is right. They match with the FUSED smlabb (base-early) form ONLY because their first
  field read is at a NON-ZERO offset (palette +8) -> mwcc materializes the entry pointer first.
  My target's first field (textHandle) is at offset 0 -> mwcc uses [base,index]+materialize-later,
  and schedules the base-add late here. The ROM does the SAME instructions but base-early.
  New forms tried this iter (all @0xC0): cast-based base `(u32)ctx+0x9670` (the sibling's own
  `(u32)context+0xa110` idiom), int-index inline (328), shared-rows base (332).
  NEXT ANGLE (untried): vary func_ov000_02059968's prototype arg TYPES (x/y as s16, color/flags
  widths) -- the stack-arg store scheduling for args 5/6 (color-store vs flags-pool-load order)
  is HALF the residue and is the one axis not yet exercised.

★ PUSH: ahead 3 (5b438, 635c8, 658bc), origin 50 min ago -- gate + push next window (crosses 1hr).

## 2026-07-30 iter 32: MATCH func_ov008_020658bc (guard + bitfield)

★ MATCHED func_ov008_020658bc = Ov008_UpdateReadyState (212B, first try). Guard-heavy widget
enabler: bit-2 of p->flags380 (BITFIELD `unsigned b2:1` -> lsl#0x1d;lsrs#0x1f) + both sentinels
p->field384/388 == 0x7fffffff (short-circuit ||, 0x7fffffff via mvn #0x80000000), then enables
widget 3 and (if field10==2 && field8==1) re-links widget 0x51. Committed 6320b8f7d.

★ PUSH: ahead 3 (5b438, 635c8, 658bc) -- all verify-clean, UNPUSHED. Last push iter 29 (~18 min
ago per %cr at iter 32 start). GATE + push the batch next window once %cr crosses ~1hr. Cracks
reconfirmed: bitfield bit-N test = `unsigned bN:1` (lsl/lsrs); 0x7fffffff literal -> mvn; the
`br<=1 && bl>=4` filter misses conditional POPs (early returns) -- guard-heavy funcs still match
first-try though. NEXT straight-line/guard candidates: 020878c4(15bl), 02057ac4, 0206a9a8,
0206aa6c, 0206f2a4, 02058984, 02086da4. Held register-coloring ties: 69180, 6cdb4.

## 2026-07-30 iter 31: MATCH func_ov008_020635c8 (straight-line); 6cdb4 held (register tie)

★ MATCHED func_ov008_020635c8 = Ov008_SetupMenuDisplay (212B, first try). 5-arg (arg5 on stack)
PURE straight-line call sequence (0 branches): builds two SRT/display objects (0203034c on
p+0x124 & p+0x250), advances/binds them (020300f8, 02030094), enables cell 0x5c, re-links its
widget, registers via 0205eafc. Committed 26cca5c09 (ahead 2 with 5b438; push held, last iter-29).

★ HELD build/try/6cdb4.c: func_ov008_0206cdb4 (list-count widget scaler, 208B). SIZE-EXACT, byte
@0x5 -- register-coloring cascade (ROM ctx->r4,val->r5,p->r6; mwcc ctx->r6,val->r4,p->r5). SAME
tie class as 69180. Documented, not parked.

★★ REFINED STRATEGY (confirmed twice now): in the ov008 widget-setup vein, the LOOP / multi-
callee-saved functions (69180, 6cdb4) hit REGISTER-COLORING ties (size-exact, unsteerable ctx/param
r6<->r7 swap). The STRAIGHT-LINE call-sequence functions (0-1 branches, 4+ bl -- 5b438, 635c8, and
the whole iter-27..29 batch) MATCH FIRST TRY. So filter the vein by shape: `br<=1 && bl>=4` = match;
loops = likely tie. 20 straight-line candidates found (020878c4, 0206b5f4, 020658bc, 020877a8,
02057ac4, 0206a9a8, 0206aa6c, 0206f2a4, 0208500c, 02086da4, 02058984, ...). NEXT: those, in order.
Held near-matches (register ties): 0208500c(*wait, that's straight-line -- retry it*), 69180, 6cdb4.

## 2026-07-29 iter 30: MATCH func_ov008_0205b438 (timed tick); 69180 held (register tie)

★ MATCHED func_ov008_0205b438 = Ov008_TickMenuTimer (180B, first try). Per-frame tick: 64-bit
deadline compare (`p->stored + 0x7fd88 < func_020031d4()`, u64) fires a one-shot once; ticks the
+4 sub-object; conditionally refreshes widget id 2 with (u16)func_ov105_020bd7c4() (cross-overlay).
Used u64 field + K=0x7fd88 literal + 02023588(0x200d) literal. Committed 3e6f62bd9 (ahead 1).

★ HELD build/try/69180.c: func_ov008_02069180 (2-widget reposition loop, 164B). SIZE-EXACT, byte
@0x15 -- whole-function REGISTER-COLORING permutation (ctx/i r6<->r7, id/widget sb<->r8) + the
field64!=0 branch uses conditional stores of hoisted 0x28000/0x88000 regs vs mwcc's moveq/movne+str.
Tried ternary/if-else/`register`; coloring won't shift. Register-coloring tie, documented.

★ VEIN STATUS: the ov008 widget-setup family's easy guard+toggle members are now mostly matched;
the remaining ones trend harder -- register-coloring loops (69180), fixed-point loops (020868d0
sb+0xb000 offsets + 0x30000/0x25000), 64-bit timers (5b438 DONE), list-count+clamp (0206c29c/
0206cdb4 with mul+02020400). Still matchable with care (5b438 proves it), but expect fewer first-try.
NEXT: 0206cdb4 (list-count+scale, 208B) or 0206c29c; then the fixed-point loaders. Push held this
hour (batch pushed iter 29); push 5b438 next window after a gate.

## 2026-07-29 iter 29: MATCH func_ov008_02071468; gating + pushing the 6-func batch

★ MATCHED func_ov008_02071468 = Ov008_PositionListCursor (160B). Positions widget id 1 from a row
index (fixed-point y = (((field0<<5)-field0C)<<12)-0x20000) or a default global point when field0<0.
Two cracks: (1) `Vec2 pt = {0,0};` zero-init (ROM writes BOTH x=0 and y=0 before the computed y --
plain `pt.x=0` alone is 2 instr short); (2) in the else branch assign pt.y BEFORE pt.x to match the
ROM's load/store order. Committed 766d51998.

★ PUSH: ahead 5 = 6 funcs (ea84, f7b0, 712f8, 655e4, bca0, 71468) -- running the 306 gate now, then
pushing the batch (b158 was pushed iter 27, several gate-bearing iterations ago = >1hr wall-clock).
Widget-setup vein continues (~98 undone). New reusable crack: for a small stack struct that the ROM
fully zero-inits before a partial field write, use `T v = {0,0};` (mwcc keeps the dead zero-store).

## 2026-07-29 iter 28: 3 more widget-setup matches (712f8, 655e4, bca0)

The ov008 WIDGET-SETUP vein keeps paying: 3 first-try (or near) matches this iteration.
  - func_ov008_020712f8 = Ov008_UpdateScrollArrows (128B) -- prev/next arrow enabler by
    index-vs-count; prev id 0x3f/0x3d ternary, next id 0x3e. Committed e196b659e-batch.
  - func_ov008_020655e4 = Ov008_UpdateButton3State (128B) -- toggle widget 3 w/ state memory
    at field48. (both committed f41cf34e1)
  - func_ov008_0206bca0 = Ov008_ChangeMenuSelection (160B) -- fade-transition selection change +
    disable buttons 0x47/0x48. ★ TERNARY-ORDER crack: write `x==0 ? 0 : BIG` (not `x!=0 ? BIG : 0`)
    so mwcc emits moveq-before-movne matching the ROM. Committed d2e0ad1f9.

★ PUSH STATE: ahead 4 (5 funcs: ea84, f7b0, 712f8, 655e4, bca0) all committed + verify_idx-clean,
UNPUSHED. b158 pushed iter 27; hold the batch push until ~1hr past that, then GATE + push all.
The `%cr origin/main` check reads b158's COMMIT date (~2h, misleading) not its push time -- go by
actual push (iter 27). Widget-setup family now ~99 undone; keep mining it (small guard+toggle
funcs match first-try). Reusable levers this vein: short-circuit `||`/`&&` guards compile direct;
ternary-order flip; state struct with the touched fields.

## 2026-07-29 iter 27: b158 PUSHED (classifier back); 0208500c size-exact (held); MATCH ea84

Classifier outage (iters 23-26) cleared. PUSHED b158 (aab7105da..b89f1b774).

★ func_ov008_0208500c: the tab-pointer form (`char *tab = st+0xc3b8; *(int*)tab=a0; *(int*)(tab+4)
=a1`) SOLVED the two-base large-offset addressing (was 2 instr short) -> now SIZE-EXACT, byte
diff @0x3C. Residue = a register-coloring cascade from ONE scheduling choice: ROM preloads `flag`
to r7 at ENTRY; mwcc here defers its stack-load to before the loop (shifts i->r7, cell->r6). Tried
& failed to move it: plain local, `register`, mask-at-top (@0x8), cell at fn scope. HELD
build/try/850c.c (tab form, best, documented). CRACK LEARNED: to reproduce a two-add materialized
large-offset base (add base,#lo; add.,#hi) use a real `char *` pointer local, NOT raw offsets or a
struct field (both CSE to one base). The sibling func_ov008_02084604 uses the same st+0xc3b8 tab.

★ MATCHED func_ov008_0206ea84 = Ov008_SetupMenuButtons (224B, 12 relocs, first try). Guard
(short-circuit `||`) + widget enable pass: 02054ba4(ctx, 02054788(ctx,id), flag) for ids
{0x29 if field44==0, 0x51, 5, 0x80}, then 0206c90c + marks done. Committed e196b659e (ahead 1;
b158 already pushed this hour so ea84 waits for next window).

★ ALSO MATCHED func_ov008_0206f7b0 = Ov008_UpdateMenuButton5 (116B, first try). Guard
(data_02090f20 && ctx->fieldC != param, short-circuit ||) -> cache value, get widget id 5,
enable (prime w/ 02054c80 then 02054ba4=1) if param!=0 else disable. Committed 04a5667c6.

★★★ RICH VEIN: the ov008 WIDGET-SETUP family -- 104 undone funcs calling func_ov008_02054788
(get widget by id) + func_ov008_02054ba4 (set enabled)/02054c80 (prime). These are guard +
widget-toggle functions (menu button enable/disable/refresh) -- clean call-sequences with
short-circuit guards, matching FIRST TRY (ea84, f7b0). This is the productive next vein. Small
ones: 020712f8(128), 020655e4(128), 0206bca0(160), 02071468(160), 02069180(164), 0205b438(180).
Template: get ctx (02050c64/02050cec), widget=02054788(ctx,id), 02054ba4(ctx,widget,flag). Grep
each callee's arity first. iter-27: 3 matches (b158 pushed, ea84, f7b0) + 0208500c held size-exact.
ahead 2 (ea84+f7b0) -- push next hour after gate (b158 pushed this hour).

## 2026-07-29 iter 22: MATCH func_ov008_0206b158 (slot-cell rebuild, struct-based loop)

★ MATCHED func_ov008_0206b158 = Ov008_RegisterSlotCells (156B, 8 relocs, first try). Rebuilds the
cell list for the current slot page: looks up the slot table (02069b60 keyed by state->pageId),
loops every slot except state->selected registering table->arrB[i] (byte @0xd+i) via 02055808+
0205589c, then 0206abb8(table->id,0,0) + registers table->arrA[state->selected] (byte @8). Used
structs Ov008SlotState{s16 selected@0; u16 pageId@2} and Ov008SlotTable{u16 id@0; u8 count@2;
u8 arrA@8; u8 arrB@0xd}. Loop re-reads count and selected each iter (ldrb/ldrsh inline, not cached).
Committed b89f1b774. func_ov008_02050cd4 returns this state (same object as b988's page).

HELD build/try/850c.c: func_ov008_0208500c (menu cell setter, 6 args). 172 vs 180, 2 instr short --
the two big-offset stores G[0xc3b8]=a0 / G[0xc3bc]=a1: the ROM computes G+0xc000 AND G+0x3b8 as two
separate bases (a0 via +0xc000+0x3b8, a1 via +0x3b8+0xc000+4) while mwcc CSEs one base no matter the
source form tried (raw offsets, 0xc000-bank struct, explicit q=G+0x3b8 pointer). int params+(u16)
casts already fixed the a2/a3 masks. Next: two-distinct-member struct, or grep matched tree for
`add rX,base,#imm; add rY,rX,#0xc000; str [rY,#4]`. NOT parked -- held, best form on disk.
NEXT after 0208500c: 02072418/02077190 (428B loaders), 02063018/02068d58 (cell-reg).

## 2026-07-29 iter 21: MATCH func_ov008_0206bdf0 (menu-screen builder, hardest family member)

★ MATCHED func_ov008_0206bdf0 = Ov008_BuildMenuScreen (444B, 27 relocs, FIRST TRY after full
pool/arity decode). The composite scene setup: loads sub-screen BG (subfile 0x27) + alternate char
bank (subfile 0), calls the loader func_ov008_0206b754(ctx,0) I matched last iter, opens a 2nd
cell-list ctx (02050c3c), attaches subfile 0x26, registers cells {1,2}, and lays out two items via
func_ov008_020559c0 -- an 8-ARG call (4 reg + 4 stack): (ctx, item, a, b, c, d, 0xffff mask,
callback). The 0xffff is a SHARED pool literal (both calls); the callbacks 0206f3ac/0206f4c0 are the
only two function-ptr relocs in the pool. Returns int 0 (mov r0,#0 -> declare int, `return 0`).
KEY to first-try: disassembled with capstone+addresses to map every `ldr [pc]` to its pool slot and
separate literals (0xffff) from relocs (the two callbacks). Committed e6746b314.

★ STRUCTS: the family's Ghidra types ALREADY EXIST as Ov000ResourceCell(12)/Ov000CharacterBlock(24)
/Ov000PaletteBlock(16)/Ov000ScreenBlock(16) -- created by the ov000 lane; they are the same NNS
resource types. DO NOT create Ov008* rivals (no-rival rule). For future ov008 matches, type the
stack `cell` local with Ov000ResourceCell rather than making a new type. The per-file C keeps its
self-contained Ov008* typedefs (codegen tool); the Ghidra database uses the shared Ov000* types.

★ func_ov008_020559c0 was ALREADY MATCHED (a prior session; it is in calls/ with param-cast C, size
92). My family scan listed it as a callee reloc, NOT an undone function -- the sweep counts a name
as done only if src/overlays/ov008/{calls,auto}/NAME.c exists. Re-scan of TRULY-undone family = 36.

★ ALSO MATCHED func_ov008_02078bb0 = Ov008_LoadMenuSubBg2 (152B, first try). Sub-screen BG2 char
loader: packed archive-subfile handle (subfile 0x30) from ctx->archiveBase via the OV000_SUBFILE
macro, func_02011988 resolves the char block, GXS_LoadBG2Char@0x4f40, free, attach data_02090b58.
Used a context struct (archiveBase @0x34) instead of a raw offset. Committed 69cdae0d2.

★ ALSO MATCHED func_ov008_02074a4c = Ov008_SwitchMenuTab (196B, 7 relocs). Menu tab-switch:
maps old/new tab index -> cell tag (0/1/2 -> 0xf0/f1/f2 and 0xf3/f4/f5), re-registers cells,
retargets p+0xc to p->arr138[idx], applies p->arr144[idx], stores idx. ★ BRANCH-VS-PREDICATE
CRACK (codegen-cracks line 1270): the tag dispatch came out 8B (2 instr) SHORT because mwcc
PREDICATED the middle (==1) case (moveq;beq) while the ROM branches it to an out-of-line mov.
Fix: write the ==1 case as an ELSE block -- `if(x!=0){ if(x!=1){ if(x==2)tag=B; } else {tag=A;} }`
-- the else form forces the out-of-line branch (last case ==2 still predicates). Flat if/else-if
(all cases) or switch both over/under-shoot. Committed after the gate.

9 family matches now (592d4, ada4, b754, a474, 067db0, bdf0, +020559c0 pre-existing, 78bb0, 74a4c).
Remaining TRULY-undone (36): 0206b158 (156B, cell-reg LOOP), 02074a4c (196B), 02056fb8 (176B),
0208500c (180B), 02063018/02068d58/02071508 (260-272B). Two iter-21 lessons: (1) always re-check
`done()` = file in calls/auto BEFORE selecting -- a callee in the scan is not necessarily undone;
(2) big composite loaders match FIRST TRY when you capstone-disassemble with addresses and map every
`ldr [pc]` to pool literal vs reloc before writing. iter-21 commits: e6746b314(bdf0), 69cdae0d2(78bb0).


## 2026-07-29 iter 20: MATCH func_ov008_020592d4 (menu BG/cell-list setup); b988 tie confirmed (16 forms)

★ MATCHED func_ov008_020592d4 = Ov008_SetupMenuBgCells (248B, 18 relocs, first try). Pure
call-sequence: G3X_SetHOffset(-0x3b); ctx=02050c28(); unpack subfile 0xA -> resource cell;
GX_LoadBGPltt/GX_LoadBG3Char from the cell; free; 02055534(ctx, subfile 7); register cells for
tags {0,1,2,4} (3 skipped). KEY: func_02024c94 takes FIVE args (ROM's `str r2,[sp]` = trailing
stack 0) -- the grep-for-arity check caught it. Resource-cell layout copied from the ov000 loader
(func_ov000_02058c28): screen/character/palette ptr trio; palette block +8 size/+0xc data,
character block +0x10 size/+0x14 data. Committed 20c5e93ad. Named in Ghidra + plate.

★ b988 EXHAUSTIVELY CONFIRMED a tie: 16 source forms (A-P) -- int/u8*/struct page, load-into-local
vs inline, load order, x1 early/late, sum-precompute, cVar1 u8/int, loop form, pointer form,
register hint, swapped compare operands, operand grouping. INVARIANT residue: ROM hoists the x1
load early (2 separate `add #0x1000`, cVar1->r0); every form keeping 2 adds schedules x1 late
(cVar1->r1); any form forcing x1 early triggers value-numbering CSE of page+0x1000 (-1 byte). No
source spelling reaches "x1-early + 2-adds" under build 139. mwcc scheduler/CSE interaction tie.
HELD build/try/b988.c (NOT parked). Confirms: pick PURE CALL-SEQUENCE ov008 funcs (like 592d4),
not byte/data-movement scorers.

★★ ALSO MATCHED (same iteration, same template):
  - func_ov008_0205ada4 = Ov008_SetupMenuBgCellsAlt (236B). Twin of 592d4; mode-selected subfile
    (func_02024e5c()==1 -> 0x16 else 5), tags {0,2}. The ==1 needed the MATERIALIZED-bool crack
    (assign to local -> moveq/movne/cmp#0; direct if is 3 instr short). Committed a22ef6f10.
  - func_ov008_0206b754 = Ov008_LoadSubScreenBg (164B). Sub-screen (GXS) BG loader; guard
    02053a90(data_0204be18+0xee0) when param_2==0; func_02024c94(...,-1,0,0); char size/data cached
    in locals to survive the palette upload (callee-saved r5/r6). Committed 8f5966f8e.

★★★ RICH VEIN FOUND: the ov008 RESOURCE-CELL / BG-LOADER family -- 40 undone ov008 funcs call
func_02024c94 / func_ov008_02055808/0205589c/02055534. Template (all self-contained, reuse the
Ov008ResourceCell{screen,character,palette} + CharacterBlock{+0x10 size,+0x14 data} +
PaletteBlock{+8 size,+0xc data} trio, copied from the ov000 loader func_ov000_02058c28):
  handle = func_0201ef9c(func_ov008_02050f08(subfile), 0xe);
  func_02024c94(&cell, handle, a,b,c);   // FIVE args -- trailing stack arg is the ROM's str [sp]
  GX[S]_LoadBGPltt(cell.palette->data[+off], off, size); GX[S]_LoadBG3Char(cell.character->...);
  if (handle) NNSi_FndFreeFromDefaultHeap(handle);
  [optional] ctx=02050c28(); 02055534(ctx, subfile7); for tags: 0205589c(ctx, 02055808(ctx, tag));
★★ ALSO MATCHED: func_ov008_0206a474 = Ov008_LoadMenuBgWithAltChars (240B, 13 relocs). Main-screen
loader (subfile 3) + optional alternate char bank (subfile 8, via func_020119d4 + DC_FlushRange +
GX_LoadBG3Char@0x1000) that runs when func_02024e5c() != 1. WATCH THE POLARITY: the materialized
`==1` early-return fires when TRUE (addne/popne), so the alternate path is the mode!=1 branch --
diffdis showed addeq vs addne and one flip fixed it. Committed 322cc7d6b.

★★ ALSO MATCHED: func_ov008_02067db0 = Ov008_LoadMenuBgWithVariantChars (300B, 19 relocs, first
try after full pool analysis). Same family, richer: descriptor is a GLOBAL passed by address
(func_0201ef9c((u32)data_ov008_020904a4, 0xe) -- one load, no deref); the BG3 char source is
branch-selected (alternate block via func_020119d4/DC_FlushRange if func_ov008_02050f40(2)!=0,
else cell.character); then a raw MMIO write `*(volatile u32*)0x04000018 = 0x01e600e3` (BG2 H/V
offset regs, both operands pool LITERALS -- NO reloc), func_ov008_02055534(ctx, data_ov008_020904bc)
with the 2nd arg also a global-by-address, and cell reg tags {0,1}. The pool literals @0x120/0x124
(0x01e600e3, 0x04000018) vs the relocs @0x11c/0x128 -- decoded from func_index hex, key to writing
it first-try. Held build/try/067db0.c (verified MATCH); commit after the gate.

5 MATCHES this iteration (592d4, ada4, b754, a474, 067db0). NEXT family members: 0206bdf0 (444B,
02024c94+534+808+89c), 0206b158/02074a4c (cell-reg only), 02072418/02077190 (428B, big loaders).
Reusable cracks reconfirmed: (1) 5-arg func_02024c94; (2) materialize an `== N` bool used in an if
(assign to a local); (3) check materialized-bool BRANCH POLARITY via diffdis (addeq vs addne);
(4) a global passed by ADDRESS -> func(...(u32)data_X...) is one load; (5) decode pool literals vs
relocs from func_index hex before writing (MMIO const stores are pool literals with no reloc).

## 2026-07-29 iter 19: b988 (ov008) cracked 25->14 diffs (&& materialization); CSE residue

Continued func_ov008_0205b988 (Ov008 page scorer). Cracked from broken/25 -> SIZE-EXACT/14 diffs:
(1) ★ the `&&`'s inner `GetField()<2` must be a MATERIALIZED bool -- `int ge2 = ...>=2; if(!ge2)`
gives the ROM's movhs/movlo/cmp#0; writing `<2` directly makes mwcc OVER-PREDICATE (3 instr short).
This is a reusable crack for menu funcs. (2) cache page[0x14f0] local, read page[0x14f1] inline.
RESIDUE: the ROM loads page[0x14f1] EARLY with its OWN page+0x1000 base (2 base computations); as a
local mwcc CSEs the base (-1), inline it loads late -> a cVar1 r0/r1 register cascade. Data-movement
base-CSE/scheduling tie. HELD build/try/b988.c.

★ REFINED PATTERN: even ov008 "fresh" funcs tie when they are BYTE/DATA-MOVEMENT (b988 = page byte
math -> CSE tie). The reliably-matchable type is PURE CALL-SEQUENCE (dac8, c884, c5e4 = straight-line
bl's, reloc-masked). NEXT: from ov008's 406 undone, pick a STRAIGHT-LINE CALL function (many bl's,
few/no branches, little byte math), not a scorer/data function. Staging: ov003(14) DIFIERE, ov000
stub. Gate 306/0 (no src edits).

## 2026-07-29 iter 18: FRONTIER RE-EVAL -- title saturated; ov008/ov002 are the fresh veins

★★★ STRATEGIC FINDING (measured undone-function counts per backbone overlay):
  ov000 (title):  C=260  stub=1(b14, sched tie)  UNDONE=0     -> DONE except 1 tie
  ov011 (title):  C=24   stub=16(mostly sched/store ties + b340 dispatcher)  UNDONE=0
  ov006 (mission):C=169  UNDONE=24
  ov008 (MENU):   C=817  UNDONE=406   <-- huge fresh vein, next play-order milestone
  ov002 (GAMEPLAY):C=826 UNDONE=648   <-- huge fresh vein
The TITLE cluster (ov000+ov011) is essentially decoded -- remaining are scheduling/store ties
(bb58,cff0,cda0,c3a0,da60,d6a0,ac40,b14,b340...). Confirmed b14 (ov000's last fn) is a 6-word
scheduling permutation a PRIOR session attacked with HUNDREDS of forms + a hill-climber -- a genuine
tie. b340 (ov011) is a 1236B dispatcher with tie-prone data-movement cases.

CONCLUSION: the title is port-ready (decoded); the matchable FRESH work is in ov008 (main menu,
next milestone) with 406 undone funcs, and ov002 (gameplay) with 648. Per port-first + change-vein,
future iterations should mine ov008 (then ov002) for clean call-sequence funcs (the dac8/c884 type
that MATCH), holding the title ties.

Validated the ov008 vein: 75 undone medium call-rich candidates. Started func_ov008_0205b988
(Ov008 page-score fn, 148B): decoded, but mwcc over-predicates the `GetField()<2` && check (mine
3 instr SHORTER than the ROM's bool-materialization: movhs/movlo/cmp#0). u8 cVar1 + ++ + comma-expr
tried, still 136B/25 diffs. HELD build/try/b988.c -- pick a PURE call-sequence ov008 fn next (b988
has predication subtleties; the straight-line ones match cleaner). Gate 306/0 (no src edits).

## 2026-07-29 iter 17: d6a0 -> SIZE-EXACT (1 store from match); ac40 scene ctor 1-store-swap

d6a0 (title-slot object registration) brought from undone -> SIZE-EXACT (byte diff @0x50, 13
diffs of which the loop + final calls match exactly; the bl diffs are reloc-masked). Crack: the
two loop stores as ARRAY index `((int*)(base))[i]` kills the i*4 induction var (was +8 B). RESIDUE
= the `cfg[1]=2` store before the 2nd func_02032388: ROM defers it (2 in r2, store just before the
call), mwcc stores early (2 in r1, reused for &cfg). ~7 source forms tried (struct, p2=cfg, mgr2,
two-local) -- all inert; the store scheduling is entangled with the &cfg register. Store-
scheduling tie of the da60 class. HELD build/try/ov011/d6a0.c.

ac40 = Ov011_CreateScene (the SCENE CONSTRUCTOR, play-order #1): re-examined the prior BESTac40.c
(size-exact). Sole residue = TWO adjacent stores swapped: the ROM stores the openParams.enabled
flag (sp+4) BEFORE the first movie-name byte; mine reverses. Moving the flag assignment in source
restructures the whole name-copy register allocation (464 or @0x0, both worse). A prior session
also left it "one instruction rotated". Store-scheduling tie, HELD build/try/ov011/BESTac40.c.

★ PATTERN (now 8 funcs): pure call-sequence funcs MATCH (dac8, c884, c5e4); anything with a struct
fill / adjacent independent stores ties on the STORE ORDER (da60, d6a0, ac40, cff0/cda0/c3a0/bb58).
c2fc = MMIO (tie-prone). NEXT MATCHABLE: func_ov011_0205b340 -- the large (1236B) 11-case state
DISPATCHER (jump table), the control-flow type that matches; big but byte-matchable. Gate 306/0.

## 2026-07-29 iter 16: dac8 MATCHED (fresh call-sequence) + d6a0 near-match -- the pattern holds

★ func_ov011_0205dac8 = Ov011_SetupTitleTileSurfaces MATCHED byte-exact (200 B, 7 relocs,
straight-line 6-call sequence: 2x func_020136b0 + 4x da60). Wired to calls/, stub removed
(C+1/ASM-1), Ghidra renamed+saved, gate 306/0, committed 3a79b865a + progress fd40d1fbf,
PUSHED (058003db3..fd40d1fbf). This CONFIRMS the iter-15 pattern: CONTROL-FLOW / call-sequence
functions MATCH; data-movement (struct-fill) functions tie.

d6a0 (284/7, title-slot object registration): decoded + brought to SIZE-EXACT (byte diff @0x50),
13 diffs. Crack: loop stores as ARRAY index `((int*)(base))[i]` kills the i*4 induction var.
The loop + final calls match EXACTLY; sole residue = the `cfg[1]=2` store before the 2nd
func_02032388 (ROM defers it in r2, mwcc stores early in r1 -- a store-scheduling detail). HELD
build/try/ov011/d6a0.c, very close (a match candidate for a fresh look).

Staging: ov003 14 DIFIERE (peer), ov000 stub. NEXT: crack d6a0's cfg[1]=2 store scheduling
(one region from a match), or another fresh CONTROL-FLOW title function. Held ties remain: bb58,
cff0, cda0, c3a0, da60 (data-movement register/store-scheduling ties, all decoded).

## 2026-07-29 iter 15: c3a0 confirmed coloring tie (grep-the-tree: no 2-sub template); cluster done

Continued c3a0. Grep-the-tree for the `sub #imm1; sub #imm2` 2-subtract pattern over ~400 matched
funcs -> ZERO hits: the 2-sub materialization is not a writable C template, so the -0x17ae pool
(+4) is DOWNSTREAM of loop-2's register allocation, not independent. Checked loop-2 callee return
types (IsVisible/GetPositionPtr both return r0 only -- correct) and arities (correct). Fresh
loop-2 variables (not reusing loop-1's) -> inert, still 580/61. Loop-2 residue is a uniform +1
register-shift (obj r7 ROM/r8 mine, paneOff2 r8/r9): the ROM RELOADS the globals base from the
pool each inner iteration (register pressure), mine caches it in a callee-saved reg -> the extra
low register. Same by-name-vs-cache/coloring class as bb58/cff0/cda0. HELD build/try/ov011/c3a0.c
at 580 (+4), NOT parked.

★ CLUSTER STATUS: the ov011 title-slot TRANSITION cluster is now fully decoded and all 4 are
size-exact/near coloring ties: bb58 (interp, 136), cff0 (tag advance, 78), cda0 (tag blit, 120),
c3a0 (transition, +4/61). Semantics + structs + Ghidra names done; bb58 2-arg crack found. The
COMPILER QUESTION IS RESOLVED (flags = -O4,p confirmed, iter 14). Per the change-vein lesson, the
matchable progress from here is FRESH title functions (the c884/c5e4 clean-match type), not more
grinding of this saturated high-register-pressure transition cluster.

Staging: ov003 14 files DIFIERE (peer), ov000 stub. Nothing to integrate. Gate 306/0 (no src).
NEXT: a fresh cleanly-matchable ov011/title function (tick/state type, by-name, switch-dispatch),
OR reconfirm the earliest unresolved play-order milestone (ov000 title/menu proper) has no earlier
matchable work before staying in this cluster.

### iter 15 addendum: da60 (fresh SIMPLE fn) is ALSO a store-scheduling tie
Tried a FRESH simple data-movement stub func_ov011_0205da60 (fills a 10-word TileSurfaceCfg and
calls the THUMB func_0202ff8c). SIZE-EXACT first try (byte diff @0x0), 24 diffs -- but a store-
SCHEDULING tie: ROM materializes all constants into r4-r7 then stores in field order, mwcc
interleaves + reuses param regs. array/struct-fields/vram-first inert; aggregate init WORSE
(120B). bl->blx NOT the issue (verify_idx masks all 4 reloc bytes). HELD build/try/ov011/da60.c.
★ PATTERN CONFIRMED across 6 funcs: control-flow state-ticks (c884,c5e4) MATCH; data-movement
funcs (bb58,cff0,cda0,c3a0,da60 -- struct fills/geometry/blits) are register/store-scheduling
ties with correct structure+semantics. Compiler=-O4,p confirmed. The matchable vein is control-
flow-heavy functions, not data-movement ones.

## 2026-07-29 iter 14: bb58 = 2-ARG (crack); c3a0 transition broken->580 (+4); flag hyp DISPROVEN

★ FLAG HYPOTHESIS DISPROVEN: swept cda0 across -O4,p/-O4,s/-O3/-O2/-O1. ROM cda0 = 520 = the
-O4,p size (-O4,s gives 508, SMALLER). So compiler AND flags are confirmed correct (-O4,p);
the cluster's residues are genuine SOURCE-shape coloring, not a flag issue. Good negative result.

★★ bb58 TAKES TWO ARGS. c3a0 sets r1=1 before BOTH bb58 calls (mov r1,#1 / mov r1,r0) but not
before cff0 -> bb58 sig is (int pane, int arg2). bb58's body overwrites r1 at instr 2 so arg2 is
unused inside (bb58's own 136-diff match is UNCHANGED with 2 params -- verified) -- but callers
MUST pass it. bb58.c updated to 2 params. No matched code calls bb58 yet (only c3a0 in build/try).

Selected c3a0 (the transition, play-order frontier that uses bb58/cff0/cda0/cad8). Brought from
broken -> 580 B (+4, ONE pool word over), 61 diffs, via cracks: bb58 2-arg; u16 flag (ldrh);
threshold <=0x80 (cmp#0x80;bgt); obj as ARRAY index `((int*)(base))[j]` (kills j*4 induction
var, inline lsl#2); read nX/nY into locals -> mwcc fuses `ldm r0,{r1,r2}`. RESIDUE: last +4 is
`nY-0x17ae` -- ROM does 2 subs (#0xae,#0x1700), mwcc pools the folded -0x17ae because a scratch
reg is free (register-pressure dependent, tied to the loop-2 coloring). HELD build/try/ov011/
c3a0.c, NOT parked. Gate 306/0 (no src edits).

Staging: ov003 14 files all still DIFIERE (peer), ov000 stub. Nothing to integrate.
NEXT: crack c3a0's -0x17ae pool (needs the loop-2 register coloring exact) OR a fresh title fn.

## 2026-07-29 iter 13: cda0 (DrawTitleTagRun) -> SIZE-EXACT; staging ov003 still not ready

Staging: ov003 pending count 15->14 (peer active) but all 14 re-verified DIFIERE; ov000 stub.
Nothing ready to integrate.

Decoded + brought FRESH func_ov011_0205cda0 (the c3a0/cff0 tag-run blit, 520B/9 relocs) from
undone -> SIZE-EXACT (byte diff @0x0), 120 masked diffs, correct structure/instr-count/structs.
Renamed Ghidra Ov011_DrawTitleTagRun (saved). Structs: Ov011TagMatch {int idx; u16 m[4]} (0xc,
data_ov011_0205dca0 4-entry table), UiLayoutPos {int nX,nY}. Two cracks: (1) fresh `invokeArg`
local not `param_6 = param_5` -> kills the spill; (2) func_02030158 = 4-arg vtable trampoline
Obj_InvokeInnerVtable4 (forwards r3, so param_4 must be live). RESIDUE: ROM keeps tag `*s` in
scratch ip and param_3 in entry reg r2 (free call arg); mwcc puts tag in callee-saved r6 -> +1
callee-saved shift (param_2->sb). bb58/cff0 class. Tried invokeArg, reorder(516 worse), named
tag, by-name pScene(536 worse), declperm(all 356). HELD build/try/ov011/cda0.c, NOT parked.

★ THREE size-exact coloring ties now held in the ov011 title cluster: bb58 (interpolator),
cff0 (tag advance), cda0 (tag blit) -- all the c3a0 transition dependencies. Each is structurally
exact with mwcc allocating one different callee-saved register than the ROM. Gate 306/0 (no src
edits). NEXT: c3a0 itself (the transition, 576/15) now has all deps understood/size-exact; or a
FRESH cleanly-matchable ov011 title function outside this high-pressure cluster.

## 2026-07-29 iter 12: cff0 declperm-swept (coloring tie confirmed); staging ov003 not ready

Staging sweep: ov009 fully integrated (gone). ov003 lane has 15 files but ALL DIFIERE
(near/tie, peer lane still working -- not ready, unlike ov009 which were byte-exact). ov000
02059b14 is still the asm stub. Nothing ready to integrate this iter.

cff0 (frontier, selected): ran declperm.py -- 120 declaration-order permutations of the 5 top
pointers, ALL at 154 bytes off (== the 78-diff residue). Plus ordering variants v12 (ent late,
90) and v13 (base before pList, 83) -- both worse than v7 (78). 30+ distinct compiled
experiments total (structural fixes + declperm 120 + orderings + long-long/width/register/
explicit-dividend). The residue is the pScene(r6 ROM/r5 mine) <-> base-dividend(r5/r6) register
swap: the dividend is an UNNAMED temp mwcc colors independently, so declaration order cannot
reach it. Genuine register-coloring tie of the bb58 class, but SIZE-EXACT with fully-correct
structure + instruction mix. HELD build/try/ov011/cff0.c (v7), documented, NOT parked.

NEXT: cff0 stays held. Its direct dependency cda0 (520/9, called 3x by cff0 -- the actual blit)
is the next frontier function to advance the port; the c3a0 transition needs {bb58 held, cff0
held size-exact, cda0}. Consider cda0 next iter (call-rich -> more matchable per session pattern).

## 2026-07-29 iter 11: integrated 15 ov009 tile funcs; cff0 -> SIZE-EXACT (structural cracks)

INTEGRATED (user asked why the ov009 staging peers were not wired in): 15 byte-exact real-C
ov009 tilemap/menu blit functions from staging -> src/overlays/ov009/calls/ (cd7c, cfbc,
d224, d924, dc00, dfcc, 52dec, 52f98, 530c4, 53404, 54558, 54924, 54b58, 556e4, 557dc).
d924 = the core tile copy (clip vs 32-row grid, copy/clear source tiles, mark dirty slot).
Gate 306/0, committed 4ea8277be + progress 058003db3, PUSHED (last push had been 70 min).
No shadows; delinks also synced c884/c5e4/02058e88 asm_stubs->calls (config lag from prior
commits -- origin delinks had been pointing at deleted stubs).

FRONTIER function cff0 (Ov011 title tag-run advance, 552B/10 relocs, c3a0 dependency):
BROUGHT FROM BROKEN 560B -> SIZE-EXACT (byte diff @0x11), 78 masked diffs, correct instr MIX.
Four structural cracks landed: (1) stm sp,{r6,r7} at cda0 needs tagRes declared before param;
(2) the pText==0 dim=8 arm must BRANCH (nest `if(pText!=0){..}else{dim=8}`) not predicate;
(3) guards `accum<=0`/`span<=0xf1` (cmp #0/#0xf1; bgt) not `<1`/`<0xf2`; (4) ent=pList+4 early
+ pane before base -> globals-base into scratch r2 (92->78). RESIDUE: pScene(r6 ROM/r5 mine)
<-> base-dividend(r5/r6) register swap under tight top pressure (r0-r3 all live) + div/pane
schedule -- same coloring-tie class as bb58/c6fc/c190 but FULLY correct structure. HELD
build/try/ov011/cff0.c size-exact, documented, NOT parked.

bb58 (title-slot interpolator): re-attacked this iter -- x/y-before-tbl (+4 worse), long-long
return of func_0202060c (correct prototype, folded in, 136 inert), short x/y (139 worse),
register hints inert. Still SIZE-EXACT 136-diff coloring tie. func_0202060c IS `long long`
(confirmed vs the tree). HELD build/try/ov011/bb58.c.

NEXT: cff0 is the frontier (size-exact, held). Its remaining sibling dependency chain is
cda0 (520/9, called by cff0). Other fresh ov011: cda0, d6a0(284/7), dac8(200/7), da60(104/2).


## 2026-07-29 iter 10: bb58 confirmed register/scheduling tie (permuter proxy diverges)

Ran the permuter on the SIZE-EXACT bb58: base score 4860 -> descended to 4130 (~3978 iters)
but its 4130 "best" is 632B/147 real diffs by verify_idx -- WORSE than the size-exact base
(136). Proxy DIVERGES (the c190/c6fc pattern) -> bb58 is a genuine register/scheduling tie,
NOT permuter-crackable. HELD size-exact build/try/ov011/bb58.c. Manual levers exhausted
(branch/switch got it size-exact; int-return worse; 3 decl-orders inert; scheduling).

★ SESSION PATTERN (iters 4-10), now firm: the ov011 title cluster splits cleanly --
CLEANLY-MATCHABLE = simple algorithmic by-name functions (c884 fade tick, c5e4 fade-out tick;
BOTH MATCHED+pushed via switch-dispatch + by-name idiom + operand order); TIE-BOUND = anything
with heavy register pressure / MMIO / scheduling (d508, be38, c190, c2fc, c6fc, bb58, d7bc --
all size-exact-or-close register/scheduling ties, permuter proxy diverges on each). To keep
landing byte-exact matches, pick the SIMPLE algorithmic fresh stubs, not the complex ones.
Remaining fresh: cff0(552/10), cda0(520/9), d6a0(284/7), dac8(200/7), da60(104/2). NEXT:
screen a smaller/simpler fresh stub (da60 104B or dac8 200B) for the c884/c5e4 clean-match
pattern.

## 2026-07-29 iter 9: bb58 -> SIZE-EXACT (from broken); register/scheduling tie

bb58 (title-slot position interpolator, c3a0 dependency) brought from +4/broken to
SIZE-EXACT (byte diff @0x1E, 136 register+scheduling diffs). Two cracks: (1) the px/py
finalize KEEPS `(short)(((x0+px)*0x10000)>>0x10)` -- lsl#16 + signed >>0x10=asr#16 (disasm
proves asr, the decompile's lsr is WRONG); removing the (short) folds the shifts (-16).
(2) direction `(a<b)?2:(a>b)?0:1` NOT `(b<a)` -- same cmp operands so mwcc reuses the flags
(movlt;blt;movgt;movle) instead of re-comparing (that re-compare was the +4).
RESIDUE: uniform "+1 register shift" (pane->r5 ROM/r4 mine, cascading through 12 locals) +
a scheduling diff. int-return WORSE (bb58 genuinely void, NOT the c884 crack); 3 decl-order
variants inert (136-139). Register-coloring tie of the c6fc/c190 class, bigger. HELD
build/try/ov011/bb58.c size-exact, documented, NOT parked. Gate 306/0 (no src edits).

FRESH ov011 stubs still open (algorithmic candidates): cff0(552/10, c3a0 dep), cda0(520/9),
d6a0(284/7), dac8(200/7), da60(104/2). NEXT: crack bb58's +1 shift/scheduling, or open a
fresh cleanly-matchable one (the c884/c5e4 pattern) like cff0 or a smaller movie-state helper.

## 2026-07-29 iter 8: pushed c884+c5e4; started bb58 (c3a0 dependency) at +4

PUSHED the 2 pending commits (c884 fade tick + c5e4 fade-out tick + progress) ->
origin/main 384be8a68..61e6b9c2d (last push was 61 min, gate 306/0). Staging unchanged.

Surveyed the next fresh function c3a0 (transition handler, 576 B): it tears down the fade
(calls cad8) then repositions title slots in two loops (Slot_Get/SetPosition/Visible),
using &local_2c -- so it risks the SAME &pos scheduler tie c190 has. Its dependencies
bb58(0/1) and cff0(0/1) are fresh stubs -> per play-order they come first.

SELECTED **func_ov011_0205bb58** (title-slot position interpolator, 644 B, dependency of
c3a0). First draft (by-name access) DIFIERE 648 != 644 (+4, one instruction over) with
pervasive register renaming + a table-copy scheduling diff. HELD build/try/ov011/bb58.c
with re-attack notes (px/py lsl16;lsr16 finalize; tbl[] copy order; pane register). NOT
parked. NEXT: refine bb58 to MATCH (it's algorithmic, reloc-masked -- 4x func_0202060c +
b8f8/b814), then cff0, then c3a0.

## 2026-07-29 iter 7: c5e4 MATCHED (fresh fade-out tick) -- the fresh vein pays off

**func_ov011_0205c5e4 = Ov011_TickTitleFadeOut is DONE** (byte-exact, 280 B, calls/, stub
removed, gate 306/0, committed 80f2c2417 + progress 61e6b9c2d; Ghidra renamed + saved).
Push HELD (last push 59 min ago; goes out next iter, hourly cadence). Title fade-out tick:
interpolates alpha from the frame timer (same func_0202060c as c884), drives both engines'
master brightness to -alpha, advances state (5/6) once the fade completes + func_02034014(0)
clear, dispatches data_ov011_0205e8cc[mode](), forwards to the transition when mode==3.

★ **THE by-name-vs-cached DISTINCTION (decides caching per function):** c884 needed a CACHED
`u8 *pScene` local; c5e4 (and cb18) need BY-NAME `data_ov011_0205e960.pScene->...` on EVERY
use, because the ROM RELOADS the globals pointer each time (its `ldr [pool]` for the globals
appears 6x). Caching pScene/timer here promoted them to callee-saved regs (r4/r5), inflated
the push, and pool-loaded the field offsets -> 40 B short + broken. Look at the ROM: repeated
`ldr rX,[pool_globals]` = access by name; a single load kept in a reg = cache it. Two more
cracks landed it: main branch already fine; the fade-complete threshold must be written
timer-first (`nTimer >= end`) for `cmp timer,end; blo` (reversed gives `cmp end,timer; bhi`).

**Validated strategy: the FRESH ov011 stubs are matchable; the held ones are register ties.**
c884 + c5e4 both matched (algorithmic, reloc-masked). The held cluster (d508/be38/c190/c2fc/
c6fc) are register/scheduler ties. c6fc HELD size-exact (register coloring, param_1 class).
NEXT fresh algorithmic candidates: c3a0(576/15, call-rich), bb58(644/8), cda0(520/9),
cff0(552/10), d6a0(284/7), dac8(200/7), da60(104/2). d324 is MMIO (tie-prone).

## 2026-07-29 iter 6: opened a FRESH fade sibling (c6fc) -> SIZE-EXACT; c190 confirmed tie

Rather than re-grind the corpus-proven c190 tie, surveyed the 10 FRESH ov011 stubs (never
attempted) and picked by PLAY ORDER: **func_ov011_0205c6fc = Ov011_ApplyPaneFade** -- the fade
APPLY function, direct sibling of the just-matched fade tick c884 (both called by the fade
dispatcher cad8; cad8 calls c6fc twice with pane index 0/1). Fresh, algorithmic (same
func_0202060c interp as c884).
- **c6fc: SIZE-EXACT** (byte diff @0x9, 35 masked diffs = pure register renaming). Two cracks
  from -8: invert the main branch (`if(timer>=end){timeout}else{interp}` -> timeout is
  fall-through, matches ROM `blo interp`); both state dispatches as `switch` not if/else-if.
  Residue: param_1 lands in callee-saved r7 (mwcc) vs caller-saved ip (ROM) -- its live range
  is promoted. int-return WORSE (56, not the c884 crack); permuter proxy DIVERGES (1015 "best"
  = 388B/42 real, worse than the size-exact base); fnpair-early reorder = 40. HELD
  build/try/ov011/c6fc.c, size-exact. Re-attack: shorten param_1's live range to keep it scratch.
- **c190**: CONFIRMED genuine scheduler tie. Corpus: matched func_ov008_0204da6c has &pos-late,
  func_ov008_0204d8bc (identical call C) has &pos-early -> the &pos schedule is provably NOT
  source-controllable (depends on wider register context). Permuter proxy diverges. Held.

FRESH ov011 stubs still unopened (play-order-order-ish, algorithmic candidates first): c5e4
(280B/9), bb58(644/8), c3a0(576/15, call-rich), cda0(520/9), cff0(552/10), d6a0(284/7),
dac8(200/7), da60(104/2); d324(484/11) is MMIO display-config (tie-prone). NEXT: finish c6fc's
param_1 register lever, or open the next fresh algorithmic sibling (c5e4).

## 2026-07-29 iter 5: PERMUTER-SCREENED the held ov011 cluster -- c884 was the only crackable one

Used the permuter as a SCREEN across the held ov011 title cluster. Verdict: the display/GFX/
handler ties are GENUINE (permuter cannot crack them); c884 (algorithmic, return-value) was
the exception.
- **d508** (EmitSlotGfx): permuter base 1220 -> plateau 1020 over 9040 iters. int-return WORSE
  (48 diffs). Genuine register-rotation tie. HELD BESTd508.c.
- **be38** (BuildTitleLayout0): permuter base 1090 -> plateau 1060 over 5300 iters. Genuine
  two-bank-display-RMW rotation tie. HELD BESTbe38.c.
- **c190** (Mode2Teardown, 364 B): base 13 diffs @0xDD, the "&pos scheduler coin-flip" (eager
  `add r2,sp` vs ROM lazy). ⚠ **PERMUTER PROXY DIVERGES FROM THE REAL GATE HERE**: its
  score-525 "best" (hoists `pos.nX` early) is 15 real diffs by verify_idx, WORSE than the base
  13. So the permuter's descending score is NOT tracking byte-exactness for c190 -- the base
  c190.c is the closest form. HELD. Re-attack: delay the &pos stack-addr computation (make the
  ROM's lazy `add r2,sp`), measured by verify_idx not the permuter score.
- **c2fc** (116 B): int-return inert, residue @0x5 (entry register). HELD BESTc2fc.c.

★★ **PERMUTER USAGE RULE (learned this iter): the permuter score (difflib/levenshtein on the
objdump) is a PROXY that can DIVERGE from verify_idx.** A descending score is only a real lead
if it descends to 0 (c884) or if the best-output form actually has fewer verify_idx diffs.
ALWAYS re-check a permuter "best" with verify_idx before trusting it. A plateau (d508/be38) or a
proxy that diverges (c190) both mean the permuter is not going to crack it -- it is a genuine
tie, hold it. Harness templates kept at build/try/perm_{d508,be38,c190,c884}/ (base.c comment-
free, target.o = delinked stub, run with the permuter-venv python).

**Net for the ov011 title scene:** the scene is semantically complete for the port (movie tick
ae4c, teardown b034, title tick cb18, fade tick c884, pane blitter b9f4 all MATCHED; the held
GFX/handler ties are port-usable). The remaining 18 stubs' byte-exact gaps are genuine mwcc-139
register/scheduler ties in DS 2D-engine display code. NEXT: either a manual &pos lever on c190
(closest, 13 diffs), or -- pending the user's steer -- a fresher matchable vein, since the
title cluster is now confirmed tie-bound except where an algorithmic lever exists.

## 2026-07-29 iter 4: c884 MATCHED via the DECOMP-PERMUTER (return-type lever) -- reusable

**func_ov011_0205c884 = Ov011_TickTitleFade is DONE** (byte-exact, calls/, stub removed,
gate 306/0, committed 42bc4a053 + progress 384be8a68, PUSHED; Ghidra renamed + int
prototype + Ov011FadePane struct saved).

**THE CRACK: the function RETURNS int, not void.** After ~28 manual experiments across
every axis left it instruction-exact with a stubborn "avoid-r0" register residue in two
low-pressure spots (switch state-temp + case-3 completion), the decomp-permuter cracked
it in ~3 iterations: base score 565 -> it tried `volatile int` return -> verify_idx MATCH.
Plain `int func_ov011_0205c884(void)` (no return statement) is byte-exact. The int return
reserves r0, producing the ROM's r1..r4 temp numbering. The MATCHED caller cad8 declares
`extern void ...` and discards the result -- separate TUs, no conflict. This is rescue #5
(void->non-void reserves r0) BUT I wrongly dismissed it because (a) the ROM sets no
explicit return and (b) the matched caller says void -- both are NON-reasons.

★★★ **REUSABLE WORKFLOW: on an INSTRUCTION-EXACT residue that is pure register renaming,
run the decomp-permuter EARLY -- do not grind 28 manual axes first.** Harness template at
build/try/perm_c884/ (base.c comment-free, compile.sh = mwcc 3.0_patch4, target.o = the
delinked asm-stub .o, settings.toml). Run with the venv:
`staging/_codex_tools/permuter-venv/Scripts/python.exe staging/_codex_tools/decomp-permuter/permuter.py <dir> --best-only --stop-on-zero -j 6`.
It explores return-type/qualifier/statement-order micro-transforms that are trivial to
dismiss by hand. (It found 405<565 fast then plateaued -- the BEST output dir source is
where the winning transform shows; verify it with verify_idx, the permuter score is only
a proxy.)

**IMPLICATION for the held ov011 cluster:** d508 (INSTRUCTION-EXACT, "pure register
rotation"), be38 ("pure register rotation"), c190, c2fc, d7bc are the SAME profile c884
had. Re-attack each with the permuter + the return-type lever. Several ov011 handlers may
be non-void (fade/state handlers whose result the dispatcher discards). NEXT: point the
permuter at d508 (closest -- size+instruction-exact), then the case handlers.

Gate 306/0. 18 ov011 stubs remain.

## 2026-07-29 (10m /loop, port-first) -- ov011 movie-state stubs: TWO held at near-match

Frontier UNCHANGED: ov011, the movie/title scene. This session worked the reloc-rich
movie-state stubs the prior handoff flagged (reachable from ae4c). KEY FINDING: those
"reloc-rich = matchable" stubs split into TWO classes -- **display-config (MMIO-heavy)**
and **algorithmic (call-heavy)**. The MMIO ones are tie-prone in their register-juggling
tail; the algorithmic ones reach instruction-exact but hit register-coloring ties.

- **func_ov011_0205d7bc = Ov011_SetupTitleBackgrounds** (676 B, 25 relocs): body (all 24
  reloc-masked calls + tilemap loop) byte-exact; residue = the 9-line dual-engine WINDOW
  register tail. ROM anchors 0x04000048 + 0x0400104a (0x1002 apart, DEFEATS mwcc CSE) +
  derives WIN0V from the 0x46 constant + splits WININ 0x3f into two ORs. Clean struct = -16
  (too optimal, CSE'd sub ptr); raw pointers = address-synthesis pathology. No corpus
  precedent for dual-engine window setup. HELD build/try/ov011/BESTd7bc.c (full re-attack notes).
- **func_ov011_0205c884 = Ov011_TickTitleFade** (596 B, 8 relocs): INSTRUCTION-EXACT
  (byte-diff @0x11). Whole residue = a uniform "+1 / avoid-r0" register-coloring shift in
  the switch state-temp and the case-3 completion block (the ROM reuses the dead a0 reg r4
  for the constant 0; mwcc-139 numbers these caller-saved temps one lower). Levers that
  worked: switch (not if/else), `if(end<=timer)X=0x10;else compute`, pane addr
  `base-const + idx*stride`, decl order `u32 timer; unsigned notbit,bit;`, NO explicit `g`.
  **ROUND 2 (2026-07-29 iter 2): ~11 more experiments, all inert/worse -> total ~23 across
  EVERY checklist axis; residue invariant at 27 masked diffs.** Inert: explicit state local,
  G2x int/void, explicit g, `register`, func_0202060c int/long-long, nested completion,
  reuse-a0-as-0. Worse: typed-struct by-name (+8), local_24[3], short alphas, int timer.
  Cross-checked against matched sibling cb18 (it uses typed by-name -> worse here, so c884's
  ROM used the cached-pointer form). c884 is a GENUINE b814-class register-coloring tie;
  HELD build/try/ov011/BESTc884.c, blocker reported, semantically complete + port-usable.
- d324 (Ov011_ConfigureDisplayForMovie, 484 B) assessed = MMIO-dominated (VRAM banks/DISPCNT/
  BG control both engines), same tie class as d7bc's tail; not started.

STAGING: 15 ov009/*.c all verify byte-exact ARM (peer lane's save/menu work, solid) but are
OFF the ov011 frontier AND ov009/delinks.txt is mid-integration by that peer lane -- NOT
integrated (would conflate two lanes' uncommitted delinks). For the ov009 lane owner.

Gate 306/0 unchanged (no src/ edits; only build/try touched, gitignored). Nothing committed.
NEXT: crack c884's avoid-r0 temp numbering (closest), or d7bc's CSE-defeat window anchoring.

## 2026-07-29 SESSION HANDOFF (loop cancelled, fresh session next) -- READ THIS FIRST

**What matched this run:** `func_ov011_0205b9f4` = Ov011_BlitPaneTiles (byte-exact, in calls/, on
origin/main). Its crack (clamp the signed param FIRST) RETIRED the whole "ov011 GFX cluster needs
retail mwcc 3.0>=140" theory -- the project compiler (3.0 build 139) is correct; these are
SOURCE-SHAPE problems. See codegen-cracks.md tail.

**The ov011 title-tick cluster is TIE-DENSE and is the reason this session stalled.** After
b9f4, every function I touched there is a genuine mwcc register/scheduler tie that resists source
steering after 10-35 experiments + corpus + build sweep EACH. All HELD at best form in
build/try/ov011/ (documented headers, re-attack angles), NONE parked/nonmatching:
- `c190` (Ov011_Mode2Teardown, mode-2 handler): 5 REAL diffs, a 1-instruction &pos scheduler
  coin-flip (eager `add r2,sp` vs ROM lazy). Ghidra-named + plate saved. build/try/ov011/c190.c.
- `c2fc` (mode-3 handler): 13 diffs, a reg-alloc puzzle (ldm {ip,lr}, &data_e960 in r2 vs r1,
  constant scheduling). Small (116 B). build/try/ov011/BESTc2fc.c.
- `d508` (Ov011_EmitSlotGfx): 42 diffs, instruction-exact, coloring permutation (entry->r4 vs r8),
  build-swept. build/try/ov011/BESTd508.c.  Plus b340/ac40/be38/b814 (same cluster).

**STRATEGY for the next session (agreed with the user):** DON'T re-grind these ties. Hold them.
Work FRESH, matchable veins where the corpus matches reliably -- either (a) the RELOC-RICH ov011
stubs the skill flags as high-yield (reloc-masked bl's hide regalloc noise): d7bc (25 relocs,
reachable from ae4c), c884 (8, from cad8), d324 (11, from ae4c), d7bc/d6a0/dac8 (ae4c movie state);
or (b) a fresher menu/gameplay milestone (ov000/ov008/ov002). Avoid the tiny/few-reloc
mode-handlers -- they are 1-instruction ties.

Gate 306/0. Tree clean (only ov000/ov009 delinks.txt from a peer lane, untouched). b9f4 pushed.

## 2026-07-29 iter 16: d508 HELD after exhaustive investigation; advance play-order to c190

**func_ov011_0205d508 is HELD at best form** (build/try/ov011/BESTd508.c, 42 register-field diffs,
NOT parked/nonmatching/deferred). ~49 compiled experiments across 4 iterations + a full build
sweep: it is SIZE-EXACT + INSTRUCTION-EXACT (same instruction stream and order, only register
FIELDS differ) and the sweep proves every 2.0/3.0 build incl 3.0_patch4 (=139, correct) gives the
same output -> SOURCE-SHAPE, not a build issue. Exhausted axes: 48 decl x init combos, share-half,
no-cache-pScene, struct-for-base, entry/disp pointer types, global-as-struct, volatile, register,
arity (all callees verified), base split, arg local, hasE split, inline helper. The residue is a
pure coloring permutation: entry lands in r4 (ROM r8), which cascades slot/half; rooted in mwcc
deferring the &data_e960 pool-load to ip instead of interleaving it into the template copy (ROM
uses a scratch arg reg early). No source lever flips it. Re-attack angle for later: force the
pScene load onto the critical path early / find the idiom that keeps ip free for the copy.

**Play-order correction:** d508 was selected by descending the b340->d508->b9f4 RENDERING chain
(vertical-slice priority 9). The strictly-earliest unresolved play-order function is the tick's
mode-2 STATE HANDLER **func_ov011_0205c190** (priority 2). The tick cb18 dispatches on
pScene->nMode: case0->be38(held), case1->c074(done), case2->**c190**, case3->c2fc. c190 is a
teardown/transition handler (frees both pane tilesets via NNSi_FndFreeFromDefaultHeap,
reconfigures 2 VRAM banks via func_0201ef9c, resets display MMIO 0x4000000/0x4001000, clears the
curPane flag) -- algorithmic, NOT a coloring tie. Selecting c190 now; d508 remains held for a
future crack. Gate 306/0.

## 2026-07-29 iter 12: b9f4 MATCHED byte-exact -> the "build-tie" was WRONG; cluster reopened

**func_ov011_0205b9f4 = Ov011_BlitPaneTiles is DONE** (byte-exact, wired to calls/, stub removed,
gate 306/0, committed, Ghidra named + params + Tile struct + plate saved). This RETIRES the
"ov011 GFX cluster needs retail mwcc 3.0>=140" theory (iters 6/11 below): the project compiler
(3.0 **build 139**, 17,662 matches) produces it byte-exact once the SOURCE SHAPE is right.

THREE cracks carried it, from a -4 B / 82-diff residue to MATCH:
1. ★ **Clamp the signed param FIRST** (`if (dstRow < 0) dstRow = 0;` as the very first statement,
   before reading the pane record). This alone dropped 82 -> 16 diffs AND fixed the size. It makes
   mwcc keep the pane pointer (param_1) in a callee-saved reg (`mov fp,r0` first) across the loop
   instead of spilling it -- the ENTIRE register cascade flips from this. The prior analysis
   (param_1's split live range, LICM tie-break) was the correct diagnosis; the FIX is to give the
   param_4/movmi its own early flag-set so the allocator commits param_1 to fp.
2. **Declare the loop counter before the running pointer** (iVar7 before puVar8): 16 -> 10 diffs,
   fixes the r4/r5 assignment.
3. **Advance the running pointer before bumping the counters** in the loop tail: 10 -> MATCH,
   fixes the pane-reload scheduling.
Plus the 5b array crack from iter 9-11 (tiles as `Tile{int px[16]}`) which had removed the size gap.

⚠⚠ **IMPLICATION: b340/d508/ac40/be38/b814 are almost certainly ALSO matchable, NOT build-ties.**
They were parked on the same "register rotation / need 3.0>=140" call that b9f4 disproved. d508 is
INSTRUCTION-EXACT (size-exact, pure register rotation) -> the closest; re-attack it with the
clamp-order / decl-order / tail-order cracks. NEXT TARGET: **func_ov011_0205d508** (Ov011_EmitSlotGfx,
348 B, 8 relocs), b9f4's caller -- going back UP the b340->d508->b9f4 dependency chain.

## 2026-07-29 iter 11: b9f4 SOURCE-SHAPE SPACE EXHAUSTED -> same build-tie as the cluster (RETRACTED above)

Prompted by the user challenging the "build-tie" calls, re-attacked b9f4's register residue with
every source axis: `register` (inert -O4), 4 decl orders, Ov011Tileset struct, param_1 as
SlotObj* struct pointer, loop-stride form -- ALL byte-identical (368, 87 diffs). Only the two
clamp cracks + the param_1-reload moved it (376->368, +12). The residue is the pure register
coin-flip (puVar5 -> callee-saved -> param_1 spilled) shared with the whole title cluster. So
b9f4, though algorithmic, is the SAME build-version tie as b340/d508/ac40/be38/b814 -- retail
mwcc 3.0>=140. build/try/ov011/ shows the siblings were each worked with dozens of experiments,
so this is not a premature call. HONEST STATE OF THE TITLE FRONT: byte-exact is blocked on the
retail compiler for the whole GFX/layout cluster; but for the PC PORT the tick is semantically
COMPLETE (b340/d508/b9f4/b1bc all decoded, named, struct'd, port-usable C in build/try). NOT
parked. Gate 306/0.

## 2026-07-29 iter 9: b9f4 down to +12 B (two clamp cracks; residue = register alloc)

Read the full b9f4 ROM disasm and landed two cracks: (1) `if(uVar4<=9) iVar3=9; else iVar3=10;`
-> the ROM's single `cmp #9; movls #9; movhi #0xa` (two ifs gave two cmps); (2) second clamp
`(param_4+uVar10) >= 0x1a` -> `cmp #0x1a; movge` (0x19< gave cmp #0x19/movgt). Also confirmed the
loop stride MUST re-read via param_1 (`*(int*)(param_1+4)+2`, 2 instrs) -- the cached puVar5[1]
form (1 instr) can never match; reverted it. Now 368 (+12, was +20). Residue (~87 lines) = pure
register allocation: the ROM PUSHES r3 (10 regs) as scratch for puVar5, keeping param_1->fp for
the loop reload; mine pushes 9, keeps puVar5->r4 (callee-saved) and SPILLS param_1 (frame 0x1c vs
0x18). Inlining puVar5 was byte-identical (inert). NEXT: reduce loop-invariant spills / bias
puVar5 to a temp so mwcc keeps param_1 in a reg. Algorithmic, NOT the GFX build-tie -> steerable.
BESTb9f4.c, NOT parked. Gate unchanged 306/0.

## 2026-07-29 iter 8: b9f4 matchable carve at +16 B (register-alloc residue)

Continued func_ov011_0205b9f4 = Ov011_BlitPaneTiles. Improved 376 -> 372 (-4 B, now +16) by
routing the loop row-stride through the cached puVar5 local (`puVar5[1]`) instead of re-reading
*(param_1+4)+2. Residue (~93 lines) is register allocation: ROM keeps param_1->fp/param_3->sl/
param_4->sb and spills only param_2; mine spills param_1 too (frame 0x1c vs 0x18). Plus a clamp
that shares one `cmp #9` in the ROM but emits two in mine. Algorithmic + reloc-masked, NOT the
GFX build-tie -> steerable; next levers: single-cmp clamp + keep param_1 in a callee-saved reg.
BESTb9f4.c, NOT parked. Gate unchanged 306/0. Frontier reality: the ov011 title cluster is
heavily build-tie-blocked (b340/d508/ac40/be38/b814); b9f4 is the one live matchable straggler.

## 2026-07-29 iter 7: d508 deps -- b1bc ALREADY DONE, b9f4 in progress (algorithmic, matchable)

Worked down d508's deps. **func_ov011_0205b1bc was ALREADY matched+integrated in calls/**
(canonical real C, documents the bitfield-nibble crack) -- I re-derived it (MATCH, bitfield
lo:4/hi:4 gives the ROM's `lsl;sub..lsr` fold) before noticing the existing calls/ file, then
removed my dup. Lesson: check calls/ AND auto/ before decompiling a "stub" -- the asm_stubs
count did not include b1bc. **func_ov011_0205b9f4** = Ov011_BlitPaneTiles (356 B, 5 relocs:
3x MIi_CpuCopy32 + GFXi + globals) is the genuine next stub: a tile-row blitter (clamp, wrap,
split-copy, GFX enqueue). First draft DIFIERE 376 != 356 (+20 B); clamp expressed relative to
9; residue ~94 lines (register/scheduling shift, param_1-in-fp caching). ALGORITHMIC with
reloc-masked calls -> likely steerable like b1bc, NOT the GFX-cluster build-tie. Best form
build/try/ov011/BESTb9f4.c, NOT parked. Gate unchanged 306/0 (b1bc dup removed, tree clean).

## HELD -- 2026-07-29 iter 6 (cont.): dep func_ov011_0205d508 = SAME BUILD-TIE (instruction-exact)

User chose "hold b340, work its deps." Selected func_ov011_0205d508 = **Ov011_EmitSlotGfx**
(348 B, ARM, 8 relocs), the GFX slot-command emitter b340 ops 6/7 call. Decoded fully, Ghidra
renamed + Ov011GfxTemplate struct + plate comment SAVED. Brought to **SIZE-EXACT + INSTRUCTION-
EXACT** (348==348): two cracks -- (1) template as int[4][4] indexed [slot][k] gives the ROM's
`ldr rD,[base,slot,lsl#4]` (1D [16] adds 3 instrs); (2) `if(entry!=0){set}else{clear}` gives the
ROM's `beq` (==0-first inverts to bne). Residue = pure register rotation (72 bytes, all register
fields). **27-BUILD SWEEP is now DEFINITIVE**: every 2.0/3.0 build produces this same size-exact
"72 off" output, NO build reproduces the ROM's register assignment (1.2->352-56, dsi->340-44).
Decl-order/register/reorder all inert. d508 is instruction-exact -> the CLEANEST proof in the
cluster that the C is correct and only the register allocation needs retail mwcc 3.0>=140.
**FINDING: the whole ov011 title-GFX cluster (b340, d508, ac40, be38, b814) is the SAME build-
version tie, blocked on the same unavailable compiler.** Both b340 + d508 held in build/try
(BESTb340.c, BESTd508.c), NOT parked, port-usable. b1bc/b9f4 (d508's own deps) are the next
title-tick stubs but are almost certainly the same tie. Gate unchanged 306/0.

## HELD (BLOCKED ON RETAIL COMPILER) -- 2026-07-29 (10m /loop, iter 6): func_ov011_0205b340

Iter 6 closed the remaining axes (all byte-identical -8): const-e (aliasing), 5 local decl
orders, idx u16, idx<<4, hoisted nTimer, scene int-vs-u8*. **~28 distinct compiled experiments,
every checklist axis covered; d508 arity=4 verified from disasm.** The residue is a pure
scene(r0)<->timer(r1) register rotation mwcc 139 resolves toward r1 (ldm-merge preference); the
-8 SIZE gap is a consequence of that swap (retail 3.0>=140 -> scene r0 -> size-exact 1236). Same
concrete missing requirement as siblings ac40/be38/b814: **retail mwcc 3.0>=140, which we do not
have.** Per the skill's blocked-protocol: BEST stays in build/try (NOT parked, NOT nonmatching),
evidence recorded, HELD for the user's decision (supply the retail compiler, or authorize
parking). b340 is semantically complete + port-usable. Gate unchanged 306/0.

## IN PROGRESS -- 2026-07-29 (10m /loop, iter 5): func_ov011_0205b340 -- semantic layer DONE, byte-exact blocked on retail mwcc

Iter 5: verified func_ov011_0205d508 arity = 4 args (r0..r3, void) from its disasm -> my
prototype is correct, arity axis closed. Case-block reorder (case 10 before 8/9) = -12, worse
(mwcc block layout != source order). Completed the Ghidra semantic layer: Ov011_TickLayoutAnimator
rename + Ov011AnimEntry struct + plate comment, ALL SAVED. KEY: the -8 B is now fully attributed
to scene->r1 (ROM: scene->r0). If scene were in r0, the COND would not ldm-merge (+1 instr) and
one reload pattern would differ (+1) -> 1236 exactly. So the -8 SIZE gap is a CONSEQUENCE of the
register swap, not a separate source bug -> consistent with a pure build-version regalloc tie:
retail 3.0>=140 allocates scene->r0 (size-exact 1236); build 139 allocates scene->r1 (1228).
mwcc 139's scheduler+allocator merge the two global reads (timer->r0) no matter the source
spelling; the by-name form that would force reloads spills. ~19 distinct experiments; all callee
arities + void return verified; no build reaches 1236. This is the same concrete missing
requirement as siblings ac40/be38/b814: retail mwcc 3.0>=140. b340 is SEMANTICALLY complete and
port-usable (the -8 C is semantically exact). NOT parked; BEST stays in build/try. Awaiting user
decision (provide retail compiler, or authorize parking). Gate unchanged.

## IN PROGRESS -- 2026-07-29 (10m /loop, iter 4): func_ov011_0205b340 at -8 B, build-tie fingerprint

Iter 4 (key finding): the matched sibling cb18 accesses this same globals object as
`data_ov011_0205e960.pScene->field` BY NAME (no cache) with the full Ov011Scene struct --
byte-exact because cb18 does NOT loop. b340 DOES loop, so by-name reloads pScene on every
access: v9 (all by-name) +84, v10 (cached g ptr, g->pScene->field) +84, both SPILL (60+ ldr
storm from aliasing reloads). So caching scene in a LOCAL (v8) is the ONLY non-spilling form
and it is -8 with scene stuck in r1. The 2 missing instrs ARE the pScene reloads v8's cache
elides -- but adding them (by-name) triggers the storm. That dichotomy (cache=-8/scene-r1 OR
by-name=+84; no middle with build 139) is the build-version-tie fingerprint, same class as
siblings ac40/be38/b814 ("need retail mwcc 3.0>=140"). ~17 distinct compiled experiments now;
none reach 1236. NOT parked -- best form (v8, struct+cached local) stays in build/try. Next:
a few remaining axes toward the 30-experiment threshold, but the evidence for the retail-build
requirement is strong. Gate unchanged (build/try + Ghidra struct only).

## IN PROGRESS -- 2026-07-29 (10m /loop, iter 3): func_ov011_0205b340 at -8 B, register-rotation residue

Iter 3: adopted the struct-globals form (Ov011Globals {int nTimer; u8 *pScene}) -- byte-
identical to the int-addr form but satisfies the struct rule. Created the **Ov011AnimEntry**
Ghidra struct (0x10 B: bOpByte{op:hi,flags:lo}, wDelta@4, bSub@8, nArg@c) and saved. Ran the
27-build sweep: **NO build reaches 1236** (2.0/3.0 -> 1228, 1.2 -> 1256-68, dsi -> 1108) --
inconclusive on the build-tie until the C is size-exact. Ruled out for scene->r0 this iter:
volatile-captured-in-local t (kills body ldm), struct-globals+u8* (byte-identical). The
residue is a scene/timer register ROTATION + 2 missing instrs in the case1/2 region (ROM
keeps 0x1093c in BOTH r5 and r10); signature matches sibling ties ac40/be38/b814 but the -8
SIZE gap means a source-shape fix is still open. NEXT: block-aligned case1/case2 disasm diff
to pin the 2 missing instrs. Full evidence in the file header. NOT parked. Gate unchanged.
Plate comment pending (bridge Swing error this iter).

## IN PROGRESS -- 2026-07-29 (10m /loop, iter 2): func_ov011_0205b340 at -8 B

Assigned-function mode on `func_ov011_0205b340` = **Ov011_TickLayoutAnimator** (1236 B,
ARM, 7 relocs), the title-layout command-list interpreter cb18 runs before its switch.
Ghidra renamed + saved. Best candidate `build/try/ov011/BESTb340.c`: **DIFIERE 1228 !=
1236 (2 instr short)**, mnemonic profile ldr -2 / add -1 / b +1.

BREAKTHROUGH this iter: the loop now ROTATES to match the ROM (bottom-tested, entry `b`,
bcc-to-body) by expressing it as a `while` whose continue-condition is
(timer>=limit && idx<cnt) -- codegen-cracks.md ~line 2566. Plus case 10 references the
global BY NAME to reproduce the return-path pool reloads. Path: v1 +60 (spill) -> v2
pointer-pairs -16 (spill gone, POINTER-PAIRS ARE LOAD-BEARING; raw offsets/offset locals
always re-spill) -> delta u16 -> rotated loop -> case10-by-name = -8.

SOLE REMAINING RESIDUE: a register coin-flip -- the ROM keeps scene in r0 (two `ldr` in
the COND), mwcc merges the two global reads into `ldm` (scene->r1) and threads scene
through r1 for the whole body. Dominant byte diff + the 2 missing instrs. Ruled out for
the split (all measured): limit temp, swapped compare (breaks poplo), volatile (+16),
idx-early (+32), register (inert), d-first (-12). NEXT UNTRIED: g as struct pointer
{int nTimer; Scene *pScene;} with named-member reads; or copy a matched rotated-loop
function's exact condition spelling. Full evidence in the file header. NOT parked.
Gate unchanged (only build/try touched -- gitignored).

## START HERE -- 2026-07-29 autonomous /loop (port-first play-order mode)

**User directive this session:** "incorpora todo lo que este match de staging y borra
lo ya integrado." Done and pushed:

- **INTEGRATED from staging (5 funcs, all byte-exact, gate DSD_OK=306 FAILED=0):**
  the ov009 save-slot / menu-element subsystem --
  `func_ov009_0205289c` Ov009_PollSaveTransfer, `func_ov009_02053554`
  Ov009_FillSaveSlotInfo, `func_ov009_020536b8` Ov009_TickSaveSlotPrep,
  `func_ov009_02053804` Ov009_MenuElementPress, `func_ov009_0205388c`
  Ov009_MenuElementRelease. Wired into `src/overlays/ov009/calls/`, Ghidra symbols
  renamed + saved. Commit `a955f9c1d`, pushed with the progress regen as `2328ef4ea`.
- **STAGING CLEANED:** deleted 34 already-integrated staging copies (28 ov000 + 6
  ov009). Remaining in staging and NOT integrated: `ov000/02059b14` (asm stub, the
  user's own function, untouched) and the 14 `ov003/*` (real C but re-verified DIFIERE
  in ARM this session -- off-frontier, left as candidates).

**Frontier UNCHANGED: ov011.** CURRENT EXACT FUNCTION still
`func_ov011_0205ac40` = Ov011_CreateScene, the documented 2-word fixed point
(`byte diff @0x138`). Iteration 11 added TWO ruled-out axes (full pScene cache ->
372 B proves the ROM re-reads globals->pScene; early bEnabled -> 6-register
prologue). Iteration 12 (this session) added a THIRD: the exact load-all-then-store
structure the ROM disassembly dictates (6 u8 temps, all loads before the stores) is
**464 B, one `ldr` short** -- it drops the globals reload, the same coupling as N=0.
All in `build/try/ov011/BESTac40.c`, kept there (NOT parked). ROM prologue fact:
globals addr in r3 across the whole setup, exactly three callee-saved r4/r5/r6, so any
`push` wider than `{r4,r5,r6,lr}` is a fast reject.

**TWO ov011 STATES MATCHED while the permuter runs on the constructor** (user asked to
continue in parallel):
- `func_ov011_0205ae4c` = **Ov011_TickMoviePlaybackState** (424 B, 27 relocs) -- the
  initial state the constructor hands back: polls the MobiClip stream each frame, and on
  finish tears the movie down and brings up the title. Byte-exact first real attempt; only
  fix was the canonical symbol `G2x_SetBlendBrightness_` for 0x02006bac. Scene flags at
  +0x23ac0 are a signed 1-bit bitfield (bit0 threadAvail read via lsl#31/asr#31, bit1 busy,
  bit2 lidClosed). Stream interface extends to +0x18 (init/open/close/start/unk/poll).
- `func_ov011_0205b034` = **Ov011_DestroyScene** (392 B, 19 relocs) -- the +8 teardown:
  unloads ov024, conditionally frees all resources, requests scene 9, nulls pScene. The
  overlay id must go through the pool as `&OVERLAY_24_ID` (absolute symbol), else 4 B short.
Both committed (gate 306/0), Ghidra renamed + saved, asm_stubs twins deleted.

**THEN `func_ov011_0205cb18` = Ov011_TickTitleMenu (648 B) MATCHED** -- the title/menu
per-frame tick. Three cracks (all in `codegen-cracks.md`-worthy territory, told in the
commit and the .c header): (1) scene-flag bits read as materialised signed shifts
`(flags<<0x1d)>>0x1f` to get the ROM's lsl/asr and keep the -1/0 live; (2) the fade
branch as an `else if` chain so the fade-in block is the fall-through; (3) the two
timerPair stores routed through a NAMED `u16 *tp = pScene->timerPair;` so mwcc allocates
the store value below the base and emits the `ldm` that loads {nTimer, pScene} together
-- that was the final 16-word residue. Committed (`8cd79add2`), gate 306/0, Ghidra
renamed. It went 110 -> 77 -> 16 -> 0 words across the session.

**`func_ov011_0205be38` = Ov011_BuildTitleLayout0 (case 0) CHARACTERISED as a
build-139-vs-retail regalloc tie** -- 532 B size-exact, 17 words, and the whole residue
is a PURE REGISTER ROTATION in the two-bank display RMW (instruction stream identical,
only r1/r2/r3 rotated). ~14 source forms tried; the closest (17) models the two engines
as an array of `DispBank` structs. Same class as func_ov011_0205ac40 (permuter-confirmed
unreachable). Best form + full evidence in `build/try/ov011/BESTbe38.c`. NOT parked (no
nonmatching/ file); advanced past per the 0205ac40 precedent -- it needs retail mwcc
3.0>=140, not another source form.

**CURRENT FRONTIER / NEXT FUNCTION: `func_ov011_0205b340`** -- the per-frame layout
animator cb18 runs BEFORE the switch (play-order-earliest unresolved). It is a 1236 B
COMMAND-LIST INTERPRETER: a `do-while` that walks 0x10-byte entries from a table
(`entry[0]` high-nibble `(b<<0x18)>>0x1c` selects one of cases 0-10), applying scroll and
position updates to both panes, with a second sub-switch on the same nibble and helper
calls into func_ov011_0205d508 / func_020326a8 / the Slot_/Stamp_ helpers. Pool datums:
DAT 0205b800/b804/b808/b80c are field offsets, 0205b810 is the globals pointer. 7 relocs.
Big and intricate -- treat as a multi-iteration carve; use a mnemonic histogram, not a
diff, on the first pass. AFTER it: the remaining switch builders c190 (case 2), c2fc
(case 3).

**DECOMP-PERMUTER now set up for this function** (user suggested it) at
`build/try/perm_ac40/` -- a working mwccarm 3.0_patch4 harness against the delinked
ROM object `build/delinks/.../func_ov011_0205ac40.o` as target.o. compile.sh is a
PYTHON script (the permuter runs it with `sys.executable` on win32, NOT bash) with
the project's exact flags; arch auto-detects arm32; `arm-none-eabi-objdump` (binutils
2.40) is the differ. Base score 865; after ~4.5k iterations the floor was 835 -- it
does not descend toward 0, consistent with the residue being unreachable in the
source-transform space with our compiler (the mwcc-build-hunt theory: retail is 3.0
>=140, which we do not have). Left running in the background to search further.
Also live, not parked: `func_ov011_0205b814`.

## START HERE -- handover, 2026-07-27 autonomous /loop session (port-first play-order mode)

Frontier: **ov011**, the scene that instantiates the title. 23 stubs left.
Gate: `DSD_OK=306 FAILED=0`, unchanged -- no `src/` edits, nothing committed or pushed,
so the tree is exactly as it was found.

**CURRENT EXACT FUNCTION: `func_ov011_0205ac40` = `Ov011_CreateScene`**, the ov011 scene
constructor -- point 1 of the vertical-slice order for this scene, PORT-REQUIRED.
**NOT PARKED.** Best form `build/try/ov011/BESTac40.c`.

**It is now 468 B -- SIZE EXACT, with the ROM's exact instruction multiset**, and after
iteration 2 the entire residue is **TWO ADJACENT WORDS SWAPPED**, 0x138 and 0x13c: the ROM
has `str r6,[sp,#4]` (`openParams.enabled`) then `strb lr,[r5]` (`name[0]`), and we emit
those two the other way round. Every other byte matches.

**The rule that got it from seven words to two** (now in `codegen-cracks.md`): mwcc emits
**stores in strict source order** -- it hoists loads freely but never reorders one store
past another. Splitting the copy after element N and putting the `enabled` store there
gives exactly N+1 differing words, a perfect line; N=1 is the minimum reachable. N=0 is the
ROM's order and is the single point that is NOT size-exact (464 B, one `ldr` short, because
mwcc then keeps the globals pool address in a register instead of re-materialising it).
So the two remaining words are the boundary between "the store is one element too late" and
"the allocator drops a reload". `tools/verify_idx.py` agrees with the local scorer:
`byte diff @0x138`, nothing else.

**Which reload, exactly** (iteration 3): the ROM loads the globals address from the pool
TWICE in that region because it overwrites that register with `pScene` (`ldr r2,[r2,#4]`,
destination == source) and must re-materialise the address for the stream chain. Every N=0
form keeps the address alive in a spare register and derefs it three times instead -- that
is the missing `ldr`. The N=0 orders that ARE size-exact (15 words) get the address right
but put the boolean in r2 instead of r6, so the store cannot sink: in the ROM r0-r3, ip and
lr are all busy across the copy, which is what forces the boolean into a callee-saved
register. Schedule and allocation each depend on the other here.

**Iteration 10 -- EXHAUSTIVE cross product, floor exactly 2, no byte-exact point.**
`crossac.py` builds the tail from scratch and crosses all four levers at once: 24 orders of the
four prefix statements x 7 positions for the `enabled` store inside the six element assignments
x 16 volatile-device subsets over the five candidate global reads = **2688 compiled points, 832
size-exact, floor exactly 2, none byte-exact**. The optimum is reached by six equivalent
configurations (orders RAPD and RADP, split=1, volatile on {12}, {9,12} or {12,13}) -- only the
stream read matters. Word count grows exactly linearly with the split position (2,3,4,5,6,7),
confirming the strict-source-order store rule across the whole space rather than on one axis.
**The answer, if any, is not a combination of these four levers. Do not repeat this cross.**

**Iteration 7 -- callee arity and prototypes, the check that was still missing.** Every
callee's real arity was read from matched call sites. One genuine surprise: `func_02024ee8` is
itself decompiled and its definition takes FOUR parameters while we declare two -- the exact
signature of the dropped-trailing-argument bug behind several rescues in the skill. It is NOT
the cause here: at the ROM's call site neither r2 nor r3 is written on that path, so that site
really passes two arguments. Measured anyway and all identical: two-parameter, explicitly
variadic, the callee's real types, and unprototyped. The other seven arities all match.
Also closed: inline accessor PAIRS applied to the store-correct order (mwcc folds them), and
the build infrastructure question -- per-file config maps compiler VERSION only, but the flag
axis is already covered in-source by `#pragma optimization_level`, so no build change is
warranted. Verified in BOTH modes (`--thumb` gives 316 != 468, confirming ARM).

**Iteration 6 -- CORRECTION to the iterations 3-4 framing, plus three half-solutions.** The
ROM's store position IS reachable in a size-exact form; what is not reachable is having it
together with the address handling. Three forms exist, each correct on a different axis and
none combinable: FORM 1 (this file, N=1) 2 words, everything right but the `enabled` store one
element late; FORM 2 (N=0, volatile on global reads 10 and 12, destination-pointer seed BEFORE
the store) 31 words, with `str r6,[sp,#4]` at 0x138 exactly and the boolean in r6 -- both halves
of the hard part -- but the globals address kept in a spare register; FORM 3 (N=0, volatile on
read 12) 15 words, address handling right, boolean and store wrong. FORM 2's mechanism is worth
keeping: seeding the destination pointer before the store lets mwcc hoist `add rX,sp,#8` early,
and that extra live value pushes the boolean into a callee-saved register, which lets the store
sink to the ROM's slot. Exhaustively swept under FORM 2's order: every 1-, 2- and 3-site volatile
combination over all 15 global reads -- only 12 are size-exact, all contain sites 10+12, all
score 31. Also closed: `volatile` on the `pScene` member and on the whole `extern` declaration
(both 488 B, seven forced reloads where two are wanted).

**Iteration 5 -- the residue is a characterised fixed point, not an untested axis.** A corpus
scan with the right filter returns 42 matched functions and `func_ov008_0204f930` has this exact
shape; its header already documents the device ("the volatile forces the reload; behaviour is
identical") as a `CTX`/`CTXV` macro pair, so the device is the tree's, not an invention. Applying
it site by site: the plain N=0 form is 460 B (TWO `ldr` short) and already destroys `&g` like the
ROM; each volatile device adds exactly one `ldr`; a single-site sweep over all 15 global reads and
a pairwise sweep over all 105 pairs yield exactly ONE size-exact N=0 point (31 words). The listing
shows why: once the stream read is forced, mwcc keeps `&g` alive in a spare register and puts
`pScene` in another, so the address is never re-materialised -- forcing the read and destroying the
address are mutually exclusive under this allocator.

Iteration 4 also closed: the globals-access spelling (struct member vs `data_X[1]` array
element, the form the matched tree uses elsewhere, vs a volatile array read) -- identical or
worse; `static inline` accessors for the stream address and the scene, with and without the
volatile, which mwcc folds into the caller so they are exactly the inline expression; and all
27 mwccarm builds on the N=0 form (no 2.0/3.0 build reproduces it; 1.2/sp3-sp4 reach 468 B but
201 bytes off, a different codegen era).
⚠ A corpus search for "the same pool word loaded twice with no call between" returns 97
matched functions but nearly all are a different phenomenon -- a function-pointer constant
returned from two switch arms. The filter matched the shape, not the mechanism; the right one
is `ldr rX,[rX,#k]` (a global's address overwritten by a deref of itself).

Iteration 3 also closed, all still 2 words or 464 B: N=0 with the boolean inlined, with
`register`, and with the stream pointer named/plain/absent across every seed position;
~430 points of the "loads hoisted above the store" family (1..6 temporaries x three types x
two boolean types x three stream-pointer positions -- **not one of them size-exact**); the
frame and the openParams reached through a pointer; **every struct-copy spelling re-tested
with the hoist in place** (still folds the stack address); and `#pragma optimization_level`
0..4, where 2, 3 and 4 are byte-identical.

Three things closed the previous 24-byte gap, all written up in `codegen-cracks.md`:
the `add rX, sp, #K` stack base comes from a NAMED destination pointer plus element-wise
assignment (a struct assignment always folds the address); the source array must be
`unsigned` or `-char signed` gives `ldrsb` where the ROM has `ldrb`; and the call-argument
address chain must be hoisted above the copy AND still reload, which a `volatile`-qualified
read of the globals pointer achieves.

⚠ Retracted from iteration 1: the "the six `strb` go through a `u8 *`, a character type that
aliases everything" explanation was needlessly exotic. mwcc does not reorder stores at all,
whatever their type.

**Do not re-run these -- all closed by compilation on the current form:** all 42 size-exact
orderings of the six statement blocks with the store before the copy (best 15 words); the
store-first skeleton with the destination-pointer seed in all five positions, a named source
pointer seeded in all six, 0-2 extra locals, `u8`/`int` temporaries hoisting 1..6 loads above
the store, and the argument written inline instead of through the local (19-32 words);
16 copy framings;
`memcpy`/`__builtin_memcpy`/`strcpy` (mwccarm does NOT inline them, all emit a `bl`); all
720 element orders; all 60 legal statement orders; both pointer-seed positions; 384 points
of bEnabled type x boolean spelling x declaration order/position; 5 argument spellings x 3
prototypes; and all 27 mwccarm builds (every 2.0/* and 3.0/* build is identical).

⚠ **THE PRAGMA AXIS IS VOID, NOT NEGATIVE.** A sweep of all 82 `opt_*` names extracted from
`mwccarm.exe`, both `on` and `off`, changes the output in exactly one case
(`optimize_for_size on`, worse). `scheduling`, `peephole`, `register_coloring`,
`opt_propagation` and the rest are accepted and ignored. "I set the pragma and nothing
changed, so that is not the cause" is not a valid argument with this compiler.

Ghidra was done in the same batch and saved: `Ov011_CreateScene` renamed and commented,
`Ov011StreamOpenParams` / `Ov011StreamInterface` / `Ov011MovieFrame` created, `Ov011Scene`
resized 0x21294 -> **0x2cf84** with `dwFlags`/`nArg`/`pResource`/`stream` at their verified
offsets, and the pool slot `arm9_ov011::0205adf4` typed `Ov011Globals *`.
That resize **resolves the open discrepancy** recorded on 2026-07-26: there is no gap and
no second base -- the scene is simply larger than its two panes.

Also in flight, NOT PARKED:

- `func_ov011_0205b814` -- the tile-row blit, `BESTb814.c`, score 12, size and relocations
  exact, residue is a three-way register rotation.

A third function, `func_ov000_02059b14`, is the USER'S -- they took it over personally
("continua con la siguiente, yo sigo con esta"). Its record is in `build/try/b14/BEST.c`.
Do not start on it without checking with them.

**Method note that paid off twice this session:** on a function with a SIZE gap, use a
mnemonic histogram against the ROM, not a diff -- one missing instruction shifts the whole
listing and makes the diff unreadable. That is what located both the boolean-normalisation
crack (worth 20 bytes on the constructor) and the remaining single instruction.


This is the living work queue for port-first matching decompilation.

It records scheduling and reachability. Verified runtime facts belong in
`game-flow.md`. Matching experiments belong in `build/try/`, not here.

Every session must verify this file against the current tree, Ghidra,
`build/func_index.json`, relocations and call sites before selecting work.

## FRONTIER 2026-07-27: `func_ov000_02059b14` (assigned by the user), then ov011

**CURRENT EXACT FUNCTION: `func_ov000_02059b14` = `Ov000_DrawMenuList`** (324 B, 10 relocs,
ARM, PORT-REQUIRED -- it is the redraw of the menu list, the last unresolved function in
ov000). **NOT PARKED, NOT IN `nonmatching/`.** Best form `build/try/b14/BEST.c`.

Session 2026-07-27 result: **a semantic error was found and fixed** -- the highlighted row
was being drawn with the title's style constant (0x821); the ROM's `ldr r2,[pc,#0x60]`
resolves to the pool word `0x02059c50` = **0x209**, the same style the ten list rows use.
Size and pool shape are identical either way, so only resolving the pc-relative target could
catch it. The rule is now in `codegen-cracks.md` and it applies project-wide.

Also corrected: the previous header argued that `#pragma scheduling off` being inert proved
the scheduler was not the cause. **mwccarm accepts unknown pragmas silently**, so that
argument was void and the scheduler is back on the table.

Residue: still six words, one window, a pure permutation (same instructions, registers and
immediates). The measured effect -- the two halves of the split base offset are adjacent at
`optimization_level` 0/1 and 7 apart from 2 upward -- plus the full closed-axis list and the
three perturbations that DO move the distance are recorded in the header of
`build/try/b14/BEST.c`. Read it before running anything.

Iteration 2 (same day) added: the `volatile` barrier axis is closed **by principle**, not just
empirically (volatile orders memory accesses, and the instruction that moves is pure
arithmetic -- see `codegen-cracks.md`); the compiler's own ~75 internal `opt_*` option names
were extracted from `mwccarm.exe` and none is settable as a pragma; -O1/-O2 are not the answer
because below -O3 mwcc rotates the loop with a pre-test guard the ROM does not have; and a
96-point systematic sweep of declaration order x loop form x pSel position, measured by
DISTANCE rather than score, found no size-and-score-exact point below distance 7.

⚠ **`staging/ov000/func_ov000_02059b14.c` appeared and was REJECTED**: it is an `asm` + `dcd`
stub under a decorative struct header. Its TYPE MODEL was better than ours and was adopted
(0x3c render surfaces, an 18-entry row array, int text handles) after checking it against
Ghidra -- where `Ov000SceneContext` already describes the whole object, so the earlier C
typedefs `Ov000ListSceneContext` / `Ov000RenderSurface` / `Ov000RowRenderEntry` were rivals and
are gone. `TileSurface` (12 matched files) and `Ov000Row` are the established names.
Ghidra: `Ov000_DrawListRows`, local typed `Ov000SceneContext *`, plate comment corrected, saved.

Gate: `DSD_OK=306 FAILED=0` (unchanged -- no `src/` edits since).

**AFTER IT:** ov011, below.

### Second ov011 function opened in parallel (user asked for it, 2026-07-27)

**`func_ov011_0205ac40` = the ov011 scene constructor** (468 B, 12 relocs, PORT-REQUIRED --
it is point 1 of the vertical-slice order for this scene). Candidate in
`build/try/ov011/BESTac40.c`, **448 B against 468, not parked**. Semantics fully settled:
it allocates the 0x2cf84-byte scene from the root heap, records the ARM7 lid/hinge bit from
`0x027fffa8` into bit 2 of the scene flags, pulls in **overlay 0x18 = ov024 (MobiClip)**,
clears the scene, seeds both panes' scroll step to -16, arms handler 0x20e9, opens
`"UI/sf/m.p2"` (`data_ov011_0205e8e4`), fills a 0x88 stack frame with the resource, an
"argument present" flag and the movie name `"843.z"` (`data_ov011_0205e8f0`, exactly the six
bytes of the inline copy), lets `func_ov024_020832c4` populate the stream interface at
+0x2cf58 and drives it (initialize, open, start), then blacks out both engines and returns
`func_ov011_0205ae4c`.

**The template is the matched `func_ov000_0205a3e0`**, which starts a movie from the ov000
menu with the same shape -- including the overlay id being the ADDRESS of the linker-absolute
`FS_OVERLAY_ID` symbol (written as a plain 24 the function comes out 4 bytes short).

The residue and the two remaining items are in the file header; use a MNEMONIC HISTOGRAM on
this one, not a diff -- a single missing instruction shifts the whole listing and makes the
diff unreadable.

### Handover 2026-07-27 (iteration 3)

The user took `func_ov000_02059b14` over personally ("continua con la siguiente, yo sigo con
esta") and this lane moved to ov011. That is the only reason the ov000 function was left; it is
still NOT parked and its record is in `build/try/b14/BEST.c`.

**CURRENT EXACT FUNCTION: `func_ov011_0205b814`** (see the ov011 block below). Full record in
the header of `build/try/ov011/BESTb814.c`.

**Iteration 4 result: the r4 <-> r5 transposition is SOLVED. Score 14 -> 12, and nPane now
lives in r5 exactly as the ROM does** (`mov r5, r0` and the closing `cmp r5, #0` both match).
The lever is a pair of `static inline` accessors (`Ov011_GetTileset` + `Ov011_GetPane`) reached
independently from the scene, instead of two inline member chains: the emitted instruction
stream is identical, but the re-shaped IR reorders the allocator. The helper split is not
free-form -- only that pair works (pane alone 32, core alone 14, VRAM helper 8 bytes short, a
third helper for wCols 32). Generalised into `codegen-cracks.md`; it should be tried on any
pure-colouring residue before another declaration-order sweep, since it is ~6 compilations
against 5040.

Also retracted this iteration: the "no matched precedent" claim (its census was filtered to
5+-parameter functions for no stated reason; without the filter there are SEVEN precedents).
And measured as NOT the lever: the explicit stride-left multiply flips the colouring only in
the forms where mwcc collapses the two pane bases (220 B).

**What is left on it:** a three-way rotation -- the ROM reuses the product's register in place
for the pane base (`add r6, r3, r6`) while we compute it out of place into r4. r4 and r5 now
agree, so the whole divergence is which register the PRODUCT gets (ROM r6, ours sb).

Iteration 9 closed the inline-qualifier cross (7x7; mwccarm rejects `always_inline`), the
accessors' index parameter type cross (6x6), and the optimisation levels on the accessor form.
It also caught a TOOLING trap worth knowing project-wide: a scorer that counts differing lines
read an aborted compile's empty diff as **zero differences, i.e. MATCH**, and put thirteen
broken variants at the top of the ranking. Same family as "an asm_stubs blob verifies
trivially" and "Jython reports success while dying on the 64K limit" -- absence of output read
as success. Written up in `tools.md`.

Iteration 8 (~700 compiles) produced the sharpest statement of where it stands: **two forms,
each half right.** The PRE-HELPER two-chain form is 14 words and its residue is a PURE r4<->r5
swap -- the product is already in r6 and nCols already shares the pScene register, so its whole
allocation is the ROM's modulo renaming two registers. The accessor-pair form (the current
BEST) is 12 and gets r4/r5 right but rotates the product, nCols and the pane base. No hybrid
keeps both. The matched sister `func_ov011_0205b8f8` settles what the target allocation is
(stride->r4, product->r6, index spilled) and its literal idiom costs 30 here because our nCols
must be one variable. A 256-point COMBINATORIAL sweep returns the score set exactly {12, 9999};
`register` (37 combinations) and all 26 inlining pragmas extracted from mwccarm.exe are inert.
Also corrected: the stride-left multiply never flipped the colouring by itself -- the
iteration-3 flip came from mwcc collapsing the two bases in those forms.

Iteration 7 re-ran ALL 27 mwccarm builds on the CURRENT (helper) form -- worth doing because the
previous sweep predated it and the shape depends on `-inline on,noauto`; every 2.0/3.0 build is
identical, so the compiler-build axis stays closed. Also closed: `static inline` helpers for the
two address COMPUTATIONS instead of the two objects (24/26/29/31 -- helpers only help when they
wrap the object lookups), and naming the pane ARRAY as a local or accessor in five positions
(all fall back to 14 and lose nPane's r5, so the accessor pair is load-bearing).

Iteration 6 added ~25 more compiles, all at 12: guard spellings (combined `||`, nested, swapped
-- the wRows test must come first, and guards above the clamp is 36), the clamp as a ternary,
the closing ternary inverted, and reading wCols/wRows/pTiles through the pane accessor instead
of the tileset local (all non-size-exact). Both ternary orientations and the guard order are
therefore fixed, not free.

Iteration 5 confirmed the floor at 12 across ~50 more compiles and closed four more axes
(helper definition order, helper signatures including scene-pointer parameters and a
`Ov011_GetScene()` accessor, the tileset accessor's intermediate object, and the callee
declarations the matched tree actually uses -- crossed 3x4, including the int-returning
`GFXi_EnqueueCommand` that several matched files declare). A corpus search for the missing
instruction form (a `mul` destination reused in place by `add rD, rZ, rD`) finds seven matched
functions, but they all get it from a loop induction variable or a multiply feeding a call
argument, so none transfers to a straight-line double-base address computation. Full record in
the header of `build/try/ov011/BESTb814.c`.

## FRONTIER 2026-07-26 (later): ov011 -- the scene that instantiates the title

ov000/ov002/ov006/ov008 are at **0 stubs**. `func_ov000_0205a4d4` loads ov012 (movies)
when the mode is 0 and **ov011** otherwise, so ov011 is the current milestone.
Class descriptor at `0x0205e8a0`: +4 ctor `func_ov011_0205ac40`, +8 `func_ov011_0205b034`,
six handlers from +0x14. **23 stubs left in ov011.**

**CURRENT EXACT FUNCTION: `func_ov011_0205b814` = `Ov011_BlitTileRow`** (228 B, ARM,
PORT-REQUIRED -- nothing paints the title panes without it). **NOT PARKED.**
Best form `build/try/ov011/BESTb814.c`: **mnemonic 0 / operand 19 / words 14** -- size,
relocations, instruction stream, immediates, offsets and shifts are all the ROM's, and
the entire residue is a single r4 <-> r5 transposition (the ROM gives r4 to the temp
chain and r5 to nPane; we do the reverse). The closed axes, the leave-one-out that names
the wrap branch as the owner, and the three things already solved are recorded in the
file header and in `state.md`.

Ghidra: renamed, parameters named, plate comment written, and the `Ov011Tileset` /
`Ov011PaneCore` / `Ov011Pane` / `Ov011Scene` / `Ov011Globals` types created with the
pool slot `arm9_ov011::0205b8f4` bound as `Ov011Globals *`.

**AFTER IT:** the ov011 constructor `func_ov011_0205ac40`, then `func_ov011_0205b034`
and the six-entry handler table, i.e. the scene's own bring-up order. The live
near-matches from the previous session (`0205be38`, `0205c190`, `0205c2fc`, `0205da60`)
stay in `build/try/ov011/`.

## FRONTIER 2026-07-26 (earlier): ov000 is 260/261

`func_ov000_02058e88` = `Ov000_SetupMenuObjects` (484 B) is MATCHED and integrated
(menu-scene display-object bring-up: tracker init, archive subfile #6, then the title
object at +0x158 and the cursor object at +0x4bd8 from six-word descriptors).
PORT-REQUIRED -- nothing draws the menu without it. Its `asm_stubs/` twin is deleted,
Ghidra is renamed/commented and the `Ov000ResourceTrackerConfig` type is created and
bound to the pool slot at `arm9_ov000::02059064`.

The crack is in `codegen-cracks.md` and told in full in the commit message: the three
repeated `base + constant` addresses must be NAMED LOCALS. mwcc rematerialises them so
the emitted code is byte-identical, but the smaller expression tree keeps the allocator
from deferring a descriptor store 60 instructions later. Found by a leave-one-out sweep,
after ~4000 experiments on the residue itself were all inert.

**ONE LEFT IN ov000:**

  func_ov000_02059b14   (324 B, 10 relocs)   build/try/b14/BEST.c   menu list redraw
                        caller: func_ov000_02059d78

STATE: 324 B, correct size and relocations, 118 of 124 instructions byte-exact. Residue
is six words in ONE window: the ROM completes the split row-array offset before reading
the index (`add r0,r8,#0x670` then `add r5,r0,#0x9000`) and stores the fifth argument
before loading the sixth's pool constant; mwcc reverses both. The FIRST split-offset
computation, at the top of the function, is byte-exact in both -- only the second moves.

OWNER: the loop. Block-level leave-one-out shows deleting the for loop restores the ROM
schedule, `i < 1` restores it and `i < 2` does not, and deleting the prologue, the title
call or the tail changes nothing. Not monotonic (loop removed = immediate at 200 B; loop
AND prologue removed = deferred again at 184 B), so it is a chaotic register-pressure
effect, NOT the IR-size threshold that closed func_ov000_02058e88.

The full negative record lives in the header of `build/try/b14/BEST.c` -- read it before
running anything, it is long and every entry is compiled evidence. Closed axes: all loop
forms x counter types, all 24 declaration orders, hoisting, real return types and arities
read back from the tree, variadic/unprototyped declarations, `const`/`register`, scopes,
a `static inline` row-draw helper, every row-access spelling, post-loop-only address
naming, 17 pragmas (including `scheduling off`, which leaves the output unchanged and so
proves the placement is decided during instruction selection), the flag space and all 27
mwccarm builds.

POSITIVE EVIDENCE: 192 matched ARM functions emit the immediate split-offset completion,
126 of them in functions that also contain a loop, and 12 of those complete it AFTER a
loop. The shape is ordinary mwcc output; we are simply not reaching the allocator state
that produces it.

The struct is aligned with the vocabulary the tree already uses: `Ov000ListSceneContext`
with `selection` at +0 and `cursor` at +2, the same object the matched
`func_ov000_0205a19c` describes -- see `game-flow.md`.

NAMING DEBT worth picking up alongside: `audit_unnamed.py` reports 109 byte-exact ov000
functions still named FUN_* in Ghidra (5,620 project-wide).

## Selection rule

Choose the earliest unresolved function required to advance the next playable
vertical slice.

Priority:

1. Explicit user-selected function or module.
2. Verified real-C staging handoff on the current frontier.
3. Earliest unresolved function on the current milestone's critical path.
4. Direct dependency of that function.
5. Transition required to reach the next milestone.
6. Other currently reachable functionality.
7. Later scenes.

Once selected, the function enters assigned-function mode until byte-exact MATCH.

Existing `nonmatching/` files are historical starting points only. Do not clear all
of `nonmatching/` before advancing the port.

## Status labels

- **PORT-REQUIRED** — needed for the next executable or playable slice.
- **PORT-HELPFUL** — improves understanding or completeness but does not block the
  next slice.
- **PLATFORM-REPLACED** — Nintendo DS-specific platform code replaced by the PC
  platform layer.
- **MATCHED-REAL-C** — byte-exact real C, not inline assembly or `dcd`.
- **UNRESOLVED** — current tree still lacks a verified real-C implementation.
- **VERIFY-CURRENT-TREE** — status may have changed since this file was written.

## Milestone 0 — process start and core runtime

Target outcome: enter the game frame loop, tick class objects and service scene
requests in the PC port.

Known backbone:

`crt0 -> main -> BootTask -> func_02023adc -> func_0202099c`

Key items:

| Item | Port status | Current planning status |
|---|---|---|
| `crt0 @ 0x02000800` | PLATFORM-REPLACED / PORT-HELPFUL | Preserve semantics needed by PC startup; do not port DS CPU-mode/cache setup literally. |
| `main @ 0x02000bcc` | PORT-REQUIRED | Historical readable source exists in `src/nonmatching/func_02000bcc.c`; verify current tree and make it real byte-exact C before moving later if it remains unresolved. |
| early init and task-system init | PORT-REQUIRED | Trace direct dependencies actually required before the frame loop. |
| `InstantiateClass @ 0x02023930` | PORT-REQUIRED | Verify current real-C status. |
| `RunClassConstructor @ 0x02023960` | PORT-REQUIRED | Verify current real-C status and semantic struct. |
| `func_02023adc` object tick | PORT-REQUIRED | Verify current real-C status; do not confuse it with the GFX command queue. |
| `func_0202099c` scene dispatcher | PORT-REQUIRED | Documented byte-exact; verify current tree. |
| `ov001` one-shot hardware init | PLATFORM-REPLACED | Replace with PC platform initialization unless game semantics are discovered inside it. |

### Current selection rule for milestone 0

If `main @ 0x02000bcc` is still nonmatching, it is the first default autonomous
target. Otherwise choose the earliest unresolved direct dependency required to
reach the frame loop and first scene request.

## Milestone 1 — Scene 1 / ov000 boot and logo

Target outcome: display and advance through the first visible boot/logo sequence.

Known entry:

- scene id 1;
- overlay `ov000`;
- ctor `func_ov000_0204d630`;
- fresh-boot setup `func_ov000_0204d7c8`.

Documented state functions include:

- `func_ov000_0204dc38`;
- `func_ov000_0204ea68`;
- `func_ov000_0204df98`;
- `func_ov000_0204f6c8`.

Verify their current real-C status and follow actual state transitions. Match the
earliest unresolved state or dependency required for the visible sequence and the
transition to title.

Do not sweep unrelated ov000 menu/load functionality before the boot/logo critical
path is complete.

## Milestone 2 — Scene 7 / ov006 title

Target outcome: render the title, process Start/input and request scene `0x13`.

Known chain:

- outer title ctor;
- real title ctor;
- visual ctor/resource loader;
- title state/input;
- `StoreGlobalPairAt10(0x13, 0)`.

Prioritize:

1. ctor and initial state;
2. visible title resource path;
3. input and Start detection;
4. transition to main menu;
5. teardown.

Verify current status before choosing; much of this path was previously documented
as matched.

## Milestone 3 — Scene 19 / ov008 main menu

Target outcome: display the menu, select Story/New Game or Load, produce the config,
and request gameplay scene 2.

Known transition:

`ov008 confirm -> StoreGlobalPairAt10(2, 0) -> ov002`

Prioritize:

1. menu ctor and state;
2. resource loader and first visible frame;
3. cursor/input;
4. config fields required by Story/New Game/Load;
5. confirm path;
6. scene-2 request and teardown.

Do not fully decompile every optional menu page before the gameplay transition is
usable.

## Milestone 4 — Scene 2 / ov002 gameplay bootstrap

Target outcome: enter gameplay and produce the first playable frame.

Documented frontier entry:

`func_ov002_020679d4`

This function and its direct subsystem initialization chain are the default next
targets once all earlier critical-path gaps are real C.

Build the queue dynamically from its calls and returned state:

1. gameplay scene ctor;
2. initial state dispatcher;
3. save/config consumption;
4. archive/room/map loading required immediately;
5. player spawn and transforms;
6. camera;
7. essential collision/world state;
8. input;
9. HUD and first visible gameplay render;
10. transition into the first story/tutorial event.

Do not match all of ov002 before identifying the minimum playable slice.

## Milestone 5 — first story/tutorial slice

This milestone must be discovered from verified `ov002` runtime transitions rather
than guessed from overlay numbers.

When discovered, append:

- exact state/function entry;
- scene/overlay relationships;
- required resources;
- player-control enable point;
- first mission/day/event transition;
- direct dependency queue.

Then continue through story progression in runtime order.

## Later milestones

Continue by actual game transitions:

- end of current state;
- next scene request;
- next overlay/class descriptor;
- next constructor;
- next returned state.

Do not use numeric overlay order as story order.

Optional modes, multiplayer, enemy families, codecs and late-game overlays are
lower priority unless they become direct dependencies of the current playable
slice.

## Current frontier record

Update this block after each reachability-changing match.

- **Verified on:** 2026-07-25 15:40 (autonomous port-first session)
- **MATCHED THIS SESSION, in play order:**
  1. `func_ov008_02068e68` = `Ov008_TickPageScroll` (792 B) -- byte-exact.
  2. `func_ov025_0209b248` = `Ov025_TickPageScroll` (792 B) -- byte-identical twin,
     propagated free by `dedupprop`.
  3. `func_ov000_02050ec4` = `Ov000_TickPageScroll` (1012 B) -- byte-exact.
  4. `func_ov009_02054180` = `Ov009_TickPageScroll` (820 B) -- byte-exact. Fourth and
     last ARM instance of that source function.
  5. `func_ov000_02051648` = `Ov000_DrawSaveSlotText` (728 B) -- byte-exact. Direct
     callee of Ov000_TickPageScroll.
  Gate after each: DSD_OK=306 FAILED=0.

- **Cracks that came out of it** (full write-ups in `codegen-cracks.md`, and each one
  is told in full in its commit message so it travels with the repo):
  * two symmetric reads of the same object may need DIFFERENT spellings -- one through
    a `volatile int *` local, one plain. This is what closed the page-scroll family
    after ~15 sweeps on every other axis;
  * `const` on a pointer local is a frame-layout knob (pointer group above vs below the
    ints); 121 declaration positions could not reach the ROM's slot assignment;
  * an `else if` written so it cannot fall through blocks if-conversion, which changes
    register pressure far away -- worth 28 bytes of spill traffic here;
  * a `bl` whose argument register is never written on that path means the callee is
    variadic and that site passes fewer arguments.

- **CURRENT EXACT FUNCTION:** `func_ov000_0205474c` = `Ov000_BlitOrClearTileRegion`
  (380 B). **NOT PARKED.** Best form `build/try/f838/t4c_BEST.c`:
  **mnemonic 0 / operand 0 / full 29** -- the instruction stream, every immediate,
  offset and shift is correct, and the residue is a permutation of the callee-saved
  registers.
  ⚠ **CORRECTION to the previous record**: this was written up as "blocked on
  infrastructure -- the build has no per-file flag override". That was WRONG.
  `#pragma opt_strength_reduction off` is a legal in-source mwcc pragma, needs no build
  change, and with it the stream matches at the tree's own optimisation level.
  `#pragma optimization_level N` works too and reproduces the -O sweep exactly. See
  `codegen-cracks.md` for the full write-up; the rule is to walk the pragma list before
  ever blaming flags or the build.
  The loop also needed the explicit guard + do-while form with the counter initialised
  inside each branch (a plain `for` is 8 bytes short).
  Left to do: the register permutation. The cascade starts at r4 -- the ROM gives the
  first callee-saved register to the incoming `bCopy` parameter, we give it to `dst`.
  Ruled out by compiling: 216 declaration permutations of dst/blob/h/i at every
  insertion point (96 size-exact, best 31), and `const` on both parameters and on blob
  in all 16 combinations (uniformly inert).
  Its twin `func_ov000_020530cc` (384 B) is the same shape and takes the same pragma.

- **ov000 remaining (9), all reached through data tables rather than function relocs:**
  `02052374` (904 B), `020526fc` (712 B), `020529c4` (688 B), `02058a40` (488 B, stub),
  `02058e88` (484 B, stub), `02051f94` (400 B, stub), `020530cc` (384 B, stub),
  `0205474c` (380 B, stub), `02059b14` (324 B, stub).
  Callers: `020530cc` <- `02052fbc`/`02052fcc`; `0205474c` <- `02054648`/`02054658`;
  `02058a40`, `02058e88` <- `02059e60`; `02059b14` <- `02059d78`; and
  `02051f94`, `02052374`, `020526fc`, `020529c4` have no function caller at all --
  they sit immediately after the Load-screen drawing code, so they are the strongest
  candidates for the Load/menu state handlers reached from a table.

- **Staging swept 2026-07-25:** only `staging/ov003/*` (14 files) pending. ov003 is NOT
  on this frontier and a previous session re-verified all 14 in both modes: none match.

- **AFTER IT:** the remaining ov000 data-table functions listed below, then
  `main @ 0x02000bcc`.
- **Done since last record:** recipe matcher family x7 (461aba7a0), + 5 ov000 data-table page
  functions: 0204f838, 0204fc64, 0204fdac, 020500d0 (b552537c8), 020508a0 (this session).
- **Verified on (old):** 2026-07-24 (autonomous port-first session)
- **Current milestone:** ov000 -- the agreed order in `state.md` is (1) finish ov000
  (boot + title + every menu level + "Load"), (2) `main`, (3) ov009/ov006, (4)
  ov002/ov008/ov025.
- **Matched this session, in play order:**
  1. `func_ov000_0204cc90` -- Ov000_RefreshMenuLayout (menu cell layout + cursor).
  2. `func_ov000_0204e270` -- Ov000_MenuFadeInState (re-entry fade).
  3. `func_ov000_0204e5b0` -- Ov000_TickMenuLoop (the interactive menu loop; input,
     confirm/cancel dispatch, 105 s idle -> attract).
  4. `func_ov000_02057850` x7 -- Ov000_LayoutPanelEntry.
  5. `func_ov000_02057dc4` x7 -- Ov000_FoldPanelIntoTally.
- **Current exact function:** `func_ov000_020573e4` (1132 B, 7 relocs, 6 byte-identical
  twins in ov004/005/009/025/069). It is the type-4 evaluator called at the end of
  Ov000_LayoutPanelEntry, i.e. the recipe/synthesis match for the panel system.
- **Reason:** it is the last function still unresolved on the static call graph reachable
  from the Scene-1 ctor `func_ov000_0204d630`. BFS from that ctor reaches 87 ov000
  functions; after this session only `020573e4` is left of them.
- **Direct dependencies:** none unresolved -- 020570d8, 02057138, 0205721c, 02056e28,
  02056b18/bac/cb4 are all byte-exact already.
- **After that:** the remaining 16 pending ov000 functions are reached through data
  tables, not through function relocs, so the BFS does not see them. Enumerate them from
  their callers (`0204f838`, `0204fc64`, `0204fdac`, `020500d0` <- `02051d3c`;
  `020508a0`, `02050ec4` <- `02052124`; `020530cc` <- `02052fbc/02052fcc`;
  `0205474c` <- `02054648/02054658`; `02058a40`, `02058e88` <- `02059e60`;
  `02059b14` <- `02059d78`; and the four with no caller at all:
  `02051f94`, `02052374`, `020526fc`, `020529c4`). Then `main @ 0x02000bcc`.
- **The panel subsystem is shared x7** (ov000/004/005/008/009/025/069): every match here
  is worth seven, and `dedupprop.py` propagates it for free.
- **Staging:** `staging/ov000/func_ov000_02057dc4.c` was an ASM stub with a decorative
  struct header -- REJECTED, and the real C above replaces it. `staging/ov003/*` (14
  files) was re-verified in both modes by a previous session: none match, and ov003 is
  not on this frontier.

## iter-55 (2026-07-30)
- MATCH func_ov008_02069320 = Ov008_TickTitleFade (164B, 5 relocs, blob-gap carve C+1/ASM+0).
  Title-menu "fade" SRT tween tick: bit2 of flags230 -> restart tween 0x2000<->0x8000 over 500u
  (dir=field234), step, flip field234; else sample tween -> apply >>12 to widget. Struct
  Ov008FadeCtx + name done in Ghidra. Commit on ahead-2.
- Tween ABI confirmed: func_02035fb0(&fade,mode,from,to,dur) 5-arg init; func_02035ffc(&fade) step;
  func_0203602c(&fade,&out) sample; func_020327e0(widget,val) apply. Reuse across menu ticks.
- PUSH: ahead 2 (6836c + 69320). origin 21min -> push next hour window with a re-gate 306/0.
- Still open Ov008IterFrame members: func_ov008_0205cde8 (936B), func_ov008_02060e3c (1952B).

## iter-56 (2026-07-30)
- MATCH func_ov008_0205cc04 = Ov008_CheckPageItemLimits (212B, 4 relocs, blob-gap carve C+1/ASM+0).
  Direct dep of the 936B frontier func_ov008_0205cde8. Per-page capacity check: 1KB counter buf,
  walk u16 grid[page][3][40] at *data_0204be18+0xc10, each cell -> 0x9c-stride entry table at
  ctx+0x207c -> itemId counter; return 1 if any exceeds limit (base+itemId+0x810). Struct
  Ov008SlotCtx + name in Ghidra. Commit on ahead-3.
  - CRACK: two prologue-scheduling diffs, both source-order: declare `result=0` BEFORE the alloc
    (fp set at 0x0c pre-call), and DON'T cache ctx+0x2000 in an early local -- access the table via
    a struct field inside the loop so mwcc hoists the +0x2000 add late (0x3c). Body+tail matched
    first try; only the setup ordering moved.
- PUSH: ahead 3 (6836c + 69320 + 5cc04). origin 32min -> push next hour window w/ re-gate 306/0.
- Frontier parent now: func_ov008_0205cde8 (936B, IterFrame+text/draw) has 5cc04 done; remaining
  undone callees of it: none tiny left besides itself. Next: 0205cde8 itself, or func_ov008_02060e3c.

## iter-57 (2026-07-30) -- WIP in build/try/5cde8.c (NOT parked, continue)
- func_ov008_0205cde8 = save/equip PAGE RENDERER (936B, 44 relocs). Full semantic map DONE;
  candidate build/try/5cde8.c reaches 928/936 (DIFIERE, 2 instrs short). Everything else exact:
  logic, branch structure, stack layout, register allocation.
- STACK LAYOUT crack (solved): decl order = {hdr(tag[3]+NNSFndList list), collect[120], self, text[128]}.
  Rule observed: first-declared local stays lowest (sp+8); the REST lay out in reverse-declaration
  order. Target offsets hdr@8, text@0x20, self@0x120, collect@0x220.
- REG crack (solved): declare `int f04, count, f00;` in THAT order -> count->r8, f00->r9 (sb),
  matching ROM. (f04->r7.)
- REMAINING residue (the only diff): ROM re-materializes `text` addr (`add r7,sp,#0x20`) before the
  group-2 AND group-3 draws inside the post-if/else merge blocks, even though r7 already holds text.
  My mwcc keeps text in r7 across all 3 groups (proves liveness) -> 2 fewer `add` = 8B short.
  Group-1 draw matches (text freshly materialized after f04 dies). NEXT: grep matched tree for the
  forced-rematerialization idiom, or find the source structure that defeats mwcc's cross-block
  redundant-add elimination for a frame-relative address. Do NOT park.
- KEY FACTS for the port: func_02013814 = Cursor_MaxOverRun takes 3 ARGS (not 4; the ROM's r3=0xf1
  is leftover). func_020262a0 = variadic sprintf(buf, cap, fmt, ...). func_020301c8/02030278 =
  6-arg Draw_WithAxisOffset variants. Grid at *data_0204be18 + 0xc10 + page*0xf0 (same as 5cc04).
- PUSH: ahead 3 (6836c+69320+5cc04). origin 52min at check -> push next window w/ re-gate 306/0.

## iter-58 (2026-07-30)
- MATCH func_ov008_0205cde8 = Ov008_DrawSavePage (936B, 44 relocs) -- the 928/936 WIP CLOSED.
  CRACK: pass the draw buffer arg as a POINTER (void *a6), not (int)text -> mwcc re-materializes
  the frame address before each of the 3 draws (the 2 missing `add r7,sp,#0x20`). Written up in
  codegen-cracks.md + the commit. Struct Ov008PageIterSelf + name in Ghidra. Commit on ahead-4.
- PUSH: ahead 4 (6836c+69320+5cc04+5cde8). origin crossed 60min -> running gate.sh (306) now;
  push on green.
- Next frontier: func_ov008_02060e3c (1952B, last Ov008IterFrame member), then menu-state
  dispatcher deps (0206bfac 752B, 0206dd7c 712B, 0206c90c 1192B).

## iter-59 (2026-07-30)
- MATCH func_ov008_0206b814 = Ov008_TickPageBTransition (632B, 23 relocs) -- menu page-B slide
  state-tick (dispatcher callee, priority-2 play order). 64-bit fixed-point + MMIO scroll regs +
  CP context + DIVCNT spin. Struct Ov008PageBCtx + name in Ghidra. Commit on ahead-1.
  CRACKS: (1) func_ov008_0205490c is 3-arg not 4 -- the ROM's r3 = leftover 0x04001010 reg pointer
  (phantom trailing arg); (2) 2nd 64-bit product: compute `pt.x += (int)((ll)inv*-0x30000+0x800>>12)`
  BEFORE `pt.y=0`, else mwcc folds -0x30000 into `sub rX,r0(=0),#0x30000` (1 instr) instead of
  ROM's mov+rsb (2 instr) -> 4B short; (3) reverse-declaration stack layout (last-declared lowest);
  (4) combine {Point pt; int sample;} into one struct to force pt@0/sample@8 contiguity.
- Remaining dispatcher state handlers (menu-state milestone): func_ov008_0206dd7c (712B),
  func_ov008_0206bfac (752B), func_ov008_0206c90c (1192B), func_ov008_0206cea0 (452B, was "held").
- PUSH: ahead 1. origin 17min -> push next hour window w/ re-gate 306/0.

## iter-60 (2026-07-30)
- MATCH func_ov008_0206dd7c = Ov008_DrawStatusPage (712B, 36 relocs) -- stats/status page render
  state (dispatcher callee). 6 draws + variadic eb64 stat-setters + 99-entry message-record scan.
  Named in Ghidra. Commit on ahead-2. CRACKS: (1) func_ov008_0206eb64 is variadic (id, flag, ...)
  -- 0/1/2 value args per call; (2) cache *(data+4) in a loop-body local (ROM reuses r1 for cmp+sub,
  else 1 instr over); (3) declare eq3/counter BEFORE uVar9 so coalesced eq3+counter -> r7, uVar9 ->
  r8 (reg-coloring order via declaration order).
- Remaining dispatcher state handlers: func_ov008_0206bfac (752B), func_ov008_0206c90c (1192B),
  func_ov008_0206cea0 (452B, was "held").
- PUSH: ahead 2 (6b814 + 6dd7c). origin 27min -> push next hour window w/ re-gate 306/0.

## iter-61 (2026-07-30)
- MATCH func_ov008_0206bfac = Ov008_LayoutMissionEntries (752B, 51 relocs) -- FIRST ATTEMPT.
  Mission/pause menu entry layout (dispatcher callee). Two 4-word ldm/stm templates + long
  FindEntryById+slot-op sequence + Session-active && block + REG_POWCNT1(0x4000304) bit15 gate +
  4-entry copy loop. Named in Ghidra. Commit on ahead-3.
  NOTES: func_02030670 reuses func_02030640's r0 result -> both zero-arg; stack layout via
  reverse-declaration (decl local_28,block2,pt -> pt@0,block2@8,local_28@0x18); MMIO test
  `(int)(*(u16*)0x4000304 & 0x8000) >> 0xf == 0`.
- Remaining dispatcher state handlers: func_ov008_0206c90c (1192B), func_ov008_0206cea0 (452B,held).
- PUSH: ahead 3 (6b814 + 6dd7c + 6bfac). origin 33min -> push next hour window w/ re-gate 306/0.

## iter-62 (2026-07-30) -- held 6cea0 re-challenge + 0206c90c analysis
- func_ov008_0206cea0 (452B) RE-CHALLENGED. Byte-identical EXCEPT ONE instruction pair: config2's
  func_0202ff98 call evaluates its args config-first (add r1,sp,#0x80 then add r0,r4,#0xdc) in the
  ROM but param-first in mwcc. Everything else (6 ldm/stm struct copies, pVramTarget/pPixels
  patches, other 5 calls, tail) is exact. 7 axes tried, ALL invariant: dest-temp, config-ptr-temp,
  dest arg type (int vs void*), config arg type, func return type (void vs int), struct-field param,
  array-of-6-structs (this last REGRESSES the copies -> separate locals is correct). Genuine
  deterministic mwcc arg-eval-order scheduling tie on ONE call. Closest form kept in build/try/6cea0.c
  (separate locals). NOT parked. Do NOT re-try these 7 axes; needs a novel arg-eval steer or accept.
- func_ov008_0206c90c (1192B, 43 relocs) ANALYZED for next iteration: scroll-list state handler.
  64-bit divide via func_02020400 (returns quot:rem in r0:r1, hi word = scroll index); signed
  div/mod-by-16 idioms (asr#3;lsr#28;asr#4 = /16; the ror#28 pattern = the remainder scaled);
  SBORROW-style scroll clamp with 4 branches; positions entries 0x29/0x51 via SetEntryPos; 6-case
  item-type switch (puVar5[2]) each fetching MsgDb records + eb64; returns "count>1" flag. Needs a
  dedicated fresh-context iteration -- the 64-bit divide + div/mod-16 idioms are the crux.
- PUSH: ahead 3 (6b814+6dd7c+6bfac). origin 45min -> push next hour window w/ re-gate 306/0.

## iter-63 (2026-07-30) -- 0206c90c WIP 1168/1192 in build/try/6c90c.c (NOT parked)
- func_ov008_0206c90c FULLY MAPPED + first C written. Progress: 1112 -> 1168/1192 (24B short).
  BIG CRACK found: local_38 (the UiLayoutPos passed to func_ov008_020548a4/02054858) is a 4-INT
  struct {nX,nY,dX,dY}; dX/dY ARE local_30/local_2c (the scroll delta). Passing &local_38 forces
  dX(=0)/dY onto the stack (mwcc can't fold dX=0 because the struct escapes) -> recovered 14 instr.
- REMAINING 24B (6 instr): register-allocation/frame nuance. ROM pushes {r3,r4,..} (10 regs, r3 for
  align) and SPILLS param_3 to sp[0] (str r2,[sp] at 0x01c), using fp for the LATE func_02020400
  result (iVar2b). Mine keeps param_3 in fp (9-reg push, sub 0x1c). param_3 (live 0->switch) and the
  late iVar2 (0x234->0x298) OVERLAP so they need distinct regs; ROM spills param_3, mine spills the
  other. Splitting iVar2 into two C vars did NOT change it. NEXT: force the param_3 spill (maybe
  reassign param_3 as the ROM does: `param_3 = EnqueueObjGfxCommand(...)` then count-clamp it and
  `return param_3` instead of `return count>1?1:0`), or increase reg pressure so param_3 spills.
- func_02020400 = `long long func_02020400(int,int)` (r0=low, r1=high divmod). iVar7/16 and iVar7%16
  are signed div/mod-by-16 (mwcc idioms, matched). 6-case switch (case 1&5 share body) matched.
- PUSH: ahead 3. origin 56min -> next iter crosses hour -> gate 306/0 + push ahead-3.

## iter-64 (2026-07-30) -- 0206c90c refined to 1168/1192, correct tail
- Confirmed the TAIL is `return count > 1 ? 1 : 0` (movgt/movle) -- NOT a param_3-mutable reassign
  (that added 3 wrong instrs). func_020300f8 is void; its return is dead.
- Remaining 6-instr gap is pure mwcc BLOCK-LAYOUT ORDER (same instructions, different physical
  order), in THREE spots: (a) the 4-way scroll clamp else-if chain is laid out in a different order
  than the ROM; (b) the 6-case switch bodies: ROM physical order is case1&5, 0, 4, 3, 2 (by addr
  0x318/0x34c/0x3bc/0x448/0x46c) -- mine differs; (c) param_3 spill to sp[0] (ROM spills, mine keeps
  in reg -- a register-pressure decision, ~2 instr). NEXT: steer the switch/clamp block layout
  (try reordering the source case blocks to 1&5,0,4,3,2; try inverting clamp branch senses), and
  raise register pressure so param_3 spills. build/try/6c90c.c = 1168/1192, structurally complete.
- PUSH: ahead 0 (just pushed f94f42fd2). Nothing due.

## iter-64b -- 0206c90c layout steers EXHAUSTED (still 1168/1192)
- Tried and NEUTRAL (do not repeat): switch case-body source reorder (1&5,0,4,3,2); visibility
  branch invert (if iVar4>=9 show-first); struct-init field order (dX,dY,nX,nY first). mwcc lays
  out the switch bodies + struct init its own way regardless of source order.
- The 6-instr residue is: (1) param_3 kept in reg vs ROM spills to sp[0] (~2 instr, register
  pressure); (2) pos-struct zero-init: ROM uses TWO base-pointer adds (add r6,sp,#0x18; add r5,sp,
  #0x10) + 4 str; mine uses direct sp-offset str (no adds) -> ROM +2; (3) clamp else-if physical
  layout order. All are mwcc reg-alloc/block-layout decisions not reached by these source axes.
  NEXT ANGLE: raise register pressure to force param_3 spill (an extra live callee-saved value),
  and find why mwcc uses base pointers for the 4-int struct init (maybe declare pos as two separate
  UiLayoutPos so each inits via its own base add). 6c90c.c is 1168/1192, correct tail, full map.

## iter-65 -- 0206c90c HELD at 1168/1192 (build/try/6c90c.c), frontier advances
- After 10+ axes across iters 63-65 (4-int pos struct [+14 instr, the key crack], correct tail,
  param_3-mutable [reverted], switch reorder, visibility invert, struct-init order, iVar2 split,
  aggregate {0} init, register hint) the 6-instr residue does NOT move. Root: mwcc uses a SEPARATE
  register (fp) for the late func_02020400 result instead of reusing the early scroll-index reg
  (r6) -> one more live callee-saved value -> forces param_3 to spill to sp[0] (ROM) + base-pointer
  pos-struct init (+2) + clamp block-layout. All downstream of that one coalescing decision, which
  no source axis reaches. Genuine deep reg-alloc/block-layout tie, like 6cea0. HELD in build/try/,
  NOT parked; re-challenge periodically. build/try/6c90c.c = 1168/1192, full map, correct tail.
- HELD TIES now: 6cea0 (1 instr, arg-eval), 6c90c (6 instr, reg-alloc). Both build/try/, both real.
- Menu-state dispatcher milestone (ov008) essentially COMPLETE: all state handlers matched
  (6b814, 6dd7c, 6bfac, 5cde8, 5cc04...) except these two held ties. FRONTIER ADVANCES.

## iter-65b (2026-07-30)
- MATCH func_ov008_0206f4c0 = Ov008_ScrollPageDown (388B, 19 relocs, blob-gap C+1/ASM+0). A CALLER
  of the held 0206c90c -- frontier advanced past the reg-alloc tie. Menu scroll-down input step.
  Named in Ghidra. Commit on ahead-1. CRACKS: (1) func_ov008_02055c24 out-param is 8 bytes -> u16
  pt[4] (sub sp,#8, no r3 pad); (2) getter/field44 gate as short-circuit `getter==2 || f44==1` (no
  bool temp -> mwcc predicates: cmp; ldrne; cmpne; addeq/popeq); (3) declare block1 BEFORE count so
  count->r6, block1->r5; (4) fits-check `count <= 8 && bound+row >= count` for the exact cmp forms
  (cmp #8;bgt and cmp r0,count;addge). div/mod-16 idioms matched as before.
- Remaining callers of 0206c90c (menu tick/transition frontier): func_ov008_0206e554 (460B),
  func_ov008_0206ed7c (1320B). These are the scroll-up/tick peers -- likely twins of 6f4c0's shape.
- PUSH: ahead 1 (6f4c0). origin 22min -> push next hour window w/ re-gate 306/0.

## iter-66 (2026-07-30)
- MATCH func_ov008_0206e554 = Ov008_TickMenuScrollInput (460B, 26 relocs) -- FIRST ATTEMPT. Another
  caller of 0206c90c (scroll/selection tick). data_0204c18c bit 0x400 input latch gate; pad bits
  0x40/0x80 scroll up/down via 0206c90c; else settles selection. Confirms 0206c90c RETURNS int
  (used: iVar2=...; if(iVar2!=0) PlaySound). Named in Ghidra. Commit on ahead-2.
  Note: func_ov008_0206bca0 = 3-arg (ctx,newSel,100); func_02030158 = 1-arg; the r3 push is align.
- Remaining caller of 0206c90c: func_ov008_0206ed7c (1320B, 52 relocs) -- the big menu tick.
- PUSH: ahead 2 (6f4c0 + 6e554). origin 28min -> push next hour window w/ re-gate 306/0.

## iter-67 (2026-07-30)
- WORK func_ov008_0206ed7c = Ov008_RedrawMenuPage (1320B, 52 relocs) -- the big menu-page rebuild
  (last caller of 0206c90c). Fully decoded + written; HELD WIP in build/try/6ed7c.c. NOT parked.
  Residue = a clean 3-cycle register rotation r7<->r8<->r9 among {iVar16, iVar17, node/scratch}:
  ROM gives r7 to the loop-heavy scratch (node/iVar9/struct-src-ptr, all coalesced) and r8/r9 to
  the long-lived captured pair (iVar16=sel id, iVar17=sel subid); mwcc gives r7 to iVar16. Size,
  every instruction, and all 52 relocs are exact modulo this rotation (51 pure reg-rename diffs;
  the two extra clusters at 0x7c eb64(2,0) addr-temp and 0x428 bVar1-vs-tail scheduling are
  DOWNSTREAM of the rotation -- fixing them independently = no change).
  ~40 compiled experiments, none flip it: declaration order (x10, ZERO effect at -O4), chained vs
  separate zeros, source-all-from-iVar16, register hints (ignored at -O4), for/while loop forms,
  node/puVar7 fusion, array-capture, reverse capture, && operand swap, split search counter,
  record-locals array, live-range shift (moving iVar16/17 zero-init down = 118 diffs, worse).
  DECODE facts (all confirmed): outer takes only `self` (param2/3/4 phantom). func_ov008_0206f6e4
  = 2 args (Ghidra's arg3/4 phantom; r2/r3 never set at call). globals: data_0204c678 = u8[] byte
  config (idx 2/3/4); data_0204c680 = u16[] halfword stat table (u32 at +0xc); data_0204be18 =
  ptr-to-struct, byte at ptr+0x811; data_ov008_0208f7f8 = 88B stat-column table (struct copy ->
  ldm/stm 5x{4}+1x{2}); data_ov008_02090f20 = int gate. e410 = 10 args; e4cc = DrawStatBar(root,
  self,idx,val). NEXT: keep re-challenging the rotation; also the ov008 menu frontier past this.

## iter-68 (2026-07-30)
- MATCHES (3), all direct dependencies of the held page-rebuild tick 0206ed7c -- milestone
  progress even while the tick itself stays a held reg-rotation tie:
  * func_ov008_0206f6e4 = Ov008_LoadWeaponStats (168B, 5 relocs, blob-gap C+1). Loads the
    equipped-weapon stat record via Ov008_LoadCharacterWeapon (0208b890, 3-arg) into a 32B local,
    copies 5 signed-16b stats + a u32 into pageB (0x1d8..0x1e6). CRACKS: pageB stat fields are
    SIGNED (store through s16* -> ldrsh, not the ldrh mwcc uses for a truncating u16 store; the
    ternary field already gets ldrsh via integer promotion); branch orientation 'if (id>=0){slot}
    else{default}' for the blt; 0x1e0-group shares pageB+0x100 base (strh offset can't reach 0x1e0).
    Struct Ov008WeaponBuf (32B) created in Ghidra.
  * func_ov008_0206e410 = Ov008_AddListEntry (188B, 4 relocs, blob-gap C+1) -- FIRST TRY. Finds the
    (kind,id) node via 0206e05c (returns int*, called with args swapped: self,kind,id,0); draws
    fresh via 0206e0e4 (9-arg) when absent, else merges extents (signed-max node[3], accumulate
    node[4]); optional refresh 0206c29c + 0206cdb4(self,self->0x48). Named in Ghidra.
  * func_ov008_0206c29c = Ov008_UpdateScrollGauge (208B, 8 relocs, blob-gap C+1) -- FIRST TRY.
    count list -> scale=0x800/(count*2) (func_02020400 returns int quotient here) clamped [0x20,0x80]
    stored 3x to self+0x4c; toggles 14 gauge segments (ids 0x30..0x3d) by (scale-0x20)/8. CRACK:
    keep the loop-invariant /8's final asr inside the per-iter compare -- write 'base / 8' in the
    condition, don't hoist the whole division. Named in Ghidra.
- 0206ed7c now has its ENTIRE call graph matched except itself. Still HELD (build/try/6ed7c.c),
  reg-rotation tie unchanged. Re-challenge next iteration.
- PUSH: ahead 3. origin 18min -> push next hour window w/ re-gate 306/0 + progress regen.

## iter-68 (cont.)
- MATCH func_ov008_0206e0e4 = Ov008_InsertListEntry (208B, 8 relocs, blob-gap C+1). Alloc+zero
  0x30 node, fill fields, dup UTF-16 label into own heap buffer ((wcslen+1)*2), sorted insert into
  self+0x1cc. Struct Ov008ListNode (0x30) in Ghidra. CRACK: insertion scan = for-loop with internal
  break (guard it!=0, break on it[2]==kind && it[0]>id) -> ROM's rotated movs/bne; one compound
  for-condition adds an instr. Dependency of e410's draw-fresh path.
- HELD func_ov008_0206cdb4 (build/try/6cdb4_held.c, 200 vs 208, 2-instr scheduling tie). Sibling of
  6c90c's tail: count -> self[0x40]=divmod(pos*(count-8)*16, 0x80-self[0x4c]); arrows 3/4 visible by
  pos>0 / pos<room; tail 0206c7a0(self,pos). Residue: ROM PRE-materializes each visibility bool into
  a callee-saved reg BEFORE its FindEntryById call (extra mov r2,rN x2); mwcc keeps recomputing it
  lazily after the call (2 instr shorter). ~9 forms tried (inline call, explicit temp, both-upfront,
  ternary, 0<pos, unsigned room, divmod temp) -- none force the pre-compute. NOT parked; re-challenge.
- ov008 menu frontier: 0206ed7c's whole call graph now matched except 0206ed7c (reg-rotation, held)
  and 0206cdb4 (held). NEXT: re-challenge these two; then other ov008 menu-state functions.

## iter-69 (2026-07-30)
- MATCH func_ov008_0206c690 = Ov008_DrawListWindow (272B, 9 relocs, blob-gap C+1). Redraws the
  visible rows of the scroll list: runs layer obj self+0x190, clears two grid regions, draws each
  populated entry in window [center-1, center+0xf) at grid row (index % 16) via c36c, tallies
  entries + kind 1/5. Returns populated count. Called by the held scroll driver 0206c90c.
  KEY CRACK: func_02030158 is 1-ARG here (self+0x190) -- Ghidra's trailing args are the caller's
  r1-r3 left in place; declaring it 4-arg keeps params live and perturbs the 1st grid-clear call's
  arg scheduling. Row = signed 'index % 16'. c36c/eb64 trailing args = %16 sign byproduct (phantom).
  Named in Ghidra.
- HELD func_ov008_0206c7a0 (build/try/6c7a0_held.c, 360 vs 364, 1-instr). Scroll-entry fixed-point
  layout: for entries 0x2d/0x2f/0x30..0x3d sets pos {nX,nY} (<<12 fixed) via 020548a4/020548bc,
  self[0x48]=param_2. Struct Ov008Pos2 {int nX,nY}. Residue: ROM materializes &pos into r3 for the
  2-field zero-init (add r3,sp,#4; str via r3), 1 instr more than mwcc's direct [sp,#4]/[sp,#8].
  Tried pp-pointer init/everywhere, chained, *(ll*)&pos=0, separate-locals -- mwcc keeps the
  direct-store (more optimal) form. Same codegen-quirk class as cdb4 (ROM slightly less optimal).
- Held tie pattern noted: cdb4 + c7a0 are both cases where the ROM emits a LESS-optimal schedule
  (pre-materialized bool / base-pointer init) than mwcc 139 produces from every source shape tried.
- NEXT: other ov008 menu functions; periodically re-challenge the held ties.

## iter-70 (2026-07-30)
- MATCH func_ov008_0206c36c = Ov008_DrawListEntryRow (804B, 28 relocs, blob-gap C+1). The core
  menu-list row renderer: jump-table switch on entry kind (node[2] 0..5, variant tag from node[7])
  sets the icon; builds UTF-16 label into a local 64-halfword buf (verbatim copy if node[3]<0 else
  mapped via 02055cbc) and draws it (02030278) with an overflow-palette swap; if node[4]>0 formats
  + draws a value string. Called per visible entry by c690 (Ov008_DrawListWindow). Row = col*16.
  CRACKS: (1) switch bodies in SOURCE ORDER 1,5,0,4,3,2 to match the ROM jump table; (2) compute
  'row = col*16' AFTER the overrun-if so MaxOverRun's r0 frees for the &buf stack arg (2-instr fix);
  (3) c36c takes 3 args (4th phantom); icon tag via unsigned short; 02055cbc variadic; DAT 0x821.
  Uses Ov008ListNode (from e0e4) -- node param typed in Ghidra. Named.
- The c90c -> c690 -> c36c menu-render chain is now matched end to end (c90c itself still held).
- NEXT: remaining ov008 menu functions + re-challenge held ties (6ed7c, 6c90c, cdb4, c7a0).

## iter-70 (cont.)
- SCAN BUG FIXED: my callee-status one-liner used `ls a b c` (exits non-zero if ANY glob misses)
  so it FALSE-NEGATIVED already-wired functions. func_02013814 (widest-line text metric) and
  func_020262a0 (THUMB variadic fwd) were reported unmatched but are ALREADY matched+wired. Re-derived
  02013814 to MATCH before noticing -- discarded. Correct check: test each path with -f individually.
- c36c's genuinely-unmatched deps are MAIN text primitives: func_02030278 (116B draw), func_020301c8
  (176B axis-offset draw), func_02013768 (172B line-measure).
- BLOCKER func_02013768 (build/try/13768.c, 148 vs 172, 24B short): line-width measure via a
  font->[4] getNextChar fn-ptr (blx r5) + two helpers 020136d4/0201371c. The ROM KEEPS a
  `cmp ret_d4,0xffff; ldreq r0,[font]; ldrheq r1,[font[0]+2]` block whose r1 is unconditionally
  overwritten by the next `ldrsb r1,[ret_1c+2]` -- mwcc eliminates it from every source form (dead).
  Reproducing it needs the CONTRACTS of 020136d4/0201371c (opaque glyph accessors, likely side
  effects). CONCRETE BLOCKER: Ghidra in this project does NOT define/decompile arm9_main (MAIN)
  functions -- only overlays are analyzed (create_function on ram:: / arm9_main:: both fail). MAIN
  text-primitive decode is stuck on that until MAIN is imported into Ghidra or the helpers are
  understood. NOT parked; best attempt held in build/try/.
- NEXT: func_02030278 / func_020301c8 (also MAIN, same Ghidra limitation) OR re-challenge held
  ov008 ties (6ed7c, 6c90c, cdb4, c7a0) which ARE in Ghidra.

## iter-71 (2026-07-30)
- INTEGRATED (user handoff) func_ov000_02059b14 = Ov000_DrawListScene (324B, 10 relocs) -- the LAST
  ov000 function. ov000 is now COMPLETE (262/262, 0 gap). Real C from the user (structs +
  intentional duplicate transferFlags store for mwcc scheduling); verified MATCH, replaced the
  asm_stubs twin (C+1/ASM-1), named Ov000_DrawListScene.
- MATCH func_02013768 = Text_MeasureLineWidth (172B, 2 relocs, MAIN). The iter-70 "blocker" was a
  DROPPED ARGUMENT: func_020136d4/func_0201371c take (font, ch) -- 2 args, ch in r1 -- so the
  ch->glyph value flows into the width lookup and the 0xffff default-glyph block is LIVE, not dead.
  Also: string cursor must be a LOCAL copy (homes only it, not all 4 args via push{r0-r3}); declare
  width before the getNext fn-ptr for r4/r5. Named + prototyped in Ghidra. Feeds 02013814 -> the
  ov008 menu label overflow check.
- ★ RETRACTED "MAIN not in Ghidra" blocker. MAIN (arm9_main 0x02000000-0204429f) IS loaded and
  1886 functions were ALREADY defined; the decompile failures were the WRONG ADDRESS PREFIX
  (arm9_main:: / ram:: fail; a BARE address like `02013768` works). Ran ~/ghidra_scripts/
  CreateMainFunctions.py (reads config/arm9/symbols.txt, clears range, sets ARM/THUMB TMode,
  disassembles + createFunction) -> made 63 more, 1949/1961 MAIN funcs now defined, 12 fail (main,
  FS_TryLoadTable, INITi_CpuClear32_0x0200093c, AutoloadCallback, a few func_0202xxxx -- odd
  boundaries, handle later). SAVED_OK. **MAIN text/draw primitives are now fully decompilable** ->
  the render frontier (02030278 draw, 020301c8 axis-offset draw, + ~600 MAIN gap funcs) is unblocked.
- NEXT: func_02030278 / func_020301c8 (MAIN text draw, now in Ghidra) to finish the menu render
  primitives; or continue ov008. Held ties unchanged (6ed7c, 6c90c, cdb4, c7a0).

## iter-72 (2026-07-30)
- MATCH func_02030278 = Text_DrawWithShadow (116B, 2 relocs, MAIN) -- FIRST TRY, now that MAIN is
  in Ghidra. Draws a text buffer with an optional drop shadow (offset +1,+1 one depth behind via
  func_020301c8 style 0x209, then the main copy). Used by c36c. Named. Style 0x209 is a pool literal.
- HELD func_020301c8 = Draw_WithAxisOffset (build/try/301c8_held.c, 172 vs 176, 1-instr). Quantises
  an orientation byte (0..7 at **(ctx+0x20)->[8]->[7]) to a signed (dx,dy) axis pair (0,7->(1,0);
  1,2->(0,1); 3,4->(-1,0); 5,6->(0,-1); else 0) packed as a 2-byte AxisOffset struct passed by value
  as the 7th arg to func_0201449c(ctx+0x1c,...). Residue: ROM holds L1=*(ctx+0x20) in r4 and zeroes
  the AxisOffset via a base pointer (add ip,sp,#0xc); mwcc uses direct sp stores (1 instr shorter).
  SAME base-pointer struct-init tie class as c7a0. ~7 forms tried (node var first/after, agg init,
  ptr p, chained zero, hold L2). Peer comment on it in Ghidra is accurate. Not parked.
- Menu render chain now: c90c(held) -> c690 -> c36c -> {02030278 done, 020301c8 held}. The label/
  glyph draw primitives are essentially all matched or held-1-instr.
- NEXT: func_0201449c (the actual glyph blitter, 7-arg, under Text draw) or continue ov008. Push
  window: re-gate 306/0 + push ahead-4.

## iter-73 (2026-07-30)
- HELD func_0201449c = text anchor/alignment (build/try/1449c_held.c, 288 vs 292, semantics EXACT).
  Measures text via func_0201386c(&dims, ctx[1..3], p6) [5-arg], then applies horizontal alignment
  (flags 0x10 center = -(w+1)/2, 0x20 = -w) and vertical (flags 2 center = -(h+1)/2, 4 = -h) as
  x/y += factor*axis using the (dx,dy) AxisOffset (param_7 by value), then blits via
  func_02014334(ctx, x, y, w, mode, flags, p6, off) [8-arg]. Structs: AxisOffset{s8 dx,dy},
  TextDims{int w,h}. Residue: the ROM SPILLS dims to a copy (sp+0x20) and re-reads it for the
  vertical/blitter args (plus keeps a DEAD copy at sp+0x10), while mwcc holds dims.w/h in registers
  and elides the copy (frame 0x20 vs 0x28, 1 instr short). A register-pressure/DCE spill artifact --
  SAME family as the c7a0/301c8 base-pointer-struct-init ties. ~8 forms tried (dead d1 struct/field
  copy, d1-for-horizontal, d2-for-func-only, vt=dims). Not parked.
- Menu text-render chain status: c36c/30278/13768 matched; 301c8/c7a0/1449c held (all 1-instr
  mwcc alloc/scheduling ties). func_02014334 (the actual glyph blitter, 360B) is the next unmatched
  primitive under 1449c.
- NEXT: func_02014334 (blitter) or re-challenge the held 1-instr ties as a family.

## iter-73 (cont.)
- MATCH func_0201386c = Text_MeasureBlock (148B, 1 reloc, MAIN). Multi-line text measure ->
  {maxWidth, totalHeight}; loops Text_MeasureLineWidth (func_02013768) tracking widest line +
  line count; height = (lines-1)*(spacing+fontLineHeight)-spacing. Feeds func_0201449c. Named.
  ★ VALIDATES the base-ptr struct zero-init crack: a FUNCTION-SCOPE 'TextDims dims = {0,0}' that is
  copied to *out via stmia DOES emit 'add r9,sp,#0; str; str' (the c7a0/301c8 residue) -- the
  trigger is aggregate-init + whole-struct copy-out, not field assignment. Compare order
  'if (w > dims.w)' as in func_02013814/1386c (cmp w,max; strgt).
- 1449c still held: its dims is func_0201386c's out-param (not zero-init) and the residue is a
  DEAD copy the ROM keeps (delay-DCE) + a spill mwcc elides -- not the same trigger, still 1-instr.
- NEXT: func_02014334 (the glyph blitter, 360B, last render primitive) or re-challenge held ties.

## iter-74 (2026-07-30) - MAIN text-render chain COMPLETE (leaf-ward)
Matched the whole draw path under the text anchor. All wired + named + structs in Ghidra:
- func_02014334 = Text_DrawAlignedLines (360B): multi-line layout loop; per line applies box
  align (0x800 right / 0x400 centre) from the measured width, renders via Text_DrawLine,
  steps along dir=(dx,dy). Cracks: px/py declared BEFORE ox/oy (register coloring); right-align
  offset as a named local so its mla takes (width-w) as multiplicand.
- func_02014280 = Text_DrawLine (180B): iterates glyphs via font getNext, blits each via
  Text_DrawGlyph, advances pen by (charSpacing+adv) along dir, reports next-line start via
  pNext. Cracks: glyph char passed UNMASKED (no (u16) -> no lsl/lsr); store c before deriving
  getNext (keeps font in reg, spills p5); pen advance as a fresh local (add keeps opts as rn).
- func_02014024 = Text_DrawGlyph (292B): glyph lookup (0xffff->default), metrics+bitmap ptrs,
  per-format pen adjust switch on glyphTable[7] {0/7,1/2,3/4,5/6}, dispatch to owner blit
  callback (*(fn**)(owner+0x14))[0] with {metrics,bitmap} GlyphDraw pair, return advance
  (s8 metrics[2]). Crack: fold +8 into the mla addend (glyph*stride + (glyphTable+8)).
- NEW Ghidra structs: TextDir {s8 dx,dy} (2B by-value dir), GlyphDraw {char* metrics; int bitmap}.
- Also integrated peer-lane staging match func_ov003_0204d55c = Ov003_DrawStatGrid (364B, handed
  over by user): 3x4 stat grid with column totals (deleted a hidden asm_stubs/CALLS/ twin).

FRONTIER now: the ONLY remaining piece of this chain is the anchor func_0201449c (held, 288 vs
292). Its residue is a mwcc "delay deadcode elimination" dead-copy: the ROM stores the measured
TextDims to sp+0x10/0x14 and never reads it. A plain `TextDim a=dims;` gets DCE'd. HANDED TO USER.
NEXT after that: whatever calls func_0201449c (the menu/HUD text-draw entry the port needs).

## iter-75 (2026-07-30) - MAIN draw-hub + math primitives
- MATCH func_0202fa38 = Text_DrawDirectional (176B): resolves text writing direction from the
  font layout-mode byte (glyphTable[7]) into a 2-byte dir and forwards to the anchor 0201449c.
  Crack: cache *(self+0x20) in a local declared BEFORE the aggregate `TextDir dir={0,0}` so mwcc
  keeps it in r4 across the base-ptr zero-init. Sibling of the held 301c8 (explicit offset).
- MATCH func_0202f188 = QuatFromAxisAngle (184B): unit quaternion from axis+angle; out[0]=cos,
  out[1..3]=sin*axis Q12; 64-bit magic-multiply angle->index into flat sincos table data_0203d210
  read as [idx*2]=sin,[idx*2+1]=cos. Cracks: single-expr angle scale (2nd idx assign spills idx*2
  to wrong reg); middle index shift logical (unsigned cast -> lsr); +round folded into 64-bit
  product; flat s16[] indexing not struct-array.
- IN INVESTIGATION func_0203084c = Session_RandNext (build/try/3084c_held.c, 84B): 64-bit LCG,
  multiply-add byte-exact, return artifact reproduced, register cascade unresolved (early-vs-late
  zero materialization pins session to r4). ~33 experiments. NOT parked.
- DATA NOTE (answered user): data symbols are never "decompiled"/matched - the delinker relinks
  them verbatim from the reference bins. They only get NAMED + TYPED in Ghidra for readability
  (e.g. data_0203d210 -> SinCos[]). That is naming, not decomp; it cannot touch the 306 gate.
- NEXT high-in-degree undone MAIN draw-hub primitives: func_020307f4 (63 callers, RandNextScaled),
  func_02031384 (70), func_0202f55c (81, 672B), func_0203034c (42).

## iter-76 (2026-07-30) - RNG + draw-hub primitives
- MATCH func_020307f4 = Session_RandNextScaled (88B): advances the GameSession 64-bit LCG,
  returns range==0 ? newHigh : (u64)newHigh*range>>32. Cracks: LCG written mult*seed (loads
  mult-first only for that order in the conditional-return context); scale multiply newHigh*range
  so the result high word lands in r0 (no extra mov); predicated tail (ldreq/umullne).
- MATCH func_0203034c = Draw_ScaledValue (104B): draws via func_02014174 with a cell width from
  self[0x38] (0x40/0x20), value self[0x10] / width through the 64-bit divide func_02020400.
  Cracks: copy param_5 to a local (keeps it in a reg vs spilling the modified param); pass the
  quotient to the u16 draw slot unmasked (no lsl/lsr).
- func_0203084c = Session_RandNext STILL in investigation (build/try/3084c_held.c): pure
  instruction-SCHEDULING tie confirmed by minimal-case diagnostic - mwcc emits the right form but
  won't hoist the return's 0<<12 above the multiply. ~41 experiments. NOT parked.
- NEW BLOCKER for later: func_02031384 (message-slot allocator, 70 callers) needs an inline `clz`
  and NO matched function in the tree produces one; __builtin_clz / __clz / MI_CountLeadingZeros
  all compile to a call, not the instruction. Need the mwcc clz intrinsic spelling. Deferred.
- NEXT: func_0202f55c (81 callers, 672B), then revisit 02031384 once clz is solved.

## iter-77 (2026-07-30) - Vec4/quat math primitives (slerp dependencies)
- MATCH func_0202f3b4 = Vec4_DotFx12 (124B, reloc-free): Q12 fx dot product, sum of
  (a[i]*b[i]+0x800)>>12 in index order 0,1,2,3 (Ghidra shows it reordered; the natural order is
  the source). Dependency of the quat slerp func_0202f55c.
- MATCH func_0202f4a4 = Vec4_Normalize (184B): magnitude via func_0202f430, else scale each
  component by 1/mag (func_01ff8a50 64-bit recip) with signed 64x32 mul-high +round. KEY crack:
  assign q[3] in BOTH branches (not a shared `last` local) so mwcc tail-merges the store through
  r0 -- that also fixes the sign-ext/umull scheduling. NEW general lesson: a shared tail store
  wants the value in a common reg; per-branch assignment + tail-merge, not a lifted local.
- IN INVESTIGATION func_0202fcb8 = Utf8ToUtf16 (build/try/2fcb8_held.c, 224 vs 216): flat else-if
  chain reproduced the ROM's predicated ASCII stores; open = multibyte bit-pack fold
  ((c&0x1f)<<16 folds to c<<27) + a c/cur register swap.
- SLERP func_0202f55c (672B, 81 callers) decoded but not started - 3 code paths, angle->index x3,
  FX_Sqrt, atan func_020050b4 (440B, undone). Large; deferred until the smaller deps are cleared.
- NEXT: crack the utf8 multibyte fold, or the atan func_020050b4.

## iter-78 (2026-07-30)
- MATCH func_0202fec8 = TileSurface_Init (142B, THUMB): inits a TileSurface from a TileSurfaceCfg
  (bpp 0x40/0x20, nRowBytes/nTotalBytes, clear+list-init+field-copy, conditional upload via
  func_02014174). Cracks: nRowBytes written rowTiles*bpp (keeps bpp in r0 across both THUMB muls);
  pCurrent/pPixels reads grouped in a block for the ROM's paired-load schedule; 7th arg to
  func_02014174 passed unmasked (no (u16)). Uses existing Ghidra TileSurface/TileSurfaceCfg types.
  Its 4 wrappers (ff8c/ff98/ffa4/ffb0) are already done.
- BLOCKER confirmed: func_02031384 + func_02031440 (message-queue subsystem, 70+14 callers) both
  need an inline `clz`. mwcc 3.0/139 has NO clz intrinsic - __CLZ/__clz/__builtin_clz/_CLZ all
  become external calls, and a shift-loop is not recognized. The ROM's clz must come from inline
  asm in the original source. Under the no-asm session rule these two are blocked pending a user
  decision on whether inline-asm intrinsics are permitted.
- func_0202fcb8 = Utf8ToUtf16 still IN INVESTIGATION (build/try/2fcb8_held.c): the (c&0x1f)<<16
  multibyte pack folds to c<<27 in ~15 experiments; only `volatile` keeps it (with spill); zero
  corpus precedent for `and; lsl #0x10`. ASCII half solved (flat else-if -> predicated stores).

## iter-79 (2026-07-30)
- IN INVESTIGATION func_02014174 = Tilemap_FillRegion (build/try/14174_held.c, 176B, indeg 7):
  size-exact + correct, residue = a 3-cycle callee-saved register rotation ({col+width,c,base2} ->
  r5/r7/r8 vs r8/r5/r7). ~25 experiments; real cracks found (cmp #0x20/bgt via mapW<=0x20, tile as
  int, ternary blk, hoisted palHi, single blk var), only the rotation remains. Same class as
  ov008 6ed7c.
- BLOCKER func_02020400 (indeg 375! the signed int divmod runtime): a computed-jump into an
  unrolled subtract-shift loop ((*(code*)(idx*0xc + 0x2020474))(...)). Hand-written assembly
  runtime routine (like __divmodsi4), NOT producible from C. Same category as the clz message-queue
  funcs - needs asm. This is the divide helper behind every integer `/` and `%`.
- OPEN QUESTION for user (unanswered): may inline-asm intrinsics be used for the runtime primitives
  (clz for the message queue; the divmod computed-jump)? They cannot be reached from pure C.

## iter-79 (cont.)
- MATCH func_02023eb4 = RandNextScaled (84B, indeg 1405 - the game-wide random source!): global
  64-bit LCG at data_0204c168, returns range==0?newHi:(u64)newHi*range>>32. Matched first try
  reusing the func_020307f4 pattern with a `result` local (kept in reg, not reloaded). Retracts
  the old deferred-tie note on this address.
- IN INVESTIGATION func_02023f08 = global RandNext (build/try/23f08_held.c, 80B, indeg 7): SAME
  (0<<12)|(hi>>20) return tie as func_0203084c, now CONFIRMED across two functions. 12-diff (size
  exact); the direct-struct access hoists mov #0 early but the OR operand order (which of 0<<12 /
  new_hi>>20 is the r0 accumulator) is not source-controllable. RNG state struct RngState created
  in Ghidra (seed@0xc, mult@0x14, inc@0x1c).

## iter-79 (cont. 2) - RNG + small MAIN helpers
- MATCH func_02034258 = ResSlot_Release (92B THUMB, indeg 63): refcount decrement + buffer free
  via NNSi_FndFreeFromDefaultHeap; new Ghidra ResEntry type.
- MATCH func_0203583c = Table_FindKey (56B THUMB, indeg 9): scan a record's key sub-array for a
  matching halfword; the NULL result is one local returned once (not per-path returns).
- IN INVESTIGATION func_02010f08 (build/try/10f08_held.c, 116B, indeg 16): 4-diff canonical-zero-
  register tie (ROM makes i/r5 the master 0; mwcc splits it to lr). Size exact, correct.
- BLOCKERS (need user call on inline asm): func_02020400 (divmod, indeg 375) + func_02020374
  (64-bit divide) are asm runtime routines; func_02031384/func_02031440 need inline clz.
- func_02020400 is the divide behind every int `/` and `%` - highest-impact blocked primitive.

## 2026-07-31 changed vein off the register ties -> GetTick64 (func_020031d4)

Per the "match-rate-too-low / cambia de veta" guidance, stopped grinding the confirmed register
ties (func_02031384, func_0201449c stay in build/try/) and selected a FRESH matchable frontier
function by reachability: func_020031d4 = OS_GetTick / GetTick64, 160B, 55 done callers (the tick
source every Tween stamps). Fully understood + build/try/31d4.c:
- MMIO: REG_TM0CNT_L (u16 @0x04000100) counter; REG_IF bit3 (@base+0x114) = timer-0 overflow.
  ONE pool word 0x04000100 is the base for both (mwcc collapses the +0x114 access).
- Accumulator: 48 bits at data_02044664 (nTickMid @+8 u32, nTickHigh @+0xc u16). Struct
  OsAlarmState confirmed from the matched sibling func_02003284 (the alarm setter); that sibling's
  header also documents the "mask the 64-bit value, not a u32 cast" crack -- so the read must be
  `*(u64*)&nTickMid & 0xffffffffffffULL` for the `& 0xffffffff` low mask to survive (mwcc writes it
  as `0xffff - 0x10000` to reuse the pooled 0xffff).
- Critical section: `state = OS_DisableInterrupts()` (state stays in r0 across the whole body),
  `OS_RestoreInterrupts(state)`. Return `(tick << 16) | count`.
- STATUS: 160B EXACT, instructions 16-35 byte-identical. Two levers found: (a) the ROM SPILLS the
  three working values (count u16 @sp+0, tick u64 @sp+4) to the stack -- reproduced by declaring
  count/tick `volatile` (the accumulator IS ISR-modified, so semantically defensible; without it
  mwcc keeps them in r4/r5/r6 -> 108B). (b) io base loaded AFTER the disable call so it doesn't
  cross it. RESIDUE: mwcc still parks the io base in r4 (callee-saved, push {r3,r4,lr}) where the
  ROM uses lr (scratch, stmdb {lr}); ~20 source variants (decl order, macros-vs-var, single-base,
  register kw, field-combine, addr-taken count) do not flip that one scratch pick. Same
  scratch-vs-callee-saved family as func_02031384. Left in build/try/31d4.c (NOT parked).

## 2026-07-31 STRATEGY: high-reloc functions break the register-tie streak

After 3 iterations stuck on scratch/spill register residues on LOW-reloc scalar/MMIO primitives
(func_0201449c, func_02031384, func_020031d4 -- all 2-3 relocs, all reg-alloc-exposed), switched
to the skill's own advice: pick MEDIUM funcs WITH MANY calls (100-250B, 8+ relocs) where the
reloc-masked bl's dominate and hide the regalloc noise. Ranked undone MAIN funcs by #done-callers
(reachability) AND reloc count, then worked them:
- func_020279e0 = Obj_InitChannelsAndRun (232B, 10 relocs, 55 callers): **MATCHED FIRST TRY**,
  integrated + committed. Lazy 3-channel init (INITi_CpuClear32 + func_02027978 per channel guarded
  by obj[2]/[4]/[6]) then dispatch func_01ffb8fc with a shared/scratch work buffer. Ghidra named +
  prototyped.
- func_02024ee8 = Msg_OpenContainerAndReadHeader (236B, 8 relocs, 31 callers): P2 message-container
  loader (db_<lang>.p2). SIZE-EXACT 236, only a 3-instruction register-swap residue in the header
  size calc (ROM reuses the dead `hi` register r1 for count*4 keeping half<<17 in r0; mwcc puts
  count*4 in r0=rd and moves half to r1 -- same op, swapped regs). Cracks that got it there:
  (a) it takes 2 params not 4 -- FS_OpenFile is 2-arg, param_3/param_4 are Ghidra phantoms (the ROM
  never saves r2/r3); (b) `OS_UnlockByWord_0x0200ae4c` is a MIS-NAMED FS_ReadFile (3 args file/buf/
  size), called for the 16B header and the table; (c) FS_CloseFile is 1-arg (rest phantom); (d) read
  the record count from the HIGH HALFWORD `*(u16*)((char*)&header+2)` (ldrh [sp,#2]), used for both
  `count = hi & 0x1ff` and `if (hi & 0x8000)`; (e) copy the 16B header to the buffer as a STRUCT
  assignment `*(P2Header*)buf = header` -> ldm/stm (field-by-field = 8 instr, 6 too many); (f) the
  table-size shift is UNSIGNED (`(unsigned)((count+1)/2) << 0x11 >> 0xf`, logical lsr) but the /2 is
  SIGNED (keeps the sign-correction add,lsr#31). Left in build/try/24ee8.c (NOT parked). The FSFile
  handle is 0x48B; buf[2]=file+8 (byte offset), buf[3]+=file+0x24 (length).

  LESSON: keep selecting high-reloc call-heavy funcs -- they match clean; the low-reloc scalar/MMIO
  primitives (message alloc, tick, text-align) are where the un-steerable regalloc ties live.

## 2026-07-31 (cont.) high-reloc vein: 2 more matches + 2 register-swap ties

- func_02024c94 = Res_LoadSpriteSet (212B, 7 relocs): **MATCHED FIRST TRY**, committed. Loads a
  sprite resource set (NRCS screen / NCGR char / PLTT palette, archive member kinds 6/1/0) into a
  3-pointer SpriteResSet; per slot: field=0; if(idx>=0 && (m=GetMember)!=0 && loader(m,&field)==0)
  field=0. Third slot is nested-if (ends the fn), first two are &&-chains. Ghidra SpriteResSet.
- func_02024ee8 = Msg_OpenContainerAndReadHeader: 236B SIZE-EXACT, build_sweep 0/27 CONFIRMED tie,
  3-instruction r0/r1 register swap in the header size calc. In build/try/24ee8.c.
- func_02024da4 (144B, 3 relocs / 2 calls-in-a-loop): OBJ ext-palette bank copier. 144B SIZE-EXACT,
  instruction stream byte-identical, only a 2-register swap (output counter `n` in r9-vs-r7,
  `bank-3` in r7-vs-r9). Cracks that got it size-exact: `n++` POST-INCREMENT in the MI_CpuCopy8
  address arg (so mwcc schedules the u16 increment BETWEEN the two calls and saves the old index,
  matching the ROM), and `int b = bank-3; b += i;` as two statements (so the `+i` fuses with the
  `<0` check into `adds`+`addmi` instead of a separate cmp). Same 2-register-swap family as
  func_02024ee8; ~8 variants (decl order, register, bankBase, u16/short) don't flip it. In
  build/try/24da4.c (NOT parked).

  Running tally of the vein: MATCHED func_020279e0, func_02033d0c, func_02024c94 (+ Slot_Spawn
  needed the `|`-order and fresh-global-read cracks). TIES (register-swap, all size/instruction
  exact, in build/try/): func_02024ee8, func_02024da4. The small funcs with 1-2 competing
  callee-saved counters are where the 2-register swaps live; the bigger call-sequence funcs match
  clean.

## 2026-07-30 frontier update (pushed ce4b2d5f6, C=15956)

Integrated+pushed last batch: Res_LoadSpriteSet (func_02024c94), Slot_Spawn
(func_02033d0c), Sound_UpdateSpatial (func_02032af0). data_0204c234 = shared
world/listener base (`base = *data_0204c234`).

Worked this iteration on two of Slot_Spawn's neighbours — BOTH byte-close ties,
left in build/try/ (see deferred-ties.md for the exact epilogue diffs):
- func_020329e8 (Slot_AllocFromPool) — register-coloring tie, 0-28 byte-exact.
- func_02012354 (object rebuild/refresh) — guard-predication tie, 0-39 byte-exact.

Next candidates on this frontier (high-reloc sequential-call vein, the validated
clean-match strategy — prefer these over the two ties above unless a fresh idea
for their epilogues appears):
- callees of func_02012354 not yet done: func_020122b8/fc/dc, func_0201231c,
  func_02011c7c, func_020118c4, func_0201285c (the transform-block setters).
- keep following Slot_Spawn / object-tick reachability, not overlay number.

## 2026-07-30 (iter 2) — graphics/palette upload subsystem (func_0201xxxx)

MATCHED + integrated (committed d618aef83, not yet pushed): func_020121c0
Pltt_Upload (texture/OBJ/sub-OBJ palette upload, switch(slot) 1/2/0 + ext-first
dwUseExt branch). Struct PlttUpload created in Ghidra.

The object/rebuild cluster (func_02012354 + its callers func_0201248x + the SRT
setters func_020122b8/fc/dc) is fully integrated except the two documented ties
(func_02012354, func_020329e8).

Frontier now = the func_0201xxxx sprite/palette/cell GRAPHICS subsystem (clearly
port-required: rendering). Next undone high-reloc candidates here:
- func_0201292c BgExtPltt_Upload — near-miss (SR tie, build/try/, see deferred-ties).
- func_02012a5c (272B, DC_Flush+MI_DmaCopy16/CpuCopy16, data_020422b8) — VRAM copy.
- func_02012f54 (204B, func_020149c4/func_02013484, data_02041ac0).
- func_020116f0 (336B), func_020111c0 (316B), func_02011b30 (276B).
Pick by reachability from the render path, not address order.

## 2026-07-30 (iter 3) — graphics-upload cluster is colour-tie-heavy

func_0201xxxx sprite/palette/char VRAM upload cluster: many live values + MMIO +
function pointers make it register-colour sensitive. Matched cleanly: func_020121c0
(Pltt_Upload). Near-miss colour ties (build/try/, documented): func_0201292c,
func_02012a5c (SR family), func_02012f54 (symmetric w/h swap). Structs created:
PlttUpload, BgPlttSrc, BgPlttReq, TexReq; functions named.

NEXT: pivot OFF this colour-tie-heavy upload cluster. Options on the render/frontier
path with different shapes: func_020116f0 (336B, 0 relocs - algorithmic, no reloc
noise), func_020111c0 (316B, 1 reloc), func_02011b30 (276B). Prefer algorithmic /
low-live-value functions to break the tie streak, per the "change vein when the
current one is tie-saturated" feedback.

## 2026-07-30 (iter 4) — LESSON: function-selection shape predicts tie vs match

Pushed func_020121c0 (Pltt_Upload) to origin (deb155767, C=15957). Then func_020116f0
(Resource_RelocatePointers, 336B, 0 relocs, nested-loop pointer relocation) came out
byte-exact in STRUCTURE but a pervasive register-permutation tie (build/try/116f0.c,
see deferred-ties). The for-loop form (not if+do-while) was the fix for the loop
shape; the residue is a whole-function callee-saved-vs-scratch permutation that 0
relocs leave fully exposed.

⭐ **Selection pattern across the last ~10 functions:**
- CLEAN matches: sequential-CALL functions, few/no loops (func_020121c0 switch+calls;
  earlier func_020279e0/02033d0c/02024c94/02032af0 - 8-13 relocs, straight-line). The
  reloc-masked bl's dominate and hide scheduling/regalloc noise.
- TIES: loop-heavy / 0-reloc / MMIO / function-pointer-dispatch functions
  (func_0201292c/02012a5c SR, func_02012f54 coloring, func_02012354 predication,
  func_020329e8 allocator, func_020116f0 register permutation). The allocation is
  exposed and mwcc's choice diverges.

**NEXT ITERATION: pick a SEQUENTIAL-CALL function** (5+ bl relocs, minimal loops) on
the reachable frontier - the caller side of the matched graphics/object functions
(e.g. func_02031c58 which calls Pltt_Upload) or scene-tick dispatchers. AVOID another
0-reloc nested-loop or tight-loop function; those are the tie vein.

## 2026-07-30 (iter 5) — sequential-call vein CONFIRMED: SpriteRes_Load matched

func_02031c58 (SpriteRes_Load, 312B THUMB, 18 sequential calls) MATCHED first-session
after the pivot to sequential-call functions (committed dc78224c0). The 18 reloc-masked
bl's dominated; the only work was arity (Ghidra over-specified: 3 params not 4,
Archive_LoadFile/func_02025464 2-arg here), stack-local order, 0xffff-via-mvns (-1),
u16 cursor bumps with no (short) cast, and the WM_EndKeySharing_0x020116e4 veneer name.
This validates the iter-4 lesson: pick SEQUENTIAL-CALL functions, not loops/0-reloc.

NEXT: keep the vein - the caller of SpriteRes_Load and its siblings in the func_0203xxxx
sprite/object-resource area. Look for 100-350B functions with many bl relocs.

## 2026-07-30 (iter 5b) — TWO sequential-call matches; two reusable cracks

Both matched cleanly, confirming the sequential-call vein (committed dc78224c0, 0cdad2c4e):
- func_02031c58 SpriteRes_Load (312B THUMB, 18 calls).
- func_0201c734 Obj_AttachResource (252B ARM, 10 calls, returns 0/1 with cleanup guards).

Two cracks worth reusing:
1. **Param used only in a late `*(base+N)` read, reloaded each use -> type it as a
   POINTER param.** func_0201c734 read param_5 as `*(uchar*)(param_5+6/+7)` and mwcc
   reloaded the base from the stack twice (+1 insn). Declaring `unsigned char *param_5`
   and using `param_5[6]/[7]` makes mwcc keep it in a callee-saved reg loaded once,
   matching the ROM's early load (the "Restarted...for space" allocation).
2. **Two stack out-params in the wrong slots -> reverse their declaration order.**
   mwcc assigned uStack_24@sp+8 / uStack_20@sp+4; the ROM wants +4/+8. Declaring
   `uStack_20, uStack_24` (the later-used one first) swapped them to match.

NEXT sequential-call candidates (from the iter-4 scan): func_0203c4a8 (280B, 7 calls,
0 data), func_0203b8bc (172B, 7 calls), func_0201cc50 (272B). AVOID func_020333c8
(has a 16-entry linked-list loop) and func_020116f0 (register-permutation tie).

## Iter L (2026-07-31) — MsgQueue_Enqueue MATCHED; Init two cracks landed

- **func_02030fdc = MsgQueue_Enqueue — BYTE-EXACT (268B ARM), integrated + gate 306/0, committed 30ac201ab (local, held for hourly push).**
  Cracks in the commit msg + .c header: len bitfield insert ((unsigned)param2<<22)>>16;
  payload = (u8*)hdr+2 fixes param colouring; writeOffset grouped wo+(param2+2); signed %2 pad.
  Ghidra: renamed MsgQueue_Enqueue, proto int(int id,int length,ushort*payload); created
  MsgQueueBuf/MsgQueueEntry/MsgQueueCtx types; typed all 11 data_0204c230 pool slots as
  MsgQueueCtx** (decompile confirms *PTR->entries[i].pActive->writeOffset, no one-short).
- **func_02030e7c = MsgQueue_Init — still in build/try (NOT parked), improved this pass:**
  colouring (ctx=r5) NOW matches via first-declared explicit `so` accumulator (vreg-flip),
  and alloc size NOW matches via `ctx->count<<5` CSE. Byte-exact through 0x2a. Remaining =
  proven 2-way add-order/colouring conflict (see codegen-cracks.md 2026-07-31) + inner-init
  order + 2nd-loop zero-share schedule. Best = build/try/30e7c_best.c.
- Message-queue subsystem map (all reference data_0204c230, indirect-dispatch registered via
  the func_02030fcc fn-ptr Init returns): matched = 020314a4 (MarkSlotReceived), 02030fdc
  (Enqueue). In-progress = 02030e7c (Init). Unresolved peers on the frontier: 02030f58,
  020310e8 (Table6 reset, called by Init), 02031130, 02031384, 02031440, 02031574, 0203158c.
- DOCS NOTE: README/PROGRESS byte metric (1,782,558 / 37.70%) is ~17KB stale vs the default-mode
  audit (1,800,118 / 38.06%, C=15962). Function count also 15961→15962. Left untouched pending
  a deliberate reconciliation of which byte measurement is canonical (do NOT auto-jump public %).

## Iter M (2026-07-31) — MsgQueue_Init narrowed 36 -> 8

- func_02030e7c still in build/try (NOT parked). Session progress: register-swap residue at
  session start (~36 off) -> 8 off, byte-exact through 0x40. Four levers landed: colouring flip
  (first-declared `so` accumulator), alloc `ctx->count<<5` CSE, inner init via `for(j=0,so=0;..)`,
  and `ctx->field0=0` placed before the template copy. Best = build/try/30e7c_best.c (colouring
  branch, +4 cracks). Remaining 8 = 3 add-order (proven mutually-exclusive with colouring) + 5
  2nd-loop preamble scheduler ordering. See codegen-cracks.md 2026-07-31 (cracks A-D).
- No new match integrated this iter (Init not yet byte-exact); func_02030fdc commit still local
  (30ac201ab), origin <1h so held.

## Iter N (2026-07-31) — MsgQueue_Init 8 -> 5, add-order conflict DISSOLVED

- func_02030e7c: 8 -> 5 diffs. The add-order/colouring "2-way conflict" documented in Iter M was
  WRONG: retype the offset as a `char *` (base as int) and the explicit accumulator produces the
  member-access add order. So colouring + alloc + init-order + add-order are ALL correct now;
  byte-exact through 0x7E. Only 5 left = template-copy preamble scheduler ordering (ldr r3 / movs r6
  / str field0 rotation). New crack recorded: codegen-cracks.md "CONTROL THUMB adds operand order
  via pointer-vs-int typing". Best = build/try/30e7c_best.c. Still in build/try, NOT parked.
- No new integrated match this iter. func_02030fdc commit still local (30ac201ab); origin 55 min,
  held (next iter clears the hour).

## Iter O (2026-07-31) — MsgQueue_Init at scheduler floor (5)

- func_02030e7c still 5 diffs, all in the 2nd-loop template-copy preamble. This iter ruled out the
  scheduler ordering via statement permutation: field0 before copy (5, best), after copy (13-15),
  do-while loop (5), idp/ids reorder (5-11). Diagnosis: ROM hoists `ldr r3` to slot 1 and lands the
  `str field0` at slot 5 (INSIDE the atomic ldm/stm copy, after the first ldm); with `params =
  data_02042110` as a single struct copy, mwcc puts field0 either just-before the copy (mine) or
  after it, never inside. Grep of 1616 matched funcs for `ldm rX!` immediately followed by a plain
  `str rZ,[rW]` (interleaved store in a memcpy) returned ~0 -- the ROM shape is rare, so my atomic-
  copy source structure differs from ROM's in a way I have not yet found. Still in build/try, NOT
  parked; every semantic/register/add-order property is correct (byte-exact through 0x7E).
- func_02030fdc commit still local (30ac201ab); origin 56 min, held (next iter clears the hour -> push).

## Iter P (2026-07-31) — func_02030fdc PUSHED; Init scheduler floor confirmed at 5

- PUSHED func_02030fdc (MsgQueue_Enqueue) to origin (d1802826b..30ac201ab) after re-running the
  306 gate green (306 OK / 0 FAILED). 0 commits pending now.
- func_02030e7c: still 5 diffs (scheduler), NOT parked, best = build/try/30e7c_best.c. This iter
  exhausted the remaining scheduling levers: chunked 8-byte copy (43, breaks the r3! walk), ids/idp
  before copy (13-16), volatile field0 store (5, no change), ids-first block (16). DEFINITIVE
  evidence: a full-corpus scan of all 15,564 real-C functions for the `ldm rX! -> str rZ,[rW]`
  interleave (ROM's exact field0-into-memcpy shape) returned ZERO hits -- the pattern exists in no
  matched function, so there is no reference C form to copy. The residue is mwcc scheduling the
  independent field0 store into the atomic struct-copy's ldm->stm latency gap; every source order
  places it before (j2, best) or after the atomic copy, never inside. ~50 experiments over 5
  iterations; all semantic/register/add-order properties correct (byte-exact through 0x7E).

## Iter Q (2026-07-31) — Init: build_sweep closes the build question (source-form residue)

- func_02030e7c still 10 bytes (5 THUMB instr) off, scheduler-only, NOT parked. This iter ran the
  definitive checks:
  * build_sweep (build/try/30e7c_best.c:func_02030e7c): ALL mwcc 2.0 and 3.0 builds -- including our
    3.0_patch4 -- give the IDENTICAL "10 off"; 1.2 gives wrong size (228/232), dsi 79-83 off,
    3.0_136 compile-fails. So no build reproduces ROM's schedule; the residue is purely source-form,
    not build-related (confirms the compiler is correct).
  * reloc scan: the whole msg-queue subsystem references data_0204c230; func_01fffbf4 (early
    boot-region 0x01fffxxx) is among the referrers, so the subsystem is boot-reachable -> the
    frontier selection is correct.
  * broadened corpus grep (ldm + store within 2 instr, no writeback): 17 hits, but all are
    block-load (`ldm rX,{...}`) struct reads, NOT the walking memcpy (`ldm rX!`) my target uses.
    The walking-memcpy-with-interleaved-store shape has ZERO precedent in 15,564 matched functions.
- CONCLUSION: byte-exact through 0x7E; the only residue is mwcc scheduling the independent
  `ctx->field0=0` store into the walking-memcpy preamble (ldr r3 hoisted to slot 1, field0 str at
  slot 5 after the first ldm). ~52 experiments over 6 iterations across every documented axis.
  Needs the ROM's exact 2nd-loop source structure (or a new scheduler insight) to cross the last 5
  instructions. Best = build/try/30e7c_best.c.

## Iter R (2026-07-31) — MsgQueue_Init semantic layer done (byte-match still at floor)

- No byte-match progress on func_02030e7c (still 5 instr / 10 bytes off, scheduler floor, verified
  build-independent last iter). Did NOT re-grind the ~52 exhausted experiments.
- Instead advanced the PORT layer for the selected function (hard rule "a match with no semantic
  layer is half done"; the port needs readable correct C, not byte-exactness):
  * Renamed func_02030e7c -> MsgQueue_Init in Ghidra (ret void*, the fn-ptr func_02030fcc).
  * Confirmed the ROM decompile is now readable via the MsgQueueCtx/Entry/Buf types created in the
    Enqueue iter: pMVar2->count=2, ->entries->slots[0].pBuffer/writeOffset/state, ->f0=0,
    Table6_ResetAll(), InstantiateClass(), AllocFromExpHeapWrapper(). Port-consumable.
  * Aligned build/try/30e7c_best.c to the same struct vocabulary (MsgQueueCtx/Entry/Buf, fields
    f0/state/pBuffer/writeOffset) so the whole subsystem reads consistently and integration is
    clean; still 5-off (struct renames don't change codegen).
- The C model in build/try IS correct and port-usable now; only the byte-exact scheduler residue
  remains open. func_02030e7c stays in build/try, NOT parked.

## Iter S (2026-07-31) — Init: field-by-field copy ruled out; floor holds at 5

- Re-examined Ghidra's readable decompile of MsgQueue_Init: it renders the template copy as
  field-by-field with `f0=0` between params[1] and params[2]. Tested that literally:
  * s1 field-by-field (`params.a=tmpl.a; ...`): 224 bytes (over by 4) -- mwcc does NOT merge
    individual field assignments into `ldm r3!/stm r2!`; it emits separate ldr/str. So Ghidra's
    field-by-field rendering is the DECOMPILE of the atomic copy's schedule, not the source shape.
  * The ROM's `ldm r3!` walking memcpy REQUIRES an atomic struct copy (`params = data_02042110`);
    chunked long-long copy = 43 (p1, prior), explicit j placement s2=5 / s3=15.
  * So the atomic struct copy is mandatory (r3! walk) and the independent f0=0 store cannot be
    source-interleaved into it; the 5-instr residue is purely whether mwcc hoists `ldr r3` to slot 1
    (ROM) vs slot 3 (ours) -- a scheduler choice not controllable from source. Confirmed
    build-independent last iter (all 2.0/3.0 builds = 10 off).
- func_02030e7c stays at 5-off in build/try (NOT parked); semantic layer done (MsgQueue_Init named,
  decompile readable, struct vocabulary aligned). Byte-match needs the ROM's exact 2nd-loop source
  or a scheduler insight; ~55 experiments exhausted across every documented axis.

## Iter T (2026-07-31) — MsgQueue_GetHeap matched (frontier dependency); Init held at floor

- DECISION: func_02030e7c (MsgQueue_Init) is exhaustively blocked (10 iters, ~55 experiments, all
  copy forms, build_sweep build-independent, no corpus precedent -- a source-uncontrollable mwcc
  scheduler residue at 5 instr / byte-exact through 0x7E). Per the skill's blocked-assigned-function
  guidance (leave best in build/try, report, wait -- NOT grind forever), it is HELD in
  build/try/30e7c_best.c, fully documented, NOT parked/nonmatching/abandoned, still the primary
  frontier. To keep the port moving on the SAME milestone, matched its direct dependency:
- **func_02030fcc = MsgQueue_GetHeap -- BYTE-EXACT (16B ARM).** The tiny handler MsgQueue_Init
  returns as a fn-ptr: calls NNSi_FndGetCurrentRootHeap and returns 0. src/calls/func_02030fcc.c,
  Ghidra-named, gate pending. Remaining subsystem peers: func_02030f58, func_020310e8
  (Table6_ResetAll), func_02031130, func_02031384, func_02031440, func_02031574, func_0203158c.

## Iter U (2026-07-31) — clz frontier cracked; MsgQueue_AllocSlot size-exact

- Surveyed the msg-queue subsystem: 6 peers already matched (f58, 10e8=Table6_ResetAll, 1440,
  1574, 158c, 01fffbf4). Remaining unmatched: 02031130 (clz dispatcher), 02031384 (clz slot
  alloc), 02031258 (20-case send gate), 02030b58 (receive dispatcher).
- func_02031384 = MsgQueue_AllocSlot: unmatchable(uncharted clz) -> SIZE-EXACT 188 this iter.
  clz idiom RESOLVED: mwcc 3.0 has no clz intrinsic (__builtin_clz/__clz/_CLZ all lower to a
  helper call, +8B); the project convention (func_02031440.c, committed) is a one-line inline-asm
  `static inline unsigned Clz(unsigned x){asm{clz x,x}return x;}` -- passes the ^asm/dcd check,
  real-C body. Pooled flags=0 (DAT_02031438) reproduced by explicit `unsigned z=0`. This unblocks
  the subsystem's other clz function (02031130). Remaining residue = register colouring (pooled 0
  in r6 vs ROM's lr, shifting idx/mask +1). Best = build/try/31384_best.c, NOT parked.
- func_02030e7c (Init) unchanged at 5-off scheduler floor in build/try.

## Iter V (2026-07-31) — MsgQueue_AllocSlot size-exact; colouring artifact isolated

- func_02031384 stays SIZE-EXACT 188 (clz cracked via the established Clz helper, pooled flags=0
  via `unsigned z=0`). Residue precisely isolated: ROM materialises the pooled 0 in TWO registers
  early (`ldr lr,[0]; mov r5,lr`) and keeps it in lr for the flags strb, which frees r6 for idx
  (ROM idx=r6/mask=r7); mwcc here loads the 0 into r6 (idx=r7/mask=r8, +1 shift). ROM has an extra
  early-0 live value my C doesn't produce -- a double-0 materialisation artifact. Tried: z decl
  order, 31440-idiom rewrite (int*base/char*slots -> 180, worse), moving the flags store earlier
  (no change). Best = build/try/31384_best.c, NOT parked. Needs the source shape that produces the
  second early 0 (vreg-flip) to push z into lr.
- func_02030e7c (Init) unchanged at 5-off scheduler floor.

## Iter W (2026-07-31) — AllocSlot colouring still finicky; recompute confirmed required

- func_02031384 stays SIZE-EXACT 188. Confirmed the recompute-from-mixed-bases form (blk for seqp,
  ctx for copy dst) is structurally correct: mirroring func_02031440's single `slots` base for the
  far offsets (0x744, 0xc8) CSEs and shrinks to 172. So 31384_best's structure is right; residue is
  purely the pooled-0 register (r6 vs ROM's lr) + the +1 idx/mask shift. ~16 colouring variants over
  3 iters (z decl order, explicit ptr vars=CSE-shrink, ret=0 double-0, 31440-idiom). Best =
  build/try/31384_best.c, NOT parked.
- func_02030e7c (Init) unchanged at 5-off scheduler floor.
- Both in-progress funcs are at finicky last-mile register/scheduler residues; every semantic /
  size / instruction-stream property is correct. Continuing per-iteration colouring grinding is
  low-yield without a new vreg-flip insight.

## Iter X (2026-07-31) — started MsgQueue_ResendForPeer (func_02031130) via clz crack

- func_02031130 = MsgQueue_ResendForPeer: unmatched -> 224/248 this iter using the established Clz
  helper (the clz crack now pays off on a 2nd subsystem function). clz slot-scan (31440 template) +
  3 state bitfield stamps + header copy + func_02031258(0xb,...) resend all semantically correct.
  Residues: middle bitfield `(lpi&7)<<2` fuses to insert idiom (ROM: explicit and#7 + lsl#2); state
  pointer mixes [base,idx*0x34] vs computed sb. Best = build/try/31130_best.c, NOT parked.
- func_02031384 (AllocSlot) unchanged: size-exact 188, pooled-0 register is an mwcc allocator
  artifact (Ghidra shows one source use; the mov r5,lr is allocator copy-insertion) -- not source-
  controllable. func_02030e7c (Init) unchanged: 5-off scheduler floor.

## Iter Y (2026-07-31) — ResendForPeer: ROM control-flow structure identified

- func_02031130: identified ROM's structure = clz scan with DUPLICATED clear+reclz in both if/else
  branches (two clear sites), `0x80000000` held in fp for the no-match clear. Single-clear form =
  224 (24 short); dup-clear form = 256 (8 over, best structure). ROM (248) is between: dup-clear
  with topbit held in fp (no-match) + rematerialised (match). Residue is now codegen-steer, not an
  allocator artifact: (a) force topbit into a held callee-saved reg, (b) middle bitfield insert
  fusion, (c) state pointer addressing. Best = build/try/31130_best.c (dup-clear structure), NOT parked.


## FRONTIER UPDATE 2026-07-31 (iter 5)
- func_ov008_020590b4 -> CLASSIFIED **platform-replaced** (pure DS display/VRAM bring-up:
  GX bank config + DISPCNT/blend/window/POWCNT RMW + VRAM clears; zero game semantics).
  It is the 5th instance of the documented "ov000 display SCHEDULING RESIDUE" (see
  codegen-cracks.md) -- toolchain axis fully closed across the family (27 builds, all
  pragmas/flags/-proc/-ipa/-lang) + ~58 local source forms. Best candidate preserved at
  build/try/590b4_best.c (@0x121, mask-accumulator form). NOT parked/nonmatching; kept for
  a future scheduler crack. Port replaces the display pipeline, so it does not block.
- NEW FRONTIER: **func_ov008_0205a3dc** (Ov008 menu-scene object constructor, 588B) -- the
  last unresolved dep of Ov008_SetupScene and genuinely game-semantic: MI_CpuFill8 the 0x528
  object, config-driven [0x6c] (LoadGlobalU8 -> 0x1000/0xaaa/0x2000), Projection_LoadDefaults,
  a per-sceneId switch building the resource name via OS_SPrintf (fmt1 for id 0, fmt2 for
  5/0x10/0x11/0x12, fmt3 default) from table data_ov008_0208e9c4[id] (stride 0x34), sequence/
  anim setup (RegisterSeqAndInit/BindAnimTrack), a second per-sceneId switch for the +0xb4
  halfword (id1->0xf8e4, {5,0xb,0xe,0x13}->0x71c, else 0), then func_0205a138/0205a1fc.
  STATUS: candidate build/try/a3dc_best.c at right SIZE (588) with the first switch's `cmp #5;
  bgt` matching (via `if (sceneId <= 5)`); remaining = sceneId register (ROM r1 vs mine r3),
  a +4 pool-layout shift (one extra instr / one fewer pool word), and downstream branch/
  call-site sharing. Switches must be if/else with SEPARATE OS_SPrintf calls (a C `switch`
  compiles 20-28B short; gotos tail-merge too far). Table modeled as SceneParam[0x34] array.
  Next: resolve the sceneId r1/r3 allocation + the pool word, then the 2nd switch.


### a3dc UPDATE 2026-07-31 (iter 6)
Both switches now structurally MATCH the ROM (candidate build/try/a3dc_best.c, 592 vs 588 = 4B/1
instr over). Cracks applied: SPrintf selection is a `switch(sceneId)` (case 0->fmt1;
5/0x10/0x11/0x12->fmt2 shared; default->fmt3) -- a C `switch` gives the cmp/cmpne chain the ROM
uses, NOT an `if`/`||` (which range-optimises to `sub;cmp;bhi`). Second switch (+0xb4 halfword)
is `switch(sceneId)` with SEPARATE case bodies (`case 5: h=0x71c; break; case 0xb: h=0x71c;
break; ...`) because the ROM emits 4 separate `ldr =0x71c; b join` blocks (does NOT merge them);
sharing via `case 5: case 0xb: ...` compiles 20B short. sceneId must be `int` (signed cmp
bgt/bge/blt), not unsigned (bhi/bhs/blo). Table = SceneParam[0x34] array (rule 5b).
REMAINING (register residue): (1) sceneId lands in r3, ROM uses r1 -- the val block
`ldr r1,[r4]; mul r0,r1,r0; ldr r2,[pc]=table; ldr r2,[r2,r0]` reuses r0/r2, mine spreads to
r0/r1/r2/r3; (2) 1 extra instruction (pool +4); (3) uVar1 case-body layout order (==5/==0xe
addresses swapped -- ldr-offset only). Next: get sceneId into r1 (try matched-tree grep for
`mov r,#0x34; mul` + switch; try val/switch register-tuning).


### a3dc UPDATE 2026-07-31 (iter 7) -- byte-exact EXCEPT one register
build/try/a3dc_best.c is now 588 B (right size) and byte-exact EVERYWHERE except one
register-allocation choice in the val+first-switch block: sceneId lands in r3 (mine) vs r1
(ROM). Cascade: ROM `ldr r1,[r4]; mul r0,r1,r0; ldr r2,[pc]=table; ldr r2,[r2,r0]=val`
(3 regs, reuses r0 for offset and r2 for table->val); mine `ldr r3,[r4]; mul r1,r3,r0;
ldr r0,[pc]; ldr r2,[r0,r1]` (4 regs). ~10 identical-mnemonic instrs differ only r1<->r3.
FIXED this iter: (1) phantom arg -- func_ov008_0205a138 takes 3 args not 4 (Ghidra invented
the trailing `6`; the ROM sets r3=6 only for func_02014e18); dropping it removed the lone
extra instruction -> 588. (2) uVar1 switch case-body order: cases must be written
`1, 0xe, 5, 0xb, 0x13` (ROM body emission order) -- fixed the bge/beq target diffs.
REMAINING: force sceneId into r1. Tried ~17 val-block source forms (struct-array, raw
offset, offset local, entry ptr, tbl ptr, &elem deref, 0x34*sceneId, *param_2-direct,
decl order, register hints, int* vs uint* param_2) -- all give r3. No matched function in
the corpus has `mul r0,r1,r0`+`ldr r2,[r2,r0]` (the ROM's reuse form), so no template.
Next ideas: the interleaved `cmp r1,#5` (ROM schedules the switch's first cmp into the
table load-use stall) may be the lever -- find a source shape that makes mwcc reuse r2 for
table->val (3-reg allocation), which frees r1 for sceneId.


### FRONTIER UPDATE 2026-07-31 (iter 10): func_ov008_0205a138 MATCHED
Advanced from the register-stuck Ov008_Menu_InitSceneObject (0205a3dc, byte-exact except one
register, candidate preserved in build/try/a3dc_best.c, semantic layer done) to its unresolved
DIRECT DEPENDENCY func_ov008_0205a138 = **Ov008_Menu_LoadSceneText** -- MATCHED byte-exact
(140 B, 8 relocs), first try. It builds the message-container name from SceneParam[sceneId].f0
via OS_SPrintf, opens it as msg unit 0xe into obj+0x1b4 (scene 0xe re-opens from a fixed name),
then Ov008_LoadCharacterWeapon(obj+0x4d4, sceneId, slot). Reuses the SceneParam Ghidra type.
Ghidra: renamed + prototyped + pool slot 0205a1b8 typed SceneParam* (SAVED). Note: func_02024ee8
(Msg_OpenContainerAndReadHeader) is 2 args (name, unit) -- Ghidra's r2/r3 args are phantoms; and
OS_SPrintf's 4th arg is param4 passed straight through (r3 never reloaded).
Remaining unresolved dep of the scene constructor: func_ov008_0205a1fc (480 B, next).


### FRONTIER UPDATE 2026-07-31 (iter 10 cont): func_ov008_0205a1fc MATCHED
func_ov008_0205a1fc = **Ov008_Menu_BindScenePanels** -- MATCHED byte-exact (480 B, 13 relocs).
Binds up to 3 named panel resources per scene: for each non-empty SceneParam name (name1/2/3),
ResDict_FindIndexByName in the scene dict (obj+0x5c +0x40), store index at obj+0x148/0x14c
(+valid flag 0x140/0x144), init the panel sub-object (0x1b8 for names 1&3, 0x31c for name 2)
via func_02059c88 (msg obj+0x1b4, sceneId, char obj+0x4d4, slot 1/2/3) + Ov008_BuildPanelIdSummary.
Crack: the `obj+0x5c ? +0x40 : 0` test must be written NON-ZERO-branch-first
(`if (x!=0) d=x+0x40; else d=0;`) to get the ROM's `addne; moveq`; zero-first gives `moveq; addne`.
STRUCT: extended the Ghidra SceneParam type to its full 0x34 layout
{int nValue; char name1[0x10]; char name2[0x10]; char name3[0x10]} (this block revealed the names).
Ghidra: renamed + prototyped + pool slot 0205a3d8 typed SceneParam* (SAVED).
Ov008_SetupScene is now FULLY RESOLVED except Ov008_Menu_InitSceneObject (0205a3dc, byte-exact
except the one sceneId register, candidate preserved). Next milestone: the menu STATE DISPATCHER
/ per-frame tick (after scene setup).

## Frontier update (2026-08-01, fire ~iter96)

Constructor func_ov002_020679d4 dependency cluster:
- func_ov002_020765f8 (Ov002_SetSceneObjectsActive) — **MATCHED+integrated+committed+pushed**
  (18848633e). Crack: reference the scene-manager global directly (array form) so mwcc re-loads
  its pool address per branch -> branch-form arms (no predication) + inline scaled list index.
- func_ov002_02078e18 — body BYTE-EXACT; 2-instr entry residue (eager vs lazy param spill;
  manager temp r0 vs r1). Best candidate build/try/78e18.c. See codegen-cracks OPEN RESIDUE.
  DO NOT park — active frontier; resume here.
- func_ov002_0207185c (252B THUMB) — not started.
- constructor func_ov002_020679d4 (968B THUMB) — after the deps.

Gate iter96: 306 OK / 0 FAILED. Last push 18848633e @ ~01:52 (020692a8, 02076924, 020765f8).

## Frontier update (2026-08-01, later same fire) — 02078e18 SOLVED
- func_ov002_02078e18 (Ov002_EnsureSceneManager) — **MATCHED+integrated+committed** (0f3508683).
  Crack: int-returning, `return sceneId` on the exists-path pins param in r0 across the null check
  -> lazy spill in the delay slot + manager temp r1; fall off the end on the create path (explicit
  `return 0` would add movs r0,#0). See codegen-cracks CRACK "return the parameter to pin r0".
- NEXT frontier: func_ov002_0207185c (252B THUMB), then constructor func_ov002_020679d4 (968B THUMB).
- Local commits ahead of origin after next gate: 0f3508683 (78e18). Last push 18848633e @ ~01:52.

## Frontier update (2026-08-01, later) — 0207185c SOLVED
- func_ov002_0207185c (Ov002_AllocSceneState) — **MATCHED+integrated+committed** (a503aeb9a).
  Cracks: pointer-cursor loop (single obj+i*0x10c accumulator, byte at +0x21c); signed char for the
  -1 index bytes (0xc/0xd/0x2298) keeps -1 as full 0xffffffff (subs/mvns) so 0xff never lands in a
  register, forcing 0x104/0x105/0x110 to be built as 0x41<<2 (matches ROM's constant economy).
- Constructor dep cluster now COMPLETE: 020765f8, 02078e18, 0207185c all matched.
- NEXT: the constructor itself func_ov002_020679d4 (968B THUMB) — the big one.
- Unpushed: 0f3508683 (78e18), a503aeb9a (7185c). Last push 18848633e @ ~01:52.

## Constructor func_ov002_020679d4 (968B, 65 relocs) — PREP for next fire
Master gameplay-slice constructor; orchestrates the whole cluster. Structure:
- Head 0x00-0x11e: heap (NNSi_FndGetCurrentRootHeap), func_02023588 x2, 0206e718, 02023bf0,
  02020aa8, card path (02030670, CARDi_GetRomAccessor, 02030788, 02069240, MI_CpuFill8, 020350c8,
  020235e8), OS_SPrintf (string build), 02024ee8, 020693cc.
- Mid 0x120-0x19e: ~30 consecutive init calls (mostly the matched ov002 funcs: 020697cc, 0206a230,
  020697e8, 02069c24, 0206a2b8/2e8/080/0f4/29c/2cc, 02069798, 0207185c, 020734e8, 0202b73c, 02076924,
  0206eabc, 0206f444, 0206fb5c, 0206da28, 020636dc, 02069b70, 020763c8, 020765f8, 02078e18, 0206b910,
  0206da54) — largely mechanical sequence.
- Tail 0x1aa-0x29c: MI_CpuFill8, func_02023c40 (big body/loop between 0x1c2 and 0x23a), MI_CpuFill8,
  02069c04, 02035c28, NNSi alloc, 020235d0, 0206e640, 020235e8.
Data globals touched: data_0204c23c/240/248/254/4d8, data_ov002_0207efb0/efbc/efc0/f134/fa00.
Approach: carve head + mid + tail; the mid run is the easy part. Start fresh next fire.

## MILESTONE (2026-08-01) — gameplay-scene constructor MATCHED
- func_ov002_020679d4 (Ov002_ConstructGameplayScene) — **MATCHED+integrated+committed** (6becad02e).
  968B THUMB, 65 relocs, mid-function literal pool. Returns the first tick handler
  (02067d9c if link session active via func_02030670, else 02067f78). Cracks: card flag merged
  store; hard-mode reward loop counter-before-pointer register order; scene-transition switch cases
  in body-emission source order (5,6,4,0x6c,0x6f,0x514,0x72,0x515). Scene-transition table
  (mission id -> data_0204c23c) documented in the .c comment.
- data_ov002_0207fa00 = root heap base; the gameplay session lives at heap+0x8xxx (GameSession).
- NEXT frontier: the constructor's init-chain callees that are still unmatched (they run during
  scene setup, i.e. before the first tick). Enumerate and take the earliest.

## Frontier update (2026-08-01, later) — first-tick core, MAIN dep matched + interpreter in progress
- func_020350c8 (Game_ApplyModeFlags) — **MATCHED+committed+pushed** (2dc7b4e89). MAIN dep of the
  constructor. func_020235e8(id,1,bit?1:0) for bits 0-3 of data_0204c240; 3rd arg is u16.
- Pushed 18848633e..2dc7b4e89 @ ~02:53 (78e18, 7185c, constructor, 350c8). Gate iter100 = 306/0.
- First-tick handlers 02067f78/02067d9c: all callees matched EXCEPT func_02020e58.
- **IN PROGRESS FRONTIER: func_02020e58** (496B THUMB, MAIN) — the gameplay command/script
  interpreter, called by Ov002_TickGameplayState (02067f78). Runs the 5-slot callback array at
  cur+0x20 (fn/arg pairs, clear on nonzero return), an action callback at cur+0x18, then a command
  loop: cur=st+4+st[0x124]*0x48 (stride 0x48 entries), cmd=cur[0x10], handler=data_020425ec[cmd[0]],
  hb=handler+cmd[1]*8; field=(cmd[2]>>0xb)&0x1f; if field==0 dispatch hb->fn(st,cmd+4) through a
  7-way JUMP TABLE on the result (0->set e+0x18=hb[4]+return1; 1->clear+advance+loop; 2->clear+loop;
  3->return0; 4->queue-pop (st[0x124]--, st[0]-=e[4]); 5->loop; 6->advance+"case6 tail"); else store
  hb[4]/e[0x1c] into e+field*8 slot and advance+loop. Advance = cmd + ((*(u16*)(cmd+2)&0x7ff)<<2).
  case6 tail (also action-result==0 path @0x19a): func_020217d4(st[0x128]+0x30 + (idx+idx<<6)<<2),
  then if func_02020a84()==2 && (func_02020a9c()&0x102)==0 -> func_02020e20(...+0x26), return 1.
  Callees: func_02020d44, func_020217d4, func_02020a84, func_02020a9c, func_02020e20;
  data_020425ec (handler table), data_0204be04 (idx byte).
  Draft in build/try/02020e58.c = 500 vs 496 (structure right; residue: mwcc emits `sub sp,#8`
  (2 stack slots) vs ROM's single r3-padding [sp] slot holding st+4 -> reduce locals / cache st+4
  in one var). NEXT: tune register pressure to drop to one stack slot. DO NOT switch off it.

NOTE (2026-08-01): caching st+4 in a var makes it WORSE (504). The 2-slot spill needs fewer
simultaneous live locals (e/cmd/hb/base) - reduce by reusing regs like ROM (r4=e, r5=cmd, r7=hb,
[sp]=st+4, no extra). Best candidate build/try/02020e58.c = 500 vs 496.

## func_02020e58 progress (2026-08-01, fire cont.) — STILL IN PROGRESS, do not park
Best candidate build/try/02020e58.c (else-form) = 500 vs 496. Progress this fire:
- Whole first half (0x00-0x87: callback loop + action dispatch) is BYTE-EXACT.
- Fixed: field spill (recompute after blx, not cache) -> single [sp] slot like ROM; action dispatch
  as switch(r) not if/else-if; merged the two return-1 paths (case0 -> case6_tail, removed the
  duplicate); callback init order (for(i=0,e=cur;...)); handler-null as if(h!=0){hb}else{null;goto}
  which makes the block order match ROM (beq null, hb block b process, null block, process).
- REMAINING (2 hard mwcc residues):
  1. e/cmd register swap: ROM e=r4/cmd=r5 throughout the mainloop; mwcc gives e=r5/cmd=r4. Pure
     r4<->r5 relabel (structure matches under normalization). ~15 experiments (register/volatile,
     decl order, scoped iterator, cast forms, count temp) did NOT flip it. Global allocation tie.
  2. +4 bytes at the 2nd func_02020e20 call: ROM materializes offset 0x128 as (r1=0x102 from the
     tst mask)+0x26 = adds r1,#0x26 (1 instr); mwcc recomputes 0x4a<<2 (2 instr). Constant-reuse
     optimization; writing 0x102+0x26 in source folds back to 0x128.
  NEXT: crack the e/cmd swap (try: change what register the callback iterator uses so the mainloop
  add lands in r4; or a struct-typed entry pointer). Then the offset-reuse +4.

ATTEMPT (2026-08-01): moving e+=8 to the for-increment (i++, e+=8) did NOT flip e/cmd. The
"most-recent-register" hypothesis is wrong. e/cmd swap remains open.

## func_02020e58 (2026-08-01 fire 3) — e/cmd swap EXHAUSTIVELY resisted; still frontier
Best candidate build/try/02020e58.c (char* else-form) = 500 vs 496. Also build/try/02020e58_st.c
(full struct-typed rewrite: Entry{script@0x10, Slot slot[6]@0x18}, GameState{entries[4]@4,
count@0x124}) — identical result (500, 264 diffs, same swap), kept for readability/future.
TWO residues, both hard mwcc-specific:
  A. e/cmd register swap: mainloop `adds` for e -> r5 (ROM r4); cmd load -> r4 (ROM r5). Pure
     r4<->r5 relabel; structure matches under normalization. This fire ruled out (all no-effect):
     all 24 pointer decl-order permutations; register on e/cmd; type-alias (cmd as int*, e as
     int*); FULL struct typing; init/increment order (i++ before/after e+=8, confirmed callback
     iterator is now r4 like ROM); scoped iterator. ~50 experiments total across 3 fires.
     Callback loop is byte-exact (iterator r4, i r5); the mainloop's fresh `e` add just won't take
     r4. Appears to be mwcc giving the earlier-USED value (cmd, used at cmd[0] immediately) the low
     register r4, while ROM gives the first-COMPUTED value (e) r4.
  B. +4: 2nd func_02020e20 call materializes offset 0x128 as 0x4a<<2 (2 instr) vs ROM's adds
     r1,#0x26 reusing the tst mask 0x102 (1 instr). Constant-CSE micro-opt; not forced by writing
     0x102+0x26 (folds to 0x128).
  NEXT IDEAS (untried): grep the matched corpus for a function with `base+count*stride` entry +
  `entry[off]` cmd both landing r4/r5 and copy its C shape; or try making e's first USE precede
  cmd's (an e store before the opcode read) if a semantically-equivalent reorder exists.

## MILESTONE (2026-08-01) — first gameplay tick fully backed by C
- func_02020e58 (Game_RunActionScript) — **MATCHED+integrated+committed** (18d02e304). The gameplay
  action/command interpreter, last unmatched callee of the first-tick handlers. 3 fires; cracks in
  codegen-cracks.md "CRACK BUNDLE: func_02020e58".
- The ov002 gameplay slice is now real C end to end: constructor -> first-tick handlers
  (02067d9c/02067f78) -> action interpreter. The PC port can now run a gameplay frame's control
  spine.
- NEXT frontier: the action-command HANDLERS in the data_020425ec table (the opcodes the
  interpreter dispatches), and/or the callees of Game_RunActionScript still unmatched
  (func_02020d44, func_020217d4, func_02020a84/a9c, func_02020e20). Enumerate next fire.

## Frontier update (2026-08-01, fire 4) — action interpreter callees done
- func_02020d44 (Game_UnwindActionStack) — MATCHED+committed. Pre-tick unwind of the entry stack
  to a saved depth; cancel-sentinel callback cleanup.
- func_020217d4 (Game_UpdateObjectMotion) — MATCHED+committed. Per-frame object transform update
  (state switch on obj+0xf8; default composes a delta transform on stack scratch). Crack: int[]
  stack scratch (not char[]) so scalar RMWs address sp-relative; state test as a switch.
- Game_RunActionScript's direct callees are now ALL matched (02020d44, 020217d4, 02020a84/a9c/e20).
- 3 commits this fire (18d02e304 02020e58, +02020d44, +020217d4). Gate i103=306/0; pushed 2dc7b4e89..9dbd96c58 @ ~03:58.
- NEXT frontier: the action-command handler table data_020425ec (the opcode handlers the
  interpreter dispatches to) and/or the transform-commit chain (func_02023cc0, func_02021418,
  func_0202e53c, func_02022654). Enumerate data_020425ec's handler entries next fire.

## Frontier (2026-08-01, fire 5) — func_02023cc0 IN PROGRESS (register fixed, scheduler residue)
Selected func_02023cc0 (176B ARM, transform-commit; called from Game_UpdateObjectMotion in every
state, earliest via state-0). Progress: func_02004d60 setup+call (struct-by-value -> ldm) MATCHES;
the two GX RMWs FIXED by modeling data_02047394 as the tree's GX struct (field_d4) instead of a
cast byte offset (51->22 diffs; see codegen-cracks "GX/hardware register block"). Remaining 22
diffs = pure list-scheduler ordering of the 3-VecFx32 copy block (obj+0x20/0x2c/0x14 ->
data_02047394.field_218/224/230): mwcc emits the p14 pointer `add` one slot later than ROM;
identical instruction multiset. ~30 experiments (decl order, ptr vars, struct fields, MtxFx33
permutation, volatile, ret type) did not move the add-placement. Best candidate build/try/23cc0.c.
NOT a register/arity/aliasing problem. DO NOT park - continue; next idea: find a matched ARM func
with a 3-consecutive-stm{r0,r1,r2} copy block sharing this RMW-then-copies-then-call context and
copy its C shape (candidates: func_ov270_020d62fc, func_ov115_020cc9bc).
Also still unmatched on the tick chain: func_02021418 (954B, motion step).

## Frontier (2026-08-01, fire 6) — action-command handler table decoded; 2 matches
- **func_02020ab4 -> Archive_FindNameIndex** MATCHED+committed (1a6dc3904). Name->index lookup over
  an archive name table (member 0: u16 count, u16 offsets[], NUL names; strcmp each). Crack: char*
  base + `i*2+2` index (not cached count + struct subscript) keeps the offset-table read a base
  re-add with the SR counter init in the loop preheader; folds to 56B otherwise. Dep of
  Game_PushObjectSlot.
- **func_02021e84 -> Game_ActionAssign** MATCHED+committed (6612fdf54). rec0 (sub-index 0) of the
  data_020425ec dispatch table = operand-to-operand assignment (mode 8 copy slot->slot, mode 4
  eval+emit). Matched first try. Named callees ActionVM_ResolveOperandSlot (func_020218a4),
  ActionVM_EvalOperand (func_02021980); struct OperandSlot.

### data_020425ec dispatch table — DECODED (do not re-derive)
- data_020425ec[0] = 0x02042640; [1..15] = 0. Single handler group at **0x02042640**: array of 8-byte
  records **{handler_fn, callback_fn}**, BOTH THUMB function pointers (addr|1). Interpreter:
  hb = 0x02042640 + cmd[1]*8; calls *(fn*)hb; installs *(fn*)(hb+4) into an entry callback slot.
- Nearly all handlers already matched. UNDONE handler_fn (by sub-index): rec0 DONE this fire;
  **rec2 func_02021f7c** (352B, blocked: deps func_0201ed3c + func_02024ee8 + func_ov023_02083cc4
  all nonmatching/tie); rec8 func_020221a0; rec10 func_020221f8; rec13 func_020222bc; rec16
  func_0202237c; rec26 func_02022544. UNDONE callback_fn: rec18 func_02022448 (22B).

### This band is CODEGEN-TIE-DENSE (measured this fire) — pick carefully next time
- **func_0201ed3c** (FS resource loader, dep of rec2 func_02021f7c): byte-exact EXCEPT one instr —
  the ext-class check `if(0<=c<0x80) c=tbl[c];` PREDICATES (ldrlt/ldrblt) but ROM BRANCHES (bge over
  a 2-instr block, shared tail). 360 vs 364. Documented if-conversion threshold artifact
  (codegen-cracks L1262+); same mechanism as parked func_0201ef9c. ~13 experiments incl. surrounding
  context. Branch orientation FIXED (handle-first). Candidate: build/try/ed3c.c. NOT parked.
- **func_020221a0** (rec8 handler, fires callback slot operand[0]-1): 3-diff reg-alloc tie — the
  (idx-1) temp lands in r1 in-place vs ROM's r2 (reuse of freed count*0x48 reg); reconverges, 62B.
  Big win was inline `if(*fnslot!=0)` test (13->3 diffs). ~14 experiments. Candidate: build/try/21a0.c.
- **func_020221f8** (rec10 handler, arms st+0x584/0x588 jump-target the interpreter checks at tick
  top): mwcc OVER-optimizes vs ROM — derives adjacent offset 0x588=0x584+4 where ROM uses two
  separate pool literals, + a register cascade; 30 diffs, 60 vs 68B. Not pursued past first passes.
- **NEXT-FIRE RECOMMENDATION**: this handler band mirrors the "saturated dispatcher census" warning
  (feedback_match_rate_too_low). Either (a) crack ONE specific tie above with a fresh lever, or
  (b) move the frontier to a non-tie vein: the rec2 dep func_02024ee8 (P2 header loader, nonmatching
  with a fixable-looking `half<<16>>14` vs `<<17>>15` shift-width note), or a different reachable
  scene. Do NOT grind the whole band.

## Frontier (2026-08-01, fire 7) — action-VM subsystem is systematically tie-dense; 0 matches, 2 fresh near-matches
- Worked 4 functions on the action-VM/operand frontier; ALL hit distinct mwcc canonicalization
  residues at 1-5 diffs. Best forms in build/try/ (NOT parked, NOT nonmatching).
- **func_02024ee8** (P2 header loader, dep of rec2 func_02021f7c) - re-attacked its existing
  nonmatching. Two coupled residues: callee-saved register cascade (param_2/buf/sz = r6/r4/r5 in
  ROM vs r5/r6/r4 mine) + `half*4` computed as `<<17>>15` (15-bit) in ROM vs `<<16>>14` (16-bit)
  mine. ~12 experiments (cast placement, count type, decl order, explicit word var) - neither
  moves. Left in its pre-existing nonmatching/.
- **func_0202119c** (MTX_MakeRotXY43, dep of Obj_PrepAltTransform) - existing nonmatching, "value-
  hold" tie (ROM holds masked angles in r5/r4; mwcc holds raw + remasks). Tried unsigned short
  PARAMS (fresh axis vs the note's pre-masked locals) -> 100B, mwcc drops the entry masks. Confirms
  the note; swept 27 builds already. Left in nonmatching/.
- **func_02021208 = Anim_InterpEased** (FRESH, dep of Obj_StepMotionTransform) - quadratic FX ease,
  8x FX_Mul (func_02005418). **DOWN TO 1 REAL DIFF** (build/try/21208.c). Fixes: cmp `<=0x1000`
  not `<0x1001` (builds the const via movs+lsls vs pool load); expr grouping `param_2 - param_3*2
  + param_4`; explicit CSE `int p3x2=param_3*2` in branch 2 (it's used twice there); temp
  `t=param_2*2+uVar1` for branch-1 first add. Remaining: branch-1 final add `sum+uVar2` encodes
  `adds r1,r3,r1` (uVar2 as Rn) vs ROM `adds r1,r1,r3` (sum as Rn) - register state IDENTICAL, pure
  commutative encoding. ROOT: branch 2's p3x2 is used twice (HELD in callee-saved) so mwcc
  canonicalizes the final add with the accumulator as Rn; branch 1's param_2*2 is used ONCE (fresh)
  so mwcc canonicalizes the other way. No natural 2nd use of param_2*2 in branch 1; forcing one via
  -(2p+p) breaks the mvns/muls first arg. ~25 experiments.
- **func_020218a4 = ActionVM_ResolveOperandSlot** (FRESH, dep of Game_ActionAssign AND
  ByteCode_ResolveOperand - central) - operand->slot resolver. **DOWN 69->~5 DIFFS**
  (build/try/218a4.c). Fixes: operand type is SIGNED (short*, ldrsh); func_020235d0
  (GameState_GetField) takes two u16 params; nested &4/&8 tests written POSITIVE (ROM inverts ==0);
  type mask `& ~0x8c` (bics) not `& 0xff73` (pool load, +4B - this fixed the size). Remaining ~5:
  branch-0x80 tail - ROM keeps offset 0x578 in a reg and uses register-offset stores `strh
  r2,[r5,r1]`, computing the return pointer separately at the end; mwcc CSEs the return address
  (param_1+0x578) with the strh and stores via the absolute pointer. offset locals / char* / early-
  return / value-temp don't break the CSE. Looks like a compiler CSE-aggressiveness diff.
- **PATTERN (5+ functions across fires 6-7)**: the 0x0202xxxx action-VM/transform/loader subsystem
  shows SYSTEMATIC mwcc 3.0/139 canonicalization residues (value-hold, commutative-encoding,
  if-conversion-threshold, addressing/return-CSE, callee-saved reg cascade). Fresh functions hit it
  as often as re-attacked nonmatching. Matches the func_0202119c note's "retail = 3.0 >=140"
  hypothesis. NEXT-FIRE: move the frontier OUT of this subsystem - try an earlier reachable scene
  (ov000 boot/logo/title deps) or a different vertical-slice layer (input, collision, HUD), whose
  functions may not share this codegen profile. build_sweep.py on 21208.c/218a4.c could also test
  whether ANY of our 27 builds closes the 1-diff / 5-diff residues.

## Frontier (2026-08-01, fire 8) — MATCH: Anim_GetBlendFactor; anim/transform math vein is clean
- **func_0202136c = Anim_GetBlendFactor** MATCHED+integrated+committed+PUSHED (c0f3c1a43). Eased
  blend-factor from a mode switch (jump table), FX_Inv / func_02020400 (64-bit divide, low word) /
  sincos table (data_0203d210). Gate VERDE 306/306. NEW CRACK (codegen-cracks.md): Ghidra hides a
  REUSE - it prints `iVar1 = q + 0xc000` where the ROM does `iVar1 = q - 0x4000; if (iVar1 < 0)
  iVar1 += 0x10000` (reusing the biased iVar1, 0x10000 = the 0x4000 reg <<2). SinCos struct created.
- **KEY LESSON**: the anim/transform MATH vein (0x0202xxxx, FX_/sincos/divide) is CLEAN - it matches,
  unlike the action-VM dispatcher/handler/loader vein which is tie-dense. When stuck in the tie
  zone, pivot to math functions. Anim_GetBlendFactor was a fresh dep of Obj_StepMotionTransform.
- **func_02021060** (camera/actor init, dep of func_02020b64 + Ov023_VmTickActor) - IN PROGRESS
  (build/try/21060.c). SIZE EXACT (316B). Crack: kVecZero (data_02041dc8) copy into +0x18 is a
  VecFx32 STRUCT COPY (ldm/stm), not field-by-field (fixed the 24B overage). Remaining: reg-alloc
  cascade - mwcc HOISTS a `param_1` copy into r3 early (for the struct-copy dest) and swaps the
  ldm/stm src/dst registers (src=r2/dst=r3 vs ROM src=r3/dst=r2); the middle FX_Mul region
  reconverges so it is localized. Not closed after dest/src-pointer variants. Looks like an mwcc
  base-pointer scheduling choice on the struct copy.
- Still open (fire 7, build/try): func_02021208 (Anim_InterpEased, 1-diff commutative tie),
  func_020218a4 (ActionVM_ResolveOperandSlot, 5-diff strh-CSE tie; GameState_GetField signature
  corrected to (int,int) + (u16) casts).
- NEXT: keep mining the anim/transform math vein for fresh clean functions; func_02021060's actor
  chain (func_02020b64) depends on it. func_02020400 (the 64-bit divide) if fresh.

## Frontier (2026-08-01, fire 9) — FOUR matches; camera + render-setup + object-registry veins are clean
- **func_02021060 = Camera_Init** MATCHED+committed (fccb6ec83). Actor camera/view init. Two levers
  (now in codegen-cracks): VecFx32 struct copies via int* base + pointer arithmetic (not byte
  offset, which hoists a 2nd base reg); sin/cos table as flat short[] `[idx*2]`/`[idx*2+1]` (a
  {sin,cos} struct's .cos reads the wrong offset when both are read).
- **func_020232d8 = SubObject_SetupDraws** MATCHED (07581ef7e). Configures 3 sub-object draw entries
  via SubObject_ConfigDraw (func_02023340). First try.
- **func_02023204 = SubObject_SetupDrawsForMode** MATCHED (fc112c81d). Flag-conditional variant.
  Lever: declare the flag result BEFORE the context locals so mwcc keeps it in r4, context in r5.
- **func_02023890 = Obj_UnlinkNode** MATCHED (235cb3c31). Object-registry node removal (global list
  data_0204c058 head +0xc + hash bucket table data_0204c068, key at node+0x10). Levers: positive
  inner condition so mwcc predicates the single store; CACHE the loaded bucket value in a temp so it
  lands in the register the compare reads first (crack 5b is a prior, not absolute - caching was
  right here).
- **KEY VEIN**: 0x02021xxx-0x02023xxx camera/render-setup/object-registry is CLEAN (matches), unlike
  the action-VM dispatcher/loader vein. Found via Camera_CommitMatrices/Obj_StepMotionTransform
  callees and the SubObject_ConfigDraw / registry-global (data_0204c058/c068) families.
- **func_02023778** (registry sorted INSERT, sibling of Obj_UnlinkNode) - IN PROGRESS build/try. 260
  vs 280 (20 short), 59 diffs. Hard: block layout (ROM emits `beq .scan; b .chainwalk`, else-first)
  + register pressure (ROM uses lr/ip for the loop cursors, mwcc r4/r5). Nested forward/backward
  bucket scans. Documented in the file header.
- **func_02020b64** (session/actor constructor, calls Camera_Init) - IN PROGRESS build/try. Hard:
  leftover args to Camera_Init, opportunistic derived constants (0x104 = 0x128-0x24), r3-slot reuse.
- Still open from fires 7-8: func_02021208 (1-diff commutative), func_020218a4 (5-diff strh-CSE).
- NEXT: more clean functions in the camera/render/registry vein (func_02023a4c registry, the
  ARM math func_02004d60 projection, the display-setup func_02023018/100 need the MMIO volatile
  convention). Avoid the action-VM tie zone.

## Fire 9 continued — SIX matches total (added Obj_Destroy + Camera_CommitMatricesEx)
- **func_02023a4c = Obj_Destroy** MATCHED (97298e852). Object teardown+free (destructor callback,
  Obj_UnlinkNode, free aux+self). Levers: cache the destructor pointer (obj[6] loaded once for null
  check AND call); declare the saved-global local BEFORE the arena handle to keep obj in r5.
- **func_02023d70 = Camera_CommitMatricesEx** MATCHED (16ec035c1). Camera_CommitMatrices variant
  with explicit projection args (func_02004eac + MTX_LookAt + GX dirty-bit RMW + VecFx32 caches).
  Reused the Camera_CommitMatrices GX-block-as-struct + VecFx32 struct-copy template. CRACK: when
  verify_idx says "relocs difieren" but the CODE matches, the global->pool mapping is wrong - the
  pool order is FIRST-REFERENCE order; read the `orig=` reloc list (offset->symbol) and assign each
  global to the pool slot that matches, then set the code so each is first-referenced in that order.
- **Obj_UnlinkNode/Obj_Destroy = the object-registry lifecycle** (data_0204c058 list + data_0204c068
  hash). func_02023778 (sorted INSERT sibling) still in build/try (block-layout + reg-pressure).
- Also in build/try: func_02023f08 (64-bit LCG RNG, down to 88 vs 80 - the umull+mla+adc fold and
  the mov#0;lsl;orr return codegen resist); func_02020b64 (session constructor, leftover args).
- **THE VEIN**: 0x02021xxx-0x02023xxx camera / render-setup / object-registry is CLEAN and DEEP -
  6 matches this fire off it. Keep mining: func_02004eac/d60 projection math, the display-setup
  func_02023018/100 (need the REG_DISPCNT volatile define), more registry/lifecycle functions.
