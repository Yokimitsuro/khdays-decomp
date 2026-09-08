/* ov022: run one frame of the state the actor can be knocked out of.
 *
 * The longest of the state steps, and the one with the most ways out.
 *
 * It opens by marking the step and, if the entry test passes, raising two more
 * marks that the ending takes back down. One flag is mirrored from the second
 * word into the third whenever it is up.
 *
 * Releasing the action bit ends the state at once. Holding it runs the body:
 * a hit of the right shape late enough in the animation raises the recovery
 * flag, then the actor is offered an escape, and failing that a second one on a
 * different button. Only if neither takes does the drift step run, scaled by a
 * fixed amount or by the block's own scale depending on one more query, folded
 * into the push, and the state ended with the recoil primed from a global.
 *
 * After all that comes the animation nudge, the state's own hook, and the same
 * two endings as the siblings. A state that actually changed takes down all
 * three marks and, unless two flags say otherwise, clears the drift.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef short s16;

#define ACTION_BIT 4
#define NODE_NO_ANIM 0x20
#define STATE_END 2
#define STATE_ESCAPE 0x1d
#define STATE_ZERO 0
#define HIT_RECOVER 0x11
#define QUERY_RECOVER 0x17
#define QUERY_ESCAPE 0x1a
#define QUERY_FASTDRIFT 0x18
#define ANIM_EARLY 0xc000
#define ANIM_NUDGE 0x9000
#define ANIM_HOLD 0x11000
#define ANIM_LATE 0x12000
#define DRIFT_FAST 0x1400
#define RECOIL_HIGH 0x300
#define RECOIL_LOW 0x200
#define BUTTON_ESCAPE 2
#define BUTTON_RECOVER 0x800

#define FLAGS_DONE 0x2000000000000ULL
#define FLAGS_STEPPING 0x100000000ULL
#define FLAGS_HELD 0x80000000ULL
#define FLAGS_RECOVER 0x20000000000ULL
#define FLAGS_KEEP_A 0x10ULL
#define FLAGS_KEEP_B 0x2000ULL
#define FLAGS2_IN_STEP 0x200ULL
#define FLAGS2_ENTERED 0x100000000ULL
#define FLAGS2_MIRROR 0x4000000ULL
#define FLAGS2_REQUEST 0x2ULL
#define FLAGS3_ENTERED 0x100000000ULL
#define FLAGS3_MIRROR 0x4000000ULL

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[2];
};

/* the actor's slot block; the knockout step reads three of its words and the
 * entry test at 0209d7a4 reads the one just before them */
struct SlotBlk {
    u8 pad000[0x110];
    int nAnimLimit;              /* 0x110 -> actor 0x1180 */
    s16 nDriftScale;             /* 0x114 -> actor 0x1184 */
    u8 pad116[2];
    int nAnimMark;               /* 0x118 -> actor 0x1188 */
};

struct Actor;

typedef void (*PreDrawFn)(struct Actor *pActor, int nReplay);
typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0xe];
    u16 nButtons;                /* 0x0018 */
    u16 nButtons2;               /* 0x001a */
    u16 nPendingAction;          /* 0x001c */
    u8 pad001e[2];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[8];
    struct VecFx32 vecDrift;     /* 0x047c */
    u8 pad0488[0x10];
    struct VecFx32 vecStep;      /* 0x0498 */
    u8 pad04a4[0x28];
    int nAnimPos;                /* 0x04cc */
    u8 pad04d0[0x194];
    PreDrawFn pfnPreDraw;        /* 0x0664 */
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;        /* bit 3 */
    u8 nFlags694High : 4;
    u8 pad0695[3];
    int nStateWordA;             /* 0x0698 */
    u8 pad069c[4];
    int nStateWordC;             /* 0x06a0 */
    u8 pad06a4[0x18];
    int nHit;                    /* 0x06bc */
    u8 pad06c0[0xf0];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x8bc];
    struct SlotBlk slotBlk;      /* 0x1070 */
};

extern u8 data_ov022_020b2eb0;

extern int func_02030788(void);
extern int func_020358f4(int nId, int nQuery);
extern int func_ov022_0209d7a4(struct Actor *pActor);
extern int func_ov022_020983ec(struct Actor *pActor, int nArg);
extern void func_ov022_02097e14(struct Actor *pActor, struct VecFx32 *pOutStep);
extern void func_ov022_02097038(struct Actor *pActor, int nPos);
extern void func_ov022_020acf14(struct Actor *pActor, int nPos);
/* Ov022_ActorSetState */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);
/* scale a vector */
extern void func_01ffa724(int nScale, const struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);
/* SceneNode_Enable */
extern void func_0202af1c(u16 *pAnimFlags);
extern void VEC_Add(const struct VecFx32 *pA, const struct VecFx32 *pB,
                    struct VecFx32 *pOut);

