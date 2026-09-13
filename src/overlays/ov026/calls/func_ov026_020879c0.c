/* func_ov026_020879c0 -- Ov008_DrawShopRowText: draw the texts of shop row
 * nRow for record pRecord on the panel's text surface (+0xc160, 16 px per
 * row).  The price style (4 = available, 6 = greyed) follows the tab
 * (+0xc250): 0 (buy) wants munny for the price (+0x8), no level flag (+0x28)
 * and the stock cap (02082234) above the owned count (GameState 0x810);
 * 1 (sell) wants a sellable item def (+0x8e) with spare copies (0208b0d0);
 * 2 wants points, the cap and the requirements (020830c8); 3 (recipes) is
 * available past the category price cap (+0xc574 + 2 * category, +0x6) or
 * with a level requirement (+0x20).  On tab 3 the price (or the "sold out"
 * text 02090eb0) is drawn at x 0xd0 while scroll (+0xc3c8) + row is below
 * the category's free count (+0xc578 + 2 * +0xc3c0), then the recipe text
 * (+0x18, or 02090eb8 with a level requirement or past the count) at x
 * 0x22.  Otherwise the item name (def +0xc) goes at x 0x3a; an unsellable
 * item on tab 1 draws variable text 3 (+0xc5d4) greyed at x 0xac, any other
 * case but "tab 0 with the level flag" draws the price there; the font
 * (surface +0x20) becomes +0xc154 in modes 1 / 4 off tab 0 and mode 5 on
 * tab 0 (02024e5c), else +0xc148; variable text 0 (+0xc5c8) is drawn at x
 * 0xae off tab 0, text 1 (+0xc5cc) on tab 0 without the level flag; the
 * font returns to +0xc13c.  Codegen: the styles are ternaries (if/else
 * hands ctx the top register); the tab-0 draw condition re-tests the tab
 * (its dead branch survives); the listed test is an int bool; the two texts
 * are arrays (their addresses are the arguments); recipe block in the else.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define TAB_BUY      0
#define TAB_SELL     1
#define TAB_TRADE    2
#define TAB_RECIPES  3
#define STYLE_ON     4
#define STYLE_OFF    6
#define STYLE_LABEL  2
#define ROW_HEIGHT   16

typedef struct Ov008ItemDef {
    u8   pad_00[0xc];
    void *pName;              /* 0x0c */
    u8   pad_10[4];
    int  nItemId;             /* 0x14 */
    u8   pad_18[0x8e - 0x18];
    u16  nSellable;           /* 0x8e */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8   pad_00[6];
    u16  nRecipeCategory;     /* 0x06: recipe view */
    u32  nPrice;              /* 0x08 */
    Ov008ItemDef *pItemDef;   /* 0x0c */
    u8   pad_10[8];
    void *pRecipeText;        /* 0x18: recipe view */
    u8   pad_1c[4];
    int  nLevelReq;           /* 0x20 */
    u8   pad_24[4];
    int  bLevelReached;       /* 0x28 */
} Ov008ParamRecord;

typedef struct Ov008TileSurface {
    u8   pad_00[0x20];
    void *pFont;              /* 0x20 */
    u8   pad_24[0x3c - 0x24];
} Ov008TileSurface;

typedef struct Ov008PanelContext {
    u8   pad_0000[0xc13c];
    u8   fontA[0xc];          /* 0xc13c */
    u8   fontB[0xc];          /* 0xc148 */
    u8   fontC[0xc];          /* 0xc154 */
    Ov008TileSurface textSurface; /* 0xc160 */
    u8   pad_c19c[0xc250 - 0xc19c];
    int  nTab;                /* 0xc250 */
    u8   pad_c254[0xc3c0 - 0xc254];
    int  nCategory;           /* 0xc3c0 */
    u8   pad_c3c4[4];
    int  nScroll;             /* 0xc3c8 */
    u8   pad_c3cc[0xc574 - 0xc3cc];
    u16  aPriceCap[2];        /* 0xc574: per category */
    u16  aFreeCount[2];       /* 0xc578: per category */
    u8   pad_c57c[0xc5c8 - 0xc57c];
    void *apVarText[5];       /* 0xc5c8 */
} Ov008PanelContext;

typedef struct GameState {
    u8  pad_0000[8];
    u32 nPoints;              /* 0x008 */
    u32 nMunny;               /* 0x00c */
    u8  pad_0010[0x810 - 0x10];
    u8  aItemCount[0x8d0];    /* 0x810 */
} GameState;

