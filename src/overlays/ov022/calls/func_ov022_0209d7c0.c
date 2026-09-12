/* Ov022_TryBlockHit -- decide whether a hit request is taken as a block
 * (guard) and, when it is, turn the actor into the block reaction and tell
 * the attacker; returns 1 when the hit was blocked.
 *
 * Requests with flag bits 3 or 7, and actors with flag bits 4 or 13 or
 * flags2 bit 8, cannot block. Rule 0x20 makes the block automatic, rule
 * 0x21 lets a finisher trigger, rule 0x12 with flags2 bit 14 (timer under
 * 9.0, menu state not 0xb) or flags2 bit 12 with reaction slot 0xc and the
 * trigger held guards; without a guard the slot block must be ready, some
 * slot flag set and the menu state not 0xb. A push with no flat part has
 * no direction. With flags2 bit 32 (a manual block) a non-automatic block
 * needs the push to come from the front (the heading difference outside
 * 0x5000..0xb000); otherwise a finisher rolls the desc's chance (flag bit
 * 16), needs the push to face the actor (dot at least 0.75) and raises
 * flags3 bit 9 for the local player, while a plain guard needs nothing and
 * anything else refuses. For the local player: a non-guard block raises
 * flags3 bit 26, keeps the push as the drift and faces it (or the node's
 * facing under rule 0x18 with a push under 1.0); in anim 0x11 a finisher-
 * less actor under 9.0 raises flag bit 31 with an interrupt record under
 * rule 0x16, rule 0x1f fires event 2/1 half the time unless the request has
 * bit 1, and the timer restarts; flags2 bit 9 runs the pre-draw hook with
 * 0x12, dispatches 0, resets the scale, drops flag bit 17, disables the
 * node and charges the interrupt 3.0; request bit 1 sends the attacker a
 * block packet (kind 0x11, 0x111 with flag bit 16; a non-guard adds the
 * block kinds allowed by rules 0x1b..0x1e) and flags3 bit 45 marks it
 * accepted (bit 44 otherwise). The request is marked handled.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed long long s64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x000 */
    u16 nAnimFlags;              /* 0x004 */
    u8 pad006[0x7a];
    u16 nAngle;                  /* 0x080 */
};

/* Ov022HitRequest */
struct HitRequest {
    u32 nFlags;                  /* 0x00 */
    VecFx32 vecPush;             /* 0x04 */
    int nDamage;                 /* 0x10 */
    int nKind;                   /* 0x14 */
    u8 nStrength;                /* 0x18 */
    u8 pad19[3];
    struct Actor *pActor;        /* 0x1c */
    int nField20;                /* 0x20 */
    u32 nResult;                 /* 0x24 */
};

/* PlayerSlotDesc */
struct SlotDesc {
    u8 pad00[0x10];
    int nBlockChance;            /* 0x10 */
};

/* PlayerSlot */
struct PlayerSlot {
    u8 pad00[0x44];
    struct SlotDesc *pDesc;      /* 0x44 */
};

/* Ov107HitPacket: the block packet handed to the attacker (16-bit halves as bitfields) */
struct HitPacket {
    u32 nFlags : 16;             /* 0x00: 0x11, 0x111 with flag bit 16 */
    u32 nKindMask : 16;          /* 0x02: one bit per allowed block kind */
    VecFx32 vecPos;              /* 0x04 */
    int nBase : 16;              /* 0x10 */
    int nDamage : 16;            /* 0x12 */
    u32 nId : 16;                /* 0x14: the blocking actor */
    u32 nField16 : 16;
    void *pNode;                 /* 0x18 */
    u8 nStrength;                /* 0x1c: 0xf when block kinds are allowed */
    u8 nExtraByte;               /* 0x1d */
    u8 pad1e[6];
    u16 nResult;                 /* 0x24 */
    u8 pad26[6];
};

struct BlockKinds {
    int a[4];
};

struct Actor;

