# Game-flow skeleton (Fase 4 — the PC-port backbone)

Traced 2026-07-15. The boot→main-loop→scene backbone, decompiled and named. This
is the flow the PC port must reproduce (ov001 HW init is replaced by the platform
layer and does NOT need porting).

## Boot chain
- **crt0 @ 0x02000800** — stacks/CPU modes, clears `.bss` (strlo loop @0x020008b4),
  cache flush, NitroSDK init (`bl 0x20207f0`, `bl 0x2020808`), then
  `ldr r1,[=0x02000bcc]; bx r1` → `main`.
- **`main` @ 0x02000bcc** (symbol is literally `main`, size 0x350, MAIN static;
  named `main` in Ghidra, plate comment set). Not in `func_index.json` (blob-gap).
  Readable reconstruction: **`src/nonmatching/func_02000bcc.c`** (not byte-verified;
  a future byte-exact carve target — has a boot-mode jump table + VBlank pacing loops).

### `main` sequence
1. `func_020027f0()` early init; `FS_Init(3)` (0x0200a9a8).
2. **ov001 one-shot HW init**: `FS_LoadOverlay(0,1)` (0x0200b6ac) → `ov001_BootInit`
   (`func_0204cd7c`) → `FS_UnloadOverlay(0,1)` (0x0200b700). ov001 exists only to run
   DS hardware bring-up once, then is unloaded. **Port replaces BootInit entirely.**
3. `func_020285f0()`, `func_02023f58()` (task-system init).
4. **boot mode → game mode**: `func_02003a20(&m)` reads boot mode 0..5; jump table
   @0x02000c14; `func_02024e34(m==0 ? 1 : m, 0)` = SetGameMode.
5. boot resource tables via `FS_TryLoadTable` (0x0200b100); store handle to
   `data_020442a0.handle`.
6. **`InstantiateClass(&g_BootTaskClassDesc, 1)`** (0x02023930) — creates the root
   task. → runs `BootTask_Construct` (see below) which selects the first scene.
7. **FRAME LOOP @0x02000cac** (see below).

## Task/class framework (the "scene/task" system)
- **`InstantiateClass(classDesc, arg)` @ 0x02023930** — `AllocFromExpHeapWrapper(0x2c,
  *DAT_0202395c)` then `RunClassConstructor(obj, classDesc, arg)`. 71+ per-overlay
  wrappers of the form `void func_ovNNN_YYYY(int a){ InstantiateClass(&desc,a); }`.
- **`RunClassConstructor(obj, desc, arg)` @ 0x02023960** — builds a 0x2c-byte task
  object from the **class descriptor** and links it into the global task list at
  `*(DAT_02023a38+4)`, then calls the descriptor's ctor. **Class descriptor layout**
  (u16* `desc`):
  | off | field | notes |
  |-----|-------|-------|
  | +0x00 u16 | magicA | → obj+0x10 |
  | +0x02 u16 | magicB | → obj+0x12 |
  | +0x04 ptr | **constructor** | called `(arg)`; return → obj+0x14 |
  | +0x08 ptr | method/vtable | stored obj+0x18 |
  | +0x0c u32 | auxSize | aux storage bytes (alloc+memset from arena) → obj+0x24, ptr obj+0x20 |
  | +0x10 ptr | arenaRef | `*arenaRef` = ExpHeap arena to alloc from → obj+0x1c |
  Task object fields: obj[1]=list link, obj[7/0x1c]=arena, obj[8/0x20]=aux ptr,
  obj[9/0x24]=aux size, obj[6/0x18]=method, obj[5]=0, obj[10]=0.

## First scene (boot/logo)
- **`g_BootTaskClassDesc` @ data_02042534** (`.data`, MAIN static; renamed in Ghidra):
  magicB=0x0f, ctor=`0x02020929` (THUMB), method=`0x02020975` (stub `bx lr`),
  auxSize=8, arenaRef=`&data_0204c024`.
