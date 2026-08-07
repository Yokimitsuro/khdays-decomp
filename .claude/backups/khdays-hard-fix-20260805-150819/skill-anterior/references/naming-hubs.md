# ★★★ LOS OFFSETS DE LOS TIPOS DE GHIDRA SE DAN EN **DECIMAL** -- Y UNA CONVERSION MAL HECHA SOBREVIVE A LA REVISION
*(27/07, encontrado re-verificando mi propio trabajo de doce iteraciones antes)*

`create_struct` / `add_struct_field` / `resize_struct` toman los offsets y el tamano en
**DECIMAL**, mientras que **toda** la evidencia (pool, desensamblado, comentarios, el `.c`) esta
en **HEX**. Al crear `Ov011Scene` convertí `0x2cf84` a `183684` cuando son **184196**: un error
de exactamente **512 bytes** que se llevaron tambien los dos campos finales.

**Por que sobrevivio doce iteraciones**: la tabla de `get_struct_layout` salia perfectamente
plausible -- los offsets eran monotonos, crecientes y cabian dentro del tamano declarado. Nada
en la tabla delata el error. Lo unico que lo delata es **la descompilacion**, que rendia los
accesos al stream como `pScene[1].aPane[0].field_0x1c0` -- o sea indexando **mas alla** de la
escena a un segundo elemento fantasma, en vez de `pScene->stream`.

**Regla**: despues de crear o redimensionar un tipo, **no te quedes en la tabla de layout: lee la
DESCOMPILACION de una funcion que use el objeto.** Si ves `x[1].campo` o `field_0xNNN` donde
esperabas un nombre, los numeros estan mal. Y convierte el hex a decimal con la calculadora, no
a ojo.

⚠ El `.c` candidato NO estaba afectado: alli los offsets se escriben como aritmetica hex
(`u8 pad[0x2cf54 - 0x23ac8];`), que es correcta por construccion. El fallo era exclusivo del
tipo de Ghidra. Otra razon para escribir los rellenos como resta de constantes hex y no como
un numero calculado a mano.

# Naming the debt — method, and the evidence behind each hub name

Opened 2026-07-19 in a session dedicated to the naming debt (`tools/audit_unnamed.py`).
Debt at the start: **5746** byte-exact C functions with no real Ghidra name, plus **1287**
with no Ghidra function at all.

## ⇒ The method: rank the debt by CALL-GRAPH IN-DEGREE, not by unit

The instinct is to pick the worst unit (main 588, ov008 393, ov025 300) and grind it.
That is the wrong order. Naming is worth exactly as much as the number of call sites it
makes readable, and the distribution is brutally skewed:

    python -c "... count relocs across build/func_index.json ..."   # see tools/namec.py

**The 5746 unnamed functions held 24,639 call sites between them, and they are brutally
skewed:** `func_02030788` alone had **1338**. (Earlier drafts of this file said the *top 45* held
all 24,639 -- that was a misreading of the script's total line. The real shape is better evidence
for the method: this session renamed **172** functions, 3% of the debt, and the call sites held by
unnamed functions fell **24,639 -> 15,510**, i.e. **37% of the opacity removed by 3% of the work**.
What is left is a long tail: only 10 functions remain above 100 xrefs, 37 above 50.)

Work the top of that ranking first: one hour there beats a day on a unit's tail, and it also
unblocks the *rest* of the debt (see the bootstrap problem below).

## ⇒ The bootstrap problem — why the debt cannot be cleared bottom-up

`tools/namec.py --profile` classifies every unnamed function by what its own C can prove:

| class | count | meaning |
|---|---|---|
| `SOME_UNNAMED` | 4134 | calls at least one function that is itself unnamed |
| `NOCALL` | 819 | a leaf — self-evident from its own body |
| `ALL_CALLEES_NAMED` | 290 | grounded: every callee has a real name |
| `FWD_UNNAMED` | 198 | a forwarder to an unnamed target |
| `EMPTY` | 166 | `{}` — needs caller context (vtable no-op slots) |
| `CRITSEC` | 26 | OS_DisableInterrupts / OS_RestoreInterrupts pair |

**73% of the debt is `SOME_UNNAMED`.** A function whose callees are all `func_0203xxxx` tells
you nothing, so the debt is self-referential and clears from the NAMED FRONTIER outward:
name a hub → its callers become `ALL_CALLEES_NAMED` → name those → repeat. That is the same
shape as `dedupprop`/`namefam_propagate`, but over the call graph instead of the byte-hash.
Re-run `--profile` after each wave; the classes should shift.

`NOCALL` (819) is the one vein that does NOT depend on the graph — pure leaves, nameable from
their own body today. Best single batch target after the hubs. Densest units: ov002 120,
ov008 117, ov025 82.

## ✗ `EMPTY` (166) is NOT the cheap batch it looks like — `nullsub` is already a PLACEHOLDER root

All 166 are provably empty (165 × `1eff2fe1` = ARM `bx lr`, 1 × `7047` = THUMB `bx lr`), so
`NullSub_<addr>` would be *true*. It is still wrong, and the audit says so itself:

    PLACEHOLDER_ROOTS = 'helper|sub|fn|func|f|thunk|nullsub|set|get|fwd|statestep|st'

**`nullsub` is in that list**, so `NullSub_02005414` matches `PLACEHOLDER` and is counted as debt
by design. The project already decided this: naming an empty function after its *emptiness* says
nothing about its ROLE. What an empty function needs is which vtable/callback slot it fills
(`Ov025_NoopDrawHandler`), and that is per-function caller work, not a batch.

**Read `PLACEHOLDER_ROOTS` before inventing any bulk naming scheme** — `set`/`get`/`st`/`fwd` are
in there too, so `SetFlag_1234`-shaped output is self-defeating. (The regex only fires on a
4–8 hex-digit suffix containing a digit, so `SetMasterBrightnessMain` is safe; the rule is about
placeholder *roots* with address suffixes.)

## ★★ An auto-namer built on callee names LAUNDERS the junk SDK names

`namec.py` originally emitted `<callee>_Wrapper` for a plain forwarder. Inspecting the 13
candidates before applying them killed the whole class:

- **`OS_IsTickAvailable_Wrapper`, `INITi_CpuClear32_0x01ff86fc_00`, `WM_EndKeySharing_0x0208a5ec_Wrapper`.**
  These roots are the **shape-matched garbage** the skill already documents (87 veneers all called
  `SNDi_UnlockMutex_0xADDR`; `OS_IsTickAvailable_0x01ff8138` is really a per-player input mask).
  Deriving a new name from one **manufactures a fresh lie *and strips the `_0x` tell that made it
  recognisable as junk*.** Junk in, junk laundered.
- **`GFXi_EnqueueCommand_Wrapper` × 3** — three different functions, one name, same address space.
- **`int_Wrapper`** — from a call through a function pointer.

Fixed: `is_named()` now also rejects `_0x[0-9a-f]{6,8}$`, and the generic `_Wrapper` rule is gone —
a forwarder earns an automatic name only when a leading **constant** selects a variant *and* the
callee has a real name (`PushCommand_0A`, `PushCommand_16`).

