/* Ov022_StepComboState -- one frame of the combo (attack) state; returns
 * the state change it made, or 0.
 *
 * The local player raises flags2 bit 4 and flags3 bit 4, drops input bit 7,
 * raises flags3 bit 7 when held (flag bit 36 with flags2 bit 7), flags2 bit
 * 6 while no combo slot is open and flags2 bit 61 while a lock B sits in
 * its frame window. The combo phase is picked, the motion stepped and the
 * contacts run (a state change there ends the frame). Off flag bit 22 a hit
 * that may be acted on records the impact (record 1 at the facing), clamps
 * the hit points for hit kinds 2/4 and enters state 0x14; on flag bit 22 a
 * record whose contact mode is not 2 sets combo bit 3. A positive hold
 * reached by the anim frame latches the record's held bit and raises flag
 * bit 49 (node enabled); the held bit raises flags3 bit 52 for the local
 * player. Without input bit 2: an open slot off flag bit 21 clamps and
 * enters state 2; a latched hold past hold + grace (0x3000 held, else
 * 0x3c000) drops flag bit 49 (node disabled) and the recoil. With input bit
 * 2 and no hold: past the longest slot with nothing open, rule 0x2e off and
 * not held, clamp and enter state 0x16; with a hold: drop flag bit 49. The
 * post-draw hook says whether the state is over; the frame reaching the
 * record's window (-0x1000 = never) in a non-zero phase forces it. Over:
 * flag bit 49 up, node enabled, flags2 bit 1 (local player). Flags2 bit 1
 * then finishes the combo: flag bit 32 down, the anchor delta zeroed, hit
 * points clamped, and by phase -- 1: unhandled when free of flag bits 22/16
 * with the anchor reachable under input bit 2 (stop), else cursor A
 * advances; 3: an allowed slot action runs the pre-draw hook with its move
 * mode, enters state 0 with flag bit 29 (flags2 bit 2 for the local player
 * without input bit 2), else flags3 bit 55 and unhandled; 4: input bit 2
 * resets the timers keeping the motion x/z, else unhandled; 5: without input
 * bit 2 and a clear react block, state 0xd with flag bit 2, else unhandled;
 * 2: input bit 2 with rule 0x32, the slot block and no aim/no lock B enters
 * state 0xb, else lock B (charge kind 1 needs a negative limit) advances
 * cursor B; 0/default: unhandled. Flag bit 22 drops. Unhandled: held ->
 * pre-draw 0xe, state 6; input bit 2 -> latched hold or an open slot off
 * record flag 4: stop -> anchor phase 3 and a signalled reset, else pre-draw
 * 0 and state 0; otherwise state 0x16; no input bit 2 -> flag bit 2 when
 * nothing is open, state 2. With a lock: Ov002_Set(1, 1) for player 0 off
 * flag bit 16 unless global bit 2, flags2 bit 31 (local), pre-draw with the
 * record's anim slot + 0x1e, flag bit 29, the entry flags broadcast and the
 * post-draw hook (or dispatch 0), flag bit 49 down, phase and timer cleared,
 * the pair processed. Any state change drops flags3 bit 4 and flag bit 32,
 * raises flag bit 29, processes the pair and clears the combo node state.
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

/* Ov022ComboRecord */
struct ComboRecord {
    u8 pad00[2];
    u8 nContactMode;             /* 0x02 */
    u8 nAnimSlot;                /* 0x03 */
    u8 pad04[4];
    int nEntryFlags;             /* 0x08 */
    int nWindow;                 /* 0x0c */
    u8 pad10[0xc];
    int nHold;                   /* 0x1c */
    u8 pad20[4];
    int nLimit;                  /* 0x24 */
    u8 pad28[4];
    u32 nFlags2c;                /* 0x2c */
    u8 pad30[0xc];
    u8 bHeld : 1;                /* 0x3c bit 0 */
    u8 nRest3c : 7;
};

/* Ov022ComboLock */
struct ComboLock {
    u8 pad00[0x14];
    struct ComboRecord *pRecord; /* 0x14 */
};

