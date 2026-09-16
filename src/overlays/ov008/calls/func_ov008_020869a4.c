/* func_ov008_020869a4 -- Ov008_DrawTradePanel: redraw the shop's trade
 * (synthesis) panel: its surface (+0xc214, cleared 0xb6 x 0x70 at (8, 0x10))
 * and the detail block (+0xc4f4).  The first draw (+0x28) runs tag callback
 * 0x3f4 (tracker +0x5c).  When the list is ready (+0xc4c4) the current row's
 * record (+0xc3d0 [+0xc3c4]) becomes the detail record: without rows the
 * column panel's left selection / base (+0xc314 / +0xc31c) clear, widget 6 (+0x7530) hides and the
 * record is dropped; else the stock cap (02082234), the owned count
 * (GameState 0x810 by the item id, 0208b0bc) and the count plus the record's
 * bonus (+0x10) decide: a price (+0x8) above the points shows the counter
 * panel with the owned count (-1 below the cap) and hides widget 6; a bonus
 * total above the cap keeps the owned count as the quantity (+0x24) with
 * the two words clear and widget 6 hidden; otherwise the quantity is the total
 * capped, left selection = 2, left base = -price and widget 6 shows; the counter
 * panel then shows the quantity.  The ready word is cleared.  Then, for the
 * record's four ingredients (+0x14, 8 each: item def, needed count), the
 * icon cells (+0x4) and mark cells (+0x14) hide, and with rows and an
 * ingredient the icon (def +0x20, frame id - 1) shows, the mark follows
 * "owned count differs from the unassigned copies (0208b148)", and a row
 * at y 16 * (i + 1) + 0xb draws the name (x 0x1a) and variable text 4
 * (+0xc5d8, x 0x82) greyed (6) while the unassigned copies are below the
 * needed count, the needed count (x 0x9a), text 02090ecc (x 0x9e), the
 * unassigned copies (x 0xa2) and text 02090ed0 (x 0xb2).  Codegen: local
 * pointers to the far members (hoisted partial bases) with the detail panel
 * declared before the slot handle (ctx r6 / pDetail r7 / hSlots r8); the
 * GameState pointer is a local for the first two reads; the ingredient def
 * is picked by if/else; the style is a ternary; the row y is unsigned; the
 * -1 for an unaffordable partial stack is assigned before the two zero
 * stores (mvn, not a subtract from the live zero); and the ingredient's
 * unassigned count reuses nOwned -- a fresh local would colour the counter
 * and the count the other way round (sl / sb).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define TAG_TRADE      0x3f4
#define INGREDIENTS    4
#define WIDGET_CONFIRM 6
#define STYLE_ON       4
#define STYLE_OFF      6
#define STYLE_LABEL    2
#define ROW_HEIGHT     16

typedef struct Ov008ItemDef {
    u8   pad_00[0xc];
    void *pName;              /* 0x0c */
    u8   pad_10[4];
    int  nItemId;             /* 0x14 */
    u8   pad_18[8];
    u16  nIconId;             /* 0x20: 1-based */
} Ov008ItemDef;

typedef struct Ov008Ingredient {
    Ov008ItemDef *pItemDef;   /* 0x00 */
    u32  nNeeded;             /* 0x04 */
} Ov008Ingredient;

typedef struct Ov008ParamRecord {
    u8   pad_00[8];
    u32  nPrice;              /* 0x08 */
    Ov008ItemDef *pItemDef;   /* 0x0c */
    int  nBonus;              /* 0x10 */
    Ov008Ingredient aIngredient[INGREDIENTS]; /* 0x14 */
} Ov008ParamRecord;

typedef struct Ov008ColumnPanel {
    int  aCell[6][8];         /* 0x00: rows 0..2 left column, 3..5 right column */
    int  nLeftSelected;       /* 0xc0 */
    int  nRightSelected;      /* 0xc4 */
    int  nLeftBase;           /* 0xc8 */
    int  nRightBase;          /* 0xcc */
} Ov008ColumnPanel;

