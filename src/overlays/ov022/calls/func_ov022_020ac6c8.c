/* Ov022_StepStuckRespawnState -- state step for a partner that is stuck:
 * count the stall and, once it is long enough, put the actor back next to
 * the leader. Returns the next state step (itself while waiting).
 *
 * The slot's stall grows by 0xcd per frame in mode 1, 0x89 otherwise; the
 * local player raises flags2/flags3 bit 39 every frame. From 1.0 on the
 * actor takes flag bit 34 (flags2/flags3 bit 33 for the local player) and
 * the respawn waits until the stall reaches the slot's respawn threshold
 * for a flag-bit-8 actor, 1.0 otherwise. The ground effect starts; a
 * flag-bit-8 actor is reset after its placement and its threshold grows by
 * 3.0 (clamped to 0..60.0). The spawn point is the leader's position plus
 * the actor's offset turned to the leader's facing; up to five times a
 * sphere cast 0x900 wide along 1.5x the offset from 0.84 above the leader
 * is run and, when it is clear (or on the last try), a ray from 4.0 above
 * the point down 5.0 looks for the ground: found, the point drops to it;
 * otherwise the offset is turned a further quarter (left, back, right,
 * left) and tried again. The point rises 0.3, becomes the node's position
 * and the actor's own; the node faces the leader unless it skips its
 * animation. Walk speed 0.3 (0.2 without the recoil pick), step rate,
 * buttons and motion reset; the slot goes to state 2 with a clear stall;
 * bit 0x200 cleared, the pre-draw hook run with 0 and state 0 entered
 * (that is the return); flag bits 8, 24 and 34 drop and bit 6 rises; the
 * sub's +0x14 hook runs with 1; the node is submitted for rendering.
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

typedef struct {
    int aM[9];
} MtxFx33;

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x000 */
    u16 nAnimFlags;              /* 0x004 */
    u8 pad006[0x7a];
    u16 nAngle;                  /* 0x080 */
};

/* Ov022ActorSub */
struct ActorSub {
    u8 pad000[0x14];
    void (*pfnHook14)(struct ActorSub *pSub, int nArg);   /* 0x014 */
};

struct Actor;

typedef void (*ActorHookFn)(struct Actor *pActor, int nArg);   /* Ov022ActorHookFn */

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
    u8 pad0024[0x42];
    u16 nSlotIndex;              /* 0x0066 */
    u8 pad0068[0x3fc];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x18];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x20];
    int nTurnRate;               /* 0x04b8 */
    s8 nDownedVoice;             /* 0x04bc */
    u8 pad04bd[0x2f];
    struct ActorSub *pSub;       /* 0x04ec */
    u8 pad04f0[0x174];
    ActorHookFn pfnPreDraw;      /* 0x0664 */
    u8 pad0668[0x30];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0x10];
    int nStepRate;               /* 0x06b4 */
};

/* PlayerSlot */
struct PlayerSlot {
    int nState;                  /* 0x00 */
    u32 nFlags;                  /* 0x04 */
    int nStall;                  /* 0x08 */
    int nCooldown;               /* 0x0c */
    int nField10;                /* 0x10 */
    int nRespawnThreshold;       /* 0x14 */
};

/* collision hit record */
struct CollHit {
    u8 pad00[0xc];
    int nT;                      /* 0x0c */
};

#define FLAG_BIT6 (1ULL << 6)
#define FLAG_BIT8 (1ULL << 8)
#define FLAG_BIT24 (1ULL << 24)
#define FLAG_BIT34 (1ULL << 34)
#define FLAG2_BIT33 (1ULL << 33)
#define FLAG2_BIT39 (1ULL << 39)
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define STALL_FAST 0xcd
#define STALL_SLOW 0x89
#define STALL_RESPAWN 0x1000
#define THRESHOLD_STEP 0x3000
#define THRESHOLD_MAX 0x3c000
#define SPAWN_TRIES 5
#define OFFSET_SCALE 0x1800
#define CAST_RAISE 0xd80
#define CAST_RADIUS 0x900
#define GROUND_RAISE 0x4000
#define GROUND_DROP 0x5000
#define SPAWN_LIFT 0x4cd
#define TURN_FAST 0x4cd
#define TURN_SLOW 0x333
#define SLOT_STATE_RESPAWNED 2

