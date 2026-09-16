/* func_ov016_02081c34 -- Ov016_KickableTargetPosition: the position a player may aim a kick
 * at, or 0.  The kickable must be switched on (bit 0 of its GameState field), have no kick
 * pending (kick flag bit 8 of +0x464) and be in the room (bit 3 of +0x12); a kickable whose
 * GameState bit is 1 is always available, any other keeps a "taken" flag in bit 1 of its field
 * that hides it.  Answers &position (+0x488). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016Kickable {
    u8 pad_000[0x12];
    u16 nPieceFlags;          /* 0x12: bit 3 = in the room */
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  pad_017[0x464 - 0x17];
    u16 nKickFlags;           /* 0x464: bit 8 = kick pending */
    u8  pad_466[0x488 - 0x466];
    VecFx32 position;         /* 0x488 */
} Ov016Kickable;

extern int func_020235d0(u16 nField, u8 nBit);                       /* GameState_GetField */

VecFx32 *func_ov016_02081c34(Ov016Kickable *pSelf)
{
    int bOn;
    int bTaken;

    bOn = (func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 1) != 0;
    if (bOn == 0 || (pSelf->nKickFlags & 0x100) != 0) {
        return 0;
    }
    if ((pSelf->nPieceFlags & 8) == 0) {
        return 0;
    }
    if (pSelf->nStateBit == 1) {
        bTaken = 0;
    } else {
        bTaken = (u16)((func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 0xfffe) >> 1) & 1;
    }
    if (bTaken != 0) {
        return 0;
    }
    return &pSelf->position;
}