- **`BootTask_Construct` @ 0x02020928** (THUMB; plate comment set, no Ghidra func
  defined — undisassembled THUMB). Inits subsystems, then picks the first scene from
  the persisted state word `*(0x027ffc20)`:
  - `state==0` (fresh boot) → `StoreGlobalPairAt10(1,0)` → **Scene 1** (boot/logo)
  - `state==-2` → `StoreGlobalPairAt10(1)` → Scene 1
  - else → `StoreGlobalPairAt10(0xc)` → Scene 12
- **`StoreGlobalPairAt10` @ 0x02020a78** — writes `{sceneId,arg}` to the scene-control
  struct `*(DAT_02020a80)+0x10 / +0x14` (base near `data_0204bd84`). This is the
  "pending scene request" latch.

## Scene poll + transitions (frame loop internals)
- **`Game_PollSceneAlive` @ 0x02001030** (renamed; `src/calls/func_02001030.c`,
  byte-exact): `id = data_027e0060` (current-scene id byte, 0 = none); if 0 return 0;
  else return `func_ov105_020bf24c()`. In `main` the frame loop calls it once/frame;
  a 0 return means "scene ended" → branch to the fade/teardown path @0x02000e20.
- **`func_ov105_020bf24c`** (ov105, 16 B) — pure getter: returns `sceneMgr->field_0x24`
  ("running" flag), ignoring its arg. Siblings `020bf25c`(+0x30), `020bf26c`(+0xc u16)
  are getters on the same ov105 scene-manager struct (pool base is one constant).
  **ov105 is a resident "scene engine" overlay** (MAIN static hard-calls into it).
- **`FrameStep_UpdateTaskQueue` @ 0x020115b8** (renamed) — per-frame walk of the task
  queue (`func_02011538`/`AdvanceAndDecrement` → `func_020114ac` per entry), gated by a
  CPU-time budget (`*(DAT_0201163c+0x10) < 0x2400`). Called twice/frame.
- Frame loop other calls: `OS_WaitVBlankIntr`(0x02003878, frame begin), `func_01ff80a8`
  (GetVBlankCount), `G3X_ResetMtxStack`(0x02006d6c), render `func_02023adc`(0)/
  `func_020208a4`(1) selected by display-mode byte `data_0204bd84` (0/1/2), present
  `func_01ff80b8`, transition dispatch `func_0200d49c`/`func_0200d164`/`func_0200d4bc`,
  input via held-keys `*(0x027fffa8)` bit 0x8000.

## Key globals
- `data_027e0060` — current scene id (s8).
- `data_0204bd84` — display mode (0/1/2); base of the scene-control struct.
- `data_0204c058` — frame-rate/skip mode.
- `data_020442a0` — scene-render state: +0x00 phase flag, +0x04 handle.
- `0x027ffc20` — persisted boot/continue state (drives first-scene choice).

## TODO for a deeper port pass
- Map `func_ov105_020bf24c`'s scene-manager struct fully (fields +0xc/+0x24/+0x30…)
  and the real per-scene update callback path (likely reached via the task queue in
  `FrameStep_UpdateTaskQueue` / `func_020114ac`, not via the getter).
- Enumerate the Scene id table (1=boot/logo, 0xc=12, …) — find all `StoreGlobalPairAt10`
  callers and the consumer that turns a pending id into a loaded scene overlay.
- Byte-exact carve of `main` (jump table + VBlank pacing loops) if desired.

## Scene/object update model (Fase 4 follow-up, 2026-07-15 — CORRECTED)
The real per-frame **object/scene update** is **`func_02023adc(mode)`** (main frame loop
calls `FUN_02023adc(0)`), NOT the "task queue". It walks the InstantiateClass object list
via the **list-manager @ 0x0204c058** (+0x04 = current-object, +0x08 = frame counter,
+0x0c = list head) and for each object calls its **state fn at obj+0x14** with NO args
(the fn reads its `this` from the current-object global `*(0x0204c058+4)`), storing any
nonzero return as the next state. Object fields: obj[0]=flags (bit0/bit2 gate ticking),
obj[5]=lifecycle sentinel (0xffffffff=dead passthrough, 0xfffffffe=spawning→func_02023a4c),
obj[7]=arena. **Initial state = the constructor's return value** (RunClassConstructor stores
ctor-return → obj+0x14). Signature: `void *ObjState(void)` (returns next state or 0=stay).
- **CORRECTION**: `FrameStep_UpdateTaskQueue` (0x020115b8) is the **GFX command queue**
  processor (`GFXi_EnqueueCommand` @ 0x02011640; queue ctx @ 0x02047370; type-vtable
  @ 0x02041934, 32 slots; item {+0=type,+4=a1,+8=a2,+0xc=a3}; dispatch
  `vtable[type](a1,a2,a3)`). That's graphics commands, not scene logic. Earlier note was wrong.
