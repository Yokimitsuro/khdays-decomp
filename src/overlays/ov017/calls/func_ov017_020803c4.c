/* func_ov017_020803c4 -- Ov017_DepositCreate: creates a deposit piece (the multi-hit prize
 * object) from its class (ov002 02076a38): places the render node (+0x2c, ov002 0207c4c0
 * with the class's node kind +0x8c, its three placement shorts +0x8e..+0x92 and the facing),
 * works out the start position (ov002 0207c53c), puts the transform (+0x38) at pPos
 * (0202b450) and fills the piece: facing (+0x18), start (+0x1c), the placement height plus
 * 0x2000 (+0x28), the step function (+0xc = Ov017_DepositStep 0207fe2c), bucket, piece flags
 * 0xc8, the GameState field / bit (+0x14 / +0x16), +0x17 = 0, the hit bookkeeping cleared
 * (+0x4d8 hits, +0x4da hit state, +0x4db animation flags, +0x4dc cooldown), the maximum
 * number of hits (+0x4d9), both animation frames and lengths zeroed (+0x4c8..+0x4d4) and the
 * hit-count GameState field / bit (+0x4e0 / +0x4e2); registers the piece (ov002 02076480). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov017DepositDef {
    u8   pad_00[0x8c];
    char nNodeKind;           /* 0x8c */
    u8   pad_8d;
    short nPlaceA;            /* 0x8e */
    short nPlaceB;            /* 0x90 */
    short nPlaceC;            /* 0x92 */
} Ov017DepositDef;

typedef struct Ov017Deposit {
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
    VecFx32 start;            /* 0x01c */
    int  nTop;                /* 0x028 */
    u8   renderNode[0x38 - 0x2c]; /* 0x02c */
    u8   transform[0x4c8 - 0x38]; /* 0x038 */
    int  nMainFrame;          /* 0x4c8 */
    int  nMainLength;         /* 0x4cc */
    int  nCrackFrame;         /* 0x4d0 */
    int  nCrackLength;        /* 0x4d4 */
    u8   nHits;               /* 0x4d8 */
    u8   nMaxHits;            /* 0x4d9 */
    u8   nHitState;           /* 0x4da */
    u8   nAnimFlags;          /* 0x4db */
    int  nCooldown;           /* 0x4dc */
    u16  nHitField;           /* 0x4e0: GameState field holding the hit count */
    u8   nHitBit;             /* 0x4e2 */
} Ov017Deposit;

extern Ov017Deposit *func_ov002_02076a38(Ov017DepositDef *pClass, int nSlot); /* take a piece from the class table */
extern void  func_ov002_0207c4c0(void *pPiece, void *pNode, int *aPlace, int nSlot, int nKind, int nA, int nB, int nC, int nFacing, int nOne);
extern void  func_ov002_0207c53c(VecFx32 *pStart, VecFx32 *pPos, int *aPlace); /* start position from the placement */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);          /* Actor_SetVecAndSyncChild */
extern void  func_ov002_02076480(int nBucket, void *pPiece);          /* register the piece */
extern void *func_ov017_0207fe2c(Ov017Deposit *pSelf);                /* Ov017_DepositStep */

Ov017Deposit *func_ov017_020803c4(Ov017DepositDef *pClass, u16 nSlot, u8 nBucket, u16 nField, u8 nBit, u16 nHitField, u8 nHitBit, u16 nMaxHits, VecFx32 *pPos, short nFacing)
{
    VecFx32 start;
    int aPlace[5];
    Ov017Deposit *pPiece;

    pPiece = func_ov002_02076a38(pClass, nSlot);
    func_ov002_0207c4c0(pPiece, pPiece->renderNode, aPlace, nSlot, pClass->nNodeKind, pClass->nPlaceA, pClass->nPlaceB, pClass->nPlaceC, nFacing, 1);
    func_ov002_0207c53c(&start, pPos, aPlace);
    func_0202b450(pPiece->transform, pPos);
    pPiece->nFacing = nFacing;
    aPlace[2] += 0x2000;
    pPiece->start = start;
    pPiece->nTop = aPlace[2];
    pPiece->nBucket = nBucket;
    pPiece->pfnStep = (void *)func_ov017_0207fe2c;
    pPiece->nPieceFlags |= 0xc8;
    pPiece->nStateField = nField;
    pPiece->nStateBit = nBit;
    pPiece->nField17 = 0;
    pPiece->nAnimFlags = 0;
    pPiece->nCooldown = 0;
    pPiece->nHitState = 0;
    pPiece->nHits = 0;
    pPiece->nMaxHits = nMaxHits;
    pPiece->nMainLength = 0;
    pPiece->nMainFrame = 0;
    pPiece->nCrackLength = 0;
    pPiece->nCrackFrame = 0;
    pPiece->nHitField = nHitField;
    pPiece->nHitBit = nHitBit;
    func_ov002_02076480(nBucket, pPiece);
    return pPiece;
}
