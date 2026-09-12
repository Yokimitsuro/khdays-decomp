/* Ov022_StepJumpState -- one frame of the jump state (aim modes 0..3);
 * returns the state change it made, or 0.
 *
 * The move rate is 1.5 under the recoil pick, else 1.0; the local player
 * raises flags2 bit 6. Aimed while rising or falling without flag bit 1, or
 * under input bit 8, the move is the facing (the aim clamped towards the
 * target and the node turned, or the node's own facing without an aim)
 * times the air step rate -- a unit step while the aim is still turning;
 * otherwise 4/5 of the motion. The flat move becomes the motion, the node
 * step 0xd00, the step grows by it, and the post-draw hook says whether the
 * state is over. Mode 0 (ground): with rule 0x2d the vertical motion grows
 * by rule/8 when the state is over and the air step rate is set (0.34, 0.22
 * without the pick); the launch goes to mode 1 with the recoil set to the
 * vertical motion and the pre-draw hook run with 3. Mode 1 (rising): the
 * recoil is clamped up to 0 past frame 0xd000 while held (button 2 or
 * anchor phase 3, no input bit 3), else halved from frame 0x4000; a negative
 * recoil turns the air timer back and enters mode 2. Mode 2 (falling): the
 * air timer runs, the recoil floors at -0.26, a finished anim-3 step
 * dispatches 0x10000, a climb target enters state 9, a held actor (flag bit
 * 36 with flags2 bit 7) drops flag bit 2 and with a floor raises bit 46 and
 * enters state 6 (pre-draw 0xe); input bit 2 enters state 0x16; else the
 * idle input dispatch may change state; past 15.0 of air time flag bit 2
 * drops. Mode 3 (landed): input bit 6 is raised, flag bit 43 clears the land
 * timer and holds; without input bit 2 the recoil is -0.26 and, on a floor
 * whose surface slots 1..2 carry no tag 6, the land timer runs and enters
 * state 2 at 3.0 (a tag 6 holds instead); button 2 resets the timers;
 * unheld with button 0x800, the follow bit and an aim: flags2 bit 30 for the
 * local player and state 8; held past anim frame 0x6000 dispatches 0x6000;
 * the state over raises flag bit 49, enables the node and flags2 bit 1 for
 * the local player; flags2 bit 1 unheld runs the pre-draw hook with 0 and
 * enters state 0; else past frame 0x6000 unheld the idle step runs and, with
 * an aim, the pre-draw hook with 1 and state 0.
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
    u8 pad082[0xc6];
    int nStep;                   /* 0x148 */
};

/* HitInfo */
struct HitInfo {
    u8 pad00[0x80];
    u8 aSurfaceSlots[4];         /* 0x80 */
};

/* Hit: the collision record kept for the floor */
struct Hit {
    void *pModel;                /* 0x00 */
    struct HitInfo *pInfo;       /* 0x04 */
    void *pState;                /* 0x08 */
    int nNearestHit;             /* 0x0c */
};

/* CollSurfaceAttr */
struct CollSurfaceAttr {
    u8 pad00[0xc];
    u8 aTags[4];                 /* 0x0c */
    u8 pad10[4];
};

/* Ov022AimState: the jump/aim phase block at actor+0x2bb0 */
struct AimState {
    u8 nJumpCount;               /* 0x00 */
    u8 bHold;                    /* 0x01 */
    s8 nAimMode;                 /* 0x02 launch 0, rising 1, falling 2, landed 3 */
    u8 pad03;
    int nAirTimer;               /* 0x04 */
    int nAirStepRate;            /* 0x08 */
    u8 pad0c[4];
    int nLandTimer;              /* 0x10 */
};

struct Actor;

