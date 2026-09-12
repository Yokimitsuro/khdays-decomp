/* Ov022_StepGlideState -- one frame of the glide state; returns the state
 * change it made, or 0.
 *
 * Input bit 7 drops; the local player raises flags2 bit 7. The latch stays
 * off (bNoLatch) under button 0x800 or when held (flag bit 36). The aim is
 * taken once it is valid (bAimedJump); an aimed jump that lost its aim while
 * not held aims along the facing. With the aim gone, off flag bit 35, rule
 * 0x23 and a target reference, the flat direction to the target beyond 2.0
 * gives the aim (when it differs from the facing by more than 0xaaa), held:
 * a negative aim becomes the facing and the target's height picks a rise
 * (above, no button 2) or a dive (below, no button 0x800). A valid aim
 * raises flags2 bit 19 for the local player; under it the node banks 600
 * per frame towards the clamped turn (turns between 100 and 0x8000 either
 * way), clamped to +-7000; otherwise the bank decays 600 per frame to 0.
 * Flag bit 35 zeroes the recoil; not held the recoil is the glide sink (x1.5
 * under the global); held with flags2 bit 7 the lift grows by accel*1.5 up
 * to the jump rate while rising (button 0x800 without 2, or a rise) and
 * shrinks while diving (button 2 without 0x800, or a dive), else decays by
 * 1/8 and dies under 16; the recoil is the lift (x1.5 under the global).
 * Under flags2 bit 19 the step rate grows by the accel up to the jump rate
 * (held there off flag bit 35); a held actor with a ledge contact 0..2.0
 * above the aim point within 0xd00 takes rate 0x100 (0x180 under the global)
 * from ledge surface tags 6/7; the move is the clamped facing times the rate
 * (x1.5 under the global), the node turned, node step 0xd00, step grown by
 * the flat move, pre-draw 0xf; under flag bit 35 with input bit 2 and a wall
 * contact whose face lies within 0x2aaa of the aim, the wall contact becomes
 * the aim (bAim); else the effect fan (rule 0x22 * 0x19a deep) run through
 * the command handlers aims at the contact (send kind 1) unless contact
 * result bit 6. Off flags2 bit 19 a steer adds 7/8 of the velocity (x/z,
 * dead under 16) to the step (pre-draw 0xe), else rate and motion are
 * zeroed (pre-draw 0xe). A floor within 0x400 below the aim with no upward
 * recoil lands unless held on tags 4/6/7, unless the combo block is not
 * done and the aim is within land reach + sink of the floor: landing aims at
 * the floor contact (latch on); a refused landing raises flag bit 46. Off
 * flag bit 35 an open latch raises flags2 bit 1 (local); on it an aim sets
 * the drift to half the facing, the hold times to 30.0, drops the aimed
 * jump, raises flag bit 4 and flags2 bit 8 (local), else 30.0 of state time
 * raises flags2 bit 1 (local); an aim or a send sends the aim. Flags2 bit 1
 * ends the glide: flags2 bit 7 off, state 0x16 under input bit 2 else 2,
 * rate 0, move rate 0x1200 (pick) or 0xc00, input bit 2 off, motion scaled
 * by 0xd80 (global) or 0x900, recoil and aimed jump cleared, hold times 30.0
 * under flag bit 35. Post-draw hook; held: flag bit 2 off, the idle action
 * evaluated when nothing changed, flags3 bit 7 (local) when still nothing.
 */

typedef unsigned char u8;
typedef signed char s8;
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
    u16 nBank;                   /* 0x082 */
    u8 pad084[0xc4];
    int nStep;                   /* 0x148 */
};

/* HitInfo */
struct HitInfo {
    u8 pad00[0x14];
    short nX;                    /* 0x14 */
    short nY;                    /* 0x16 */
    short nZ;                    /* 0x18 */
    u8 pad1a[0x66];
    u8 aSurfaceSlots[4];         /* 0x80 */
};

