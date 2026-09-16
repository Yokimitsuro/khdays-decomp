/* func_ov016_02080ec0 -- Ov016_BreakableCreate: take a breakable piece from the class table
 * (ov002 02076a38), place its render node (+0x2c, ov002 0207c4c0 kind 3 with the class's four
 * placement parameters and the facing), work out the start position (ov002 0207c53c), set
 * the position (0202b450) and copy the facing into the node (+0xb8, flag bit 5 of +0x3c)
 * unless it already has one; then fill the piece: facing (+0x18), start position (+0x1c),
 * +0x28 = 0, state 0 (+0x2b8) and the four state bytes (+0x2bc..+0x2bf), the drop key and
 * argument (+0x2c0 / +0x2c4), bucket (+0x10), the step function (+0xc = 02080b08), bit 3 of
 * the piece flags (+0x12), the GameState field / bit (+0x14 / +0x16); set binding byte 1 of
 * the node's +0x148 block to 3 (02029438) and register the piece (02076480). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016BreakableDef {
    u8 pad_00[0x84];
    int nPlaceB;              /* 0x84 */
    int nPlaceC;              /* 0x88 */
    int nPlaceD;              /* 0x8c */
} Ov016BreakableDef;

typedef struct Ov016Breakable {
    u8 pad_000[0xc];
    void *pfnStep;            /* 0x0c: state function */
    u8  nBucket;              /* 0x10 */
    u8  pad_011;
    u16 nPieceFlags;          /* 0x12 */
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  nField17;             /* 0x17 */
    short nFacing;            /* 0x18 */
    u8  pad_01a[2];
    VecFx32 start;            /* 0x1c */
    int nField28;             /* 0x28 */
    u8  renderNode[0x38 - 0x2c]; /* 0x2c */
    u32 nNodeFlagsA;          /* 0x38: bit 5 = facing set */
    u16 nNodeFlagsB;          /* 0x3c */
    u8  pad_03e[0xb8 - 0x3e];
    short nNodeFacing;        /* 0xb8 */
    u8  pad_0ba[0x148 - 0xba];
    u8  binding[0x2b8 - 0x148]; /* 0x148 */
    int nState;               /* 0x2b8 */
    u8  bHit;                 /* 0x2bc */
    u8  bDropPending;         /* 0x2bd */
    u8  bActive;              /* 0x2be */
    u8  nTrack;               /* 0x2bf */
    int nDropKey;             /* 0x2c0 */
    int nDropArg;             /* 0x2c4 */
} Ov016Breakable;

extern Ov016Breakable *func_ov002_02076a38(Ov016BreakableDef *pClass, int nSlot); /* take a piece from the class table */
extern int   func_ov002_0207c4c0(void *pPiece, void *pNode, int *pPlace, int nSlot, int nKind,
                                 int nParamA, int nParamB, int nParamC, int nFacing, int nFlag); /* place the node */
extern void  func_ov002_0207c53c(VecFx32 *pOut, VecFx32 *pPos, int *pPlace);  /* start position */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);              /* Actor_SetVecAndSyncChild */
extern void  func_02029438(void *pBlock, int nIndex, u8 nValue);          /* Actor_SetBindingByte */
extern void  func_ov002_02076480(int nBucket, void *pPiece);              /* register the piece */
extern void *func_ov016_02080b08(Ov016Breakable *pSelf);                  /* Ov016_BreakableStep */

Ov016Breakable *func_ov016_02080ec0(Ov016BreakableDef *pClass, u16 nSlot, u8 nBucket, VecFx32 *pPos, short nFacing,
                                    u16 nField, u8 nBit, int nDropKey, int nDropArg)
{
    int aPlace[5];
    VecFx32 start;
    Ov016Breakable *pPiece;
    int nYaw;

    pPiece = func_ov002_02076a38(pClass, nSlot);
    nYaw = nFacing;
    func_ov002_0207c4c0(pPiece, pPiece->renderNode, aPlace, nSlot, 3, pClass->nPlaceB, pClass->nPlaceC, pClass->nPlaceD, nYaw, 1);
    func_ov002_0207c53c(&start, pPos, aPlace);
    func_0202b450(&pPiece->nNodeFlagsA, pPos);
    if ((pPiece->nNodeFlagsA & 0x20) == 0) {
        pPiece->nNodeFacing = nYaw;
        pPiece->nNodeFlagsB |= 0x20;
    }
    pPiece->nFacing = nFacing;
    pPiece->start = start;
    pPiece->nField28 = 0;
    pPiece->nState = 0;
    pPiece->bHit = 0;
    pPiece->bDropPending = 0;
    pPiece->nTrack = 0;
    pPiece->bActive = 0;
    pPiece->nDropKey = nDropKey;
    pPiece->nDropArg = nDropArg;
    pPiece->nBucket = nBucket;
    pPiece->pfnStep = (void *)func_ov016_02080b08;
    pPiece->nPieceFlags |= 8;
    pPiece->nStateField = nField;
    pPiece->nStateBit = nBit;
    pPiece->nField17 = 0;
    func_02029438(pPiece->binding, 1, 3);
    func_ov002_02076480(nBucket, pPiece);
    return pPiece;
}