typedef void (*ActorHookFn)(struct Actor *pActor, int nArg);   /* Ov022ActorHookFn */
typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0xe];
    u16 nButtons;                /* 0x0018 */
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[4];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0xc];
    struct Hit floorHit;         /* 0x0068 */
    u8 pad0078[0x94];
    int nHasFloor;               /* 0x010c */
    u8 pad0110[0x354];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0xc];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[0x1e];
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0xc];
    int nMoveRate;               /* 0x04b0 */
    u8 pad04b4[0x1b0];
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
    u8 pad06b8[4];
    int nAnimId;                 /* 0x06bc */
    u8 pad06c0[0xf0];
    int nAnimFrame;              /* 0x07b0 */
    u8 nAnchorPhase;             /* 0x07b4 */
    u8 pad07b5[0x9d7];
    u8 blkFollow;                /* 0x118c */
    u8 pad118d[0x192d];
    short nAreaFrame;            /* 0x2aba */
    int nAimAngle;               /* 0x2abc */
    u8 pad2ac0[0xf0];
    struct AimState aim;         /* 0x2bb0 */
};

#define FLAG_BIT1 (1ULL << 1)
#define FLAG_BIT2 (1ULL << 2)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT43 (1ULL << 43)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define FLAG2_BIT6 (1ULL << 6)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT30 (1ULL << 30)
#define INPUT_BIT2 0x4
#define INPUT_BIT3 0x8
#define INPUT_BIT6 0x40
#define INPUT_BIT8 0x100
#define BUTTON_2 0x2
#define BUTTON_JUMP 0x800
#define BUTTON2_HOLD 0x2
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define NODE_STEP_MOVE 0xd00
#define NO_AIM -1
#define RATE_FAST 0x1800
#define RATE_SLOW 0x1000
#define MOTION_KEEP 0xccd
#define RULE_RISE 0x2d
#define AIR_STEP_FAST 0x566
#define AIR_STEP_SLOW 0x39a
#define PREDRAW_LAUNCH 3
#define PREDRAW_HELD 0xe
#define ANCHOR_PHASE_HOLD 3
#define FRAME_HOLD 0xd000
#define FRAME_HALVE 0x4000
#define FRAME_LAND 0x6000
#define RECOIL_FLOOR -0x420
#define ANIM_STEP 3
#define AIR_TIME_FREE 0xf000
#define LAND_TIME 0x3000
#define TAG_NO_LAND 6
#define STATE_IDLE 0
#define STATE_END 2
#define STATE_HELD 6
#define STATE_DODGE 8
#define STATE_CLIMB 9
#define STATE_LAND_END 0x16

extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick */
extern short data_0203d210[];               /* kFxSinCosTable: sin, cos pairs */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_ov022_020ad4e8(struct Actor *pActor, u32 nAngle);               /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int nScale, VecFx32 *pIn, VecFx32 *pOut);             /* ScaleVec3Fx12 */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern void func_ov022_02097038(struct Actor *pActor, int nArg);                /* SetField7b0AndDispatch */
extern int func_ov022_02095e48(struct Actor *pActor);                           /* Ov022_FindClimbTarget */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);               /* Ov022_ActorSetState */
extern int func_ov022_020a6d0c(struct Actor *pActor);                           /* Ov022_DispatchIdleInput */
extern struct CollSurfaceAttr *func_0202c37c(struct Hit *pHit, int nTag);
extern int func_ov022_02097d50(struct Actor *pActor, int bSignal);              /* Ov022_ResetTimersAndMaybeSignal */
extern int func_ov022_020928c0(u8 *pFlags);                                     /* Ov022_IsBit0Set */
extern int func_0202aee0(u16 *pAnimFlags, int nArg);                            /* Anim_GetFrame */
extern void func_0202af1c(u16 *pAnimFlags);                                     /* SceneNode_Enable */
extern int func_ov022_020981f4(struct Actor *pActor);                           /* Ov022_StepIdleActor */

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

