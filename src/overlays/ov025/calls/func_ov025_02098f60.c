/* func_ov025_02098f60 -- Ov008_MenuKeyCancel: the grid menu's cancel handler.
 * Nothing while busy (+0x30), while a drag/tween/scroll is live (+0x24/+0x28/
 * +0x2c) or with a touch down.  Resets the grid, hides widget 3, then: from
 * the sub-menu (+8 == 1) clears the parameter overrides, closes the list
 * (mode 0; the secondary list too when no secondary panel) and rebinds the
 * three list hooks; otherwise closes the list with mode 1, refreshes menu
 * button 5 and rebuilds the grid hits.  Cue 0x38 either way.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov008MenuContext {
    u8   pad_0000[0x8];
    int  nPending;            /* 0x0008: 1 = sub-menu open */
    u8   pad_000c[0x24 - 0xc];
    int  bDrag;               /* 0x0024 */
    int  bTween;              /* 0x0028 */
    int  bScroll;             /* 0x002c */
    int  nBusy;               /* 0x0030 */
    u8   pad_0034[0x4c - 0x34];
    int  bSecondaryPanel;     /* 0x004c */
} Ov008MenuContext;

typedef struct Ov008ListHooks {
    u8   pad_00[0x14];
    void (*pfnSelect)(void); /* 0x14 */
    void (*pfnCancel)(void); /* 0x18 */
    u8   pad_1c[8];
    void (*pfnDone)(void);   /* 0x24 */
} Ov008ListHooks;

#define WIDGET_DRAG 3
#define SOUND_CANCEL 0x38

extern int  func_ov025_02084a7c(void);                                    /* Ov008_GetContext */
extern void func_ov025_020899dc(void *pOut);                              /* touch record */
extern void func_ov025_02093b08(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void func_ov025_0208896c(int nCtx, void *pEntry);                  /* Ov008_SwapParamOverrides */
extern void func_ov025_02095070(Ov008MenuContext *pCtx, int nMode);
extern void func_ov025_020956f8(Ov008MenuContext *pCtx, int nMode);
extern void func_ov025_020a4d94(int nArg);                                /* Ov008_UpdateMenuButton5 */
extern void func_ov025_02093038(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern void func_ov025_020988c0(void);
extern void func_ov025_020984ac(void);
extern void func_ov025_020985b8(void);
extern Ov008ListHooks data_ov025_020b4d4c;

void func_ov025_02098f60(Ov008MenuContext *pCtx)
{
    int nCtx = func_ov025_02084a7c();
    u16 touch[3];

    if (pCtx->nBusy != 0) {
        return;
    }
    if (pCtx->bDrag != 0 || pCtx->bTween != 0 || pCtx->bScroll != 0) {
        return;
    }
    func_ov025_020899dc(touch);
    if (touch[2] != 0) {
        return;
    }
    func_ov025_02093b08(pCtx, 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_DRAG), 0);
    if (pCtx->nPending == 1) {
        func_ov025_0208896c(nCtx, 0);
        func_ov025_02095070(pCtx, 0);
        if (pCtx->bSecondaryPanel == 0) {
            func_ov025_020956f8(pCtx, 0);
        }
        data_ov025_020b4d4c.pfnDone = func_ov025_020988c0;
        data_ov025_020b4d4c.pfnSelect = func_ov025_020984ac;
        data_ov025_020b4d4c.pfnCancel = func_ov025_020985b8;
    } else {
        func_ov025_02095070(pCtx, 1);
        func_ov025_020a4d94(1);
        func_ov025_02093038(pCtx);
    }
    func_02033b78(0, SOUND_CANCEL);
}
