/* ov022: run everything the actor's frame still owes.
 *
 * The per-frame tick's catch-all step. For the local player it drives the two
 * ambient sound channels and the chip gauge, then for every actor it walks the
 * subsystem blocks in order -- reaction, effect slots, timers, trails, the
 * slot mask and the state block -- feeding each the frame delta, the facing
 * vector and the node's angle. It finishes by calling whatever update hook the
 * actor carries, and then, only for the local player, consumes a one-shot flag
 * that asks for a menu sound.
 *
 * The two ambient channels are routed differently in one area, which is why
 * the area id is fetched three times rather than cached.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 {
    int x, y, z;
};

struct Node {
    u8 pad00[0x80];
    u16 nAngle;                   /* 0x80 */
};

struct Actor;
typedef void (*PfnUpdate)(struct Actor *pActor);

struct Actor {
    unsigned long long nFlags;    /* 0x0000 */
    u8 nOwner;                    /* 0x0008 */
    u8 nId;                       /* 0x0009 */
    u8 pad00a[8];
    u16 nHp;                      /* 0x0012 */
    u8 pad014[0xc];
    struct Node *pNode;           /* 0x0020 */
    u32 nInputMask;               /* 0x0024 */
    u8 pad028[0x3e];
    short nSlotIndex;             /* 0x0066 */
    u8 collMain;                  /* 0x0068 */
    u8 pad069[0x3fb];
    unsigned long long nFlags2;   /* 0x0464 */
    u8 pad46c[0x20];
    struct Vec3 vecPos;           /* 0x048c */
    u8 pad498[0x1d4];
    PfnUpdate pfnUpdate;          /* 0x066c */
    u8 pad670[0x4c];
    int nHitReaction;             /* 0x06bc */
    u8 pad6c0[0xf8];
    int nEffectA;                 /* 0x07b8 */
    int nEffectB;                 /* 0x07bc */
    u8 pad7c0[0x8b0];
    u8 slotBlk;                   /* 0x1070 */
    u8 pad1071[0x127];
    u8 reactBlk;                  /* 0x1198 */
    u8 pad1199[0x17f];
    u8 comboBlk;                  /* 0x1318 */
    u8 pad1319[0x973];
    u8 timerBlk;                  /* 0x1c8c */
    u8 pad1c8d[0x11b];
    u8 reactionBlk;               /* 0x1da8 */
    u8 pad1da9[0x4df];
    u8 slotMask;                  /* 0x2288 */
    u8 pad2289[0x6f];
    u8 chipBlk;                   /* 0x22f8 */
    u8 pad22f9[0x7c0];
    short nAreaFrame;             /* 0x2aba */
    u8 pad2abc[0x134];
    int nWrapA;                   /* 0x2bf0 */
    u8 pad2bf4[4];
    int nWrapB;                   /* 0x2bf8 */
};

extern u8 data_0204c240;
extern u16 data_0204c18c;

extern void func_ov022_020ad44c(struct Vec3 *pOut, struct Actor *pActor);
extern int func_02030788(void);
extern int func_02020a9c(void);
extern void func_ov106_020b81ac(int bOn);
extern void func_ov002_02061e70(int bOn);
extern void func_ov082_020b8194(int bOn);
extern void func_ov002_02061e58(int bOn);
extern int func_ov022_02095648(u8 *pBlk);
extern int func_ov002_0206e770(int nWhich);
extern int func_ov002_0206b84c(void);
extern void func_ov002_020596c0(int bOn);
extern void func_ov002_02059730(int nWhich, u16 nValue);
extern int func_ov022_020ad61c(struct Actor *pActor, int nKind);
extern int func_ov022_020b2240(u8 nId);
extern void func_ov022_020ad2e4(struct Actor *pActor, int nMode);
extern void func_ov022_02093f24(u8 *pBlk, int nBit);
extern void func_ov022_020a4490(struct Actor *pActor, int nA, int nCue);
extern void func_ov022_02097904(struct Actor *pActor);
extern void func_ov022_020979e0(struct Actor *pActor);
extern void func_ov022_02093cb0(u8 *pBlk);
extern void func_ov022_02092bfc(u8 *pBlk, struct Vec3 *pVec, u16 nAngle,
                                int bReact, int nFrame);
