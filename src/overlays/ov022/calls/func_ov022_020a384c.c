/* Ov022_SetAnimState -- switch the actor to animation nAnim.
 *
 * The node slot resources of the current animation are released first.
 * While flag bits 28 and 48 are both up the request's own animation (when
 * it has one) is played instead, becomes current, and both bits drop. A
 * repeat of the current animation is ignored -- for the slot-driven ones
 * (0x17..0x1a) only on the local player. The animation source depends on
 * the id: 0..0xb come from the main track, 0xc..0x16 from the six render
 * slots (0x13 with flags2 bit 11 first rotates the reaction block about
 * the facing at the sub position, 0x15/0x16 with flags2 bit 56 apply the
 * position to the reach block), 0x17..0x19 and 0x1a are slot animations --
 * the local player dispatches them through the request header (mode 0x12
 * or 0x11, flag bit 33) and records the value, a remote player takes the
 * request's track when the header accepts it (0x1a also initialising the
 * reaction block) -- 0x1e..0x2d are combo entries and 0x2e up run entries.
 * The blend frames come from the mode pair and the model.
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

#define FLAG_BIT28 (1ULL << 28)
#define FLAG_BIT33 (1ULL << 33)
#define FLAG_BIT48 (1ULL << 48)
#define FLAG2_BIT11 (1ULL << 11)
#define FLAG2_BIT56 (1ULL << 56)
#define ANIM_SLOT_FIRST 0x17
#define ANIM_SLOT_LAST 0x1a
#define ANIM_COMBO_FIRST 0x1e
#define ANIM_RUN_FIRST 0x2e
#define ANGLE_HALF 0x8000
#define HEADER_MODE_A 0x12
#define HEADER_MODE_B 0x11

/* Ov022AnimTrack: the request's track, its animation at +4 */
struct AnimTrack {
    u8 pad0000[4];
    u8 anim;                     /* 0x04 */
};

/* Ov022AnimRequest */
struct AnimRequest {
    struct AnimTrack *pTrack;    /* 0x00 */
    u8 pad0004[0xc];
};

/* Ov022ActorNode */
struct Node {
    u8 pad0000[0x80];
    u16 nAngle;                  /* 0x80 */
};

/* Ov022RenderSlot */
struct RenderSlot {
    u8 blk[0x24];
};

struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[4];
    int nModelId;                /* 0x000c */
    u8 pad0010[0x10];
    struct Node *pNode;          /* 0x0020 */
    u8 pad0024[0x440];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    struct Vec3 vecAim;          /* 0x048c */
    u8 pad0498[0x46];
    u16 nLatchedArg;             /* 0x04de */
    u8 pad04e0[3];
    volatile signed char nField4e3;   /* 0x04e3, the synced record: read in order */
    volatile u16 nField4e4;      /* 0x04e4 */
    volatile u16 nField4e6;      /* 0x04e6 */
    u8 pad04e8[0x1d4];
    int nAnimId;                 /* 0x06bc, the current animation (was nHitReaction) */
    u8 pad06c0[0x250];
    u8 combo[0x480];             /* 0x0910 Ov022ComboState */
    struct AnimRequest animReq;  /* 0x0d90 */
    u8 pad0da0[0x3f8];
    u8 reactBlk[0x180];          /* 0x1198 */
    u8 pad1318[0x974];
    u8 blkReach[0x11c];          /* 0x1c8c */
    u8 reactionBlk[0x4e0];       /* 0x1da8 */
    u8 reactionCtx[0x70];        /* 0x2288 Ov022ReactionCtx */
    u8 run[0x7c8];               /* 0x22f8 Ov022ActionOwner */
    struct RenderSlot aRenderSlots[6];   /* 0x2ac0 */
};

extern void func_ov022_020a46f8(struct Actor *pActor, int nAnim);               /* Ov022_ReleaseNodeSlotResources */
extern int func_ov022_020b1ba0(struct AnimRequest *pReq);                       /* Ov022_GetByteCOrA */
extern int func_ov002_020519b0(int nNewMode, int nOldMode, int nKind);          /* Ov002_GetModeBlendFrames */
extern void func_ov022_020a3c78(struct Actor *pActor, void *pAnim, int nSub, int nBlend);   /* SetSlot2c28AndPlay */
extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern void func_ov022_020ad44c(struct Vec3 *pOut, struct Actor *pActor);       /* CopyVec3FromSub948 */
extern void func_ov022_02092b60(u8 *pBlk, struct Vec3 *pVec, int nAngle);       /* Ov022_RotateAboutAxis */
extern void func_ov022_020941a0(u8 *pBlk, struct Vec3 *pVec);                   /* Ov022_ApplyVec3AndResetTracks */
extern int func_ov022_02090978(u8 *pCtx, int nSlotState);                       /* Ov022_GetSlotMoveMode */
extern void func_ov022_020b19cc(struct AnimRequest *pReq, int nAnim, int nMode);   /* SetSlotHeaderDispatch */
extern void func_ov022_020902d4(u8 *pCtx, int nValue);                          /* Ov022_SetRecordValue */
extern int func_ov022_020b19ec(struct AnimRequest *pReq, int nAnim);            /* SetSlotHeaderReturnState3 */
extern void func_ov022_02093c0c(u8 *pBlk);                                      /* SetByte1And4Dispatch */
extern void func_ov022_02093c48(u8 *pBlk, int nA, int nB, int nC);              /* InitStateAndDispatch */
extern void *func_ov022_020b0ba8(u8 *pCombo, int nKind);                        /* Ov022_FindEntryByKind */
extern void *func_ov022_02095600(u8 *pRun);                                     /* ov022_GetWordAt0x340Plus4 */

