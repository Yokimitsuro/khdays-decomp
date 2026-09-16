/* func_ov021_02080390 -- Ov021_PrizeBoxCreate: creates a prize box piece from its class (ov002
 * 02076a38): places the render node (+0x2c, ov002 0207c4c0 with the class's node kind +0x6c,
 * its three placement shorts +0x6e..+0x72 and the facing), works out the start position
 * (ov002 0207c53c), puts the transform (+0x38) at pPos (0202b450) and fills the piece: facing
 * (+0x18), start (+0x1c), the placement height (+0x28), the step function (+0xc =
 * Ov021_PrizeBoxStep 0207feec), bucket, piece flags 0x48, +0x17 = 0, the GameState field / bit
 * (+0x14 / +0x16), state 0, flags 0, track 0 with its length from the 02080f18 table (+0x1b4)
 * and frame 0, the slot (+0x1ba), no replay (+0x1bd) and no spawn id (+0x1bb = -1).  The host
 * gives the box its prize from the class's shuffled order (+0x1be = aOrder[slot]) and, for an
 * item prize (type 0), takes a spawn id from the low band (ov002 02077b30) and requests the
 * item's resources (ov002 0206cf4c); a peer waits for the prize (+0x1be = -1).  Registers the
 * piece (ov002 02076480) and, in mission 0x41d (ov002 0206b84c), marks the bucket (02076968
 * mode 1). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov021Prize {
    char  nType;              /* 0x00: 0 item, 1 munny, 2 keyed object, 3 nothing */
    u8    pad_01;
    short nValue;             /* 0x02 */
    u8    bFlag;              /* 0x04 */
    u8    pad_05;
} Ov021Prize;

typedef struct Ov021PrizeBoxDef {
    u8   pad_00[0x6c];
    s8   nNodeKind;           /* 0x6c */
    u8   pad_6d;
    short nPlaceA;            /* 0x6e */
    short nPlaceB;            /* 0x70 */
    short nPlaceC;            /* 0x72 */
    u8   pad_74[4];
    Ov021Prize aPrize[0x20];  /* 0x78 */
    s8   aOrder[0x20];        /* 0x138 */
} Ov021PrizeBoxDef;

typedef struct Ov021PrizeBox {
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
    u8   transform[0x1b0 - 0x38]; /* 0x038 */
    int  nFrame;              /* 0x1b0 */
    int  nLength;             /* 0x1b4 */
    u8   nState;              /* 0x1b8 */
    u8   nFlags;              /* 0x1b9 */
    char nSlot;               /* 0x1ba */
    char nSpawnId;            /* 0x1bb */
    char nTrack;              /* 0x1bc */
    char bReplay;             /* 0x1bd */
    char nPrize;              /* 0x1be */
} Ov021PrizeBox;

extern Ov021PrizeBox *func_ov002_02076a38(Ov021PrizeBoxDef *pClass, int nSlot); /* take a piece from the class table */
extern void  func_ov002_0207c4c0(void *pPiece, void *pNode, int *aPlace, int nSlot, int nKind, int nA, int nB, int nC, int nFacing, int nOne);
extern void  func_ov002_0207c53c(VecFx32 *pStart, VecFx32 *pPos, int *aPlace); /* start position from the placement */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);          /* Actor_SetVecAndSyncChild */
extern int   func_02030788(void);                                     /* Session_GetLocalPlayerIndex */
extern int   func_ov002_02077b30(void);                               /* take a spawn id from the low band */
extern void  func_ov002_0206cf4c(int nKey);                           /* request an item's resources */
extern void  func_ov002_02076480(int nBucket, void *pPiece);          /* register the piece */
extern int   func_ov002_0206b84c(void);                               /* the mission id */
extern void  func_ov002_02076968(int nBucket, int nMode);             /* mark the bucket */
extern void *func_ov021_0207feec(Ov021PrizeBox *pSelf);               /* Ov021_PrizeBoxStep */
extern const s8 data_ov021_02080f18[];                                /* track lengths in frames */

Ov021PrizeBox *func_ov021_02080390(Ov021PrizeBoxDef *pClass, u16 nSlot, u8 nBucket, u16 nField, u8 nBit, VecFx32 *pPos, short nFacing)
{
    VecFx32 start;
    int aPlace[5];
    Ov021PrizeBox *pPiece;

    pPiece = func_ov002_02076a38(pClass, nSlot);
    func_ov002_0207c4c0(pPiece, pPiece->renderNode, aPlace, nSlot, pClass->nNodeKind, pClass->nPlaceA, pClass->nPlaceB, pClass->nPlaceC, nFacing, 1);
    func_ov002_0207c53c(&start, pPos, aPlace);
    func_0202b450(pPiece->transform, pPos);
    pPiece->nFacing = nFacing;
    pPiece->start = start;
    pPiece->nTop = aPlace[2];
    pPiece->nBucket = nBucket;
    pPiece->pfnStep = (void *)func_ov021_0207feec;
    pPiece->nPieceFlags |= 0x48;
    pPiece->nField17 = 0;
    pPiece->nStateField = nField;
    pPiece->nStateBit = nBit;
    pPiece->nState = 0;
    pPiece->nFlags = 0;
    pPiece->nTrack = 0;
    pPiece->nLength = data_ov021_02080f18[pPiece->nTrack] << 12;
    pPiece->nFrame = 0;
    pPiece->nSlot = nSlot;
    pPiece->bReplay = 0;
    pPiece->nSpawnId = -1;
    if (func_02030788() == 0) {
        pPiece->nPrize = pClass->aOrder[pPiece->nSlot];
        if (pClass->aPrize[pPiece->nPrize].nType == 0) {
            pPiece->nSpawnId = func_ov002_02077b30();
            func_ov002_0206cf4c(pClass->aPrize[pPiece->nPrize].nValue);
        }
    } else {
        pPiece->nPrize = -1;
    }
    func_ov002_02076480(nBucket, pPiece);
    if (func_ov002_0206b84c() == 0x41d) {
        func_ov002_02076968(nBucket, 1);
    }
    return pPiece;
}
