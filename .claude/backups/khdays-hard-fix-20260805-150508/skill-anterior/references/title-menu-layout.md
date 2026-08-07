# ⚠ CORRECTION 2026-07-16: ov006 is the CHARACTER SELECT, not the title

**Verified at runtime** (savestate on the character-select screen): `curId = 7` → ov06. The title
is **ov000**, `curId = 1`. This supersedes everything below that gives ov006 a "title" role; the
rest of the technical content (resource ids, struct offsets, the P2 handle construction) still
stands.

**ov000 hosts the title, every menu level AND the "Load" screen** — the KH logo stays on top
throughout. That is why the title and the menu looked like one thing in the original brief.
It also answers P5: the 3D title model is drawn by **ov000** (`/ttl/ttl.p2` and `ttl/ttl_&.p2`
live there; ov006 never touches them).

### Corrections to `func_ov006_0205454c`, values read from RAM

| symbol | actual value | previously (wrong) |
|---|---|---|
| `data_ov006_02056540` | `"/text/font_eu_10all.NFTR"` | "title graphic (BG3)" |
| `data_ov006_0205655c` | `"/text/font_eu_10all.NFTR"` | "title graphic (BG7)" |
| `data_ov006_02056578` | `"UI/mlt/res.p2"` | "message container" |
| `data_ov006_02056588` | `"UI/mlt/res_&.p2"` (localised) | "message container" |

Both font entries are **the same file**, loaded into BG3 and BG7. The two `.p2` files are the
**char-select UI pack**, not message containers. The 0x97f8 heap figure was right — it is the
char-select manager context.

Every resource ov006 loads is `UI/mlt/*` (`mlt` = multi; Mission Mode is the multiplayer) plus
that font. No logo, no title art.

**How this happened:** the original brief said "título ov06" and it was taken as given and never
verified — "title screen scene constructor" was written into a matched function on that basis
alone. All 23 `Ov006_Title*` symbols are now `Ov006_Mission*` and all 61 ov006 source comments
are corrected. **Check an overlay's resource strings (or the runtime scene id) before naming
anything after a screen.**

---

# Title (ov006) + character/mission menu (ov008) — resource & layout map

Investigation 2026-07-16 for the PC port (exact button/slot positions). All addresses
verified read-only in Ghidra (`days.nds`). Mutation channel was in terminated-tx state,
so the semantic Ghidra renames are queued in `pending-ghidra-renames.md`.

## Archive_LoadFile (0x0201ef9c) — the file-vs-handle dispatch (foundational)

`Archive_LoadFile(ref, heapId=0xe, heap, tail)` branches on **bit 31 of `ref`**:
- `(ref & 0x80000000) == 0` → `ref` is a **string path**. `Msg_BuildLangPath(ref)` performs
  the `&` → language-code substitution (EU: e/f/g/i/s…); a trailing extension letter that maps
  to `'Z'` (0x5a) flags the file LZ-compressed.
- bit31 set → `ref` is a **packed subfile handle** → `Archive_OpenSubfileByHandle`.

`FUN_02050f08(id)` builds such a handle: `((*(*(ctx+4)+0x96b0)+0x8000) & 0x00fffffc) << 7 |
0x80000000 | (id & 0x1ff)` — i.e. *(mounted archive bank)* + *subfile `id`*.
Mask `DAT 0x02050f3c = 0x00fffffc`; ctx global `DAT 0x02050f38 = 0x02090f04`.

## P1 — Title (ov006) files. Ctor `func_ov006_0205454c`.

Loads (all **string paths**, inline descriptors in the ov006 string pool):

| resource sym            | path                       | dest / role |
|-------------------------|----------------------------|-------------|
| `data_ov006_02056540`   | `/text/font_eu_10all.NFTR` | → base+0x9760, painted as **BG3 (main)** |
| `data_ov006_0205655c`   | `/text/font_eu_10all.NFTR` | → base+0x97ac, painted as **BG7 (sub)** |
| `data_ov006_02056578`   | `UI/mlt/res.p2`            | MLT/text container → base[0] (`Msg_OpenContainerAndReadHeader`) |
| `data_ov006_02056588`   | `UI/mlt/res_&.p2`         | language-variant MLT → base[4] |
| `data_ov006_020565a4`   | `UI/mlt/mltgp.BGU`        | BG graphics unit (string pool, adjacent) |

**"MODO HISTORIA / MODO MISIÓN" are NOT baked bitmaps.** `func_ov006_02053b24` renders
them as **text onto BG3/BG7** using the NFTR font: it fills a rect `{x=0,y=0,w=0x20,h=0x18}`
(full 256×192) via `func_0202f834(handle, layer, fontRes, rect)`; `rect[5]` is the palette /
highlight index (0xf = highlighted, 0 = normal) selected by the menu-state switch. The
string content comes from the `res.p2` MLT/message container. Port path: render font glyphs
of the mode strings onto the BG layer at the layout position (see `func_0202f834` for the
tile/alloc math; `rect` = `{x,y,w,h,screenBase,palette,[6],[7]=6}`).

