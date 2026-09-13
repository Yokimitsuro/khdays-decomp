/* func_ov025_020a2914 -- Ov008_SelectStatusTab: switch the status panel to
 * tab nTab (+0x208) unless it is already shown or the panel is busy (+0x8).
 * Every tab widget 0x79..0x86 of block 4a80 except 0x80 is hidden; the tab's
 * label widget (0x79 + tab) and its page widget (0x81 + tab, 0x80 for tab 6)
 * are reset to frame 0 and shown -- an unknown tab selects none.  The page
 * widget is kept at +0x54 and the tab recorded.
 */
typedef unsigned char u8;

#define TAB_COUNT     7
#define WIDGET_FIRST  0x79
#define WIDGET_LAST   0x86
#define WIDGET_SKIP   0x80

typedef struct Ov008StatusPanel {
    u8  pad_000[0x8];
    int nBusy;                /* 0x008 */
    u8  pad_00c[0x54 - 0xc];
    void *pPageWidget;        /* 0x054 */
    u8  pad_058[0x208 - 0x58];
    int nTab;                 /* 0x208 */
} Ov008StatusPanel;

extern int  func_ov025_02084a8c(void);                                    /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void func_ov025_02088928(int nCtx, void *pEntry, int nFrame);      /* Ov008_ReleaseTwoSlotsEx */

void func_ov025_020a2914(Ov008StatusPanel *pPanel, int nTab)
{
    int i;
    int nCtx;
    void *pLabel;
    void *pPage;

    if (pPanel->nTab == nTab) {
        return;
    }
    if (pPanel->nBusy != 0) {
        return;
    }
    nCtx = func_ov025_02084a8c();
    for (i = WIDGET_FIRST; i <= WIDGET_LAST; i++) {
        if (i != WIDGET_SKIP) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), 0);
        }
    }
    switch (nTab) {
    case 0:
        pLabel = func_ov025_0208843c(nCtx, 0x79);
        pPage = func_ov025_0208843c(nCtx, 0x81);
        break;
    case 1:
        pLabel = func_ov025_0208843c(nCtx, 0x7a);
        pPage = func_ov025_0208843c(nCtx, 0x82);
        break;
    case 2:
        pLabel = func_ov025_0208843c(nCtx, 0x7b);
        pPage = func_ov025_0208843c(nCtx, 0x83);
        break;
    case 3:
        pLabel = func_ov025_0208843c(nCtx, 0x7c);
        pPage = func_ov025_0208843c(nCtx, 0x84);
        break;
    case 4:
        pLabel = func_ov025_0208843c(nCtx, 0x7d);
        pPage = func_ov025_0208843c(nCtx, 0x85);
        break;
    case 5:
        pLabel = func_ov025_0208843c(nCtx, 0x7e);
        pPage = func_ov025_0208843c(nCtx, 0x86);
        break;
    case 6:
        pLabel = func_ov025_0208843c(nCtx, 0x7f);
        pPage = func_ov025_0208843c(nCtx, 0x80);
        break;
    default:
        pLabel = 0;
        pPage = 0;
        break;
    }
    if (pLabel != 0) {
        func_ov025_02088928(nCtx, pLabel, 0);
        func_ov025_0208884c(nCtx, pLabel, 1);
    }
    if (pPage != 0) {
        func_ov025_02088928(nCtx, pPage, 0);
        func_ov025_0208884c(nCtx, pPage, 1);
    }
    pPanel->pPageWidget = pPage;
    pPanel->nTab = nTab;
}
