/* func_ov008_020877a8 -- Ov008_CloseBuyDialog: the inverse of
 * Ov008_OpenBuyDialog (0208744c): runs tag 0x199 of the primary tracker
 * (+0x10) through callback 0x40, hides widgets 9 and 7 of the widget context
 * (+0x2ab0), unlinks the buy dialog's (+0xc54c) two category cells (+0x8) and
 * three digit cells (+0x10) from the slot manager (+0xbfb0), and clears the
 * dialog surface (+0xc160) region the open framed (0x20, 0x30, 0xc0 x 0x60).
 *
 * Codegen: the members sit at their real offsets and mwcc splits the
 * unencodable ones itself (ctx+0xab0 / ctx+0x160 kept as partial bases with
 * +0x2000 / +0xc000 at each use, ctx+0x14c+0xc400 for the dialog).  The
 * context pointer is a `const` local: a plain `ctx = global` is copy-propagated
 * into the global's load temp, which is coloured last (r8) and pushes hSlots
 * into r6; the const local keeps ctx a declared variable (r6) and lets the
 * tail's 0x60 reuse r4.  The dialog pointer is assigned first.
 */
typedef unsigned char u8;

#define TAG_BUY_DIALOG   0x199
#define WIDGET_DIALOG_A  9
#define WIDGET_DIALOG_B  7
#define CATEGORY_CELLS   2
#define DIGIT_CELLS      3

typedef struct Ov008BuyDialog {
    u8  pad_00[8];
    int aCategoryCell[CATEGORY_CELLS]; /* 0x08 (0xc554) */
    int aDigitCell[DIGIT_CELLS];       /* 0x10 (0xc55c) */
} Ov008BuyDialog;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x10];
    u8  tracker[0x2ab0 - 0x10];       /* 0x0010: primary tag tracker */
    u8  widgets[0xbfb0 - 0x2ab0];     /* 0x2ab0: widget context */
    int hSlots;                       /* 0xbfb0 */
    u8  pad_bfb4[0xc160 - 0xbfb4];
    u8  dialogSurface[0xc54c - 0xc160]; /* 0xc160 */
    Ov008BuyDialog buy;               /* 0xc54c */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern int   func_ov008_02055808(void *pTracker, int nTag);              /* ov008_FindEntryByTag */
extern void  func_ov008_020558f4(void *pTracker, int nCell);             /* ov008_InvokeCallback40 */
extern void *func_ov008_02054788(void *pWidgets, int nId);               /* FindEntryById */
extern void  func_ov008_02054ba4(void *pWidgets, void *pWidget, int bVisible); /* SetEntrySlotsVisible */
extern void  func_02032450(int hSlots, int hObject);                     /* Slot_UnlinkIfLinked */
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8 */

void func_ov008_020877a8(void)
{
    Ov008PanelContext *const ctx = data_ov008_02090fac;
    Ov008BuyDialog *pDialog;
    int hSlots;
    u8 *pWidgets;
    u8 *pSurface;
    int i;

    pDialog = &ctx->buy;
    hSlots = ctx->hSlots;
    pWidgets = ctx->widgets;
    pSurface = ctx->dialogSurface;

    func_ov008_020558f4(ctx->tracker, func_ov008_02055808(ctx->tracker, TAG_BUY_DIALOG));
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_DIALOG_A), 0);
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_DIALOG_B), 0);
    func_02032450(hSlots, pDialog->aCategoryCell[0]);
    func_02032450(hSlots, pDialog->aCategoryCell[1]);
    for (i = 0; i < DIGIT_CELLS; i++) {
        func_02032450(hSlots, pDialog->aDigitCell[i]);
    }
    func_0203011c(pSurface, 0x20, 0x30, 0xc0, 0x60);
}
