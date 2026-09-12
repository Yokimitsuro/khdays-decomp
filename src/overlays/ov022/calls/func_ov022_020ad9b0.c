/* Ov022_StepPartnerSlot -- one frame of a partner's slot AI against its
 * leader.
 *
 * The buttons and flag bit 61 clear, the command kind rests at 7 and the
 * walk speed is 0x4cd (0x333 under the global). When input is allowed for
 * the active slot the slot goes to state 1 with buttons2, flag bit 33 and
 * the command argument cleared and the reaction context marked. Nothing
 * more runs under flag bit 24, allowed input, or flags2 bit 33 with flag
 * bit 34. The cooldown, rest and wait timers count down by a frame step
 * (0xcd, or 0x89 under the global) clamped to 0..2.0 / 0..rest time /
 * 0..1.0. A leader holding input bit 7 while the partner has input bit 2
 * asks for a guard break when the leader is within 1.0 flat and 2.0 up.
 *
 * State 9 aims one reach past the leader: the aim point is checked, moved
 * out by the reach, the walk speed halved and the partner steered with
 * climbing; a steer that fails or a leader beyond the near range breaks
 * the guard (off leader flag bit 26) and clears the stall. State 3 holds a
 * formation offset: every global-count frames the side vector (leader
 * direction x up, mirrored from the second partner on) is rebuilt 1.5
 * beside the leader; the partner steers to leader + offset (no climbing
 * unless the leader holds input bit 2), a failed steer breaks the guard
 * unless knockdown kind 0xb, then the follow slot steps. State 4 is the
 * idle choice: a wander is barred by slot flag 0 and a seek by slot flag
 * 1, knockdown kind 6, a blocked run or slot flag 6; both open, a roll of
 * 100 against chance base + bonus (+10 for kind 0xa) keeps one. A wander
 * looks at the ref item: within the reach height and reach bonus +
 * inverse (or feet mode) it is reached (command 9, rest reset under slot
 * flag 6 with no anchor phase, no combo lock and phase != 1), else the
 * partner steers to it (kind != 9), and slot flag 6 follows the outcome. A
 * seek walks the twelve slot ids in kOv022SlotOrder: an allowed, set slot
 * whose ref entity stat (kOv022SlotCols by column, x16) is 0 for kinds 9 /
 * 0x18 / 0x19 / 0x27 in column 0, or 1.0 with a 75% roll, or above 1.0, is
 * skipped; otherwise a 50% roll picks it (command 8, rest reset), and
 * nothing picked with nothing allowed raises slot flag 1. State 10 keeps
 * flag bit 44 while the run is neither in state 9/6 nor blocked, else
 * returns to state 1 with it cleared. State 5 decides an aid: slot flag 4
 * means aid, flag 3 without flag 5 means none; free of flags 4, 2, 3 and
 * kind 6 a roll of 100 against chance base + bonus (0x32000 past game
 * field 9 >= 0x48 with the global bit and getter 0x69) decides; no aid
 * tries the three kOv022AidKeys through Table_FindKey (command 0xb,
 * cooldown 2.0, else slot flag 4), an aid tries kOv022AidSlots (command
 * 8, cooldown 2.0, else slot flag 3). States 6/7/8 break the guard when
 * the leader is past the outer reach, take slot 0xe / key 4 / key 7 as
 * commands 8 / 0xb / 0xb with cooldown 2.0, and return to state 1. State
 * 2 stalls 0.5 then returns to state 1. Every state ends with its share
 * of the follow step, the partner target drive, the retreat roll, the aid
 * decision and the slot state toggle.
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

/* PlayerSlotDesc */
struct SlotDesc {
    u8 pad00[0x18];
    int nReachOuter;             /* 0x18 */
    int nReachInner;             /* 0x1c */
    int nRangeNear;              /* 0x20 */
    u8 pad24[4];
    int nFeetMode;               /* 0x28 */
    int nRestTime;               /* 0x2c */
    u8 pad30[8];
    int nChanceBonus;            /* 0x38 */
};

