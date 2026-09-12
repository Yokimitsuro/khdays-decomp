/* Ov022_StepAnchoredState -- run one frame of an anchor-driven state and
 * decide whether it is over.
 *
 * Without flag bit 10 the frame's delta comes from the anchor; with it the
 * delta is zero. Past frame 0x5000 a vertical delta becomes the recoil and the
 * horizontal part is added to the step. Before that the actor is moved to its
 * aim plus the delta, the node placed there, the push and the drift cleared,
 * input bit 2 dropped and flag-2 bit 23 raised for the local player.
 *
 * The state's own step then answers whether it is done: that raises flag bit
 * 49, pokes the animation unless the node is already skipping it and raises
 * the end request (flag-2 bit 1) for the local player. Once the request is up
 * the state ends into state 2, and the delta is kept as the actor's motion.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

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

struct Actor;

typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[0x18];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x10];
    struct VecFx32 vecDrift;     /* 0x047c */
    u8 pad0488[4];
    struct VecFx32 vecAim;       /* 0x048c */
    struct VecFx32 vecStep;      /* 0x0498 */
    u8 pad04a4[0x1c];
    struct VecFx32 *pPush;       /* 0x04c0 */
    u8 pad04c4[0x1a4];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
    u8 pad0695[3];
    struct VecFx32 vecMotion;    /* 0x0698 */
    u8 pad06a4[0x10c];
    int nAnimFrame;              /* 0x07b0 */
};

#define FLAG_BIT10 (1ULL << 10)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define FLAG2_BIT23 (1ULL << 23)
#define INPUT_BIT2 0x4
#define NODE_NO_ANIM 0x20
#define ANCHOR_FRAME 0x5000
#define STATE_END 2

extern void func_ov022_0209fe20(struct Actor *pActor, struct VecFx32 *pOut);   /* Ov022_StepAnchorDelta */
extern void VEC_Add(const struct VecFx32 *pA, const struct VecFx32 *pB, struct VecFx32 *pOut);
extern void func_0202b450(struct ActorNode *pNode, struct VecFx32 *pPos);      /* Actor_SetVecAndSyncChild */
extern int func_02030788(void);
extern void func_0202af1c(u16 *pAnimFlags);                                    /* SceneNode_Enable */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);             /* Ov022_ActorSetState */

int func_ov022_020a8764(struct Actor *pActor)
{
    struct VecFx32 vecDelta;
    struct VecFx32 vecPos;
    struct VecFx32 vecFlat;
    int nRet;
    struct VecFx32 *pPush;

    nRet = 0;
    if ((pActor->nFlags & FLAG_BIT10) == 0) {
        func_ov022_0209fe20(pActor, &vecDelta);
    } else {
        vecDelta.z = 0;
        vecDelta.y = 0;
        vecDelta.x = 0;
    }
    if (pActor->nAnimFrame >= ANCHOR_FRAME) {
        if (vecDelta.y != 0) {
            pActor->nRecoil = vecDelta.y;
        }
        vecFlat = vecDelta;
        vecFlat.y = 0;
        VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
    } else {
        pActor->nInputMask &= ~INPUT_BIT2;
        VEC_Add(&pActor->vecAim, &vecDelta, &vecPos);
        func_0202b450(pActor->pNode, &vecPos);
        pPush = pActor->pPush;
        pPush->z = 0;
        pPush->y = 0;
        pPush->x = 0;
        pActor->vecDrift.z = 0;
        pActor->vecDrift.y = 0;
        pActor->vecDrift.x = 0;
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT23;
        }
    }
    pActor->bStateOver = pActor->pfnPostDraw(pActor);
    if (pActor->bStateOver != 0) {
        pActor->nFlags |= FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT1;
        }
    }
    if ((pActor->nFlags2 & FLAG2_BIT1) != 0) {
        nRet = func_ov022_020a35f4(pActor, STATE_END);
    }
    if (nRet != 0) {
        pActor->vecMotion = vecDelta;
    }
    return nRet;
}
