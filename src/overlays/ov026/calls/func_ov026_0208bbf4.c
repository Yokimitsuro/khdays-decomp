/* func_ov026_0208bbf4 -- Ov008_CounterDialogInput: one frame of input on
 * the shop's buy / sell counter dialog (+0xc4c8); returns the next step
 * (020893dc) or 0.  The touch state updates (02082bf4), the input source
 * (+0xc0fc) is polled, and the shoulder-held bit (0204c18c 0xf0) shifts
 * into the repeat register (+0x28).  Selection 0 (the counter): without a
 * step and with the previous shoulder bit clear -- or with a held row
 * (+0x18) -- a touch (+0xc118) tests the four arrow boxes (0208fea7),
 * bumping the hold (+0x14) and taking the row; a continuing touch
 * (+0xc11c) on the held row's box counts the hold and repeats it every
 * rate (+0xc5de) frames past the delay (+0xc5dc), otherwise the hold /
 * row clear; a taken row maps to keys through 0208fe64.  The repeat
 * register's low bits arm (+0x2a, 1 with no row) or clear the key repeat,
 * which adds the polled keys.  Up / down (0x40 / 0x80) step the count
 * (+0xc) by one, page up / down (0x10 / 0x20 without L / R held) by ten,
 * A (0204c190 bit 1) opens the confirmation (sound 1, selection 1, state 1,
 * choice 1), B (bit 2) cancels (sound 3, next step).  Selection 1 (the
 * confirmation): without a step a touch on the yes / no boxes (0208fe84 /
 * 0208fe88) presses A / B and sets the choice; L / R (0x30) toggle the
 * choice (sound 0); A on "yes" (sound 0x181) buys on tab 0 (+0xc250: the
 * item count 0204be18 +0x810, the level +0x1168, flag 0x4db, the munny
 * +0xc less the price times the count, the record's level-reached mark
 * +0x28 when the level cap +0x20 is met) or sells on tab 1 (count down,
 * points +0x8 up to 999999), clears the column bases (+0xc31c / +0xc320)
 * and steps; A on "no" acts as B, which (sound 3) steps when the dialog
 * state is set, otherwise moves to selection 2 with state 1.  Without a
 * step the count is clamped to 1 .. the cap (02082234, less the base
 * +0x10; the level cap less the level; 1 for a formula-priced record; the
 * affordable count) on tab 0 or the spare count (0208b0d0) on tab 1, the counter
 * panel redraws (02083c44) with sound 0 on a change, and both columns
 * redraw (02083360); the dialog (0208637c) and the panel (020878c4)
 * always refresh.  Codegen: the next step is a spilled local initialised
 * from the zero of the key accumulator; its tests while only that zero
 * reaches are the ROM's `movs r0,#0; bne` (a multi-def local is not
 * folded); the pressed keys are a u16 local, the held keys re-read per
 * use; the tab tests are switches; the sold-out flag is cleared after the
 * munny update so its zero is not shared with the clamp; the repeat
 * remainder and the affordable quotient are the two halves of
 * Math_DivMod; declaration order i, nPressed, pfnNext, nRow, pBox, nKeys.
 */
typedef signed short   s16;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_COUNT       4
#define KEY_A           1
#define KEY_B           2
#define KEY_PAGE_DOWN   0x10
#define KEY_PAGE_UP     0x20
#define KEY_UP          0x40
#define KEY_DOWN        0x80
#define KEY_SHOULDERS   0xc0
#define KEY_REPEAT_MASK 0xf0
#define SOUND_CONFIRM   0x181
#define POINTS_CAP      999999
#define FLAG_ITEM_BOUGHT 0x4db
#define TAB_BUY         0
#define TAB_SELL        1

typedef void (*Ov008ShopStep)(void);

typedef struct Ov008ChoiceBox {
    u8 nX;
    u8 nY;
    u8 nW;
    u8 nH;
} Ov008ChoiceBox;

typedef struct Ov008ParamRecord {
    int nKind;                /* 0x00 */
    int nUnlockBit;           /* 0x04: record id; also indexes GameState aLevel */
    u32 nPrice;               /* 0x08 */
    u8  pad_0c[4];
    u32 nBasePrice;           /* 0x10 */
    int nExponent;            /* 0x14 */
    u32 nMaxPrice;            /* 0x18 */
    int nPrereqSlot;          /* 0x1c */
    u32 nLevelReq;            /* 0x20: level cap of the record */
    u16 nDay;                 /* 0x24 */
    u8  nDivisor;             /* 0x26 */
    u8  nTierReq;             /* 0x27 */
    int bLevelReached;        /* 0x28 */
} Ov008ParamRecord;