- **ov105 sceneMgr @ 0x020c04c0** = state holder only (getters: 0xbf24c→+0x24 "running",
  0xbf25c→+0x30, 0xbf26c→+0xc u16; methods 0x020be43c-0x020be5cc). Does NOT load overlays
  or call InstantiateClass.
- **Scene-control struct @ 0x0204bda4**: +0x00 u16 (get 0x02020aa4/set 0x02020a94), +0x0c
  (get 0x02020a84), **+0x10 pending scene id / +0x14 pending arg** (set by
  `StoreGlobalPairAt10` 0x02020a78). Runtime array @ 0x020425ec (SetArrayEntry 0x02020ab4).
  Active flag data_027e0060 (0/1; SceneTick family 0x02001030/54/88).
- **Scene requesters** (StoreGlobalPairAt10 callers): main/BootTask_Construct (ids 1, 12),
  ov000 (0x0204ee18,0x0204ef14), ov002 (0x020687e8,0x0206885e,0x02068870,0x02068896,0x0206889e).
- **BootTask initial state = 0x02020978** (ARM): thin steady state, each frame calls helper
  ~0x0202099x and returns 0 (stays). Boot-logo visuals are in a scene overlay loaded via the
  request mechanism.
## Scene dispatcher (Fase 4 — RESOLVED 2026-07-15) — the pending-id consumer

- **`func_0202099c`** (ARM, MAIN static, **byte-exact** `src/calls/func_0202099c.c`, 220 B) is the
  consumer. It is the per-frame helper called by the BootTask steady state
  (`func_02020978` = `{ func_0202099c(); return 0; }`), whose return is ignored. Ghidra display
  name intended: `SceneDispatch_AdvancePending` (rename pending — Ghidra tx was stuck this
  session; apply on recovery). Two-step machine over the scene-control record @0x0204bda4:
  - **Teardown**: if `rec.obj != 0` (current scene object exists) **and** `func_02023bbc(obj)!=0`
    (scene reports ended), unload the current scene's overlay via `func_0201e4a8(0)` (skipped when
    `entry->overlayId == -1`), `func_02020834()`, `func_02023604(*(void**)0x0204c02c)`, then
    clear `obj` and `curId`.
  - **Load**: when `rec.obj == 0` and `pendId != 0`, look the id up in **g_SceneTable @0x02042548**
    (`SceneEntry{ int overlayId; void *classDesc; }`, indexed by scene id): if `overlayId != -1`,
    `func_0201e470(0, overlayId)` = FS_LoadOverlay(ARM9, overlayId); then
    `obj = InstantiateClass(entry->classDesc, pendArg)` (0x02023930); `func_02023a3c(obj, 1)`;
    latch `curId = pendId`; clear `pendId`/`pendArg`. Always returns 1.
- **Scene-control record @0x0204bda4** (one struct; `data_0204bda4` and `data_0204bda8` are two
  delink symbols into it — `data_0204bda8 == &rec.obj == rec+4`; func_02020988 clears rec+4..+0x18):
  | off | abs | field |
  |-----|-----|-------|
  | +0x00 | 0x0204bda4 | u16 flag (get 0x02020aa4 / set 0x02020a94) |
  | +0x04 | 0x0204bda8 | obj — current scene task object (InstantiateClass result) |
  | +0x08 | 0x0204bdac | entry — &g_SceneTable[curId] |
  | +0x0c | 0x0204bdb0 | curId — active scene id (get 0x02020a84) |
  | +0x10 | 0x0204bdb4 | pendId — pending scene id (set by StoreGlobalPairAt10 0x02020a78) |
  | +0x14 | 0x0204bdb8 | pendArg — pending scene arg |
