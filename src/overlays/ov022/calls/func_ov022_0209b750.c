/* Ov022_StepChargeSequence -- one frame of the actor's charge sequence (the
 * knockdown-kind phase machine kept in the charge block); returns the state
 * step change it made, or 0.
 *
 * The phase is mirrored into nMenuState. A released charge raises flags2 bit
 * 50 for the local player. Per phase: 1 drops button 2 on both button words
 * and waits 67.5; 2 turns the node by 30 degrees and, from 3.0 on with input
 * bit 2, ends the sequence (limit 45.0); 3 leaves a state other than the
 * ab8d0 step from 5.0 on into state 0x1a (flags3 bit 57, entry 0x14 cleared)
 * and waits 90.0 less 2.0 per count (at least 1.0); 5 stops the meter under
 * flags2 bit 8, otherwise swaps the paired state flags and waits 75.0; 6, 9
 * and 0xc wait 150.0, 0xa waits 75.0; 7 deals, every 30.0, one per cent of
 * the max HP (the fraction carried in the accumulator, capped to leave 1 HP)
 * as request 0x31a, counting the deals, and ends after 18 deals or with HP
 * under 2; 0xb raises flags2 bit 49 for the local player and, under 30.0,
 * disarms the charge, else from 30.0 on sweeps a fan of ten per cent of the
 * max HP (at least 1.0) at the slot: a taken command counts as a hit unless
 * the held kind is 4 with hit kind 2; otherwise a marshalled hit counts
 * unless it is kind 2 or a kind-1 hit whose four contacts include a
 * pass-through surface; a hit or an armed charge fires the release, and the
 * phase waits 112.5; 0xe stops the meter and, while the mission clear has
 * not finished and rule 0x47 holds, ticks the level timer. The meter then
 * advances by the frame step and, past a positive limit outside phase 0xe,
 * the sequence ends.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

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

/* Ov022Charge */
struct Charge {
    s8 nKnockdownKind;           /* 0x00: the phase */
    u8 pad01[3];
    int nMeter;                  /* 0x04 */
    int nCount;                  /* 0x08 */
    u8 bReleased : 1;            /* 0x0c bit 0 */
    u8 bArmed : 1;               /* 0x0c bit 1 */
    u8 pad0d[3];
    int nAccum;                  /* 0x10 */
    int nEntry;                  /* 0x14 */
};

struct Actor;

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

/* Ov022EffectPlace */
struct EffectPlace {
    VecFx32 vecAt;               /* 0x00 */
    int nScaleX;                 /* 0x0c */
    int nSlotIndex;              /* 0x10 */
    VecFx32 vecFace;             /* 0x14 */
    int nScaleZ;                 /* 0x20 */
    void *pTail;                 /* 0x24 */
    int nField28;                /* 0x28 */
};

/* Ov022SweepHit: the 40-byte hit context the command handlers take */
struct SweepHit {
    int nFace;                   /* 0x00: here the fan radius in whole units */
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
    u8 pad26[2];
};

/* Ov022SweepContact */
struct SweepContact {
    u32 nResult;                 /* 0x00 */
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[3];
    VecFx32 vec;                 /* 0x0c */
    void *pOwner;                /* 0x18 */
    struct SweepHit hit;         /* 0x1c: nFace is the collision handle, pPart the contact bytes */
    u8 pad44[0x70];
};

/* CollSurfaceAttr */
struct CollSurfaceAttr {
    u8 pad00[0xc];
    u8 aTags[4];                 /* 0x0c */
    u8 pad10[4];
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[2];
    u16 nHpMax;                  /* 0x0016 */
    u16 nButtons;                /* 0x0018 */
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[4];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x3e];
    short nSlotIndex;            /* 0x0066 */
    u8 pad0068[0x3f8];
    void *pfnState;              /* 0x0460 */
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x2248];
    struct SweepContact contact; /* 0x26bc */
    struct Charge charge;        /* 0x2770 */
    u8 pad2788[0x330];
    u8 nMenuState;               /* 0x2ab8 */
};

#define FLAG2_BIT8 (1ULL << 8)
#define FLAG2_BIT49 (1ULL << 49)
#define FLAG2_BIT50 (1ULL << 50)
#define FLAG3_BIT57 (1ULL << 57)
#define INPUT_BIT2 0x4
#define BUTTON_2 0x2
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define TURN_30DEG 0x1555
#define PHASE_END 0xe
#define STATE_LEAVE 0x1a
#define RULE_LEVEL_TIMER 0x47
#define DEAL_ID 0x31a
#define DEAL_PERIOD 0x1e000
#define DEAL_COUNT_MAX 0x12
#define FAN_SCALE 0x11cd
#define FAN_FLAGS 0x48
#define FAN_KIND 0xb
#define FAN_FACE 0x800
#define HIT_KIND_STOP 2
#define HELD_KIND_STOP 4
#define TAG_PASS_THROUGH 2
#define LIMIT_1 0x10e000
#define LIMIT_2 0xb4000
#define LIMIT_3 0x5a000
#define LIMIT_3_STEP 0x2000
#define LIMIT_5 0x12c000
#define LIMIT_6 0x258000
#define LIMIT_B 0x1c2000
#define METER_2 0x3000
#define METER_3 0x5000

