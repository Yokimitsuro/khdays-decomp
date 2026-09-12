/* func_ov025_02099558 -- Ov008_RebindListAndFadeAfterTransfer: once the pending
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

extern Ov008MenuContext *func_ov025_02084afc(void);            /* Ov008_GetMenuContext */
extern void func_ov025_02095070(Ov008MenuContext *pCtx, int nMode);
extern void func_ov025_020956f8(Ov008MenuContext *pCtx, int nMode);
extern void func_02033b78(int nKind, int nArg);                 /* PlaySound */
extern void func_ov025_020988c0(void);
extern void func_ov025_020984ac(void);
extern void func_ov025_020985b8(void);
extern Ov008ListHooks data_ov025_020b4d4c;

void func_ov025_02099558(void)
{
    Ov008MenuContext *pCtx = func_ov025_02084afc();

    if (pCtx->nTransferPending != 0) {
        return;
    }
    func_ov025_02095070(pCtx, 0);
    if (pCtx->nSecondaryOpen == 0) {
        func_ov025_020956f8(pCtx, 0);
    }
    data_ov025_020b4d4c.pfnDone = func_ov025_020988c0;
    data_ov025_020b4d4c.pfnSelect = func_ov025_020984ac;
    data_ov025_020b4d4c.pfnCancel = func_ov025_020985b8;
    func_02033b78(0, 1);
}