extern void func_ov022_02092e08(u8 *pBlk);
extern void func_ov022_02092710(u8 *pBlk, struct Vec3 *pPos, u16 nAngle,
                                int nScale);
extern void func_ov022_02092808(u8 *pBlk, int nFrame);
extern void func_ov022_02094224(u8 *pBlk, struct Vec3 *pPos, int nFrame);
extern int func_ov022_02083f90(void);
extern void func_ov022_02093040(u8 *pBlk, struct Vec3 *pPos, struct Vec3 *pVec,
                                int nDelta, int nReaction, u16 nAngle,
                                u8 *pColl);
extern void func_ov022_0209d0b0(struct Actor *pActor, int *pCounter, int nDelta);
extern void func_ov022_0209d118(struct Actor *pActor, int nDelta);
extern void func_ov022_02097b78(struct Actor *pActor);
extern int func_ov002_02072754(int nSlot);
extern void func_ov013_0207fc2c(struct Actor *pActor);
extern void func_ov022_0209d2bc(struct Actor *pActor, int nDelta);
extern void func_ov022_0209045c(u8 *pMask, int nDelta);
extern void func_ov022_02094d90(u8 *pBlk, int nDelta);
extern void func_ov022_0209aefc(struct Actor *pActor, int nDelta);
extern void func_ov022_020976f4(struct Actor *pActor);
extern int func_020235d0(int nFlag, int nWhich);
extern void func_ov002_0205e448(void);
extern int func_ov002_0205e430(void);
extern int func_ov002_0205e2b8(void);
extern void func_ov002_02056d90(int nWhich);