typedef struct Ov008SellDialog {
    Ov008ParamRecord *pRecord; /* 0x00 (0xc4c8) */
    int   hCounterA;          /* 0x04 */
    int   hCounterB;          /* 0x08 */
    int   nCount;             /* 0x0c (0xc4d4) */
    int   nBase;              /* 0x10: owned / stock base of the counter */
    u32   nHold;              /* 0x14: frames the arrow row is held */
    int   nRow;               /* 0x18: held arrow row, -1 none */
    s16   nSelection;         /* 0x1c (0xc4e4) */
    u8    nState : 4;         /* 0x1e: dialog state */
    u8    bCanBuy : 4;        /* 0x1e: the item can still be bought / sold */
    u8    nChoice;            /* 0x1f: 0 yes, 1 no */
    void *pTextLeft;          /* 0x20 */
    void *pTextRight;         /* 0x24 */
    u16   nRepeatBits;        /* 0x28: shoulder-held history, one bit per frame */
    u16   bRepeat;            /* 0x2a: key repeat armed */
} Ov008SellDialog;

typedef struct Ov008ColumnPanel {
    int  aCell[6][8];         /* 0x00 */
    int  nLeftSelected;       /* 0xc0 */
    int  nRightSelected;      /* 0xc4 */
    int  nLeftBase;           /* 0xc8 (0xc31c) */
    int  nRightBase;          /* 0xcc (0xc320) */
} Ov008ColumnPanel;

typedef struct Ov008ShopGauge {
    u8   pad_00[0x60];
    s16  nRepeatDelay;        /* 0x60 (0xc5dc) */
    s16  nRepeatRate;         /* 0x62 (0xc5de) */
} Ov008ShopGauge;

typedef struct Ov008PanelContext {
    u8   pad_0000[0xc0fc];
    u16  inputSource;         /* 0xc0fc */
    u8   pad_c0fe[0xc118 - 0xc0fe];
    int  bTouch;              /* 0xc118 */
    int  bTouchHeld;          /* 0xc11c */
    u8   pad_c120[0xc250 - 0xc120];
    int  nTab;                /* 0xc250 */
    Ov008ColumnPanel columns; /* 0xc254 */
    u8   pad_c324[0xc4c8 - 0xc324];
    Ov008SellDialog sell;     /* 0xc4c8 */
    u8   pad_c4f4[0xc57c - 0xc4f4];
    Ov008ShopGauge gauge;     /* 0xc57c */
} Ov008PanelContext;

typedef struct GameState {
    u8  pad_0000[8];
    u32 nPoints;              /* 0x008 */
    u32 nMunny;               /* 0x00c */
    u8  pad_0010[0x810 - 0x10];
    u8  aItemCount[0x1168 - 0x810]; /* 0x810: itemCounts */
    u16 aLevel[1];            /* 0x1168 */
} GameState;

extern Ov008PanelContext *data_ov026_02091368;
extern u16 data_0204c18c;                                              /* keys held */
extern u16 data_0204c190;                                              /* keys pressed */
extern GameState *data_0204be18;                                       /* g_pTallySource */
extern const Ov008ChoiceBox data_ov026_020910ff[ROW_COUNT];            /* arrow boxes */
extern const u16 data_ov026_020910bc[ROW_COUNT];                       /* keys by arrow row */
extern const Ov008ChoiceBox data_ov026_020910dc[1];                    /* yes box */
extern const Ov008ChoiceBox data_ov026_020910e0[1];                    /* no box */
extern void  func_ov026_0208c28c(void);                                /* next step after the dialog */
extern void  func_ov026_02085aa4(void);                                /* Ov008_UpdateTouchState */
extern void  FS_UnloadOverlayImage_0x020362ec(u16 *pSource);           /* poll the input source */
extern u16   func_020362fc(const u16 *pSource);                        /* ReadU16 */
extern int   func_ov026_02085b9c(const Ov008ChoiceBox *pBox);          /* Ov008_CursorInBox */
extern unsigned long long func_0202060c(u32 nNum, u32 nDen);           /* Math_DivMod: quotient low, remainder high */
extern void  func_02033b78(int nBank, int nSound);                     /* PlaySound */
extern void  func_02033b24(int nSound, int nArg);                      /* PlaySoundChecked */
extern int   func_ov026_0208df6c(Ov008ParamRecord *pRecord);           /* GetChildField14OrNeg1: item id */
extern void  func_020235a8(int nFlag);                                 /* GameState_SetFlag */
extern int   func_ov026_020850e4(Ov008ParamRecord *pRecord);           /* stock cap */
extern u8    func_ov026_0208df80(Ov008ParamRecord *pRecord);           /* Ov008_CountSpareItemsOfChild */
extern void  func_ov026_02086af4(Ov008ParamRecord *pRecord, int nOwned); /* Ov008_DrawCounterPanel */
extern void  func_ov026_02086210(void);                                /* Ov008_RedrawBothColumns */
extern void  func_ov026_0208922c(void);                                /* Ov008_DrawSellDialog */
extern void  func_ov026_0208a774(void);                                /* Ov008_RefreshPanelDisplay */