★ **The filter immediately corrected a measurement**: `ALL_CALLEES_NAMED` fell **279 → 243**, i.e.
36 functions looked grounded and were grounded only by junk. **Any "is this identified yet?" count
that trusts `_0xADDR` names is overcounting.**

## ⇒ Frontier expansion is SLOWER than it looks — don't expect the classes to move

Naming 25 hubs moved `SOME_UNNAMED` by **6** (4134 → 4128). Reclassification needs *every* callee
named, so one hub in a function's 5-callee list changes nothing measurable. The leverage of hub
naming is **readability at the call sites** (9,100 of them resolved this session), not the class
counters. Judge this work by `audit_unnamed`'s total and by the call-site figure, not by the
profile shifting.

## ⇒ Discipline: shallow-but-true beats FUN_; speculative is WORSE than FUN_

A name that lies survives, propagates through `namefam_propagate`, and misleads the port. The
project has already paid for this once (~23 `Ov006_Title*` symbols that were really Mission
Mode). So: only write what the body proves. `PushCommandCmd0A` is a fine name. Guessing that a
u16 field is "health" is not.

Corollary — **`createFunction` guards**: never overwrite a name that does not start with
`FUN_`/`func_` unless you are deliberately replacing an address-embedding placeholder (e.g.
`IsGlobal_0204c228_NonZero` → `Session_Exists`), and say so in the script.

## ★★★ THE THUMB TRAP, NOW IN THE *DEFINE* PATH (2026-07-19)

The skill already warns that `verify_idx.py` and any compiling tool must try both modes. It bites
`createFunction` too, and this one is nastier because it produces a **plausible-looking result**:

> `createFunction()` / `disassemble()` assume **ARM**. On a THUMB function they create a
> **1-byte phantom function** — correctly *named*, so `audit_unnamed.py` counts it as paid off,
> pointing at nothing.

Hit on `func_02030550` (`Session_Destroy`, THUMB, 0x20 B): `createFunction` gave
`body=[[02030550, 02030550]]` and `disassemble_function` returned **empty string**, while
`read_memory` plainly showed `10 b5` = `push {r4,lr}`. The fix is to set the **TMode** context
register to 1 over the body before disassembling — `~/ghidra_scripts/DefineThumb.py` does this
and produced the correct `body=[[02030550, 0203056b]]`.

⚠ **This matters most for the 1287 functions with no Ghidra function at all.** A bulk
define-then-name over that bucket that ignores mode will silently fake every THUMB member —
and the audit will report the debt as paid. Mode comes from `config/arm9/symbols.txt`
(`kind:function(thumb,size=…)`) or `build/func_index.json` (`mode`). Same lesson as the
`build_sweep.py` false negative: **scope the rule by the failure mode (assuming a mode), not by
the API that exposed it.**

---

## ★★★ STRUCTS: the project had ZERO, and that is a bigger debt than the names

Asked 2026-07-20 ("¿estás haciendo structs?"). The answer was no, and checking turned up worse:
**Ghidra contained no user data types at all** — no structs, no categories, nothing.

What exists instead is ~4,000 **per-file ad-hoc declarations** in the C tree:

| declaration | files |
|---|---|
| `struct hw60` | 645 |
| `struct Obj` | 460 |
| `struct bf` | 407 |
| `struct A` | 390 |
| `struct S` | 285 |

`struct hw60` is byte-identical copy-paste across 645 files. The generic ones are worse: `Obj`,
`A`, `S`, `C` describe **the same underlying object with a different shape and name in every
file**, whatever that one function's codegen needed.

Why it happened, and why it is not a bug in the matching work: byte-exactness forces each `.c` to
be self-contained, delinking rules out shared headers, and the struct is used as a **codegen tool**
(force a `ldrh`+shift pair, pick a base register) rather than as a data model. For the 306 gate
this is irrelevant. **For the PC port it is central** — 460 conflicting local shapes of one entity
is worse than none, because each one looks authoritative.

**The fix is Ghidra data types, not C headers.** Ghidra types cost nothing at build time (they
never touch the `.c`), and they pay off immediately in every decompilation that touches the object.
Created so far, all from layouts proven this session:

| struct | size | key fields |
|---|---|---|
| `SrtTransform` | 0x2c | quat(w first) @0, translation @0x10, scale @0x1c, flags @0x28 (bit0 identity, bit1 uniform) |
| `SlotEntry` | 0x8c | velocity @0xc, pos pair @0x10, 2-bit mode @0x74, flags @0x7c (bit0 linked, bit2 visible) |
| `GameSession` | 0x30 | state @0, connectedMask @4, 64-bit LCG @8/0x10/0x18, localPlayerIndex @0x22 |
| `CardTransferCtx` | 8 | blockCounter @0, slot @1, resultCode @4 |

Measured payoff — `Session_GetLocalPlayerIndex` before and after:

```c
return *(undefined2 *)(iVar2 + 0x22);   ->   return iVar2->wLocalPlayerIndex;
```

### Three traps when doing this in bulk

1. **Every type tool leaks a transaction.** `create_struct`, `apply_data_type`,
   `set_function_prototype`, `set_local_variable_type` all return the
   `endTransaction` error **while succeeding**. After a batch, `save_program` fails with
   "Unable to lock due to active transaction". One session left **13** open;
   `CloseTxAndSave.py` reported `closed=13; tx_after=NONE; SAVED_OK`. **Always read the result
   back, and always close-and-save at the end or the whole batch is lost.**
2. **`apply_data_type` fails on BSS-style globals** — `0204c228` and `arm9_ov008::02090fb4` both
   answer `Unable to read bytes` / `Address is not in program memory`. Typing the **local
   variable** in the consumer is the workaround, **but only for one of the two shapes**, and the
   difference is worth knowing before you waste calls:
   - ✅ `local = *DAT_xxx;` — the global holds a **pointer** to the object. Retyping the local to
     `Obj *` works; this is what turned `*(undefined2 *)(iVar2 + 0x22)` into
     `iVar2->wLocalPlayerIndex`.
   - ✗ `local = DAT_xxx;` — the global **is** the object, and its address has no backing bytes.
     `set_local_variable_type` answers *"Unable to use type for symbol"*, because the local is
     bound to an untyped `DAT_` constant rather than to a real datum. Hit on
     `Ov008_CardTransferStep` with `CardTransferCtx`.
   **The real fix for the second shape is to give those regions an uninitialized memory block in
   Ghidra**, after which the address becomes typeable like any other. That is a change to the
   program's memory map, so agree it with the user before doing it project-wide — but it is the
   thing standing between `CardTransferCtx`/`SlotEntry` and actually being usable.
3. **The decompiler reaches the global through the literal pool** (`DAT_020307b4` holds
   `0x0204c228`), so typing the pool slot is not the same as typing the object. Same pool-vs-data
   distinction the skill already warns about for reading constants.

# Evidence log — challenge these, don't trust them

## SRT transform API (main) — the object is 0x2c bytes

