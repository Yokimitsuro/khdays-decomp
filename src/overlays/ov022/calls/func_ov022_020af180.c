/* Ov022_DrivePartnerTarget -- one frame of a partner's target choice: pick
 * what to go after, resolve it, and decide whether the partner engages
 * (slot state 4) or keeps its current state.
 *
 * Slot flag 2 drops once any of the 12 slot bits the actor's reaction
 * context marks is set with a positive table entry. Flag 1 with flag 2 or
 * charge kind 6, game flag 0x20e0, or a running rest keep the state and
 * clear flag 0x40. With a desc mode the leader's kind-1 pick is copied;
 * else the slot selection is built. No pick: the pick is stored and
 * resolved. A kind-1 pick: with slot flag 0x800 and the leader picking the
 * same id, the pick is skipped unless exactly one open, live, healthy node
 * remains in the sub's table; the table child overrides ('k' or 'm' kinds
 * skip, states 1 and 2 do not). Not skipped: an engaged slot re-engages when
 * the entity is not stalled, is live and not in state 4, the point is
 * within the desc's near range (or mode 0x34), and the delta is in range
 * (the pick is stored when its id is unchanged); otherwise the pick is
 * stored and resolved and the slot engages when the item is within the
 * inverse plus the outer reach plus the slot bonus, the entity is not in
 * state 4 and the delta is in range. Engaging: a sphere of 0.5 from the
 * feet (1.0 up) towards the item, shortened by 0.5 and the inverse, finds
 * the item's node; a miss in aim mode 2 raises buttons2 0x42; a hit with
 * a charge kind other than 10 looks for the other actor owning that node
 * and, within the inner reach, steers the partner to it (nudged a unit
 * away, or the feet under desc mode 0x28) 2.0 up, or engages again when
 * the shot channel is closed. Engaging without a state-9/6 run and slot
 * flag 1 raises flag bit 44 and, unless the action is blocked, leaves the
 * slot in state 10; else bit 44 drops and a model-2 partner in a state-9/6
 * run faces its item. Finally an engaged slot going to another state rests
 * for the desc's rest time.
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
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
};

/* Ov022EntryTable */
struct EntryTable {
    u8 pad00[0x80];
    u8 listEntries[4];           /* 0x80 */
};

/* Ov022ActorSub */
struct ActorSub {
    u8 pad00[4];
    struct EntryTable *pTable;   /* 0x04 */
};