typedef void (*ActorHookFn)(struct Actor *pActor, int nArg);   /* Ov022ActorHookFn */

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x16];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x440];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[8];
    VecFx32 vecDrift;            /* 0x047c */
    u8 pad0488[0x2c];
    int nInterruptCharge;        /* 0x04b4 */
    u8 pad04b8[0x14];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x1c];
    void *pSub;                  /* 0x04ec */
    u8 pad04f0[0x174];
    ActorHookFn pfnPreDraw;      /* 0x0664 */
    u8 pad0668[0x2c];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;
    u8 bSequenceRunning : 1;
    u8 bVoicePlayed : 1;
    u8 bTriggerHeld : 1;         /* 0x0694 bit 6 */
    u8 nSpare6947 : 1;
    u8 pad0695[0x27];
    int nAnimId;                 /* 0x06bc */
    u8 pad06c0[0x9b0];
    u8 slotBlk;                  /* 0x1070 */
    u8 pad1071[0x1223];
    int nReactionSlot;           /* 0x2294 reactionCtx.nSlot */
    u8 pad2298[0x820];
    u8 nMenuState;               /* 0x2ab8 */
};

#define REQ_NO_BLOCK 0x8
#define REQ_UNBLOCKABLE 0x80
#define REQ_NO_EVENT 0x2
#define REQ_NOTIFY 0x1
#define FLAG_BIT4 (1ULL << 4)
#define FLAG_BIT13 (1ULL << 13)
#define FLAG_BIT16 (1ULL << 16)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG_BIT31 (1ULL << 31)
#define FLAG2_BIT8 (1ULL << 8)
#define FLAG2_BIT9 (1ULL << 9)
#define FLAG2_BIT12 (1ULL << 12)
#define FLAG2_BIT14 (1ULL << 14)
#define FLAG2_BIT32 (1ULL << 32)
#define FLAG3_BIT9 (1ULL << 9)
#define FLAG3_BIT26 (1ULL << 26)
#define FLAG3_BIT44 (1ULL << 44)
#define FLAG3_BIT45 (1ULL << 45)
#define RULE_AUTO_BLOCK 0x20
#define RULE_FINISHER 0x21
#define RULE_GUARD 0x12
#define RULE_FACE_HELD 0x18
#define RULE_INTERRUPT 0x16
#define RULE_EVENT 0x1f
#define RULE_KIND_BASE 0x1b
#define TIMER_LIMIT 0x9000
#define MENU_STATE_LOCKED 0xb
#define REACTION_SLOT_GUARD 0xc
#define ANIM_BLOCK 0x11
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define BEHIND_MIN 0x5000
#define BEHIND_MAX 0xb000
#define FACING_MIN 0xc00
#define PUSH_SHORT 0x1000
#define CHANCE_SCALE 0x64000
#define EVENT_CHANCE 0x32000
#define INTERRUPT_CHARGE 0x3000
#define PREDRAW_BLOCK 0x12
#define PACKET_KIND 0x11
#define PACKET_KIND_STRONG_BIT 0x100
#define PACKET_COUNT 0xf

extern short data_0203d210[];                    /* kFxSinCosTable: sin, cos pairs */
extern const struct BlockKinds data_ov022_020b25e4;   /* kOv022BlockKinds: 7, 3, 11, 2 */

extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_02095d10(struct Actor *pActor);                           /* Ov022_CanTriggerFinisher */
extern int func_ov022_020926f8(u8 *pBlk);                                       /* slot block ready */
extern int func_ov022_0209fc78(struct Actor *pActor, int nSlot);                /* IsAnySlotFlagSet */
extern short FX_Atan2(int y, int x);
extern struct PlayerSlot *func_020358a4(int nSlot);                             /* GetPlayerSlotTableEntry */
extern int func_0203084c(void);                                                 /* Session_RandNext */
extern int func_01ff8d18(VecFx32 *pIn, VecFx32 *pOut);                          /* VEC_Normalize */
extern int VEC_DotProduct(VecFx32 *pA, VecFx32 *pB);
extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int VEC_Mag(VecFx32 *pVec);
extern void func_ov022_0209ccf4(struct Actor *pActor);                          /* Ov022_SendInterruptRecord */
extern void func_ov022_0208a0b4(int nId, int nEvent, int nArg);                 /* MarshalEventPacketSix */
extern void func_ov022_02097038(struct Actor *pActor, int nArg);                /* SetField7b0AndDispatch */
extern void func_ov022_020acebc(struct Actor *pActor, int nScale);              /* ConfigFlag40AndScale */
extern void func_0202af2c(u16 *pAnimFlags);                                     /* SceneNode_Disable */
extern int func_ov107_020c5cfc(struct Actor *pAttacker, void *pSub, struct HitPacket *pPacket);   /* the attacker takes the block */

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

