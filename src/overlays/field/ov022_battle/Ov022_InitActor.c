/* Ov022_InitActor -- set an actor up: reset its motion state, bind its
 * player record, build every sub block and load its resources.
 *
 * The drift and push are cleared, the move and turn rates picked by the
 * recoil pick (0x1200/0x4cd fast, 0xc00/0x333 slow), the state and recoil
 * fields reset (reaction -1, body reach 0x900, a mode-dependent area frame
 * of 0x1800 or 0x1000, aim angle -1). The player record is the manager's
 * entry for the actor id; when there is one the local player installs its
 * callbacks (a remote player only the dispatch, and only for its own actor),
 * the base rate is 0x2000 in an active session without flag bit 36 and
 * 0x3000 otherwise, grown by slot rule 0x4c in units of 0x555, and the
 * record is pointed back at the actor with its push vector exposed. The
 * node is bound to its animation track and elements, the slot records
 * allocated and shared with it, the actor's sub blocks built in turn, the
 * two HP drains seeded from the panel thresholds, and the pre-draw hook run
 * once. Mode flag bit 2 with a nonzero tally kind raises flag bit 12.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Actor;

typedef void (*ActorFn)(struct Actor *pActor, int nArg);
typedef void (*SubFn)(void);

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[0x1e];
    u32 nRenderFlags;            /* 0x24, the render object; its +0x28 is the callback */
    u8 *pDesc;                   /* 0x28, byte 0x17: the number of slot records */
    u8 pad2c[0x24];
    struct Actor *pActor;        /* 0x50 */
    u8 pad54[4];
    struct Slot *pSlots;         /* 0x58 */
    u8 pad5c[0x20];
    void *pElements;             /* 0x7c, count byte at +0x18 */
    u8 pad80[0x64];
    u8 animBind;                 /* 0xe4 */
};

/* Ov022Slot */
struct Slot {
    u8 blk[0x58];
};

/* Ov022ActorSub: the per-player record owned by the ov107 actor manager */
struct ActorSub {
    u8 pad0000[0x54];
    int nHold;                   /* 0x054 */
    u8 pad0058[0x18];
    int nHeight;                 /* 0x070 */
    u8 pad0074[0x118];
    struct Actor *pActor;        /* 0x18c */
    u8 pad0190[0x18];
    VecFx32 vecPush;             /* 0x1a8 */
    u8 pad01b4[8];
    SubFn pfnDispatch;           /* 0x1bc */
    SubFn pfnApplyAction;        /* 0x1c0 */
    SubFn pfnDispatchIfNotBusy;  /* 0x1c4 */
    SubFn pfnGetActorByIndex;    /* 0x1c8 */
    SubFn pfnIsStateSelectable;  /* 0x1cc */
    SubFn pfnDispatch9;          /* 0x1d0 */
    SubFn pfnSetReadyBit;        /* 0x1d4 */
    u8 pad01d8[4];
    int nRate;                   /* 0x1dc */
    int nRateBase;               /* 0x1e0 */
};

/* Ov107ActorManager */
struct ActorManager {
    u8 pad0000[0x2c];
    struct ActorSub *apPlayers[4];   /* 0x2c */
};

