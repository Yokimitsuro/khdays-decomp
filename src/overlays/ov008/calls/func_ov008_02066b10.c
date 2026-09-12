/* func_ov008_02066b10 -- Ov008_MenuKeyCancel: the grid menu's cancel handler.
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

extern int  func_ov008_02050c54(void);                                    /* Ov008_GetContext */
extern void func_ov008_02055dcc(void *pOut);                              /* touch record */
extern void func_ov008_020615dc(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void *func_ov008_02054788(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void func_ov008_02054cc4(int nCtx, void *pEntry);                  /* Ov008_SwapParamOverrides */
extern void func_ov008_02062b44(Ov008MenuContext *pCtx, int nMode);
extern void func_ov008_020631cc(Ov008MenuContext *pCtx, int nMode);
extern void func_ov008_0206f7b0(int nArg);                                /* Ov008_UpdateMenuButton5 */
extern void func_ov008_02060ae8(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern void func_ov008_02066394(void);
extern void func_ov008_02065f80(void);
extern void func_ov008_0206608c(void);
extern Ov008ListHooks data_ov008_02090380;

void func_ov008_02066b10(Ov008MenuContext *pCtx)
{
    int nCtx = func_ov008_02050c54();
    u16 touch[3];

    if (pCtx->nBusy != 0) {
        return;
    }
    if (pCtx->bDrag != 0 || pCtx->bTween != 0 || pCtx->bScroll != 0) {
        return;
    }
    func_ov008_02055dcc(touch);
    if (touch[2] != 0) {
        return;
    }
    func_ov008_020615dc(pCtx, 0);
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_DRAG), 0);
    if (pCtx->nPending == 1) {
        func_ov008_02054cc4(nCtx, 0);
        func_ov008_02062b44(pCtx, 0);
        if (pCtx->bSecondaryPanel == 0) {
            func_ov008_020631cc(pCtx, 0);
        }
        data_ov008_02090380.pfnDone = func_ov008_02066394;
        data_ov008_02090380.pfnSelect = func_ov008_02065f80;
        data_ov008_02090380.pfnCancel = func_ov008_0206608c;
    } else {
        func_ov008_02062b44(pCtx, 1);
        func_ov008_0206f7b0(1);
        func_ov008_02060ae8(pCtx);
    }
    func_02033b78(0, SOUND_CANCEL);
}
