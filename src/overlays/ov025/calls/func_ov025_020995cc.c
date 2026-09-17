/* func_ov025_020995cc -- Ov008_RebindListHooksAfterTransfer: the target slot is cleared
 * (Ov008_SetTargetSlot 02084798 0 / -1) and, once no transfer is pending (+0x30 of the menu
 * context), the three list callbacks of data_ov025_020b4d4c are rebound (done 020988c0, select
 * 020984ac, cancel 020985b8) and the confirm sound plays (02033b78 0 / 1).  Sibling of 02099558
 * without the list closing. */
typedef unsigned char  u8;

typedef struct Ov008MenuContext {
    u8   pad_0000[0x30];
    int  nTransferPending;    /* 0x30 */
} Ov008MenuContext;

typedef struct Ov008ListHooks {
    u8   pad_00[0x14];
    void (*pfnSelect)(void);  /* 0x14 */
    void (*pfnCancel)(void);  /* 0x18 */
    u8   pad_1c[8];
    void (*pfnDone)(void);    /* 0x24 */
} Ov008ListHooks;

extern Ov008MenuContext *func_ov025_02084afc(void);                 /* Ov008_GetMenuContext */
extern void  func_ov025_02084798(int nEntry, int nTarget);          /* Ov008_SetTargetSlot */
extern void  func_ov025_020988c0(void);
extern void  func_ov025_020984ac(void);
extern void  func_ov025_020985b8(void);
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern Ov008ListHooks data_ov025_020b4d4c;

void func_ov025_020995cc(void)
{
    Ov008MenuContext *pCtx;

    pCtx = func_ov025_02084afc();
    func_ov025_02084798(0, -1);
    if (pCtx->nTransferPending != 0) {
        return;
    }
    data_ov025_020b4d4c.pfnDone = func_ov025_020988c0;
    data_ov025_020b4d4c.pfnSelect = func_ov025_020984ac;
    data_ov025_020b4d4c.pfnCancel = func_ov025_020985b8;
    func_02033b78(0, 1);
}