/* PlayerSlot */
struct PlayerSlot {
    int nState;                  /* 0x00 */
    u32 nFlags;                  /* 0x04 */
    int nStall;                  /* 0x08 */
    int nCooldown;               /* 0x0c */
    int nRest;                   /* 0x10 */
    int nRespawnThreshold;       /* 0x14 */
    int nWait;                   /* 0x18 */
    int nChanceBase;             /* 0x1c */
    VecFx32 vecPos;              /* 0x20 */
    u8 pad2c[4];
    int nReachHeight;            /* 0x30 */
    int nReachBonus;             /* 0x34 */
    VecFx32 vecOffset;           /* 0x38 */
    struct SlotDesc *pDesc;      /* 0x44 */
};

/* Ov107ChildStats */
struct RefStats {
    u8 pad00[0x34];
    short aStats[12];            /* 0x34 */
};

/* Ov107Child */
struct RefNode {
    u8 pad000[0x19c];
    u8 nKind;                    /* 0x19c */
    u8 pad19d[3];
    struct RefStats *pStats;     /* 0x1a0 */
};

/* Ov022RefPlace */
struct RefPlace {
    u8 pad00[4];
    VecFx32 vecPos;              /* 0x04 */
};

/* Ov022RefItem */
struct RefItem {
    struct RefPlace *pPlace;     /* 0x00 */
};

/* Ov022ComboState */
struct ComboState {
    u32 nFlags;                  /* 0x000 */
    u8 pad004[0x46c];
    void *pLock;                 /* 0x470 */
    u8 pad474[8];
    int nPhase;                  /* 0x47c */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u16 nFlags;                  /* 0x00 */
    u8 nState;                   /* 0x02 */
    u8 pad03[0x6d];
};

/* Ov022ActionOwner */
struct ActionOwner {
    u32 nFlags;                  /* 0x00 */
};

/* Ov022Charge */
struct Charge {
    s8 nKnockdownKind;           /* 0x00 */
};

/* Table_FindKey entry */
struct KeyEntry {
    u16 nKey;                    /* 0x00 */
    short nCount;                /* 0x02 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0xe];
    u16 nButtons;                /* 0x0018 */
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[8];
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x43c];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x20];
    int nWalkSpeed;              /* 0x04b8 */
    u8 pad04bc[0x1a];
    s8 nCommandKind;             /* 0x04d6 */
    u8 pad04d7[1];
    u16 nCommandArg;             /* 0x04d8 */
    u8 pad04da[0x22];
    struct RefNode *pRefEntity;  /* 0x04fc */
    struct RefItem *pRefItem;    /* 0x0500 */
    u8 pad0504[0x2b0];
    u8 nAnchorPhase;             /* 0x07b4 */
    u8 pad07b5[0x15b];
    struct ComboState combo;     /* 0x0910 */
    u8 pad0d90[0x14f8];
    struct ReactionCtx reactionCtx;  /* 0x2288 */
    struct ActionOwner run;      /* 0x22f8 */
    u8 pad22fc[0x474];
    struct Charge charge;        /* 0x2770 */
};

#define FLAG_BIT24 (1ULL << 24)
#define FLAG_BIT26 (1ULL << 26)
#define FLAG_BIT33 (1ULL << 33)
#define FLAG_BIT34 (1ULL << 34)
#define FLAG_BIT44 (1ULL << 44)
#define FLAG_BIT61 (1ULL << 61)
#define FLAG2_BIT33 (1ULL << 33)
#define INPUT_BIT2 0x4
#define INPUT_BIT7 0x80
#define BUTTON_BIT0 0x1
#define WALK_FAST 0x4cd
#define WALK_SLOW 0x333
#define STEP_FAST 0xcd
#define STEP_SLOW 0x89
#define COOLDOWN_MAX 0x2000
#define WAIT_MAX 0x1000
#define STALL_LIMIT 0x800
#define NEAR_FLAT 0x1000
#define NEAR_UP 0x2000
#define OFFSET_SIDE 0x1800
#define ROLL_100 0x64000
#define ROLL_BOOST 0xa000
#define ROLL_FIXED 0x32000
#define STAT_FULL 0x1000
#define STAT_SHIFT 4
#define PICK_CHANCE 0x32
#define STAT_ROLL 0x19
#define FIELD_THRESHOLD 0x48
#define GETTER_MATCH 0x69
#define GLOBAL_BIT0 0x1
#define SLOT_FLAG0 0x1
#define SLOT_FLAG1 0x2
#define SLOT_FLAG2 0x4
#define SLOT_FLAG3 0x8
#define SLOT_FLAG4 0x10
#define SLOT_FLAG5 0x20
#define SLOT_FLAG6 0x40
#define KIND_STAY 6
#define KIND_FOUND 9
#define KIND_BOOST 0xa
#define KIND_NO_BREAK 0xb
#define REF_KIND_A 9
#define REF_KIND_B 0x18
#define REF_KIND_C 0x19
#define REF_KIND_D 0x27
#define COMMAND_REST 7
#define COMMAND_SLOT 8
#define COMMAND_ITEM 9
#define COMMAND_KEY 0xb
#define NO_ARG 0xffff
#define SLOT_AID 0xe
#define KEY_A 4
#define KEY_B 7
#define STATE_IDLE 1
#define ROW_COUNT 12
#define COL_COUNT 4
#define AID_COUNT 3

