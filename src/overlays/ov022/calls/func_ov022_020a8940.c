/* Ov022_ResetActorAfterPlace -- put a freshly placed actor back to idle.
 *
 * The local player resets the state machine to state 0 and clears the
 * reaction context and block. Then the hit reaction, buttons, anim frame,
 * input block, drift, flag words (only a few bits survive, bit 29 raised),
 * charge and voice flags are reset, the interrupt charge set to 0x6000, the
 * velocity zeroed and the placement re-synced, the wall hold and scroll
 * target cleared. With a player record its target takes the aim point and
 * the record is moved there. Under mode flag bit 2 or flag bit 16 an actor
 * at 0 HP is refilled by the local player -- and when it is its own actor
 * and the ov002 root word's bit 31 is clear the global byte is raised --
 * and model 2 marshals its status.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Vec3 {
    int x;
    int y;
    int z;
};

#define VEC_COPY(pDst, pSrc) (*(pDst) = *(struct Vec3 *)(void *)(pSrc))

#define FLAGS_KEEP 0x400000f000011461ULL
#define FLAG_BIT29 (1ULL << 29)
#define FLAG_BIT16 (1ULL << 16)
#define INPUT_BIT2 0x4
#define CHARGE_INIT 0x6000
#define MODE_FLAG_BIT2 0x4
#define MODEL_2 2
#define CHARGE_RELEASED 0x1

struct Actor;
typedef void (*PfnState)(struct Actor *pActor);

/* Ov022ActorSub */
struct Sub {
    u8 pad0000[0x190];
    struct Vec3 vecTarget;       /* 0x190 */
};

/* Ov022Charge */
struct Charge {
    u8 pad0000[0xc];
    u8 bReleased;                /* 0x0c, bit 0 */
};

struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 nOwner;                   /* 0x0008 */
    u8 pad0009[3];
    int nModelId;                /* 0x000c */
    u8 pad0010[2];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[2];
    u16 nHpMax;                  /* 0x0016 */
    u16 nButtons;                /* 0x0018 */
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[4];
    void *pNode;                 /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    struct Vec3 vecVel;          /* 0x0028 */
    u8 pad0034[0x42c];
    PfnState pfnState;           /* 0x0460 */
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[8];
    struct Vec3 vecDrift;        /* 0x047c */
    u8 pad0488[0x2c];
    int nInterruptCharge;        /* 0x04b4 */
    u8 pad04b8[0x34];
    struct Sub *pSub;            /* 0x04ec */
    u8 pad04f0[0x1a4];
    u8 bSuppressDraw : 1;        /* 0x0694 */
    u8 bStateOver : 1;
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;
    u8 bSequenceRunning : 1;
    u8 bVoicePlayed : 1;
    u8 bTriggerHeld : 1;
    u8 nSpare6947 : 1;
    u8 pad0695[0x27];
    int nHitReaction;            /* 0x06bc */
    u8 pad06c0[0xf0];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x128];
    u16 nTrackCount;             /* 0x08dc */
    u8 pad08de[0x14ca];
    u8 reactionBlk[0x4e0];       /* 0x1da8 */
    u16 reactionCtx[0x38];       /* 0x2288 Ov022ReactionCtx (0x70) */
    u8 pad22f8[0x34c];
    void *pShotChannels;         /* 0x2644 */
    u8 pad2648[0x128];
    struct Charge charge;        /* 0x2770 */
};

extern const struct Vec3 data_02041dc8;     /* kVecZero */
extern u8 data_0204c240;                    /* g_modeAndDayClock.nModeFlags */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);               /* Ov022_ActorSetState */
extern void func_ov022_02090360(u16 *pCtx);                                     /* ov022_SetBit5OfHalf0IfByte2 */
extern void func_ov022_02093c34(u8 *pBlk);                                      /* ov022_ClearByte1IfEquals4 */
extern void func_ov022_02097ff0(struct Actor *pActor);                          /* InitField4d0Block */
extern void func_0202de3c(void **pPlacement, int nArg);                         /* re-place the node */
extern void func_ov022_02096964(struct Actor *pActor);                          /* ClearVec3At_2bc4 */
extern void func_ov022_020965b8(struct Actor *pActor);                          /* SetScrollTargetOrClamp */
extern void func_ov022_0209a3a4(struct Vec3 *pOut, struct Actor *pActor);       /* Ov022_ComputeAimPoint */
extern void func_ov107_020c5c54(struct Sub *pSub, const struct Vec3 *pPos);     /* Ov107_MoveNodeAndRelayout */
extern void func_ov022_020acc94(struct Actor *pActor, int nValue);              /* Ov022_ActorSetHp */
extern u32 func_ov002_0206dbf8(void);                                           /* Ov002_GetRootField8b64 */
extern void func_02020878(int nArg);                                            /* StoreGlobalByteAt1_0204bd84 */
extern void func_ov022_0209190c(void *pChannels);                               /* MarshalStatusTwoByte */

void func_ov022_020a8940(struct Actor *pActor)
{
    struct Vec3 vecSubCopy;
    struct Vec3 vecSubPos;

    if (func_02030788() == 0) {
        pActor->pfnState = (PfnState)func_ov022_020a35f4(pActor, 0);
        func_ov022_02090360(pActor->reactionCtx);
        func_ov022_02093c34(pActor->reactionBlk);
    }
    pActor->nHitReaction = -1;
    pActor->nButtons = 0;
    pActor->nButtons2 = 0;
    pActor->nAnimFrame = 0;
    func_ov022_02097ff0(pActor);
    pActor->vecDrift.x = pActor->vecDrift.y = pActor->vecDrift.z = 0;
    pActor->nFlags2 = 2;
    pActor->nFlags3 = 1;
    pActor->nInputMask |= INPUT_BIT2;
    pActor->nFlags &= FLAGS_KEEP;
    pActor->nFlags |= FLAG_BIT29;
    pActor->charge.bReleased &= ~CHARGE_RELEASED;
    pActor->nTrackCount = 0;
    pActor->bVoicePlayed = 0;
    pActor->nInterruptCharge = CHARGE_INIT;
    pActor->vecVel.x = data_02041dc8.x;
    pActor->vecVel.y = 0;
    pActor->vecVel.z = data_02041dc8.z;
    func_0202de3c(&pActor->pNode, 1);
    func_ov022_02096964(pActor);
    func_ov022_020965b8(pActor);
    if (pActor->pSub != 0) {
        struct Sub *pSub;

        func_ov022_0209a3a4(&vecSubPos, pActor);
        VEC_COPY(&vecSubCopy, &vecSubPos);
        pSub = pActor->pSub;
        VEC_COPY(&pSub->vecTarget, &vecSubCopy);
        func_ov107_020c5c54(pSub, &pSub->vecTarget);
    }
    if ((data_0204c240 & MODE_FLAG_BIT2) == 0 && (pActor->nFlags & FLAG_BIT16) == 0) {
        return;
    }
    if (pActor->nHp != 0) {
        return;
    }
    if (func_02030788() == 0) {
        func_ov022_020acc94(pActor, pActor->nHpMax);
        if (pActor->nOwner == func_02030788() && (func_ov002_0206dbf8() & 0x80000000) == 0) {
            func_02020878(1);
        }
    }
    if (pActor->nModelId == MODEL_2) {
        func_ov022_0209190c(pActor->pShotChannels);
    }
}