Ov008ShopStep func_ov026_0208bbf4(void)
{
    Ov008PanelContext *ctx;
    Ov008SellDialog *pDialog;
    int nTab;
    int nCountBefore;
    int i;
    u16 nPressed;
    Ov008ShopStep pfnNext;
    int nRow;
    const Ov008ChoiceBox *pBox;
    u32 nKeys;
    u32 nHold;
    u32 nDelay;
    u32 nBits;
    int nItem;
    u32 nCost;
    int bReached;
    Ov008ParamRecord *pRecord;
    u32 nPoints;
    int nCap;
    u32 nLeft;
    u8 nSpare;

    ctx = data_ov026_02091368;
    nKeys = 0;
    pfnNext = 0;
    pDialog = &ctx->sell;
    nTab = ctx->nTab;
    nCountBefore = pDialog->nCount;
    func_ov026_02085aa4();
    FS_UnloadOverlayImage_0x020362ec(&ctx->inputSource);
    nPressed = data_0204c190;
    pDialog->nRepeatBits = (pDialog->nRepeatBits << 1) | ((data_0204c18c & KEY_REPEAT_MASK) != 0);
    switch (pDialog->nSelection) {
    case 0:
        if ((pfnNext == 0 && (pDialog->nRepeatBits & 1) == 0) || pDialog->nRow >= 0) {
            nRow = -1;
            if (ctx->bTouch != 0) {
                i = 0;
                pBox = data_ov026_020910ff;
                do {
                    if (func_ov026_02085b9c(pBox) != 0) {
                        pDialog->nHold += 1;
                        pDialog->nRow = i;
                        pDialog->bRepeat = 0;
                        nRow = i;
                        break;
                    }
                    i++;
                    pBox++;
                } while (i < ROW_COUNT);
            } else if (ctx->bTouchHeld != 0 && pDialog->nHold != 0) {
                if (func_ov026_02085b9c(&data_ov026_020910ff[pDialog->nRow]) != 0) {
                    nHold = pDialog->nHold + 1;
                    pDialog->nHold = nHold;
                    nDelay = ctx->gauge.nRepeatDelay;
                    if (nHold >= nDelay && (u32)(func_0202060c(nHold - nDelay, ctx->gauge.nRepeatRate) >> 32) == 0) {
                        nRow = pDialog->nRow;
                    }
                } else {
                    pDialog->nHold = 0;
                }
            } else {
                pDialog->nHold = 0;
                pDialog->nRow = -1;
            }
            if (nRow >= 0) {
                nKeys = data_ov026_020910bc[nRow];
            }
        }
        nBits = pDialog->nRepeatBits & 3;
        if (nBits == 1 && pDialog->nRow < 0) {
            pDialog->bRepeat = 1;
        } else if (nBits == 2) {
            pDialog->bRepeat = 0;
        }
        if (pDialog->bRepeat != 0) {
            nKeys |= func_020362fc(&ctx->inputSource);
        }
        if (nKeys & KEY_UP) {
            pDialog->nCount += 1;
        } else if (nKeys & KEY_DOWN) {
            pDialog->nCount -= 1;
        } else if ((nKeys & KEY_PAGE_DOWN) && (data_0204c18c & KEY_SHOULDERS) == 0) {
            pDialog->nCount += 10;
        } else if ((nKeys & KEY_PAGE_UP) && (data_0204c18c & KEY_SHOULDERS) == 0) {
            pDialog->nCount -= 10;
        } else if (nPressed & KEY_A) {
            func_02033b78(0, 1);
            pDialog->nSelection = 1;
            pDialog->nState = 1;
            pDialog->nChoice = 1;
        } else if (nPressed & KEY_B) {
            func_02033b78(0, 3);
            pfnNext = func_ov026_0208c28c;
        }
        break;
    case 1:
        nKeys |= func_020362fc(&ctx->inputSource);
        if (pfnNext == 0 && ctx->bTouch != 0) {
            if (func_ov026_02085b9c(data_ov026_020910dc) != 0) {
                nPressed |= KEY_A;
                pDialog->nChoice = 0;
            } else if (func_ov026_02085b9c(data_ov026_020910e0) != 0) {
                nPressed |= KEY_B;
                pDialog->nChoice = 1;
            }
        }
        if (nKeys & (KEY_PAGE_DOWN | KEY_PAGE_UP)) {
            func_02033b78(0, 0);
            pDialog->nChoice ^= 1;
        } else if (nPressed & KEY_A) {
            if (pDialog->nChoice == 0) {
                func_02033b24(SOUND_CONFIRM, 1);
                switch (nTab) {
                case TAB_BUY:
                    nItem = func_ov026_0208df6c(pDialog->pRecord);
                    data_0204be18->aItemCount[nItem] += pDialog->nCount;
                    data_0204be18->aLevel[pDialog->pRecord->nUnlockBit] += pDialog->nCount;
                    func_020235a8(func_ov026_0208df6c(pDialog->pRecord) + FLAG_ITEM_BOUGHT);
                    nCost = pDialog->pRecord->nPrice * pDialog->nCount;
                    if (data_0204be18->nMunny > nCost) {
                        data_0204be18->nMunny -= nCost;
                    } else {
                        data_0204be18->nMunny = 0;
                    }
                    bReached = 0;
                    pRecord = pDialog->pRecord;
                    if (pRecord->nLevelReq != 0 && data_0204be18->aLevel[pRecord->nUnlockBit] >= pRecord->nLevelReq) {
                        bReached = 1;
                    }
                    pRecord->bLevelReached = bReached != 0;
                    break;
                case TAB_SELL:
                    nItem = func_ov026_0208df6c(pDialog->pRecord);
                    data_0204be18->aItemCount[nItem] -= pDialog->nCount;
                    data_0204be18->nPoints += pDialog->pRecord->nPrice * pDialog->nCount;
                    if (data_0204be18->nPoints > POINTS_CAP) {
                        data_0204be18->nPoints = POINTS_CAP;
                    }
                    break;
                }
                nPressed = 0;
                ctx->columns.nRightBase = 0;
                ctx->columns.nLeftBase = 0;
                pfnNext = func_ov026_0208c28c;
            } else {
                nPressed = KEY_B;
            }
        }
        if (nPressed & KEY_B) {
            func_02033b78(0, 3);
            if (pDialog->bCanBuy != 0) {
                pfnNext = func_ov026_0208c28c;
            } else {
                pDialog->nSelection = 2;
                pDialog->nState = 1;
            }
        }
        break;
    }
    if (pfnNext == 0) {
        if (pDialog->nCount < 1) {
            pDialog->nCount = 1;
        }
        switch (nTab) {
        case TAB_BUY:
            nCap = func_ov026_020850e4(pDialog->pRecord);
            pRecord = pDialog->pRecord;
            if (pRecord->nExponent != 0 && pRecord->nDivisor != 0 && pRecord->nMaxPrice != 0) {
                pDialog->nCount = 1;
            }
            pRecord = pDialog->pRecord;
            if (pRecord->nLevelReq != 0) {
                nLeft = pRecord->nLevelReq - data_0204be18->aLevel[pRecord->nUnlockBit];
                if ((u32)pDialog->nCount > nLeft) {
                    pDialog->nCount = nLeft;
                }
            }
            if (pDialog->nCount + pDialog->nBase > nCap) {
                pDialog->nCount = nCap - pDialog->nBase;
            }
            nCost = pDialog->pRecord->nPrice * pDialog->nCount;
            if (nCost > data_0204be18->nMunny) {
                pDialog->nCount = (u32)func_0202060c(data_0204be18->nMunny, pDialog->pRecord->nPrice);
            }
            func_ov026_02086af4(pDialog->pRecord, pDialog->nCount + pDialog->nBase);
            if (nCountBefore != pDialog->nCount) {
                func_02033b78(0, 0);
            }
            break;
        case TAB_SELL:
            nSpare = func_ov026_0208df80(pDialog->pRecord);
            if (pDialog->nCount > nSpare) {
                pDialog->nCount = nSpare;
            }
            func_ov026_02086af4(pDialog->pRecord, pDialog->nBase - pDialog->nCount);
            if (nCountBefore != pDialog->nCount) {
                func_02033b78(0, 0);
            }
            break;
        }
        func_ov026_02086210();
    }
    func_ov026_0208922c();
    func_ov026_0208a774();
    return pfnNext;
}
