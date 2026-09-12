/* Ov022_DecidePartnerAid -- let a partner's slot decide whether to aid the
 * target actor.
 *
 * The partner's slot is the one before its id. Unless the slot is muted
 * (flag bit 4) the partner's key table is checked for keys 4 and 7 with a
 * positive count, and reaction 0xe counts when the partner's rule allows it
 * and the reaction bit is set. The decision runs when the slot is armed
 * (flag bit 9), its cooldown has run out, neither actor has an action
 * blocked, progress flag 0x20e0 is clear and at least one aid is
 * available: an aid state (6..8) drops back to following; otherwise, with
 * the target's HP check passing, a roll of 100 is taken while flag bit 44
 * is raised -- past 50 when the target is under a tenth of its max HP,
 * past 33 when its action is blocked or its ref kind is not 1 -- and a
 * winning roll picks state 6 (reaction), 7 (key 4) or 8 (key 7). The
 * cooldown is then reset to 0x2000. When the decision does not run an aid
 * state drops back to following as well.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define SLOT_MUTED 0x10
#define SLOT_ARMED 0x200
#define SLOT_FOLLOWING 1
#define SLOT_AID_REACT 6
#define SLOT_AID_KEY4 7
#define SLOT_AID_KEY7 8
#define AID_COOLDOWN 0x2000
#define KEY_4 4
#define KEY_7 7
#define REACTION_E 0xe
#define PROGRESS_FLAG 0x20e0
#define FLAG_BIT44 (1ULL << 44)
#define ROLL_RANGE 100
#define ROLL_LOW_HP 0x32
#define ROLL_NORMAL 0x21
#define LOW_HP_SHARE 0x19a
#define REF_KIND_1 1

/* one key table entry */
struct KeyEntry {
    u16 nKey;                    /* 0x00 */
    short nCount;                /* 0x02 */
};

/* PlayerSlot */
struct PlayerSlot {
    int nState;                  /* 0x00 */
    u32 nFlags;                  /* 0x04 */
    int nField08;                /* 0x08 */
    int nCooldown;               /* 0x0c */
};

/* Ov002MissionMember: per-id table of 0x104-byte records */
struct Record {
    u8 pad0000[0xe];
    u16 nHpMax;                  /* 0x000e body.nHpMax */
    u8 pad0010[0xf4];
};

struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008;
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[0x4dc];
    u8 nRefKind;                 /* 0x04f0 */
    u8 pad04f1[0x1d97];
    short reactionCtx[0x38];     /* 0x2288 Ov022ReactionCtx (0x70) */
    u32 run[0xdc];               /* 0x22f8 Ov022ActionOwner (0x370) */
};

extern struct Record data_0204c678[];      /* kOv022KindRecords */

extern struct PlayerSlot *func_020358a4(int nSlot);                             /* GetPlayerSlotTableEntry */
extern struct KeyEntry *func_0203583c(int nId, int nKey);                       /* Table_FindKey */
extern int func_020357f4(int nId, int nSlot);                                   /* Load2DArrayU8_c714 */
extern int func_ov022_0209029c(short *pCtx, int nBit);                          /* IsSlotBitSetOrAll */
extern int func_ov022_02095524(u32 *pRun);                                      /* ov022_IsState9Or6WithFlag200 */
extern int func_02023588(int nFlag);                                            /* GameState_IsFlagSet */
extern int func_ov022_020ad7b0(struct Actor *pActor);                           /* IsField12LeShifted16 */
extern u32 func_020307f4(int nRange);                                           /* Session_RandNextScaled */
extern int func_ov022_020956e8(u32 *pRun);                                      /* Ov022_IsActionBlocked */

static inline int FxMulU(u32 nValue, u32 nScale)
{
    return (int)(((u64)nValue * nScale + 0x800) >> 12);
}

void func_ov022_020afabc(struct Actor *pSelf, struct Actor *pTarget)
{
    struct PlayerSlot *pSlot;
    struct KeyEntry *pKey;
    int bReact;
    int bKey4;
    int bKey7;
    struct Record *pRec;
    u32 nRoll;
    int bAid;

    pSlot = func_020358a4((u8)(pSelf->nId - 1));
    bReact = 0;
    bKey4 = 0;
    bKey7 = 0;
    pRec = &data_0204c678[pTarget->nId];
    if ((pSlot->nFlags & SLOT_MUTED) == 0) {
        pKey = func_0203583c(pSelf->nId, KEY_4);
        if (pKey != 0 && pKey->nCount > 0) {
            bKey4 = 1;
        }
        pKey = func_0203583c(pSelf->nId, KEY_7);
        if (pKey != 0 && pKey->nCount > 0) {
            bKey7 = 1;
        }
    }
    if (func_020357f4(pSelf->nId, REACTION_E) > 0 && func_ov022_0209029c(pSelf->reactionCtx, REACTION_E)) {
        bReact = 1;
    }
    if (!((pSlot->nFlags & SLOT_ARMED) != 0 && pSlot->nCooldown <= 0
          && func_ov022_02095524(pSelf->run) == 0 && func_ov022_02095524(pTarget->run) == 0
          && func_02023588(PROGRESS_FLAG) == 0 && (bKey4 || bKey7 || bReact))) {
        if ((u32)(pSlot->nState - SLOT_AID_REACT) <= SLOT_AID_KEY7 - SLOT_AID_REACT) {
            pSlot->nState = SLOT_FOLLOWING;
        }
    } else {
        if ((u32)(pSlot->nState - SLOT_AID_REACT) <= SLOT_AID_KEY7 - SLOT_AID_REACT) {
            pSlot->nState = SLOT_FOLLOWING;
        } else if (func_ov022_020ad7b0(pTarget)) {
            nRoll = func_020307f4(ROLL_RANGE);
            pTarget->nFlags |= FLAG_BIT44;
            bAid = 0;
            if (FxMulU(pRec->nHpMax, LOW_HP_SHARE) > pTarget->nHp) {
                if (nRoll > ROLL_LOW_HP) {
                    bAid = 1;
                }
            } else if (func_ov022_020956e8(pTarget->run) == 0) {
                if (pTarget->nRefKind != REF_KIND_1) {
                    if (nRoll > ROLL_NORMAL) {
                        bAid = 1;
                    }
                }
            } else if (nRoll > ROLL_NORMAL) {
                bAid = 1;
            }
            pTarget->nFlags &= ~FLAG_BIT44;
            if (bAid) {
                if (bReact) {
                    pSlot->nState = SLOT_AID_REACT;
                } else if (bKey4) {
                    pSlot->nState = SLOT_AID_KEY4;
                } else if (bKey7) {
                    pSlot->nState = SLOT_AID_KEY7;
                }
            }
        }
        pSlot->nCooldown = AID_COOLDOWN;
    }
}