/* CollSurfaceAttr */
struct CollSurfaceAttr {
    u8 pad00[0xc];
    u8 aTags[4];                 /* 0x0c */
    u8 pad10[4];
};

/* Ov022CollBlock */
struct CollBlock {
    int nHandle;                 /* 0x00 */
    struct HitInfo *pContacts;   /* 0x04 */
    void *pRide;                 /* 0x08 */
    u8 pad0c[0x8c];
    VecFx32 vecContact;          /* 0x98 */
    int nContactMode;            /* 0xa4 */
};

/* Ov022EffectRequest */
struct EffectRequest {
    u8 pad00[0x28];
};

/* Ov022EffectPlace */
struct EffectPlace {
    VecFx32 vecAt;               /* 0x00 */
    u8 pad0c[0x20];
};

/* Ov022SweepContact */
struct SweepContact {
    u32 nResult;                 /* 0x00 */
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[3];
    VecFx32 vec;                 /* 0x0c */
    u8 pad18[0x9c];
};

/* the glide tuning fields at actor+0x1c78; Ghidra keeps them flat in Ov022Actor
 * (nGlideAccel, nJumpRate, nGlideSink, nGlideLandReach) -- the ROM reaches them
 * through one base register */
struct Glide {
    short nGlideAccel;           /* 0x00 (0x1c78) */
    short nJumpRate;             /* 0x02 (0x1c7a) */
    short nGlideSink;            /* 0x04 (0x1c7c) */
    u8 pad06[6];
    int nGlideLandReach;         /* 0x0c (0x1c84) */
};

struct Actor;

typedef void (*ActorHookFn)(struct Actor *pActor, int nArg);   /* Ov022ActorHookFn */
typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x10];
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[4];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    VecFx32 vecVel;              /* 0x0028 */
    u8 pad0034[0x24];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0xc];
    struct CollBlock collMain;   /* 0x0068 */
    struct CollBlock collLedge;  /* 0x0110 */
    struct CollBlock collWallA;  /* 0x01b8 */
    struct CollBlock collWallB;  /* 0x0260 */
    u8 pad0308[0x15c];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[4];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[2];
    VecFx32 vecDrift;            /* 0x047c */
    u32 nFacingAngle;            /* 0x0488 */
    VecFx32 vecAim;              /* 0x048c */
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0xc];
    int nMoveRate;               /* 0x04b0 */
    u8 pad04b4[9];
    s8 bAimedJump;               /* 0x04bd */
    u8 pad04be[0xe];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x194];
    ActorHookFn pfnPreDraw;      /* 0x0664 */
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* 0x0694 bit 1 */
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;
    u8 bSequenceRunning : 1;
    u8 bVoicePlayed : 1;
    u8 bTriggerHeld : 1;
    u8 nSpare6947 : 1;
    u8 pad0695[3];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0x10];
    int nStepRate;               /* 0x06b4 */
    int nRecoilDecay;            /* 0x06b8 */
    u8 pad06bc[0xc5c];
    u8 comboBlk;                 /* 0x1318 */
    u8 pad1319[0x957];
    int nHoldTime;               /* 0x1c70 */
    u8 pad1c74[4];
    struct Glide glide;          /* 0x1c78 */
    u8 pad1c88[0x110];
    int nGlideHoldTime;          /* 0x1d98 */
    u8 pad1d9c[0x920];
    struct SweepContact contact; /* 0x26bc */
    u8 pad2770[0x34c];
    int nAimAngle;               /* 0x2abc */
};