- **g_SceneTable @0x02042548** (`{overlayId, classDesc}` × id, `overlayId==0xffffffff` = no overlay):
  | id | overlay | classDesc | id | overlay | classDesc |
  |----|---------|-----------|----|---------|-----------|
  | 0 | — | — | 7 | ov06 (0x06) | 0x020565c0 |
  | **1** | **ov000 (0x00)** | **0x0205a9c0** | 8 | ov11 (0x0b) | 0x0205e8a0 |
  | 2 | ov02 (0x02) | 0x0207ef54 | 9 | ov09 (0x09) | 0x02056220 |
  | 3 | ov03 (0x03) | 0x0204f8e4 | 10 | ov07 (0x07) | 0x0204d3c4 |
  | 4 | — | — | 11 | ov12 (0x0c) | 0x0205c2bc |
  | 5 | ov04 (0x04) | 0x02051210 | 12 | ov10 (0x0a) | 0x0204cfa0 |
  | 6 | ov05 (0x05) | 0x0205b4dc | 19 | ov08 (0x08) | 0x0208ffa0 |

  (field0 is the FS overlay index, not the scene id; ids 0,4,13–18 have overlayId=-1.)
- **Scene 1 (boot/logo) = ov000**, class descriptor @arm9_ov000::0x0205a9c0 =
  { magicA=8, magicB=0x0f, **ctor=0x0204d630**, method=0x0204dbb4, auxSize=0x507c, arenaRef=0 }.
  So the boot-logo visuals are built by **`func_ov000_0204d630`** (byte-exact
  `src/overlays/ov000/calls/func_ov000_0204d630.c`, 252 B). ov000 spans 0x0204cac0–0x0205ac1f.
- **`func_ov000_0204d630`** (Scene-1 ctor, MATCHED 2026-07-15): grabs the current root heap as the
  scene data block (cached in `data_ov000_0205ac20`), one-time init `func_0201e1d0()`, then picks
  the initial **state fn** by launch arg + boot sub-mode `func_ov000_02054bac()`:
  `switch(mode)` on respawn (arg 0xfffffffe), else arg-first if-chain. Heap word slots
  [0x1311]=re-enter, [0x1313]=sub-mode, [0x1317]=mode-5. Fresh boot: `MI_CpuFill8(heap,0,0x507c)`
  then `return func_ov000_0204d7c8(0)`. Initial states returned: `func_ov000_0204f6c8` (carved),
  `func_ov000_0204d560`, or `func_ov000_0204d7c8(0)`'s result.
- **`func_ov000_0204d7c8`** (fresh-boot logo GFX setup, MATCHED 2026-07-15, byte-exact
  `src/overlays/ov000/calls/func_ov000_0204d7c8.c`, 1004 B / 41 relocs) — the real first-screen
  build: VRAM bank assign (`GX_SetBankForTex/BG/SubBG/SubOBJ`, `GX_BeginLoadOBJExtPltt`), programs
  both display engines (main+sub DISPCNT/BG control via `reg_GX_DISPCNT`/`reg_G2_BG0CNT` + held
  `vu16*` for BG1CNT 0x0400000a and sub 0x0400100a + independent `vu32*` subDISPCNT 0x04001000),
  loads the logo archive `func_0201ef9c` + 8 sub-resources (table `data_ov000_0205a9d4`, 3 s8/entry)
  into the scene heap, wires the sequence/anim players (`func_02024a6c`/`func_02024ae0`), copies a
  0x200-byte palette, returns the running-state fn (`func_ov000_0204dc38` on arg 0, else
  `func_ov000_0204ea68`; or `func_ov000_0204df98` when re-entering). **The entire Scene-1 path,
  boot→first pixels, is now byte-exact.** Deeper visual detail lives one level down in the state
  fns (`func_ov000_0204dc38`, `func_ov000_0204f6c8`) and the archive contents.