/* Ov107Child: the ov107 child a pick resolves to */
struct RefNode {
    u8 pad000[0x60];
    u16 nOpen : 8;               /* 0x060 bits 0 to 7: bit 0 live, bit 1 closed */
    u16 nRest60 : 8;
    u8 pad062[0x117];
    u8 nState;                   /* 0x179 */
    u8 pad17a[0x22];
    u8 nKind;                    /* 0x19c: 'k' / 'm' */
    u8 pad19d[0xf];
    u16 nFlags1ac;               /* 0x1ac */
    u8 pad1ae[0x6a];
    short nHp;                   /* 0x218 */
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

/* HitState (what a sphere cast reports) */
struct HitState {
    u8 pad00[0x28];
    struct ActorNode *pNode;     /* 0x28 */
};

/* Hit */
struct Hit {
    u8 pad00[8];
    struct HitState *pState;     /* 0x08 */
};

/* Ov022ShotPool */
struct ShotPool {
    u8 pad00[0x18];
    u8 nBudget;                  /* 0x18 */
};

/* PlayerSlotDesc */
struct SlotDesc {
    u8 pad00[0x18];
    int nReachOuter;             /* 0x18 */
    int nReachInner;             /* 0x1c */
    int nRangeNear;              /* 0x20 */
    u8 pad24[4];
    int nFeetMode;               /* 0x28 */
    int nRestTime;               /* 0x2c */
    int nMode30;                 /* 0x30 */
    int nMode34;                 /* 0x34 */
};

/* PlayerSlot */
struct PlayerSlot {
    int nState;                  /* 0x00 */
    u32 nFlags;                  /* 0x04 */
    u8 pad08[8];
    int nRest;                   /* 0x10 */
    u8 pad14[0x20];
    int nReachBonus;             /* 0x34 */
    u8 pad38[0xc];
    struct SlotDesc *pDesc;      /* 0x44 */
};

/* Ov022Pick: the three-byte target pick */
struct Pick {
    u8 nKind;                    /* 0x00 */
    u8 nId;                      /* 0x01 */
    u8 nIndex;                   /* 0x02 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[2];
    int nModelId;                /* 0x000c */
    u8 pad0010[0xa];
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[4];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x454];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[0x12];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x54];
    struct ActorSub *pSub;       /* 0x04ec */
    struct Pick pick;            /* 0x04f0 */
    u8 pad04f3[9];
    struct RefNode *pRefEntity;  /* 0x04fc */
    struct RefItem *pRefItem;    /* 0x0500 */
    u8 pad0504[0x1d84];
    short aReaction[0x38];       /* 0x2288 Ov022ReactionCtx */
    u32 run[0xd3];               /* 0x22f8 Ov022ActionOwner */
    struct ShotPool *pShotChannels;   /* 0x2644 */
    u8 pad2648[0x128];
    s8 nKnockdownKind;           /* 0x2770 charge.nKnockdownKind */
    u8 pad2771[0x441];
    s8 nAimMode;                 /* 0x2bb2 */
};

#define SLOT_FLAG_HOLD 0x1
#define SLOT_FLAG_WAIT 0x2
#define SLOT_FLAG_SETTLED 0x40
#define SLOT_FLAG_SHARED 0x800
#define SLOT_ENGAGED 4
#define SLOT_IDLE 1
#define SLOT_BLOCKED 10
#define CHARGE_KIND_HELD 6
#define CHARGE_KIND_CARRIED 10
#define GAME_FLAG_NO_TARGET 0x20e0
#define PICK_KIND_NODE 1
#define NODE_OPEN_LIVE 0x1
#define NODE_OPEN_CLOSED 0x2
#define NODE_STATE_GONE 4
#define NODE_KIND_K 0x6b
#define NODE_KIND_M 0x6d
#define ENTITY_STALLED 0x2
#define FLAG_BIT44 (1ULL << 44)
#define FOOT_RAISE 0x1000
#define CAST_SHORTEN 0x800
#define CAST_RADIUS 0x800
#define BUTTON2_AIM 0x42
#define BUTTON2_FACE 0x40
#define STEER_RAISE 0x2000
#define AIM_MODE_ITEM 2
#define MODEL_PARTNER 2

