/* func_ov025_02095070 -- Ov008_BeginMenuModeSwitch: start switching the grid
 * menu to mode nMode.  Unless the menu state (+0x10) is already 2 the grid is
 * reset and state 2 entered.  Mode 0 requests cursor mode 0x14 with 0; mode 1
 * hides widgets 400..407, 500..507, 1, 2 and 0x4a, disables the row block,
 * refreshes the equip panel from the summary (+0x1f78) and requests cursor
 * mode 0x14 with 4.  Then the grid is refreshed, widget 3 hidden, context
 * field 95fc cleared, the slide tween (+0x368) configured from 0 to -10.0
 * (fx32) over 100 frames and started, context field 9628 set, the transition
 * flag (+0x4) raised, the save-page group shown or hidden for the mode, and
 * the mode recorded (+0x8, previous one kept at +0xc).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;

#define STATE_IDLE     2
#define CURSOR_MODE_DRAG 0x14
#define WIDGET_DRAG    3
#define WIDGET_ICON    0x4a
#define ROW_WIDGET_A   400
#define ROW_WIDGET_B   500
#define ROW_WIDGET_COUNT 8
#define SLIDE_TARGET   (-0xa0000)
#define SLIDE_FRAMES   100

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    long long startTick;
    u32 flags;
} Tween;

typedef struct Ov008GridSummary {
    u8 pad[0x100];
} Ov008GridSummary;

typedef struct Ov008MenuContext {
    u8  pad_0000[4];
    int bTransition;          /* 0x0004 */
    int menuMode;             /* 0x0008 */
    int prevMenuMode;         /* 0x000c */
    int menuState;            /* 0x0010 */
    u8  pad_0014[0x368 - 0x14];
    Tween slideTween;         /* 0x0368 */
    u8  pad_0384[0x1f78 - 0x384];
    Ov008GridSummary summary; /* 0x1f78 */
} Ov008MenuContext;

extern int  func_ov025_02084a7c(void);                                    /* Ov008_GetContext */
extern void func_ov025_02093b08(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void func_ov025_020956f8(Ov008MenuContext *pCtx, int nState);      /* enter a menu state */
extern int  func_ov025_020a41f0(int nMode, int nA, int nB);               /* cursor mode request */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void func_ov025_020a4264(void);                                    /* Ov008_DisableRowBlock */
extern void func_ov025_020a4408(Ov008GridSummary *pSummary);              /* Ov008_RefreshEquipPanel */
extern void func_ov025_020a4970(void);                                    /* grid refresh */
extern void func_ov025_02084868(int nValue);                              /* Ov008_SetCtxField95fc */
extern void func_02035fb0(Tween *pTween, int nMode, int nFrom, int nTo, int nFrames); /* Tween_Configure */
extern void func_02035ffc(Tween *pTween);                                 /* Tween_Start */
extern void func_ov025_02084ccc(int nValue);                              /* Ov008_SetCtxField9628 */
extern void func_ov025_02090000(Ov008MenuContext *pCtx, int nMode);       /* Ov008_SetSavePageGroupVisible */

void func_ov025_02095070(Ov008MenuContext *pCtx, int nMode)
{
    int nCtx;
    int i;

    nCtx = func_ov025_02084a7c();
    if (pCtx->menuState != STATE_IDLE) {
        func_ov025_02093b08(pCtx, 0);
        func_ov025_020956f8(pCtx, STATE_IDLE);
    }
    switch (nMode) {
    case 0:
        func_ov025_020a41f0(CURSOR_MODE_DRAG, 0, 0);
        break;
    case 1:
        for (i = ROW_WIDGET_A; i <= ROW_WIDGET_A + ROW_WIDGET_COUNT - 1; i++) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), 0);
        }
        for (i = ROW_WIDGET_B; i <= ROW_WIDGET_B + ROW_WIDGET_COUNT - 1; i++) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), 0);
        }
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 1), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 2), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_ICON), 0);
        func_ov025_020a4264();
        func_ov025_020a4408(&pCtx->summary);
        func_ov025_020a41f0(CURSOR_MODE_DRAG, 0, 4);
        break;
    }
    func_ov025_020a4970();
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_DRAG), 0);
    func_ov025_02084868(0);
    func_02035fb0(&pCtx->slideTween, 1, 0, SLIDE_TARGET, SLIDE_FRAMES);
    func_02035ffc(&pCtx->slideTween);
    func_ov025_02084ccc(1);
    pCtx->bTransition = 1;
    func_ov025_02090000(pCtx, nMode);
    pCtx->prevMenuMode = pCtx->menuMode;
    pCtx->menuMode = nMode;
}
