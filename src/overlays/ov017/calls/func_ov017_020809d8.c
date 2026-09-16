/* func_ov017_020809d8 -- Ov017_ItemCreate: creates an item piece from its class (ov002
 * 02076a38) and fills it: facing (+0x18), position (+0x1c), +0x28 = 4, the item id (+0x1b6),
 * +0x1b0 = 0, spawn id -1 (+0x1b9), state 1 on a peer / 0 on the host (+0x1b4, 02030788),
 * the second GameState field / bit (+0x1ba / +0x1bc), bucket (+0x10), the step function
 * (+0xc = Ov017_ItemStep 02080720), piece flag bit 3, the GameState field / bit (+0x14 /
 * +0x16) and +0x17 = 1; then registers the piece (ov002 02076480). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov017Item {
    u8   pad_000[0xc];
    void *pfnStep;            /* 0x00c */
    u8   nBucket;             /* 0x010 */
    u8   pad_011;
    u16  nPieceFlags;         /* 0x012 */
    u16  nStateField;         /* 0x014: GameState field */
    u8   nStateBit;           /* 0x016 */
    u8   nField17;            /* 0x017 */
    short nFacing;            /* 0x018 */
    u8   pad_01a[2];
    VecFx32 position;         /* 0x01c */
    int  nWord28;             /* 0x028 */
    u8   pad_02c[0x1b0 - 0x2c];
    int  nTimer;              /* 0x1b0 */
    u8   nState;              /* 0x1b4 */
    u8   pad_1b5;
    u16  nItemId;             /* 0x1b6 */
    u8   nPlayer;             /* 0x1b8 */
    char nSpawnId;            /* 0x1b9 */
    u16  nTakenField;         /* 0x1ba: second GameState field */
    u8   nTakenBit;           /* 0x1bc */
} Ov017Item;

extern Ov017Item *func_ov002_02076a38(void *pClass, int nSlot);      /* take a piece from the class table */
extern int   func_02030788(void);                                    /* Session_GetLocalPlayerIndex */
extern void  func_ov002_02076480(int nBucket, void *pPiece);         /* register the piece */
extern void *func_ov017_02080720(Ov017Item *pSelf);                  /* Ov017_ItemStep */

void func_ov017_020809d8(void *pClass, u16 nSlot, u8 nBucket, VecFx32 *pPos, short nFacing, u16 nField, u8 nBit, u16 nTakenField, u8 nTakenBit, short nItemId)
{
    Ov017Item *pPiece;
    u8 nState;

    pPiece = func_ov002_02076a38(pClass, nSlot);
    pPiece->nFacing = nFacing;
    pPiece->position = *pPos;
    pPiece->nWord28 = 4;
    pPiece->nItemId = nItemId;
    pPiece->nTimer = 0;
    pPiece->nSpawnId = -1;
    switch (func_02030788()) {   /* host 0, any peer 1 (a switch: an if / else folds into the other branch order) */
    case 0:
        nState = 0;
        break;
    default:
        nState = 1;
        break;
    }
    pPiece->nState = nState;
    pPiece->nTakenField = nTakenField;
    pPiece->nTakenBit = nTakenBit;
    pPiece->nBucket = nBucket;
    pPiece->pfnStep = (void *)func_ov017_02080720;
    pPiece->nPieceFlags |= 8;
    pPiece->nStateField = nField;
    pPiece->nStateBit = nBit;
    pPiece->nField17 = 1;
    func_ov002_02076480(nBucket, pPiece);
}
