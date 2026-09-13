/* func_ov008_02087e14 -- Ov008_ShopTabSelectTick: one frame of the shop's
 * tab selection; returns the next handler (02088114 = fade out towards the
 * chosen tab / exit, 02088178 = enter the tab) or 0.  Buttons 0x40 / 0x80
 * of the input source (+0xc0fc) move the cursor (+0xc3b0) up / down over
 * the five entries, wrapping, and skip entry 3 without the story flag
 * (+0xc5f4) and entry 2 without the session (+0xc5f0).  Key A (cursor 4 =
 * exit: fade, else enter) and key B (fade) reset the step (+0x0).  Without a
 * handler yet a touch (+0xc118) is tested against the boxes of 0208fedc
 * (from 1 unless both story and session are available, up to 4 or 5 with
 * the session); a hit takes the cursor from the row of 0208fe98 (3 x 5)
 * selected by the availability (2 both, 1 session, 0 neither).  Entering a
 * tab copies cursor 0..3 into the tab (+0xc250).  The columns are then
 * rebuilt and the display refreshed.  Codegen: the touch boxes are a 4-byte
 * struct array (walking pointer); the tab order is a 15-byte struct copy.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define BTN_UP       0x40
#define BTN_DOWN     0x80
#define KEY_A        1
#define KEY_B        2
#define SOUND_MOVE   0
#define SOUND_SELECT 1
#define SOUND_CANCEL 3
#define TAB_ENTRIES  5
#define ENTRY_EXIT   4
#define ENTRY_SESSION 2
#define ENTRY_STORY  3

typedef struct Ov008ChoiceBox {
    u8 nX;
    u8 nY;
    u8 nW;
    u8 nH;
} Ov008ChoiceBox;

typedef struct Ov008TabOrder {
    u8 aEntry[3][TAB_ENTRIES]; /* per availability: entry of each touch box */
} Ov008TabOrder;

typedef struct Ov008PanelContext {
    int nStep;                /* 0x0000 */
    u8  pad_0004[0xc0fc - 4];
    u16 inputSource;          /* 0xc0fc */
    u8  pad_c0fe[0xc118 - 0xc0fe];
    int bTouch;               /* 0xc118 */
    u8  pad_c11c[0xc250 - 0xc11c];
    int nTab;                 /* 0xc250 */
    u8  pad_c254[0xc3b0 - 0xc254];
    int nTabCursor;           /* 0xc3b0 */
    u8  pad_c3b4[0xc5f0 - 0xc3b4];
    int bReady;               /* 0xc5f0: session available */
    int bStoryPast;           /* 0xc5f4: story tab available */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern u16 data_0204c190;                                         /* keys pressed */
extern u8  data_ov008_0208fe98[];                                 /* Ov008TabOrder */
extern Ov008ChoiceBox data_ov008_0208fedc[];                      /* touch boxes */
extern void  FS_UnloadOverlayImage_0x020362ec(u16 *pSource);
extern u16   func_020362fc(const u16 *pSource);                   /* ReadU16 */
extern void  func_02033b78(int nKind, int nSound);                /* PlaySound */
extern void  func_ov008_02082bf4(void);                           /* Ov008_UpdateTouchState */
extern int   func_ov008_02082cec(Ov008ChoiceBox *pBox);           /* Ov008_CursorInBox */
extern void  func_ov008_02083654(void);                           /* Ov008_RefreshTabCursor */
extern void  func_ov008_02083360(void);                           /* Ov008_RedrawBothColumns */
extern void  func_ov008_020878c4(void);                           /* Ov008_RefreshPanelDisplay */
extern int   func_ov008_02088114(void);                           /* Ov008_FadeToBlackStep */
extern void *func_ov008_02088178(void);                           /* enter the tab */

void *func_ov008_02087e14(void)
{
    void *pNext;
    Ov008PanelContext *ctx;
    int bStoryPast;
    int bReady;
    u16 nButtons;
    Ov008TabOrder order;
    int nSet;
    int nFirst;
    int nLast;
    int i;
    u8 *pRow;
    int nCursor;

    pNext = 0;
    ctx = data_ov008_02090fac;
    bStoryPast = ctx->bStoryPast;
    bReady = ctx->bReady;
    FS_UnloadOverlayImage_0x020362ec(&ctx->inputSource);
    nButtons = func_020362fc(&ctx->inputSource);
    if (nButtons & BTN_UP) {
        func_02033b78(0, SOUND_MOVE);
        ctx->nTabCursor--;
        if (ctx->nTabCursor < 0) {
            ctx->nTabCursor = TAB_ENTRIES - 1;
        } else {
            if (bStoryPast == 0 && ctx->nTabCursor == ENTRY_STORY) {
                ctx->nTabCursor--;
            }
            if (bReady == 0 && ctx->nTabCursor == ENTRY_SESSION) {
                ctx->nTabCursor--;
            }
        }
    } else if (nButtons & BTN_DOWN) {
        func_02033b78(0, SOUND_MOVE);
        ctx->nTabCursor++;
        if (ctx->nTabCursor >= TAB_ENTRIES) {
            ctx->nTabCursor = 0;
        } else {
            if (bReady == 0 && ctx->nTabCursor == ENTRY_SESSION) {
                ctx->nTabCursor++;
            }
            if (bStoryPast == 0 && ctx->nTabCursor == ENTRY_STORY) {
                ctx->nTabCursor++;
            }
        }
    } else if (data_0204c190 & KEY_A) {
        if (ctx->nTabCursor == ENTRY_EXIT) {
            func_02033b78(0, SOUND_CANCEL);
            pNext = func_ov008_02088114;
        } else {
            func_02033b78(0, SOUND_SELECT);
            pNext = func_ov008_02088178;
        }
        ctx->nStep = 0;
    } else if (data_0204c190 & KEY_B) {
        func_02033b78(0, SOUND_CANCEL);
        pNext = func_ov008_02088114;
        ctx->nStep = 0;
    }
    func_ov008_02082bf4();
    if (pNext == 0 && ctx->bTouch != 0) {
        order = *(Ov008TabOrder *)data_ov008_0208fe98;
        if (bStoryPast & bReady) {
            nSet = 2;
        } else {
            nSet = bReady != 0;
        }
        nLast = bReady != 0 ? TAB_ENTRIES : TAB_ENTRIES - 1;
        nFirst = (bStoryPast & bReady) == 0;
        pRow = order.aEntry[nSet];
        for (i = nFirst; i < nLast; i++) {
            if (func_ov008_02082cec(&data_ov008_0208fedc[i]) != 0) {
                nCursor = pRow[i];
                ctx->nTabCursor = nCursor;
                if (nCursor == ENTRY_EXIT) {
                    func_02033b78(0, SOUND_CANCEL);
                    pNext = func_ov008_02088114;
                } else {
                    func_02033b78(0, SOUND_SELECT);
                    pNext = func_ov008_02088178;
                }
                ctx->nStep = 0;
                break;
            }
        }
    }
    if (pNext == func_ov008_02088178) {
        switch (ctx->nTabCursor) {
        case 0:
            ctx->nTab = 0;
            break;
        case 1:
            ctx->nTab = 1;
            break;
        case 2:
            ctx->nTab = 2;
            break;
        case 3:
            ctx->nTab = 3;
            break;
        }
    }
    func_ov008_02083654();
    func_ov008_02083360();
    func_ov008_020878c4();
    return pNext;
}
