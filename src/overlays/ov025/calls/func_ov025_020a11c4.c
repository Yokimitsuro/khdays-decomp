/* func_ov025_020a11c4 -- Ov008_DrawStatusPanelLabels: lay out and draw the
 * status panel's labels.  The four widget pairs of data_ov025_020b4390 are
 * placed at the panel's four positions (+0x21c, 8 bytes each), shifted left
 * by 4.0 (fx32) while the +0x44 word is clear.  The label surface (+0xdc)
 * is cleared and variable records 0..3 drawn at x = 8 + shift, y = 4 / 0x14
 * / 0x24 / 0x34 in colour 0xf2 with shadow; record 2 (and record 3 for
 * global short 0204c1ec 5 or 3) uses the wide glyph set's pixel buffer
 * (surface word +0xfc), the others block 968c.  Page-B widgets 2, 3, 5 and 6
 * are then drawn with the values at +0x1f8.. and their extras at +0x1e8..,
 * and the panel refreshed (0206f35c).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define PAIR_COUNT   4
#define LABEL_COLOUR 0xf2
#define SHIFT_NARROW (-4)

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008WidgetPair {
    int nFirst;
    int nSecond;
} Ov008WidgetPair;

typedef struct Ov008WidgetPairTable {
    Ov008WidgetPair aPair[PAIR_COUNT];
} Ov008WidgetPairTable;

typedef struct Ov008StatusPanel {
    u8  pad_000[0x44];
    int bWide;                /* 0x044 */
    u8  pad_048[0x58 - 0x48];
    u8  textLoader[0xc];      /* 0x058 */
    u8  pad_064[0xdc - 0x64];
    u8  labelSurface[0x20];   /* 0x0dc */
    void *pLabelPixels;       /* 0x0fc: surface pixel buffer */
    u8  pad_100[0x1e8 - 0x100];
    int aExtra[4];            /* 0x1e8 */
    int aValue[4];            /* 0x1f8 */
    u8  pad_208[0x21c - 0x208];
    UiLayoutPos aPos[PAIR_COUNT]; /* 0x21c */
} Ov008StatusPanel;

extern const Ov008WidgetPairTable data_ov025_020b4390;
extern int   func_02024e5c(void);                                         /* LoadGlobalShort_0204c1ec */
extern void *func_ov025_02084c84(void);                                   /* Ov008_GetCtxBlock968c */
extern void *func_ov025_02084cb4(void);                                   /* wide glyph set */
extern int   func_ov025_02084a8c(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void  MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void  func_ov025_0208854c(int nCtx, void *pEntry, UiLayoutPos *pPos); /* set the base position */
extern void  func_02030158(void *pSurface);                               /* Obj_InvokeInnerVtable4: clear */
extern void *func_ov025_02089894(void *pRecords, int nIndex);             /* GetVarRecordByIndex */
extern void  func_02030278(void *pSurface, int nX, int nY, int nColour, void *pText, int nShadow); /* Text_DrawWithShadow */
extern void  func_ov025_020a42b8(int nKind, int nArg, ...);               /* Ov008_DrawPageBWidget */
extern void  func_ov025_020a4948(void);

void func_ov025_020a11c4(Ov008StatusPanel *pPanel)
{
    Ov008WidgetPairTable pairs;
    UiLayoutPos pos = { 0, 0 };
    int nMode;
    void *pNarrow;
    void *pWide;
    int nShift;
    int i;
    int nCtx;

    pairs = data_ov025_020b4390;
    nMode = func_02024e5c();
    pNarrow = func_ov025_02084c84();
    pWide = func_ov025_02084cb4();
    if (pPanel->bWide == 0) {
        nShift = SHIFT_NARROW;
    } else {
        nShift = 0;
    }
    nCtx = func_ov025_02084a8c();
    for (i = 0; i < PAIR_COUNT; i++) {
        MI_CpuCopy8(&pPanel->aPos[i], &pos, sizeof(pos));
        pos.nX += nShift << 12;
        func_ov025_0208854c(nCtx, func_ov025_0208843c(nCtx, pairs.aPair[i].nFirst), &pos);
        func_ov025_0208854c(nCtx, func_ov025_0208843c(nCtx, pairs.aPair[i].nSecond), &pos);
    }
    func_02030158(pPanel->labelSurface);
    func_02030278(pPanel->labelSurface, nShift + 8, 4, LABEL_COLOUR, func_ov025_02089894(pPanel->textLoader, 0), 1);
    func_02030278(pPanel->labelSurface, nShift + 8, 0x14, LABEL_COLOUR, func_ov025_02089894(pPanel->textLoader, 1), 1);
    pPanel->pLabelPixels = pWide;
    func_02030278(pPanel->labelSurface, nShift + 8, 0x24, LABEL_COLOUR, func_ov025_02089894(pPanel->textLoader, 2), 1);
    pPanel->pLabelPixels = pNarrow;
    if (nMode == 5 || nMode == 3) {
        pPanel->pLabelPixels = pWide;
    }
    func_02030278(pPanel->labelSurface, nShift + 8, 0x34, LABEL_COLOUR, func_ov025_02089894(pPanel->textLoader, 3), 1);
    if (nMode == 5 || nMode == 3) {
        pPanel->pLabelPixels = pNarrow;
    }
    func_ov025_020a42b8(2, pPanel->aValue[0], pPanel->aExtra[0]);
    func_ov025_020a42b8(3, pPanel->aValue[1], pPanel->aExtra[1]);
    func_ov025_020a42b8(5, pPanel->aValue[2], pPanel->aExtra[2]);
    func_ov025_020a42b8(6, pPanel->aValue[3], pPanel->aExtra[3]);
    func_ov025_020a4948();
}