## Title (Scene 7 = ov06) + Main menu (Scene 0x13 = ov08) — 2026-07-15 (for the port)

**Scene 7 = TITLE, overlay ov06.** g_SceneTable[7] = {overlayId 6, classDesc ov06::0x020565c0}.
- **Ctor chain** (each step instantiates the next as a child object, InstantiateClass):
  - Outer `ov06::0x020560cc` (auxSize 8): grabs root heap, `InstantiateClass(0x020563e4, arg)` (real
    title class) → heap[0]; returns top state `ov06::0x02056154`.
  - Real title `ov06::0x020500c4` (auxSize 0x70): `InstantiateClass(0x0205652c, ...)` (visual class),
    window init via `func_02036298`; returns state 0x02050e1c/0x020502e4 by variant.
  - **Visual `ov06::0x0205454c` (auxSize 0x97f8) = THE GRAPHICS LOADER.**
- **Files the title loads** (in the visual ctor, descriptors are inline ASCII-path structs):
  - Font `/text/font_eu_10all.NFTR` ×2 via `LoadResourceThenInit_0202f7fc`.
  - UI containers **`UI/mlt/res.p2`** and **`UI/mlt/res_&.p2`** via `Msg_OpenContainerAndReadHeader`
    (`&` = language-code placeholder substituted at load). Stored at heap[0]/heap[1].
  - Plus 8× 0x600-byte tile/palette buffers (`func_02023684(0x600,2)`), DISPCNT/BG regs.
- **Start transition**: top state `ov06::0x02056154` polls `func_ov006_02051f6c` (input; returns 1 when
  key state 7/9 = Start). On 1 → `StoreGlobalPairAt10(0x13, 0)` + return 0xfffffffe (spawn) → **Scene
  0x13 (19)**. (A 2nd branch → Scene 1 = logo, e.g. attract-mode reset.)

**Scene 0x13 (19) = MAIN MENU, overlay ov08.** g_SceneTable[19] = {overlayId 8, classDesc ov08::0x0208ffa0}.
- **Ctor `ov08::0x0204db2c` (auxSize 0x5050 — the whole menu):** `func_ov008_0204d7c0` (DISPCNT/BG/VRAM
  setup), `func_ov008_0204d8bc` (loads the container), registers handlers, returns state `ov08::0x0204dd24`.
- **Files the menu loads** (descriptor @0x0208ffb4; container load in func_0204d8bc → heap+0x608):
  - **`UI/mlt/res.p2`** (SAME primary UI container as the title) via `Msg_OpenContainerAndReadHeader`.
  - Fonts `text/font_eu_08.nftr`, `text/font_eu_...`.
- **Navigation state**: `ov08::0x0204dd24` runs `func_ov008_0204da6c` (per-frame input/cursor) +
  `func_ov008_0204d564` (draw); on select it dispatches events and returns the next state
  `DAT_0204de3c`. Cursor/option logic lives in **func_ov008_0204da6c**.

Key SDK-ish loaders: `Msg_OpenContainerAndReadHeader(pathDesc, 0xe, ...)` opens a .p2 container by
inline path; `LoadResourceThenInit_0202f7fc(dst, pathDesc, ...)` loads a single file. Scene switch is
always `StoreGlobalPairAt10(sceneId, arg)` consumed by func_0202099c (dispatcher) next frame.

## Title (ov006) resource->layer map (item 1, extracted 2026-07-15)
Object base = *data_ov006_02056664; sub-block at base+0x9000. Loaded by ctor func_ov006_0205454c:
- base[0] = res.p2 container (data_ov006_02056578 path), base[1] = res_&.p2 (lang, data_ov006_02056588).
- base+0x9760 = graphic resource 1 (data_ov006_02056540, via func_0202f7fc), base+0x97ac = resource 2 (data_ov006_0205655c).

