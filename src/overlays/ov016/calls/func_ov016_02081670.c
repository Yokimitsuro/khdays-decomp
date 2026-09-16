/* func_ov016_02081670 -- Ov016_KickableHandleMessage: the kickable's message handler (its
 * class slot), switching on the message type byte.  Type 2 (a kick): stores the kicking
 * player (+0x61f, the 7-bit field), picks the kick speed (+0x1c) from the kind row of the
 * 02082748 table (the second speed when the message's top bit is set), takes the kick
 * direction (+0x468) from the message's position and raises kick flag bit 2; kind 0 and 2
 * kickables whose body is not held (bit 2 of +0x28) are launched: body value +0x5c cleared,
 * kick flag bit 0 (in flight) and a vertical lift of 0x19a.  Type 3: acknowledges a peer
 * (Ov016_KickableAckPeer 02081624 with the message's peer byte) unless sync bit 0 is set.
 * Type 4 (a kick target): copies the target (+0x474), raises kick flags 0x304, and derives
 * the velocity (+0x468) as (target - rest) scaled by 1 / (3 * frame delta) (ov002 0207687c,
 * FX_Inv, ScaleVec3Fx12 01ffa724), zeroing +0x484.  Type 6 (a peer's velocity, ignored on the
 * host): the three halfword components times 16 go to +0x640 and sync bit 1 is raised.
 * Types 0, 1, 5 and anything above 6 do nothing. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016KickableKindRow {
    void *pfnStep;            /* 0x00 */
    short nLength;            /* 0x04 */
    short nPad06;             /* 0x06 */
    int  nStep;               /* 0x08 */
    short nSpeedA;            /* 0x0c */
    short nSpeedB;            /* 0x0e */
    short nSpeedC;            /* 0x10 */
    short nPad12;             /* 0x12 */
} Ov016KickableKindRow;

typedef struct Ov016KickableDef {
    u8  pad_00[0x7c];
    u8  nKind;                /* 0x7c */
} Ov016KickableDef;

typedef struct Ov016KickableMessage {
    u8   nType;               /* 0x00: 2 kick, 3 acknowledge, 4 target, 6 velocity */
    u8   pad_01[3];
    union {
        VecFx32 position;     /* 0x04: types 2 and 4 */
        u8  nPeer;            /* 0x04: type 3 */
        short aVelocity[3];   /* 0x04: type 6 */
    } u;
    char nPlayer : 7;         /* 0x10: type 2 */
    char bFlag : 1;
} Ov016KickableMessage;

typedef struct Ov016Kickable {
    u8   pad_000[8];
    Ov016KickableDef *pDef;   /* 0x008 */
    u8   pad_00c[0x1c - 0xc];
    u16  nSpeedA;             /* 0x01c */
    u8   pad_01e[0x28 - 0x1e];
    u32  nBodyFlags;          /* 0x028: body + 4, bit 2 held */
    u8   pad_02c[0x5c - 0x2c];
    int  nBodyWord5c;         /* 0x05c: body + 0x38 */
    u8   pad_060[0x464 - 0x60];
    u16  nKickFlags;          /* 0x464: bit 0 in flight, bit 2 kicked, bits 8/9 target */
    u8   pad_466[2];
    VecFx32 kick;             /* 0x468: kick direction / velocity */
    VecFx32 target;           /* 0x474 */
    int  nWord480;            /* 0x480 */
    int  nWord484;            /* 0x484 */
    u8   pad_488[0x54c - 0x488];
    VecFx32 rest;             /* 0x54c */
    u8   pad_558[0x61c - 0x558];
    u8   nSyncFlags;          /* 0x61c */
    u8   nAckMask;            /* 0x61d */
    u8   nTrack;              /* 0x61e */
    char nPlayer;             /* 0x61f */
    u8   pad_620[0x640 - 0x620];
    VecFx32 velocity;         /* 0x640 */
} Ov016Kickable;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int  func_ov016_02081624(Ov016Kickable *pSelf, int nPeer);        /* Ov016_KickableAckPeer */
extern void VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern int  func_ov002_0207687c(void);                                    /* frame delta */
extern int  FX_Inv(int nNumerator, int nDenominator);
extern void func_01ffa724(int nScale, const VecFx32 *pVec, VecFx32 *pOut); /* ScaleVec3Fx12 */
extern int  func_02030788(void);                                          /* Session_GetLocalPlayerIndex */
extern Ov016KickableKindRow data_ov016_02082748[];                        /* per-kind rows */

void func_ov016_02081670(Ov016Kickable *pSelf, Ov016KickableMessage *pMessage)
{
    Ov016KickableDef *pDef;

    pDef = pSelf->pDef;
    switch (pMessage->nType) {
    case 0:
    case 1:
        break;
    case 2:
        pSelf->nPlayer = pMessage->nPlayer;
        pSelf->nSpeedA = pMessage->bFlag ? data_ov016_02082748[pDef->nKind].nSpeedB : data_ov016_02082748[pDef->nKind].nSpeedA;
        pSelf->kick = pMessage->u.position;
        pSelf->nKickFlags |= 4;
        if (pDef->nKind == 2 || pDef->nKind == 0) {
            if ((pSelf->nBodyFlags & 4) == 0) {
                pSelf->nBodyWord5c = 0;
                pSelf->nKickFlags |= 1;
                pSelf->kick.y = 0x19a;
            }
        }
        break;
    case 3:
        if ((pSelf->nSyncFlags & 1) == 0) {
            func_ov016_02081624(pSelf, pMessage->u.nPeer);
        }
        break;
    case 4:
        pSelf->target = pMessage->u.position;
        pSelf->nKickFlags |= 0x304;
        VEC_Subtract(&pSelf->target, &pSelf->rest, &pSelf->kick);
        func_01ffa724(FX_Inv(0x1000, FX_Mul(func_ov002_0207687c(), 0x3000)), &pSelf->kick, &pSelf->kick);
        pSelf->nWord484 = 0;
        break;
    case 5:
        break;
    case 6:
        if (func_02030788() != 0) {
            pSelf->velocity.x = pMessage->u.aVelocity[0] << 4;
            pSelf->velocity.y = pMessage->u.aVelocity[1] << 4;
            pSelf->velocity.z = pMessage->u.aVelocity[2] << 4;
            pSelf->nSyncFlags |= 2;
        }
        break;
    }
}