void func_ov022_020a384c(struct Actor *pActor, int nAnim)
{
    struct Vec3 vecSub;
    int bSkip;
    int bChanged;
    int nSub;
    void *pAnim;
    int nOwn;
    int nBlend;

    bSkip = 0;
    pAnim = 0;
    bChanged = 1;
    func_ov022_020a46f8(pActor, nAnim);
    if ((pActor->nFlags & FLAG_BIT28) != 0 && (pActor->nFlags & FLAG_BIT48) != 0) {
        if (func_ov022_020b1ba0(&pActor->animReq) >= 0) {
            nOwn = func_ov022_020b1ba0(&pActor->animReq);
            nBlend = func_ov002_020519b0(nOwn, -1, pActor->nModelId);
            func_ov022_020a3c78(pActor, &pActor->animReq.pTrack->anim, 0, nBlend);
            pActor->nAnimId = func_ov022_020b1ba0(&pActor->animReq);
        }
        pActor->nFlags &= ~FLAG_BIT48;
        pActor->nFlags &= ~FLAG_BIT28;
        return;
    }
    switch (nAnim) {
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
        if (func_02030788() == 0 && nAnim == pActor->nAnimId) {
            bChanged = 0;
        }
        break;
    default:
        if (nAnim < ANIM_COMBO_FIRST && nAnim == pActor->nAnimId) {
            bChanged = 0;
        }
        break;
    }
    if (!bChanged) {
        return;
    }
    switch (nAnim) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xa:
    case 0xb:
        nSub = nAnim;
        pAnim = 0;
        break;
    case 0xc:
    case 0xd:
        pAnim = &pActor->aRenderSlots[5];
        nSub = nAnim - 0xc;
        break;
    case 0x10:
        pAnim = &pActor->aRenderSlots[2];
        nSub = 0;
        break;
    case 0x13:
    case 0x14:
        if (nAnim == 0x13 && (pActor->nFlags2 & FLAG2_BIT11) != 0) {
            func_ov022_020ad44c(&vecSub, pActor);
            func_ov022_02092b60(pActor->reactBlk, &vecSub, (u16)(pActor->pNode->nAngle - ANGLE_HALF));
        }
        pAnim = &pActor->aRenderSlots[1];
        nSub = nAnim - 0x13;
        break;
    case 0xe:
    case 0xf:
        pAnim = &pActor->aRenderSlots[0];
        nSub = nAnim - 0xe;
        break;
    case 0x11:
    case 0x12:
        pAnim = &pActor->aRenderSlots[3];
        nSub = nAnim - 0x11;
        break;
    case 0x15:
    case 0x16:
        if ((pActor->nFlags2 & FLAG2_BIT56) != 0) {
            func_ov022_020941a0(pActor->blkReach, &pActor->vecAim);
        }
        pAnim = &pActor->aRenderSlots[4];
        nSub = nAnim - 0x15;
        break;
    case 0x17:
    case 0x18:
    case 0x19:
        if (func_02030788() == 0) {
            nAnim = func_ov022_02090978(pActor->reactionCtx, pActor->nLatchedArg);
            pActor->nFlags |= FLAG_BIT33;
            func_ov022_020b19cc(&pActor->animReq, nAnim, HEADER_MODE_A);
            func_ov022_020902d4(pActor->reactionCtx, pActor->nLatchedArg);
            bSkip = 1;
        } else if (func_ov022_020b19ec(&pActor->animReq, nAnim) == 0) {
            bSkip = 1;
        } else {
            pAnim = &pActor->animReq.pTrack->anim;
            nSub = 0;
        }
        break;
    case 0x1a:
        if (func_02030788() == 0) {
            pActor->nFlags |= FLAG_BIT33;
            func_ov022_020b19cc(&pActor->animReq, nAnim, HEADER_MODE_B);
            func_ov022_02093c0c(pActor->reactionBlk);
            bSkip = 1;
        } else if (func_ov022_020b19ec(&pActor->animReq, nAnim) == 0) {
            bSkip = 1;
        } else {
            func_ov022_02093c48(pActor->reactionBlk, pActor->nField4e4, pActor->nField4e3, pActor->nField4e6);
            pAnim = &pActor->animReq.pTrack->anim;
            nSub = 0;
        }
        break;
    default:
        if (nAnim >= ANIM_COMBO_FIRST && nAnim < ANIM_RUN_FIRST) {
            pAnim = func_ov022_020b0ba8(pActor->combo, nAnim - ANIM_COMBO_FIRST);
            nSub = 0;
        } else if (nAnim >= ANIM_RUN_FIRST) {
            pAnim = func_ov022_02095600(pActor->run);
            nSub = nAnim - ANIM_RUN_FIRST;
        }
        break;
    }
    nBlend = func_ov002_020519b0(nAnim, pActor->nAnimId, pActor->nModelId);
    if (!bSkip) {
        func_ov022_020a3c78(pActor, pAnim, nSub, nBlend);
    }
    pActor->nAnimId = nAnim;
}
