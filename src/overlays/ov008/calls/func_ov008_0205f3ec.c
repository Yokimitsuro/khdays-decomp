/* func_ov008_0205f3ec -- Ov008_InitMenuScrollKnob: size the menu list's
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
extern int   func_ov008_02050c54(void);                                   /* Ov008_GetContext */
extern void *func_ov008_02054788(int nCtx, int nId);                      /* FindEntryById */
extern void  func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);   /* SetEntrySlotsVisible */
extern int  *func_ov008_0205489c(int nCtx, void *pEntry);                 /* Ov008_GetEntryBlock2c */
extern void  func_ov008_02054858(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void  func_ov008_0205f388(Ov008LayoutCtx2 *pCtx, int nA, int nB, int nC, int nD); /* eased scroll */

void func_ov008_0205f3ec(Ov008LayoutCtx2 *pCtx, int nRows, int nView, int nTotal)
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
    nCtx = func_ov008_02050c54();
    for (i = 0; i < nSegments; i++) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i + SEGMENT_FIRST), 1);
    }
    for (; i < SEGMENT_COUNT; i++) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i + SEGMENT_FIRST), 0);
    }
    pCapA = func_ov008_02054788(nCtx, WIDGET_CAP_A);
    pCapB = func_ov008_02054788(nCtx, WIDGET_CAP_B);
    func_ov008_02054ba4(nCtx, pCapA, 1);
    func_ov008_02054ba4(nCtx, pCapB, 1);
    pBlock = func_ov008_0205489c(nCtx, pCapA);
    pos.nX = pBlock[0];
    pos.nY = pBlock[1] + ((nKnob - 0x10) << 12);
    func_ov008_02054858(nCtx, pCapB, &pos);
    pCtx->nKnobLength = nKnob;
    func_ov008_0205f388(pCtx, 0, nRows, nView, nTotal);
}