Layout, proven three independent ways:

| offset | field | proof |
|---|---|---|
| `+0x00..0x0c` | **quaternion, w first** | `0202f188` writes `dst[0]=cos`, `dst[1..3]=sin*axis` from a sin/cos table = axis-angle→quat |
| `+0x10..0x18` | **translation** | ov131 does `VEC_Add(&obj->mat + 16, tmp, tmp); 0203ca30(&obj->mat, tmp)` — reads the field the setter writes |
| `+0x1c..0x24` | **scale** | call sites pass `0x1000` (= 1.0 in Q12) and `0x14cd` (≈1.3); one passes `(x, y, x)` = squash/stretch |
| `+0x28` | **flags** | bit0 / bit1, below |

**Flag bits — read them off `Srt_Concat` (0203cac0), which is where they are consumed:**
- **bit 0 = this transform is IDENTITY.** `Srt_Concat` returns the *other* operand unchanged when
  either side has bit 0 set. That is why *every* setter does `&= ~1`: writing a real value means
  it is no longer identity. (It is NOT a dirty/stale-matrix bit — that was the first reading and
  it was wrong.)
- **bit 1 = the scale is UNIFORM.** `Srt_SetScaleUniform` sets it (`&0xfe | 2`); the per-axis
  setters clear it (`&0xfc`). `Srt_Concat` reads only `+0x1c` on the uniform path.

| addr | name | xrefs | proof |
|---|---|---|---|
| `0203ca30` | `Srt_SetTranslation` | 502 | writes +0x10..0x18 from a Vec3*, clears identity |
| `0203c9d0` | `Srt_SetRotationQuat` | 403 | copies 4 words to +0x00, clears identity |
| `0203c9b4` | `Srt_SetRotationAxisAngle` | | calls `QuatFromAxisAngle` then clears identity |
| `0203ca50` | `Srt_SetScaleXYZ` | | +0x1c..0x24 from 3 scalars, clears identity+uniform |
| `0203ca74` | `Srt_SetScaleVec` | | same from a Vec3* |
| `0203ca9c` | `Srt_SetScaleUniform` | | all three = one value, SETS the uniform bit |
| `0203cac0` | `Srt_Concat` | | parent×local, identity fast paths, quat multiply `01ff919c` |
| `0202f188` | `QuatFromAxisAngle` | | sin/cos table; `dst[0]`=cos, `dst[1..3]`=sin*axis |
| `0203c904` | `Node_ComposeWorldSrt` | | `Srt_Concat(self+0x30, parent+0x30, self+4)` — world matrix cached at +0x30, node's local SRT at +4, parent ptr at +0 |
| `0203c83c` | `Obj_ReplaceRef` | | decrements old refcount, stores, increments new |

## Game session singleton at `0x0204c228`

One object holding a **synced RNG** and **4-player state** — which is exactly what a
single/multiplayer session needs (Mission Mode syncs the RNG across players).

| offset | field | proof |
|---|---|---|
| `+0x00` | state enum | guards test `!= 1` and `!= 3` |
| `+0x04` | connected-player bitmask | `0203070c` walks 4 bits of it |
| `+0x08..0x1c` | 64-bit LCG: seed, multiplier, increment | `0203084c` |
| `+0x22` | **local player index (0..3)** | see below |

`+0x22` = local player index, three independent ways: the script VM (`02020d10`) adds an offset
and wraps at 4 (`if (r >= 4) r -= 4`); ov006 (Mission Mode select) uses it as the cursor row;
ov002 compares it to a slot owner id, and that file's own pre-existing comment already read it as
"the local player's". Returns **0** when there is no session — in single player you are player 0.

| addr | name | xrefs |
|---|---|---|
| `02030788` | `Session_GetLocalPlayerIndex` | **1338** |
| `02030640` | `Session_Exists` (replaced `IsGlobal_0204c228_NonZero`) | |
| `0203070c` | `Session_PackConnectedPlayerMask` | compacts absolute slots → dense connected index |
| `0203084c` | `Session_RandNext` | 64-bit LCG, returns `hi >> 0x14` |
| `02030550` | `Session_Destroy` | frees two heap fields, nulls the singleton (THUMB — see above) |

Still unnamed on purpose: `02030670` (`state != 1`) and `02030694` (`state != 3`) — the state
enum is not decoded yet, and a guess would be a lie.

## Script VM operand fetch (main, ~0x02021xxx)

`020218a4` resolves an operand from the bytecode stream (tag at `[0]`: 8 = indirect through the
frame, 4 = call a handler, `&0x80` = addressed forms). Its two consumers unpack by tag:

| addr | name | xrefs | proof |
|---|---|---|---|
| `02021980` | `ScriptVm_ReadOperandInt` | 619 | returns the raw word when tag == 1 |
| `02021994` | `ScriptVm_ReadOperandFx32` | 229 | tag 1 → `<<12` (int→fx32); tag 0x10 → already fx32 |
| `020218a4` | `ScriptVm_ResolveOperand` | | the fetch itself |

## Doubly-linked circular list with an embedded cursor

`node[0]`=prev, `node[1]`=next, `node[3]`=payload; `list[9]`=cursor. Convention was already set
by the pre-existing `List_InsertSorted_fca8` (address-sorted insert, key at +8).

| addr | name | xrefs |
|---|---|---|
| `01fffd70` | `List_First` | 245 |
| `01fffd8c` | `List_Next` | 243 |
| `01fffdac` | `List_Last` | |
| `01fffdc4` | `List_Prev` | |

## Leaves

| addr | name | proof |
|---|---|---|
| `01ff8640` | `DmaSetChannel` | writes src/dst/ctrl at `0x40000b0` = REG_DMAxSAD/DAD/CNT |
| `01ffd0e8` | `Vec3ScaleAdd` | `c = b + (s*a >> 27)` componentwise |
| `ov002 02053ec0` | `Ov002_IsPointInBox` | `b->x <= px <= b->x+b->w` and same for y |

## Second wave (same session)

