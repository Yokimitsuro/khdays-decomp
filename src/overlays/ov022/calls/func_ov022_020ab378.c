/* Ov022_StepDownedState -- run one frame of the downed state.
 *
 * The local player raises flag-2 bits 28 and 23; input bit 6 goes up, the
 * interrupt charge is set to half a unit and the drift cleared. At exactly
 * 0x33 units of state time the actor's point is broadcast as record 3 with
 * the node's facing. Past 0x44 units the end request (flag-2 bit 33) is
 * raised for the local player and the actor's downed voice is played once.
 * Past animation frame 0x9000 flag bit 49 goes up and the animation is poked
 * unless the node is already skipping it. Past 0x4e units the flag-2 word is
 * reset to bits 27 and 33, the drift cleared again, a mission tally added the
 * first time (flag bit 8 remembers it) and the health zeroed. The state's own
 * step runs last; the answer is always 0.
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
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[0x7a];
    u16 nAngle;                  /* 0x80 */
};

struct Actor;

typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[0xc];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x43c];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x10];
    VecFx32 vecDrift;            /* 0x047c */
    u8 pad0488[0x2c];
    int nInterruptCharge;        /* 0x04b4 */
    u8 pad04b8[4];
    s8 nDownedVoice;             /* 0x04bc */
    u8 pad04bd[0xf];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x198];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;        /* bit 3 */
    u8 bSequenceRunning : 1;     /* bit 4 */
    u8 bVoicePlayed : 1;         /* bit 5 */
    u8 nFlags694Rest : 2;
    u8 pad0695[0x11b];
    int nAnimFrame;              /* 0x07b0 */
};

#define FLAG_BIT8 (1ULL << 8)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT23 (1ULL << 23)
#define FLAG2_BIT27 (1ULL << 27)
#define FLAG2_BIT28 (1ULL << 28)
#define FLAG2_BIT33 (1ULL << 33)
#define INPUT_BIT6 0x40
#define NODE_NO_ANIM 0x20
#define CHARGE_HALF 0x2000
#define TIME_BROADCAST 0x33000
#define TIME_END_REQUEST 0x44000
#define TIME_SETTLE 0x4e000
#define FRAME_POKE 0x9000
#define ANGLE_BIAS 0x8000
#define NET_RECORD_DOWNED 3
#define NET_TAG_DOWNED 0x1000
#define TALLY_DOWNED 1

extern int func_02030788(void);
extern void func_ov022_020ad44c(VecFx32 *pOut, struct Actor *pActor);
extern void func_ov022_020ad208(struct Actor *pActor, int nRecord, VecFx32 *pAt, int nTag,
                                u32 nAngle, int nKind);        /* Ov022_MarshalNetworkRecord */
extern void SNDi_ProcessEntryAlt(int nVoice);
extern void func_0202af1c(u16 *pAnimFlags);                    /* SceneNode_Enable */
extern void func_ov002_0206bbb8(int nWho, int nKind, int nCount);   /* Ov002_AddMissionTally */

int func_ov022_020ab378(struct Actor *pActor)
{
    VecFx32 vecAt;
    VecFx32 vecPoint;

    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT28;
    }
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT23;
    }
    pActor->nInputMask |= INPUT_BIT6;
    pActor->nInterruptCharge = CHARGE_HALF;
    pActor->vecDrift.x = pActor->vecDrift.y = pActor->vecDrift.z = 0;
    if (pActor->nStateTimer == TIME_BROADCAST) {
        func_ov022_020ad44c(&vecPoint, pActor);
        vecAt = vecPoint;
        func_ov022_020ad208(pActor, NET_RECORD_DOWNED, &vecAt, NET_TAG_DOWNED,
                            (u16)(pActor->pNode->nAngle - ANGLE_BIAS), 0);
    }
    if ((int)pActor->nStateTimer >= TIME_END_REQUEST) {
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT33;
        }
        if (!pActor->bVoicePlayed) {
            SNDi_ProcessEntryAlt(pActor->nDownedVoice);
            pActor->bVoicePlayed = 1;
        }
    }
    if (pActor->nAnimFrame >= FRAME_POKE) {
        pActor->nFlags |= FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
    }
    if ((int)pActor->nStateTimer >= TIME_SETTLE) {
        pActor->nFlags2 = FLAG2_BIT27 | FLAG2_BIT33;
        pActor->vecDrift.x = pActor->vecDrift.y = pActor->vecDrift.z = 0;
        if ((pActor->nFlags & FLAG_BIT8) == 0) {
            func_ov002_0206bbb8(pActor->nId, TALLY_DOWNED, 1);
        }
        pActor->nFlags |= FLAG_BIT8;
        pActor->nHp = 0;
    }
    pActor->pfnPostDraw(pActor);
    return 0;
}