extern struct PlayerSlot *func_020358a4(int nSlot);                             /* GetPlayerSlotTableEntry */
extern int func_020357f4(int nId, int nIndex);                                  /* Load2DArrayU8_c714 */
extern int func_ov022_0209029c(short *pCtx, int nBit);                          /* IsSlotBitSetOrAll */
extern int func_02023588(int nFlag);                                            /* GameState_IsFlagSet */
extern int func_ov022_02086688(struct Pick *pPick, int nId);                    /* Ov022_BuildSlotSelection */
extern void func_ov022_020acfa4(struct Actor *pActor);                          /* Ov022_ResolveTargetPick */
extern struct RefNode **func_01fffd70(void *pList);                             /* List_First */
extern struct RefNode **func_01fffd8c(void *pList);                             /* List_Next */
extern struct RefNode *func_ov107_020c2b50(struct EntryTable *pTable, int nId); /* Ov107_FindChildById */
extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);                             /* VEC_Distance */
extern int func_ov022_020afd38(struct Actor *pActor, int nY);                   /* IsDeltaInRange */
extern int func_ov022_020afd78(struct Actor *pActor);                           /* GetInverseByHeaderKind */
extern int func_01fffe14(void);                                                 /* QueryActiveStateOrDelegate */
extern int func_ov022_02088474(int nIndex);                                     /* Ov022_GetEntryField66 (slot index) */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_01ff8d18(VecFx32 *pIn, VecFx32 *pOut);                          /* VEC_Normalize */
extern void func_01ffa724(int nScale, VecFx32 *pIn, VecFx32 *pOut);             /* ScaleVec3Fx12 */
extern struct Hit *func_0202c2ac(u16 nSlot, VecFx32 *pFrom, VecFx32 *pDir, int nRadius, struct ActorNode *pNode);   /* sphere cast */
extern int func_ov022_020882f8(void);                                           /* GetActiveField34 (actor count) */
extern struct Actor *func_01fffde0(int nIndex);                                 /* Ov022_GetEntryField20ByIndex */
extern int VEC_Mag(VecFx32 *pVec);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_ov022_020ae8a4(struct Actor *pSelf, struct Actor *pLeader, VecFx32 *pPoint, int bNoClimb);   /* Ov022_SteerPartnerToPoint */
extern int func_ov022_02095524(u32 *pRun);                                      /* ov022_IsState9Or6WithFlag200 */
extern int func_ov022_020956e8(u32 *pRun);                                      /* Ov022_IsActionBlocked */
extern short FX_Atan2(int y, int x);

#define CLAMP(v, lo, hi) ((v) > (hi) ? (hi) : ((v) < (lo) ? (lo) : (v)))

