/* Ov022_StepAnchorReadyState -- one step of state 9: the actor held at
 * its ground point, ready to anchor.
 *
 * The local player raises flags2 bit 10; flag bit 26 is raised. When the
 * contact the actor rests on has a piece element its velocity moves the ground
 * point along, unless it has a horizontal part, which locks the actor in
 * place. The node is moved to the ground point, the position copied from
 * it, flags2 bit 23 raised by the local player, motion and recoil cleared,
 * and the node turned to the facing (once, animation flag 0x20). The post
 * hook decides whether the state is over (pre hook 6 when it is). Past
 * anim frame 6.0 with the animation not held and button 0x40 down the actor
 * anchors (state 10). Otherwise it is locked by button 2, by a pending
 * action, by a contact within 2.75 units of the body centre, or by another
 * actor above it within one unit and in front (dot <= 0.5): a locked actor
 * is nudged backwards by 1/16 and put into state 2. A state change clears
 * flags2 bit 23 (unless getting up) and the step scratch.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Vec3 {
    int x;
    int y;
    int z;
};

#define FLAG_BIT26 (1ULL << 26)
#define FLAG2_BIT10 (1ULL << 10)
#define FLAG2_BIT23 (1ULL << 23)
#define NODE_FLAG_NO_TURN 0x20
#define ANIM_FLAG_TURNED 0x20
#define ANIM_FLAG_HELD 0x4
#define BUTTON_2 0x2
#define BUTTON_GET_UP 0x40
#define GET_UP_FRAME 0x6000
#define CONTACT_REACH 0x2c00
#define NEAR_DIST 0x1000
#define FRONT_DOT 0x800
#define NUDGE_SCALE 0x100
#define ANGLE_HALF 0x8000
#define STATE_STAGGER 2
#define STATE_ANCHORED 10
#define PRE_DRAW_OVER 6

struct Actor;
typedef int (*PfnPost)(struct Actor *pActor);
typedef void (*PfnPre)(struct Actor *pActor, int nArg);

/* Ov022ActorNode */
struct Node {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad0006[0x7a];
    u16 nAngle;                  /* 0x80 */
};

/* HitPassOwner */
struct PassOwner {
    u8 pad0000[0x158];
    void *pElement;              /* 0x158 Ov002PieceElement */
};

/* HitState */
struct HitState {
    u8 pad0000[0x28];
    struct PassOwner *pPassOwner;   /* 0x28 */
};

/* Ov022GroundBlock: the ground block at actor+0x5b8 */
struct Ground {
    struct Vec3 vec;             /* 0x00 */
    u8 pad000c[8];
    struct HitState *pHit;       /* 0x14 */
    u8 pad0018[0x8c];
    int nStepScratch;            /* 0xa4 */
    u16 nFacingAngle;            /* 0xa8 */
    u8 pad00aa[2];
};

/* Ov022CollBlock */
struct CollBlock {
    u8 pad0000[0x9c];
    int nContactY;               /* 0x9c */
    u8 pad00a0[4];
    int nContactMode;            /* 0xa4 */
};

struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008;
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0xe];
    u16 nButtons;                /* 0x0018 */
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[4];
    struct Node *pNode;          /* 0x0020 */
    u8 pad0024[0x34];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0xc];
    struct CollBlock collMain;   /* 0x0068 */
    u8 pad0110[0x354];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    struct Vec3 vecAim;          /* 0x048c */
    u8 pad0498[0x120];
    struct Ground ground;        /* 0x05b8 Ov022GroundBlock: nStepScratch 0x65c, nFacingAngle 0x660 */
    PfnPre pfnPreDraw;           /* 0x0664 */
    PfnPost pfnPostDraw;         /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 */
    u8 bStateOver : 1;
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;
    u8 bSequenceRunning : 1;
    u8 bVoicePlayed : 1;
    u8 bTriggerHeld : 1;
    u8 nSpare6947 : 1;
    u8 pad0695[3];
    struct Vec3 vecMotion;       /* 0x0698 */
    u8 pad06a4[0x10c];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x1ef8];
    int nCenterY;                /* 0x26ac */
};

extern short data_0203d210[];               /* kFxSinCosTable: sin, cos pairs */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern struct Vec3 *func_ov002_02076d04(void *pElement);                        /* Ov002_GetElementVelocity */
extern void VEC_Add(struct Vec3 *pA, struct Vec3 *pB, struct Vec3 *pOut);
extern void func_0202b450(struct Node *pNode, struct Vec3 *pVec);              /* Actor_SetVecAndSyncChild */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);               /* Ov022_ActorSetState */
extern int func_ov022_020983ec(struct Actor *pActor, int nArg);                 /* Ov022_TryPendingAction */
extern int func_ov022_020882f8(void);                                           /* GetActiveField34 */
extern struct Vec3 *func_ov022_020881f8(int nIndex);                            /* GetEntryPtr48cOrDefault */
extern void VEC_Subtract(struct Vec3 *pA, struct Vec3 *pB, struct Vec3 *pOut);
extern int VEC_Mag(struct Vec3 *pVec);
extern int VEC_DotProduct(struct Vec3 *pA, struct Vec3 *pB);
extern int func_01ff8d18(struct Vec3 *pSrc, struct Vec3 *pDst);                 /* VEC_Normalize */
extern void func_01ffa724(int nScale, struct Vec3 *pSrc, struct Vec3 *pDst);    /* ScaleVec3Fx12 */

