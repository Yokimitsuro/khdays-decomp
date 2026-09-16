/* func_ov015_02081694 -- Ov015_ChestPushPlayer: push an actor away from a treasure chest
 * once per player: unless the player's bit is already set in the pushed mask (+0x730),
 * builds an ov107 hit packet whose normal is the unit direction from the chest position
 * (+0x488) to the actor position (+0xb0) scaled by 0x266, with flags 8, kind mask 0x80
 * (class 0x1b) or 8, base half the actor's HP (+0x218), no damage, the opener (+0x726)
 * as id, the given part node and strength 100, sends it to the actor (ov107 020c5cfc)
 * and marks the player's bit.  Always returns 1. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern void func_01ff8d18(VecFx32 *pVec, VecFx32 *pOut);                  /* VEC_Normalize */
extern void func_01ffa724(int nScale, const VecFx32 *pVec, VecFx32 *pOut); /* ScaleVec3Fx12 */
extern void VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);

/* Ov107HitPacket */
typedef struct Ov015HitPacket {
    u32 nFlags : 16;             /* 0x00 */
    u32 nKindMask : 16;
    VecFx32 vecPos;              /* 0x04 */
    int nBase : 16;              /* 0x10 */
    int nDamage : 16;
    u32 nId : 16;                /* 0x14 */
    u32 nSpare16 : 16;
    void *pNode;                 /* 0x18 */
    s8  nStrength;               /* 0x1c */
    u8  nExtraByte;              /* 0x1d */
    u8  pad1e[6];
    u32 nResult : 16;            /* 0x24 */
    u32 nSpare24 : 16;
    u32 nField28;                /* 0x28 */
} Ov015HitPacket;

extern int func_ov107_020c5cfc(void *pActor, void *pSub, Ov015HitPacket *pPacket);

typedef struct Ov022Actor {
    u8   pad_000[0xb0];
    VecFx32 position;         /* 0x0b0 */
    u8   pad_0bc[0x218 - 0xbc];
    short nHp;                /* 0x218 */
} Ov022Actor;

typedef struct Ov015ChestDef {
    u8   pad_00[0x4c];
    u16  nClass;              /* 0x4c: 0x1b / 0x1c */
} Ov015ChestDef;

typedef struct Ov015Chest {
    u8   pad_000[8];
    Ov015ChestDef *pDef;      /* 0x008 */
    u8   pad_00c[0x488 - 0xc];
    VecFx32 position;         /* 0x488 */
    u8   pad_494[0x726 - 0x494];
    s8   nOpener;             /* 0x726 */
    u8   pad_727[0x730 - 0x727];
    int  nPushedMask2;        /* 0x730 */
} Ov015Chest;

int func_ov015_02081694(u8 nPlayer, Ov022Actor *pActor, void *pNode, Ov015Chest *pChest)
{
    Ov015ChestDef *pDef;
    Ov015HitPacket packet;
    VecFx32 direction;
    VecFx32 position;

    pDef = pChest->pDef;
    if ((pChest->nPushedMask2 & (1 << nPlayer)) == 0) {
        position = pActor->position;
        VEC_Subtract(&position, &pChest->position, &direction);
        func_01ff8d18(&direction, &direction);
        func_01ffa724(0x266, &direction, &packet.vecPos);
        packet.nFlags = 8;
        packet.nKindMask = (pDef->nClass == 0x1b) ? 0x80 : 8;
        packet.nBase = pActor->nHp >> 1;
        packet.nDamage = 0;
        packet.nId = pChest->nOpener;
        packet.pNode = pNode;
        packet.nStrength = 100;
        func_ov107_020c5cfc(pActor, 0, &packet);
        pChest->nPushedMask2 |= 1 << nPlayer;
    }
    return 1;
}
