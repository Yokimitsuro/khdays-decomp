/* func_ov008_020672d0 -- Ov008_RunPendingGridAction: perform the grid menu's
 * pending action (+0xa4) once the menu is idle (+0x30 == 0).  Action 2 saves
 * the panel layout into preset +0x20: the item ids of the 3 x 40 page slots
 * (+0x19c4, 0 for an empty slot) go to the preset's GameState table (0xc10 +
 * 0xf0 per preset), flag 0x3c67 + preset is set, mode 3 entered (02063790)
 * and sound 0x3b played.  Action 5 loads it: the grid is emptied, the preset
 * table copied over the equipped items (0xee0, 0xf0 bytes), the grid rebuilt
 * (02064fb8, 02062d00 0/0), mode 6 entered, the row block disabled, the equip
 * panel refreshed from the summary (+0x1f78) and sound 0x3c played.  Action 7
 * clears the grid: mode 8, the summary rebuilt from the slots and the tracked
 * node list, the equip panel refreshed, the row block disabled, sound 0x37.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GRID_PAGES   3
#define PAGE_SLOTS   40
#define PRESET_COUNT 3
#define ACTION_SAVE_PRESET  2
#define ACTION_LOAD_PRESET  5
#define ACTION_CLEAR_GRID   7
#define FLAG_PRESET_SAVED   0x3c67
#define MODE_SAVED    3
#define MODE_LOADED   6
#define MODE_CLEARED  8
#define SOUND_SAVED   0x3b
#define SOUND_LOADED  0x3c
#define SOUND_CLEARED 0x37

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    u8  pad_18[0x9c - 0x18];
} Ov008Message15Record;

typedef struct Ov008GridSummary {
    u8 pad[0x100];
} Ov008GridSummary;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x20];
    int nPreset;              /* 0x0020: selected preset page */
    u8  pad_0024[0x30 - 0x24];
    int nBusy;                /* 0x0030 */
    u8  pad_0034[0xa4 - 0x34];
    int nPendingAction;       /* 0x00a4 */
    u8  pad_00a8[0x19c4 - 0xa8];
    Ov008Message15Record *apPageSlot[GRID_PAGES][PAGE_SLOTS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e7c - 0x1ba4];
    u8  trackedNodeList[12];  /* 0x1e7c */
    u8  pad_1e88[0x1f78 - 0x1e88];
    Ov008GridSummary summary; /* 0x1f78 */
} Ov008MenuContext;

typedef struct GameState {
    u8  pad_0000[0xc10];
    u16 aPresetItems[PRESET_COUNT][GRID_PAGES][PAGE_SLOTS]; /* 0x0c10 */
    u16 equippedItems[GRID_PAGES][PAGE_SLOTS];              /* 0x0ee0 */
} GameState;

extern GameState *data_0204be18;
extern Ov008MenuContext *func_ov008_02050cd4(void);                      /* Ov008_GetMenuContext */
extern void func_020235a8(int nFlag);                                    /* GameState_SetFlag */
extern void func_ov008_02063790(Ov008MenuContext *pCtx, int nMode);      /* enter a grid menu mode */
extern void func_02033b78(int nKind, int nSound);                        /* PlaySound */
extern void func_ov008_02065420(Ov008MenuContext *pCtx);                 /* Ov008_ClearGridMenu */
extern void MIi_CpuCopy16(const void *pSrc, void *pDst, u32 nSize);
extern void func_ov008_02064fb8(Ov008MenuContext *pCtx);                 /* place the equipped items */
extern void func_ov008_02062d00(Ov008MenuContext *pCtx, int nA, int nB); /* rebuild the grid */
extern void func_ov008_0206ebd8(void);                                   /* Ov008_DisableRowBlock */
extern void func_ov008_0206ed7c(Ov008GridSummary *pSummary);             /* Ov008_RefreshEquipPanel */
extern void func_ov008_02053470(Ov008GridSummary *pSummary, void *pSlots, void *pList); /* RebuildViewAndCountCells */

void func_ov008_020672d0(void)
{
    Ov008MenuContext *pCtx;
    int nPage;
    int i;
    Ov008Message15Record *pRecord;

    pCtx = func_ov008_02050cd4();
    if (pCtx->nBusy != 0) {
        return;
    }
    switch (pCtx->nPendingAction) {
    case ACTION_SAVE_PRESET:
        for (nPage = 0; nPage < GRID_PAGES; nPage++) {
            for (i = 0; i < PAGE_SLOTS; i++) {
                pRecord = pCtx->apPageSlot[nPage][i];
                if (pRecord != 0) {
                    data_0204be18->aPresetItems[pCtx->nPreset][nPage][i] = pRecord->nItemId;
                } else {
                    data_0204be18->aPresetItems[pCtx->nPreset][nPage][i] = 0;
                }
            }
        }
        func_020235a8(pCtx->nPreset + FLAG_PRESET_SAVED);
        func_ov008_02063790(pCtx, MODE_SAVED);
        func_02033b78(0, SOUND_SAVED);
        break;
    case ACTION_LOAD_PRESET:
        func_ov008_02065420(pCtx);
        MIi_CpuCopy16(data_0204be18->aPresetItems[pCtx->nPreset], data_0204be18->equippedItems, sizeof(data_0204be18->equippedItems));
        func_ov008_02064fb8(pCtx);
        func_ov008_02062d00(pCtx, 0, 0);
        func_ov008_02063790(pCtx, MODE_LOADED);
        func_ov008_0206ebd8();
        func_ov008_0206ed7c(&pCtx->summary);
        func_02033b78(0, SOUND_LOADED);
        break;
    case ACTION_CLEAR_GRID:
        func_ov008_02065420(pCtx);
        func_ov008_02063790(pCtx, MODE_CLEARED);
        func_ov008_02053470(&pCtx->summary, pCtx->apPageSlot, pCtx->trackedNodeList);
        func_ov008_0206ed7c(&pCtx->summary);
        func_ov008_0206ebd8();
        func_02033b78(0, SOUND_CLEARED);
        break;
    }
}
