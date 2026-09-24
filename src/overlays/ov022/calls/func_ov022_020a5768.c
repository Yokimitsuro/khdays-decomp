/* MWCC opt_dead_assignments must stay off: its default pass changes the post-call register/store schedule. */
#pragma opt_dead_assignments off
/* Ov022_RunContactMode0 -- sweep a scaled contact slot's fan and fire.
 *
 * Only while the frame lies in the slot's window. The fan starts at the actor's aim plus the slot's
 * offset turned by the node's facing, faces the node, takes the slot's radius and spread (both, with
 * the offset, scaled by the actor's +0x92c scale where the slot's control asks, 020b0c24), filters
 * through the hit-id list and lives in the actor's slot group. The hit context carries the slot's
 * face, the push (x into x and z, y into y), mode 0, the matched row's mask and amount, and flag
 * bits 2, 0 (slot rule 0x30) and 5 (full). A hit the contact vetoes is dropped; any other emits the
 * slot's event (one kind higher when full) at the axis angle at the contact point, and the actor's
 * contact state is updated (0209bd10).
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    volatile int y;
    int z;
} VecFx32;

typedef struct {
    int m[3][3];
} MtxFx33;

/* Ov022ScaledFanSlot: a contact slot whose fan offset / radius / spread follow the actor's scale */
struct ScaledFanSlot {
    int nFace;                   /* 0x00 */
    int nStartFrame;             /* 0x04 */
    int nEndFrame;               /* 0x08 */
    volatile int nPushX;                  /* 0x0c */
    int nPushY;                  /* 0x10 */
    u8 bFull : 1;                /* 0x14 bit 0 */
    u8 bHeld : 1;                /* 0x14 bit 1 */
    u8 nRest14 : 6;
    u8 pad15[3];
    VecFx32 vecOffset;           /* 0x18: also the scale control (flags at +0x13) */
    int nRadius;                 /* 0x24 */
    short nCosSpread;            /* 0x28 */
    u8 nEventKind;               /* 0x2a */
};

/* Ov022ComboSlot */
struct ComboSlot {
    int nFace;                   /* 0x00 */
    int nStartFrame;             /* 0x04 */
    int nEndFrame;               /* 0x08 */
    int nPushX;                  /* 0x0c */
    int nPushY;                  /* 0x10 */
    u8 bFull : 1;                /* 0x14 bit 0 */
    u8 bHeld : 1;                /* 0x14 bit 1 */
    u8 nRest14 : 6;
    u8 pad15[3];
    s8 nSide;                    /* 0x18 */
    u8 pad19[3];
    int nRadius1c;               /* 0x1c */
    u8 bNetwork;                 /* 0x20 */
    u8 nEventKind21;             /* 0x21 */
};

/* Ov022FanQuery */
struct FanQuery {
    VecFx32 vecOrigin;           /* 0x00 */
    int nRadius;                 /* 0x0c */
    int nGroup;                  /* 0x10 */
    VecFx32 vecDir;              /* 0x14 */
    int nCosSpread;              /* 0x20 */
    short *pHitIds;              /* 0x24 */
    u32 nFlags;                  /* 0x28 */
};

struct PushView {
    volatile int x;
    volatile int y;
    int z;
};

/* Ov022SweepHit: the 40-byte hit context the command handlers take */
struct SweepHit {
    int nFace;                   /* 0x00 */
    void *pPart;                 /* 0x04 */
    u32 nFlags;                  /* 0x08 */
    int nMatchMask;              /* 0x0c */
    u8 nAmount;                  /* 0x10 */
    u8 pad11[3];
    struct PushView vecPush;             /* 0x14 */
    int nMode;                   /* 0x20 */
    u8 nField24;                 /* 0x24 */
    u8 bHeld : 1;                /* 0x25 bit 0 */
    u8 bMatched : 1;             /* 0x25 bit 1 */
    u8 nRest25 : 6;
    u8 pad26[2];
};

/* Ov022SweepContact */
struct SweepContact {
    u32 nResult;                 /* 0x00 */
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[3];
    VecFx32 vec;                 /* 0x0c */
};

/* Ov022ActorBody: the block at actor +0x118 */
struct ScaleSub { u8 pad[0x14]; int nScale; };
struct ScaleBody { u8 pad[0x800]; struct ScaleSub sub; };
struct ScaleView { u8 pad[0x118]; struct ScaleBody body; };
struct ActorBody {
    u8 pad000[0x814];
    int nScale;                  /* 0x814 (actor +0x92c) */
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x16];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x42];
    short nSlotIndex;            /* 0x0066 */
    u8 pad0068[0x424];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x318];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x1f08];
    struct SweepContact contact; /* 0x26bc */
};

#define HIT_MATCH_ANY 0xe
#define HIT_FLAG_BIT0 0x1
#define HIT_FLAG_BIT2 0x4
#define HIT_FLAG_FULL 0x20
#define CONTACT_VETO 0x40
#define RULE_HIT_BIT0 0x30
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4

