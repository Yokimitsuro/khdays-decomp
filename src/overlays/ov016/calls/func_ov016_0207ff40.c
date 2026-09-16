/* func_ov016_0207ff40 -- Ov016_LiftCreate: take a lift piece from the class table (ov002
 * 02076a38), place its render node (+0x2c, ov002 0207c4c0 with the class's two parameters,
 * height 0x1800 and the facing), set the position (0202b450) and copy the facing into the
 * node (+0xb8, flag bit 5 of +0x3c) unless it already has one (bit 5 of +0x38); then fill the
 * piece: facing (+0x18), bucket (+0x10), the state function table (+0xc = 0207fb34), the two
 * GameState field / bit pairs (+0x14 / +0x16 and +0x2e4 / +0x2e6), state 0 (+0x2b8), the
 * top / bottom heights, speed and wait (+0x2d4..+0x2e0) and the home position (+0x2e8);
 * finally mark the bucket (ov002 02076968 mode 1) and register the piece (02076480). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016LiftDef {
    u8 pad_00[0x68];
    int nParamA;              /* 0x68 */
    int nParamB;              /* 0x6c */
} Ov016LiftDef;

typedef struct Ov016Lift {
    u8 pad_000[0xc];
    void *pfnStep;            /* 0x0c: state function */
    u8  nBucket;              /* 0x10 */
    u8 pad_011[3];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  nField17;             /* 0x17 */
    short nFacing;            /* 0x18 */
    u8 pad_01a[0x2c - 0x1a];
    u8 renderNode[0x38 - 0x2c]; /* 0x2c */
    u32 nNodeFlagsA;          /* 0x38: bit 5 = facing set */
    u16 nNodeFlagsB;          /* 0x3c */
    u8 pad_03e[0xb8 - 0x3e];
    short nNodeFacing;        /* 0xb8 */
    u8 pad_0ba[0x2b8 - 0xba];
    u8  nState;               /* 0x2b8 */
    u8 pad_2b9[0x2d4 - 0x2b9];
    int nTop;                 /* 0x2d4 */
    int nBottom;              /* 0x2d8 */
    int nSpeed;               /* 0x2dc */
    int nWait;                /* 0x2e0 */
    u16 nTriggerField;        /* 0x2e4: GameState field that starts the ride */
    u8  nTriggerBit;          /* 0x2e6 */
    u8  pad_2e7;
    VecFx32 home;             /* 0x2e8 */
} Ov016Lift;

extern Ov016Lift *func_ov002_02076a38(Ov016LiftDef *pClass, int nSlot);   /* take a piece from the class table */
extern int   func_ov002_0207c4c0(void *pPiece, void *pNode, int *pPlace, int nSlot, int nKind,
                                 int nParamA, int nParamB, int nParamC, int nFacing, int nFlag); /* place the node */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);              /* Actor_SetVecAndSyncChild */
extern void  func_ov002_02076968(int nBucket, int nMode);
extern void  func_ov002_02076480(int nBucket, void *pPiece);              /* register the piece */
extern void *func_ov016_0207fb34(Ov016Lift *pSelf);                       /* Ov016_LiftStep */

Ov016Lift *func_ov016_0207ff40(Ov016LiftDef *pClass, u16 nSlot, u8 nBucket, VecFx32 *pPos, short nFacing,
                               u16 nField, u8 nBit, u16 nTriggerField, u8 nTriggerBit,
                               int nTop, int nBottom, int nSpeed, int nWait)
{
    int aPlace[5];
    Ov016Lift *pLift;
    int nYaw;

    pLift = func_ov002_02076a38(pClass, nSlot);
    nYaw = nFacing;
    func_ov002_0207c4c0(pLift, pLift->renderNode, aPlace, nSlot, 0, pClass->nParamA, pClass->nParamB, 0x1800, nYaw, 1);
    func_0202b450(&pLift->nNodeFlagsA, pPos);
    if ((pLift->nNodeFlagsA & 0x20) == 0) {
        pLift->nNodeFacing = nYaw;
        pLift->nNodeFlagsB |= 0x20;
    }
    pLift->nFacing = nFacing;
    pLift->nBucket = nBucket;
    pLift->pfnStep = (void *)func_ov016_0207fb34;
    pLift->nStateField = nField;
    pLift->nStateBit = nBit;
    pLift->nField17 = 0;
    pLift->nState = 0;
    pLift->nTop = nTop;
    pLift->nBottom = nBottom;
    pLift->nSpeed = nSpeed;
    pLift->nWait = nWait;
    pLift->nTriggerField = nTriggerField;
    pLift->nTriggerBit = nTriggerBit;
    pLift->home = *pPos;
    func_ov002_02076968(nBucket, 1);
    func_ov002_02076480(nBucket, pLift);
    return pLift;
}
