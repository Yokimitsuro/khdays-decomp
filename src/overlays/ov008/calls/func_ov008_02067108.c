/* func_ov008_02067108 -- Ov008_RebindListAndFadeAfterTransfer: once the pending
 * transfer is done, close the list (and the secondary list if it is not open),
 * rebind the three list callbacks and start the fade.  Twin of 02067640, which
 * skips the secondary list.
 */
typedef unsigned char u8;

typedef struct Ov008MenuContext {
    u8   pad_0000[0x30];
    int  nTransferPending;   /* 0x30 */
    u8   pad_0034[0x18];
    int  nSecondaryOpen;     /* 0x4c */
} Ov008MenuContext;

typedef struct Ov008ListHooks {
    u8   pad_00[0x14];
    void (*pfnSelect)(void); /* 0x14 */
    void (*pfnCancel)(void); /* 0x18 */
    u8   pad_1c[8];
    void (*pfnDone)(void);   /* 0x24 */
} Ov008ListHooks;

extern Ov008MenuContext *func_ov008_02050cd4(void);            /* Ov008_GetMenuContext */
extern void func_ov008_02062b44(Ov008MenuContext *pCtx, int nMode);
extern void func_ov008_020631cc(Ov008MenuContext *pCtx, int nMode);
extern void func_02033b78(int nKind, int nArg);                 /* PlaySound */
extern void func_ov008_02066394(void);
extern void func_ov008_02065f80(void);
extern void func_ov008_0206608c(void);
extern Ov008ListHooks data_ov008_02090380;

void func_ov008_02067108(void)
{
    Ov008MenuContext *pCtx = func_ov008_02050cd4();

    if (pCtx->nTransferPending != 0) {
        return;
    }
    func_ov008_02062b44(pCtx, 0);
    if (pCtx->nSecondaryOpen == 0) {
        func_ov008_020631cc(pCtx, 0);
    }
    data_ov008_02090380.pfnDone = func_ov008_02066394;
    data_ov008_02090380.pfnSelect = func_ov008_02065f80;
    data_ov008_02090380.pfnCancel = func_ov008_0206608c;
    func_02033b78(0, 1);
}
