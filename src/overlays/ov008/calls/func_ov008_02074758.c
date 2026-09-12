/* func_ov008_02074758 -- Ov008_LayoutDetailPanel: place the mission detail
 * panel's widgets for scroll nScroll (clamped to [0, 0x60 - height]).  The
 * panel top (+0x160) becomes scroll + 0x3f; the nine row widgets 0x18..0x20 go
 * to x = widget 0x16's block x and y = top + 8 * i + 0x10 (fx32), the frame
 * widget 0x16 to the top and the footer 0x17 to top + height - 0x10; then the
 * scroll arrows are refreshed.
 */
typedef unsigned char u8;

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008DetailPanel {
    u8  pad_000[0x160];
    int nTop;                 /* 0x160 */
    int nHeight;              /* 0x164 */
} Ov008DetailPanel;

#define PANEL_SPAN   0x60
#define PANEL_BASE_Y 0x3f
#define WIDGET_FRAME  0x16
#define WIDGET_FOOTER 0x17
#define WIDGET_ROW0   0x18
#define WIDGET_ROW_LAST 0x20
#define ROW_STEP 8

extern int  func_ov008_02050c64(void);                                    /* Ov008_GetCtxBlock4a80 */
extern void *func_ov008_02054788(int nBlock, int nId);                    /* FindEntryById */
extern int *func_ov008_0205489c(int nBlock, void *pEntry);                /* Ov008_GetEntryBlock2c */
extern void func_ov008_02054858(int nBlock, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void func_ov008_020746dc(Ov008DetailPanel *pPanel, int nScroll);   /* Ov008_UpdateScrollArrows */

void func_ov008_02074758(Ov008DetailPanel *pPanel, int nScroll)
{
    UiLayoutPos pos = { 0, 0 };
    int nId;
    int nBlock;
    int nMax;

    nBlock = func_ov008_02050c64();
    nMax = PANEL_SPAN - pPanel->nHeight;
    if (nScroll > nMax) {
        nScroll = nMax;
    }
    if (nScroll < 0) {
        nScroll = 0;
    }
    pPanel->nTop = nScroll + PANEL_BASE_Y;
    pos.nX = *func_ov008_0205489c(nBlock, func_ov008_02054788(nBlock, WIDGET_FRAME));
    for (nId = WIDGET_ROW0; nId <= WIDGET_ROW_LAST; nId++) {
        pos.nY = (pPanel->nTop + (nId - WIDGET_ROW0) * ROW_STEP + 0x10) << 12;
        func_ov008_02054858(nBlock, func_ov008_02054788(nBlock, nId), &pos);
    }
    pos.nY = pPanel->nTop << 12;
    func_ov008_02054858(nBlock, func_ov008_02054788(nBlock, WIDGET_FRAME), &pos);
    pos.nY = (pPanel->nTop + pPanel->nHeight - 0x10) << 12;
    func_ov008_02054858(nBlock, func_ov008_02054788(nBlock, WIDGET_FOOTER), &pos);
    func_ov008_020746dc(pPanel, nScroll);
}