/* Ov022ComboState */
struct ComboState {
    u32 nFlags;                  /* 0x000 */
    u8 pad004[0x46c];
    struct ComboLock *pLock;     /* 0x470 */
    u8 pad474[8];
    int nPhase;                  /* 0x47c */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u16 nFlags;                  /* 0x00 */
    u8 nState;                   /* 0x02 */
    u8 pad03[0x6d];
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

/* Ov022AimState */
struct AimState {
    u8 nJumpCount;               /* 0x00 */
    u8 bHold;                    /* 0x01 */
    s8 nAimMode;                 /* 0x02 */
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
    u8 pad000a[0x16];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x58];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0xe];
    u16 nLatchedArg;             /* 0x04de */
    u8 pad04e0[0x184];
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
    u8 pad06a4[0x10c];
    int nAnimFrame;              /* 0x07b0 */
    u8 nAnchorPhase;             /* 0x07b4 */
    u8 pad07b5[0x137];
    VecFx32 vecAnchorDelta;      /* 0x08ec */
    u8 pad08f8[0x18];
    struct ComboState combo;     /* 0x0910 */
    u8 pad0d90[0x2e0];
    u8 slotBlk;                  /* 0x1070 */
    u8 pad1071[0x127];
    u8 reactBlk;                 /* 0x1198 */
    u8 pad1199[0x10ef];
    struct ReactionCtx reactionCtx;  /* 0x2288 */
    u8 pad22f8[0x3c4];
    struct SweepContact contact; /* 0x26bc */
    u8 pad2770[0x34c];
    int nAimAngle;               /* 0x2abc */
    u8 pad2ac0[0xf0];
    struct AimState aim;         /* 0x2bb0 */
};

#define FLAG_BIT2 (1ULL << 2)
#define FLAG_BIT16 (1ULL << 16)
#define FLAG_BIT21 (1ULL << 21)
#define FLAG_BIT22 (1ULL << 22)
#define FLAG_BIT29 (1ULL << 29)
#define FLAG_BIT32 (1ULL << 32)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define FLAG2_BIT2 (1ULL << 2)
#define FLAG2_BIT4 (1ULL << 4)
#define FLAG2_BIT6 (1ULL << 6)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT31 (1ULL << 31)
#define FLAG2_BIT55 (1ULL << 55)
#define FLAG2_BIT61 (1ULL << 61)
#define FLAG3_BIT4 (1ULL << 4)
#define FLAG3_BIT7 (1ULL << 7)
#define FLAG3_BIT52 (1ULL << 52)
#define INPUT_BIT2 0x4
#define INPUT_BIT7 0x80
#define NODE_NO_ANIM 0x20
#define ANGLE_BIAS 0x8000
#define RECORD_IMPACT 1
#define IMPACT_TAG 0xa3d
#define HIT_STATE_LANDED 2
#define HIT_STATE_MISSED 4
#define CONTACT_MODE_2 2
#define GRACE_HELD 0x3000
#define GRACE_FREE 0x3c000
#define RULE_NO_END 0x2e
#define RULE_DODGE 0x32
#define WINDOW_NEVER -0x1000
#define FRAME_NEVER 0x7fffffff
#define RECORD_FLAG_4 0x4
#define GLOBAL_BIT2 0x4
#define ANIM_SLOT_BASE 0x1e
#define ANCHOR_PHASE_3 3
#define CHARGE_KIND_1 1
#define PREDRAW_HELD 0xe
#define STATE_IDLE 0
#define STATE_END 2
#define STATE_HELD 6
#define STATE_DODGE 0xb
#define STATE_REACT 0xd
#define STATE_HIT 0x14
#define STATE_LAND_END 0x16
#define PHASE_NONE 0

extern const VecFx32 data_02041dc8;               /* kVecZero */
extern u8 data_0204c240;                    /* global flags byte */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern void *func_ov022_020b0e20(struct ComboState *pCombo);                    /* Ov022_ComboStateOpenOrSelf */
extern struct ComboLock *func_ov022_020b0b10(struct ComboState *pCombo);        /* Ov022_PickComboLockB */
extern int func_ov022_020b0bf0(struct ComboState *pCombo, int nFrame);          /* Ov022_IsFrameInComboWindow */
extern void func_ov022_0209f118(struct Actor *pActor);                          /* Ov022_PickComboPhase */
extern void func_ov022_0209f370(struct Actor *pActor);                          /* Ov022_StepComboMotion */
extern int func_ov022_020a5570(struct Actor *pActor);                           /* Ov022_RunComboContacts */
extern int func_ov022_02095a38(struct Actor *pActor);                           /* Ov022_MayActOnHit */
extern void func_ov022_020ad208(struct Actor *pActor, int nRecord, VecFx32 *pAt, int nTag,
                                u32 nAngle, int nKind);                         /* Ov022_MarshalNetworkRecord */