int func_ov022_020a64e0(struct Actor *pActor)
{
    VecFx32 vecMove;
    VecFx32 vecFlat;
    struct ActorNode *pNode;
    int nRet;
    int nState;
    int bAim;
    int nAim;
    u32 nTarget;
    u32 nAngle;
    int nTrig;
    int nRule;
    int bLaunch;
    int i;
    int bHold;
    int bOnFloor;
    struct Hit *pGround;
    struct CollSurfaceAttr *pAttr;
    struct AimState *pAim;

    pAim = &pActor->aim;
    nRet = 0;
    bAim = 0;
    pActor->nMoveRate = data_ov022_020b2eb0 ? RATE_FAST : RATE_SLOW;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT6;
    }
    vecMove.z = 0;
    vecMove.y = 0;
    vecMove.x = 0;
    nAim = pActor->nAimAngle;
    if (nAim != NO_AIM && (pAim->nAimMode == 1 || pAim->nAimMode == 2) && (pActor->nFlags & FLAG_BIT1) == 0) {
        bAim = 1;
    }
    if ((pActor->nInputMask & INPUT_BIT8) != 0) {
        bAim = 1;
    }
    if (bAim) {
        if (nAim != NO_AIM) {
            nTarget = (u16)(nAim + pActor->nAngleBias);
            nAngle = func_ov022_020ad4e8(pActor, nTarget);
            nTrig = ((int)nAngle >> 4) * 2;
            vecMove.x = -data_0203d210[nTrig];
            vecMove.z = -data_0203d210[nTrig + 1];
            vecMove.y = 0;
            pNode = pActor->pNode;
            if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                pNode->nAngle = nAngle + ANGLE_BIAS;
                pNode->nAnimFlags |= ANIM_HOLD;
            }
        } else {
            nAngle = (u16)(pActor->pNode->nAngle - ANGLE_BIAS);
            nTrig = ((int)nAngle >> 4) * 2;
            vecMove.x = -data_0203d210[nTrig];
            vecMove.z = -data_0203d210[nTrig + 1];
            vecMove.y = 0;
            nTarget = nAngle;
        }
        pActor->nStepRate = pAim->nAirStepRate;
        if (nAngle == nTarget) {
            func_01ffa724(pActor->nStepRate, &vecMove, &vecMove);
        } else {
            func_01ffa724(1, &vecMove, &vecMove);
        }
    } else {
        vecMove = pActor->vecMotion;
        func_01ffa724(MOTION_KEEP, &vecMove, &vecMove);
    }
    pActor->vecMotion.x = vecMove.x;
    pActor->vecMotion.z = vecMove.z;
    pActor->pNode->nStep = NODE_STEP_MOVE;
    vecFlat = pActor->vecMotion;
    vecFlat.y = 0;
    VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
    pActor->bStateOver = (u8)pActor->pfnPostDraw(pActor);
    switch (pAim->nAimMode) {
    case 0:
        nRule = func_020358f4(pActor->nId, RULE_RISE);
        bLaunch = 0;
        if (nRule > 0) {
            if (pActor->bStateOver) {
                pActor->vecMotion.y += FxMul(pActor->vecMotion.y, nRule << 9);
                pActor->aim.nAirStepRate = data_ov022_020b2eb0 ? AIR_STEP_FAST : AIR_STEP_SLOW;
                bLaunch = 1;
            }
        } else if (pActor->bStateOver) {
            bLaunch = 1;
        }
        if (bLaunch) {
            pAim->nAimMode = 1;
            pActor->nRecoil = pActor->vecMotion.y;
            pActor->pfnPreDraw(pActor, PREDRAW_LAUNCH);
        }
        break;
    case 1:
        if (((pActor->nButtons2 & BUTTON2_HOLD) != 0 || pActor->nAnchorPhase == ANCHOR_PHASE_HOLD) && (pActor->nInputMask & INPUT_BIT3) == 0) {
            if (pActor->nAnimFrame <= FRAME_HOLD && pActor->nRecoil < 0) {
                pActor->nRecoil = 0;
            }
        } else {
            if (pActor->nAnimFrame >= FRAME_HALVE && pActor->nRecoil > 0) {
                pActor->nRecoil >>= 1;
            }
        }
        if (pActor->nRecoil < 0) {
            pAim->nAirTimer -= pActor->nAreaFrame;
            pAim->nAimMode = 2;
        }
    case 2:
        if (pAim->nAimMode == 2) {
            pAim->nAirTimer += pActor->nAreaFrame;
        }
        if (pActor->nRecoil < RECOIL_FLOOR) {
            pActor->nRecoil = RECOIL_FLOOR;
        }
        if (pActor->bStateOver && pActor->nAnimId == ANIM_STEP) {
            func_ov022_02097038(pActor, 0x10000);
        }
        if (func_ov022_02095e48(pActor) != 0) {
            nRet = func_ov022_020a35f4(pActor, STATE_CLIMB);
            if (nRet != 0) {
                goto done;
            }
        }
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
            pActor->nFlags &= ~FLAG_BIT2;
            if (pActor->nHasFloor != 0) {
                pActor->nFlags |= FLAG_BIT46;
                pActor->pfnPreDraw(pActor, PREDRAW_HELD);
                nRet = func_ov022_020a35f4(pActor, STATE_HELD);
                if (nRet == 0) {
                    /* refused: skip the input check, go on to the idle dispatch */
                } else {
                    goto done;
                }
            }
        } else if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            nRet = func_ov022_020a35f4(pActor, STATE_LAND_END);
            if (nRet != 0) {
                goto done;
            }
        }
        if (nRet == 0) {
            nState = func_ov022_020a6d0c(pActor);
            if (nState != 0) {
                nRet = nState;
                goto done;
            }
        }
        if (pAim->nAirTimer >= AIR_TIME_FREE) {
            pActor->nFlags &= ~FLAG_BIT2;
        }
        break;
    case 3:
        pActor->nInputMask |= INPUT_BIT6;
        bHold = 0;
        if ((pActor->nFlags & FLAG_BIT43) != 0) {
            pAim->nLandTimer = 0;
            bHold = 1;
        }
        if ((pActor->nInputMask & INPUT_BIT2) == 0) {
            bOnFloor = 0;
            pActor->nRecoil = RECOIL_FLOOR;
            pGround = 0;
            if (pActor->nHasFloor != 0) {
                pGround = &pActor->floorHit;
                bOnFloor = 1;
            }
            if (bOnFloor && pGround != 0 && pGround->pInfo != 0) {
                for (i = 1; i < 3; i++) {
                    pAttr = func_0202c37c(pGround, pGround->pInfo->aSurfaceSlots[i]);
                    if (pAttr != 0 && pAttr->aTags[0] == TAG_NO_LAND) {
                        bOnFloor = 0;
                        bHold = 1;
                        break;
                    }
                }
            }
            if (bOnFloor) {
                pAim->nLandTimer += pActor->nAreaFrame;
                if (pAim->nLandTimer >= LAND_TIME) {
                    nRet = func_ov022_020a35f4(pActor, STATE_END);
                    if (nRet != 0) {
                        goto done;
                    }
                }
            }
        }
        if ((pActor->nButtons & BUTTON_2) == BUTTON_2) {
            nRet = func_ov022_02097d50(pActor, 0);
            if (nRet != 0) {
                goto done;
            }
        }
        if (bHold == 0 && (pActor->nButtons & BUTTON_JUMP) == BUTTON_JUMP && func_ov022_020928c0(&pActor->blkFollow) && pActor->nAimAngle != NO_AIM) {
            if (func_02030788() == 0) {
                pActor->nFlags2 |= FLAG2_BIT30;
            }
            nRet = func_ov022_020a35f4(pActor, STATE_DODGE);
            if (nRet != 0) {
                goto done;
            }
        }
        if (bHold && func_0202aee0(&pActor->pNode->nAnimFlags, 0) >= FRAME_LAND) {
            func_ov022_02097038(pActor, FRAME_LAND);
        }
        if (pActor->bStateOver) {
            pActor->nFlags |= FLAG_BIT49;
            if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
                func_0202af1c(&pActor->pNode->nAnimFlags);
            }
            if (func_02030788() == 0) {
                pActor->nFlags2 |= FLAG2_BIT1;
            }
        }
        if ((pActor->nFlags2 & FLAG2_BIT1) != 0 && bHold == 0) {
            pActor->pfnPreDraw(pActor, 0);
            nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
        } else if (pActor->nAnimFrame >= FRAME_LAND && bHold == 0) {
            nRet = func_ov022_020981f4(pActor);
            if (nRet != 0) {
                goto done;
            }
            if (pActor->nAimAngle != NO_AIM) {
                pActor->pfnPreDraw(pActor, 1);
                nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
            }
        }
        break;
    }
done:
    return nRet;
}