extern Ov008PanelContext *data_ov026_02091368;
extern GameState *data_0204be18;
extern u8    data_ov026_0209131c[];                                      /* "sold out" text */
extern u8    data_ov026_02091324[];                                      /* locked recipe text */
extern int   func_02024e5c(void);                                        /* LoadGlobalShort_0204c1ec */
extern int   func_ov026_020850e4(Ov008ParamRecord *pRecord);             /* stock cap */
extern char  func_ov026_0208df80(Ov008ParamRecord *pRecord);             /* Ov008_CountSpareItemsOfChild */
extern int   func_ov026_02085f78(Ov008ParamRecord *pRecord);             /* Ov008_AreRequirementsMet */
extern void  func_ov026_02085bf4(Ov008TileSurface *pSurface, void *pText, int nX, int nY, int nStyle, int nShadow); /* Ov008_DrawStringShadowed */
extern void  func_ov026_02085c48(Ov008TileSurface *pSurface, u32 nValue, int nX, int nY, int nStyle); /* Ov008_BuildTable9AndDelegate: draw a number */

void func_ov026_020879c0(int nRow, Ov008ParamRecord *pRecord)
{
    Ov008PanelContext *ctx;
    int nY;
    Ov008TileSurface *pSurface;
    int nMode;
    int nStyle;
    int bListed;
    void *pText;

    ctx = data_ov026_02091368;
    pSurface = &ctx->textSurface;
    nY = nRow * ROW_HEIGHT;
    nMode = func_02024e5c();
    switch (ctx->nTab) {
    case TAB_BUY:
        nStyle = (pRecord->nPrice <= data_0204be18->nMunny && pRecord->bLevelReached == 0
            && data_0204be18->aItemCount[pRecord->pItemDef->nItemId] < func_ov026_020850e4(pRecord)) ? STYLE_ON : STYLE_OFF;
        break;
    case TAB_SELL:
        nStyle = (pRecord->pItemDef->nSellable == 1 && func_ov026_0208df80(pRecord) > 0) ? STYLE_ON : STYLE_OFF;
        break;
    case TAB_TRADE:
        nStyle = (pRecord->nPrice <= data_0204be18->nPoints
            && data_0204be18->aItemCount[pRecord->pItemDef->nItemId] < func_ov026_020850e4(pRecord)
            && func_ov026_02085f78(pRecord) != 0) ? STYLE_ON : STYLE_OFF;
        break;
    case TAB_RECIPES:
        nStyle = (pRecord->nPrice > ctx->aPriceCap[pRecord->nRecipeCategory] || pRecord->nLevelReq != 0) ? STYLE_ON : STYLE_OFF;
        break;
    }
    if (ctx->nTab != TAB_RECIPES) {
        func_ov026_02085bf4(pSurface, pRecord->pItemDef->pName, 0x3a, nY + 0x1b, nStyle, 8);
        if (ctx->nTab == TAB_SELL && pRecord->pItemDef->nSellable == 0) {
            func_ov026_02085bf4(pSurface, data_ov026_02091368->apVarText[3], 0xac, nY + 0x1b, STYLE_OFF, 0x20);
        } else if (ctx->nTab != TAB_BUY || pRecord->bLevelReached == 0) {
            func_ov026_02085c48(pSurface, pRecord->nPrice, 0xac, nY + 0x1b, nStyle);
        }
        if (((nMode == 1 || nMode == 4) && ctx->nTab != TAB_BUY) || (nMode == 5 && ctx->nTab == TAB_BUY)) {
            pSurface->pFont = ctx->fontC;
        } else {
            pSurface->pFont = ctx->fontB;
        }
        if (ctx->nTab != TAB_BUY) {
            func_ov026_02085bf4(pSurface, data_ov026_02091368->apVarText[0], 0xae, nY + 0x1d, STYLE_LABEL, 8);
        } else if (ctx->nTab != TAB_BUY || pRecord->bLevelReached == 0) {
            func_ov026_02085bf4(pSurface, data_ov026_02091368->apVarText[1], 0xae, nY + 0x1d, STYLE_LABEL, 8);
        }
        pSurface->pFont = ctx->fontA;
    } else {
        bListed = ctx->nScroll + nRow < ctx->aFreeCount[ctx->nCategory];
        if (bListed) {
            func_ov026_02085c48(pSurface, pRecord->nPrice, 0xd0, nY + 0x1b, nStyle);
        } else {
            func_ov026_02085bf4(pSurface, data_ov026_0209131c, 0xd0, nY + 0x1b, nStyle, 0x20);
        }
        if (bListed && pRecord->nLevelReq == 0) {
            pText = pRecord->pRecipeText;
        } else {
            pText = data_ov026_02091324;
        }
        func_ov026_02085bf4(pSurface, pText, 0x22, nY + 0x1b, nStyle, 8);
    }
}
