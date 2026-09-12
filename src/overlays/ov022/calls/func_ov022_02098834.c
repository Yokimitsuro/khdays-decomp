/* Ov022_EnterActorState -- state entry for the player actor: sets the
 * animation, flags, timers and speeds a state starts with and returns the
 * step function that will run it (0 keeps the caller's default).
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

struct Actor;
struct ActorSub;

typedef void (*ActorHookFn)(struct Actor *pActor, int nArg);
typedef int (*ActorEnterFn)(struct Actor *pActor, int nArg);
typedef void (*SubHookFn)(struct ActorSub *pSub, int nArg);

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[0x7a];
    u16 nAngle;                  /* 0x80 */
};

/* Ov022Flags60Bits */
struct SubFlags60 {
    u16 nMode : 8;
    u16 nBits : 8;
};

/* Ov022ActorSub */
struct ActorSub {
    u8 pad00[0x14];
    SubHookFn pfnHook14;         /* 0x14 */
    u8 pad18[0x3c];
    int nHold;                   /* 0x54 */
    u8 pad58[8];
    struct SubFlags60 flags60;   /* 0x60 */
    u8 pad62[0xe];
    int nHeight;                 /* 0x70 */
};

/* Ov022ComboRecord */
struct ComboRecord {
    u8 pad00[3];
    u8 nAnimSlot;                /* 0x03 */
    u8 pad04[4];
    int nEntryFlags;             /* 0x08 */
};

/* Ov022ComboLock */
struct ComboLock {
    u8 pad00[0x14];
    struct ComboRecord *pRecord; /* 0x14 */
};

/* Ov022ComboState */
struct ComboState {
    u8 pad000[0x20];
    short nChaseReach;           /* 0x020 */
    short nChaseScale;           /* 0x022 */
    u8 pad024[0x44c];
    struct ComboLock *pLock;     /* 0x470 */
    u8 pad474[8];
    int nPhase;                  /* 0x47c */
};

/* Ov022AnimRequest */
struct AnimRequest {
    u8 pad00[0x10];
};

/* Ov022DodgeParams (0x118e) */
struct DodgeParams {
    u16 nCharge;                 /* 0x00 */
    u8 pad02[2];
    short nScale;                /* 0x04 */
    short nHold;                 /* 0x06 */
};

/* Ov022GlideParams (0x1c78) */
struct GlideParams {
    short nGlideAccel;           /* 0x00 */
    short nJumpRate;             /* 0x02 */
    short nGlideSink;            /* 0x04 */
    u16 nMoveRate;               /* 0x06 */
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
    u8 pad01[0x17];
    int nHeld;                   /* 0x18 */
};

/* Ov022AimState */
struct AimState {
    u8 nJumpCount;               /* 0x00 */
    u8 bHold;                    /* 0x01 */
    s8 nAimMode;                 /* 0x02 */
    u8 pad03[1];
    int nAirTimer;               /* 0x04 */
    int nAirStepRate;            /* 0x08 */
    u8 nWalkPhase;               /* 0x0c */
    u8 pad0d[3];
    int nLandTimer;              /* 0x10 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 nOwner;                   /* 0x0008 */
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x16];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[8];
    u16 nAnimSpeed;              /* 0x0064 */
    u8 pad0066[0x3fe];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[8];
    VecFx32 vecDrift;            /* 0x047c */
    u8 pad0488[4];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x18];
    int nMoveRate;               /* 0x04b0 */
    int nInterruptCharge;        /* 0x04b4 */
    u8 pad04b8[4];
    s8 nDownedVoice;             /* 0x04bc */
    u8 bAimedJump;               /* 0x04bd */
    u8 pad04be[0xe];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0xc];
    s8 nLatchedKind;             /* 0x04dc */
    u8 pad04dd[1];
    u16 nLatchedArg;             /* 0x04de */
    u16 nLatchedArg2;            /* 0x04e0 */
    u8 pad04e2[2];
    u16 nHeldArg;                /* 0x04e4 */
    u8 pad04e6[6];
    struct ActorSub *pSub;       /* 0x04ec */
    u8 pad04f0[8];
    void *pEquip;                /* 0x04f8 */
    u8 pad04fc[0x15c];
    VecFx32 vecGround;           /* 0x0658 */
    ActorHookFn pfnPreDraw;      /* 0x0664 */
    u8 pad0668[0x20];
    ActorEnterFn pfnEnterHook;   /* 0x0688 */
    u8 pad068c[0xc];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0x10];
    int nStepRate;               /* 0x06b4 */
    u8 pad06b8[4];
    int nAnimId;                 /* 0x06bc */
    u8 pad06c0[0xf4];
    u8 nAnchorPhase;             /* 0x07b4 */
    u8 pad07b5[0x15b];
    struct ComboState combo;     /* 0x0910 */
    struct AnimRequest animReq;  /* 0x0d90 */
    u8 pad0da0[0x3e6];
    short nRunScale;             /* 0x1186 */
    u8 pad1188[6];
    struct DodgeParams dodge;    /* 0x118e */
    u8 pad1196[2];
    u8 reactBlk;                 /* 0x1198 */
    u8 pad1199[0x177];
    u16 nAimJumpCharge;          /* 0x1310 */
    u8 pad1312[6];
    u8 comboBlk;                 /* 0x1318 */
    u8 pad1319[0x957];
    int nHoldTime;               /* 0x1c70 */
    u8 pad1c74[4];
    struct GlideParams glide;    /* 0x1c78 */
    u8 pad1c80[0x118];
    int nGlideHoldTime;          /* 0x1d98 */
    u8 pad1d9c[0xc];
    u8 reactionBlk;              /* 0x1da8 */
    u8 pad1da9[0x4df];
    struct ReactionCtx reactionCtx;  /* 0x2288 */
    struct ActionOwner run;      /* 0x22f8 */
    u8 pad22fc[0x364];
    int nRushSpeed;              /* 0x2660 */
    int nRushTime;               /* 0x2664 */
    u8 pad2668[0x108];
    struct Charge charge;        /* 0x2770 */
    u8 pad278c[0x330];
    int nAimAngle;               /* 0x2abc */
    u8 pad2ac0[0xf0];
    struct AimState aim;         /* 0x2bb0 */
};

