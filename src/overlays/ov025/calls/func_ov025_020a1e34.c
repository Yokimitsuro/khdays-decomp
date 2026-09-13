/* func_ov025_020a1e34 -- Ov008_LayoutScrollGauge: place the scroll menu's
 * gauge widgets for knob position nPos.  The rail base comes from widget
 * 0x2d's block (+0 = x); the fourteen knob segments 0x30..0x3d sit at
 * y = nPos + 8 + 8 * i + 0x10 (fx32), the top cap 0x2d at nPos + 8 and the
 * bottom cap 0x2f at nPos + 8 + nGaugeScale - 0x10; every widget also gets the
 * menu's horizontal slide (-nSlideX, +0x38) applied as an offset sum.  The
 * knob offset (+0x48) records nPos.
 */
typedef unsigned char u8;

#define SEGMENT_FIRST 0x30
#define SEGMENT_LAST  0x3d
#define WIDGET_CAP_TOP    0x2d
#define WIDGET_CAP_BOTTOM 0x2f

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008ScrollMenu {
    u8  pad_000[0x38];
    int nSlideX;              /* 0x038 */
    u8  pad_03c[0xc];
    int nKnobPos;             /* 0x048 */
    int nGaugeScale;          /* 0x04c */
} Ov008ScrollMenu;

extern int   func_ov025_02084a8c(void);                                  /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                     /* FindEntryById */
extern int  *func_ov025_02088544(int nCtx, void *pEntry);                /* Ov008_GetEntryBlock2c */
extern void  func_ov025_0208854c(int nCtx, void *pEntry, UiLayoutPos *pPos); /* set the base position */
extern void  func_ov025_02088564(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_ApplyOffsetSum */

void func_ov025_020a1e34(Ov008ScrollMenu *pMenu, int nPos)
{
    UiLayoutPos pos = { 0, 0 };
    int nCtx;
    int *pRail;
    void *pEntry;
    void *pCapTop;
    void *pCapBottom;
    int nId;
    int nTop;

    nCtx = func_ov025_02084a8c();
    pRail = func_ov025_02088544(nCtx, func_ov025_0208843c(nCtx, WIDGET_CAP_TOP));
    nTop = nPos + 8;
    for (nId = SEGMENT_FIRST; nId <= SEGMENT_LAST; nId++) {
        pEntry = func_ov025_0208843c(nCtx, nId);
        pos.nX = pRail[0];
        pos.nY = (nTop + (nId - SEGMENT_FIRST) * 8 + 0x10) << 12;
        func_ov025_0208854c(nCtx, pEntry, &pos);
        pos.nX = -pMenu->nSlideX << 12;
        pos.nY = 0;
        func_ov025_02088564(nCtx, pEntry, &pos);
    }
    pCapTop = func_ov025_0208843c(nCtx, WIDGET_CAP_TOP);
    pCapBottom = func_ov025_0208843c(nCtx, WIDGET_CAP_BOTTOM);
    pos.nX = pRail[0];
    pos.nY = nTop << 12;
    func_ov025_0208854c(nCtx, pCapTop, &pos);
    pos.nY = (nTop + pMenu->nGaugeScale - 0x10) << 12;
    func_ov025_0208854c(nCtx, pCapBottom, &pos);
    pos.nX = -pMenu->nSlideX << 12;
    pos.nY = 0;
    func_ov025_02088564(nCtx, pCapTop, &pos);
    func_ov025_02088564(nCtx, pCapBottom, &pos);
    pMenu->nKnobPos = nPos;
}