| addr | name | proof |
|---|---|---|
| `02016f10` | `ResDict_FindIndexByName` | 16-byte fixed-name compare; linear scan under 0x10 entries, patricia trie above; returns index or `0xffffffff`. NNS resource-dictionary shape |
| `0203bdfc` | `FindResourceIndexByName` | zero-fills a 16-byte buffer, `strlen`+`MI_CpuCopy8` the C string in, then the lookup above; normalises failure to -1 |
| `01ff8a14` | `DivSyncResult64` | `FX_DivAsync`, poll `DIVCNT`(0x04000280) bit 15, read `DIV_RESULT`(0x040002a0). Sibling of the pre-existing `WaitDivResult64_8ab0`, which only waits |
| `0201e374` / `0201e3cc` | `SetMasterBrightnessMain` / `...Sub` | `MASTER_BRIGHT` 0x0400006C (main) / 0x0400106C (sub); writes during vblank, else defers via a bit in `data_027e0080` |
| `0202ffbc` | `FreeAllListNodeSubBuffers` | walks its NNS list, frees each node's `sub` and nulls it |
| `020300f8` | `EnqueueObjGfxCommand` | forwards 4 object fields to the already-named `GFXi_EnqueueCommand` |
| `0202a440` | `FreeAllResourceTables` | nested free loops over 5 counted handle arrays, then the block, then the sub-object at `p[3]` |
| `02032450` | `Slot_UnlinkIfLinked` | slot array at `base+0x7c` stride `0x8c`; tests bit0, calls the named `ListNodeUnlink_02031df0`, clears bit0 |
| `ov107 020c9074` | `Ov107_EnqueueValue` | `*List_InsertSorted(node+0x260, 4, key=0x64) = val` |
| `ov107 020c5c54` | `Ov107_MoveNodeAndRelayout` | `Srt_SetTranslation(node+0xa0, vec)` then re-layout. ⚠ really takes TWO params; the matched C declares one and passes r1 through — the arity case state.md already flags |
| `ov008 02055c84` etc | `GetVarRecordByIndex` | count at `s[1]`, data at `s[2]`, each record prefixed by its own u32 size; returns body (`p+4`). Same routine in ov002/ov006/ov007/ov008/ov025 |
| `ov008 02054788`, `ov025 0208843c` | `FindEntryById` | walks the NNS list at `+0x4a38` for the node whose `field[3]` == id |
| `ov002 02053efc` | `Ov002_FindActiveEntryById` | scans for an ACTIVE entry (`fieldC != 0`) with a matching id |

## Third wave — the slot table, and a RETRACTED "honest unknown"

★ **`func_01fff774` (564 xrefs) was parked here as unnameable last iteration. The objection was
wrong, and the thing that killed it was reading ONE more function.** The park said: callers pass a
small index (`n-1`) where the wrap limit is `count<<12`, so the wrap could never fire. But `n`
comes from `func_0202aef8`, which returns `p[2][2] << 12` — **already Q12**. Both sides were Q12
the whole time. The lesson is the project's own negative-result rule pointed the other way for
once: *before parking something as contradictory, check the units of the value the caller passes
in*, which means opening the producer, not just the consumer.

| addr | name | xrefs | proof |
|---|---|---|---|
| `01fff774` | `Anim_SetFrameWrapped` | **564** | sets the Q12 cursor `p[0]`, wraps at the resource's length |
| `01fff75c` | `Anim_GetChannelState` | | resolves obj+channel → per-channel state |
| `0202aee0` | `Anim_GetFrame` | 94 | returns `p[0]`, the cursor the above writes |
| `0202aef8` | `Anim_GetLengthQ12` | 60 | `p[2][2] << 12` |
| `02016294` | `G3_ReadClipAndVectorMtx` | 62 | push/identity, `G3X_GetClipMtx` + `G3X_GetVectorMtx`, pop |
| `0203ca14` | `Srt_SetTranslationXYZ` | 61 | `r0[4..6]` = +0x10..0x18, clears the identity bit — the 3-scalar sibling of `Srt_SetTranslation` |

Supporting context: callers hold the animation resource at `obj+0x88`, and its `+0x24`/`+0x40` is
the name dictionary that `FindResourceIndexByName` searches — so animations are looked up by name
and played per channel.

### The slot table (`base + index*0x8c`) — and how bit 2 got decoded

`+0x0c` velocity magnitude · `+0x10` position pair (fixed point) · `+0x74` a 2-bit field ·
`+0x7c` flags: **bit0 = linked into the list**, **bit2 = visible**.

Bit 2 was an honest unknown blocking 669 call sites. It fell to **`arm9_ov011::0205c3a0`**, which
scrolls elements downward: it sets bit 2 to `1` when the element is spawned, then every frame does
`Slot_SetVisible(base, i, (-0x40000 < y))` after decrementing `y` — a bounds test. Combined with
ov008/ov025/ov026 toggling it for a UI entry's two slots, "visible" is the reading.
**Method note: the setter had no informative callers in the C tree; the getter (`02032748`) had
exactly one, in an overlay, and that one caller decoded the bit.** When a flag's meaning is
missing, `get_function_callers` on the *reader* beats staring at the writer.

| addr | name | xrefs |
|---|---|---|
| `02032710` | `Slot_SetVisible` | 161 |
| `02032748` | `Slot_IsVisible` | |
| `0203257c` / `020325a0` | `Slot_SetPosition` / `Slot_GetPositionPtr` | |
| `02032450` | `Slot_UnlinkIfLinked` | |
| `ov008 02054ba4`, `ov025 0208884c`, `ov026 020843e8` | `SetEntrySlotsVisible` | 328+268+73 |
| `ov008 02050c54`, `ov025 02084a7c` | `Ov008_GetContext` / `Ov025_GetContext` | 70+69 |

⚠ **`func_02032710` writes BIT 2, not bit 0** — the matched C spells it `p[index].flag = (value != 0)`
through a struct, which hides the bit. Ghidra's `& 0xfffffffb | (x<<31)>>29` is the truth. **A
struct-typed field in our own C is an abstraction, not evidence about which bit the ROM touches.**

## Fourth wave — sound, and a NAME THAT LIED

★★ **`func_02033b78` (475 xrefs) is `PlaySound`, and the file's own comment said "fire UI event".**
The 0x0201bxxx/0x0201cxxx region is the sound driver — its neighbours are documented `SND_*` users
(`func_0201c254` = `SndSwapSlotReleaseChannel`, via `SND_SetActiveSlotSwap`), and
`data_0204c234+0xb44c8` is the player. `0201c608(player, bank, id)` walks
`GetSectionEntryPtr(bank)` → `GetArrayEntry(id)` → an entry with `byte@+9 / u16@+4 / byte@+8` and
starts it. ov008 clinches it: an empty roster slot fires `(0,4)`, a confirmed pick fires `(0,1)` —
the menu's error and confirm sounds. **A prose comment left by an earlier pass is a hypothesis,
not evidence** — the same standing as a `nonmatching/` write-up.

| addr | name | xrefs |
|---|---|---|
| `02033b78` | `PlaySound` | **475** |
| `02033b24` | `PlaySoundChecked` | |
| `0201c608` | `Snd_StartEntry` | |

### The packed game-state bit store — and `DispatchToHandler2_020235d0` was a LIE

`data_0204be18+0x10` holds single flags **and** multi-bit fields, addressed **MSB-first** within
each 32-bit word:

| addr | name | what it really does |
|---|---|---|
| `02025640` | `BitArray_SetBit` | `word |= 1 << (31 - (bit & 31))` |
| `02025694` | `BitArray_TestBit` | the matching test |
| `020256b8` | `BitArray_GetField` | extracts a **width-bit field**, straddling words |
| `02023588` | `GameState_IsFlagSet` | 184 xrefs |
| `020235a8` | `GameState_SetFlag` | was `ForwardGlobalPlus10To_02025640` |
| `020235d0` | `GameState_GetField` | **was `DispatchToHandler2_020235d0`** |