/* event handed to the equip command on state 0x13 */
struct EquipEvent {
    u8 nId;                      /* 0x00 */
};

#define FLAG_BIT1 (1ULL << 1)
#define FLAG_BIT2 (1ULL << 2)
#define FLAG_BIT4 (1ULL << 4)
#define FLAG_BIT6 (1ULL << 6)
#define FLAG_BIT7 (1ULL << 7)
#define FLAG_BIT8 (1ULL << 8)
#define FLAG_BIT13 (1ULL << 13)
#define FLAG_BIT16 (1ULL << 16)
#define FLAG_BIT17 (1ULL << 17)
#define FLAG_BIT23 (1ULL << 23)
#define FLAG_BIT24 (1ULL << 24)
#define FLAG_BIT28 (1ULL << 28)
#define FLAG_BIT29 (1ULL << 29)
#define FLAG_BIT31 (1ULL << 31)
#define FLAG_BIT32 (1ULL << 32)
#define FLAG_BIT35 (1ULL << 35)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT40 (1ULL << 40)
#define FLAG_BIT41 (1ULL << 41)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG_BIT48 (1ULL << 48)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT4 (1ULL << 4)
#define FLAG2_BIT6 (1ULL << 6)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT8 (1ULL << 8)
#define FLAG2_BIT9 (1ULL << 9)
#define FLAG2_BIT11 (1ULL << 11)
#define FLAG2_BIT15 (1ULL << 15)
#define FLAG2_BIT16 (1ULL << 16)
#define FLAG2_BIT28 (1ULL << 28)
#define FLAG2_BIT29 (1ULL << 29)
#define FLAG2_BIT30 (1ULL << 30)
#define FLAG2_BIT31 (1ULL << 31)
#define FLAG2_BIT32 (1ULL << 32)
#define FLAG2_BIT33 (1ULL << 33)
#define FLAG2_BIT36 (1ULL << 36)
#define FLAG2_BIT39 (1ULL << 39)
#define FLAG2_BIT54 (1ULL << 54)
#define FLAG2_BIT55 (1ULL << 55)
#define FLAG2_BIT56 (1ULL << 56)
#define FLAG3_BIT4 (1ULL << 4)
#define FLAG3_BIT7 (1ULL << 7)
#define FLAG3_BIT8 (1ULL << 8)
#define FLAG3_BIT16 (1ULL << 16)
#define FLAG3_BIT29 (1ULL << 29)
#define FLAG3_BIT32 (1ULL << 32)
#define FLAG3_BIT36 (1ULL << 36)
#define FLAG3_BIT39 (1ULL << 39)
#define NODE_LOCKED 0x20
#define NODE_ANIM_HOLD 0x20
#define INPUT_BIT2 0x4
#define INPUT_BIT6 0x40
#define GLOBAL_BIT2 0x4
#define ANGLE_HALF 0x8000
#define ONE 0x1000