int func_ov022_0209d7c0(struct Actor *pActor, struct HitRequest *pReq)
{
    VecFx32 vecFacing;
    VecFx32 vecDir;
    VecFx32 vecFace;
    struct HitPacket packet;
    int aList[4];
    struct BlockKinds kinds;
    int bGuard;
    int bFinisher;
    int bAuto;
    int bHasDir;
    int nReject;
    int nTrig;
    int nTrig2;
    u16 nFace;
    u16 nAngle;
    u16 nHit;
    int nDiff;
    int nAllowed;
    int i;
    int bSent;
    struct PlayerSlot *pSlot;
    struct ActorNode *pNode;
    struct Actor *pAttacker;

    bFinisher = 0;
    bAuto = 0;
    bGuard = 0;
    bHasDir = 1;
    if ((pReq->nFlags & REQ_NO_BLOCK) != 0) {
        return 0;
    }
    if ((pReq->nFlags & REQ_UNBLOCKABLE) != 0) {
        return 0;
    }
    if ((pActor->nFlags & FLAG_BIT4) != 0 || (pActor->nFlags & FLAG_BIT13) != 0 || (pActor->nFlags2 & FLAG2_BIT8) != 0) {
        return 0;
    }
    if (func_020358f4(pActor->nId, RULE_AUTO_BLOCK) != 0) {
        bAuto = 1;
    }
    if (func_020358f4(pActor->nId, RULE_FINISHER) != 0) {
        bFinisher = func_ov022_02095d10(pActor);
    }
    if (func_020358f4(pActor->nId, RULE_GUARD) != 0 && (pActor->nFlags2 & FLAG2_BIT14) != 0
        && (int)pActor->nStateTimer <= TIMER_LIMIT && pActor->nMenuState != MENU_STATE_LOCKED) {
        bGuard = 1;
    }
    if ((pActor->nFlags2 & FLAG2_BIT12) != 0 && pActor->nReactionSlot == REACTION_SLOT_GUARD && pActor->bTriggerHeld) {
        bGuard = 1;
    }
    if (!bGuard) {
        if (!func_ov022_020926f8(&pActor->slotBlk)) {
            return 0;
        }
        if (!func_ov022_0209fc78(pActor, -1)) {
            return 0;
        }
        if (pActor->nMenuState == MENU_STATE_LOCKED) {
            return 0;
        }
    }
    if (pReq->vecPush.x == 0 && pReq->vecPush.z == 0) {
        bHasDir = 0;
    }
    if ((pActor->nFlags2 & FLAG2_BIT32) != 0) {
        if (bAuto == 0 && bHasDir) {
            nFace = pActor->pNode->nAngle - ANGLE_BIAS;
            nAngle = nFace + ANGLE_BIAS;
            nHit = FX_Atan2(-pReq->vecPush.x, -pReq->vecPush.z);
            nDiff = (u16)(nAngle - nHit);
            if (nDiff > BEHIND_MIN && nDiff < BEHIND_MAX) {
                return 0;
            }
        }
    } else if (bFinisher) {
        if ((u32)(pActor->nFlags & FLAG_BIT16) != 0) {
            pSlot = func_020358a4((u8)(pActor->nId - 1));
            if (pSlot != 0 && pSlot->pDesc != 0) {
                if (FxMul(func_0203084c(), CHANCE_SCALE) > pSlot->pDesc->nBlockChance) {
                    return 0;
                }
            }
        }
        if (bHasDir) {
            nTrig = ((u16)((u16)(pActor->pNode->nAngle - ANGLE_BIAS) + ANGLE_BIAS) >> 4) * 2;
            vecFacing.x = -data_0203d210[nTrig];
            /* Capture the stored zero; its live range across the calls matters. */
            nReject = vecFacing.y = 0;
            vecFacing.z = -data_0203d210[nTrig + 1];
            vecDir = pReq->vecPush;
            vecDir.y = nReject;
            func_01ff8d18(&vecDir, &vecDir);
            if (VEC_DotProduct(&vecDir, &vecFacing) < FACING_MIN) {
                return nReject;
            }
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT9;
        }
    } else if (!bGuard) {
        return 0;
    }
    if ((pActor->nFlags2 & FLAG2_BIT32) == 0 && !bFinisher && !bGuard) {
        return 0;
    }
    if (func_02030788() == 0) {
        bSent = 0;
        if (!bGuard) {
            pActor->nFlags3 |= FLAG3_BIT26;
            pActor->vecDrift = pReq->vecPush;
            if (bHasDir) {
                nHit = (u16)FX_Atan2(pActor->vecDrift.x, pActor->vecDrift.z);
                pNode = pActor->pNode;
                if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                    pNode->nAngle = nHit + ANGLE_BIAS;
                    pNode->nAnimFlags |= ANIM_HOLD;
                }
            }
            if (func_020358f4(pActor->nId, RULE_FACE_HELD) != 0 && VEC_Mag(&pReq->vecPush) < PUSH_SHORT) {
                nTrig2 = ((u16)((u16)(pActor->pNode->nAngle - ANGLE_BIAS) + ANGLE_BIAS) >> 4) * 2;
                {
                    int nSin;
                    int nCos;
                    nSin = -data_0203d210[nTrig2];
                    nCos = -data_0203d210[nTrig2 + 1];
                    vecFace.x = nSin;
                    vecFace.z = nCos;
                    vecFace.y = 0;
                }
                pActor->vecDrift = vecFace;
            }
        }
        if (pActor->nAnimId == ANIM_BLOCK) {
            if ((int)pActor->nStateTimer <= TIMER_LIMIT && (pActor->nFlags & FLAG_BIT31) == 0 && bFinisher != 1
                && func_020358f4(pActor->nId, RULE_INTERRUPT) != 0) {
                pActor->nFlags |= FLAG_BIT31;
                func_ov022_0209ccf4(pActor);
            }
            if ((pReq->nFlags & REQ_NO_EVENT) == 0 && func_020358f4(pActor->nId, RULE_EVENT) != 0
                && FxMul(func_0203084c(), CHANCE_SCALE) < EVENT_CHANCE) {
                func_ov022_0208a0b4(pActor->nId, 2, 1);
            }
            pActor->nStateTimer = 0;
        }
        if ((pActor->nFlags2 & FLAG2_BIT9) != 0) {
            pActor->pfnPreDraw(pActor, PREDRAW_BLOCK);
            func_ov022_02097038(pActor, 0);
            func_ov022_020acebc(pActor, 0x1000);
            pActor->nFlags &= ~FLAG_BIT49;
            if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
                func_0202af2c(&pActor->pNode->nAnimFlags);
            }
            pActor->nInterruptCharge = INTERRUPT_CHARGE;
        }
        if ((pReq->nFlags & REQ_NOTIFY) != 0) {
            pAttacker = pReq->pActor;
            packet.vecPos.z = 0;
            packet.vecPos.y = 0;
            packet.vecPos.x = 0;
            packet.nBase = 0;
            packet.nDamage = 0;
            packet.nFlags = PACKET_KIND;
            packet.pNode = 0;
            packet.nId = pActor->nId;
            packet.nKindMask = 0;
            packet.nStrength = 0;
            if ((u32)(pActor->nFlags & FLAG_BIT16) != 0) {
                packet.nFlags |= PACKET_KIND_STRONG_BIT;
            }
            if (!bGuard) {
                kinds = data_ov022_020b25e4;
                nAllowed = 0;
                for (i = 0; i < 4; i++) {
                    if (func_020358f4(pActor->nId, i + RULE_KIND_BASE) != 0) {
                        aList[nAllowed++] = kinds.a[i];
                    }
                }
                if (nAllowed > 0) {
                    packet.nStrength = PACKET_COUNT;
                    for (i = 0; i < nAllowed; i++) {
                        packet.nKindMask |= 1 << aList[i];
                    }
                }
            }
            if (func_ov107_020c5cfc(pAttacker, pActor->pSub, &packet) != 0) {
                bSent = 1;
            }
        }
        if (bSent) {
            pActor->nFlags3 |= FLAG3_BIT45;
        } else {
            pActor->nFlags3 |= FLAG3_BIT44;
        }
    }
    pReq->nResult |= 1;
    return 1;
}
