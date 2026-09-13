/* func_ov025_020958c0 -- Ov008_SetupPresetPanel: display setup for the three
 * preset rows and the page indicator of the grid menu.  Each preset surface
 * (+0x160, 0x3c apart) is built on layer hLayer at x = 8 + 3 * i, bound to the
 * row's target (+0x29c, 0x10 apart), and gets its var record (+0x28c, index
 * 0x10 + i) drawn twice (0x39 / 0x38, colour 0xf3 when the preset is
 * unlocked -- flag 0x3c67 + i, or always with bAll -- else 0xf5).  With bAll
 * entries 0x59..0x5b and 0x57 are enabled and entry 0x59 re-linked, selecting
 * page target 2; otherwise entries 0x5d..0x5f are shown with their subitem set
 * pushed from flag 0x3c0a + id, entry 0x58 enabled and entry 0x5d + preset
 * (+0x20) re-linked, selecting page target 0.  The page surface (+0x214) is
 * built at x = 4 and bound to that target (+0x2c8).
 * Codegen: the surface pointer and x are indexed from i at every use (mwcc
 * strength-reduces them into r7 / r6 itself; explicit walking locals colour
 * the other way round).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define PRESET_COUNT      3
#define FLAG_PRESET_BASE  0x3c67
#define FLAG_ENTRY_BASE   0x3c0a
#define COLOUR_UNLOCKED   0xf3
#define COLOUR_LOCKED     0xf5
#define TEXT_FLAGS        0x412

typedef struct TileSurface {
    u8 pad_00[0x3c];
} TileSurface;

typedef struct Ov008PresetRow {
    int hTarget;              /* 0x00 */
    u8  pad_04[0xc];
} Ov008PresetRow;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x20];
    int nPreset;              /* 0x020 */
    u8  pad_0024[0x160 - 0x24];
    TileSurface aPresetSurface[PRESET_COUNT]; /* 0x160 */
    TileSurface pageSurface;  /* 0x214 */
    u8  pad_0250[0x28c - 0x250];
    u8  varRecords[0x10];     /* 0x28c */
    Ov008PresetRow aPresetRow[PRESET_COUNT]; /* 0x29c */
    u8  pad_02cc[0x2c8 - 0x2cc + 4];
} Ov008MenuContext;

extern const u8 data_ov008_020635c4[];
extern void  func_0203034c(TileSurface *pSurface, int hLayer, int nX, int nY, int nPalette); /* Draw_ScaledValue */
extern void  func_02030094(TileSurface *pSurface, int nTarget, int nUpdate);          /* TileSurface_SetCurrentItem */
extern int   func_02023588(int nFlag);                                                 /* GameState_IsFlagSet */
extern void *func_ov025_02089894(void *pRecords, int nIndex);                          /* GetVarRecordByIndex */
extern void  func_02030158(TileSurface *pSurface);                                     /* Obj_InvokeInnerVtable4 */
extern void  func_020301c8(TileSurface *pSurface, int nX, int nY, int nColour, u32 nFlags, void *pRecord); /* Text_DrawDirectional */
extern void  func_020300f8(TileSurface *pSurface);                                     /* EnqueueObjGfxCommand */
extern void  func_ov025_0208ff84(void *pMenu, int nId, int bEnable);                   /* Ov008_ResolveEntryAndConfigure */
extern void *func_ov025_0208843c(void *pMenu, int nId);                                /* FindEntryById */
extern void  func_ov025_0208896c(void *pMenu, void *pEntry);                           /* Ov008_SwapParamOverrides */
extern void  func_ov025_0208f144(void *pEntry);                                        /* Ov008_SetTag3RowPos */
extern void  func_ov025_0208884c(void *pMenu, void *pEntry, int bVisible);             /* SetEntrySlotsVisible */
extern void  func_ov025_020887c0(void *pMenu, void *pEntry, int nValue);               /* Ov008_PushSubitemSet */

void func_ov025_020958c0(Ov008MenuContext *pCtx, void *pMenu, int hLayer, int bAll)
{
    int i;
    int bUnlocked;
    void *pRecord;
    int nColour;
    void *pEntry;
    int nTarget;

    for (i = 0; i < PRESET_COUNT; i++) {
        func_0203034c(&pCtx->aPresetSurface[i], hLayer, 8 + i * 3, 0xf, 0);
        func_02030094(&pCtx->aPresetSurface[i], pCtx->aPresetRow[i].hTarget, 1);
        if (bAll != 0) {
            bUnlocked = 1;
        } else {
            bUnlocked = func_02023588(FLAG_PRESET_BASE + i);
        }
        pRecord = func_ov025_02089894(pCtx->varRecords, i + 0x10);
        if (bUnlocked != 0) {
            nColour = COLOUR_UNLOCKED;
        } else {
            nColour = COLOUR_LOCKED;
        }
        func_02030158(&pCtx->aPresetSurface[i]);
        func_020301c8(&pCtx->aPresetSurface[i], 0x39, 7, nColour - 1, TEXT_FLAGS, pRecord);
        func_020301c8(&pCtx->aPresetSurface[i], 0x38, 6, nColour, TEXT_FLAGS, pRecord);
        func_020300f8(&pCtx->aPresetSurface[i]);
    }
    if (bAll != 0) {
        for (i = 0x59; i <= 0x5b; i++) {
            func_ov025_0208ff84(pMenu, i, 1);
        }
        func_ov025_0208ff84(pMenu, 0x57, 1);
        nTarget = 2;
        func_ov025_0208896c(pMenu, func_ov025_0208843c(pMenu, 0x59));
        func_ov025_0208f144(func_ov025_0208843c(pMenu, 0x59));
    } else {
        for (i = 0x5d; i <= 0x5f; i++) {
            pEntry = func_ov025_0208843c(pMenu, i);
            func_ov025_0208884c(pMenu, pEntry, 1);
            func_ov025_020887c0(pMenu, pEntry, func_02023588(FLAG_ENTRY_BASE + i) == 0);
        }
        func_ov025_0208ff84(pMenu, 0x58, 1);
        nTarget = 0;
        func_ov025_0208896c(pMenu, func_ov025_0208843c(pMenu, pCtx->nPreset + 0x5d));
        func_ov025_0208f144(func_ov025_0208843c(pMenu, pCtx->nPreset + 0x5d));
    }
    func_0203034c(&pCtx->pageSurface, hLayer, 4, 0xf, 0);
    func_02030094(&pCtx->pageSurface, *(int *)((u8 *)pCtx + 0x2c8 + nTarget * 4) /* page targets: the screen's target table is laid out per screen */, 1);
}