typedef struct Ov008ShopView {
    int  nRow;                /* 0x00 */
    u8   pad_04[8];
    Ov008ParamRecord **apRows; /* 0x0c */
    u8   pad_10[0x100 - 0x10];
    int  bListReady;          /* 0x100 */
} Ov008ShopView;

typedef struct Ov008ShopDetailPanel {
    Ov008ParamRecord *pRecord; /* 0x00 */
    int  aRowCell[2 * INGREDIENTS]; /* 0x04: icons, then marks */
    u32  nQuantity;           /* 0x24 */
    int  bReady;              /* 0x28 */
} Ov008ShopDetailPanel;

typedef struct Ov008PanelContext {
    u8   pad_0000[0x5c];
    u8   tagTracker[0x7530 - 0x5c];   /* 0x005c */
    u8   widgets[0xbfb4 - 0x7530];    /* 0x7530: widget manager */
    int  hSlotsB;                     /* 0xbfb4 */
    u8   pad_bfb8[0xc214 - 0xbfb8];
    u8   tradeSurface[0x3c];          /* 0xc214 */
    u8   pad_c250[4];
    Ov008ColumnPanel columns;         /* 0xc254 */
    u8   pad_c324[0xc3c4 - 0xc324];
    Ov008ShopView view;               /* 0xc3c4 */
    u8   pad_c4c8[0xc4f4 - 0xc4c8];
    Ov008ShopDetailPanel detail;      /* 0xc4f4 */
    u8   pad_c520[0xc5c8 - 0xc520];
    void *apVarText[5];               /* 0xc5c8 */
} Ov008PanelContext;

typedef struct GameState {
    u8  pad_0000[8];
    u32 nPoints;              /* 0x008 */
    u8  pad_000c[0x810 - 0xc];
    u8  aItemCount[0x8d0];    /* 0x810 */
} GameState;

