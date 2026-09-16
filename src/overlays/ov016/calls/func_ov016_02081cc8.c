/* func_ov016_02081cc8 -- Ov016_KickableQueryParamA: the definition's word at +0x68 while the
 * kickable's GameState bit is set and it is not locked (bit 8 of +0x464); else 0. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov016KickableDef {
    u8 pad_00[0x68];
    int nParam;               /* 0x68 */
} Ov016KickableDef;

typedef struct Ov016Kickable {
    u8 pad_000[0x8];
    Ov016KickableDef *pDef;       /* 0x08 */
    u8 pad_00c[0x8];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8 pad_017[0x464 - 0x17];
    u16 nDoorFlags;           /* 0x464: bit 8 = locked */
} Ov016Kickable;

extern int func_020235d0(u16 nField, u8 nBit);   /* GameState_GetField */

int func_ov016_02081cc8(Ov016Kickable *pSelf)
{
    Ov016KickableDef *pDef;
    int bOpen;

    pDef = pSelf->pDef;
    bOpen = (func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 1) != 0;
    if (bOpen == 0 || (pSelf->nDoorFlags & 0x100) != 0) {
        return 0;
    }
    return pDef->nParam;
}