## P2/P3 — ov008 menu (12-slot character/mission select). It is DATA-DRIVEN from a file.

Cursor object layout (the obj passed to the cursor family):
- `+0x18/1c/20`  live cursor world pos (x,y,z, Q-format)
- `+0x24/28/2c`  shadow pos = cursor + {0, 0x1000, 0x28000}
- `+0x70`        **slot table: 12 × 0x40 B; first 0xc B of each = target (x,y,z)**
- `+0x424/428/42c` projected screen coords (`FX_Inv(shadowX/Y, 0x14cd)`, shadowZ-0x64000)
- `+0x11f0`      previous active slot (-1 = none)
- `+0x11f4/1210/122c` the 3 axis interpolators (tween state)

Cursor family (all MATCHED byte-exact 2026-07-16):
- `func_ov008_0205bea0` MoveToSlot(obj, slot, dur): clamp slot 0..11; if prev<0 snap
  (`MI_CpuCopy8` slot→cursor) else tween; record prev.
- `func_ov008_0205bcb4` TweenToSlot: 3× `func_02035fb0(mode2)` cursor→slot over dur.
- `func_ov008_0205bbf0` UpdateShadowProj / `func_ov008_0205bc68` TweenStep.
- Instant/speed thunks `0205c564`(dur0) `0205c54c`(dur = fast?500:1000) — NOT in func_index
  (jump-table veneers), left unmatched.

**Who fills the 12 slot rects (P2):** NOT a flat static table. The layout loader
`FUN_02055534(obj, ref, heap, tail)` (rename queued `Ov008_LoadLayoutResource`):
1. `res = Archive_LoadFile(ref, 0xe, …)` — `ref` for the char/mission menu is the **packed
   handle `FUN_02050f08(0x13)` → subfile #0x13** of the mounted menu archive.
2. header = 3 section offsets `res[0],res[1],res[2]`.
3. `func_ov008_02054e94(obj, res+res[0])`  — section 0
4. `func_ov008_02054ed4(obj, res+res[1])`  — section 1
5. `Ov008_Set_4f3c(obj, res+res[2])`        — **section 2 = the tag/layout table** (P3 source)

`Ov008_Set_4f3c` (0x02054f3c) walks `{u32 count; record[count]}`, each record
`{u32 size; u32 p5; u32 p6; u16 tagCount@+0xc; u16 @+0xe; u16 tags[]@+0x10}`, calling
`BuildTagTrackerNode(obj, tagCount, &tags, u16, p5, p6, 0)`.

`BuildTagTrackerNode` = `func_ov008_0205563c`: allocates a 0x30-B node, stores a
**Q-format position scaled by `0x82ea`** (`DAT 0x02055704`) from p6 (lo) / p7 (hi):
`node[3] = (0x82ea*p6)>>6 | hi<<26; node[4] = hi>>6` where `hi = p7*0x82ea + (0x82ea*p6>>32)`;
resolves each tag via `ov008_FindEntryByTag` (`func_ov008_02055808`). Slot screen rects are
then produced by the world→screen projection (`020c5bc4`, P3).

**Port recommendation (P2/P3):** rather than statically reproduce the 3D projection, extract
menu-archive **subfile #0x13**, parse its 3-section header, and read section-2 records (the
`{size,p5,p6,tagCount,tags[]}` layout table) directly; OR hook `obj+0x70` after menu init and
dump the 12 × 0xc-B rects. The scale constant is `0x82ea`, the projection reciprocal base `0x14cd`.

## P4 — initial slot / menu controller

`FUN_0205b230` (char/mission menu FSM, state at `param_1[0]`): on state 0 it loads the layout
(`FUN_02055534` with subfile 0x13), then `DispatchToHandler2_020235d0(0,9)` picks the initial
slot index (4, or 0 if `>= DAT_0205b394`), and `func_ov008_0205c564(obj+1, slot)` snaps the
cursor there. `param_1[0x538] = (mode==2)` records story-vs-mission (`func_ov008_02050fc8`).
Item→slot mapping / page-swap (`0204fa00/0204fa60/0204f7b8`) — not yet traced.

## P6 (partial) — cursor → action 7/8 mapping [FOUND 2026-07-16]

`func_ov008_0205b720` (ov008, in `nonmatching/` — redundant-`orr` tie, semantics verified) is the
cursor→action encoder:

```c
int obj = func_ov008_02050cd4();
if (func_ov008_02051028() == 0) return;          /* only while a page transition is active */
cmd = (slot << 8) | (obj->f14e0 == 0 ? 7 : 8);   /* <-- the 7/8 the brief asked about */
func_ov008_020566f4(obj + 0x13fc, cmd);          /* scroll widget at obj+0x13fc */
func_ov008_0205a8c4(obj);                        /* refresh */
```

