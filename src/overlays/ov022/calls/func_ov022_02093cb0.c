/* ov022: step one reaction request's phase.
 *
 * Every frame the four reaction animations that are still marked pending are
 * advanced; each one that reports done clears its own bit, and any that is not
 * done keeps the request from moving on. An actor with no hit points left is
 * pushed straight to the wind-down phase.
 *
 * The phase itself then advances: phase 1 waits for the owning slot to settle
 * and either arms the request or drops it, phase 2 runs the clock until the
 * firing routine has both published and dispatched, phase 3 waits for the
 * actor's own reaction to clear before restarting the clock, and phase 5 counts
 * that clock back down to idle. The firing routine runs afterwards either way.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Anim {
    u8 pad0000[0x108];
};

struct Actor {
    u8 pad0000[0x12];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[0x450];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x250];
    int nReaction;               /* 0x06bc */
    u8 pad06c0[0x23fa];
    short nStep;                 /* 0x2aba */
};

struct Request {
    u8 nFlags;                   /* 0x0000 */
    u8 nPhase;                   /* 0x0001 */
    u8 pad0002[0xe];
    short nKind;                 /* 0x0010 */
    u8 pad0012[2];
    int nMode;                   /* 0x0014 */
    int nParam;                  /* 0x0018 */
    u32 nKindMask;               /* 0x001c */
    struct Anim aAnims[4];       /* 0x0020 */
    u8 pad0440[0x94];
    int nSlot;                   /* 0x04d4 */
    u8 pad04d8_a[0];
};

extern int func_ov022_02093bf4(struct Request *pReq);
extern int func_0202a818(struct Anim *pAnim, int nStep);
extern int func_ov022_020b1b74(int nSlot);
extern int func_ov022_020b1ba0(int nSlot);
extern int func_ov022_02083f90(void);
extern void func_ov022_02093474(struct Request *pReq);

void func_ov022_02093cb0(struct Request *pReq)
{
    int i;
    struct Actor *pActor;
    struct Anim *pAnim;
    int bAllDone;
    int bFire;

    pActor = *(struct Actor **)((u8 *)pReq + 0x4d8);
    bAllDone = 1;
    if (func_ov022_02093bf4(pReq) == 0) {
        return;
    }
    if (pActor->nHp == 0) {
        pReq->nPhase = 3;
    }
    i = 0;
    pAnim = pReq->aAnims;
    do {
        if ((pReq->nKindMask & (1 << i)) != 0) {
            if (func_0202a818(pAnim, pActor->nStep) == 0) {
                bAllDone = 0;
            } else {
                pReq->nKindMask &= ~(1 << i);
            }
        }
        i++;
        pAnim++;
    } while (i < 4);
    switch (pReq->nPhase) {
    case 1:
        if (func_ov022_020b1b74(pReq->nSlot) != 0) {
            if (pActor->nReaction == 0x1a
                && func_ov022_020b1ba0(pReq->nSlot) == 0x1a
                && (pActor->nFlags2 & 0x2000ULL) != 0) {
                pReq->nPhase = 2;
            } else {
                pReq->nPhase = 0;
            }
        }
        break;
    case 2:
        bFire = 0;
        *(int *)((u8 *)pReq + 0x4d0) += pActor->nStep;
        if (pReq->nKind < 0xc) {
            if (bAllDone != 0) {
                bFire = (pReq->nFlags & 0x10) != 0;
            }
        } else if ((pReq->nFlags & 0x20) != 0 && (pReq->nFlags & 0x10) != 0) {
            bFire = 1;
        }
        if (bFire != 0) {
            pReq->nFlags &= ~8;
            pReq->nFlags &= ~0x20;
            pReq->nFlags &= ~0x10;
            pReq->nPhase = 3;
        }
        break;
    case 3:
        if ((pActor->nFlags2 & 0x2000ULL) == 0 && pActor->nReaction != 0x1a) {
            *(int *)((u8 *)pReq + 0x4d0) = 0;
            pReq->nFlags = 1;
            pReq->nPhase = 5;
        }
        break;
    case 5:
        *(int *)((u8 *)pReq + 0x4d0) += func_ov022_02083f90();
        if (*(int *)((u8 *)pReq + 0x4d0) >= 0x9000) {
            pReq->nPhase = 0;
        }
        break;
    }
    func_ov022_02093474(pReq);
}
