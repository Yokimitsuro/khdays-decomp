/* ov022: take a hit request and turn it into damage, if everything allows it.
 *
 * Most of this is refusal. Three helpers get first say, then a long run of flag
 * gates on the actor, then the guard window, then the two upgrade paths that can
 * turn an ordinary hit into a block or a break. Only what survives all of that
 * reaches the applier at the end.
 *
 * Two of the gates answer differently: one refuses with a yes, because a hit
 * absorbed on purpose still counts as handled.
 *
 * The flag words at 0x00, 0x464 and 0x46c are each 64 bits wide, which is why
 * testing a low bit of any of them masks the other half with nothing.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define ACTOR_FLAGS(p) (*(unsigned long long *)(p)->aFlags)
#define ACTOR_FLAGS2(p) (*(unsigned long long *)(p)->aFlags2)
#define ACTOR_FLAGS3(p) (*(unsigned long long *)(p)->aFlags3)

#define GUARD_WINDOW 0x6000
#define BREAK_WINDOW 0x15000
#define MIN_SHOVE 0x1000
#define SHOVE_SLOW 0x4cd
#define SHOVE_FAST 0x99a

struct Vec3 {
    int x, y, z;
};

struct Source {
    u8 pad000[0x19c];
    u8 nRole;                    /* 0x19c */
};

struct Request {
    int nFlags;                  /* 0x00 */
    struct Vec3 vec;             /* 0x04 */
    u8 pad10[0xc];
    struct Source *pSrc;         /* 0x1c */
    int nAmount;                 /* 0x20 */
    int nFlags2;                 /* 0x24 */
};

struct Node {
    u8 pad00[0x14];
    int *pRow;                   /* 0x14 */
};

struct Actor {
    u32 aFlags[2];               /* 0x0000 */
    u8 pad008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad00a[8];
    u16 nHp;                 /* 0x0012 */
    u8 pad014[2];
    u16 nSpeed;                  /* 0x0016 */
    u8 pad018[0x44c];
    u32 aFlags2[2];              /* 0x0464 */
    u32 aFlags3[2];              /* 0x046c */
    u8 pad474[8];
    struct Vec3 vecDrift;        /* 0x047c */
    u32 nFacingAngle;            /* 0x0488 */
    u8 pad48c[0x28];
    int nInterruptCharge;                  /* 0x04b4 */
    u8 pad4b8[0x1dc];
    u8 nSpareLow : 3;            /* 0x0694 */
    u8 bActionLocked : 1;
    u8 nSpareHigh : 4;
    u8 pad695[0x11b];
    int nAnimFrame;                  /* 0x07b0 */
    u8 pad7b4[0x5cc];
    struct Node *pNode;          /* 0x0d80 */
    u8 padd84[0x1574];
    u8 run[4];                   /* 0x22f8 */
    u8 pad22fc[0x480];
    u8 nBreakBits;               /* 0x277c */
    u8 pad277d[0x33b];
    u8 nMenuState;                  /* 0x2ab8 */
};

extern u8 data_0204c240[];
extern u8 data_0204c248[];
extern const struct Vec3 data_02041dc8;

