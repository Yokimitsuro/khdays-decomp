# Symbol renames

Tables of `old_name<TAB>new_name<TAB>module` for every rename that changed a function or data symbol, so
code outside this repository that refers to functions by name can migrate mechanically.

| File | What changed |
|---|---|
| `2026-09-27-sdk-and-veneers.tsv` | NitroSDK/NitroSystem identifications and the undoing of shape-matched names (`WM_EndKeySharing_0x*`, `SNDi_UnlockMutex_0x*`, ...). Some old names are reused as new names for other addresses (for example `SNDi_UnlockMutex`, `FX_Inv`, `OS_UnlockByWord`), so apply the table in one pass, never line by line. |
| `2026-09-28-function-names.tsv` | 22036 `func_<addr>` symbols given the names they carry in the Ghidra project. Functions whose name could not be verified keep `func_<addr>`. |
| `2026-09-29-header-placeholders.tsv` | The 56 `func_<addr>` placeholders left in the shared prototype headers (`include/game/engine.h`, `include/game/enemy_common.h`), named from their callers and the globals they touch (`Sleep_Block`, `GetFrameRateMode`, `SoundMgr_SwitchBgm`, ...). |
| `2026-09-30-data-names.tsv` | The first data and BSS symbols given names (`gSceneTable`, `gObjSystem`, `gPadHeld`, `gEntityMgr`, ...): globals whose meaning the code already shows. Data keeps `data_<addr>` until what it holds is known. |
| `2026-09-30-class-descriptors.tsv` | The class descriptors whose owner is known: the boot task (`gBootTaskClass`), the root class of each identified scene in the scene table (`gOv000TitleSceneClass`, `gOv002FieldSceneClass`, ...) and each player overlay's character class (`gOv030RoxasClass`, `gOv049RoxasDualClass`, ...). |
| `2026-09-30-pack-path-formats.tsv` | Each enemy overlay's copy of `"Ms/%02x.p"`, the format its factory fills with an enemy class id to open that enemy's resource pack (`gOv114PackPathFmt`, ...; `_2` for the copy the `_2` factory uses). |
| `2026-09-30-string-names.tsv` | 2240 strings named after what they hold: file paths (`gOv034XaldinDefHPackPath` for `"ba/ch/xa/def_h.p.z"`, the `ba/ch/<code>/` folder read as its character), names looked up in models and animations (`gOv221BoneHeadName`), formats (`gOv002IntFmt`) and sentences (`...Text`). Copies of one string in a module are numbered; strings that are not readable ASCII keep `data_<addr>`. |
| `2026-10-05-findings-names.tsv` | Names that said something else, from tracing the running game: NitroSystem G3D's draw (`NNS_G3dDraw`, `NNSi_G3dDrawInternal`, `NNS_G3dRS`, `NNS_G3dGetResultMtx`, `NNS_G3dGlbFlush`/`NNS_G3dGlb`) and its SBC command handlers and table (`NNSi_G3dFuncSbc_NOP`..`_POSSCALE`, `NNS_G3dFuncSbcTable`; `NNSi_G3dSbcCmdSetPolygonAttr` was MTX), `OS_SetTick` (was `SetupTimer0Reload`), the backup lock pair (`CARD_UnlockBackup` locked: it is `CARD_LockBackup`, and `CardUnlockAfterKeyShare` is `CARD_UnlockBackup`), the four `Backup_ReadChunked` (they read), the frame texture VRAM manager (`gGfdFrmTexRegions`, `NNSi_GfdSetTexNrmSearchArray`, `NNS_GfdAllocFrmTexVram`) and ov022's item hook `Ov022_OnItemGiven`. A swap: apply it in one pass. |
| `2026-10-05-fx-atan2.tsv` | A swap: the function called `FX_Atan2` (0x0200526c, a 1/65536-turn angle) is NitroSDK's `FX_Atan2Idx`, and `func_020050b4` (radians, `fx16`) is `FX_Atan2`. Its callers now declare it returning `fx16` as defined. |
| `2026-10-05-texmtx-calculators.tsv` | A swap: Maya's texture-matrix calculators for slots 1 and 5 (`texmtxCalc_flagS_`, `texmtxCalc_flagTS_`, were `NNSi_G3dCalcTexMtxRot` and `G3d_ComputeFrustumPlanes`) take the plain names as their maya.c neighbours do; 3ds Max's two that held them become `..._2`. |
| `2026-09-30-runtime-map.tsv` | From what the running game shows: the Config page's loaders (`Ov008_Config_LoadValues`/`SaveValues`, were `LoadItemCounts`/`SaveItemCounts`), the L shortcuts (`Ov002_SelectShortcut`), the D-pad heading and the key-repeat bits. |
| `2026-09-30-field-controls.tsv` | Names the field's controls and traces say otherwise: the command deck's cursor movers (`Ov002_PanelCursorNext`/`Prev`/`StepRight`), the camera's `Ov002_Camera_LeaveLookView`, the lock-on `Ov022_TryLockOn`, the animation step's `Ov022_SetAnimSpeed`/`Ov022_StepScaledAnimTracks`, and the entity manager's casts with ready-made parameters. |
| `2026-09-29-sdk-names.tsv` | NitroSDK functions identified by their body (`func_02003948` is `OS_ResetSystem`). |
| `2026-09-29-misleading-names.tsv` | Names that described something else (`StreamReader_InitU16` is `NNS_G2dFontInitUTF16`, `Session_GetSlotTable` is `Session_GetSetup`, `Callbacks_SetByte` is `PauseMenu_SetMode`, ...). |

Addresses never change, so a name can always be recovered from `config/arm9/**/symbols.txt`.

The build reads these tables too: `tools/gen_delinks.py` uses them to carry a committed DATA
claim (a function's local `.rodata`) over to its source's new file name. Add a table for every
future rename of function symbols, and keep the old ones.