extern short data_0203d210[];            /* sin, cos pairs by angle >> 4 */

extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(VecFx32 *pVec, MtxFx33 *pMtx, VecFx32 *pOut);
extern void func_ov022_020b0c24(void *pControl, VecFx32 *pVec, int *pRadius, int *pSpread,
                                int nScale);                   /* Ov022_ApplySlotScale */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_ov022_020a22f0(struct Actor *pActor, int bFull, int *pMatchMask,
                               u8 *pAmount);                   /* Ov022_SearchMatchingRow */
extern int func_ov022_020a1f84(struct Actor *pActor, int nFace, int nMatchMask, int bFull);
extern int func_020358f4(int nId, int nRule);
extern int func_ov022_020a0fb8(struct Actor *pActor, struct FanQuery *pFan,
                               struct SweepHit *pCtx);          /* Ov022_RunCommandHandlers */
extern int FX_Atan2(int x, int z);
extern void func_ov022_020a5f28(struct Actor *pActor, int nKind, u32 nAngle,
                                VecFx32 *pAt);                 /* Ov022_EmitEventBlocks */
extern void func_ov022_0209bd10(struct Actor *pActor);

void func_ov022_020a5768(struct Actor *pActor, struct ScaledFanSlot *pSlot, short *pHitIds, int bFull)
{
    struct ScaleSub *pBody = &((struct ScaleView *)pActor)->body.sub;
    struct FanQuery fan;
    struct SweepHit ctx;
    VecFx32 vecDir;
    VecFx32 vecOff;
    MtxFx33 mtx;
    u16 nAngle;
    int nTrig;
    int nHit;
    int nKind;
    u16 nAxis;
    int nPushX;
    int nPushY;
    u8 bOld;

    if (pSlot->nStartFrame > pActor->nAnimFrame) {
        return;
    }
    if (pSlot->nEndFrame <= pActor->nAnimFrame) {
        return;
    }
    ctx.pPart = 0;
    vecDir.y = 0;
    nAngle = pActor->pNode->nAngle - ANGLE_BIAS;
    nTrig = (nAngle >> ANGLE_STEP) * 2;
    vecDir.x = -data_0203d210[nTrig];
    vecDir.z = -data_0203d210[nTrig + 1];
    MTX_RotY33_(&mtx, vecDir.x, vecDir.z);
    MTX_MultVec33(&pSlot->vecOffset, &mtx, &vecOff);
    fan.vecDir = vecDir;
    fan.nRadius = pSlot->nRadius;
    fan.nGroup = pActor->nSlotIndex;
    fan.nCosSpread = pSlot->nCosSpread;
    fan.nFlags = 0;
    fan.pHitIds = pHitIds;
    func_ov022_020b0c24(&pSlot->vecOffset, &vecOff, &fan.nRadius, &fan.nCosSpread, pBody->nScale);
    VEC_Add(&pActor->vecAim, &vecOff, &fan.vecOrigin);
    ctx.nMatchMask = HIT_MATCH_ANY;
    ctx.nAmount = 0;
    ctx.bMatched = func_ov022_020a22f0(pActor, bFull, &ctx.nMatchMask, &ctx.nAmount);
    ctx.nFace = func_ov022_020a1f84(pActor, pSlot->nFace, ctx.nMatchMask, bFull);
    ctx.nFlags = HIT_FLAG_BIT2;
    pHitIds = (short *)pSlot->nPushX;

    nPushY = pSlot->nPushY;
    ctx.vecPush.x = (int)pHitIds;
    bOld = ((volatile u8 *)&ctx)[0x25];
    ctx.vecPush.z = (int)pHitIds;
    ctx.nMode = 0;
    ctx.vecPush.y = nPushY;
    ((u8 *)&ctx)[0x25] = (u8)((bOld & ~1) | (pSlot->bHeld & 1));
    ctx.nField24 = 0;
    if (bFull) { ctx.nFlags |= HIT_FLAG_FULL; }
    if (func_020358f4(pActor->nId, RULE_HIT_BIT0) != 0) {
        ctx.nFlags |= HIT_FLAG_BIT0;
    }
    nHit = func_ov022_020a0fb8(pActor, &fan, &ctx);
    if (nHit != 0 && (pActor->contact.nResult & CONTACT_VETO) != 0) {
        nHit = 0;
        pActor->contact.nResult = 0;
        pActor->contact.nState = 0;
    }
    if (nHit == 0) {
        return;
    }
    nAxis = FX_Atan2(fan.vecDir.x, fan.vecDir.z);
    nKind = pSlot->nEventKind;
    if (bFull) {
        nKind++;
    }
    func_ov022_020a5f28(pActor, nKind, nAxis, &pActor->contact.vec);
    func_ov022_0209bd10(pActor);
}
