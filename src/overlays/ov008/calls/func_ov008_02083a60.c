/* func_ov008_02083a60 -- Ov008_ShowCounterPanel: build the counter panel
 * (ctx+0xc324) unless it is already visible (+4).  On tabs (+0xc250) other
 * than 3 each of the three counters gets a kind-0 cell at y = 0x9f + 8 * i
 * and kind-2 / kind-3 cells at y = 0xe2 + 8 * i, all at x = 0xb2 (fx32), plus
 * the extra kind-4 cell (+0x38) at (0xb2, 0xaf), and widgets 7 / 8 of the
 * widget manager (+0x7530) are hidden; on tab 3 widgets 0x1e / 0x1f are
 * hidden and the counters get two kind-0 cells at y = 0x8c + 8 * i and
 * 0xc4 + 8 * i, x = 0xb0.  The ready word is cleared and the panel marked
 * visible.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define DIGIT_COUNT   3
#define TAB_SPECIAL   3
#define CELL_X        (0xb2 << 12)
#define CELL_X_TAB3   (0xb0 << 12)
#define EXTRA_Y       (0xaf << 12)
#define DIGIT_STEP    8

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
    u8   pad_0000[0x7530];
    u8   widgets[0xbfb4 - 0x7530];    /* 0x7530: widget manager */
    int *hSlotsB;                     /* 0xbfb4 */
    u8   pad_bfb8[0xc250 - 0xbfb8];
    int  nTab;                        /* 0xc250 */
    u8   pad_c254[0xc324 - 0xc254];
    Ov008CounterPanel counter;        /* 0xc324 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern int   func_ov008_02082ecc(int *hSlots, unsigned int nKind, int nSlot, int nY, int nX); /* create a cell */
extern void *func_ov008_02054788(void *pManager, int nId);                /* FindEntryById */
extern void  func_ov008_02054ba4(void *pManager, void *pEntry, int bVisible); /* SetEntrySlotsVisible */

void func_ov008_02083a60(void)
{
    Ov008PanelContext *ctx;
    Ov008CounterPanel *pPanel;
    int *hSlots;
    int i;
    void *pWidgets;

    ctx = data_ov008_02090fac;
    pPanel = &ctx->counter;
    if (pPanel->bVisible != 0) {
        return;
    }
    hSlots = ctx->hSlotsB;
    pWidgets = ctx->widgets;
    if (ctx->nTab != TAB_SPECIAL) {
        for (i = 0; i < DIGIT_COUNT; i++) {
            pPanel->aDigitA[i] = func_ov008_02082ecc(hSlots, 0, 0, (0x9f + i * DIGIT_STEP) << 12, CELL_X);
            pPanel->aDigitB[i] = func_ov008_02082ecc(hSlots, 2, 0, (0xe2 + i * DIGIT_STEP) << 12, CELL_X);
            pPanel->aDigitC[i] = func_ov008_02082ecc(hSlots, 3, 0, (0xe2 + i * DIGIT_STEP) << 12, CELL_X);
        }
        pPanel->hExtra = func_ov008_02082ecc(hSlots, 4, 0, EXTRA_Y, CELL_X);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 7), 0);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 8), 0);
    } else {
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 0x1e), 0);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 0x1f), 0);
        for (i = 0; i < DIGIT_COUNT; i++) {
            pPanel->aDigitA[i] = func_ov008_02082ecc(hSlots, 0, 0, (0x8c + i * DIGIT_STEP) << 12, CELL_X_TAB3);
            pPanel->aDigitB[i] = func_ov008_02082ecc(hSlots, 0, 0, (0xc4 + i * DIGIT_STEP) << 12, CELL_X_TAB3);
        }
    }
    pPanel->bReady = 0;
    pPanel->bVisible = 1;
}
