/* func_ov026_02089658 -- Ov008_HideDetailOverlay: take the detail overlay
 * down on the shared panel context: re-lays out the dialog surface region
 * (+0xc160: 0x28, 0x38, 0xb0 x 0x40), unlinks the sell dialog's (+0xc4c8) two
 * cells (+0x4 / +0x8) from the slot handle, hides widget 6 of the widget
 * context (+0x2ab0) and widgets 6 and 5 of the widget manager (+0x7530),
 * clears the column panel pair that belongs to the current tab (+0xc250: tab 0
 * clears the right selection and base, any other the left pair), then unlinks
 * the four choice cells (+0xc5e0).  The first two unlinks re-read the slot
 * handle from the context; the last four use the local.
 *
 * Codegen: `Ov008PanelContext *const ctx` keeps the context a declared
 * variable (a plain copy is propagated into the global's load temp and
 * coloured last), declared after hSlots; members at their real offsets so
 * mwcc splits 0x2ab0 / 0x7530 / 0xc4c8 itself; the dialog pointer is assigned
 * before the two widget bases and the first call's 0x40 then reuses the
 * widget-context register (240/2880 orders match).
 */
typedef unsigned char u8;

#define WIDGET_OVERLAY_A 6
#define WIDGET_OVERLAY_B 5
#define TAB_SPECIAL      0

typedef struct Ov008ColumnPanel {
    int aCell[6][8];          /* 0x00 (0xc254) */
    int nLeftSelected;        /* 0xc0 (0xc314) */
    int nRightSelected;       /* 0xc4 (0xc318) */
    int nLeftBase;            /* 0xc8 (0xc31c) */
    int nRightBase;           /* 0xcc (0xc320) */
} Ov008ColumnPanel;

typedef struct Ov008SellDialog {
    void *pRecord;            /* 0x00 (0xc4c8) */
    int   aCell[2];           /* 0x04 (0xc4cc): name / price cells */
} Ov008SellDialog;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x2ab0];
    u8  widgets[0x7530 - 0x2ab0];     /* 0x2ab0: widget context */
    u8  widgetsB[0xbfb0 - 0x7530];    /* 0x7530: widget manager */
    int hSlots;                       /* 0xbfb0 */
    u8  pad_bfb4[0xc160 - 0xbfb4];
    u8  dialogSurface[0xc250 - 0xc160]; /* 0xc160 */
    int nTab;                         /* 0xc250 */
    Ov008ColumnPanel columns;         /* 0xc254 */
    u8  pad_c324[0xc4c8 - 0xc324];
    Ov008SellDialog sell;             /* 0xc4c8 */
    u8  pad_c4d4[0xc5e0 - 0xc4d4];
    int aChoiceCell[4];               /* 0xc5e0 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov026_02091368;
extern void  func_0203011c(void *pRegion, int nX, int nY, int nW, int nH);
extern void  func_02032450(int hSlots, int nCell);                       /* Slot_UnlinkIfLinked */
extern void *func_ov026_0208427c(void *pWidgets, int nId);               /* FindEntryById */
extern void  func_ov026_020843e8(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */

void func_ov026_02089658(void)
{
    int hSlots;
    Ov008PanelContext *const ctx = data_ov026_02091368;
    Ov008SellDialog *pSell;
    u8 *pWidgets;
    u8 *pWidgetsB;

    hSlots = ctx->hSlots;
    pSell = &ctx->sell;
    pWidgets = ctx->widgets;
    pWidgetsB = ctx->widgetsB;
    func_0203011c(ctx->dialogSurface, 0x28, 0x38, 0xb0, 0x40);
    func_02032450(ctx->hSlots, pSell->aCell[0]);
    func_02032450(ctx->hSlots, pSell->aCell[1]);
    func_ov026_020843e8(pWidgets, func_ov026_0208427c(pWidgets, WIDGET_OVERLAY_A), 0);
    func_ov026_020843e8(pWidgetsB, func_ov026_0208427c(pWidgetsB, WIDGET_OVERLAY_A), 0);
    func_ov026_020843e8(pWidgetsB, func_ov026_0208427c(pWidgetsB, WIDGET_OVERLAY_B), 0);
    if (ctx->nTab == TAB_SPECIAL) {
        ctx->columns.nRightSelected = 0;
        ctx->columns.nRightBase = 0;
    } else {
        ctx->columns.nLeftSelected = 0;
        ctx->columns.nLeftBase = 0;
    }
    func_02032450(hSlots, ctx->aChoiceCell[0]);
    func_02032450(hSlots, ctx->aChoiceCell[1]);
    func_02032450(hSlots, ctx->aChoiceCell[2]);
    func_02032450(hSlots, ctx->aChoiceCell[3]);
}
