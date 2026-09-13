/* func_ov026_0208c2d8 -- Ov008_ShopDetailConfirmTick: one frame of the shop
 * detail panel's confirm dialog; returns the next handler (020896b4 when the
 * dialog closes) or 0.  The input source (+0xc0fc) is unloaded and read and
 * the touch state updated.  A pending confirmation (+0xc538) is carried out:
 * selection (+0xc534) set to 1, widgets 7 / 8 shown and 1 hidden, the
 * record's price (+0x8) taken from the points, the two words +0xc31c / +0xc314
 * cleared, the synthesis order committed, the columns redrawn, widget 6 of
 * the second widget context hidden and the record applied with -1.
 * Otherwise on selection 0 the choice (+0xc53c) is toggled by buttons 0x20 /
 * 0x10 (sound 0), taken from key A (current choice) or B (1), or from a touch
 * (+0xc118) on box 0208fe74 (0) / 0208fe78 (1); choice 0 plays 0x3d and
 * marks the confirmation, choice 1 plays 3 and closes.  On any other
 * selection keys 0xb or a touch play sound 0, hide widgets 7 / 8 and close.
 * The detail panel and the display are then redrawn.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define BTN_SWAP_A   0x20
#define BTN_SWAP_B   0x10
#define KEY_A        1
#define KEY_B        2
#define KEY_CLOSE    0xb
#define SOUND_MOVE   0
#define SOUND_CANCEL 3
#define SOUND_BUY    0x3d
#define CHOICE_NONE  (-1)

typedef struct Ov008ParamRecord {
    u8  pad_00[8];
    u32 nPrice;               /* 0x08 */
} Ov008ParamRecord;

typedef struct Ov008ShopDetailPanel {
    Ov008ParamRecord *pRecord; /* 0x00 */
    u8  pad_04[0x40 - 4];
    int nSelection : 16;      /* 0x40 */
    int pad_40 : 16;
    u16 bConfirmed;           /* 0x44 */
    u8  pad_46[2];
    int nChoice;              /* 0x48 */
} Ov008ShopDetailPanel;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x2ab0];
    u8  widgets[0x7530 - 0x2ab0]; /* 0x2ab0 */
    u8  widgetsB[0xc0fc - 0x7530]; /* 0x7530 */
    u16 inputSource;          /* 0xc0fc */
    u8  pad_c0fe[0xc118 - 0xc0fe];
    int bTouch;               /* 0xc118 */
    u8  pad_c11c[0xc314 - 0xc11c];
    int nHold314;             /* 0xc314 */
    u8  pad_c318[4];
    int nHold31c;             /* 0xc31c */
    u8  pad_c320[0xc4f4 - 0xc320];
    Ov008ShopDetailPanel detail;  /* 0xc4f4 */
} Ov008PanelContext;

typedef struct GameState {
    u8  pad_00[8];
    int nPoints;              /* 0x08 */
} GameState;

extern Ov008PanelContext *data_ov026_02091368;
extern GameState *data_0204be18;
extern u16 data_0204c190;                                         /* keys pressed */
extern u8  data_ov026_020910cc[];                                 /* choice 0 box */
extern u8  data_ov026_020910d0[];                                 /* choice 1 box */
extern void  FS_UnloadOverlayImage_0x020362ec(u16 *pSource);
extern u16   func_020362fc(const u16 *pSource);                   /* ReadU16 */
extern void  func_ov026_02085aa4(void);                           /* Ov008_UpdateTouchState */
extern void *func_ov026_0208427c(void *pWidgets, int nId);        /* FindEntryById */
extern void  func_ov026_020843e8(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov026_0208e178(Ov008ParamRecord *pRecord);      /* Ov008_CommitSynthesisOrder */
extern void  func_ov026_02089854(void);
extern void  func_ov026_02086210(void);                           /* Ov008_RedrawBothColumns */
extern void  func_ov026_02086af4(Ov008ParamRecord *pRecord, u32 nQuantity);
extern void  func_02033b78(int nKind, int nSound);                /* PlaySound */
extern int   func_ov026_02085b9c(u8 *pBox);                       /* Ov008_CursorInBox */
extern void  func_ov026_0208a010(void);                           /* Ov008_DrawShopDetailPanel */
extern void  func_ov026_0208a774(void);                           /* Ov008_RefreshPanelDisplay */
extern void *func_ov026_0208c564(void);                           /* next handler */

void *func_ov026_0208c2d8(void)
{
    Ov008PanelContext *ctx;
    Ov008ShopDetailPanel *pPanel;
    void *pNext;
    int nChoice;
    u8 *pWidgets;
    u8 *pWidgetsB;
    u16 nButtons;
    u16 nKeys;

    ctx = data_ov026_02091368;
    pNext = 0;
    nChoice = CHOICE_NONE;
    pPanel = &ctx->detail;
    pWidgets = ctx->widgets;
    pWidgetsB = ctx->widgetsB;
    FS_UnloadOverlayImage_0x020362ec(&ctx->inputSource);
    nButtons = func_020362fc(&ctx->inputSource);
    func_ov026_02085aa4();
    if (pPanel->bConfirmed != 0) {
        pPanel->bConfirmed = 0;
        pPanel->nSelection = 1;
        func_ov026_020843e8(pWidgets, func_ov026_0208427c(pWidgets, 7), 1);
        func_ov026_020843e8(pWidgets, func_ov026_0208427c(pWidgets, 8), 1);
        func_ov026_020843e8(pWidgets, func_ov026_0208427c(pWidgets, 1), 0);
        data_0204be18->nPoints -= pPanel->pRecord->nPrice;
        ctx->nHold31c = 0;
        ctx->nHold314 = 0;
        func_ov026_0208e178(pPanel->pRecord);
        func_ov026_02089854();
        func_ov026_02086210();
        func_ov026_020843e8(pWidgetsB, func_ov026_0208427c(pWidgetsB, 6), 0);
        func_ov026_02086af4(pPanel->pRecord, -1);
    } else if (pPanel->nSelection == 0) {
        if ((nButtons & BTN_SWAP_A) || (nButtons & BTN_SWAP_B)) {
            pPanel->nChoice ^= 1;
            func_02033b78(0, SOUND_MOVE);
        } else {
            nKeys = data_0204c190;
            if (nKeys & KEY_A) {
                nChoice = pPanel->nChoice;
            } else if (nKeys & KEY_B) {
                nChoice = 1;
            }
        }
        if (nChoice < 0 && ctx->bTouch != 0) {
            if (func_ov026_02085b9c(data_ov026_020910cc) != 0) {
                nChoice = 0;
                pPanel->nChoice = 0;
            } else if (func_ov026_02085b9c(data_ov026_020910d0) != 0) {
                nChoice = 1;
                pPanel->nChoice = 1;
            }
        }
        if (nChoice == 0) {
            func_02033b78(0, SOUND_BUY);
            pPanel->bConfirmed = 1;
        } else if (nChoice == 1) {
            func_02033b78(0, SOUND_CANCEL);
            pNext = func_ov026_0208c564;
        }
    } else {
        if ((data_0204c190 & KEY_CLOSE) != 0 || ctx->bTouch != 0) {
            func_02033b78(0, SOUND_MOVE);
            func_ov026_020843e8(pWidgets, func_ov026_0208427c(pWidgets, 7), 0);
            func_ov026_020843e8(pWidgets, func_ov026_0208427c(pWidgets, 8), 0);
            pNext = func_ov026_0208c564;
        }
    }
    func_ov026_0208a010();
    func_ov026_0208a774();
    return pNext;
}