/* Ov022HpDrain */
struct HpDrain {
    int nAccum;                  /* 0x00 */
    u16 nPeriod;                 /* 0x04 */
    u16 pad06;
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 nOwner;                   /* 0x0008 */
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[0xc];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x448];
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[8];
    VecFx32 vecDrift;            /* 0x047c */
    u8 pad0488[0x1c];
    VecFx32 vecPush;             /* 0x04a4 */
    int nMoveRate;               /* 0x04b0 */
    int nInterruptCharge;        /* 0x04b4 */
    int nWalkSpeed;               /* 0x04b8 */
    u8 pad04bc[1];
    u8 bAimedJump;               /* 0x04bd */
    u8 pad04be[2];
    VecFx32 *pPush;              /* 0x04c0 */
    int nBodyReach;              /* 0x04c4 */
    u8 pad04c8[0x1c];
    u16 nField4e4;               /* 0x04e4 */
    u8 pad04e6[6];
    struct ActorSub *pSub;       /* 0x04ec */
    u8 pad04f0[0x174];
    ActorFn pfnPreDraw;          /* 0x0664 */
    u8 pad0668[0x2c];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nSpare694 : 1;            /* bit 2 */
    u8 nFlags694Rest : 5;
    u8 pad0695[0x1f];
    int nStepRate;               /* 0x06b4 */
    int nRecoilDecay;            /* 0x06b8 */
    int nHitReaction;            /* 0x06bc */
    u8 pad06c0[0x6d0];
    u8 animReq[0x10];            /* 0x0d90 Ov022AnimRequest */
    u8 trackHdr[8];              /* 0x0da0 Ov022TrackHeader */
    u8 aSubBlocks[0x2c8];        /* 0x0da8 Ov022ActorSubBlock[2] */
    u8 slotBlk[0x11c];           /* 0x1070 */
    u8 blkFollow[0xc];           /* 0x118c */
    u8 reactBlk[0x180];          /* 0x1198 */
    u8 comboBlk[0x974];          /* 0x1318 */
    u8 blkReach[0x11c];          /* 0x1c8c */
    u8 reactionBlk[0x4e0];       /* 0x1da8 */
    u8 reactionCtx[0x70];        /* 0x2288 */
    u8 run[0x370];               /* 0x22f8 */
    int nLandingPoint;           /* 0x2668 */
    u8 mark[0x18];               /* 0x266c Ov022GroundMark */
    struct Slot *pSlots;         /* 0x2684 */
    u8 pad2688[0x2c];
    void *hShadow;               /* 0x26b4 */
    u8 pad26b8[0x402];
    short nAnimStep;            /* 0x2aba */
    int nAimAngle;               /* 0x2abc */
    u8 pad2ac0[0xf0];
    u8 nAimSlot;                 /* 0x2bb0 */
    u8 bHold;                    /* 0x2bb1 */
    u8 nAimMode;                 /* 0x2bb2 */
    u8 pad2bb3;
    int nAirTimer;               /* 0x2bb4 */
    u8 pad2bb8[0x38];
    struct HpDrain hpDrainA;     /* 0x2bf0 */
    struct HpDrain hpDrainB;     /* 0x2bf8 */
    u8 dot[0x28];                /* 0x2c00 Ov022DotRecord */
    void *pCurAnim;              /* 0x2c28 */
};

#define FLAG_BIT6 (1ULL << 6)
#define FLAG_BIT12 (1ULL << 12)
#define FLAG_BIT36 (1ULL << 36)
#define NODE_NO_ANIM 0x20
#define RATE_FAST 0x1200
#define RATE_SLOW 0xc00
#define TURN_FAST 0x4cd
#define TURN_SLOW 0x333
#define BODY_REACH 0x900
#define ANIM_STEP_20FPS 0x1800
#define ANIM_STEP_30FPS 0x1000
#define RULE_RATE 0x4c
#define RATE_UNIT 0x555
#define SUB_RATE_SLOW 0x3000
#define SUB_RATE_FAST 0x2000
#define SUB_HOLD 0x1000
#define SUB_HEIGHT 0xa00
#define SLOT_SIZE 0x58
#define SLOT_COUNT_BYTE 0x17
#define TAG_ALL 0x7fff
#define MODE_FLAG_BIT2 0x4
#define ELEMENT_ARG 0x3f

extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick */
extern const VecFx32 data_02041dc8;        /* kVecZero */
extern u8 data_0204c254[];                 /* g_ov002PanelThresholds: +0xa/+0xc the HP drain periods */
extern u8 data_0204c240;                   /* g_modeAndDayClock.nModeFlags */
extern u8 data_0204c248;                   /* Ov002TallyRules.nKind */