#define FRAME_STEP() (func_02023c40() == 1 ? STEP_FAST : STEP_SLOW)
#define CLAMP(v, lo, hi) ((v) > (hi) ? (hi) : ((v) < (lo) ? (lo) : (v)))

extern const VecFx32 data_ov022_020b27c0;   /* kOv022Up */
struct IdRow {
    int a[ROW_COUNT];
};

struct IdCols {
    int a[COL_COUNT];
};

struct IdTriple {
    int a[AID_COUNT];
};

extern const struct IdRow data_ov022_020b27dc;     /* kOv022SlotOrder */
extern const struct IdCols data_ov022_020b27cc;    /* kOv022SlotCols */
extern const struct IdTriple data_ov022_020b279c;  /* kOv022AidKeys */
extern const struct IdTriple data_ov022_020b27b4;  /* kOv022AidSlots */
extern u8 data_ov022_020b2eb4;              /* gOv022PartnerTick */
extern u8 data_0204c240;                    /* global flags byte */

extern struct PlayerSlot *func_020358a4(int nSlot);                             /* GetPlayerSlotTableEntry */
extern int func_02023c40(void);                                                 /* LoadGlobalU8_0204c058 */
extern int func_ov022_0208868c(void);                                           /* Ov022_IsInputAllowedForActiveSlot */
extern void func_ov022_02090360(struct ReactionCtx *pCtx);                      /* ov022_SetBit5OfHalf0IfByte2 */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern void func_ov022_020acbf0(struct Actor *pActor);                          /* Ov022_RequestGuardBreak */
extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);                             /* VEC_Distance */
extern int func_ov022_020aef50(struct Actor *pActor, struct Actor *pLeader, VecFx32 *pPoint);
extern void VEC_MultAdd(int nScale, VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_ov022_020ae8a4(struct Actor *pSelf, struct Actor *pLeader, VecFx32 *pPoint, int bNoClimb);   /* Ov022_SteerPartnerToPoint */
extern void func_ov022_020aeef8(struct Actor *pActor, struct Actor *pLeader);    /* ToggleSlotStateAroundCall */
extern void func_01ff8d18(VecFx32 *pIn, VecFx32 *pOut);                         /* VEC_Normalize */
extern void VEC_CrossProduct(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_ov022_020aed60(struct Actor *pActor, struct Actor *pPartner);   /* Ov022_StepFollowSlot */
extern int func_ov022_02095524(struct ActionOwner *pRun);                       /* ov022_IsState9Or6WithFlag200 */
extern int func_0203084c(void);                                                 /* Session_RandNext */
extern int func_ov022_020afd78(struct Actor *pActor);                           /* GetInverseByHeaderKind */
extern void *func_ov022_020b0ac8(struct ComboState *pCombo);                    /* Ov022_PickComboLockA */
extern void *func_ov022_020b0b10(struct ComboState *pCombo);                    /* Ov022_PickComboLockB */
extern int func_020357f4(int nId, int nSlot);                                   /* Load2DArrayU8_c714 */
extern int func_ov022_0209029c(struct ReactionCtx *pCtx, int nBit);             /* IsSlotBitSetOrAll */
extern u32 func_020307f4(int nRange);                                           /* Session_RandNextScaled */
extern void func_ov022_020af180(struct Actor *pActor, struct Actor *pLeader, VecFx32 *pPoint);   /* Ov022_DrivePartnerTarget */
extern void func_ov022_020af930(struct Actor *pActor);                          /* Ov022_RollSlotRetreat */
extern void func_ov022_020afabc(struct Actor *pSelf, struct Actor *pTarget);     /* Ov022_DecidePartnerAid */
extern int func_ov022_020956e8(struct ActionOwner *pRun);                       /* Ov022_IsActionBlocked */
extern int func_020235d0(int nFlag, int nWhich);                                /* GameState_GetField */
extern int func_ov002_0206b84c(void);                                           /* Ov002_Getter */
extern struct KeyEntry *func_0203583c(int nId, int nKey);                        /* Table_FindKey */

static inline void VEC_Set(VecFx32 *pVec, int x, int y, int z)
{
    pVec->x = x;
    pVec->y = y;
    pVec->z = z;
}

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

/* nFlags is unused here; the caller (0208739c) still passes its flag word */
void func_ov022_020ad9b0(struct Actor *pActor, struct Actor *pLeader, u32 nFlags)
{
    VecFx32 vecDelta;
    VecFx32 vecTarget;
    VecFx32 vecUp;
    VecFx32 vecSide;
    VecFx32 vecToLeader;
    VecFx32 vecDir;
    struct PlayerSlot *pSlot;
    struct RefNode *pRef;
    struct RefStats *pStats;
    struct KeyEntry *pEntry;
    int nDist;
    int nDy;
    int nRoll;
    int nLimit;
    int nField;
    int nInv;
    int nStat;
    int nCol;
    int nId;
    int bWander;
    int bSeek;
    int bFound;
    int i;
    int bSkip;
    int bNoClimb;
    int bIdle;
    int bAid;
    u32 nSlotFlags;
    int bAny;
    int nKey;
    VecFx32 *pPoint;
    int bPicked;
    VecFx32 *pAim;

    pPoint = &pLeader->vecAim;
    pSlot = func_020358a4((u8)(pActor->nId - 1));
    pActor->nButtons = 0;
    pActor->nFlags &= ~FLAG_BIT61;
    pActor->nCommandKind = COMMAND_REST;
    pActor->nWalkSpeed = func_02023c40() == 1 ? WALK_FAST : WALK_SLOW;
    if (func_ov022_0208868c() != 0) {
        pActor->nButtons2 = 0;
        pSlot->nState = STATE_IDLE;
        pActor->nFlags &= ~FLAG_BIT33;
        func_ov022_02090360(&pActor->reactionCtx);
        pActor->nCommandArg = NO_ARG;
    }
    if ((pActor->nFlags & FLAG_BIT24) != 0) {
        return;
    }
    if (func_ov022_0208868c() != 0) {
        return;
    }
    if ((pActor->nFlags2 & FLAG2_BIT33) != 0 && (pActor->nFlags & FLAG_BIT34) != 0) {
        return;
    }
    pSlot->nCooldown = CLAMP(pSlot->nCooldown - FRAME_STEP(), 0, COOLDOWN_MAX);
    pSlot->nRest = CLAMP(pSlot->nRest - FRAME_STEP(), 0, pSlot->pDesc->nRestTime);
    pSlot->nWait = CLAMP(pSlot->nWait - FRAME_STEP(), 0, WAIT_MAX);
    if ((pLeader->nInputMask & INPUT_BIT7) != 0 && (pActor->nInputMask & INPUT_BIT2) != 0) {
        VEC_Subtract(pPoint, &pActor->vecAim, &vecDelta);
        nDy = vecDelta.y;
        vecDelta.y = 0;
        if (VEC_Mag(&vecDelta) < NEAR_FLAT && nDy < NEAR_UP) {
            func_ov022_020acbf0(pActor);
        }
    }
    switch (pSlot->nState) {
    case 9:
        nDist = func_01ff8e94(pPoint, &pActor->vecAim);
        vecTarget = *pPoint;
        pActor->nFlags |= FLAG_BIT61;
        if (func_ov022_020aef50(pActor, pLeader, &vecTarget) != 0) {
            VEC_MultAdd(pSlot->pDesc->nReachOuter, &vecTarget, &pActor->vecAim, &vecTarget);
            pActor->nWalkSpeed = FxMul(func_02023c40() == 1 ? WALK_FAST : WALK_SLOW, 0x800);
            if (func_ov022_020ae8a4(pActor, pLeader, &vecTarget, 1) != 0 || pSlot->pDesc->nRangeNear < nDist) {
                if ((pLeader->nFlags & FLAG_BIT26) == 0) {
                    func_ov022_020acbf0(pActor);
                    pSlot->nStall = 0;
                }
            }
        }
        func_ov022_020aeef8(pActor, pLeader);
        return;
    case 3:
        vecUp = data_ov022_020b27c0;
        data_ov022_020b2eb4++;
        bNoClimb = 1;
        if ((u32)func_02023c40() < data_ov022_020b2eb4) {
            data_ov022_020b2eb4 = 0;
            VEC_Subtract(pPoint, &pActor->vecAim, &vecToLeader);
            func_01ff8d18(&vecToLeader, &vecDir);
            VEC_CrossProduct(&vecDir, &vecUp, &vecSide);
            if (pActor->nId >= 2) {
                VEC_Set(&vecSide, -vecSide.x, -vecSide.y, -vecSide.z);
            }
            func_01ff8d18(&vecSide, &vecSide);
            VEC_MultAdd(OFFSET_SIDE, &vecSide, &vecToLeader, &vecSide);
            pSlot->vecOffset = vecSide;
        }
        vecSide = pSlot->vecOffset;
        VEC_Add(&pActor->vecAim, &vecSide, &vecSide);
        if ((pLeader->nInputMask & INPUT_BIT2) != 0) {
            bNoClimb = 0;
        }
        if (func_ov022_020ae8a4(pActor, pLeader, &vecSide, bNoClimb) != 0) {
            if (pActor->charge.nKnockdownKind != KIND_NO_BREAK && (pLeader->nFlags & FLAG_BIT26) == 0) {
                func_ov022_020acbf0(pActor);
            }
            pSlot->nStall = 0;
        }
        func_ov022_020aed60(pActor, pLeader);
        func_ov022_020aeef8(pActor, pLeader);
        return;
    case 4:
        bWander = 1;
        pActor->nCommandKind = COMMAND_REST;
        pActor->nCommandArg = NO_ARG;
        bSeek = 1;
        pActor->nButtons &= ~BUTTON_BIT0;
        if ((pSlot->nFlags & SLOT_FLAG0) != 0) {
            bWander = 0;
        }
        if ((pSlot->nFlags & SLOT_FLAG1) != 0 || pActor->charge.nKnockdownKind == KIND_STAY
            || func_ov022_02095524(&pActor->run) != 0 || (pSlot->nFlags & SLOT_FLAG6) != 0) {
            bSeek = 0;
        }
        if (bWander && bSeek) {
            nRoll = FxMul(func_0203084c(), ROLL_100);
            nLimit = pSlot->nChanceBase + pSlot->pDesc->nChanceBonus;
            if (pActor->charge.nKnockdownKind == KIND_BOOST) {
                nLimit += ROLL_BOOST;
            }
            if (nRoll <= nLimit) {
                bWander = 0;
            } else {
                bSeek = 0;
            }
        }
        if (bWander) {
            int bSteer;
            int bReached;

            bSteer = 0;
            bReached = 0;
            pAim = &pActor->vecAim;
            if (pActor->pRefItem != 0) {
                nInv = func_ov022_020afd78(pActor);
                nDist = func_01ff8e94(&pActor->pRefItem->pPlace->vecPos, pAim);
                nDy = pActor->pRefItem->pPlace->vecPos.y - pAim->y;
                if (nDy < 0) {
                    nDy = -nDy;
                }
                if (pSlot->nReachHeight > nDy && (pSlot->nReachBonus + nInv > nDist || pSlot->pDesc->nFeetMode != 0)) {
                    bReached = 1;
                } else if (pActor->charge.nKnockdownKind != KIND_FOUND) {
                    bSteer = 1;
                    if (func_ov022_020ae8a4(pActor, pLeader, &pActor->pRefItem->pPlace->vecPos, 0) != 0) {
                        bSteer = 0;
                        if (pActor->charge.nKnockdownKind != KIND_NO_BREAK && (pLeader->nFlags & FLAG_BIT26) == 0) {
                            func_ov022_020acbf0(pActor);
                        }
                        pSlot->nStall = 0;
                    }
                }
            }
            if (bReached) {
                pActor->nCommandKind = COMMAND_ITEM;
                pActor->nButtons |= BUTTON_BIT0;
                if ((pSlot->nFlags & SLOT_FLAG6) != 0 && pActor->nAnchorPhase == 0
                    && (pActor->combo.pLock == 0
                        || (func_ov022_020b0ac8(&pActor->combo) == 0 && func_ov022_020b0b10(&pActor->combo) == 0))
                    && pActor->combo.nPhase != 1) {
                    pSlot->nRest = pSlot->pDesc->nRestTime;
                }
            }
            if (bReached || bSteer) {
                pSlot->nFlags |= SLOT_FLAG6;
            } else {
                pSlot->nFlags &= ~SLOT_FLAG6;
            }
        } else if (bSeek) {
            struct IdRow ids = data_ov022_020b27dc;

            bAny = 0;
            bPicked = 0;
            for (i = 0; i < ROW_COUNT; i++) {
                nId = ids.a[i];
                if (func_020357f4(pActor->nId, nId) > 0 && func_ov022_0209029c(&pActor->reactionCtx, nId) != 0) {
                    pRef = pActor->pRefEntity;
                    bAny = 1;
                    if (pRef != 0 && (pStats = pRef->pStats) != 0) {
                        struct IdCols cols = data_ov022_020b27cc;

                        nCol = i % COL_COUNT;
                        bSkip = 0;
                        nStat = pStats->aStats[cols.a[nCol]] << STAT_SHIFT;
                        if (nCol == 0) {
                            switch (pRef->nKind) {
                            case REF_KIND_A:
                            case REF_KIND_B:
                            case REF_KIND_C:
                            case REF_KIND_D:
                                bSkip = 1;
                                break;
                            }
                        }
                        if (nStat == STAT_FULL) {
                            if (func_020307f4(100) > STAT_ROLL) {
                                bSkip = 1;
                            }
                        } else if (nStat > STAT_FULL) {
                            bSkip = 1;
                        }
                        if (bSkip) {
                            continue;
                        }
                    }
                    if (func_020307f4(100) > PICK_CHANCE) {
                        pActor->nCommandArg = nId;
                        bPicked = 1;
                        break;
                    }
                }
            }
            if (bPicked) {
                pActor->nCommandKind = COMMAND_SLOT;
                pActor->nButtons |= BUTTON_BIT0;
                pSlot->nRest = pSlot->pDesc->nRestTime;
            } else if (!bAny) {
                pSlot->nFlags |= SLOT_FLAG1;
            }
        } else {
            pSlot->nState = STATE_IDLE;
            return;
        }
        func_ov022_020af180(pActor, pLeader, pPoint);
        func_ov022_020af930(pActor);
        func_ov022_020afabc(pActor, pLeader);
        func_ov022_020aeef8(pActor, pLeader);
        return;
    case 10:
        if (func_ov022_02095524(&pActor->run) != 0 || func_ov022_020956e8(&pActor->run) != 0) {
            pSlot->nState = STATE_IDLE;
            pActor->nFlags &= ~FLAG_BIT44;
        } else {
            pActor->nFlags |= FLAG_BIT44;
        }
        return;
    case 5:
        nSlotFlags = pSlot->nFlags;
        bIdle = 1;
        bAid = 0;
        if ((nSlotFlags & SLOT_FLAG4) != 0) {
            bAid = 1;
        }
        if ((nSlotFlags & SLOT_FLAG3) != 0 && (nSlotFlags & SLOT_FLAG5) == 0) {
            bAid = 0;
        }
        if ((nSlotFlags & SLOT_FLAG4) == 0 && (nSlotFlags & SLOT_FLAG2) == 0 && (nSlotFlags & SLOT_FLAG3) == 0
            && pActor->charge.nKnockdownKind != KIND_STAY) {
            int nLimit;

            nRoll = FxMul(func_0203084c(), ROLL_100);
            nField = func_020235d0(0, 9);
            nLimit = pSlot->nChanceBase + pSlot->pDesc->nChanceBonus;
            if (nField >= FIELD_THRESHOLD && (data_0204c240 & GLOBAL_BIT0) != 0 && func_ov002_0206b84c() == GETTER_MATCH) {
                nLimit = ROLL_FIXED;
            }
            if (nRoll <= nLimit) {
                bAid = 1;
            }
            bIdle = 0;
        }
        if ((pSlot->nFlags & SLOT_FLAG4) == 0 && (bIdle || !bAid)) {
            struct IdTriple keys = data_ov022_020b279c;

            pActor->nCommandKind = COMMAND_REST;
            bFound = 0;
            pActor->nCommandArg = NO_ARG;
            pActor->nButtons &= ~BUTTON_BIT0;
            for (i = 0; i < AID_COUNT; i++) {
                pEntry = func_0203583c(pActor->nId, keys.a[i]);
                if (pEntry != 0 && pEntry->nCount > 0) {
                    nKey = pEntry->nKey;
                    bFound = 1;
                    break;
                }
            }
            if (bFound) {
                pActor->nCommandKind = COMMAND_KEY;
                pActor->nCommandArg = nKey;
                pActor->nButtons |= BUTTON_BIT0;
                pSlot->nCooldown = COOLDOWN_MAX;
            } else {
                pSlot->nFlags |= SLOT_FLAG4;
            }
        }
        if ((pSlot->nFlags & SLOT_FLAG2) == 0 && (pSlot->nFlags & SLOT_FLAG3) == 0 && pActor->charge.nKnockdownKind != KIND_STAY
            && (bIdle || bAid)) {
            struct IdTriple slots = data_ov022_020b27b4;

            pActor->nCommandKind = COMMAND_REST;
            bFound = 0;
            pActor->nCommandArg = NO_ARG;
            pActor->nButtons &= ~BUTTON_BIT0;
            for (i = 0; i < AID_COUNT; i++) {
                nId = slots.a[i];
                if (func_020357f4(pActor->nId, nId) > 0 && func_ov022_0209029c(&pActor->reactionCtx, nId) != 0) {
                    pActor->nCommandArg = nId;
                    bFound = 1;
                    break;
                }
            }
            if (bFound) {
                pActor->nCommandKind = COMMAND_SLOT;
                pActor->nButtons |= BUTTON_BIT0;
                pSlot->nCooldown = COOLDOWN_MAX;
            } else {
                pSlot->nFlags |= SLOT_FLAG3;
            }
        }
        func_ov022_020af930(pActor);
        func_ov022_020afabc(pActor, pLeader);
        func_ov022_020aeef8(pActor, pLeader);
        return;
    case 6:
    case 7:
    case 8:
        if (pSlot->pDesc != 0 && pSlot->pDesc->nReachOuter < func_01ff8e94(pPoint, &pActor->vecAim)
            && (pLeader->nFlags & FLAG_BIT26) == 0) {
            func_ov022_020acbf0(pActor);
        }
        switch (pSlot->nState) {
        case 6:
            if (func_020357f4(pActor->nId, SLOT_AID) > 0 && func_ov022_0209029c(&pActor->reactionCtx, SLOT_AID) != 0) {
                pActor->nCommandKind = COMMAND_SLOT;
                pActor->nCommandArg = SLOT_AID;
                pActor->nButtons |= BUTTON_BIT0;
                pSlot->nCooldown = COOLDOWN_MAX;
            }
            break;
        case 7:
            pEntry = func_0203583c(pActor->nId, KEY_A);
            if (pEntry != 0 && pEntry->nCount > 0) {
                pActor->nCommandKind = COMMAND_KEY;
                pActor->nCommandArg = KEY_A;
                pActor->nButtons |= BUTTON_BIT0;
                pSlot->nCooldown = COOLDOWN_MAX;
            }
            break;
        case 8:
            pEntry = func_0203583c(pActor->nId, KEY_B);
            if (pEntry != 0 && pEntry->nCount > 0) {
                pActor->nCommandKind = COMMAND_KEY;
                pActor->nCommandArg = KEY_B;
                pActor->nButtons |= BUTTON_BIT0;
                pSlot->nCooldown = COOLDOWN_MAX;
            }
            break;
        }
        pSlot->nState = STATE_IDLE;
        return;
    case 2:
        pSlot->nStall += FRAME_STEP();
        if (pSlot->nStall <= STALL_LIMIT) {
            return;
        }
        pSlot->nStall = 0;
        pSlot->nState = STATE_IDLE;
        return;
    default:
        break;
    }
    func_ov022_020aed60(pActor, pLeader);
    func_ov022_020af180(pActor, pLeader, pPoint);
    func_ov022_020af930(pActor);
    func_ov022_020afabc(pActor, pLeader);
    func_ov022_020aeef8(pActor, pLeader);
}