func_ov006_02053b24 (BG layers, per sub-state):
- BG layer 3 <- resource base+0x9760 (obj base+0x976c), placement rect {x0,y0,w0x20,h0x18,..,alpha,..,6}.
- BG layer 7 <- resource base+0x97ac (obj base+0x97b8).
- Normal title states {0,1,2,3,10,11,13,14}: both alpha 0xf (shown). Attract {4,5,6,7}: layer7 alpha 0 (hidden). {8,9,12}: unchanged.

func_ov006_0205341c (title TEXT, per-language, per sub-state) [data extracted, match pending - 792B]:
- Loads localized text archive piVar1 via Archive_LoadFile(idx from base[0]+0x8000&0xfffffc<<7|0x80000000, mode 0xe).
- Sub-resource cells selected via func_02024c94(&info, arch, -1, IDX, param); IDX = the text piece:
  - Normal states: IDX 1 (param 1) then IDX 0 (param 0).
  - Attract states {4-7}: IDX 3 (param3), IDX 4 (param-1), IDX 2 (param2).
- Extra language-variant archive (piVar3) loaded when LoadGlobalShort_0204c1ec()!=1: path |0x80000003 (normal) / |0x80000004 (attract), sub-resource IDX 0.
- Uploads via GX/GXS_LoadBGPltt (palette) + GXS_LoadBG3Char variants (tiles) from the cell's pChar/pPltt fields.

func_ov006_02053734 (BG char/screen-base regs per sub-state) - MATCHED. func_ov006_02054a00 (per-frame state, 15-entry handler table data_ov006_020562d0) - MATCHED.

## ov000 logo sub-resources (item 4, 2026-07-15)
data_ov000_0205a9d4 = 8 triples {resIdx, p1, p2} loaded by func_ov000_0204d7c8 loop into heap slots h[0x54+3i]:
  i0{0,0,0} i1{1,-1,-1} i2{2,-1,-1} i3{3,1,1} i4{4,2,2} i5{5,-1,-1} i6{6,-1,-1} i7{7,3,3}
Sub-resources = archive indices 0..7 (from handle h[0x53]). Animation players wired to only TWO:
  player 5 <- sub-resource 0 (slot h[0x54]); player 1 <- sub-resource 4 (slot h[0x60]).
So the VISIBLE animated logo elements are sub-resource 0 and sub-resource 4; the -1/-1 ones
(1,2,5,6) are static tile/palette layers. Nearby strings: "UI/load/lrd_&.s.z" (compressed load
screen), "text/font_eu_10all.nftr", "/ttl/ttl.p2" + "ttl/ttl_&.p2" (title archive).

## Correction: ov006 title 0x9760/0x97ac resources are FONTS, not logo gfx
data_ov006_02056578="UI/mlt/res.p2", 02056588="UI/mlt/res_&.p2" (containers, base[0]/base[1]).
data_ov006_02056540="/text/font_eu_10all.NFTR" (font). So func_0202f7fc loads the font into
base+0x9760 (and base+0x97ac); the BG layers 3/7 bound by func_ov006_02053b24 are FONT-based
TEXT layers. The real title graphic cells come from res.p2 via func_ov006_0205341c.

## Menu (ov008) layout + event-flags + sound (items 2/3, 2026-07-15)
Menu ctor func_ov008_0204db2c:
- Container: data_ov008_0208ffb4 = "UI/mlt/res.p2" -> heap[0x608] (func_02024ee8 mode 0xe).
- func_020235bc(0x200a); func_020235bc(0x200c): these CLEAR event-flag bits 0x200a/0x200c in the
  global flag bitmask at data_0204be18+0x10. func_020235bc = clear-bit (func_02025668),
  func_020235d0(bit,N) = read N bits (func_020256b8). These are PROGRESS/STATE event-flags,
  NOT sound. (dd24 reads flags 0x451, 0x44e for menu-option availability.)
