/* func_ov008_02065664 -- Ov008_FinishMenuModeSwitch: complete a grid menu
 * mode switch once the slide tween (+0x368) has finished (flag bit 2 set) and
 * both scroll sentinels (+0x384, +0x388) reached 0x7fffffff.  The grid is
 * hidden and the parameter overrides cleared; mode 0 (grid) invokes tag 2 of
 * block 9500, shows widget 0x28 (and 3 in menu state 2), changes to the
 * current page (+0x70), pushes subitem set 1 of widgets 0x50..0x5f, shows the
 * seven widgets listed at 0208f1cc (0x37 / 0x38 too with the secondary panel,
 * +0x4c), redraws the value surface (+0xac) with slot 10 and sets +0x1c and
 * the u16 at +0x38c (0x99); mode 1 (list) invokes tag 9, refreshes the list
 * screen and clears the three list hooks (02090380) and +0x1c.  Then slot 10
 * is marked used, the slide tween runs back from -10.0 (fx32) to 0 over 100
 * frames and the transition word (+0x4) becomes 2.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;

#define TWEEN_DONE     0x7fffffff
#define SLIDE_START    (-0xa0000)
#define SLIDE_FRAMES   100
#define MODE_GRID      0
#define MODE_LIST      1
#define STATE_IDLE     2
#define WIDGET_COUNT   7

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    long long startTick;
    u32 bPending : 1;
    u32 bStarted : 1;
    u32 bDone : 1;
    u32 rest : 29;
} Tween;

typedef struct Ov008WidgetList {
    int aId[WIDGET_COUNT];
} Ov008WidgetList;

typedef struct Ov008ListHooks {
    u8   pad_00[0x14];
    void (*pfnSelect)(void); /* 0x14 */
    void (*pfnCancel)(void); /* 0x18 */
    u8   pad_1c[8];
    void (*pfnDone)(void);   /* 0x24 */
} Ov008ListHooks;

typedef struct Ov008MenuContext {
    u8  pad_0000[4];
    int bTransition;          /* 0x0004 */
    int menuMode;             /* 0x0008 */
    int prevMenuMode;         /* 0x000c */
    int menuState;            /* 0x0010 */
    u8  pad_0014[8];
    int bShown;               /* 0x001c */
    u8  pad_0020[0x4c - 0x20];
    int bSecondaryPanel;      /* 0x004c */
    u8  pad_0050[0x70 - 0x50];
    int nPage;                /* 0x0070 */
    u8  pad_0074[0xac - 0x74];
    u8  valueSurface[0x3c];   /* 0x00ac */
    u8  pad_00e8[0x368 - 0xe8];
    Tween slideTween;         /* 0x0368 */
    int nScrollTargetA;       /* 0x0384 */
    int nScrollTargetB;       /* 0x0388 */
    u16 nSlideStep;           /* 0x038c */
} Ov008MenuContext;

extern const Ov008WidgetList data_ov008_0208f1cc;
extern Ov008ListHooks data_ov008_02090380;
extern int   func_ov008_02050c28(void);                                   /* Ov008_GetCtxBlock9500 */
extern int   func_ov008_02050c54(void);                                   /* Ov008_GetContext */
extern void  func_ov008_02065294(Ov008MenuContext *pCtx);                 /* Ov008_HideGridMenu */
extern void  func_ov008_02054cc4(int nCtx, void *pEntry);                 /* Ov008_SwapParamOverrides */
extern void *func_ov008_02055808(int nTracker, int nTag);                 /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(int nTracker, void *pCell);              /* Ov008_TagTracker_InvokeCallback */
extern void *func_ov008_02054788(int nCtx, int nId);                      /* FindEntryById */
extern void  func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);   /* SetEntrySlotsVisible */
extern int   func_ov008_02063018(Ov008MenuContext *pCtx, int nPage);      /* Ov008_Menu_ChangePage */
extern void  func_ov008_02054b18(int nCtx, void *pEntry, int nValue);     /* Ov008_PushSubitemSet */
extern int   func_ov008_02050c7c(int nSlot);                              /* Ov008_ResetEntry */
extern void  func_0203034c(void *pSurface, int hLayer, int nX, int nY, int nPalette); /* Draw_ScaledValue */
extern void  func_ov008_02063790(Ov008MenuContext *pCtx, int nArg);       /* list screen refresh */
extern void  func_ov008_02050b3c(int nSlot);                              /* Ov008_MarkSlotUsed */
extern void  func_02035fb0(Tween *pTween, int nMode, int nFrom, int nTo, int nFrames); /* Tween_Configure */
extern void  func_02035ffc(Tween *pTween);                                /* Tween_Start */

void func_ov008_02065664(Ov008MenuContext *pCtx)
{
    Ov008WidgetList widgets;
    int nTracker;
    int nCtx;
    int i;

    widgets = data_ov008_0208f1cc;
    if (pCtx->slideTween.bDone == 0) {
        return;
    }
    if (pCtx->nScrollTargetA != TWEEN_DONE || pCtx->nScrollTargetB != TWEEN_DONE) {
        return;
    }
    nTracker = func_ov008_02050c28();
    nCtx = func_ov008_02050c54();
    func_ov008_02065294(pCtx);
    func_ov008_02054cc4(nCtx, 0);
    switch (pCtx->menuMode) {
    case MODE_GRID:
        func_ov008_0205589c(nTracker, func_ov008_02055808(nTracker, 2));
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x28), 1);
        if (pCtx->menuState == STATE_IDLE) {
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 3), 1);
        }
        func_ov008_02063018(pCtx, pCtx->nPage);
        for (i = 0x50; i <= 0x5f; i++) {
            func_ov008_02054b18(nCtx, func_ov008_02054788(nCtx, i), 1);
        }
        for (i = 0; i < WIDGET_COUNT; i++) {
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, widgets.aId[i]), 1);
        }
        if (pCtx->bSecondaryPanel != 0) {
            for (i = 0x37; i <= 0x38; i++) {
                func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i), 1);
            }
        }
        func_0203034c(pCtx->valueSurface, func_ov008_02050c7c(10), 3, 0xd, 0);
        pCtx->bShown = 1;
        pCtx->nSlideStep = 0x99;
        break;
    case MODE_LIST:
        func_ov008_0205589c(nTracker, func_ov008_02055808(nTracker, 9));
        func_ov008_02063790(pCtx, 0);
        data_ov008_02090380.pfnDone = 0;
        data_ov008_02090380.pfnSelect = 0;
        data_ov008_02090380.pfnCancel = 0;
        pCtx->bShown = 0;
        break;
    }
    func_ov008_02050b3c(10);
    func_02035fb0(&pCtx->slideTween, 2, SLIDE_START, 0, SLIDE_FRAMES);
    func_02035ffc(&pCtx->slideTween);
    pCtx->bTransition = 2;
}