int func_ov022_020a8354(struct Actor *pActor)
{
    struct Vec3 vecFacing;
    struct Vec3 vecOther;
    struct Vec3 vecDiff;
    struct Vec3 vecFrom;
    int nRet;
    int bLocked;
    int bAnchor;
    int i;
    struct Ground *pGround;
    struct Node *pNode;
    struct Vec3 *pVel;
    void *pElement;
    int nCenter;
    int nDiff;
    int nIndex;
    u16 nFacing;

    nRet = 0;
    bLocked = 0;
    bAnchor = 0;
    pGround = &pActor->ground;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT10;
    }
    pActor->nFlags |= FLAG_BIT26;
    if (pGround->pHit != 0 && (pElement = pGround->pHit->pPassOwner->pElement) != 0
        && (pVel = func_ov002_02076d04(pElement)) != 0) {
        if (pVel->x != 0 || pVel->z != 0) {
            bLocked = 1;
        } else {
            VEC_Add(pVel, &pGround->vec, &pGround->vec);
        }
    }
    func_0202b450(pActor->pNode, &pGround->vec);
    pActor->vecAim = pGround->vec;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT23;
    }
    pActor->vecMotion.x = pActor->vecMotion.y = pActor->vecMotion.z = 0;
    pActor->nRecoil = 0;
    pNode = pActor->pNode;
    nFacing = pActor->ground.nFacingAngle;
    if ((pNode->nFlags & NODE_FLAG_NO_TURN) == 0) {
        pNode->nAngle = nFacing + ANGLE_HALF;
        pNode->nAnimFlags |= ANIM_FLAG_TURNED;
    }
    nCenter = pActor->nCenterY + pActor->vecAim.y;
    pActor->bStateOver = (u8)pActor->pfnPostDraw(pActor);
    if (pActor->bStateOver) {
        pActor->pfnPreDraw(pActor, PRE_DRAW_OVER);
    }
    if (pActor->nAnimFrame > GET_UP_FRAME && (pActor->pNode->nAnimFlags & ANIM_FLAG_HELD) == 0
        && (pActor->nButtons2 & BUTTON_GET_UP) != 0) {
        nRet = func_ov022_020a35f4(pActor, STATE_ANCHORED);
        bAnchor = 1;
    } else {
        if ((pActor->nButtons & BUTTON_2) == BUTTON_2) {
            bLocked = 1;
        } else {
            nRet = func_ov022_020983ec(pActor, 0);
            if (nRet != 0) {
                bLocked = 1;
            }
        }
        if (pActor->collMain.nContactMode != 0) {
            nDiff = nCenter - pActor->collMain.nContactY;
            if (nDiff < 0) {
                nDiff = -nDiff;
            }
            if (nDiff < CONTACT_REACH) {
                bLocked = 1;
            }
        }
        if (!bLocked) {
            for (i = 0; i < func_ov022_020882f8(); i++) {
                if (i == pActor->nId) {
                    continue;
                }
                vecOther = *func_ov022_020881f8(i);
                if (vecOther.y > pGround->vec.y) {
                    vecFrom = pGround->vec;
                    vecFrom.y += pActor->nCenterY;
                    VEC_Subtract(&vecFrom, &vecOther, &vecDiff);
                    if (VEC_Mag(&vecDiff) <= NEAR_DIST) {
                        nIndex = pGround->nFacingAngle >> 4;
                        vecFacing.y = 0;
                        vecFacing.x = -data_0203d210[nIndex * 2];
                        vecFacing.z = -data_0203d210[nIndex * 2 + 1];
                        if (VEC_DotProduct(&vecDiff, &vecFacing) <= FRONT_DOT) {
                            bLocked = 1;
                            break;
                        }
                    }
                }
            }
        }
        if (bLocked) {
            nFacing = pActor->pNode->nAngle - ANGLE_HALF;
            nIndex = (u16)(nFacing + ANGLE_HALF) >> 4;
            pActor->vecMotion.x = -data_0203d210[nIndex * 2];
            pActor->vecMotion.y = 0;
            pActor->vecMotion.z = -data_0203d210[nIndex * 2 + 1];
            func_01ff8d18(&pActor->vecMotion, &pActor->vecMotion);
            func_01ffa724(NUDGE_SCALE, &pActor->vecMotion, &pActor->vecMotion);
            if (nRet == 0) {
                nRet = func_ov022_020a35f4(pActor, STATE_STAGGER);
            }
        }
    }
    if (nRet != 0) {
        if (!bAnchor) {
            pActor->nFlags2 &= ~FLAG2_BIT23;
        }
        pActor->ground.nStepScratch = 0;
    }
    return nRet;
}