extern void func_ov022_02095c58(struct Actor *pActor);                          /* Ov022_ClampHitPoints */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);               /* Ov022_ActorSetState */
extern void func_ov022_020b0e3c(struct ComboState *pCombo);                     /* Ov022_SetBit3IfClear */
extern void func_0202af1c(u16 *pAnimFlags);                                     /* SceneNode_Enable */
extern void func_0202af2c(u16 *pAnimFlags);                                     /* SceneNode_Disable */
extern int func_ov022_020b0b58(struct ComboState *pCombo);                      /* Ov022_LongestComboSlot */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_02095dc8(struct Actor *pActor);                           /* Ov022_TestAnchorReachable */
extern void func_ov022_020b09e0(struct ComboState *pCombo);                     /* Ov022_AdvanceCursorClampFieldA */
extern int func_ov022_0209038c(struct ReactionCtx *pCtx, u32 nArg);             /* Ov022_IsSlotActionAllowed */
extern int func_ov022_02090978(struct ReactionCtx *pCtx, u32 nArg);             /* Ov022_GetSlotMoveMode */
extern void func_ov022_020b09c4(struct ComboState *pCombo);                     /* Ov022_ClearNodeState */
extern int func_ov022_02097d50(struct Actor *pActor, int bSignal);              /* Ov022_ResetTimersAndMaybeSignal */
extern int func_ov022_02092b10(u8 *pBlk, u32 nSlot);                            /* Ov022_IsSubAndField170Zero */
extern int func_ov022_020926f8(u8 *pBlk);
extern int func_ov022_0209bd04(struct Actor *pActor);                           /* Ov022_GetChargeKind */
extern void func_ov022_020b0a54(struct ComboState *pCombo);                     /* Ov022_AdvanceCursorClampFieldB */
extern void func_ov002_0206cd60(int a, int b);                                  /* Ov002_Set */
extern void func_ov022_020acf14(struct Actor *pActor, int nFlags);              /* Ov022_SetEntryFlagsAndBroadcast */
extern void func_ov022_02097038(struct Actor *pActor, int nArg);                /* Ov022_SetField7b0AndDispatch */
extern void func_ov022_0209c700(struct Actor *pActor);                          /* Ov022_ProcessPairThenSetFlag */