★★★ **It dispatches nothing.** ov008's `func_020235d0(0, 9)` is "read 9 bits from offset 0", which
an earlier comment misread as "roster cursor slot 9" — so one wrong name bred a wrong comment.
Both are replaced. **A name with a semantic root and an address suffix passes `audit_unnamed`, so
a LIE of this shape is invisible to the debt counter forever.** The counter measures whether a
name exists, never whether it is true. When you touch a heavily-used function that already has a
name, read its body anyway.

Two replacement categories are legitimate (say so in the script both times):
1. the name **lies** (`DispatchToHandler2_*`);
2. the name is **mechanical** — it describes forwarding or an address rather than meaning
   (`ForwardGlobalPlus10To_02025640`, `IsGlobal_0204c228_NonZero`).

## ⇒⇒ THE BEST REMAINING NAMING LEAD: decode the shared ov008/ov025 CONTEXT STRUCT

After 182 renames the in-degree ranking is drained (10 functions left above 100 xrefs, and those
are the honest unknowns below). The 20–100 xref band is **much harder per function** — it is almost
entirely field accessors on context structs nobody has decoded, so each one costs a subsystem
investigation and yields one name.

The way to break that open is to attack the **struct, not the functions**. `ov008` (393 debt) and
`ov025` (300) share a context struct — the same offsets appear in both:

    Ov008_GetContext / Ov025_GetContext   = the pointer at +4 of the module global
    +0x4a80, +0x13fc, +0x959c, +0x95a0, +0x96b0 ...

`+0x959c` yields the object the menu logic passes everywhere (`func_ov008_02058df0(obj, 2)` to
commit a pick; fields at `+0x8c`/`+0x90`).

### ✗ TESTED AND IT DOES NOT BOOTSTRAP — `tools/fieldid.py`, measured

The plan was: a field's TYPE is revealed by its consumers, so if an accessor's result is handed to
`Srt_SetTranslation` / `Anim_SetFrameWrapped` / `List_First`, the field is identified for free.
`fieldid.py` finds the trivial `ctx + N` accessors and follows their results (both the direct form
and, crucially, the `int obj = accessor();` via-a-local form).

**Result across ov008 + ov002 + ov025 + ov107 = 541 accessors: exactly ONE reaches a named
function** (`ov025 +0x959c` → `MI_CpuFill8`, which only says "it gets cleared").

The machinery is fine — self-tested, it finds **288 consumer edges** for ov008 alone. **Every one
of those consumers is itself unnamed.** These overlays are closed islands: the named frontier has
not reached them, so there is nothing to borrow. Naming their context means understanding ov008's
own menu logic first — the same cost as decompiling it. **Do not re-run this expecting a different
answer; re-run it only after a big batch of ov008/ov025 internals gets named.**

Two process notes from building it, both instances of standing rules:
- **Strip comments before any regex over source.** The first run reported four consumers named
  `sprite`, `page`, `rebuild`, `scrolls` — English words inside `/* */` followed by a paren. Four
  plausible hits, zero real.
- **Then it reported 0, and that zero was also an artifact** — it only matched the direct nested
  form `callee(accessor(), …)`, while real code parks the result in a local first. *State the
  positive form and confirm the search can match it* applies to your own tooling, twice in a row.

Second-best lead: `NOCALL` (772 graph-independent leaves; ov002 120, ov008 117, ov025 82) — but
most are accessors on these same undecoded structs, so it is the same job wearing a different hat.
**Realistic read: the remaining ~5.5k debt is not separable from decompiling those overlays. Name
each match in its own batch during decomp (the standing rule) rather than planning another
naming-only push.**

## Deliberately NOT named (honest unknowns — do not "fix" these with a guess)

- `0202af1c` (187 xrefs) — body is `*p |= 2`. Nothing in it identifies the flag.
- `0203c7ac` (462) — invokes callbacks at `+0x68` and `+0x78`; a notify pair, but what is being
  notified is not proven. Callers pass `self+0x384`.
- `func_01fffc24` — self-linking init (`p->e = p`), but its field set does not match the list
  layout above, so it is a different container.
- `func_01fff99c` — `return param == 1 || param == 4`. Opaque without the enum.
- `func_0203c640` (109) / `func_0203c650` (360) — the pair that sets node `+0x24 = 1`, one by
  pointer and one by searching the list for `+0x1c == id`. Nothing found so far *reads* `+0x24`,
  so its meaning is unproven. 469 call sites ride on this pair; whoever decodes `+0x24` should
  name both together.
- `func_02032710` (161) — sets bit 2 of the slot flags. Which bit is certain; what bit 2 *means*
  is not. Blocks `ov008_02054ba4` / `ov025_0208884c` (328 + 268 xrefs) too, since those are just
  "apply it to an entry's two sub-slots and mirror the boolean into bit 1".

## A `skipped` line from the naming script is a WARNING, not noise (2026-07-20)

`NameHubs*.py` refuses to rename a function that already carries a real name, and prints it
as `SKIP=[...]`. Treat that list as evidence you are **about to introduce a rival
vocabulary**, and read it before moving on.

What happened: a batch of 16 came back `named=14 skipped=2`, the two skips being
`ov002_FindActiveEntryByTag` and `SetTagTrackerNodeArmed`. Those two are the *targets* of
three forwarders I had just named `Ov002_FindNodeByTag`, `Ov002_SetNodeArmed` and
`Ov002_NotifyAnimManager`. So the same subsystem now had two names -- "AnimMgr/Node" from
me, "TagTracker" from the project. One command settles it:

```
grep -rhoE "[A-Za-z0-9_]*TagTracker[A-Za-z0-9_]*" src/ --include=*.c | sort | uniq -c | sort -rn
```

`BuildTagTrackerNode` (8 files) and `TickTagTrackerNodes` (2) -- **TagTracker was already the
established word**, and the skips were the only reason I looked. Retired my three via a new
`~/ghidra_scripts/ForceRename.py` (renames unconditionally; use it ONLY to retire a name you
introduced this session, never to overwrite existing work).

Two rules fall out:
1. **Grep the tree for the subsystem's vocabulary BEFORE naming a forwarder** -- the callee
   usually already has the word you want. Same discipline as `grep "} Name;"` before creating
   a struct.
2. **When a forwarder binds a context to a generic routine, name it `<Unit>_Ctx_<CalleeName>`**
   rather than inventing a synonym. `Ov002_Ctx_SetTagTrackerNodeArmed` says exactly what it
   adds over `SetTagTrackerNodeArmed`, and it cannot collide with the callee inside one unit --
   which is the case the collision check exists to refuse.

## Naming a function can ROT a name elsewhere -- check its forwarders (2026-07-20)

`func_ov006_0205606c` was called `Ov006_Fwd_020521a0`: a placeholder that embeds the ADDRESS
of the function it forwards to. The moment 020521a0 became `Ov006_MissionDrawTextRun`, that
name stopped carrying any information a reader could use -- it points at a raw address whose
real name now exists two lines away. Renamed to `Ov006_MissionDrawTextRunFwd`.

