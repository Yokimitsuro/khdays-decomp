/* Ov022_RunContactMode1 -- sweep a combo slot's full-spread fan from a side
 * slot and fire, then report it over the network.
 *
 * Only while the frame lies in the slot's window, and only for side 2 or a
 * side whose record bit says it is armed. The fan starts at the actor's aim
 * plus the side slot's offset from the spare slot turned by the node's
 * facing, reaches the slot's radius with a full spread, faces the node,
 * filters through the hit-id list and lives in the actor's slot group. The
 * hit context carries the slot's face, the push (y and x swapped into y and
 * z), mode 1, the matched row's mask and amount, and flag bits 2, 0 (slot
 * rule 0x30) and 5 (full). A hit the contact vetoes is dropped; any other
 * emits the slot's event (one kind higher when full) at the axis angle, one
 * unit from the contact toward the fan's apex.
 *
 * Then a landed contact (result bit 0), or a state-4 contact of kind 1 or 3,
 * or of kind 2 while the slot's network flag is up, is marshalled as record
 * 1 at the apex with the axis angle and the slot's event kind.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int m[3][3];
} MtxFx33;

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

/* Ov022SweepHit: the 40-byte hit context the command handlers take */
struct SweepHit {
    int nFace;                   /* 0x00 */
    void *pPart;                 /* 0x04 */
    u32 nFlags;                  /* 0x08 */
    int nMatchMask;              /* 0x0c */
    u8 nAmount;                  /* 0x10 */
    u8 pad11[3];
    VecFx32 vecPush;             /* 0x14 */
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
    u8 pad0498[0x7c];
    int nSlotSideA;              /* 0x0514 */
    int nSlotSideB;              /* 0x0518 */
    int nSlotSpare;              /* 0x051c */
    u8 pad0520[0x290];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x1f08];
    struct SweepContact contact; /* 0x26bc */
};

#define HIT_MATCH_ANY 0xe
#define HIT_FLAG_BIT0 0x1
#define HIT_FLAG_BIT2 0x4
#define HIT_FLAG_FULL 0x20
#define CONTACT_LANDED 0x1
#define CONTACT_VETO 0x40
#define CONTACT_STATE_4 4
#define RULE_HIT_BIT0 0x30
#define SIDE_A 0
#define SIDE_B 1
#define SIDE_BOTH 2
#define SPREAD_FULL 0x1000
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4
#define NET_RECORD_CONTACT 1
#define NET_TAG_CONTACT 0xa3d

extern short data_0203d210[];            /* sin, cos pairs by angle >> 4 */

extern int func_ov022_0209fc48(struct Actor *pActor, int nSide);      /* side record armed */
extern void func_ov022_020ad7f0(struct Actor *pActor, int nSlot, VecFx32 *pOut);   /* Ov022_GetSlotPos */
extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void MTX_MultVec33(VecFx32 *pVec, MtxFx33 *pMtx, VecFx32 *pOut);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_ov022_020a22f0(struct Actor *pActor, int bFull, int *pMatchMask,
                               u8 *pAmount);                   /* Ov022_SearchMatchingRow */
extern int func_ov022_020a1f84(struct Actor *pActor, int nFace, int nMatchMask, int bFull);
extern int func_020358f4(int nId, int nRule);
extern int func_ov022_020a0fb8(struct Actor *pActor, struct FanQuery *pFan,
                               struct SweepHit *pCtx);          /* Ov022_RunCommandHandlers */
extern int FX_Atan2(int x, int z);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);       /* VEC_Normalize */
extern void func_ov022_020a5f28(struct Actor *pActor, int nKind, u32 nAngle,
                                VecFx32 *pAt);                 /* Ov022_EmitEventBlocks */
extern void func_ov022_020ad208(struct Actor *pActor, int nRecord, VecFx32 *pAt, int nTag,
                                u32 nAngle, int nKind);        /* Ov022_MarshalNetworkRecord */

