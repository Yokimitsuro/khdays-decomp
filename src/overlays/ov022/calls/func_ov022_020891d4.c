/* ov022: claim a slot from the actor's pool and place it.
 *
 * The position the caller gives is raised by the pool's own offset before it is
 * written in. A pool in the first mode hands out the first slot that is free
 * and answers with its index; a pool in the second mode hands out slots in
 * turn, wrapping the shared cursor once it passes the end, and answers with the
 * index it used. Any other mode, or a first-mode pool with nothing free,
 * answers -1.
 */

typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

#define MODE_FIRST_FREE 0
#define MODE_ROUND_ROBIN 1

struct Ov022AnimationSlot {
    u8 bInUse;                   /* 0x0000 */
    u8 pad0001[3];
    u8 anim;                     /* 0x0004 animation record */
    u8 pad0005[0xa3];
    VecFx32 vecPos;              /* 0x00a8 */
    u8 pad00b4[0x60];
};

struct Ov022RootHeap {
    u8 nFlags : 2;               /* 0x0000 bits 0 and 1 */
    u8 nCount : 6;               /* 0x0000 bits 2 to 7 */
    u8 nMode : 3;                /* 0x0001 bits 0 to 2 */
    u8 nModeFlags : 5;
    u8 pad0002[2];
    int nYOffset;                /* 0x0004 */
    u8 pad0008[4];
    struct Ov022AnimationSlot *pSlots;         /* 0x000c */
};

struct Ov022PoolOwner {
    u8 pad0000[0x20];
    struct Ov022RootHeap *pPool;          /* 0x0020 */
};

/* Shared cursor for the round-robin mode. */
extern int data_ov022_020b2ea0;

extern void func_ov022_020892f0(u8 *pAnim, int nArg);

/* Compile-time layout checks for the ARM32 target. */
typedef char Ov022Arm32Layout[
    sizeof(void *) == 4 && sizeof(int) == 4 && sizeof(VecFx32) == 12 &&
    sizeof(struct Ov022AnimationSlot) == 0x114 &&
    sizeof(struct Ov022RootHeap) == 0x10 &&
    sizeof(struct Ov022PoolOwner) == 0x24 ? 1 : -1];

#pragma push
#pragma opt_optimizecontrolflow off
int func_ov022_020891d4(struct Ov022PoolOwner *pActor, const VecFx32 *pvecPos)
{
    VecFx32 vecPos;
    struct Ov022AnimationSlot *pSlot;
    int nRet;
    int nSlot;
    struct Ov022RootHeap *pPool;
    int nCount;

    pPool = pActor->pPool;
    vecPos = *pvecPos;
    vecPos.y = vecPos.y + pPool->nYOffset;
    nRet = -1;
    switch (pPool->nMode) {
    case MODE_FIRST_FREE:
        nCount = pPool->nCount;
        nSlot = 0;
        if (nCount > 0) {
            pSlot = pPool->pSlots;
            do {
                if (pSlot->bInUse == 0) {
                    pSlot->bInUse = 1;
                    func_ov022_020892f0(&pSlot->anim, 0);
                    nRet = nSlot;
                    pSlot->vecPos = vecPos;
                    break;
                }
                nSlot++;
                pSlot++;
            } while (nSlot < nCount);
        }
        break;
    case MODE_ROUND_ROBIN: {
        int *pCursor;
        pSlot = &pPool->pSlots[data_ov022_020b2ea0];
        pSlot->bInUse = 1;
        func_ov022_020892f0(&pSlot->anim, 0);
        /* Intentional MWCC 3.0/139 matching device. This case is entered
         * with nRet == -1 and has not changed it, so this loop executes
         * exactly once and pCursor is always initialized. Together with
         * the scoped optimization setting it preserves the early cursor
         * address in r4 without introducing a premature reset constant.
         * The emitted code contains neither this test nor a loop. */
        while (nRet == -1) {
            pCursor = &data_ov022_020b2ea0;
            break;
        }
        pSlot->vecPos = vecPos;
        nRet = *pCursor;
        nSlot = nRet + 1;
        nCount = pPool->nCount;
        *pCursor = nSlot;
        if (nSlot > nCount) {
            *pCursor = 0;
        }
        break;
    }
    }
    return nRet;
}
#pragma pop