**So after naming a hub, look at what forwards to it.** The audit already counts
address-embedding names as debt (the placeholder tally dropped 230 -> 229 on this one rename),
but it will not tell you *which* ones just became fixable -- and they are the cheapest names
in the project, because the target's name is the answer.

Checked for a wider sweep: `search_functions("_Fwd_")` returns nothing else, so this spelling
was a one-off. Other address-embedding spellings (`stDispatchByStateByte_ccbcc`,
`SetMode95d0`, ...) are covered by the existing `ADDR_IN_NAME` predicate in
`namefam_propagate` -- and note that predicate deliberately does NOT require a digit, because
`_ccbcc` and `_cadc` are addresses spelled entirely in letters.

## A class of naming debt the AUDIT CANNOT SEE (2026-07-20)

Renaming eight functions from `ovNNN_setupDual_<addr>` to `ReleaseAndFreeField2644` moved
`audit_unnamed.py` by **zero**. That is not a bug in the counter -- it is the deliberate rule
that a semantic root with an address suffix is a disambiguated real name (`WaitDivResult64_8ab0`
and ~1035 like it). `setupDual` looks like a semantic root, so the audit counts it as named.

But those eight names were wrong twice over:
- they embedded each function's **own address**, so eight byte-identical copies of one routine
  carried eight different names; and
- **`setupDual` is not what the function does.** It releases the sub-object at +0x2644 and frees
  it. It is a teardown that had been called a setup.

So the debt figure is a floor, not the whole picture: **a plausible-looking root with an address
suffix is invisible to the audit and can still be a lie.** These do not surface by counting.
Where they DO surface is `namefam_propagate`'s "families whose named members DISAGREE" list --
seven spellings of one name is the tell that a family was named member-by-member instead of
once. Read that list; it is currently the only detector for this class.

Remaining disagreeing families worth the same treatment (each needs a human, which is why the
tool refuses them): `SetPose1ThenAdvanceSlot | SetPoseThenAdvanceSlot`,
`AdvancePositionUnlessHitFlag | ConfigSubStateThenAdvanceSlot`,
`GridConfirmOnPenUp | GridConfirmOnPenUp2`, `stDiv10Store_cd154 | stDiv10Store_d0d94`,
`CreateRegistryEntryAndLink | CreateRegistryEntryForActor`.

## The DISAGREE list has TWO classes -- do not unify blindly (2026-07-20)

`namefam_propagate`'s "families whose named members DISAGREE" is the only detector for
member-by-member naming, but roughly half its entries are NOT errors:

**Class 1 -- one routine, named inconsistently. FIX.** The tell is a placeholder root plus
each copy's own address, or two names for identical bodies. Fixed this session:
`setupDual_<addr>` x8 -> `ReleaseAndFreeField2644` (and it was a teardown called a setup),
`stDiv10Store_<addr>` x2 -> `SeedTimerFireThenAdvanceSlot`, x3 -> `SeedTimerFireAttack2ThenAdvanceSlot`,
`ConfigSubStateThenAdvanceSlot | AdvancePositionUnlessHitFlag` x4 -> `DecayCopyPosFireOnHitFlag`
(the second name had the gate INVERTED -- it fires IF the flag, not unless), and
`CreateRegistryEntryAndLink | CreateRegistryEntryForActor` x7 unified on the first.

**Class 2 -- one SHAPE, semantically different instances. LEAVE ALONE.** Forwarder templates
are byte-identical modulo relocs while forwarding somewhere different, so disagreement is
CORRECT. Example flagged by the tool: `Ov002_Ctx_FindActiveEntryByTag |
Ov002_Ctx_InvokeTagTrackerCallback | Ov002_ForwardToSubDc` -- three names I wrote myself the
same day, all right. Same for two copies of a routine inside ONE overlay, where a numeric
suffix is the correct disambiguation (`GridConfirmOnPenUp` / `GridConfirmOnPenUp2` in ov008 --
identical bodies, identical comments, genuinely duplicated in the ROM).

**The discriminator is the CALLEE, not the shape: if the members call different functions, the
names should differ.** Read one body before unifying anything off this list.

## ★★★ symbols.txt contains DEGENERATE names, and one class of them is provably wrong

*(2026-07-20.)* `config/arm9/symbols.txt` has **64 function names ending in `_0xNNNNNNNN` across 22
roots**. They are not variants of one routine -- they are what happens when N distinct functions
are **byte-identical once the relocs are masked**, which is exactly the comparison the byte-matcher
uses: all N match one name, and the rest get their address appended.

Worst offenders: `WM_EndKeySharing` x14, `SNDi_UnlockMutex` x12, `GXS_LoadBG3Scr` x7,
`GXS_LoadBG3Char` x7, `OS_IsThreadAvailable` x4.

**The GX set was demonstrably mis-assigned and is now FIXED.** The sixteen are
`GX_LoadBG{0..3}{Scr,Char}` + `GXS_LoadBG{0..3}{Scr,Char}`, and each names itself by the single
call that distinguishes it (`G2_/G2S_GetBG<n>{Scr,Char}Ptr`). `GXS_LoadBG3Scr` was sitting on
`GX_LoadBG0Scr`'s address. Ghidra already had them right -- symbols.txt was the wrong one.

**Rule that falls out: when a symbols.txt name has an address suffix, treat the ROOT name as
unverified for EVERY member of the set, including the unsuffixed one.** The unsuffixed member is
not the original; it is just the first one the matcher hit.
Only fix a set when the true name is **derivable from the function itself** (a distinguishing
callee, a constant, a register). The WM/SNDi sets are tiny veneers with nothing to derive from --
Ghidra's `Veneer_<addr>` is the honest name there, and they were deliberately left alone.

⚠ Related: `WM_EndKeySharing_0x02023ad0` is used in matched `.c` files as an OBJECT DESTRUCTOR
(paired with `func_02023930` as constructor). That is the degenerate-name problem reaching the
C tree. Do not read meaning into a `*_0xADDR` name.

## ★★★ A GREEN 306 GATE DOES NOT PROVE A `.c` IS BEING USED

Found the hard way during that fix, and it generalises well beyond it.

The source files in `src/calls/` are named **after the symbol**, and `gen_delinks.py` binds a file
to an address **by filename**. Rewriting only the file CONTENTS left
`src/calls/GXS_LoadBG3Scr.c` *defining* `GX_LoadBG0Scr` while the build still bound that filename
to `GXS_LoadBG3Scr`'s address.

**`dsd check` reported 306/0 in that state. `audit_shadowed.py` reported 0 too.**

This is the same blind spot as an `asm_stubs/` twin shadowing real C, reached from the other
direction: when the delinked object does not provide what the slot wants, the build falls back to
the original bytes and the gate -- which compares against those same original bytes -- is happy.

**So: 306 proves the ROM still matches. It does NOT prove your C produced any of it.**
The only per-file proof is `verify_idx.py` on the file itself. Run it after ANY change that can
desync filename from content: symbol renames, file moves, copying a template.

## ★★ STRUCT DISCOVERY BY ACCESSOR SWEEP -- the cheapest layout you will ever get

