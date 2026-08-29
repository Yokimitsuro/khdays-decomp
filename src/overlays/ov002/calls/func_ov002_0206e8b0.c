typedef unsigned short u16;

/* One waiting entry: its first word is the poll it answers with. */
typedef struct Ov002Waiter {
    int (*pfnPoll)(struct Ov002Waiter *pSelf);   /* +0x00 */
} Ov002Waiter;

/* Only the fields this routine touches. */
typedef struct Ov002SessionCtx {
    u16 wFlags;                         /* +0x000 */
    char pad0002[0xa];
    Ov002Waiter *apLocal[32];           /* +0x00c */
    char pad008c[0xa0];
    Ov002Waiter *apRemote[32];          /* +0x12c */
} Ov002SessionCtx;

extern Ov002SessionCtx *NNSi_FndGetCurrentRootHeap(void);
extern int func_02030694(void);
extern int func_ov002_0206b7f4(void);
extern int func_02023588(int nFlag);
extern void func_ov002_0206ef68(int nId);
extern int func_ov002_0206e888(void);

/* Find the first entry that is ready and claim it.
 *
 * Nothing happens until the session is up. Flag bit 0 hands back the entry
 * point the caller is meant to run instead, and bit 2 stops the pass outright.
 * Otherwise the leave has to be finished and the saved flag clear. The two
 * banks of thirty-two entries are then walked in turn, local first; the first
 * entry whose poll answers anything but -2 is claimed, with bit 12 set on its
 * id when it came from the remote bank.
 */
void *func_ov002_0206e8b0(void)
{
    Ov002SessionCtx *pCtx;
    Ov002Waiter **apList;
    Ov002Waiter *pWaiter;
    int i;
    int nId;
    int bRemote;

    pCtx = NNSi_FndGetCurrentRootHeap();
    if (func_02030694() == 0) {
        return 0;
    }
    if ((pCtx->wFlags & 1) > 0) {
        return (void *)func_ov002_0206e888;
    }
    if ((pCtx->wFlags & 4) > 0) {
        return 0;
    }
    if (func_ov002_0206b7f4() == 0 || func_02023588(0x2087) != 0) {
        return 0;
    }

    for (i = 0; i < 2; i++) {
        bRemote = (i != 0);
        if (bRemote) {
            apList = pCtx->apRemote;
        } else {
            apList = pCtx->apLocal;
        }
        for (nId = 0; nId < 0x20; nId++) {
            pWaiter = apList[nId];
            if (pWaiter != 0 && pWaiter->pfnPoll != 0
                    && pWaiter->pfnPoll(pWaiter) != -2) {
                if (bRemote) {
                    nId |= 0x1000;
                }
                func_ov002_0206ef68(nId);
                break;
            }
        }
    }
    return 0;
}
