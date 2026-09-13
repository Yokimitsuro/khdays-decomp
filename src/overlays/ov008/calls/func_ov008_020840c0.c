/* func_ov008_020840c0 -- Ov008_HideCounterPanel: take the counter panel
 * (ctx+0xc324) down when it is visible (+4).  On any tab (+0xc250) but 3 the
 * three digit cells of its three counters (+8, +0x14, +0x20) and the extra
 * cell (+0x38) are unlinked from slot set B (+0xbfb4), and widgets 7, 9, 1
 * and 0x14..0x1a of the widget manager (+0x7530) hidden; on tab 3 widgets
 * 0x1e / 0x1f are hidden and only the first two counters unlinked.  Then the
 * tag-tracker callback of tag 0x3f2 (+0x5c) fires, the panel's render
 * surface (+0xc1d8) is reset to a 0xb0 x 0x30 box at the origin and the
 * ready / visible words cleared.
 *
 * NOTE: compiled with #pragma opt_common_subs off (push/pop scoped): with CSE on
 * the context pointer is coloured r7 and the panel / slots / index registers
 * rotate one down; the pragma reproduces the ROM's r4..r7 assignment.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define DIGIT_COUNT   3
#define TAB_SPECIAL   3
#define TAG_COUNTER   0x3f2
#define WIDGET_FIRST  0x14
#define WIDGET_LAST   0x1a
#define PANEL_W       0xb0
#define PANEL_H       0x30

typedef struct Ov008CounterPanel {
    int bReady;               /* 0x00 */
    int bVisible;             /* 0x04 */
    int aDigitA[DIGIT_COUNT]; /* 0x08 */
    int aDigitB[DIGIT_COUNT]; /* 0x14 */
    int aDigitC[DIGIT_COUNT]; /* 0x20 */
    u8  pad_2c[0x38 - 0x2c];
    int hExtra;               /* 0x38 */
} Ov008CounterPanel;

typedef struct Ov008PanelContext {
    u8   pad_0000[0x5c];
    u8   tagTracker[0x7530 - 0x5c];   /* 0x005c */
    u8   widgets[0xbfb4 - 0x7530];    /* 0x7530: widget manager */
    int *hSlotsB;                     /* 0xbfb4 */
    u8   pad_bfb8[0xc1d8 - 0xbfb8];
    u8   counterSurface[0xc250 - 0xc1d8]; /* 0xc1d8 */
    int  nTab;                        /* 0xc250 */
    u8   pad_c254[0xc324 - 0xc254];
    Ov008CounterPanel counter;        /* 0xc324 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern void  func_02032450(int *hSlots, int nCell);                       /* Slot_UnlinkIfLinked */
extern void *func_ov008_02054788(void *pManager, int nId);                /* FindEntryById */
extern void  func_ov008_02054ba4(void *pManager, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void *func_ov008_02055808(void *pOwner, int nTag);                 /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(void *pOwner, void *pEntry);             /* Ov008_TagTracker_InvokeCallback */
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8 */

#pragma push
#pragma opt_common_subs off
#pragma push
#pragma opt_common_subs off
void func_ov008_020840c0(void)
{
    Ov008PanelContext *ctx;
    Ov008CounterPanel *pPanel;
    int *hSlots;
    int i;
    void *pWidgets;
    void *pSurface;

    ctx = data_ov008_02090fac;
    pPanel = &ctx->counter;
    if (pPanel->bVisible == 0) {
        return;
    }
    hSlots = ctx->hSlotsB;
    pSurface = ctx->counterSurface;
    pWidgets = ctx->widgets;
    if (ctx->nTab != TAB_SPECIAL) {
        for (i = 0; i < DIGIT_COUNT; i++) {
            func_02032450(hSlots, pPanel->aDigitA[i]);
            func_02032450(hSlots, pPanel->aDigitB[i]);
            func_02032450(hSlots, pPanel->aDigitC[i]);
        }
        func_02032450(hSlots, pPanel->hExtra);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 7), 0);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 9), 0);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 1), 0);
        for (i = WIDGET_FIRST; i <= WIDGET_LAST; i++) {
            func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, i), 0);
        }
    } else {
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 0x1e), 0);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 0x1f), 0);
        for (i = 0; i < DIGIT_COUNT; i++) {
            func_02032450(hSlots, pPanel->aDigitA[i]);
            func_02032450(hSlots, pPanel->aDigitB[i]);
        }
    }
    func_ov008_0205589c(ctx->tagTracker, func_ov008_02055808(ctx->tagTracker, TAG_COUNTER));
    func_0203011c(pSurface, 0, 0, PANEL_W, PANEL_H);
    pPanel->bReady = 0;
    pPanel->bVisible = 0;
}
#pragma pop
#pragma pop