*(2026-07-20. Produced `MenuContext` -- 17 fields shared by ov008 and ov025 -- in one pass.)*

When a global has dozens of tiny users, most of them are one-field accessors of the shape
`*(g+4) -> +OFFSET`. **Disassemble every user under ~40 bytes and read the offset out of each
one.** You get the field map, the WIDTH of each field (from `ldr`/`ldrh`/`ldrsh`/`ldrb`), whether
it is an array (an `add rX, rY, rZ` index, scaled by the `lsl`), and GET/SET pairs that
corroborate each other -- with no Ghidra round trip and no reading of any function's logic.

Then: create the struct, type the global's pool slots `T **` (see the pool-slot recipe), and
every one of those dozens of users decompiles as `PTR[1]->nField9630`.

**Do NOT sum every immediate.** The first version added the `ldr rX,[pc,#N]` displacement to
every offset, inflating each by 8-0xc. It looked entirely plausible -- consistent, plenty of
paired GET/SET, sensible spacing. What exposed it was that names ALREADY in Ghidra
(`Ov008_GetCtxBlock9500`, `...954c`, `...968c`) did not match the computed numbers.

★ **If a mechanical extraction contradicts a name that already existed, suspect the extraction.**
Correct method: accumulate only the `add rX, rY, #imm` bases plus the final load/store
displacement, and skip both the `[pc, #N]` pool load and the `[rX, #4]` global deref.

⚠ **Known limitation: it assumes ONE field per accessor.** A setter that writes two fields comes
out as the SUM of both bases -- `+0x12c3a` in the ov008/ov025 sweep, which is nowhere near either
real field (0x9638 and 0x963a). The tell is an offset far outside the cluster the rest form.
Both overlays produced the same bogus offset, so consistency across units does NOT validate it.

### Cross-unit corroboration is the strongest evidence available here

Running the sweep independently on ov008 and ov025 produced the same 17 offsets with the same
widths. Neither extraction could see the other. That is what upgraded "these two overlays share a
menu context" from a two-field observation in `state.md` to a proven 17-field layout, and it is
worth doing deliberately whenever two units look like twins.

## ★★ Merge a struct from a lane's MATCHED C -- layout firm, names yours

*(2026-07-20. Produced `Ov000SceneContext`, 0xd18c, from five independent views.)*

A peer lane's hand-off is a layout source as well as a match source. The lane stated the split
explicitly and it is the right one to assume in general:

> **offsets, strides, sizes and matches are FIRM; struct and field NAMES are provisional.**

So: take the geometry, throw away the names, and build the Ghidra type yourself. Extract every
`typedef struct` from the lane's matched `.c` files, convert each to absolute offsets, and merge.

```bash
awk '/^typedef struct/,/^}/' src/overlays/ovNNN/calls/*.c
```

Five files each declared a differently-shaped `OverlayContext`; converted to absolute offsets they
agree on every field and the total closes exactly at the size the constructor's `MI_CpuFill8`
clears. **Each offset also cross-checked against the lane's prose description of the function that
touches it** -- that is two independent confirmations per field, and it is cheap.

⚠ **Expect the views to CONFLICT, and do not resolve it by picking a winner.** Four views read
+0x00 as a 16-bit pair and one reads it as a 32-bit counter. That is the per-file "struct as a
codegen tool" divergence doing exactly what it is supposed to do. Model the majority reading in
Ghidra and RECORD the disagreement in the field comment. Ghidra is the data model; the `.c` files
are tooling, and they are allowed to disagree with it and with each other.

---

## ★ "Check the existing name" has a second half: check it belongs to THIS object

*(2026-07-22. Cost one wrong commit, caught an hour later.)*

The rule in SKILL.md is "check the name the tree already uses before creating one" — and I
followed it. `data_ov002_0207f618` needed a type, `Ov002PanelContext` (548 B) already existed, the
name fitted the function I was writing (`Ov002_SetPanelMode`), so I typed all **28** of f618's
literal-pool slots as `Ov002PanelContext **`.

It was the wrong object. `Ov002PanelContext` had been reconstructed by `accsweep.py` from
**`data_ov002_0207f614`'s** accessor family, and every named field in it is an f614 offset —
`nField003c`, `nField0048`, `nField018c`, `nField01b8`, exactly the offsets f614's consumers use in
the C tree. f618's own accessors stride **0x18 at +0x7c** and **4 at +0xce**, which land in that
type's padding and match nothing. Two globals four bytes apart, two different objects.

**What caught it** was decompiling an unrelated function in the next batch — `func_ov002_02056b70`,
an f614 consumer — and seeing Ghidra render it as `Ov002PanelContext *` **already**. If the type
was already bound to f614, it could not also be f618's.

So the check to actually run, and it is one call:

> **`get_struct_layout <Type>`, and read its named field offsets against the offsets THIS global's
> own accessors use.** A type reconstructed from an accessor family is named after the family, not
> after the concept — the offsets are the identity, the name is a label someone chose.

Two corollaries:
- A plausible-sounding name is the *weakest* evidence available here. `PanelContext` fitted a
  function called `SetPanelMode` perfectly, and that agreement was a coincidence of vocabulary.
- **Typing pool slots is a bulk operation, so a wrong assignment is a bulk error** — 28 functions
  would have decompiled into a confident, wrong field vocabulary. Prefer leaving a global untyped
  over typing it on a name match; an untyped global reads as offsets, which is honest.

Backing it out is cheap (`clearCodeUnits` over the slots), so the recovery cost is nothing compared
to the cost of it going unnoticed.


---

## ★★★ 2026-07-23 -- LA DEUDA DE STRUCTS ESTABA MAL CONTADA, Y EL NUMERO ENGANABA

`audit_struct_sync.py` decia **"817 de 878 structs sin tipo en Ghidra"**. Ese numero no era
deuda. Medido sobre todo el arbol, esos nombres se parten en tres y solo el tercer grupo es
trabajo pendiente:

| categoria | cuantos | por que NO se tipan |
|---|---:|---|
| dispositivos de codegen | 557 | todos sus miembros son bitfields, o son un relleno + <=2 campos |
| nombres de scratch | 40 | `Obj` sale en 596 ficheros con **61 cuerpos distintos**; `S` en 292 con 67 |
| alias de un tipo que YA existe | 94 | `Vec3`/`vec3`/`vec`/`w3`/`V`/`s3` son `VecFx32`; `blk16`/`vec4`/`w4`/`quat` son `Quaternion` |
| **deuda real** | **210** | |

**La leccion de fondo**: `struct bf { unsigned b : 8; }` en 407 ficheros y `struct hw60` en 658
no son objetos. No tienen direccion ni semantica: existen para forzar `lsl #24 ; lsr #24` en vez
de `and #0xff`, o para alcanzar un offset. Tiparlos en Ghidra seria inventarse un modelo de datos
que el juego no tiene. Y `Obj` con 61 cuerpos distintos no se puede unificar sin mentir.

