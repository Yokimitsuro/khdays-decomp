/* ov022: pick the state the actor is forced into this frame.
 *
 * The per-frame tick calls this before running the state machine and stores a
 * non-zero result straight into the actor's state slot, so what it returns is
 * a state function, not a number.
 *
 * In order it decides: whether the actor has dropped below the floor for its
 * slot, accumulating a timer and killing it past 0x3000; whether a pending
 * forced state should be entered; the whole death path once hit points reach
 * zero, which differs between the two game modes; the guard-break state; and
 * finally the knockdown table selected by the byte at 0x2770.
 *
 * Note the flag test before the guard-break call reads only the low half of
 * the 64-bit word, unlike every other test here, so it is spelled as a cast.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 {
    int x, y, z;
};

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 nOwner;                   /* 0x008 */
    u8 pad009[9];
    u16 nHp;                     /* 0x012 */
    u8 pad014[0x52];
    short nSlotIndex;            /* 0x066 */
    u8 pad068[0x3f8];
    void *pfnState;              /* 0x460 */
    unsigned long long nFlags2;  /* 0x464 */
    u8 pad46c[8];
    int nFallTimer;              /* 0x474 */
    u8 pad478[0x14];
    struct Vec3 vecPos;          /* 0x48c */
    u8 pad498[0x1f8];
    int nPendingState;           /* 0x690 */
    u8 bSuppressDraw : 1;        /* 0x694 bit 0 */
    u8 nPad694 : 2;
    u8 bDeathHandled : 1;        /* bit 3 */
    u8 nRest694 : 4;
    u8 pad695[0x27];
    u32 nField6bc;               /* 0x6bc */
    u8 pad6c0[0x1c38];
    u8 stateBlk;                 /* 0x22f8 */
    u8 pad22f9[0x477];
    signed char nKnockdownKind;  /* 0x2770 */
};

extern u8 data_0204c240;

extern int func_ov002_020728f4(int nSlot);
extern int func_02030788(void);
extern int func_ov022_02083f90(void);
extern void func_ov022_020acc94(struct Actor *pActor, int nValue);
extern void *func_ov022_020a35f4(struct Actor *pActor, int nState);
extern void *func_ov022_0209b750(struct Actor *pActor);
extern void func_ov022_0209b1e8(struct Actor *pActor);
extern void func_ov022_020ab378(void);
extern void func_020208d0(int nArg);
extern void func_02020878(int nArg);
extern void func_ov022_0209d1c0(struct Actor *pActor);
extern void *func_ov022_0209d6c0(struct Actor *pActor);
extern int func_ov022_020954c0(u8 *pBlk);

void *func_ov022_0209a6f4(struct Actor *pActor)
{
    void *pNext;
    void *pGuard;
    int nFloor;
    int bAlive;

    pNext = 0;
    if ((pActor->nFlags & (1ULL << 24)) != 0) {
        return pNext;
    }
    nFloor = func_ov002_020728f4(pActor->nSlotIndex);
    if (pActor->vecPos.y < nFloor) {
        if (func_02030788() == 0) {
            pActor->nFlags2 |= (1ULL << 34);
        }
        pActor->nFallTimer += func_ov022_02083f90();
        if (pActor->nFallTimer >= 0x3000) {
            pActor->nFlags &= ~(1ULL << 19);
            func_ov022_020acc94(pActor, 0);
        }
    } else {
        pActor->nFallTimer = 0;
    }

    if ((pActor->nFlags & (1ULL << 28)) != 0) {
        bAlive = 1;
        if (pActor->nHp == 0) {
            bAlive = 0;
        }
        if ((pActor->nFlags & (1ULL << 13)) != 0) {
            bAlive = 0;
        }
        if (bAlive != 0) {
            if ((pActor->nFlags & (1ULL << 36)) != 0
                && (pActor->nField6bc == 0xe || pActor->nField6bc == 0xf)
                && func_02030788() == 0) {
                pActor->nFlags2 |= (1ULL << 7);
            }
            pNext = func_ov022_020a35f4(pActor, pActor->nPendingState);
        } else {
            pActor->nFlags &= ~(1ULL << 28);
        }
    }

    if ((pActor->nFlags & (1ULL << 19)) != 0) {
        if ((pActor->nFlags & (1ULL << 8)) == 0
            && (pActor->nFlags & (1ULL << 17)) == 0 && pNext == 0) {
            switch (pActor->nKnockdownKind) {
            case 0:
            case 4:
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                pNext = func_ov022_0209b750(pActor);
                break;
            default:
                break;
            }
        }
        return pNext;
    }

    if (pActor->nHp == 0) {
        func_ov022_0209b1e8(pActor);
        if ((data_0204c240 & 4) != 0) {
            if (pActor->pfnState != (void *)func_ov022_020ab378
                && (pActor->nFlags & (1ULL << 8)) == 0
                && pActor->bDeathHandled == 0) {
                pNext = func_ov022_020a35f4(pActor, 0x10);
                if (pActor->nOwner == func_02030788()) {
                    func_020208d0(0);
                    func_02020878(0);
                }
            }
        } else {
            if (func_02030788() == 0) {
                pActor->nFlags2 |= (1ULL << 27);
            }
            if ((pActor->nFlags & (1ULL << 8)) == 0) {
                func_ov022_0209d1c0(pActor);
                pActor->nFlags |= (1ULL << 8);
                if (((u32)pActor->nFlags & 0x10000) == 0) {
                    func_02020878(0);
                    pNext = func_ov022_0209d6c0(pActor);
                } else {
                    pNext = func_ov022_020a35f4(pActor, 0x1c);
                }
            }
        }
    }

    if ((pActor->nFlags & (1ULL << 23)) != 0) {
        if (pNext == 0) {
            pNext = func_ov022_020a35f4(pActor, 0x1c);
        } else {
            pActor->nFlags &= ~(1ULL << 23);
        }
    }

    if ((pActor->nFlags & (1ULL << 8)) == 0
        && (pActor->nFlags & (1ULL << 17)) == 0
        && (pActor->nFlags & (1ULL << 13)) == 0
        && (pActor->nFlags & (1ULL << 7)) == 0) {
        pGuard = func_ov022_0209b750(pActor);
        if (pNext == 0 && pGuard != 0) {
            pNext = pGuard;
        }
    }
    if (pNext == 0 && func_ov022_020954c0(&pActor->stateBlk) != 0) {
        pNext = func_ov022_020a35f4(pActor, 0x17);
    }
    return pNext;
}