#define STATE_IDLE_ENTRY 0xe
#define STATE_LAST 0x1f

extern u8 data_ov022_020b2eb0;              /* global mode byte */
extern u8 data_0204c240;                    /* global flags byte */
extern short data_0203d210[];               /* sin/cos table */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern struct PlayerSlot *func_020358a4(int nSlot);                             /* GetPlayerSlotTableEntry */
extern int FX_Atan2(int y, int x);
extern int VEC_Mag(VecFx32 *pVec);
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);                        /* VEC_Normalize */
extern void func_01ffa724(int nScale, VecFx32 *pSrc, VecFx32 *pDst);            /* ScaleVec3Fx12 */
extern void func_0202af1c(u16 *pAnimFlags);                                     /* SceneNode_Enable */
extern void SNDi_ProcessEntryAlt(int nVoice);
extern void func_ov002_0204cb70(int nOwner, int nMode, int nArg);
extern void func_ov002_0206cd60(int nA, int nB);                                /* Ov002_Set_cd60 */
extern int func_ov002_02076e08(void *pEquip, struct EquipEvent *pEvent);        /* Ov002_DispatchNodeEventGated */
extern int func_ov022_02083f0c(void);                                           /* GetGlobalFieldCOr18 */
extern int func_ov022_0208868c(void);                                           /* Ov022_IsInputAllowedForActiveSlot */
extern void func_ov022_02090360(struct ReactionCtx *pCtx);                      /* ov022_SetBit5OfHalf0IfByte2 */
extern int func_ov022_02092dc8(u8 *pBlk, int nArg);                             /* CheckState135Range */
extern void func_ov022_02093034(u8 *pBlk);                                      /* ov022_CopyWord968To958 */
extern void func_ov022_02093c34(u8 *pBlk);                                      /* ov022_ClearByte1IfEquals4 */
extern void func_ov022_02093c48(u8 *pBlk, int nArg, int nKind, int nArg2);      /* InitStateAndDispatch */
extern int func_ov022_02095450(struct ActionOwner *pRun);                       /* IsStateActiveOrFlagged */
extern void func_ov022_020954e4(struct ActionOwner *pRun);                      /* ov022_SetBit8ClearBit7 */
extern void func_ov022_02097038(struct Actor *pActor, int nArg);                /* SetField7b0AndDispatch */
extern void func_ov022_02097a90(struct Actor *pActor);                          /* Ov022_StartGroundEffect */
extern void func_ov022_02097de4(struct Actor *pActor);                          /* ClearFieldsIfBit2 */
extern void func_ov022_0209b1e8(struct Actor *pActor);                          /* Ov022_EnterState0E */
extern void func_ov022_0209d1c0(struct Actor *pActor);                          /* Ov022_CopyBlock2c00 */
extern void func_ov022_0209d5a4(struct Actor *pActor);                          /* Ov022_TurnAwayFromDrift */
extern int func_ov022_0209d7a4(struct Actor *pActor);                           /* IsField7b0LEField117c */
extern void func_ov022_020acebc(struct Actor *pActor, int nScale);              /* ConfigFlag40AndScale */
extern void func_ov022_020acf14(struct Actor *pActor, int nFlags);              /* SetEntryFlagsAndBroadcast */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);                      /* GetSubBufferByState4f0 */
extern int func_ov022_020ad1b4(struct Actor *pActor);                           /* GetField4f4UnlessState5 */
extern void func_ov022_020ad208(struct Actor *pActor, int nRecord, VecFx32 *pAt, int nScale, int nAngle, int nKind);   /* Ov022_MarshalNetworkRecord */
extern void func_ov022_020b08f4(struct ComboState *pCombo, int bReverse, int nGroup);   /* Ov022_StartGroupWalk */
extern int func_ov022_020b1ba0(struct AnimRequest *pReq);                       /* Ov022_GetByteCOrA */