extern Ov008PanelContext *data_ov008_02090fac;
extern GameState *data_0204be18;
extern u8    data_ov008_02090ecc[];                                      /* "/" text */
extern u8    data_ov008_02090ed0[];                                      /* unit text */
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8: clear */
extern void *func_ov008_02055808(void *pTracker, int nTag);              /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(void *pTracker, void *pEntry);          /* Ov008_TagTracker_InvokeCallback */
extern void *func_ov008_02054788(void *pManager, int nId);               /* FindEntryById */
extern void  func_ov008_02054ba4(void *pManager, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern int   func_ov008_02082234(Ov008ParamRecord *pRecord);             /* stock cap */
extern int   func_ov008_0208b0bc(Ov008ParamRecord *pRecord);             /* GetChildField14OrNeg1: item id */
extern void  func_ov008_02083c44(Ov008ParamRecord *pRecord, int nCount); /* Ov008_DrawCounterPanel */
extern void  func_02032710(int hSlots, int nCell, int bVisible);         /* Slot_SetVisible */
extern void  func_020325ec(int hSlots, int nCell, u32 nFrame);           /* Slot_ForwardToEntry */
extern char  func_ov008_0208b148(int nItemId);                           /* Ov008_CountUnassignedCopies */
extern void  func_ov008_02082d44(void *pSurface, void *pText, int nX, int nY, int nStyle, int nShadow); /* Ov008_DrawStringShadowed */
extern void  func_ov008_02082d98(void *pSurface, u32 nValue, int nX, int nY, int nStyle); /* draw a number */
extern void  func_ov008_02082df0(void *pSurface, int nValue, int nX, int nY, int nColour); /* Ov008_DrawNumber3Shadowed */

void func_ov008_020869a4(void)
{
    Ov008PanelContext *ctx;
    Ov008ShopDetailPanel *pDetail;
    int hSlots;
    u8 *pSurface;
    u8 *pWidgets;
    Ov008ColumnPanel *pColumns;
    Ov008ShopView *pView;
    Ov008ParamRecord *pRecord;
    int nCap;
    GameState *pState;
    int nOwned;
    int nTotal;
    int i;
    Ov008ItemDef *pIngredient;
    int nStyle;
    u32 nY;

    ctx = data_ov008_02090fac;
    hSlots = ctx->hSlotsB;
    pDetail = &ctx->detail;
    pSurface = ctx->tradeSurface;
    pColumns = &ctx->columns;
    pView = &ctx->view;
    pWidgets = ctx->widgets;
    func_0203011c(pSurface, 8, 0x10, 0xb6, 0x70);
    if (pDetail->bReady == 0) {
        func_ov008_0205589c(ctx->tagTracker, func_ov008_02055808(ctx->tagTracker, TAG_TRADE));
        pDetail->bReady = 1;
    }
    if (pView->bListReady != 0) {
        if (pView->apRows == 0) {
            pColumns->nLeftSelected = 0;
            pColumns->nLeftBase = 0;
            func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), 0);
            pDetail->pRecord = 0;
        } else {
            pRecord = pView->apRows[pView->nRow];
            pDetail->pRecord = pRecord;
            nCap = func_ov008_02082234(pRecord);
            pState = data_0204be18;
            nOwned = pState->aItemCount[func_ov008_0208b0bc(pDetail->pRecord)];
            pRecord = pDetail->pRecord;
            nTotal = nOwned + pRecord->nBonus;
            if (pRecord->nPrice <= pState->nPoints) {
                if (pDetail->pRecord->nBonus + data_0204be18->aItemCount[func_ov008_0208b0bc(pRecord)] > (u32)nCap) {
                    pDetail->nQuantity = nOwned;
                    pColumns->nLeftSelected = 0;
                    pColumns->nLeftBase = 0;
                    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), 0);
                } else {
                    if (nTotal > nCap) {
                        nTotal = nCap;
                    }
                    pDetail->nQuantity = nTotal;
                    pColumns->nLeftSelected = 2;
                    pColumns->nLeftBase = -pDetail->pRecord->nPrice;
                    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), 1);
                }
                func_ov008_02083c44(pDetail->pRecord, pDetail->nQuantity);
            } else {
                if (nOwned < nCap) {
                    nOwned = -1;
                }
                pColumns->nLeftSelected = 0;
                pColumns->nLeftBase = 0;
                func_ov008_02083c44(pDetail->pRecord, nOwned);
                func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), 0);
            }
        }
        pView->bListReady = 0;
    }
    for (i = 0; i < INGREDIENTS; i++) {
        func_02032710(hSlots, pDetail->aRowCell[i], 0);
        func_02032710(hSlots, pDetail->aRowCell[INGREDIENTS + i], 0);
        if (pDetail->pRecord == 0) {
            pIngredient = 0;
        } else {
            pIngredient = pDetail->pRecord->aIngredient[i].pItemDef;
        }
        if (pView->apRows != 0 && pIngredient != 0) {
            if (pIngredient->nIconId != 0) {
                func_02032710(hSlots, pDetail->aRowCell[i], 1);
                func_020325ec(hSlots, pDetail->aRowCell[i], (u16)(pIngredient->nIconId - 1));
                func_02032710(hSlots, pDetail->aRowCell[INGREDIENTS + i], data_0204be18->aItemCount[pIngredient->nItemId] != func_ov008_0208b148(pIngredient->nItemId));
            }
            nOwned = func_ov008_0208b148(pIngredient->nItemId);   /* the ingredient's unassigned copies */
            nStyle = (u32)nOwned >= pDetail->pRecord->aIngredient[i].nNeeded ? STYLE_ON : STYLE_OFF;
            nY = (i + 1) * ROW_HEIGHT;
            func_ov008_02082d44(pSurface, pIngredient->pName, 0x1a, nY + 0xb, nStyle, 8);
            func_ov008_02082d44(pSurface, data_ov008_02090fac->apVarText[4], 0x82, nY + 0xb, nStyle, 8);
            func_ov008_02082d98(pSurface, pDetail->pRecord->aIngredient[i].nNeeded, 0x9a, nY + 0xb, nStyle);
            func_ov008_02082d44(pSurface, data_ov008_02090ecc, 0x9e, nY + 0xb, STYLE_LABEL, 8);
            func_ov008_02082df0(pSurface, nOwned, 0xa2, nY + 0xb, STYLE_LABEL);
            func_ov008_02082d44(pSurface, data_ov008_02090ed0, 0xb2, nY + 0xb, STYLE_LABEL, 8);
        }
    }
}