#define FLAG_BIT2 (1ULL << 2)
#define FLAG_BIT4 (1ULL << 4)
#define FLAG_BIT35 (1ULL << 35)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG2_BIT1 (1ULL << 1)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT8 (1ULL << 8)
#define FLAG2_BIT19 (1ULL << 19)
#define FLAG3_BIT7 (1ULL << 7)
#define INPUT_BIT1 0x2
#define INPUT_BIT2 0x4
#define INPUT_BIT7 0x80
#define BUTTON2_DIVE 0x2
#define BUTTON2_RISE 0x800
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define NO_AIM -1
#define RULE_AIM_TARGET 0x23
#define RULE_FAN_DEPTH 0x22
#define TARGET_MIN_DIST 0x2000
#define AIM_RETURN_MIN 0xaaa
#define TURN_MIN 100
#define TURN_MAX (0x10000 - 100)
#define BANK_STEP 600
#define BANK_MAX 7000
#define BANK_MIN (0x10000 - 7000)
#define LIFT_ACCEL 0x1800
#define LIFT_DECAY 0x800
#define LIFT_DEAD 0x10
#define LEDGE_ABOVE 0x2000
#define LEDGE_REACH 0xd00
#define LEDGE_RATE_FAST 0x180
#define LEDGE_RATE_SLOW 0x100
#define TAG_LEDGE_A 6
#define TAG_LEDGE_B 7
#define TAG_NO_LAND 4
#define NODE_STEP_MOVE 0xd00
#define PREDRAW_GLIDE 0xf
#define PREDRAW_HELD 0xe
#define WALL_FACE_SPAN 0x2aaa
#define FAN_DEPTH_UNIT 0x19a
#define CONTACT_NO_AIM 0x40
#define STEER_KEEP 0xe00
#define STEER_DEAD 0x10
#define LAND_GAP 0x400
#define HOLD_TIME 0x1e000
#define AIM_HEIGHT 0x800
#define DRIFT_SCALE 0x800
#define STATE_END 2
#define STATE_LAND_END 0x16
#define MOVE_RATE_FAST 0x1200
#define MOVE_RATE_SLOW 0xc00
#define END_SCALE_FAST 0xd80
#define END_SCALE_SLOW 0x900
#define SEND_CONTACT 1

extern const short data_0203d210[];         /* kFxSinCosTable: sin, cos pairs */
extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_020ad1b4(struct Actor *pActor);                           /* Ov022_GetField4f4UnlessState5 */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);                      /* Ov022_GetTargetPos */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pIn, VecFx32 *pOut);                         /* VEC_Normalize */
extern int FX_Atan2(int y, int x);
extern u32 func_ov022_020ad4e8(struct Actor *pActor, u32 nAngle);               /* Ov022_ClampAngleTowardTarget */
extern int func_02023c40(void);                                                 /* LoadGlobalU8_0204c058 */
extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);                             /* VEC_Distance */
extern struct CollSurfaceAttr *func_0202c37c(struct CollBlock *pBlock, int nTag);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_02028d74(int nHandle, short *pPacked, VecFx32 *pOut);          /* VecFx32FromVecS16 */
extern void func_ov022_020ad62c(struct Actor *pActor, VecFx32 *pAt, struct EffectPlace *pPlace,
                                struct EffectRequest *pRequest);                /* Ov022_FillEffectBlocks */
extern int func_ov022_020a0fb8(struct Actor *pActor, struct EffectPlace *pPlace,
                               struct EffectRequest *pRequest);                 /* Ov022_RunCommandHandlers */
extern int func_ov022_0209344c(u8 *pBlk);                                       /* Ov022_IsBlockDone */
extern void func_01ffa724(int nScale, VecFx32 *pIn, VecFx32 *pOut);             /* ScaleVec3Fx12 */
extern void func_ov022_0209cf58(struct Actor *pActor, VecFx32 *pFrom, VecFx32 *pTo, int nHeight,
                                int bCheck);                                    /* Ov022_SendAimAtTarget */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);               /* Ov022_ActorSetState */
extern int func_ov022_020a6f9c(struct Actor *pActor);                           /* Ov022_EvaluateActionOrForward */

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

