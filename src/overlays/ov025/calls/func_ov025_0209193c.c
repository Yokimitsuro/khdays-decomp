/* func_ov025_0209193c -- Ov008_InitMenuScrollKnob: size the menu list's
 * scroll knob and start the scroll.  The knob length (+0x2f8) is
 * nView * nTotal / nRows (at most nTotal, at least 0x20); (knob - 0x19) / 8 knob segment widgets 0xf.. are shown and the rest
 * up to 0x1a hidden; the end caps 0xd / 0xe are shown, and cap 0xe is placed
 * (knob - 0x10) rows (fx32) below cap 0xd's block position.  Then the eased
 * scroll (0205f388) is kicked with target 0.
 */
typedef unsigned char u8;

#define SEGMENT_FIRST 0xf
#define SEGMENT_COUNT 0xc
#define WIDGET_CAP_A  0xd
#define WIDGET_CAP_B  0xe
#define KNOB_MIN      0x20

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008LayoutCtx2 {
    u8  pad_0000[0x2f8];
    int nKnobLength;          /* 0x2f8 */
} Ov008LayoutCtx2;

extern int   func_02020400(int nNum, int nDen);                           /* _s32_div_f */
extern int   func_ov025_02084a7c(void);                                   /* Ov008_GetContext */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);   /* SetEntrySlotsVisible */
extern int  *func_ov025_02088544(int nCtx, void *pEntry);                 /* Ov008_GetEntryBlock2c */
extern void  func_ov025_02088500(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void  func_ov025_020918d8(Ov008LayoutCtx2 *pCtx, int nA, int nB, int nC, int nD); /* eased scroll */

void func_ov025_0209193c(Ov008LayoutCtx2 *pCtx, int nRows, int nView, int nTotal)
{
    UiLayoutPos pos = { 0, 0 };
    int nCtx;
    int i;
    int nSegments;
    int nKnob;
    void *pCapA;
    void *pCapB;
    int *pBlock;

    nKnob = func_02020400(nView * nTotal, nRows);
    if (nKnob > nTotal) {
        nKnob = nTotal;
    }
    if (nKnob < KNOB_MIN) {
        nKnob = KNOB_MIN;
    }
    nSegments = (nKnob - 0x19) / 8;
    nCtx = func_ov025_02084a7c();
    for (i = 0; i < nSegments; i++) {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i + SEGMENT_FIRST), 1);
    }
    for (; i < SEGMENT_COUNT; i++) {
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i + SEGMENT_FIRST), 0);
    }
    pCapA = func_ov025_0208843c(nCtx, WIDGET_CAP_A);
    pCapB = func_ov025_0208843c(nCtx, WIDGET_CAP_B);
    func_ov025_0208884c(nCtx, pCapA, 1);
    func_ov025_0208884c(nCtx, pCapB, 1);
    pBlock = func_ov025_02088544(nCtx, pCapA);
    pos.nX = pBlock[0];
    pos.nY = pBlock[1] + ((nKnob - 0x10) << 12);
    func_ov025_02088500(nCtx, pCapB, &pos);
    pCtx->nKnobLength = nKnob;
    func_ov025_020918d8(pCtx, 0, nRows, nView, nTotal);
}