void func_ov022_020a59b8(struct Actor *pActor, struct ComboSlot *pSlot, short *pHitIds, int bFull)
{
    struct FanQuery fan;
    struct SweepHit ctx;
    VecFx32 vecAt;
    VecFx32 vecToApex;
    MtxFx33 mtx;
    VecFx32 vecOff;
    VecFx32 vecSpare;
    int nSend;
    int nSlot;
    u16 nAngle;
    int nTrig;
    int nSinNeg;
    int nCosNeg;
    int nHit;
    int nKind;
    u16 nAxis;
    int nPushX;
    int nPushY;

    nSend = 0;
    ctx.pPart = 0;
    if (pSlot->nStartFrame > pActor->nAnimFrame) {
        return;
    }
    if (pSlot->nEndFrame <= pActor->nAnimFrame) {
        return;
    }
    if (pSlot->nSide != SIDE_BOTH && func_ov022_0209fc48(pActor, pSlot->nSide) == 0) {
        return;
    }
    func_ov022_020ad7f0(pActor, pActor->nSlotSpare, &vecSpare);
    switch (pSlot->nSide) {
    case SIDE_A:
        nSlot = pActor->nSlotSideA;
        break;
    case SIDE_B:
        nSlot = pActor->nSlotSideB;
        break;
    case SIDE_BOTH:
        nSlot = pActor->nSlotSideA;
        break;
    }
    nAngle = pActor->pNode->nAngle - ANGLE_BIAS;
    nTrig = (nAngle >> ANGLE_STEP) * 2;
    nCosNeg = -data_0203d210[nTrig + 1];
    nSinNeg = -data_0203d210[nTrig];
    MTX_RotY33_(&mtx, nSinNeg, nCosNeg);
    func_ov022_020ad7f0(pActor, nSlot, &vecOff);
    VEC_Subtract(&vecOff, &vecSpare, &vecOff);
    MTX_MultVec33(&vecOff, &mtx, &vecOff);
    VEC_Add(&vecOff, &pActor->vecAim, &fan.vecOrigin);
    fan.vecDir.x = nSinNeg;
    fan.vecDir.z = nCosNeg;
    fan.vecDir.y = 0;
    fan.nRadius = pSlot->nRadius1c;
    fan.nGroup = pActor->nSlotIndex;
    fan.nCosSpread = SPREAD_FULL;
    ctx.nMatchMask = HIT_MATCH_ANY;
    fan.pHitIds = pHitIds;
    fan.nFlags = 0;
    ctx.nAmount = 0;
    ctx.bMatched = func_ov022_020a22f0(pActor, bFull, &ctx.nMatchMask, &ctx.nAmount);
    ctx.nFace = func_ov022_020a1f84(pActor, pSlot->nFace, ctx.nMatchMask, bFull);
    ctx.nFlags = HIT_FLAG_BIT2;
    if (func_020358f4(pActor->nId, RULE_HIT_BIT0) != 0) {
        ctx.nFlags |= HIT_FLAG_BIT0;
    }
    nPushX = pSlot->nPushX;
    nPushY = pSlot->nPushY;
    ctx.vecPush.x = 0;
    ctx.vecPush.y = nPushY;
    ctx.vecPush.z = nPushX;
    ctx.nMode = 1;
    if (bFull) {
        ctx.nFlags |= HIT_FLAG_FULL;
    }
    ctx.bHeld = pSlot->bHeld;
    ctx.nField24 = 0;
    nHit = func_ov022_020a0fb8(pActor, &fan, &ctx);
    if (nHit != 0 && (pActor->contact.nResult & CONTACT_VETO) != 0) {
        nHit = 0;
        pActor->contact.nResult = 0;
        pActor->contact.nState = 0;
    }
    if (nHit != 0) {
        nAxis = FX_Atan2(fan.vecDir.x, fan.vecDir.z);
        VEC_Subtract(&fan.vecOrigin, &pActor->contact.vec, &vecToApex);
        func_01ff8d18(&vecToApex, &vecToApex);
        VEC_Add(&vecToApex, &pActor->contact.vec, &vecAt);
        nKind = pSlot->nEventKind21;
        if (bFull) {
            nKind++;
        }
        func_ov022_020a5f28(pActor, nKind, nAxis, &vecAt);
    }
    if ((pActor->contact.nResult & CONTACT_LANDED) != 0) {
        nSend = 1;
    } else if (pActor->contact.nState == CONTACT_STATE_4) {
        nSend = pActor->contact.nKind;
        if (nSend == 4) {
            nSend = 0;
        }
        if (nSend == 2 && pSlot->bNetwork == 0) {
            nSend = 0;
        }
    }
    if (nSend <= 0) {
        return;
    }
    nAxis = FX_Atan2(fan.vecDir.x, fan.vecDir.z);
    vecAt = fan.vecOrigin;
    func_ov022_020ad208(pActor, NET_RECORD_CONTACT, &vecAt, NET_TAG_CONTACT, nAxis,
                        pSlot->nEventKind21);
}