/* the per-state step functions handed back to Ov022_ActorSetState */
extern int func_ov022_020a37d0(struct Actor *pActor);
extern int func_ov022_020a49e0(struct Actor *pActor);
extern int func_ov022_020a64e0(struct Actor *pActor);
extern int func_ov022_020a70cc(struct Actor *pActor);
extern int func_ov022_020a72f8(struct Actor *pActor);
extern int func_ov022_020a74d0(struct Actor *pActor);
extern int func_ov022_020a7a38(struct Actor *pActor);
extern int func_ov022_020a7d80(struct Actor *pActor);
extern int func_ov022_020a8020(struct Actor *pActor);
extern int func_ov022_020a8354(struct Actor *pActor);
extern int func_ov022_020a8764(struct Actor *pActor);
extern int func_ov022_020a8b54(struct Actor *pActor);
extern int func_ov022_020a8ec0(struct Actor *pActor);
extern int func_ov022_020a947c(struct Actor *pActor);
extern int func_ov022_020a98b4(struct Actor *pActor);
extern int func_ov022_020aac98(struct Actor *pActor);
extern int func_ov022_020aaea0(struct Actor *pActor);
extern int func_ov022_020ab378(struct Actor *pActor);
extern int func_ov022_020ab57c(struct Actor *pActor);
extern int func_ov022_020ab764(struct Actor *pActor);
extern int func_ov022_020ab810(struct Actor *pActor);
extern int func_ov022_020ab8d0(struct Actor *pActor);
extern int func_ov022_020abb6c(struct Actor *pActor);
extern int func_ov022_020abe80(struct Actor *pActor);
extern int func_ov022_020ac21c(struct Actor *pActor);
extern int func_ov022_020ac480(struct Actor *pActor);
extern int func_ov022_020ac6c8(struct Actor *pActor);

struct PlayerSlot {
    u8 pad00[8];
    int nStall;                  /* 0x08 */
};

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

static inline void FaceAwayFrom(struct Actor *pActor, VecFx32 *pVec)
{
    struct ActorNode *pNode;
    u16 nAngle;

    nAngle = (u16)FX_Atan2(-pVec->x, -pVec->z);
    pNode = pActor->pNode;
    if ((pNode->nFlags & NODE_LOCKED) == 0) {
        pNode->nAngle = nAngle + ANGLE_HALF;
        pNode->nAnimFlags |= NODE_ANIM_HOLD;
    }
}