static inline int FxMulL(int nValue, s64 nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}int func_ov022_020a98b4(struct Actor *pActor)
{
    VecFx32 vecDir;
    VecFx32 vecWall;
    VecFx32 vecAimAt;
    VecFx32 vecAimFrom;
    VecFx32 vecDelta;
    struct EffectPlace place;
    struct EffectRequest request;
    VecFx32 vecFan;
    VecFx32 vecSteer;
    VecFx32 vecFlat;
    VecFx32 vecSteerFlat;
    int nRet;
    int bTurned;
    int bNoLatch;
    int nSendKind;
    int bRise;
    int bDive;
    VecFx32 *pAim;
    int bAim;
    struct Glide *pGlide;
    int nAim;
    int nBank;
    int bSteer;
    int nFacing;
    int bLand;
    u32 nAngle;
    int nTarget;
    int nFace;
    int nAway;
    int nTurn;
    u16 nWallAngle;
    int nDiff;
    struct ActorNode *pNode;
    int nDelta;
    int nLift;
    int nRate;
    int nTrig;
    int nSink;
    int nFloor;
    int nDist;
    int i;
    struct CollSurfaceAttr *pAttr;
    u16 nButtons2;

    nRet = 0;
    bTurned = 0;
    bNoLatch = 0;
    bAim = 0;
    nSendKind = 0;
    bSteer = 0;
    bRise = 0;
    bDive = 0;
    pAim = &pActor->vecAim;
    pGlide = &pActor->glide;
    pActor->nInputMask &= ~INPUT_BIT7;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT7;
    }
    if ((pActor->nButtons2 & BUTTON2_RISE) != 0 || (pActor->nFlags & FLAG_BIT36) != 0) {
        bNoLatch = 1;
    }
    nFacing = pActor->nFacingAngle;
    nBank = pActor->pNode->nBank;
    nAim = pActor->nAimAngle;
    if (pActor->bAimedJump != 0) {
        if (nAim < 0 && (pActor->nFlags & FLAG_BIT36) == 0) {
            nAim = (u16)(nFacing - pActor->nAngleBias);
        }
    } else if (nAim >= 0) {
        pActor->bAimedJump = 1;
    }
    if (pActor->bAimedJump != 0 && pActor->nAimAngle == NO_AIM && (pActor->nFlags & FLAG_BIT35) == 0
        && func_020358f4(pActor->nId, RULE_AIM_TARGET) != 0 && func_ov022_020ad1b4(pActor) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(pActor), pAim, &vecDelta);
        vecDir = vecDelta;
        vecDir.y = 0;
        if (VEC_Mag(&vecDir) > TARGET_MIN_DIST) {
            if (VEC_Mag(&vecDir) != 0) {
                func_01ff8d18(&vecDir, &vecDir);
            }
            nTarget = FX_Atan2(-vecDir.x, -vecDir.z);
            nFace = (u16)(pActor->pNode->nAngle - ANGLE_BIAS);
            nAway = (u16)(nTarget - nFace);
            if (nAway > AIM_RETURN_MIN) {
                nAim = (u16)(nTarget - pActor->nAngleBias);
            }
            if ((pActor->nFlags & FLAG_BIT36) != 0) {
                if (nAim < 0) {
                    nAim = (u16)(nFace + ANGLE_BIAS);
                }
                if (vecDelta.y > 0 && (pActor->nButtons2 & BUTTON2_DIVE) == 0) {
                    bRise = 1;
                } else if (vecDelta.y < 0 && (pActor->nButtons2 & BUTTON2_RISE) == 0) {
                    bDive = 1;
                }
            }
        }
    }
    if (nAim >= 0 && func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT19;
    }
    if ((pActor->nFlags2 & FLAG2_BIT19) != 0) {
        nAngle = (u16)(nAim + pActor->nAngleBias);
        nAngle = func_ov022_020ad4e8(pActor, nAngle);
        nTurn = (u16)(nAngle - nFacing);
        if ((nTurn > TURN_MIN && nTurn < 0x8000) || (nTurn > 0x8000 && nTurn < TURN_MAX)) {
            if (nTurn > TURN_MIN && nTurn < 0x8000) {
                nDelta = -BANK_STEP;
            } else {
                nDelta = BANK_STEP;
            }
            nBank = (u16)(nBank + nDelta);
            if (nBank >= BANK_MAX && nBank <= 0x8000) {
                nBank = BANK_MAX;
            } else if (nBank <= BANK_MIN && nBank > 0x8000) {
                nBank = BANK_MIN;
            }
            bTurned = 1;
        }
    }
    if (!bTurned && nBank != 0) {
        nBank = (u16)(nBank + (nBank > 0x8000 ? BANK_STEP : -BANK_STEP));
        if (nBank <= BANK_STEP) {
            nBank = 0;
        }
    }
    pNode = pActor->pNode;
    pNode->nBank = nBank;
    pNode->nAnimFlags |= ANIM_HOLD;
    if ((pActor->nFlags & FLAG_BIT35) != 0) {
        pActor->nRecoil = 0;
    } else if ((pActor->nFlags & FLAG_BIT36) != 0) {
        if ((pActor->nFlags2 & FLAG2_BIT7) != 0) {
            nButtons2 = pActor->nButtons2;
            if (((nButtons2 & BUTTON2_RISE) != 0 && (nButtons2 & BUTTON2_DIVE) == 0) || bRise) {
                nLift = pActor->nRecoilDecay;
                if (nLift < 0) {
                    pActor->nRecoilDecay = 0;
                } else if (pGlide->nJumpRate > nLift) {
                    pActor->nRecoilDecay = nLift + FxMul(pGlide->nGlideAccel, LIFT_ACCEL);
                }
                bSteer = 1;
            } else if (((nButtons2 & BUTTON2_RISE) == 0 && (nButtons2 & BUTTON2_DIVE) != 0) || bDive) {
                nLift = pActor->nRecoilDecay;
                if (nLift > 0) {
                    pActor->nRecoilDecay = 0;
                } else if (-pGlide->nJumpRate < nLift) {
                    pActor->nRecoilDecay = nLift - FxMul(pGlide->nGlideAccel, LIFT_ACCEL);
                }
                bSteer = 1;
            }
        }
        if (!bSteer) {
            nLift = pActor->nRecoilDecay;
            nLift -= FxMul(nLift, LIFT_DECAY);
            pActor->nRecoilDecay = nLift;
            if (nLift < 0) {
                nLift = -nLift;
            }
            if (nLift < LIFT_DEAD) {
                pActor->nRecoilDecay = 0;
            }
        }
        pActor->nRecoil = func_02023c40() == 1 ? pActor->nRecoilDecay * 3 / 2 : pActor->nRecoilDecay;
    } else {
        pActor->nRecoil = func_02023c40() == 1 ? (-pGlide->nGlideSink * 3) / 2 : -pGlide->nGlideSink;
    }
    if ((pActor->nFlags2 & FLAG2_BIT19) != 0) {
        nAngle = func_ov022_020ad4e8(pActor, (u16)(nAim + pActor->nAngleBias));
        if (pActor->nStepRate < pGlide->nJumpRate) {
            pActor->nStepRate += pGlide->nGlideAccel;
        } else if ((pActor->nFlags & FLAG_BIT35) == 0) {
            pActor->nStepRate = pGlide->nJumpRate;
        }
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0
            && pActor->collLedge.nContactMode != 0 && pActor->collLedge.pContacts != 0) {
            if (pAim->y < pActor->collLedge.vecContact.y
                && pAim->y + LEDGE_ABOVE > pActor->collLedge.vecContact.y
                && func_01ff8e94(pAim, &pActor->collLedge.vecContact) <= LEDGE_REACH) {
                for (i = 1; i < 3; i++) {
                    pAttr = func_0202c37c(&pActor->collLedge, pActor->collLedge.pContacts->aSurfaceSlots[i]);
                    if (pAttr != 0) {
                        if (func_02023c40() == 1) {
                            nRate = LEDGE_RATE_FAST;
                        } else {
                            nRate = LEDGE_RATE_SLOW;
                        }
                        if (!(pAttr->aTags[0] != TAG_LEDGE_A && pAttr->aTags[0] != TAG_LEDGE_B)) {
                            pActor->nStepRate = nRate;
                        }
                    }
                }
            }
        }
        nRate = func_02023c40() == 1 ? pActor->nStepRate * 3 / 2 : pActor->nStepRate;
        nTrig = ((int)nAngle >> 4) * 2;
        vecDir.x = -data_0203d210[nTrig];
        vecDir.z = -data_0203d210[nTrig + 1];
        vecDir.y = 0;
        pNode = pActor->pNode;
        if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
            pNode->nAngle = nAngle + ANGLE_BIAS;
            pNode->nAnimFlags |= ANIM_HOLD;
        }
        vecDir.x = FxMul(vecDir.x, nRate);
        vecDir.z = FxMul(vecDir.z, nRate);
        vecDir.y = 0;
        pActor->vecMotion = vecDir;
        pActor->pNode->nStep = NODE_STEP_MOVE;
        vecFlat = vecDir;
        vecFlat.y = 0;
        VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
        pActor->pfnPreDraw(pActor, PREDRAW_GLIDE);
        if ((pActor->nFlags & FLAG_BIT35) != 0) {
            if ((pActor->nInputMask & INPUT_BIT1) != 0 && pActor->collWallA.pContacts != 0) {
                func_02028d74(pActor->collWallA.nHandle, &pActor->collWallA.pContacts->nX, &vecWall);
                nWallAngle = FX_Atan2(vecWall.x, vecWall.z);
                nDiff = (u16)(nWallAngle - nAngle);
                if (nDiff < WALL_FACE_SPAN || nDiff > 0x10000 - WALL_FACE_SPAN) {
                    vecAimAt = pActor->collWallA.vecContact;
                    vecAimFrom = pActor->vecAim;
                    bAim = 1;
                }
            }
            if (!bAim) {
                vecFan.z = func_020358f4(pActor->nId, RULE_FAN_DEPTH) * FAN_DEPTH_UNIT;
                vecFan.y = 0;
                vecFan.x = 0;
                func_ov022_020ad62c(pActor, &vecFan, &place, &request);
                if (func_ov022_020a0fb8(pActor, &place, &request) != 0 && (pActor->contact.nResult & CONTACT_NO_AIM) == 0) {
                    vecAimAt = pActor->contact.vec;
                    vecAimFrom = place.vecAt;
                    nSendKind = SEND_CONTACT;
                }
            }
        }
    } else {
        if (bSteer) {
            vecSteer = pActor->vecVel;
            vecSteer.y = 0;
            vecSteer.z = FxMulL(vecSteer.z, STEER_KEEP);
            vecSteer.x = FxMulL(vecSteer.x, STEER_KEEP);
            if ((vecSteer.x < 0 ? -vecSteer.x : vecSteer.x) < STEER_DEAD) {
                vecSteer.x = 0;
            }
            if ((vecSteer.z < 0 ? -vecSteer.z : vecSteer.z) < STEER_DEAD) {
                vecSteer.z = 0;
            }
            vecSteerFlat = vecSteer;
            vecSteerFlat.y = 0;
            VEC_Add(&pActor->vecStep, &vecSteerFlat, &pActor->vecStep);
            pActor->pfnPreDraw(pActor, PREDRAW_HELD);
        } else {
            pActor->nStepRate = 0;
            pActor->vecMotion.z = 0;
            pActor->vecMotion.y = 0;
            pActor->vecMotion.x = 0;
            pActor->pfnPreDraw(pActor, PREDRAW_HELD);
        }
    }
    if (pActor->collMain.nContactMode != 0 && pActor->collMain.pContacts != 0) {
        if (pAim->y - pActor->collMain.vecContact.y <= LAND_GAP && pActor->nRecoil <= 0) {
            bLand = 1;
            if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
                for (i = 1; i < 3; i++) {
                    pAttr = func_0202c37c(&pActor->collMain, pActor->collMain.pContacts->aSurfaceSlots[i]);
                    if (pAttr != 0 && !(pAttr->aTags[0] != TAG_NO_LAND && pAttr->aTags[0] != TAG_LEDGE_A && pAttr->aTags[0] != TAG_LEDGE_B)) {
                        bLand = 0;
                    }
                }
            }
            if (bLand) {
                nFloor = pActor->collMain.vecContact.y + LAND_GAP;
                if (func_ov022_0209344c(&pActor->comboBlk) == 0) {
                    nSink = func_02023c40() == 1 ? pGlide->nGlideSink * 3 / 2 : pGlide->nGlideSink;
                    nDist = nFloor - pActor->vecAim.y;
                    nDist = nDist < 0 ? -nDist : nDist;
                    if (nDist < pGlide->nGlideLandReach + nSink) {
                        bLand = 0;
                    }
                }
                if (bLand) {
                    vecAimFrom = pActor->vecAim;
                    vecAimAt = pActor->collMain.vecContact;
                    bNoLatch = 0;
                    bAim = 1;
                } else {
                    pActor->nFlags |= FLAG_BIT46;
                }
            } else {
                pActor->nFlags |= FLAG_BIT46;
            }
        }
    }
    if ((pActor->nFlags & FLAG_BIT35) == 0) {
        if (!bNoLatch && func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT1;
        }
    } else {
        if (bAim) {
            nTrig = ((u16)((u16)(pActor->pNode->nAngle - ANGLE_BIAS) + ANGLE_BIAS) >> 4) * 2;
            pActor->vecDrift.x = -data_0203d210[nTrig];
            pActor->vecDrift.z = -data_0203d210[nTrig + 1];
            pActor->vecDrift.y = 0;
            func_01ffa724(DRIFT_SCALE, &pActor->vecDrift, &pActor->vecDrift);
            pActor->nHoldTime = HOLD_TIME;
            pActor->nGlideHoldTime = HOLD_TIME;
            pActor->bAimedJump = 0;
            pActor->nFlags |= FLAG_BIT4;
            if (func_02030788() == 0) {
                pActor->nFlags2 |= FLAG2_BIT8;
            }
        } else if ((int)pActor->nStateTimer >= HOLD_TIME && func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT1;
        }
        if (bAim || nSendKind != 0) {
            func_ov022_0209cf58(pActor, &vecAimAt, &vecAimFrom, AIM_HEIGHT, nSendKind);
        }
    }
    if ((pActor->nFlags2 & FLAG2_BIT1) != 0) {
        pActor->nFlags2 &= ~FLAG2_BIT7;
        if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            nRet = func_ov022_020a35f4(pActor, STATE_LAND_END);
        } else {
            nRet = func_ov022_020a35f4(pActor, STATE_END);
        }
        pActor->nStepRate = 0;
        pActor->nMoveRate = data_ov022_020b2eb0 ? MOVE_RATE_FAST : MOVE_RATE_SLOW;
        pActor->nInputMask &= ~INPUT_BIT2;
        func_01ffa724(func_02023c40() == 1 ? END_SCALE_FAST : END_SCALE_SLOW, &pActor->vecMotion, &pActor->vecMotion);
        pActor->nRecoil = 0;
        pActor->bAimedJump = 0;
        if ((pActor->nFlags & FLAG_BIT35) != 0) {
            pActor->nHoldTime = HOLD_TIME;
            pActor->nGlideHoldTime = HOLD_TIME;
        }
    }
    pActor->bStateOver = (u8)pActor->pfnPostDraw(pActor);
    if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
        pActor->nFlags &= ~FLAG_BIT2;
        if (nRet == 0) {
            nRet = func_ov022_020a6f9c(pActor);
        }
        if (nRet == 0 && func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT7;
        }
    }
    return nRet;
}