extern VecFx32 data_ov022_020b26f4[4];       /* kOv022RespawnOffsets, per actor id */
extern short data_0203d210[];                /* kFxSinCosTable: sin, cos pairs */
extern u8 data_ov022_020b2eb0;               /* gOv022RecoilPick */

extern int func_02023c40(void);                                                 /* LoadGlobalU8_0204c058 */
extern struct PlayerSlot *func_020358a4(int nSlot);                             /* GetPlayerSlotTableEntry */
extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern void func_ov022_02097a90(struct Actor *pActor);                          /* Ov022_StartGroundEffect */
extern void func_ov022_020a8940(struct Actor *pActor);                          /* Ov022_ResetActorAfterPlace */
extern u16 func_01fffe14(void);                                                 /* QueryActiveStateOrDelegate */
extern VecFx32 *func_ov022_020881f8(int nIndex);                                /* GetEntryPtr48cOrDefault */
extern short func_ov022_02088254(int nIndex);                                   /* GetEntryField80Biased */
extern void MTX_Identity33_(MtxFx33 *pMtx);
extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(VecFx32 *pVec, MtxFx33 *pMtx, VecFx32 *pOut);
extern void MTX_Concat33(MtxFx33 *pA, MtxFx33 *pB, MtxFx33 *pOut);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_01ffa724(int nScale, VecFx32 *pIn, VecFx32 *pOut);             /* ScaleVec3Fx12 */
extern int func_0202c2ac(int nSlot, VecFx32 *pFrom, VecFx32 *pDir, int nRadius, struct ActorNode *pNode);   /* sphere cast */
extern struct CollHit *func_0202c268(int nSlot, VecFx32 *pFrom, VecFx32 *pDir, struct ActorNode *pNode);    /* ray cast */
extern void func_01ffd0e8(int nT, VecFx32 *pDir, VecFx32 *pFrom, VecFx32 *pOut); /* Vec3ScaleAddQ27 */
extern void func_0202b450(struct ActorNode *pNode, VecFx32 *pPos);              /* Actor_SetVecAndSyncChild */
extern void func_ov022_0209a68c(struct Actor *pActor, int nOn);                 /* SetOrClearBit200 */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);               /* Ov022_ActorSetState */
extern void func_0202ba78(int nVoice, int nSlot, int nArg, VecFx32 *pPos);      /* Render_SubmitNode by voice */
int func_ov022_020ac6c8(struct Actor *pActor);

static inline void VEC_Set(VecFx32 *pVec, int x, int y, int z)
{
    pVec->x = x;
    pVec->y = y;
    pVec->z = z;
}

int func_ov022_020ac6c8(struct Actor *pActor)
{
    VecFx32 vecSpawn;
    VecFx32 vecOffset;
    MtxFx33 mtx;
    VecFx32 vecDir;
    VecFx32 vecFrom;
    VecFx32 vecTop;
    VecFx32 vecDown;
    VecFx32 vecGround;
    MtxFx33 mtxTurn;
    int nRet;
    int nStep;
    struct PlayerSlot *pSlot;
    VecFx32 *pLeaderPos;
    int nLeaderAngle;
    int nThreshold;
    int nTry;
    int bTurn;
    struct CollHit *pHit;
    struct ActorNode *pNode;
    void (*pfnHook)(struct ActorSub *pSub, int nArg);

    nStep = func_02023c40() == 1 ? STALL_FAST : STALL_SLOW;
    nRet = (int)func_ov022_020ac6c8;
    pSlot = func_020358a4((u8)(pActor->nId - 1));
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT39;
    }
    if (func_02030788() == 0) {
        pActor->nFlags3 |= FLAG2_BIT39;
    }
    pSlot->nStall += nStep;
    if (pSlot->nStall >= STALL_RESPAWN) {
        pActor->nFlags |= FLAG_BIT34;
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT33;
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 |= FLAG2_BIT33;
        }
        if ((pActor->nFlags & FLAG_BIT8) != 0) {
            if (pSlot->nRespawnThreshold <= pSlot->nStall) {
                goto respawn;
            }
            goto done;
        }
        if (pSlot->nStall < STALL_RESPAWN) {
            goto done;
        }