int func_ov022_020a49e0(struct Actor *pActor)
{
    VecFx32 vecAt;
    VecFx32 vecKeep;
    int nRet;
    struct ComboRecord *pRecord;
    struct ComboLock *pLock;
    int nHold;
    int nGrace;
    int nLimit;
    int nEntryFlags;
    int bHandled;
    int bStop;
    int bDone;

    pRecord = pActor->combo.pLock->pRecord;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT4;
    }
    if (func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT4;
    }
    pActor->nInputMask &= ~INPUT_BIT7;
    if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0 && func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT7;
    }
    if (func_ov022_020b0e20(&pActor->combo) == 0 && func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT6;
    }
    if (func_ov022_020b0b10(&pActor->combo) != 0 && func_ov022_020b0bf0(&pActor->combo, pActor->nAnimFrame) != 0
        && func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT61;
    }
    func_ov022_0209f118(pActor);
    func_ov022_0209f370(pActor);
    nRet = func_ov022_020a5570(pActor);
    if (nRet != 0) {
        goto done;
    }
    if ((pActor->nFlags & FLAG_BIT22) == 0) {
        if (func_ov022_02095a38(pActor) != 0) {
            vecAt = pActor->contact.vec;
            func_ov022_020ad208(pActor, RECORD_IMPACT, &vecAt, IMPACT_TAG, (u16)(pActor->pNode->nAngle - ANGLE_BIAS), 0);
            if (!(pActor->contact.nState != HIT_STATE_MISSED && pActor->contact.nState != HIT_STATE_LANDED)) {
                func_ov022_02095c58(pActor);
            }
            nRet = func_ov022_020a35f4(pActor, STATE_HIT);
            goto done;
        }
    } else if (pRecord->nContactMode != CONTACT_MODE_2) {
        func_ov022_020b0e3c(&pActor->combo);
    }
    nHold = pActor->combo.pLock->pRecord->nHold;
    if (nHold > 0 && !pRecord->bHeld && pActor->nAnimFrame >= nHold) {
        pRecord->bHeld = 1;
        pActor->nFlags |= FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
    }
    if (pRecord->bHeld && func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT52;
    }
    if ((pActor->nInputMask & INPUT_BIT2) == 0) {
        if (func_ov022_020b0e20(&pActor->combo) != 0 && (pActor->nFlags & FLAG_BIT21) == 0) {
            func_ov022_02095c58(pActor);
            nRet = func_ov022_020a35f4(pActor, STATE_END);
            goto done;
        }
        if (nHold != 0 && pRecord->bHeld) {
            nGrace = (pActor->nFlags & FLAG_BIT36) != 0 ? GRACE_HELD : GRACE_FREE;
            if ((int)pActor->nStateTimer >= nHold + nGrace) {
                pActor->nFlags &= ~FLAG_BIT49;
                if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
                    func_0202af2c(&pActor->pNode->nAnimFlags);
                }
                pActor->nRecoil = 0;
            }
        }
    } else if (nHold == 0) {
        if (pActor->nAnimFrame > func_ov022_020b0b58(&pActor->combo) && func_ov022_020b0e20(&pActor->combo) == 0
            && func_020358f4(pActor->nId, RULE_NO_END) == 0
            && ((pActor->nFlags & FLAG_BIT36) == 0 || (pActor->nFlags2 & FLAG2_BIT7) == 0)) {
            func_ov022_02095c58(pActor);
            nRet = func_ov022_020a35f4(pActor, STATE_LAND_END);
            goto done;
        }
    } else {
        pActor->nFlags &= ~FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
            func_0202af2c(&pActor->pNode->nAnimFlags);
        }
    }
    pActor->bStateOver = (u8)pActor->pfnPostDraw(pActor);
    nLimit = FRAME_NEVER;
    if (pActor->combo.pLock->pRecord->nWindow != WINDOW_NEVER) {
        nLimit = pActor->combo.pLock->pRecord->nWindow;
    }
    if (pActor->nAnimFrame >= nLimit && pActor->combo.nPhase != PHASE_NONE) {
        pActor->bStateOver = 1;
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
    bStop = 0;
    if ((pActor->nFlags2 & FLAG2_BIT1) != 0) {
        bHandled = 1;
        pActor->nFlags &= ~FLAG_BIT32;
        pActor->vecAnchorDelta = data_02041dc8;
        func_ov022_02095c58(pActor);
        switch (pActor->combo.nPhase) {
        case 1:
            if ((pActor->nFlags & FLAG_BIT22) == 0 && (pActor->nFlags & FLAG_BIT16) == 0 && func_ov022_02095dc8(pActor) != 0
                && (pActor->nInputMask & INPUT_BIT2) != 0) {
                bStop = 1;
                bHandled = 0;
            }
            if (bHandled) {
                func_ov022_020b09e0(&pActor->combo);
            }
            break;
        case 3:
            if (func_ov022_0209038c(&pActor->reactionCtx, pActor->nLatchedArg) != 0) {
                if ((pActor->nInputMask & INPUT_BIT2) == 0 && func_02030788() == 0) {
                    pActor->nFlags2 |= FLAG2_BIT2;
                }
                pActor->pfnPreDraw(pActor, func_ov022_02090978(&pActor->reactionCtx, pActor->nLatchedArg));
                nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
                pActor->nFlags |= FLAG_BIT29;
                func_ov022_020b09c4(&pActor->combo);
            } else {
                if (func_02030788() == 0) {
                    pActor->nFlags2 |= FLAG2_BIT55;
                }
                bHandled = 0;
            }
            break;
        case 4:
            if ((pActor->nInputMask & INPUT_BIT2) == 0) {
                bHandled = 0;
            } else {
                vecKeep = pActor->vecMotion;
                nRet = func_ov022_02097d50(pActor, 0);
                pActor->vecMotion.x = vecKeep.x;
                pActor->vecMotion.z = vecKeep.z;
                func_ov022_020b09c4(&pActor->combo);
            }
            break;
        case 5:
            if ((pActor->nInputMask & INPUT_BIT2) == 0 && func_ov022_02092b10(&pActor->reactBlk, pActor->aim.nJumpCount) != 0) {
                nRet = func_ov022_020a35f4(pActor, STATE_REACT);
                pActor->nFlags |= FLAG_BIT2;
                func_ov022_020b09c4(&pActor->combo);
            } else {
                bHandled = 0;
            }
            break;
        case 2:
            bDone = 0;
            if ((pActor->nInputMask & INPUT_BIT2) != 0 && func_020358f4(pActor->nId, RULE_DODGE) != 0
                && func_ov022_020926f8(&pActor->slotBlk) != 0
                && (pActor->nAimAngle == -1 || func_ov022_020b0b10(&pActor->combo) == 0)) {
                nRet = func_ov022_020a35f4(pActor, STATE_DODGE);
                func_ov022_020b09c4(&pActor->combo);
                bDone = 1;
            }
            if (!bDone) {
                bHandled = 0;
                pLock = func_ov022_020b0b10(&pActor->combo);
                if (pLock != 0) {
                    if (func_ov022_0209bd04(pActor) == CHARGE_KIND_1) {
                        if (pLock->pRecord->nLimit < 0) {
                            bHandled = 1;
                        }
                    } else {
                        bHandled = 1;
                    }
                }
                if (bHandled) {
                    func_ov022_020b0a54(&pActor->combo);
                }
            }
            break;
        default:
            bHandled = 0;
            break;
        }
        pActor->nFlags &= ~FLAG_BIT22;
        if (!bHandled) {
            if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
                pActor->pfnPreDraw(pActor, PREDRAW_HELD);
                nRet = func_ov022_020a35f4(pActor, STATE_HELD);
            } else if ((pActor->nInputMask & INPUT_BIT2) != 0) {
                if (pRecord->bHeld == 1
                    || (func_ov022_020b0e20(&pActor->combo) != 0 && (pRecord->nFlags2c & RECORD_FLAG_4) == 0)) {
                    if (bStop) {
                        pActor->nAnchorPhase = ANCHOR_PHASE_3;
                        nRet = func_ov022_02097d50(pActor, 1);
                    } else {
                        pActor->pfnPreDraw(pActor, 0);
                        nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
                    }
                } else {
                    nRet = func_ov022_020a35f4(pActor, STATE_LAND_END);
                }
            } else {
                if (func_ov022_020b0e20(&pActor->combo) == 0) {
                    pActor->nFlags |= FLAG_BIT2;
                }
                nRet = func_ov022_020a35f4(pActor, STATE_END);
            }
            func_ov022_020b09c4(&pActor->combo);
        }
        if (pActor->combo.pLock != 0) {
            nEntryFlags = pActor->combo.pLock->pRecord->nEntryFlags;
            if ((data_0204c240 & GLOBAL_BIT2) == 0) {
                if ((u32)(pActor->nFlags & FLAG_BIT16) == 0 && pActor->nId == 0) {
                    func_ov002_0206cd60(1, 1);
                }
            }
            if (func_02030788() == 0) {
                pActor->nFlags2 |= FLAG2_BIT31;
            }
            pActor->pfnPreDraw(pActor, pActor->combo.pLock->pRecord->nAnimSlot + ANIM_SLOT_BASE);
            pActor->nFlags |= FLAG_BIT29;
            if (nEntryFlags > 0) {
                func_ov022_020acf14(pActor, nEntryFlags);
                pActor->pfnPostDraw(pActor);
            } else {
                func_ov022_02097038(pActor, 0);
            }
            pActor->nFlags &= ~FLAG_BIT49;
            if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
                func_0202af2c(&pActor->pNode->nAnimFlags);
            }
            pActor->combo.nPhase = PHASE_NONE;
            pActor->nStateTimer = 0;
            func_ov022_0209c700(pActor);
        }
    }
done:
    if (nRet != 0) {
        pActor->nFlags3 &= ~FLAG3_BIT4;
        pActor->nFlags &= ~FLAG_BIT32;
        pActor->nFlags |= FLAG_BIT29;
        func_ov022_0209c700(pActor);
        func_ov022_020b09c4(&pActor->combo);
    }
    return nRet;
}
