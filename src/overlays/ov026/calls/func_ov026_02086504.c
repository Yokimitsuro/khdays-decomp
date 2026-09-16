/* func_ov026_02086504 -- Ov008_RefreshFilterRows: move the filter-row
 * highlight and redraw the rows.  The highlighted row starts from the
 * selection (+0xc3b0) shifted by the two mode flags (+0xc5f4 clear: +1 up to
 * 3; else +0xc5f0 clear: +1 below 2, -1 otherwise); widget 1 of the widget
 * context (+0x2ab0) goes to y = 0x18 * row + 0x20 (fx32) at its block x, the
 * text region (+0xc160) is laid out (0x50, 0x18, 0x60, 0x70), and the rows
 * are drawn with Ov008_ShowFilterRow: all five with their own label when
 * +0xc5f4 is set; rows 1..4 with labels 0,1,2,4 when +0xc5f0 is set; rows
 * 1..3 with labels 0,1,3 otherwise -- lit when the label is the selection.
 * Finally the selection's description (var text record 7 + selection from
 * +0xc130) is drawn.
 *
 * Codegen: here the ROM colours the context LAST (sl), so the plain copy
 * (propagated into the global's load temp) is right; members at their real
 * offsets so mwcc splits 0x2ab0 / 0xc160 / 0xc360 itself; the rows pointer
 * is declared first and the selection is read through it (through the
 * context it shares the +0xc000 partial with the flags).
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define FILTER_ROWS 5
#define ROW_PITCH   0x18
#define ROW_TOP     0x20
#define TEXT_DESCRIPTION_BASE 7

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008FilterRows {
    u8    pad_00[0x14];
    int   aOffCell[FILTER_ROWS];  /* +0x14 (ctx 0xc374) */
    int   aOnCell[FILTER_ROWS];   /* +0x28 (ctx 0xc388) */
    void *aLabel[FILTER_ROWS];    /* +0x3c (ctx 0xc39c) */
    int   nSelected;              /* +0x50 (ctx 0xc3b0) */
} Ov008FilterRows;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x2ab0];
    u8  widgets[0xc130 - 0x2ab0];     /* 0x2ab0: widget context */
    u8  textLoader[0xc160 - 0xc130];  /* 0xc130: var text records */
    u8  detailSurface[0xc360 - 0xc160]; /* 0xc160 */
    Ov008FilterRows rows;             /* 0xc360 */
    u8  pad_c3b4[0xc5f0 - 0xc3b4];
    int bFourRows;                    /* 0xc5f0 */
    int bAllRows;                     /* 0xc5f4 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov026_02091368;
extern void *func_ov026_0208427c(void *pGroup, int nId);                /* FindEntryById */
extern UiLayoutPos *func_ov026_020842f8(void *pGroup, void *pWidget);   /* Ov008_GetEntryPos */
extern void func_ov026_02084330(void *pGroup, void *pWidget, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void func_0203011c(void *pRegion, int nX, int nY, int nW, int nH);
extern void func_ov026_02086438(int nRow, int nLabel, int bOn);         /* Ov008_ShowFilterRow */
extern u16 *func_ov026_02084d74(void *pCache, int nIndex);              /* GetVarRecordByIndex */
extern void func_ov026_02085e58(u16 *pText, int nArg);                  /* Ov008_DrawDescriptionText */

void func_ov026_02086504(void)
{
    Ov008PanelContext *ctx = data_ov026_02091368;
    Ov008FilterRows *pRows = &ctx->rows;
    int bAllRows = ctx->bAllRows;
    int bFourRows = ctx->bFourRows;
    int nRow = pRows->nSelected;
    u8 *pWidgets = ctx->widgets;
    u8 *pSurface = ctx->detailSurface;
    UiLayoutPos pos;
    int i;
    int nLabel;

    if (bAllRows == 0 && nRow < 3) {
        nRow++;
    } else if (bFourRows == 0) {
        if (nRow < 2) {
            nRow++;
        } else {
            nRow--;
        }
    }
    pos.nX = func_ov026_020842f8(pWidgets, func_ov026_0208427c(pWidgets, 1))->nX;
    pos.nY = (nRow * ROW_PITCH + ROW_TOP) << 12;
    func_ov026_02084330(pWidgets, func_ov026_0208427c(pWidgets, 1), &pos);
    func_0203011c(pSurface, 0x50, 0x18, 0x60, 0x70);
    if (bAllRows != 0) {
        for (i = 0; i < FILTER_ROWS; i++) {
            func_ov026_02086438(i, i, i == pRows->nSelected);
        }
    } else if (bFourRows != 0) {
        for (i = 1; i < FILTER_ROWS; i++) {
            nLabel = i <= 3 ? i - 1 : i;
            func_ov026_02086438(i, nLabel, nLabel == pRows->nSelected);
        }
    } else {
        for (i = 1; i < 4; i++) {
            nLabel = i <= 2 ? i - 1 : i + 1;
            func_ov026_02086438(i, nLabel, nLabel == pRows->nSelected);
        }
    }
    func_ov026_02085e58(func_ov026_02084d74(ctx->textLoader, pRows->nSelected + TEXT_DESCRIPTION_BASE), -1);
}