respawn:
        func_ov022_02097a90(pActor);
        if ((pActor->nFlags & FLAG_BIT8) != 0) {
            func_ov022_020a8940(pActor);
            nThreshold = pSlot->nRespawnThreshold + THRESHOLD_STEP;
            if (nThreshold > THRESHOLD_MAX) {
                nThreshold = THRESHOLD_MAX;
            } else if (nThreshold < 0) {
                nThreshold = 0;
            }
            pSlot->nRespawnThreshold = nThreshold;
        }
        pLeaderPos = func_ov022_020881f8(func_01fffe14());
        nLeaderAngle = func_ov022_02088254(func_01fffe14());
        vecOffset = data_ov022_020b26f4[pActor->nId];
        MTX_Identity33_(&mtx);
        MTX_RotY33_(&mtx, data_0203d210[(nLeaderAngle >> 4) * 2], data_0203d210[(nLeaderAngle >> 4) * 2 + 1]);
        MTX_MultVec33(&vecOffset, &mtx, &vecOffset);
        VEC_Add(&vecOffset, pLeaderPos, &vecSpawn);
        nTry = 0;
        do {
            vecDir = vecOffset;
            func_01ffa724(OFFSET_SCALE, &vecDir, &vecDir);
            VEC_Set(&vecFrom, pLeaderPos->x, pLeaderPos->y + CAST_RAISE, pLeaderPos->z);
            if (func_0202c2ac(pActor->nSlotIndex, &vecFrom, &vecDir, CAST_RADIUS, pActor->pNode) == 0 || nTry == SPAWN_TRIES - 1) {
                vecDown.x = 0;
                vecDown.y = -GROUND_DROP;
                vecDown.z = 0;
                vecTop = vecSpawn;
                vecTop.y += GROUND_RAISE;
                pHit = func_0202c268(pActor->nSlotIndex, &vecTop, &vecDown, pActor->pNode);
                if (pHit != 0) {
                    func_01ffd0e8(pHit->nT, &vecDown, &vecTop, &vecGround);
                    vecSpawn.y = vecGround.y;
                    break;
                }
                if (nTry == SPAWN_TRIES - 1) {
                    break;
                }
                bTurn = 1;
            } else {
                bTurn = 1;
            }
            if (bTurn) {
                MTX_Identity33_(&mtxTurn);
                switch (nTry) {
                case 0:
                case 3:
                    MTX_RotY33_(&mtxTurn, 0x1000, 0);
                    break;
                case 1:
                    MTX_RotY33_(&mtxTurn, 0, -0x1000);
                    break;
                case 2:
                    MTX_RotY33_(&mtxTurn, -0x1000, 0);
                    break;
                }
                MTX_Concat33(&mtx, &mtxTurn, &mtx);
                vecOffset = data_ov022_020b26f4[pActor->nId];
                MTX_MultVec33(&vecOffset, &mtx, &vecOffset);
                VEC_Add(&vecOffset, pLeaderPos, &vecSpawn);
            }
            nTry++;
        } while (nTry < SPAWN_TRIES);
        vecSpawn.y += SPAWN_LIFT;
        func_0202b450(pActor->pNode, &vecSpawn);
        pActor->vecAim = vecSpawn;
        pNode = pActor->pNode;
        if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
            pNode->nAngle = nLeaderAngle + ANGLE_BIAS;
            pNode->nAnimFlags |= ANIM_HOLD;
        }
        pActor->nTurnRate = data_ov022_020b2eb0 ? TURN_FAST : TURN_SLOW;
        pActor->nStepRate = 0;
        pActor->nButtons = 0;
        pActor->nButtons2 = 0;
        pActor->vecMotion.x = 0;
        pActor->vecMotion.y = 0;
        pActor->vecMotion.z = 0;
        pSlot->nState = SLOT_STATE_RESPAWNED;
        pSlot->nStall = 0;
        func_ov022_0209a68c(pActor, 0);
        pActor->pfnPreDraw(pActor, 0);
        nRet = func_ov022_020a35f4(pActor, 0);
        pActor->nFlags &= ~FLAG_BIT8;
        pActor->nFlags &= ~FLAG_BIT24;
        pActor->nFlags &= ~FLAG_BIT34;
        pActor->nFlags |= FLAG_BIT6;
        pfnHook = pActor->pSub->pfnHook14;
        if (pfnHook != 0) {
            pfnHook(pActor->pSub, 1);
        }
        func_0202ba78((u16)pActor->nDownedVoice, pActor->nSlotIndex, 0, &pActor->vecAim);
    }
done:
    return nRet;
}
