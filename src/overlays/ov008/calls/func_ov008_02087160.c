/* func_ov008_02087160 -- Ov008_DrawShopDetailPanel: redraw the shop's detail
 * panel surface (+0xc160): frame (0x28, 0x38, 0xb0 x 0x50), the record's item
 * name (+0xc4f4 -> item def -> name) centred on 0x92 from its width (+0xc548)
 * at y 0x3b, and the label for the current selection (+0xc528 [+0xc534]) at
 * (0x80, 0x4e).  The four choice cells (+0xc5e0) show "selection 0 and choice
 * (+0xc53c) 0 / not 0 / 1 / not 1".  On selection 0 the two texts (+0xc520,
 * +0xc524) are drawn at (0x50, 0x6a) / (0xb0, 0x6a), the record's quantity
 * (+0xc518) is applied and widget 1 of the panel context (+0x2ab0) is moved to
 * x = (0x20 or 0x80 by the choice) << 12, keeping its y.  Codegen: local
 * pointers to the far members (hoisted partial bases), assigned in the order
 * hSlots, pPanel, pWidgets, pSurface; the selection is the low 16 bits of an
 * int (ldr + lsl/asr).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_CELLS 8
#define TEXT_STYLE 4

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008ItemDef {
    u8    pad_00[0xc];
    void *pName;              /* 0x0c */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8            pad_00[0xc];
    Ov008ItemDef *pItemDef;   /* 0x0c */
} Ov008ParamRecord;

typedef struct Ov008ShopDetailPanel {
    Ov008ParamRecord *pRecord; /* 0x00 */
    int   aRowCell[ROW_CELLS]; /* 0x04 */
    u32   nQuantity;          /* 0x24 */
    u8    pad_28[4];
    void *pTextLeft;          /* 0x2c */
    void *pTextRight;         /* 0x30 */
    void *apLabel[3];         /* 0x34: per selection */
    int   nSelection : 16;    /* 0x40 */
    int   pad_40 : 16;
    u8    pad_44[4];
    int   nChoice;            /* 0x48 */
    u8    pad_4c[8];
    int   nTitleWidth;        /* 0x54 */
} Ov008ShopDetailPanel;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x2ab0];
    u8  widgets[0xbfb0 - 0x2ab0]; /* 0x2ab0: widget context */
    int hSlots;               /* 0xbfb0 */
    u8  pad_bfb4[0xc160 - 0xbfb4];
    u8  detailSurface[0x3c];  /* 0xc160 */
    u8  pad_c19c[0xc4f4 - 0xc19c];
    Ov008ShopDetailPanel detail;  /* 0xc4f4 */
    u8  pad_c54c[0xc5e0 - 0xc54c];
    int aChoiceCell[4];       /* 0xc5e0 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH);            /* Obj_InvokeInnerVtable8 */
extern void  func_ov008_02082d44(void *pSurface, void *pText, int nX, int nY, int nStyle, int nShadow); /* Ov008_DrawStringShadowed */
extern void  func_02032710(int hSlots, int nCell, int bVisible);                        /* Slot_SetVisible */
extern void  func_ov008_02083c44(Ov008ParamRecord *pRecord, u32 nQuantity);
extern void *func_ov008_02054788(void *pWidgets, int nId);                              /* FindEntryById */
extern UiLayoutPos *func_ov008_02054820(void *pWidgets, void *pEntry);                  /* Ov008_GetEntryPos */
extern void  func_ov008_02054858(void *pWidgets, void *pEntry, UiLayoutPos *pPos);      /* Ov008_SetEntryPos */

void func_ov008_02087160(void)
{
    Ov008PanelContext *ctx;
    Ov008ShopDetailPanel *pPanel;
    u8 *pSurface;
    int hSlots;
    u8 *pWidgets;
    UiLayoutPos pos;

    ctx = data_ov008_02090fac;
    hSlots = ctx->hSlots;
    pPanel = &ctx->detail;
    pWidgets = ctx->widgets;
    pSurface = ctx->detailSurface;
    func_0203011c(pSurface, 0x28, 0x38, 0xb0, 0x50);
    func_ov008_02082d44(pSurface, pPanel->pRecord->pItemDef->pName, 0x92 - ((pPanel->nTitleWidth + 0x10) >> 1), 0x3b, TEXT_STYLE, 8);
    func_ov008_02082d44(pSurface, pPanel->apLabel[pPanel->nSelection], 0x80, 0x4e, TEXT_STYLE, 0x10);
    func_02032710(hSlots, ctx->aChoiceCell[0], pPanel->nSelection == 0 && pPanel->nChoice == 0);
    func_02032710(hSlots, ctx->aChoiceCell[1], pPanel->nSelection == 0 && pPanel->nChoice != 0);
    func_02032710(hSlots, ctx->aChoiceCell[2], pPanel->nSelection == 0 && pPanel->nChoice == 1);
    func_02032710(hSlots, ctx->aChoiceCell[3], pPanel->nSelection == 0 && pPanel->nChoice != 1);
    if (pPanel->nSelection != 0) {
        return;
    }
    func_ov008_02082d44(pSurface, pPanel->pTextLeft, 0x50, 0x6a, TEXT_STYLE, 0x10);
    func_ov008_02082d44(pSurface, pPanel->pTextRight, 0xb0, 0x6a, TEXT_STYLE, 0x10);
    func_ov008_02083c44(pPanel->pRecord, pPanel->nQuantity);
    pos.nX = ((pPanel->nChoice == 0 ? 0 : 0x60) + 0x20) << 12;
    pos.nY = func_ov008_02054820(pWidgets, func_ov008_02054788(pWidgets, 1))->nY;
    func_ov008_02054858(pWidgets, func_ov008_02054788(pWidgets, 1), &pos);
}