extern int GetFrameRateMode(void);                                                 /* 0: 30 fps, 1: 20 fps, 2: 60 fps */
extern void func_ov022_02097ff0(struct Actor *pActor);                          /* InitField4d0Block */
extern void Ov022_ApplyMissionLevelStats(struct Actor *pActor);                          /* Ov022_ApplyMissionLevelStats */
extern struct ActorManager *Ov107_GetActorManager(void);
extern int Slot_EvalPackedParam(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int Session_GetLocalPlayerIndex(void);                                                 /* Session_GetLocalPlayerIndex */
extern int Session_IsActive(void);                                                 /* Session_IsActive */
extern int FX_Mul(int a, int b);                                         /* FX_Mul */
extern void func_ov022_02096964(struct Actor *pActor);                          /* ClearVec3At_2bc4: the wall hold */
extern void Ov022_LoadMissionRecord(struct Actor *pActor);                          /* Ov022_LoadMissionRecord */
extern void BindAnimTrack(u16 *pAnimFlags, int nArg, u8 *pBind, int nZero);     /* BindAnimTrack */
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *pList, int nArg);                               /* ForEachElement */
extern void EventRecord_Init(u8 *pMark, const VecFx32 *pVec, void *pArg, int nZero);   /* EventRecord_Init */
extern void Widget_SetTagWord(u16 *pAnimFlags, int nTag);                           /* Widget_SetTagWord */
extern void SceneNode_SetFlag40(u16 *pAnimFlags, int bSet);                           /* SceneNode_SetFlag40 */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void NNS_G3dRenderObjSetInitFunc(u32 *pRenderObj, void (*pfn)(void));                   /* sets the object's +0x28 callback */
extern void Ov022_ResetActionBlockFromTable(struct Actor *pActor);                          /* Ov022_ResetActionBlockFromTable */
extern void Ov022_ResetByte8AndSetField4(u8 *pAnimReq, struct Actor *pActor);            /* Ov022_ResetByte8AndSetField4 */
extern void func_ov022_020b1be8(u8 *pHdr, int nId);                              /* InitNodeHeader */
extern void Ov022_LoadCueTables(struct Actor *pActor);                          /* Ov022_LoadCueTables */
extern void Ov022_BuildEffectSlots(struct Actor *pActor);                          /* Ov022_BuildEffectSlots */
extern void Ov022_BuildActorSlot(struct Actor *pActor);                          /* Ov022_BuildActorSlot */
extern void Ov022_ClearByte(u8 *pBlk);                                      /* Ov022_ClearByte_2634 */
extern void Ov022_ClearByte_2(u8 *pBlk);                                      /* Ov022_ClearByte_2868 */
extern void Ov022_ClearByte0AndByte0x135(u8 *pBlk);                                      /* ov022_ClearByte0AndByte0x135 */
extern void Ov022_ResetBlock94c(u8 *pBlk);                                      /* Ov022_ResetBlock94c */
extern void Ov022_ClearBytes01(u8 *pBlk);                                      /* ov022_ClearBytes01 */
extern void func_ov022_02093b10(u8 *pBlk, struct Actor *pActor);                /* InitNodeFields */
extern void Ov022_InitEntryState(u8 *pBlk);                                      /* Ov022_InitEntryState */
extern void Ov022_ClearFields(u8 *pBlk);                                      /* Ov022_ClearFields_4c2c */
extern void Ov022_LoadActorEffects(struct Actor *pActor);                          /* Ov022_LoadActorEffects */
extern void func_ov022_0209d08c(struct Actor *pActor, struct HpDrain *pDrain, int nPeriod);   /* InitPairIfFlag2: period only under mode flag bit 1 */
extern void Ov022_VeneerTo_Ov022_CopyBlock2c00(struct Actor *pActor);                    /* veneer to Ov022_CopyBlock2c00 */
extern void Ov022_OnItemGiven(void);                                          /* DispatchField18c */
extern void Ov022_ApplyActorAction(void);                                          /* Ov022_ApplyActorAction */
extern void func_ov022_0209a614(void);                                          /* DispatchField18c9 */
extern void func_ov022_0209a630(void);                                          /* SetNodeBit80000IfReady */
extern void func_ov022_02088398(void);                                          /* DispatchEntryA08a8IfNotBusy */
extern void GetEntryField20ByIndex(void);                                                /* Ov022_GetEntryField20ByIndex */
extern void func_ov022_0209fcd4(void);                                          /* IsStateSelectable */
extern void func_ov022_0209a4e0(void);                                          /* SetCallback24 */