extern const VecFx32 data_02041dc8;         /* kVecZero */
extern short data_0203d210[];               /* kFxSinCosTable: sin, cos pairs */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_ov002_0206e770(int nArg);                                       /* ov002_IsMissionClearFinished */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_02083f90(void);                                           /* Ov022_GetGlobal34 (frame step) */
extern void func_ov022_0209be64(struct Actor *pActor, int nStep);               /* Ov022_TickLevelTimer */
extern void func_ov022_0209bdbc(struct Actor *pActor);                          /* Ov022_SwapPairedStateFlags */
extern void func_ov022_0209b1e8(struct Actor *pActor);                          /* Ov022_EnterState0E */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);               /* Ov022_ActorSetState */
extern int func_ov022_020a08a8(struct Actor *pActor, struct HitRequest *pReq);  /* deal a hit request */
extern void func_ov022_020ad44c(VecFx32 *pOut, struct Actor *pActor);           /* CopyVec3FromSub948 */
extern int func_ov022_020a0fb8(struct Actor *pActor, struct EffectPlace *pPlace, struct SweepHit *pCtx);   /* Ov022_RunCommandHandlers */
extern void func_01ffa724(int nScale, VecFx32 *pIn, VecFx32 *pOut);             /* ScaleVec3Fx12 */
extern int func_ov022_020a1c28(struct Actor *pActor, struct EffectPlace *pPlace, struct SweepContact *pContact);   /* MarshalEightWords */
extern struct CollSurfaceAttr *func_0202c37c(struct SweepHit *pHit, int nTag);
extern void func_ov022_0209bd10(struct Actor *pActor);                          /* Ov022_FireChargeRelease */
extern int func_ov022_020ab8d0(struct Actor *pActor);                           /* a state step */

/* Kept inline: no extra call or out-of-line helper is emitted.
 * This spells the request initialization in ordinary C. Its argument binding,
 * together with the function-scoped MWCC option below, is important to the
 * register allocation of the original case-7 division and vector copy. */
static inline void Ov022_InitChargeHitRequest(struct HitRequest *r,
                                             struct Actor *actor,
                                             int id, int damage)
{
    r->vecPush = data_02041dc8;
    r->nFlags = id;
    r->nKind = 0;
    r->nDamage = damage;
    r->nStrength = 0;
    r->pActor = actor;
    r->nResult = 0;
    r->nField20 = 0;
}

/* Match-specific option, restored at the end of this translation unit.
 * Verified with the original MWCCARM 3.0 build 139 and the canonical flags. */