Menu root cell (func_ov008_0204d8bc, MATCHED): sub-resource index 1 of res.p2
  (desc {((cont+0x8000&0xfffffc)<<7)|0x80000001, 2,0,0}), registered func_02032388 into
  object-manager heap+0x60c, created at slot 5 -> heap[0x5044], scale 1.0 (0x8000/0x8000),
  frame 0, pos default (0,0). Sub-BG mode 1 (DISPCNT sub 0x04001000 |0x1000).
- Object-manager API: func_02032388 (register), WM_EndKeySharing_0x02032444 (create/slot),
  func_020325ec (setFrame), func_020326cc (commit), func_0203257c (setScale). All matched.

Sound/BGM (item 3): SDAT play API is SND_PrepareSeq/SND_StartPreparedSeq (0x020080xx). The ONLY
caller of SND_StartPreparedSeq is func_0201a360 (356B, the sound-manager wrapper) - the single
SDAT choke-point. Neither ov006 nor ov008 scene code calls SND_* directly, so BGM is requested
through a higher-level path that reaches func_0201a360; the sequence-id<->BGM table lives around
func_0201a360, not in the scene event-flag calls. func_ov006_020551a4 (the title "1000" call) is
NOT sound - it is the state-transition+scroll setup (mode, scrollX/Y clamped +/-0x10).

## Item resolution 2026-07-15 (round 2) - MATCHES + scene ids
func_ov006_0205341c MATCHED (792B). Confirms title sub-resource binding:
- Main pack = res_&.p2 container base[0]; entry addr = (container+0x8000 & 0xfffffc)<<7 | 0x8000000N.
- Normal states {0,1,2,3,10,11,13,14}: cell sub-res idx 1 (GX_LoadBGPltt main + BG3 char) then
  idx 0 (GXS_LoadBGPltt sub + BG3 char). Language pack (res_&.p2 via base[1]) sub-resource 3 when
  func_02024e5c()!=1 (i.e. non-default language) overlays extra char.
- Attract states {4,5,6,7}: cell sub-res idx 3, then idx 4, then idx 2; language pack sub-resource 4.
- Uploads target the SUB engine BG3 (GXS_LoadBG3Char variants). Palette via GX_LoadBGPltt(main)/
  GXS_LoadBGPltt(sub). func_02024e5c = "current language != default" test (was mislabeled LoadGlobalShort).

Menu (ov008) confirm -> scene id (from func_ov008_0204dc48, exec reads action code at ctx+0x9678):
- action 8 -> StoreGlobalPairAt10(2,0) = SCENE 2 = ov002 (GAMEPLAY), after loading a save-slot
  config (func_020315f4 slot -> CopyConfig16_02031600). = "enter game" (Story/Mission).
- action 7 -> StoreGlobalPairAt10(1,0) = SCENE 1 = ov000 (logo), with func_02003948(-2) + func_020352cc.
g_SceneTable @data_02042548 {overlayId,classDesc} (8-byte entries): 0=null, 1=ov000(logo),
2=ov002(game), 3=ov003, 4=null, 5=ov004, 6=ov005, 7=ov006(title), 0x13=ov008(menu).
Story vs Mission and difficulty are SUB-menu choices within ov008 (sub-scene func_ov008_0204ec34)
that set the CONFIG copied into scene 2/ov002 - not distinct scene ids.

Sound/BGM: NOT event-flags. func_020235bc/d0 -> func_02025668/020256b8 = global EVENT-FLAG
bitmask (data_0204be18+0x10); confirmed .word func_02025668 in dispatcher pool. SDAT play is
SND_PrepareSeq/StartPreparedSeq; only func_0201a360 (player-update loop) calls StartPreparedSeq
(when player+0x2f flag set). Scene code never calls SND_* directly -> BGM chosen by a higher-level
sound director keyed on game state, decoupled. Title "1000" call func_ov006_020551a4 = state
transition + BG scroll (scrollX/Y clamped +/-0x10), NOT sound.