void func_ov022_020af180(struct Actor *pActor, struct Actor *pLeader, VecFx32 *pPoint)
{
    VecFx32 vecDir;
    VecFx32 vecFoot;
    VecFx32 vecOther;
    VecFx32 vecDelta;
    VecFx32 vecFace;
    struct Pick pick;
    struct PlayerSlot *pSlot;
    struct SlotDesc *pDesc;
    int nState;
    int bDone;
    int bSkip;
    int bClear;
    int i;
    int nDist;
    int nInv;
    int nLen;
    int bInRange;
    int nActive;
    int nSlotIdx;
    struct EntryTable *pTable;
    int nCount;
    struct RefNode **ppNode;
    struct RefNode *pNode;
    struct RefNode *pEnt;
    struct Hit *pHit;
    struct Actor *pOther;

    pSlot = func_020358a4((u8)(pActor->nId - 1));
    bDone = 0;
    nState = pSlot->nState;
    if (nState == SLOT_ENGAGED) {
        nState = SLOT_IDLE;
    }
    if ((pSlot->nFlags & SLOT_FLAG_WAIT) != 0) {
        for (i = 0; i < 12; i++) {
            if (func_020357f4(pActor->nId, i) > 0 && func_ov022_0209029c(pActor->aReaction, i)) {
                pSlot->nFlags &= ~SLOT_FLAG_WAIT;
            }
        }
    }
    if (((pSlot->nFlags & SLOT_FLAG_HOLD) != 0 && ((pSlot->nFlags & SLOT_FLAG_WAIT) != 0 || pActor->nKnockdownKind == CHARGE_KIND_HELD))
        || func_02023588(GAME_FLAG_NO_TARGET) != 0 || pSlot->nRest > 0) {
        pSlot->nState = nState;
        pSlot->nFlags &= ~SLOT_FLAG_SETTLED;
        return;
    }
    if ((pSlot->pDesc->nMode30 != 0 || pSlot->pDesc->nMode34 != 0) && pLeader->pick.nKind == PICK_KIND_NODE && pLeader->pRefItem != 0) {
        pick.nKind = pLeader->pick.nKind;
        pick.nId = pLeader->pick.nId;
        bDone = 1;
        pick.nIndex = pLeader->pick.nIndex;
    }
    if (!bDone && func_ov022_02086688(&pick, pActor->nId) != 0) {
        bDone = 1;
    }
    if (bDone) {
        if (pick.nKind == PICK_KIND_NODE) {
            bSkip = 0;
            pTable = 0;
            if (pActor->pSub != 0) {
                pTable = pActor->pSub->pTable;
            }
            if ((pSlot->nFlags & SLOT_FLAG_SHARED) != 0 && pLeader->pick.nKind == PICK_KIND_NODE && pLeader->pRefItem != 0
                && pick.nId == pLeader->pick.nId) {
                bSkip = 1;
                if (pTable != 0) {
                    nCount = 0;
                    ppNode = func_01fffd70(pTable->listEntries);
                    pNode = ppNode == 0 ? 0 : *ppNode;
                    while (pNode != 0) {
                        if ((pNode->nOpen & NODE_OPEN_CLOSED) == 0 && (pNode->nOpen & NODE_OPEN_LIVE) != 0 && pNode->nHp > 0) {
                            nCount++;
                        }
                        ppNode = func_01fffd8c(pTable->listEntries);
                        pNode = ppNode == 0 ? 0 : *ppNode;
                    }
                    if (nCount == 1) {
                        bSkip = 0;
                    }
                }
            }
            if (pTable != 0) {
                pNode = func_ov107_020c2b50(pTable, pick.nId);
                if (pNode != 0) {
                    if (pNode->nKind == NODE_KIND_K) {
                        bSkip = 1;
                    }
                    if (!(pNode->nState != 1 && pNode->nState != 2)) {
                        bSkip = 0;
                    }
                    if (pNode->nKind == NODE_KIND_M) {
                        bSkip = 1;
                    }
                }
            }
            if (!bSkip) {
                if (pSlot->nState == SLOT_ENGAGED && (pSlot->pDesc->nMode30 != 0 || pSlot->pDesc->nMode34 != 0)) {
                    nDist = func_01ff8e94(pPoint, &pActor->vecAim);
                    bInRange = 1;
                    if (pActor->pRefItem != 0) {
                        bInRange = func_ov022_020afd38(pActor, pActor->pRefItem->pPlace->vecPos.y);
                    }
                    pEnt = pActor->pRefEntity;
                    if ((pEnt->nFlags1ac & ENTITY_STALLED) == 0) {
                        if ((pEnt->nOpen & NODE_OPEN_LIVE) != 0 && pEnt->nState != NODE_STATE_GONE
                            && (pSlot->pDesc->nRangeNear > nDist || pSlot->pDesc->nMode34 != 0) && bInRange) {
                            if (pick.nId == pActor->pick.nId) {
                                pActor->pick.nKind = pick.nKind;
                                pActor->pick.nId = pick.nId;
                                pActor->pick.nIndex = pick.nIndex;
                                func_ov022_020acfa4(pActor);
                            }
                            nState = SLOT_ENGAGED;
                        }
                    }
                } else {
                    pActor->pick.nKind = pick.nKind;
                    pActor->pick.nId = pick.nId;
                    pActor->pick.nIndex = pick.nIndex;
                    func_ov022_020acfa4(pActor);
                    nInv = func_ov022_020afd78(pActor);
                    nDist = func_01ff8e94(&pActor->pRefItem->pPlace->vecPos, pPoint);
                    if (nInv + (pSlot->pDesc->nReachOuter + pSlot->nReachBonus) > nDist && pActor->pRefEntity->nState != NODE_STATE_GONE
                        && func_ov022_020afd38(pActor, pActor->pRefItem->pPlace->vecPos.y) != 0) {
                        nState = SLOT_ENGAGED;
                    }
                }
            }
            if (nState == SLOT_ENGAGED) {
                nActive = func_01fffe14();
                nSlotIdx = func_ov022_02088474(nActive);
                if (nActive >= 0 && nSlotIdx >= 0) {
                    vecFoot = pActor->vecAim;
                    vecFoot.y += FOOT_RAISE;
                    VEC_Subtract(&pActor->pRefItem->pPlace->vecPos, &vecFoot, &vecDir);
                    nLen = func_01ff8d18(&vecDir, &vecDir);
                    nLen = CLAMP(nLen - CAST_SHORTEN - func_ov022_020afd78(pActor), 0, nLen);
                    func_01ffa724(nLen, &vecDir, &vecDir);
                    pHit = func_0202c2ac((u16)nSlotIdx, &vecFoot, &vecDir, CAST_RADIUS, pActor->pNode);
                    if (pHit != 0) {
                        nState = pSlot->nState;
                        if (nState == SLOT_ENGAGED) {
                            nState = SLOT_IDLE;
                        }
                        if (pActor->nKnockdownKind != CHARGE_KIND_CARRIED && pHit->pState != 0) {
                            for (i = 0; i < func_ov022_020882f8(); i++) {
                                pOther = func_01fffde0(i);
                                if (i != pActor->nId && pOther->pNode == pHit->pState->pNode) {
                                    vecOther = pOther->vecAim;
                                    vecOther.y += FOOT_RAISE;
                                    VEC_Subtract(&vecOther, &vecFoot, &vecDelta);
                                    pDesc = pSlot->pDesc;
                                    if (pDesc->nReachInner >= VEC_Mag(&vecDelta)) {
                                        if (pActor->pShotChannels == 0 || pActor->pShotChannels->nBudget != 0) {
                                            if (pDesc->nFeetMode != 0) {
                                                vecOther = vecFoot;
                                            } else {
                                                func_01ff8d18(&vecDelta, &vecDelta);
                                                VEC_Add(&vecDelta, &vecOther, &vecOther);
                                            }
                                            vecOther.y += STEER_RAISE;
                                            func_ov022_020ae8a4(pActor, pLeader, &vecOther, 1);
                                        } else {
                                            nState = SLOT_ENGAGED;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    } else {
                        if (pActor->nAimMode == AIM_MODE_ITEM) {
                            pActor->nButtons2 |= BUTTON2_AIM;
                        }
                    }
                }
            }
            if (nState == SLOT_ENGAGED) {
                bClear = 0;
                if (nState == SLOT_ENGAGED && func_ov022_02095524(pActor->run) == 0 && (pSlot->nFlags & SLOT_FLAG_HOLD) == 0) {
                    pActor->nFlags |= FLAG_BIT44;
                    bClear = 1;
                }
                if (bClear && func_ov022_020956e8(pActor->run) == 0) {
                    pSlot->nState = SLOT_BLOCKED;
                    return;
                }
                pActor->nFlags &= ~FLAG_BIT44;
                if (pActor->nModelId == MODEL_PARTNER) {
                    if (func_ov022_02095524(pActor->run) != 0 && pActor->pRefItem != 0) {
                        VEC_Subtract(&pActor->pRefItem->pPlace->vecPos, &pActor->vecAim, &vecFace);
                        vecFace.y = 0;
                        if (func_01ff8d18(&vecFace, &vecFace) != 0) {
                            pActor->nAngleBias = FX_Atan2(-vecFace.x, -vecFace.z);
                            pActor->nButtons2 |= BUTTON2_FACE;
                        }
                    }
                }
            }
        }
    } else {
        pActor->pick.nKind = pick.nKind;
        pActor->pick.nId = pick.nId;
        pActor->pick.nIndex = pick.nIndex;
        func_ov022_020acfa4(pActor);
    }
    if (pSlot->nState == SLOT_ENGAGED) {
        if (nState != SLOT_ENGAGED && nState != SLOT_IDLE) {
            nState = SLOT_IDLE;
            pSlot->nRest = pSlot->pDesc->nRestTime;
            pSlot->nFlags &= ~SLOT_FLAG_SETTLED;
        }
    } else {
        pSlot->nFlags &= ~SLOT_FLAG_SETTLED;
    }
    pSlot->nState = nState;
}