int func_ov022_020a8ec0(struct Actor *pActor)
{
    struct VecFx32 vecDrift;
    struct VecFx32 vecMove;
    struct SlotBlk *pBlk;
    int nRet;
    int nRecoil;

    pBlk = &pActor->slotBlk;
    nRet = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 = pActor->nFlags2 | FLAGS2_IN_STEP;
    }
    if (func_ov022_0209d7a4(pActor) != 0) {
        if (func_02030788() == 0) {
            pActor->nFlags2 = pActor->nFlags2 | FLAGS2_ENTERED;
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 = pActor->nFlags3 | FLAGS3_ENTERED;
        }
    }
    if ((pActor->nFlags2 & FLAGS2_MIRROR) != 0) {
        pActor->nFlags3 = pActor->nFlags3 | FLAGS3_MIRROR;
    }
    if ((pActor->nInputMask & ACTION_BIT) == 0) {
        nRet = func_ov022_020a35f4(pActor, STATE_END);
    } else {
        if (pActor->nPendingAction == 1
            && (pActor->nFlags2 & FLAGS2_MIRROR) != 0
            && pActor->nAnimPos <= ANIM_EARLY
            && func_020358f4(pActor->nId, QUERY_RECOVER) != 0) {
            pActor->nFlags = pActor->nFlags | FLAGS_STEPPING;
        }
        if (((pActor->nFlags2 & FLAGS2_MIRROR) != 0
             && pActor->nAnimPos >= pBlk->nAnimLimit)
            || (pActor->nFlags & FLAGS_HELD) != 0) {
            nRet = func_ov022_020983ec(pActor, 0);
            if (nRet != 0) {
                if (pActor->nPendingAction != 1) {
                    pActor->nFlags = pActor->nFlags & ~FLAGS_STEPPING;
                }
                goto done;
            }
        }
        if (func_020358f4(pActor->nId, QUERY_ESCAPE) != 0
            && (pActor->nFlags2 & FLAGS2_MIRROR) != 0) {
            if ((pActor->nButtons & BUTTON_ESCAPE) != 0) {
                nRet = func_ov022_020a35f4(pActor, STATE_ESCAPE);
            }
            if (nRet != 0) {
                pActor->nFlags = pActor->nFlags & ~FLAGS_STEPPING;
                goto done;
            }
        }
        vecDrift.z = 0;
        vecDrift.y = 0;
        vecDrift.x = 0;
        if ((pActor->nFlags & FLAGS_HELD) == 0) {
            func_ov022_02097e14(pActor, &vecDrift);
            if (func_020358f4(pActor->nId, QUERY_FASTDRIFT) != 0) {
                func_01ffa724(DRIFT_FAST, &vecDrift, &vecDrift);
            } else {
                func_01ffa724(pBlk->nDriftScale, &vecDrift, &vecDrift);
            }
        }
        vecMove = vecDrift;
        vecMove.y = 0;
        VEC_Add(&pActor->vecStep, &vecMove, &pActor->vecStep);
        if ((pActor->nInputMask & ACTION_BIT) == 0) {
            pActor->nFlags = pActor->nFlags & ~FLAGS_STEPPING;
            pActor->nStateWordA = vecDrift.x;
            pActor->nStateWordC = vecDrift.z;
            if (data_ov022_020b2eb0 != 0) {
                nRecoil = RECOIL_HIGH;
            } else {
                nRecoil = RECOIL_LOW;
            }
            pActor->nRecoil = nRecoil;
            nRet = func_ov022_020a35f4(pActor, STATE_END);
        }
    }
done:
    if ((pActor->nFlags2 & FLAGS2_MIRROR) == 0 && nRet == 0
        && pActor->nHit == HIT_RECOVER) {
        if ((pActor->nButtons2 & BUTTON_RECOVER) != 0
            && (pActor->nFlags & FLAGS_RECOVER) != 0) {
            if (pActor->nAnimPos < pBlk->nAnimMark + ANIM_NUDGE
                && pActor->nAnimFrame >= ANIM_HOLD) {
                func_ov022_02097038(pActor, ANIM_NUDGE);
            }
        } else {
            pActor->nFlags = pActor->nFlags & ~FLAGS_RECOVER;
            if (pActor->nAnimFrame < ANIM_LATE) {
                func_ov022_020acf14(pActor, ANIM_LATE);
            }
        }
    }
    pActor->bStateOver = pActor->pfnPostDraw(pActor);
    if (pActor->bStateOver != 0) {
        pActor->nFlags = pActor->nFlags | FLAGS_DONE;
        if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 = pActor->nFlags2 | FLAGS2_REQUEST;
        }
    }
    if ((pActor->nFlags2 & FLAGS2_REQUEST) != 0 && nRet == 0) {
        nRet = func_ov022_020a35f4(pActor, STATE_ZERO);
        pActor->pfnPreDraw(pActor, 0);
        pActor->nFlags = pActor->nFlags & ~FLAGS_STEPPING;
    }
    if (nRet != 0) {
        pActor->nFlags2 = pActor->nFlags2 & ~FLAGS2_IN_STEP;
        pActor->nFlags2 = pActor->nFlags2 & ~FLAGS2_ENTERED;
        pActor->nFlags3 = pActor->nFlags3 & ~FLAGS3_ENTERED;
        if ((pActor->nFlags & FLAGS_KEEP_A) == 0
            && (pActor->nFlags & FLAGS_KEEP_B) == 0) {
            pActor->vecDrift.z = 0;
            pActor->vecDrift.y = 0;
            pActor->vecDrift.x = 0;
        }
    }
    return nRet;
}