extern int func_ov022_0209d7c0(struct Actor *pActor, struct Request *pReq);
extern int func_ov022_0209df9c(struct Actor *pActor, struct Request *pReq);
extern void func_ov022_0209b250(struct Actor *pActor, struct Request *pReq, int nArg2);
extern void func_ov022_0209b3c4(struct Actor *pActor, struct Request *pReq, int nArg2);
extern int func_ov022_0209bd04(struct Actor *pActor);
extern int func_ov022_020a2424(struct Actor *pActor, struct Request *pReq);
extern void func_ov022_020acc94(struct Actor *pActor, int nAmount);
extern void func_ov022_020ace24(struct Actor *pActor, int nShove, int nMode);
extern int func_ov022_02095524(u8 *pCue);
extern int func_ov022_0208868c(void);
extern int func_02030670(void);
extern int func_02030788(void);
extern int func_020358f4(int nId, int nQuery);
extern void func_ov002_0206cd60(int nMode, int nArg);
extern void func_ov022_0209d440(struct Actor *pActor, int nAmount, int bFlag);int func_ov022_020a08a8(struct Actor *pActor, struct Request *pReq)
{
    struct Vec3 vShove;
    int nAmount;
    int bBreak;
    int bBlock;
    int nMode;
    int nShove;
    int bStagger;
    unsigned long long nFlags;

    vShove = pReq->vec;
    pReq->nFlags2 = 0;
    pReq->nAmount = 0;
    if (func_ov022_0209d7c0(pActor, pReq) != 0) {
        return 0;
    }
    if (func_02030788() != 0) {
        return 0;
    }
    if (func_ov022_0209df9c(pActor, pReq) != 0) {
        return 0;
    }
    if ((pReq->nFlags & 1) != 0
        && (pReq->pSrc->nRole == 2 || pReq->pSrc->nRole == 0x21)) {
        ACTOR_FLAGS(pActor) |= 0x4000;
    }
    if ((ACTOR_FLAGS(pActor) & 0x80000) != 0) {
        return 0;
    }
    if ((ACTOR_FLAGS(pActor) & 0x800000000000) != 0) {
        return 0;
    }
    if ((ACTOR_FLAGS(pActor) & 0x400) != 0) {
        return 1;
    }
    if (func_02030670() == 0) {
        if (func_ov022_0208868c() != 0) {
            return 0;
        }
    } else if (pActor->bActionLocked != 0) {
        return 0;
    }
    nFlags = ACTOR_FLAGS(pActor);
    if ((nFlags & 0x1000000) != 0) {
        return 0;
    }
    if (pActor->nHp == 0 || (nFlags & 0x100) != 0 || (nFlags & 0x20000) != 0) {
        return 0;
    }
    if (pActor->nInterruptCharge == 0
        && (ACTOR_FLAGS(pActor) & 0x1000000000000000) == 0) {
        func_ov022_0209b250(pActor, pReq, 0);
    }
    if (pActor->nInterruptCharge != 0 && (pReq->nFlags & 0x400) == 0) {
        return 0;
    }
    if ((pReq->nFlags & 0x200) == 0) {
        pActor->nInterruptCharge = GUARD_WINDOW;
    }
    if (pActor->nMenuState == 0xb && (pReq->nFlags & 0x800) == 0) {
        pActor->nBreakBits |= 2;
    }
    if ((data_0204c240[0] & 4) == 0
        && ((u32)(ACTOR_FLAGS(pActor) & 0x10000)) == 0 && pActor->nId == 0) {
        func_ov002_0206cd60(1, 0);
    }
    bBreak = 0;
    bBlock = 0;
    nMode = func_020358f4(pActor->nId, 0x40);
    nAmount = func_ov022_020a2424(pActor, pReq);
    if (nAmount >= pActor->nHp && (pReq->nFlags & 0x800) != 0) {
        nAmount = pActor->nHp - 1;
    }
    if (func_020358f4(pActor->nId, 0x3f) != 0
        && (ACTOR_FLAGS(pActor) & 0x1000000000000000) == 0
        && (ACTOR_FLAGS(pActor) & 0x2000000000) == 0
        && pActor->nHp <= nAmount
        && pActor->nHp > 1) {
        pReq->nFlags2 &= ~2;
        bBlock = 1;
        nAmount = pActor->nHp - 1;
        ACTOR_FLAGS(pActor) |= 0x2000000000;
        ACTOR_FLAGS(pActor) |= 0x800000000000;
    }
    if (nMode > 0
        && (ACTOR_FLAGS(pActor) & 0x1000000000000000) == 0
        && (ACTOR_FLAGS(pActor) & 0x4000000000) == 0
        && pActor->nHp <= nAmount) {
        ACTOR_FLAGS3(pActor) |= 0x800000000000000;
        pActor->nInterruptCharge = BREAK_WINDOW;
        pReq->nFlags2 &= ~2;
        bBreak = 1;
        ACTOR_FLAGS(pActor) |= 0x4000000000;
    }
    if ((ACTOR_FLAGS(pActor) & 0x1000000000000000) == 0 && bBreak == 0) {
        func_ov022_020acc94(pActor, pActor->nHp - nAmount);
    }
    if (bBreak != 0) {
        switch (nMode) {
        case 1:
            nShove = pActor->nSpeed * SHOVE_SLOW;
            break;
        case 2:
            nShove = pActor->nSpeed * SHOVE_FAST;
            break;
        case 3:
            nShove = pActor->nSpeed << 12;
            break;
        default:
            break;
        }
        if (nShove < MIN_SHOVE) {
            nShove = MIN_SHOVE;
        }
        func_ov022_020ace24(pActor, nShove >> 12, 1);
    }
    pReq->nAmount = nAmount;
    if ((ACTOR_FLAGS(pActor) & 0x1000000000000000) == 0 && bBlock == 0
        && bBreak == 0) {
        func_ov022_0209b3c4(pActor, pReq, 0);
    }
    if (func_ov022_0209bd04(pActor) == 2) {
        vShove.y = 0xa00;
    }
    if ((data_0204c240[0] & 4) != 0 && data_0204c248[0] == 1
        && (pReq->nFlags & 2) != 0) {
        vShove.z = 0;
        vShove.y = 0;
        vShove.x = 0;
    }
    bStagger = 1;
    if (func_ov022_02095524(pActor->run) != 0) {
        bStagger = 0;
    }
    if ((pReq->nFlags & 0x10) != 0) {
        bStagger = 0;
    }
    if (func_020358f4(pActor->nId, 0x49) != 0
        && (ACTOR_FLAGS2(pActor) & 0x1000) != 0
        && pActor->nAnimFrame < 0x12000) {
        bStagger = 0;
    }
    if (bStagger != 0) {
        if (func_020358f4(pActor->nId, 0x2f) != 0) {
            if ((ACTOR_FLAGS2(pActor) & 0x10) == 0) {
                bStagger = 1;
            } else if (pActor->pNode == 0) {
                bStagger = 1;
            } else {
                int nValue = pActor->pNode->pRow[3];
                int nLimit = 0x7fffffff;

                bStagger = 0;
                if (nValue != -MIN_SHOVE) {
                    nLimit = nValue;
                }
                if (pActor->nAnimFrame > nLimit) {
                    bStagger = 1;
                }
            }
            if (func_ov022_0209bd04(pActor) != 0xe) {
                bStagger = 1;
            }
            if (pActor->vecDrift.y != 0) {
                bStagger = 1;
            }
        }
    }
    if (pActor->nHp == 0) {
        bStagger = 1;
    }
    if (bStagger != 0) {
        ACTOR_FLAGS(pActor) |= 0x10;
        if (func_02030788() == 0) {
            ACTOR_FLAGS2(pActor) |= 0x100;
        }
        pActor->vecDrift = vShove;
    } else {
        pActor->vecDrift = data_02041dc8;
    }
    func_ov022_0209d440(pActor, nAmount, (pReq->nFlags & 2) != 0);
    return 1;
}