#pragma push
#pragma opt_dead_assignments off
int func_ov022_0209b750(struct Actor *pActor)
{
    struct SweepContact contact;
    struct HitRequest req;
    struct EffectPlace place;
    struct SweepHit ctx;
    int nRet;
    struct Charge *pCharge;
    int nLimit;
    int bTick;
    struct ActorNode *pNode;
    u16 nAngle;
    int nTrig;
    struct CollSurfaceAttr *pAttr;

    /* Shared across disjoint cases: fixed-point total in case 7,
     * boolean hit result (initialized again) in case 0xb. */
    int bHit;
    int i;
    int nRadius;

    pCharge = &pActor->charge;
    pActor->nMenuState = pActor->charge.nKnockdownKind;
    nRet = 0;
    nLimit = 0;
    bTick = 1;
    if (pCharge->bReleased && func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT50;
    }
    switch (pCharge->nKnockdownKind) {
    case PHASE_END:
        bTick = 0;
        if (func_ov002_0206e770(0) == 0 && func_020358f4(pActor->nId, RULE_LEVEL_TIMER) != 0) {
            func_ov022_0209be64(pActor, func_ov022_02083f90());
        }
        break;
    case 0xa:
        nLimit = LIMIT_5;
        break;
    case 9:
        nLimit = LIMIT_6;
        break;
    case 1:
        pActor->nButtons2 &= ~BUTTON_2;
        pActor->nButtons &= ~BUTTON_2;
        nLimit = LIMIT_1;
        break;
    case 5:
        if ((pActor->nFlags2 & FLAG2_BIT8) != 0) {
            bTick = 0;
        } else {
            func_ov022_0209bdbc(pActor);
            nLimit = LIMIT_5;
        }
        break;
    case 2:
        { const struct Actor *pRead = pActor;
          nAngle = pRead->pNode->nAngle - ANGLE_BIAS; }
        pNode = pActor->pNode;
        if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
            pNode->nAngle = (u16)(nAngle + TURN_30DEG) + ANGLE_BIAS;
            pNode->nAnimFlags |= ANIM_HOLD;
        }
        nLimit = LIMIT_2;
        if (pCharge->nMeter >= METER_2 && (pActor->nInputMask & INPUT_BIT2) != 0) {
            func_ov022_0209b1e8(pActor);
        }
        break;
    case 6:
        nLimit = LIMIT_6;
        break;
    case 3:
        if (pActor->pfnState != (void *)func_ov022_020ab8d0 && pActor->charge.nMeter >= METER_3) {
            pActor->nFlags3 |= FLAG3_BIT57;
            nRet = func_ov022_020a35f4(pActor, STATE_LEAVE);
            pCharge->nEntry = -1;
        }
        nLimit = LIMIT_3 - pCharge->nCount * LIMIT_3_STEP;
        if (nLimit <= 0) {
            nLimit = 0x1000;
        }
        break;
    case 7:
        if (pCharge->nMeter >= DEAL_PERIOD) {
            /* Keep the quotient FIRST and capture bHit inside the argument.
             * Moving this assignment to a preceding statement, reversing
             * the sum, or removing the scoped pragma changes the machine code.
             * All other arguments are side-effect-free and do not read bHit. */
            Ov022_InitChargeHitRequest(
                &req, pActor, DEAL_ID,
                (bHit = (pActor->nHpMax << 12) / 100 + pCharge->nAccum) >> 12);
            if (pActor->nHp <= (bHit >> 12)) {
                req.nDamage = pActor->nHp - 1;
            }
            if (req.nDamage > 0) {
                func_ov022_020a08a8(pActor, &req);
            }
            pCharge->nAccum = bHit & 0xfff;
            pCharge->nCount++;
            pCharge->nMeter = 0;
        }
        if (pCharge->nCount >= DEAL_COUNT_MAX || pActor->nHp <= 1) {
            func_ov022_0209b1e8(pActor);
        }
        break;
    case 0xb:
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT49;
        }
        if (pCharge->nMeter < DEAL_PERIOD) {
            pCharge->bArmed = 0;
        } else {
            nRadius = (pActor->nHpMax << 12) / 100 * 10;
            bHit = 0;
            if (nRadius < 0x1000) {
                nRadius = 0x1000;
            }
            if (pActor->nSlotIndex != -1) {
                func_ov022_020ad44c(&place.vecAt, pActor);
                place.nScaleX = FAN_SCALE;
                place.nSlotIndex = pActor->nSlotIndex;
                ctx.nFace = nRadius >> 12;
                ctx.nFlags = FAN_FLAGS;
                ctx.nMatchMask = FAN_KIND;
                ctx.vecPush = data_02041dc8;
                place.nScaleZ = 0x1000;
                ctx.bHeld = 0;
                ctx.bMatched = 0;
                place.vecFace.z = 0;
                place.vecFace.y = 0;
                place.vecFace.x = 0;
                place.pTail = 0;
                place.nField28 = 0;
                ctx.nMode = 0;
                ctx.nAmount = 0;
                ctx.pPart = 0;
                ctx.nField24 = 0;
                if (func_ov022_020a0fb8(pActor, &place, &ctx) != 0) {
                    bHit = 1;
                    if (pActor->contact.nState == HELD_KIND_STOP && pActor->contact.nKind == HIT_KIND_STOP) {
                        bHit = 0;
                    }
                } else {
                    nTrig = ((u16)(pActor->pNode->nAngle - ANGLE_BIAS) >> 4) * 2;
                    place.vecFace.x = -data_0203d210[nTrig];
                    place.vecFace.z = -data_0203d210[nTrig + 1];
                    place.vecFace.y = 0;
                    func_01ffa724(FAN_FACE, &place.vecFace, &place.vecFace);
                    if (func_ov022_020a1c28(pActor, &place, &contact) != 0) {
                        bHit = 1;
                        if (contact.nKind != 1) {
                            if (contact.nKind == HIT_KIND_STOP) {
                                bHit = 0;
                            }
                        } else {
                            for (i = 0; i < 4; i++) {
                                pAttr = func_0202c37c(&contact.hit, ((u8 *)contact.hit.pPart)[i + 0x80]);
                                if (pAttr != 0 && pAttr->aTags[0] == TAG_PASS_THROUGH) {
                                    bHit = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (bHit || pCharge->bArmed) {
                    func_ov022_0209bd10(pActor);
                }
                nLimit = LIMIT_B;
            }
        }
        break;
    case 0xc:
        nLimit = LIMIT_6;
        break;
    }
    if (bTick) {
        pCharge->nMeter += func_ov022_02083f90();
    }
    if (nLimit > 0 && pCharge->nKnockdownKind != PHASE_END && pCharge->nMeter >= nLimit) {
        func_ov022_0209b1e8(pActor);
    }
    return nRet;
}

#pragma pop
