typedef unsigned char u8;

typedef struct Ov002EventHandler Ov002EventHandler;
typedef struct Ov002EventSlot Ov002EventSlot;

/* Both hooks take the same three arguments; every one seen so far reads at
 * most two.  Ov002_CloseEvent asks a handler to close with mode 1, and this
 * walk reaches both kinds with mode 0. */
typedef int (*Ov002EventAskCloseFn)(Ov002EventHandler *pHandler, int nMode,
                                    int nUnused);
typedef int (*Ov002SlotRefreshFn)(Ov002EventSlot *pSlot, int nMode,
                                  int nUnused);

struct Ov002EventHandler {
    char pad0000[8];
    Ov002EventAskCloseFn pfnAskClose;   /* 0x08 */
};

struct Ov002EventSlot {
    void *pfnRun;                       /* 0x00 */
    void *pfnFree;                      /* 0x04 */
    Ov002SlotRefreshFn pfnRefresh;      /* 0x08 */
};

typedef struct {
    Ov002EventHandler *aHandlers[32];   /* 0x000 */
    Ov002EventSlot *aSlots[32];         /* 0x080 */
    u8 aFlags[32];                      /* 0x100 */
} Ov002EventBank;

typedef struct {
    char pad0000[0xc];
    Ov002EventBank aBanks[2];           /* 0x0c and 0x12c */
} Ov002EventCtx;

extern Ov002EventCtx *data_ov002_0207fa04;

/* Reaches every entry both event banks hold with mode zero: the thirty-two
 * handlers at each bank's head and the thirty-two slots behind them.
 *
 * The two walks are not guarded alike.  A handler is called only when the very
 * hook about to run is set; a slot is tested on its run hook and then called
 * through its refresh hook, so a slot carrying one without the other would
 * jump through nothing.  Every slot the tree builds sets all three.
 */
void func_ov002_0206ea24(void)
{
    Ov002EventCtx *pCtx;
    Ov002EventBank *pBank;
    Ov002EventHandler *pHandler;
    int j;
    int i;
    Ov002EventSlot *pSlot;

    i = 0;
    pCtx = data_ov002_0207fa04;
    do {
        if (i == 0) {
            pBank = &pCtx->aBanks[0];
        } else {
            pBank = &pCtx->aBanks[1];
        }
        j = 0;
        do {
            pHandler = pBank->aHandlers[j];
            pSlot = pBank->aSlots[j];
            if (pHandler != 0 && pHandler->pfnAskClose != 0) {
                pHandler->pfnAskClose(pHandler, 0, 0);
            }
            if (pSlot != 0 && pSlot->pfnRun != 0) {
                pSlot->pfnRefresh(pSlot, 0, 0);
            }
            j++;
        } while (j < 32);
        i++;
    } while (i < 2);
}