So **action 7 = normal pick, action 8 = the alternate mode**, selected by the flag at `obj+0x14e0`;
the slot index is packed into the high byte (`slot << 8`). The sibling `func_ov008_0205b770`
(MATCHED) is the same path without the 7/8 encode — it forwards the raw input to the same widget
(`obj+0x13fc`, `func_ov008_020566f4`). `func_ov008_020566f4` takes only 2 real args (r2/r3 are
leftovers — phantom args in the Ghidra decompile).

Still open for P6: the 20-word config `data_ov008_0208f328`, and the difficulty mapping in the big
handlers (`func_ov008_02060e3c` / `02074c40` / `02088410`).

## P6 — the 20-word config `data_ov008_0208f328` [RESOLVED 2026-07-16]

**The data** (20 × u32, index → value):

```
idx : 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19
val : 10 0  16 11 14 12 1  4  5  6  7  9  13 15 17 18 8  2  3  10
```
Values span 0..18 (10 appears at both idx 0 and idx 19) — it is a **remap / display-order table**,
not a set of tunables.

**The only reader** is `func_ov008_0205c580(out_remapped, out_raw)` (ALREADY MATCHED, in `calls/`):
1. copies the 20 words onto the stack (the `ldm/stm` struct-copy crack),
2. `id = func_02030788()` → `entry = func_020315c0(id)` (current player's save accessor),
3. if found: `*out_remapped = table[entry->f4]`, `*out_raw = entry->f4`.
Both out-params are optional (NULL-checked), so callers pick which they want.

**Consumers** (3): `func_ov008_0205eb6c`, `func_ov008_020659c0`, and the big
`func_ov008_02060e3c` — the handler named in the brief.

**How `02060e3c` (mission-briefing stat panel) uses it:**
- calls `func_ov008_0205c580(NULL, &raw)` — it wants **only the raw `entry->f4` index**, not the
  remapped value.
- feeds it to `func_02035730(raw, value, &out)` twice (for `param_1+0x1ff0` and `iStack_380`) —
  i.e. `raw` selects a **per-character scaling row**; this is the "difficulty"-ish lookup.
- **`f4 == 0` and `f4 == 0x13` (19) are sentinels**: when the index is either, the handler
  substitutes `0` or `0x13` based on the flags at `param_1+0x1fa4` / `iStack_3cc`
  (`iVar5 = (param_1->f1fa4 == 0) ? 0 : 0x13`). 0x13 = 19 = the table's last index.
- it then pushes stat deltas to numbered rows via
  `func_ov008_0206ec2c(rowId, delta, value, base)` for **rowIds 2, 3, 5, 6, 7, 9, 0xb, 0xc, 0xd**,
  and calls `Ov008_DisableRowBlock` (`func_ov008_0206ebd8`, MATCHED) to blank rows 0xc9..0xdc.

**Caveat / still open:** `func_02035730` itself is not yet decompiled, so the precise meaning of
the scaling it returns is inferred from the call shape, not proven. The other two big handlers
(`02074c40`, `02088410`) are not yet traced.

## The ov008 three-page scroll subsystem (2026-07-25, from the disassembly)

Named and typed in Ghidra while working `func_ov008_02068e68`. Useful before touching
anything in the ov008 page/menu area.

- **`Ov008_TickPageScrollState`** (`arm9_ov008::02068ba8`) -- per-frame state machine.
  Jump table on `pCtx->nActiveState` with **six** entries (0..5). States 1, 2 and the
  default fall through to the common tail; 0, 3, 4 and 5 each run their own block.
  Whatever the state, the tail always runs `Ov008_TickPageScroll(pCtx)` and then
  `func_ov008_02069180(pCtx)`, so the animation advances every frame and the state only
  chooses what happens before it. **Nothing in the ROM holds a relocation to this
  address** -- it is reached through a class descriptor, so its context is an instance
  from the object framework, not a global, and there is no pool slot to type.
- **`Ov008_TickPageScroll`** (`arm9_ov008::02068e68`) -- the animation step itself; its
  own inner switch handles only states 0, 1 and 4. Byte-identical modulo relocations to
  `func_ov025_0209b248`.
- **`Ov008PageScrollCtx`** (480 B, Ghidra type): `nPageIndex` +0x000,
  `nActiveState` +0x004, `aCellOffset[24]` +0x068 (stride page*64 + cell*8),
  `aPageTarget[3]` +0x128 and `aPageCurrent[3]` +0x140 -- **adjacent, no padding** --
  and a block at +0x1DC handed to `func_020300f8`. The cell-id table for page i is
  `data_ov008_0208de8c[i][0..7]`, stride 32 bytes.
- Positions everywhere in this subsystem are **`UiLayoutPos`** { int x; int y; } in
  1/4096 units. Entry access is `FindEntryById(root, tag)` -> `Ov008_GetEntryPos` /
  `Ov008_SetEntryPos`, which forward to the shared `Slot_GetPositionPtr` /
  `Slot_SetPosition`. See `naming-hubs.md` -- two of those ov008 names were WRONG until
  2026-07-25 and are now corrected.
- The value that looks like an opaque handle at the top of many ov008 functions is
  `Ov008_GetContext()` (the scene root, `data_ov008_02090f04[1]`) plus 0x9500.
