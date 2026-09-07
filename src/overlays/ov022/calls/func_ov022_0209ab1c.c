/* ov022: decide whether the actor gets knocked into a stun.
 *
 * The per-frame tick calls this after the state function has run and stores a
 * non-zero result back into the state slot, so what it returns is a state
 * function.
 *
 * It first flushes a pending pair when any stun flag is up and either the
 * animation has run far enough or the hit was unblockable. Then it picks
 * between the guard break, the heavy stun and the light stun -- and it tells an
 * ongoing stun from a fresh one by comparing the CURRENT state function against
 * the two stun states, which is why two function addresses sit in the pool.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 pad008[1];
    u8 nId;                      /* 0x009 */
    u8 pad00a[0x1a];
    u32 nInputMask;              /* 0x024 */
    u8 pad028[0x438];
    void *pfnState;              /* 0x460 */
    unsigned long long nFlags2;  /* 0x464 */
    u8 pad46c[0x48];
    int nStunHold;               /* 0x4b4 */
    u8 pad4b8[0x2f8];
    int nAnimFrame;              /* 0x7b0 */
};

extern void func_ov022_0209c700(struct Actor *pActor);
extern int func_ov002_02072a38(u8 nId);
extern int func_02030788(void);
extern void *func_ov022_0209d6c0(struct Actor *pActor);
extern void *func_ov022_020a35f4(struct Actor *pActor, int nState);
extern void func_ov022_020ab764(void);
extern void func_ov022_020ab810(void);

void *func_ov022_0209ab1c(struct Actor *pActor)
{
    int bGuardBreak;
    int bHeavy;
    int bStun;
    int bLight;
    void *pNext;

    bGuardBreak = 0;
    bHeavy = 0;
    bStun = 0;
    bLight = 0;
    pNext = 0;

    if ((pActor->nFlags & (1ULL << 8)) != 0
        || (pActor->nFlags & (1ULL << 17)) != 0
        || (pActor->nFlags & (1ULL << 24)) != 0) {
        return 0;
    }
    if ((pActor->nFlags2 & (1ULL << 4)) != 0
        || (pActor->nFlags2 & (1ULL << 9)) != 0
        || (pActor->nFlags2 & (1ULL << 12)) != 0
        || (pActor->nFlags2 & (1ULL << 16)) != 0) {
        bStun = 1;
    }
    if ((pActor->nFlags & (1ULL << 15)) != 0) {
        bStun = 1;
    }
    if (bStun != 0) {
        if (pActor->nAnimFrame >= 0x3000
            || (pActor->nFlags & (1ULL << 15)) != 0
            || (pActor->nFlags2 & (1ULL << 16)) != 0) {
            func_ov022_0209c700(pActor);
        }
    }

    if (func_ov002_02072a38(pActor->nId) >= 0 && func_02030788() == 0) {
        pActor->nFlags2 |= (1ULL << 51);
    }
    if ((pActor->nFlags & (1ULL << 47)) != 0) {
        pActor->nStunHold = 0x15000;
        if ((pActor->nFlags2 & (1ULL << 8)) == 0) {
            if ((pActor->nFlags & (1ULL << 4)) == 0) {
                pActor->nFlags &= ~(1ULL << 47);
            }
        }
    }

    if ((pActor->nFlags & (1ULL << 4)) != 0
        && (pActor->nFlags & (1ULL << 13)) == 0) {
        bGuardBreak = 1;
    }
    if ((pActor->nFlags & (1ULL << 13)) != 0
        && pActor->pfnState != (void *)func_ov022_020ab764) {
        bHeavy = 1;
    }
    if ((pActor->nFlags & (1ULL << 11)) != 0
        && pActor->pfnState != (void *)func_ov022_020ab810) {
        bLight = 1;
    }
    if (bGuardBreak != 0) {
        pNext = func_ov022_0209d6c0(pActor);
    } else if (bHeavy != 0) {
        pNext = func_ov022_020a35f4(pActor, 0x15);
    } else if (bLight != 0) {
        pNext = func_ov022_020a35f4(pActor, 0x1f);
    }

    if ((pActor->nInputMask & 4) != 0
        && (pActor->nFlags2 & (1ULL << 6)) == 0
        && (pActor->nFlags2 & (1ULL << 4)) == 0) {
        pActor->nFlags &= ~(1ULL << 2);
    }
    return pNext;
}
