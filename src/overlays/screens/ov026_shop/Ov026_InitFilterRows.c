/* Ov026_InitFilterRows -- Ov008_InitFilterRows: build the five filter rows of the
 * panel: for each row rect of the 0208fedc table (x, y, w, h bytes) an "off"
 * cell (kind 2) at the rect centre and an "on" cell (kind 1) 8 px right of it
 * are created on the slot handle, and the row's label text is fetched from the
 * var text records (+0xc130); then the secondary tracker's (+0x5c) cell tagged
 * 0x3e9 is run, widget 1 of the widget context (+0x2ab0) is snapped to its
 * block position and shown, the selected row cleared, the row highlight
 * refreshed and the pending unlock bits merged.
 *
 * Codegen: `Ov008PanelContext *const ctx` keeps the context a declared
 * variable (a plain copy is propagated into the global's load temp and
 * coloured last); members at their real offsets so mwcc splits 0x2ab0 /
 * 0xc360 itself; the rows pointer is assigned first; the text-record base is
 * NOT a variable -- written as ctx->textLoader in the loop it becomes the
 * loop-invariant temp r4 = ctx+0x130 the ROM has, and only then does the
 * rows completion add schedule before the widget-context add.
 */

#include "nitro/types.h"

#define FILTER_ROWS 5
#define TAG_FILTER_FRAME 0x3e9
#define WIDGET_FILTER_CURSOR 1
#define ON_CELL_DX 0x8000

typedef struct Ov008RowRect {
    u8 x, y, w, h;
} Ov008RowRect;

typedef struct Ov008FilterRows {
    u8    pad_00[0x14];
    int   aOffCell[FILTER_ROWS];  /* +0x14 (ctx 0xc374) */
    int   aOnCell[FILTER_ROWS];   /* +0x28 (ctx 0xc388) */
    void *aLabel[FILTER_ROWS];    /* +0x3c (ctx 0xc39c) */
    int   nSelected;              /* +0x50 (ctx 0xc3b0) */
} Ov008FilterRows;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x5c];
    u8  trackerB[0x2ab0 - 0x5c];      /* 0x005c: secondary tag tracker */
    u8  widgets[0xbfb0 - 0x2ab0];     /* 0x2ab0: widget context */
    int hSlots;                       /* 0xbfb0 */
    u8  pad_bfb4[0xc130 - 0xbfb4];
    u8  textLoader[0xc360 - 0xc130];  /* 0xc130: var text records */
    Ov008FilterRows rows;             /* 0xc360 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov026_02091368;
extern const Ov008RowRect data_ov026_02091134[];

extern int Ov026_CreateMissionCell(int *mgr, unsigned int res, int slot, int xform, ...); /* create a cell */
extern void *Ov026_GetVarRecordByIndex(void *pCache, int nIndex);             /* GetVarRecordByIndex */
extern int  Ov026_FindEntryByTag(void *pTracker, int nTag);              /* ov008_FindEntryByTag */
extern void Ov026_TagTracker_InvokeCallback(void *pTracker, int nCell);             /* Ov008_TagTracker_InvokeCallback */
extern void *Ov026_FindEntryById(void *pGroup, int nId);                /* FindEntryById */
extern void *Ov026_GetEntryBlock2c(void *pGroup, void *pWidget);          /* Ov008_GetEntryBlock2c */
extern void Ov026_ReleaseTwoSlotsEx(void *pGroup, void *pWidget, void *pPos); /* Ov008_SetEntryPos */
extern void Ov026_SetEntrySlotsVisible(void *pGroup, void *pWidget, int bVisible); /* SetEntrySlotsVisible */
extern void Ov026_RefreshFilterRows(void);                                  /* refresh the row highlight */
extern void Ov026_MergePendingUnlockBits(void);                                  /* Ov008_MergePendingUnlockBits */

void Ov026_InitFilterRows(void)
{
    Ov008PanelContext *const ctx = data_ov026_02091368;
    Ov008FilterRows *pRows;
    int hSlots;
    u8 *pWidgets;
    int i;
    int nX;
    int nY;
    void *pWidget;

    pRows = &ctx->rows;
    hSlots = ctx->hSlots;
    pWidgets = ctx->widgets;
    for (i = 0; i < FILTER_ROWS; i++) {
        nX = (data_ov026_02091134[i].x + (data_ov026_02091134[i].w >> 1)) << 12;
        nY = (data_ov026_02091134[i].y + (data_ov026_02091134[i].h >> 1)) << 12;
        pRows->aOffCell[i] = Ov026_CreateMissionCell((int *)hSlots, 2, 0, nX, nY);
        pRows->aOnCell[i] = Ov026_CreateMissionCell((int *)hSlots, 1, 0, nX + ON_CELL_DX, nY);
        pRows->aLabel[i] = Ov026_GetVarRecordByIndex(ctx->textLoader, i);
    }
    Ov026_TagTracker_InvokeCallback(ctx->trackerB, Ov026_FindEntryByTag(ctx->trackerB, TAG_FILTER_FRAME));
    pWidget = Ov026_FindEntryById(pWidgets, WIDGET_FILTER_CURSOR);
    Ov026_ReleaseTwoSlotsEx(pWidgets, pWidget, Ov026_GetEntryBlock2c(pWidgets, pWidget));
    Ov026_SetEntrySlotsVisible(pWidgets, pWidget, 1);
    pRows->nSelected = 0;
    Ov026_RefreshFilterRows();
    Ov026_MergePendingUnlockBits();
}