int func_ov022_02098834(struct Actor *pActor, int nState, u32 nPrevTimer)
{
    VecFx32 vecDelta;
    VecFx32 vecDir;
    VecFx32 vecAt;
    VecFx32 vecStep;
    struct EquipEvent event;
    struct AimState *pAim;
    int nResult;
    struct ComboState *pCombo;
    struct DodgeParams *pDodge;
    struct GlideParams *pGlide;
    VecFx32 *pTarget;
    u64 nFlags;
    int nParam;
    int nScale;
    int nArg;
    int nAnim;
    int nTrig;

    nResult = 0;
    pAim = &pActor->aim;
    switch (nState) {
    case 0:
        func_ov022_02097de4(pActor);
        nResult = (int)func_ov022_020a37d0;
        break;
    case 3:
        nParam = func_020358f4(pActor->nId, 0x27);
        if (nParam > 0 && func_ov022_020ad1b4(pActor) != 0 && func_ov022_02095450(&pActor->run) == 0) {
            pTarget = func_ov022_020ad0c0(pActor);
            nScale = pActor->combo.nChaseReach;
            VEC_Subtract(pTarget, &pActor->vecAim, &vecDelta);
            vecDelta.y = 0;
            if (VEC_Mag(&vecDelta) > nScale * 5 && VEC_Mag(&vecDelta) < (nParam * 3 + 5) << 12) {
                nResult = 1;
            }
        }
        if (nResult == 0) {
            pActor->nAnchorPhase = 1;
            if ((pActor->nFlags2 & FLAG2_BIT36) != 0 && func_02030788() == 0) {
                pActor->nFlags3 |= FLAG3_BIT36;
            }
            nResult = (int)func_ov022_020a7a38;
        } else {
            pActor->nMoveRate = nParam * (data_ov022_020b2eb0 != 0 ? 0x65 : 0x43);
            FaceAwayFrom(pActor, &vecDelta);
            pActor->nRushSpeed = nParam * 0x200 + 0x600;
            pActor->nRushTime = -ONE;
            pActor->pfnPreDraw(pActor, 0x13);
            nResult = (int)func_ov022_020abe80;
        }
        break;
    case 9:
        func_ov022_02097de4(pActor);
        pActor->pfnPreDraw(pActor, 5);
        nResult = (int)func_ov022_020a8354;
        pActor->nInputMask &= ~INPUT_BIT2;
        break;
    case 10:
        pActor->nRecoil = 0x80000000;
        pActor->pfnPreDraw(pActor, 7);
        nResult = (int)func_ov022_020a8764;
        break;
    case 0xb:
        pActor->pfnPreDraw(pActor, 0x11);
        func_ov022_020acebc(pActor, pActor->nRunScale);
        if (func_ov022_020ad1b4(pActor) != 0) {
            pTarget = func_ov022_020ad0c0(pActor);
            VEC_Subtract(pTarget, &pActor->vecAim, &vecDir);
            vecDir.y = 0;
            if (VEC_Mag(&vecDir) != 0) {
                func_01ff8d18(&vecDir, &vecDir);
            }
            FaceAwayFrom(pActor, &vecDir);
        }
        pActor->nFlags &= ~FLAG_BIT40;
        pActor->nFlags &= ~FLAG_BIT31;
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT32;
        }
        nResult = (int)func_ov022_020a8b54;
        break;
    case 0xc:
        if ((pActor->nFlags2 & FLAG2_BIT9) != 0) {
            pActor->pfnPreDraw(pActor, 0x12);
            pActor->nFlags &= ~FLAG_BIT41;
        } else {
            pActor->nStateTimer = nPrevTimer;
            pActor->nFlags |= FLAG_BIT41;
            pActor->pfnPreDraw(pActor, 0x11);
            func_ov022_020acebc(pActor, pActor->nRunScale);
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT9;
        }
        if (func_ov022_0209d7a4(pActor) != 0) {
            pActor->nFlags3 |= FLAG3_BIT32;
        }
        pActor->nFlags2 |= FLAG2_BIT32;
        if ((pActor->nFlags & FLAG_BIT31) != 0) {
            pActor->pSub->nHold = 0;
        }
        pActor->nAnimSpeed = 0x1800;
        nResult = (int)func_ov022_020a8ec0;
        break;
    case 8:
        pDodge = &pActor->dodge;
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT30;
        }
        pActor->pfnPreDraw(pActor, 0x10);
        pActor->nFlags |= FLAG_BIT29;
        pActor->nAnimSpeed = 0xccd;
        if (pActor->pSub != 0) {
            pActor->pSub->nHold = pDodge->nHold;
            pActor->pSub->nHeight = 0x500;
        }
        if (pActor->nInterruptCharge < pDodge->nCharge << 12) {
            pActor->nInterruptCharge = pDodge->nCharge << 12;
        }
        func_ov022_020acebc(pActor, pDodge->nScale);
        nResult = (int)func_ov022_020a947c;
        break;
    case 0x15:
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT55;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT15;
        }
        pActor->nFlags &= ~FLAG_BIT28;
        pActor->nFlags &= ~FLAG_BIT32;
        pActor->vecDrift.x = pActor->vecDrift.y = pActor->vecDrift.z = 0;
        func_ov022_02090360(&pActor->reactionCtx);
        func_ov022_02093c34(&pActor->reactionBlk);
        func_ov022_0209d5a4(pActor);
        func_ov022_020acf14(pActor, 0x9000);
        pActor->nFlags |= FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_LOCKED) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
        nResult = (int)func_ov022_020ab764;
        break;
    case 0x10:
        pActor->pfnPreDraw(pActor, 8);
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT28;
        }
        pActor->nFlags |= FLAG_BIT17;
        pActor->nFlags |= FLAG_BIT7;
        func_ov022_02090360(&pActor->reactionCtx);
        func_ov022_02093c34(&pActor->reactionBlk);
        func_ov022_0209d1c0(pActor);
        pActor->nFlags &= ~FLAG_BIT4;
        pActor->nFlags &= ~FLAG_BIT13;
        pActor->vecDrift.x = pActor->vecDrift.y = pActor->vecDrift.z = 0;
        nResult = (int)func_ov022_020ab378;
        pActor->nInputMask |= INPUT_BIT6;
        break;
    case 0x1f:
        vecAt = pActor->vecAim;
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT55;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT33;
        }
        pActor->nFlags &= ~FLAG_BIT28;
        pActor->nFlags &= ~FLAG_BIT32;
        pActor->nFlags |= FLAG_BIT24;
        pActor->nFlags |= FLAG_BIT7;
        pActor->vecDrift.x = pActor->vecDrift.y = pActor->vecDrift.z = 0;
        func_ov022_02090360(&pActor->reactionCtx);
        func_ov022_02093c34(&pActor->reactionBlk);
        func_ov022_0209b1e8(pActor);
        func_ov022_0209d1c0(pActor);
        func_ov022_020ad208(pActor, 4, &vecAt, ONE, (u16)(pActor->pNode->nAngle - ANGLE_HALF), 0);
        pActor->pSub->flags60.nBits &= ~1;
        SNDi_ProcessEntryAlt(pActor->nDownedVoice);
        pActor->pfnPreDraw(pActor, 0);
        pActor->nInterruptCharge = 0x3000;
        nResult = (int)func_ov022_020ab810;
        break;
    case 1:
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT6;
        }
        pActor->aim.nAimMode = 0;
        pAim->nJumpCount = 0;
        pAim->bHold = 0;
        pAim->nAirTimer = 0;
        pAim->nAirStepRate = data_ov022_020b2eb0 != 0 ? 0x3fa : 0x2a6;
        pActor->pfnPreDraw(pActor, 2);
        pActor->vecGround.y = 0;
        nResult = (int)func_ov022_020a64e0;
        break;
    case 2:
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
            pActor->nFlags |= FLAG_BIT46;
            pActor->nFlags &= ~FLAG_BIT2;
            pActor->pfnPreDraw(pActor, 0xe);
        } else {
            if (func_02030788() == 0) {
                pActor->nFlags2 |= FLAG2_BIT6;
            }
            pActor->aim.nAimMode = 2;
            pActor->aim.nAirStepRate = data_ov022_020b2eb0 != 0 ? 0x3fa : 0x2a6;
            pActor->aim.nLandTimer = 0;
            pActor->vecGround.y = 0;
            nAnim = pActor->nAnimId;
            if (nAnim != 3) {
                switch (nAnim) {
                case 0xe:
                case 0x13:
                case 0x14:
                    nArg = 0;
                    break;
                default:
                    nArg = 0xc000;
                    break;
                }
                pActor->pfnPreDraw(pActor, 3);
                func_ov022_02097038(pActor, nArg);
            }
            pActor->aim.nAirTimer = 0;
            nResult = (int)func_ov022_020a64e0;
        }
        break;
    case 0x16:
        pActor->nFlags &= ~FLAG_BIT2;
        pActor->pfnPreDraw(pActor, 4);
        pActor->aim.nAimMode = 3;
        pActor->aim.nLandTimer = 0;
        func_ov022_02097de4(pActor);
        nResult = (int)func_ov022_020a64e0;
        break;
    case 4:
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT55;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT8;
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT8;
        }
        pActor->nFlags &= ~FLAG_BIT28;
        pActor->nFlags &= ~FLAG_BIT32;
        pActor->nFlags &= ~FLAG_BIT4;
        func_ov022_02090360(&pActor->reactionCtx);
        func_ov022_02093c34(&pActor->reactionBlk);
        pActor->nStepRate = 0;
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT31;
        }
        func_ov022_0209d5a4(pActor);
        nResult = (int)func_ov022_020a7d80;
        break;
    case 5:
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT55;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT8;
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT8;
        }
        pActor->nFlags &= ~FLAG_BIT28;
        pActor->nFlags &= ~FLAG_BIT32;
        pActor->nFlags &= ~FLAG_BIT4;
        pActor->nStepRate = 0;
        func_ov022_02090360(&pActor->reactionCtx);
        func_ov022_02093c34(&pActor->reactionBlk);
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT31;
        }
        func_ov022_0209d5a4(pActor);
        nResult = (int)func_ov022_020a8020;
        break;
    case 0x11:
        pActor->nFlags |= FLAG_BIT48;
        nAnim = func_ov022_020b1ba0(&pActor->animReq);
        pActor->pfnPreDraw(pActor, nAnim);
        func_ov022_02093c48(&pActor->reactionBlk, pActor->nLatchedArg, pActor->nLatchedKind, pActor->nLatchedArg2);
        pActor->nHeldArg = pActor->nLatchedArg;
        pActor->nFlags |= FLAG_BIT29;
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0 && func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT7;
        }
        nResult = (int)func_ov022_020aac98;
        break;
    case 0x12:
        pActor->nFlags |= FLAG_BIT48;
        nAnim = func_ov022_020b1ba0(&pActor->animReq);
        pActor->pfnPreDraw(pActor, nAnim);
        pActor->nHeldArg = pActor->nLatchedArg;
        pActor->nFlags |= FLAG_BIT29;
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0 && func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT7;
        }
        nResult = (int)func_ov022_020aaea0;
        break;
    case 6:
        pGlide = &pActor->glide;
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0 && func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT7;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT7;
        }
        pActor->nFlags &= ~FLAG_BIT35;
        if ((pActor->nFlags & FLAG_BIT36) != 0) {
            pActor->nMoveRate = (data_ov022_020b2eb0 != 0 ? 0x1200 : 0xc00) / 2;
        } else {
            pActor->nMoveRate = pGlide->nMoveRate;
            func_ov022_02093034(&pActor->comboBlk);
            if (pActor->nStepRate < (data_ov022_020b2eb0 != 0 ? 0x300 : 0x200)) {
                pActor->nStepRate = data_ov022_020b2eb0 != 0 ? 0x300 : 0x200;
            }
        }
        if (func_020358f4(pActor->nId, 0x24) != 0 && func_ov022_02092dc8(&pActor->reactBlk, 0) != 0) {
            pActor->bAimedJump = 1;
            pActor->nFlags |= FLAG_BIT35;
            pActor->nStepRate = 0xd00;
            pActor->nMoveRate = FxMul(pActor->nMoveRate, 0x19a);
            pActor->nFlags |= FLAG_BIT46;
        }
        nResult = (int)func_ov022_020a98b4;
        break;
    case 0xd:
        if (pActor->nInterruptCharge < pActor->nAimJumpCharge << 12) {
            pActor->nInterruptCharge = pActor->nAimJumpCharge << 12;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT11;
        }
        pActor->pfnPreDraw(pActor, 0x13);
        pActor->nFlags &= ~FLAG_BIT32;
        nResult = (int)func_ov022_020a74d0;
        break;
    case 0x13:
        if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            pActor->pfnPreDraw(pActor, 0);
        }
        pActor->nInputMask |= INPUT_BIT6;
        if (pActor->pEquip != 0) {
            event.nId = pActor->nId;
            func_ov002_02076e08(pActor->pEquip, &event);
            if (func_02030788() == 0) {
                pActor->nFlags2 |= FLAG2_BIT29;
            }
            if (func_02030788() == 0) {
                pActor->nFlags3 |= FLAG3_BIT29;
            }
            pActor->nFlags |= FLAG_BIT7;
            nResult = (int)func_ov022_020ab57c;
        }
        break;
    case 0x14:
        nTrig = (u16)(pActor->pNode->nAngle - ANGLE_HALF) >> 4;
        vecStep.x = data_0203d210[nTrig * 2];
        vecStep.y = 0;
        vecStep.z = data_0203d210[nTrig * 2 + 1];
        func_01ffa724(0x400, &vecStep, &pActor->vecDrift);
        if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            pActor->pfnPreDraw(pActor, 0xc);
            pActor->vecMotion.x = pActor->vecMotion.y = pActor->vecMotion.z = 0;
        } else {
            pActor->pfnPreDraw(pActor, 0xd);
            func_01ffa724(0x300, &vecStep, &pActor->vecMotion);
            pActor->nRecoil = 0x300;
            if ((pActor->nFlags & FLAG_BIT36) == 0 || (pActor->nFlags2 & FLAG2_BIT7) == 0) {
                pActor->nFlags |= FLAG_BIT2;
            }
        }
        nResult = (int)func_ov022_020a72f8;
        break;
    case 0x1a:
        pActor->nFlags |= FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_LOCKED) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
        pActor->nFlags &= ~FLAG_BIT4;
        pActor->charge.nHeld = 0;
        nResult = (int)func_ov022_020ab8d0;
        break;
    case 0x1b:
        if (pAim->bHold == 0) {
            pAim->bHold++;
        } else {
            pActor->nHoldTime = 0x4b000;
            pActor->nGlideHoldTime = 0x4b000;
        }
        if (pActor->nInterruptCharge < 0x3000) {
            pActor->nInterruptCharge = 0x3000;
        }
        switch (pActor->nAnimId) {
        case 9:
        case 0xb:
            nResult = 0x15;
            break;
        case 8:
        case 10:
            nResult = 0x16;
            break;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT56;
        }
        pActor->pfnPreDraw(pActor, nResult);
        pActor->vecMotion.x = pActor->vecMotion.y = pActor->vecMotion.z = 0;
        pActor->nRecoil = 0x400;
        nResult = (int)func_ov022_020abb6c;
        break;
    case 0xe:
    case 0xf:
        pCombo = &pActor->combo;
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT4;
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT4;
        }
        pActor->nFlags |= FLAG_BIT1;
        if ((data_0204c240 & GLOBAL_BIT2) == 0) {
            if ((u32)(pActor->nFlags & FLAG_BIT16) == 0 && pActor->nId == 0) {
                func_ov002_0206cd60(1, 1);
            }
        }
        if ((pActor->nFlags2 & FLAG2_BIT7) != 0 && func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT7;
        }
        if ((pActor->nFlags & FLAG_BIT32) != 0) {
            nResult = 1;
        }
        if (nState == STATE_IDLE_ENTRY) {
            func_ov022_020b08f4(pCombo, nResult, 0);
        } else {
            func_ov022_020b08f4(pCombo, nResult, 1);
        }
        nResult = (int)func_ov022_020a49e0;
        pActor->pfnPreDraw(pActor, pCombo->pLock->pRecord->nAnimSlot + 0x1e);
        func_ov022_020acebc(pActor, pCombo->nChaseScale);
        pActor->nAnimSpeed = ONE;
        if ((pActor->nFlags2 & FLAG2_BIT36) != 0) {
            func_ov022_020acf14(pActor, pCombo->pLock->pRecord->nEntryFlags);
        }
        pActor->combo.nPhase = 0;
        break;
    case 0x1c:
        if (func_ov022_0208868c() != 0) {
            break;
        }
        nFlags = pActor->nFlags;
        if ((nFlags & FLAG_BIT24) != 0) {
            break;
        }
        if ((nFlags & FLAG_BIT8) == 0 && (nFlags & FLAG_BIT13) != 0) {
            break;
        }
        if ((nFlags & FLAG_BIT8) == 0 && (nFlags & FLAG_BIT17) != 0) {
            break;
        }
        if ((nFlags & FLAG_BIT8) == 0
            && (pActor->charge.nKnockdownKind == 3 || pActor->charge.nKnockdownKind == 0xb
                || pActor->charge.nKnockdownKind == 2)) {
            break;
        }
        func_020358a4((u8)(pActor->nId - 1))->nStall = 0;
        pActor->pfnPreDraw(pActor, 3);
        func_ov022_02097a90(pActor);
        if (pActor->pSub->pfnHook14 != 0) {
            pActor->pSub->pfnHook14(pActor->pSub, 0);
        }
        SNDi_ProcessEntryAlt(pActor->nDownedVoice);
        pActor->nFlags &= ~FLAG_BIT6;
        pActor->nFlags &= ~FLAG_BIT23;
        pActor->nFlags |= FLAG_BIT24;
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT39;
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT39;
        }
        nResult = (int)func_ov022_020ac6c8;
        break;
    case 0x1d:
        if (pActor->nInterruptCharge < 0x6000) {
            pActor->nInterruptCharge = 0x6000;
        }
        if (pActor->nAimAngle == -1) {
            if (func_02030788() == 0) {
                pActor->nFlags2 |= FLAG2_BIT54;
            }
            pActor->pfnPreDraw(pActor, 0x14);
        } else {
            if (func_02030788() == 0) {
                pActor->nFlags2 |= FLAG2_BIT56;
            }
            pActor->pfnPreDraw(pActor, 0x16);
        }
        nResult = (int)func_ov022_020ac21c;
        break;
    case 0x1e:
        nAnim = pActor->nAnimId;
        if (nAnim != 3) {
            switch (nAnim) {
            case 0xe:
            case 0x13:
            case 0x14:
                nArg = 0;
                break;
            default:
                nArg = 0xc000;
                break;
            }
            pActor->pfnPreDraw(pActor, 3);
            func_ov022_02097038(pActor, nArg);
        }
        pActor->aim.nWalkPhase = 0;
        nResult = (int)func_ov022_020ac480;
        break;
    case 0x17:
        pActor->nInterruptCharge = 0x2000;
        if (pActor->nOwner == func_02030788() && (u32)(pActor->nFlags & FLAG_BIT16) == 0) {
            func_ov002_0204cb70(func_ov022_02083f0c(), 6, 0);
        }
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0 && func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT7;
        }
        func_ov022_020954e4(&pActor->run);
        pActor->pfnPreDraw(pActor, 0x2e);
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT16;
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT16;
        }
        func_ov022_0209b1e8(pActor);
        pActor->nFlags |= FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_LOCKED) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
        nResult = (int)func_ov022_020a70cc;
        break;
    case 0x18:
        nResult = pActor->pfnEnterHook(pActor, 0);
        break;
    case 0x19:
        nResult = pActor->pfnEnterHook(pActor, 1);
        break;
    default:
        break;
    }
    return nResult;
}