La herramienta ahora **clasifica midiendo** (todos los miembros son bitfields; el cuerpo no
coincide entre ficheros; la FORMA normalizada coincide con un tipo existente) en vez de llevar una
lista negra a mano, y ordena la deuda real por numero de ficheros que se volverian legibles.

⚠ **Y tenia un bug que conviene recordar**: construia el conjunto "Ghidra ya lo tiene" con
`re.findall(r'\w+')` sobre TODA la respuesta del puente, asi que cualquier palabra que apareciera
en una ruta o en una descripcion contaba como tipo existente. Una comprobacion de pertenencia que
no puede fallar no es una comprobacion -- la misma regla que ya costo una sesion con `asm_stubs`
en `nearfam.py` y en el barrido de builds.

### Tipos creados en esa pasada

- **`ActorXfmBlock`** (0x2c) -- las 11 palabras que se copian tal cual de `actor+0xa0` a cada nodo
  de render en `+0x10`. 48 ficheros lo declaran y **los 48 coinciden**, asi que el tamano y el
  hecho de que sea UN objeto son firmes; el interior sigue sin decodificar y la descripcion lo dice.
  Colocado dentro de `Actor` partiendo el relleno `pada0` (quedan 88 bytes de padding).
- **`Quaternion`** (0x10) -- cuatro fx32. Nombre tomado del que ya usa el arbol (15 ficheros dicen
  `Quaternion`, 12 `quat`), no inventado. La evidencia fuerte es
  `func_0202ed60(Quaternion *out, const VecFx32 *axis, const VecFx32 *hit)` en ov158, que lo empareja
  con el `VecFx32` que ya existia.
- **`AiSplineState`** (0x44) y **`Ov030EmitterSlot`** (0x170), de los layouts decodificados al casar
  la familia ov117 y la de ov030.

⚠ `Ov030EmitterSlot` salio primero a 0x160 -- hasta su ultimo campo escrito, no hasta el stride
real de 0x170. Y `Ov022SlotId` salio a 3 bytes en vez de 1 porque una estructura sin
`setPackingEnabled(True)` le da a cada bitfield su propia unidad de almacenamiento. **Leer el
tamano de vuelta despues de crear un tipo**, siempre.

### Lo que queda en la deuda real, por rentabilidad

`Src` (32 ficheros), `obj` (25), `top` (16), `Holder` (15), `Buf` (13), `mid` (12), `Big` (10).
Son vistas de objetos por familia y necesitan analisis por familia: no se pueden crear a ciegas.

## Two ov008 layout names were WRONG, and the fix came from the matched source (2026-07-25)

Found while doing the semantic layer for `Ov008_TickPageScroll` (`func_ov008_02068e68`).
Both functions already had confident-looking names that described the opposite of what
they do, and both are read by dozens of call sites:

| address | was | is | why |
|---|---|---|---|
| `arm9_ov008::02054820` | `Ov008_ApplyFirstValidSlot` | **`Ov008_GetEntryPos`** | it *returns* `Slot_GetPositionPtr(root, id)` for the first of the entry's two slot ids that is not -1. It applies nothing; the caller dereferences the result. 25 callers. |
| `arm9_ov008::02054858` | `Ov008_ReleaseTwoSlotsEx` | **`Ov008_SetEntryPos`** | it calls `Slot_SetPosition(root, id, pPos)` for *every* valid slot id. It releases nothing. 50 callers. |

The evidence was free: both functions are already byte-exact in `src/overlays/ov008/`,
and the generic helpers they call were already named `Slot_GetPositionPtr` /
`Slot_SetPosition`. **Reading the matched C of a callee settles its name faster than
reading its own decompilation** -- and a wrong name that is already in Ghidra reads as
authoritative, which is exactly why it survived.

Prototypes were typed at the same time, so the position now shows as a type rather
than an `undefined4 *`:

```
UiLayoutPos * Ov008_GetEntryPos(int nSceneRoot, int *pEntry)
void          Ov008_SetEntryPos(int nSceneRoot, int *pEntry, UiLayoutPos *pPos)
UiLayoutPos * Slot_GetPositionPtr(int nSceneRoot, int nSlot)      /* MAIN, shared */
void          Slot_SetPosition(int nSceneRoot, int nSlot, UiLayoutPos *pPos)
```

`UiLayoutPos` is the new 2-int fixed-point point type for the UI layout system. The
tree only had `struct vec2_020548bc` for it (an address-derived scratch name in 3
files); `VecFx32` is the established name but it is 3D, so it does not apply.

Also settled while here, and worth knowing before naming anything in ov008:
`Ov008_GetContext` (`02050c54`, 70 callers) returns `data_ov008_02090f04[1]` -- the
scene root -- and `func_ov008_02050c28` (27 callers) returns **root + 0x9500**. So the
value that reads like an opaque "handle" at the top of many ov008 functions is just a
pointer to a sub-object of the same root. `FindEntryById` (`02054788`, **518 callers**)
walks the NNS list at `root + 0x4a38` for the node whose field at +0x0C equals the tag,
which confirms that existing name.

## ⭐ OVERLAY FUNCTIONS *ARE* REACHABLE IN GHIDRA — use the overlay-space prefix (2026-08-05)

The old "ov002 overlay functions not reachable by raw address" note was WRONG and cost a whole
32-function batch of un-synced names. The truth:

- `days.nds` is loaded with 407 overlay spaces. Each overlay is a space named `arm9_ovNNN`
  (code) / `arm9_ovNNN.bss` (bss), all overlaying `ram`. Get the list with `get_address_spaces`.
- A raw address like `0x02054b40` resolves to the DEFAULT `ram` space, where these functions do NOT
  exist — that is the "No function found" / stray-1-byte-function trap. **Always prefix:
  `arm9_ov002::02054b40`.** Overlay names are case-sensitive.
- The overlay bytes are present and disassemblable. To carve+name a not-yet-defined overlay function
  in one `run_script_inline` (Java): `AddressSpace ov = currentProgram.getAddressFactory()
  .getAddressSpace("arm9_ov002"); Address a = ov.getAddress(Long.parseLong(hex,16)); Function f =
  getFunctionAt(a); if(f==null){ disassemble(a); f = createFunction(a,name);} f.setName(name,
  SourceType.USER_DEFINED);` — this created + named all 32 in one pass (auto-decompiled signatures
  appeared too).
- `run_script_inline` does NOT surface `println` (status only) — VERIFY with
  `get_function_by_address arm9_ov002::ADDR` or `search_functions`. `run_ghidra_script` DOES capture
  console output (that is how CloseTxAndSave reports `closed=N; SAVED_OK`).
- Persist with `run_ghidra_script CloseTxAndSave.py` (drains analysis, closes the leaked MCP tx,
  saves). Its trailing `IllegalStateException: No transaction is open` is HARMLESS — read the
  CONSOLE OUTPUT line (`SAVED_OK`), not the success flag.

**GOING FORWARD: name each matched overlay function in Ghidra in the same batch as the C match**,
using `arm9_ovNNN::ADDR`. Prior sessions already named many with the `Ov002_` prefix — mine used
`ov002_` (lowercase o); both coexist fine.