## Menu (ov008) option -> scene: DEFINITIVE (2026-07-15)
ov008 is a SINGLE menu overlay that assembles a config; Story/Mission/New-Game/Load/difficulty
are NOT separate g_SceneTable scenes. Every external transition from ov008:
- func_ov008_0204dc48 (confirm exec, reads action code at sceneObj+0x9678 via func_02050e44):
  * code 8 -> StoreGlobalPairAt10(2,0) = SCENE 2 = ov002 (GAMEPLAY). Loads the selected save
    slot's config (func_020315f4 = DAT_020315fc) -> CopyConfig16_02031600. = enter game.
  * code 7 -> func_02003948(-2) = SOFT RESET (OSi_FinalizeReset, boot-mode -2 saved to persistent
    DAT_020039f4) then StoreGlobalPairAt10(1,0) = SCENE 1 = ov000. = full reboot / return to title.
- func_ov008_02081ec4 (sub-state): ctx+4==1 -> scene 0x13 (re-enter menu); ==2 -> scene 1 (ov000).
So: Story mode AND Mission mode both play in ov002 (scene 2); the mode + difficulty
(Principiante/Normal/Experto) + New-Game-vs-Load are FIELDS in the config struct copied into
ov002, chosen by internal ov008 selections & the sub-scene func_ov008_0204ec34 - not scene ids.
The gameplay overlay is ov002 for every mode. Menu option LABELS are localized strings drawn via
FUN_02031258 from UI/mlt/res.p2 (text-id bytes set per-field by func_ov008_0204cadc:
+0x110 len0x1c, +0x4c len0x44, +0x12c len0x44, +0x26 len0x20, +0x90 len0x10, ...).
The exact config-field-for-mode/difficulty + cursor-index->option mapping lives in the 3 large
ov008 handlers: func_ov008_02060e3c (1952B), 02074c40 (3460B), 02088410 (2032B).

## Title-menu sweep status + next targets (end of 2026-07-16 session)
~84 new byte-exact funcs this session across ov006/ov008 (+ ov009/ov025 dedup twins). The
logo(ov000)->title(ov006 sc7)->menu(ov008 sc0x13)->confirm->game(ov002 sc2) flow is fully mapped
and mostly byte-exact: scene ctors, per-frame states, page/scroll animation, cursor/highlight,
teardown, sorted lists, event-flags, cell (re)registration, popups. Remaining ov006/ov008 funcs
are increasingly codegen ties (see deferred-ties.md tie classes) or complex control flow.
Next-session options (in rough value order):
1. `dedupprop.py` first (always) — new matches keep unlocking twins.
2. Keep sweeping ov008 medium-with-calls (0x206x-0x208x mission-UI range has many left).
3. The ov002 GAMEPLAY ctor func_ov002_020679d4 (968B, scene 2 entry) + its ~40 subsystem inits —
   BUT ov002 funcs aren't created in Ghidra this session; create them first (Ghidra mutations were
   blocked by the endTransaction/timeout bug — a fresh bridge may fix it).
4. func_ov006_0205341c-class title TEXT loaders are matched; the per-language sub-resource indices
   are documented above (item 1).
Data still open for the port: exact SDAT sequence<->BGM mapping (item 3 — the scene event-flags
are NOT sound; SND_StartPreparedSeq is only called by func_0201a360; the seq-id table lives there).


## ov000 list-menu scene: one context object, three matched consumers

`Ov000ListSceneContext` (the object `NNSi_FndGetCurrentRootHeap()` returns inside the
ov000 list menu) is shared by functions that were decompiled independently and named
differently. Verified 2026-07-26 by matching offsets across their matched sources:

- `selection` at +0 (scroll position) and `cursor` at +2 (highlighted row);
- the two text panels at +0x94 (label) and +0xd0 (value);
- display objects at +0x10c, +0x158 and +0x4bd8 (the last one is the cursor object that
  `func_ov000_02058e88` builds);
- draw flags at +0x966c, the row table at +0x9670 (stride 0x18: label pointer, value
  pointer, 0x10 bytes of state), the title string at +0xd114.

Flow: `func_ov000_0205a19c` (matched, touch/input handler) calls `func_ov000_02059d78`,
which calls `func_ov000_02059b14` (the list redraw). Use `Ov000ListSceneContext` and the
field names above for anything else touching this object -- do not invent a rival type.
