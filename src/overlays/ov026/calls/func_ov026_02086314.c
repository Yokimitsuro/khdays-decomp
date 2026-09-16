/* func_ov026_02086314 -- Ov008_InitFilterRows: build the five filter rows of the
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
typedef unsigned char u8;

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

extern int  func_ov026_02085d7c(int hSlots, int nKind, int nLabel, int nX, int nY); /* create a cell */
extern void *func_ov026_02084d74(void *pCache, int nIndex);             /* GetVarRecordByIndex */
extern int  func_ov026_02083530(void *pTracker, int nTag);              /* ov008_FindEntryByTag */
extern void func_ov026_020835c4(void *pTracker, int nCell);             /* Ov008_TagTracker_InvokeCallback */
extern void *func_ov026_0208427c(void *pGroup, int nId);                /* FindEntryById */
extern void *func_ov026_02084374(void *pGroup, void *pWidget);          /* Ov008_GetEntryBlock2c */
extern void func_ov026_02084330(void *pGroup, void *pWidget, void *pPos); /* Ov008_SetEntryPos */
extern void func_ov026_020843e8(void *pGroup, void *pWidget, int bVisible); /* SetEntrySlotsVisible */
extern void func_ov026_02086504(void);                                  /* refresh the row highlight */
extern void func_ov026_0208e35c(void);                                  /* Ov008_MergePendingUnlockBits */

void func_ov026_02086314(void)
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
        pRows->aOffCell[i] = func_ov026_02085d7c(hSlots, 2, 0, nX, nY);
        pRows->aOnCell[i] = func_ov026_02085d7c(hSlots, 1, 0, nX + ON_CELL_DX, nY);
        pRows->aLabel[i] = func_ov026_02084d74(ctx->textLoader, i);
    }
    func_ov026_020835c4(ctx->trackerB, func_ov026_02083530(ctx->trackerB, TAG_FILTER_FRAME));
    pWidget = func_ov026_0208427c(pWidgets, WIDGET_FILTER_CURSOR);
    func_ov026_02084330(pWidgets, pWidget, func_ov026_02084374(pWidgets, pWidget));
    func_ov026_020843e8(pWidgets, pWidget, 1);
    pRows->nSelected = 0;
    func_ov026_02086504();
    func_ov026_0208e35c();
}
