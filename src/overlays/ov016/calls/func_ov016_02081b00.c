/* func_ov016_02081b00 -- Ov016_KickableHit: hit handler of the kickable (a player touching it).
 * A kickable that is not in the room (bit 3 of +0x12), one hidden by its taken flag (bit 1 of
 * its GameState field, unless its bit is 1), one whose kick message is still unacknowledged
 * (sync flag bit 4 of +0x61c) or a hit with bit 3 of its flags answers 8; a kickable with a
 * kick pending (bit 8 of +0x464) answers 1.  Otherwise the touch position is pulled towards
 * the player (ov002 0207c948, radius 0x400) when the hit asks for it (bit 2) and spread by the
 * kind row's length / step (ov002 0207c9d8 on the 02082748 table), and a type-2 kick message
 * (kind 0x14) carrying the position, the player (7 bits) and bit 5 of the hit flags is queued
 * on the piece (ov002 020766e0); once accepted the ack mask (+0x61d) is cleared and sync flag
 * bit 4 raised.  Answers 0. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016HitInfo {
    VecFx32 position;         /* 0x00 */
    char nPlayer;             /* 0x0c */
    u8   pad_0d[7];
    int  nFlags;              /* 0x14: bit 2 pull towards the player, bit 3 no kick, bit 5 */
} Ov016HitInfo;

typedef struct Ov016KickMessage {
    u8   nType;               /* 0x00: 2 */
    u8   pad_01[3];
    VecFx32 position;         /* 0x04 */
    char nPlayer : 7;         /* 0x10 */
    char bFlag : 1;
    u8   pad_11[3];
} Ov016KickMessage;

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

typedef struct Ov016Kickable {
    u8   pad_000[8];
    Ov016KickableDef *pDef;   /* 0x008 */
    u8   pad_00c[6];
    u16  nPieceFlags;         /* 0x012: bit 3 in the room */
    u16  nStateField;         /* 0x014: GameState field */
    u8   nStateBit;           /* 0x016 */
    u8   pad_017[0x464 - 0x17];
    u16  nKickFlags;          /* 0x464: bit 8 kick pending */
    u8   pad_466[0x61c - 0x466];
    u8   nSyncFlags;          /* 0x61c: bit 4 kick message unacknowledged */
    u8   nAckMask;            /* 0x61d */
} Ov016Kickable;

extern int  func_020235d0(u16 nField, u8 nBit);                                  /* GameState_GetField */
extern void func_ov002_0207c948(void *pPiece, Ov016HitInfo *pHit, int nRange, VecFx32 *pOut); /* pull a spot towards its member */
extern void func_ov002_0207c9d8(VecFx32 *pDir, int nLength, int nStep, VecFx32 *pOut);      /* spread offset */
extern int  func_ov002_020766e0(void *pPiece, void *pMessage, int nKind);        /* queue a message on the piece */
extern Ov016KickableKindRow data_ov016_02082748[];                               /* per-kind rows */

int func_ov016_02081b00(Ov016Kickable *pSelf, Ov016HitInfo *pHit)
{
    VecFx32 position;
    VecFx32 spread;
    Ov016KickMessage kick;
    Ov016KickableDef *pDef;
    int bTaken;

    pDef = pSelf->pDef;
    position = pHit->position;
    if ((pSelf->nPieceFlags & 8) == 0) {
        return 8;
    }
    if (pSelf->nStateBit == 1) {
        bTaken = 0;
    } else {
        bTaken = (u16)((func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 0xfffe) >> 1) & 1;
    }
    if (bTaken != 0) {
        return 8;
    }
    if (pSelf->nKickFlags & 0x100) {
        return 1;
    }
    if (pSelf->nSyncFlags & 0x10) {
        return 8;
    }
    if (pHit->nFlags & 8) {
        return 8;
    }
    if (pHit->nFlags & 4) {
        func_ov002_0207c948(pSelf, pHit, 0x400, &position);
    }
    spread = position;
    func_ov002_0207c9d8(&spread, data_ov016_02082748[pDef->nKind].nLength, data_ov016_02082748[pDef->nKind].nStep, &position);
    kick.nType = 2;
    kick.nPlayer = pHit->nPlayer;
    kick.bFlag = (pHit->nFlags & 0x20) != 0;
    kick.position = position;
    if (func_ov002_020766e0(pSelf, &kick, 0x14) != 0) {
        pSelf->nAckMask = 0;
        pSelf->nSyncFlags |= 0x10;
    }
    return 0;
}