void Ov022_InitActor(struct Actor *pActor)
{
    int bFast;
    int nId;
    struct ActorManager *pMgr;
    int nRule;
    int nRate;
    struct ActorNode *pNode;

    pActor->vecDrift.x = pActor->vecDrift.y = pActor->vecDrift.z = 0;
    pActor->vecPush.x = pActor->vecPush.y = pActor->vecPush.z = 0;
    bFast = data_ov022_020b2eb0;
    pActor->nMoveRate = bFast ? RATE_FAST : RATE_SLOW;
    pActor->nWalkSpeed = bFast ? TURN_FAST : TURN_SLOW;
    pActor->nInterruptCharge = 0;
    pActor->bStateOver = 0;
    pActor->nStepRate = 0;
    pActor->nRecoilDecay = 0;
    pActor->nHitReaction = -1;
    pActor->bAimedJump = 0;
    pActor->nFlags3 = 0;
    pActor->nLandingPoint = 0;
    pActor->nHp = 0;
    pActor->nSpare694 = 0;
    pActor->nBodyReach = BODY_REACH;
    pActor->pCurAnim = 0;
    pActor->nAnimStep = GetFrameRateMode() == 1 ? ANIM_STEP_20FPS : ANIM_STEP_30FPS;
    pActor->nAimAngle = -1;
    pActor->nField4e4 = 0xffff;
    func_ov022_02097ff0(pActor);
    Ov022_ApplyMissionLevelStats(pActor);
    pActor->nAimSlot = 0;
    pActor->bHold = 0;
    pActor->nAimMode = 0;
    pActor->nAirTimer = 0;
    nId = pActor->nId;
    pMgr = Ov107_GetActorManager();
    pActor->pSub = pMgr != 0 ? pMgr->apPlayers[nId] : 0;
    if (pActor->pSub != 0) {
        nRule = Slot_EvalPackedParam(pActor->nId, RULE_RATE);
        if (Session_GetLocalPlayerIndex() == 0) {
            pActor->pSub->pfnDispatch = Ov022_OnItemGiven;
            pActor->pSub->pfnApplyAction = Ov022_ApplyActorAction;
            pActor->pSub->pfnDispatch9 = func_ov022_0209a614;
            pActor->pSub->pfnSetReadyBit = func_ov022_0209a630;
        } else if (pActor->nOwner == Session_GetLocalPlayerIndex()) {
            pActor->pSub->pfnDispatch = Ov022_OnItemGiven;
        }
        if (Session_IsActive() != 0 && (pActor->nFlags & FLAG_BIT36) == 0) {
            nRate = SUB_RATE_FAST;
        } else {
            nRate = SUB_RATE_SLOW;
        }
        pActor->pSub->nRateBase = nRate;
        if (nRule > 0) {
            nRate += FX_Mul(nRate, nRule * RATE_UNIT);
        }
        pActor->pSub->nRate = nRate;
        pActor->pSub->nHold = SUB_HOLD;
        pActor->pSub->nHeight = SUB_HEIGHT;
        pActor->pSub->pActor = pActor;
        pActor->pSub->pfnDispatchIfNotBusy = func_ov022_02088398;
        pActor->pSub->pfnGetActorByIndex = GetEntryField20ByIndex;
        pActor->pSub->pfnIsStateSelectable = func_ov022_0209fcd4;
        pActor->pPush = &pActor->pSub->vecPush;
    }
    func_ov022_02096964(pActor);
    Ov022_LoadMissionRecord(pActor);
    pNode = pActor->pNode;
    if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
        BindAnimTrack(&pNode->nAnimFlags, 3, &pNode->animBind, 0);
    }
    pActor->nFlags |= FLAG_BIT6;
    NNS_G3dMdlSetMdlPolygonIDAll(pActor->pNode->pElements, ELEMENT_ARG);
    EventRecord_Init(pActor->mark, &data_02041dc8, pActor->hShadow, 0);
    Widget_SetTagWord(&pActor->pNode->nAnimFlags, TAG_ALL);
    SceneNode_SetFlag40(&pActor->pNode->nAnimFlags, 1);
    pActor->pSlots = NNSi_FndAllocFromDefaultExpHeap(pActor->pNode->pDesc[SLOT_COUNT_BYTE] * SLOT_SIZE);
    pActor->pNode->pSlots = pActor->pSlots;
    pActor->pNode->pActor = pActor;
    NNS_G3dRenderObjSetInitFunc(&pActor->pNode->nRenderFlags, func_ov022_0209a4e0);
    Ov022_ResetActionBlockFromTable(pActor);
    Ov022_ResetByte8AndSetField4(pActor->animReq, pActor);
    func_ov022_020b1be8(pActor->trackHdr, pActor->nId);
    Ov022_LoadCueTables(pActor);
    Ov022_BuildEffectSlots(pActor);
    Ov022_BuildActorSlot(pActor);
    Ov022_ClearByte(pActor->slotBlk);
    Ov022_ClearByte_2(pActor->blkFollow);
    Ov022_ClearByte0AndByte0x135(pActor->reactBlk);
    Ov022_ResetBlock94c(pActor->comboBlk);
    Ov022_ClearBytes01(pActor->blkReach);
    func_ov022_02093b10(pActor->reactionBlk, pActor);
    Ov022_InitEntryState(pActor->reactionCtx);
    Ov022_ClearFields(pActor->run);
    Ov022_LoadActorEffects(pActor);
    func_ov022_0209d08c(pActor, &pActor->hpDrainA, *(u16 *)(data_0204c254 + 0xa));
    func_ov022_0209d08c(pActor, &pActor->hpDrainB, *(u16 *)(data_0204c254 + 0xc));
    Ov022_VeneerTo_Ov022_CopyBlock2c00(pActor);
    pActor->pNode->nRenderFlags |= 1;
    pActor->pfnPreDraw(pActor, 0);
    if ((data_0204c240 & MODE_FLAG_BIT2) != 0 && data_0204c248 != 0) {
        pActor->nFlags |= FLAG_BIT12;
    }
}
