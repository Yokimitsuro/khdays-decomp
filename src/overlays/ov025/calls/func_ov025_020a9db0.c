/* func_ov025_020a9db0 -- Ov008_LayoutDetailPanel: place the mission detail
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

extern int  func_ov025_02084a8c(void);                                    /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nBlock, int nId);                    /* FindEntryById */
extern int *func_ov025_02088544(int nBlock, void *pEntry);                /* Ov008_GetEntryBlock2c */
extern void func_ov025_02088500(int nBlock, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void func_ov025_020a9d34(Ov008DetailPanel *pPanel, int nScroll);   /* Ov008_UpdateScrollArrows */

void func_ov025_020a9db0(Ov008DetailPanel *pPanel, int nScroll)
{
    UiLayoutPos pos = { 0, 0 };
    int nId;
    int nBlock;
    int nMax;

    nBlock = func_ov025_02084a8c();
    nMax = PANEL_SPAN - pPanel->nHeight;
    if (nScroll > nMax) {
        nScroll = nMax;
    }
    if (nScroll < 0) {
        nScroll = 0;
    }
    pPanel->nTop = nScroll + PANEL_BASE_Y;
    pos.nX = *func_ov025_02088544(nBlock, func_ov025_0208843c(nBlock, WIDGET_FRAME));
    for (nId = WIDGET_ROW0; nId <= WIDGET_ROW_LAST; nId++) {
        pos.nY = (pPanel->nTop + (nId - WIDGET_ROW0) * ROW_STEP + 0x10) << 12;
        func_ov025_02088500(nBlock, func_ov025_0208843c(nBlock, nId), &pos);
    }
    pos.nY = pPanel->nTop << 12;
    func_ov025_02088500(nBlock, func_ov025_0208843c(nBlock, WIDGET_FRAME), &pos);
    pos.nY = (pPanel->nTop + pPanel->nHeight - 0x10) << 12;
    func_ov025_02088500(nBlock, func_ov025_0208843c(nBlock, WIDGET_FOOTER), &pos);
    func_ov025_020a9d34(pPanel, nScroll);
}