void func_ov022_02097150(struct Actor *pActor)
{
    struct Vec3 vecFacing;
    int bLoud;
    int nGauge;
    int bBlocked;
    int nDelta;
    int nMask;

    func_ov022_020ad44c(&vecFacing, pActor);
    if (pActor->nOwner == func_02030788()
        && (bLoud = 0, (u32)pActor->nFlags & 0x10000) == 0) {
        if ((pActor->nFlags2 & (1ULL << 53)) != 0) {
            bLoud = 1;
        }
        if (func_02020a9c() == 0x2a) {
            func_ov106_020b81ac(bLoud);
        } else {
            func_ov002_02061e70(bLoud);
        }
        if ((pActor->nFlags2 & (1ULL << 61)) != 0) {
            if (func_02020a9c() == 0x2a) {
                func_ov082_020b8194(1);
            } else {
                func_ov002_02061e58(1);
            }
        } else {
            if (func_02020a9c() == 0x2a) {
                func_ov082_020b8194(0);
            } else {
                func_ov002_02061e58(0);
            }
        }
    }

    if (pActor->nOwner == func_02030788()
        && ((u32)pActor->nFlags & 0x10000) == 0) {
        nGauge = func_ov022_02095648(&pActor->chipBlk);
        bBlocked = 0;
        if (func_ov002_0206e770(bBlocked) != 0) {
            bBlocked = 1;
        }
        if (func_ov002_0206b84c() == 0x6c && (data_0204c240 & 4) == 0) {
            bBlocked = 1;
        }
        if (nGauge > 0) {
            if (nGauge >= pActor->nHp && bBlocked == 0) {
                func_ov002_020596c0(1);
            } else {
                func_ov002_020596c0(0);
            }
            func_ov002_02059730(1, (u16)nGauge);
        }
    }

    if (func_ov022_020ad61c(pActor, 0xc) != 0) {
        nGauge = func_ov022_020b2240(pActor->nId);
        if (nGauge == -1 || nGauge == 2) {
            func_ov022_020ad2e4(pActor, 2);
        }
    }
    if ((pActor->nFlags2 & (1ULL << 59)) != 0) {
        func_ov022_02093f24(&pActor->reactionBlk, 8);
        func_ov022_020a4490(pActor, 0, 0x5b);
    }
    if (((pActor->nFlags2 & (1ULL << 40)) != 0
         || (pActor->nFlags2 & (1ULL << 41)) != 0)
        && pActor->nEffectA != 0) {
        func_ov022_02097904(pActor);
    }
    if (pActor->nEffectB != -1) {
        func_ov022_020979e0(pActor);
    }
    func_ov022_02093cb0(&pActor->reactionBlk);
    func_ov022_02092bfc(&pActor->reactBlk, &vecFacing,
                        (u16)(pActor->pNode->nAngle - 0x8000),
                        pActor->nHitReaction == 0x13, pActor->nAreaFrame);
    if ((pActor->nFlags2 & (1ULL << 27)) != 0
        || (pActor->nFlags2 & (1ULL << 28)) != 0) {
        func_ov022_02092e08(&pActor->reactBlk);
    }
    if ((pActor->nFlags2 & (1ULL << 45)) != 0
        || (pActor->nFlags2 & (1ULL << 44)) != 0) {
        func_ov022_02092710(&pActor->slotBlk, &pActor->vecPos,
                            (u16)(pActor->pNode->nAngle - 0x8000), 0x1000);
    }
    func_ov022_02092808(&pActor->slotBlk, pActor->nAreaFrame);
    func_ov022_02094224(&pActor->timerBlk, &pActor->vecPos, pActor->nAreaFrame);
    nDelta = func_ov022_02083f90();
    func_ov022_02093040(&pActor->comboBlk, &pActor->vecPos, &vecFacing, nDelta,
                        pActor->nHitReaction,
                        (u16)(pActor->pNode->nAngle - 0x8000),
                        &pActor->collMain);
    if (func_02030788() == 0) {
        if ((data_0204c240 & 2) != 0) {
            if ((pActor->nInputMask & 4) != 0
                && (pActor->nFlags2 & (1ULL << 7)) == 0) {
                func_ov022_0209d0b0(pActor, &pActor->nWrapB,
                                    func_ov022_02083f90());
            } else {
                pActor->nWrapB = 0;
            }
            func_ov022_0209d0b0(pActor, &pActor->nWrapA,
                                func_ov022_02083f90());
        }
        func_ov022_0209d118(pActor, func_ov022_02083f90());
    }
    if (((u32)pActor->nFlags & 0x10000) != 0) {
        func_ov022_02097b78(pActor);
    }
    if (func_ov002_02072754(pActor->nSlotIndex) == 0xf) {
        func_ov013_0207fc2c(pActor);
    }
    func_ov022_0209d2bc(pActor, func_ov022_02083f90());
    func_ov022_0209045c(&pActor->slotMask, func_ov022_02083f90());
    func_ov022_02094d90(&pActor->chipBlk, func_ov022_02083f90());
    func_ov022_0209aefc(pActor, func_ov022_02083f90());
    func_ov022_020976f4(pActor);
    pActor->pfnUpdate(pActor);

    if (pActor->nOwner != func_02030788()) {
        return;
    }
    if ((pActor->nFlags & (1ULL << 16)) != 0) {
        return;
    }
    if ((pActor->nFlags & (1ULL << 20)) == 0) {
        return;
    }
    if (func_020235d0(0x37c5, 1) == 0) {
        if (func_020235d0(0x37c4, 1) == 0) {
            nMask = 0x200;
        } else {
            nMask = 0x100;
        }
        if ((data_0204c18c & (u16)nMask) == 0
            || ((func_ov002_0205e430() != 0 || func_ov002_0205e2b8() != 0) ? 1 : 0) == 0) {
            func_ov002_02056d90(0);
        }
    } else {
        func_ov002_0205e448();
    }
    pActor->nFlags &= ~(1ULL << 20);
}
