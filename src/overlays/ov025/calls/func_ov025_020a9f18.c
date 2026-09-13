/* func_ov025_020a9f18 -- Ov008_InitDetailPanelKnob: size the detail panel's
 * scroll knob for nRows rows: 0x480 / nRows, clamped to 0x20..0x60 (+0x164);
 * (knob - 0x19) / 8 segment widgets 0x18.. are shown and the rest up to 0x20
 * hidden; widgets 0x16..0x20 get their slots released (plain and with frame
 * 0); the caps 0x16 / 0x17 are shown and cap 0x17 placed (knob - 0x10) rows
 * (fx32) below cap 0x16's block position.  Then the panel is laid out at
 * scroll 0 (02074878).
 */
typedef unsigned char u8;

#define SEGMENT_FIRST 0x18
#define SEGMENT_COUNT 9
#define WIDGET_CAP_A  0x16
#define WIDGET_CAP_B  0x17
#define WIDGET_LAST   0x20
#define KNOB_MAX      0x60
#define KNOB_MIN      0x20
#define PANEL_SPAN    0x480

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008DetailPanel {
    u8  pad_000[0x164];
    int nHeight;              /* 0x164: knob length */
} Ov008DetailPanel;

extern int   func_02020400(int nNum, int nDen);                           /* _s32_div_f */
extern int   func_ov025_02084a8c(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);   /* SetEntrySlotsVisible */
extern void  func_ov025_020888b0(int nCtx, void *pEntry);                 /* Ov008_ReleaseTwoSlots */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nFrame);     /* Ov008_ReleaseTwoSlotsEx */
extern int  *func_ov025_02088544(int nCtx, void *pEntry);                 /* Ov008_GetEntryBlock2c */
extern void  func_ov025_02088500(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void  func_ov025_020a9ed0(Ov008DetailPanel *pPanel, int nScroll);  /* lay the panel out */

void func_ov025_020a9f18(Ov008DetailPanel *pPanel, int nRows)
{
    int nKnob;
    int nSegments;
    int nCtx;
    int i;
    void *pCapA;
    void *pCapB;
    int *pBlock;

    nKnob = func_02020400(PANEL_SPAN, nRows);
    if (nKnob > KNOB_MAX) {
        nKnob = KNOB_MAX;
    }
    if (nKnob < KNOB_MIN) {
        nKnob = KNOB_MIN;
    }
    nSegments = (nKnob - 0x19) / 8;
    nCtx = func_ov025_02084a8c();
    {
        UiLayoutPos pos = { 0, 0 };
        for (i = 0; i < nSegments; i++) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i + SEGMENT_FIRST), 1);
        }
        for (; i < SEGMENT_COUNT; i++) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i + SEGMENT_FIRST), 0);
        }
        for (i = WIDGET_CAP_A; i <= WIDGET_LAST; i++) {
            func_ov025_020888b0(nCtx, func_ov025_0208843c(nCtx, i));
            func_ov025_02088928(nCtx, func_ov025_0208843c(nCtx, i), 0);
        }
        pCapA = func_ov025_0208843c(nCtx, WIDGET_CAP_A);
        pCapB = func_ov025_0208843c(nCtx, WIDGET_CAP_B);
        func_ov025_0208884c(nCtx, pCapA, 1);
        func_ov025_0208884c(nCtx, pCapB, 1);
        pBlock = func_ov025_02088544(nCtx, pCapA);
        pos.nX = pBlock[0];
        pos.nY = pBlock[1] + ((nKnob - 0x10) << 12);
        func_ov025_02088500(nCtx, pCapB, &pos);
        pPanel->nHeight = nKnob;
        func_ov025_020a9ed0(pPanel, 0);
    }
}
