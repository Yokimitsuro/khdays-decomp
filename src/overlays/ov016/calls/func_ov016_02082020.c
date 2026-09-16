/* func_ov016_02082020 -- Ov016_KickableCreate: take a kickable piece from the class table (ov002
 * 02076a38), place its render node (+0x498, ov002 0207c4c0 with the class's kind byte, three
 * placement parameters and the facing), work out the start position (ov002 0207c53c), set the
 * position (0202b450 on the transform at +0x4a4) and fill the piece: facing (+0x18), position
 * (+0x488) and ground height (+0x494), GameState field / bit, sync flags (+0x61c), bucket, the
 * kind row's step function (+0xc, table at 02082748, 0x14 bytes per kind), piece flags bits 3
 * and 6, the home (+0x634 from +0x54c) and target (+0x474 from the home) positions, the second
 * field / bit pair (+0x630 / +0x632), the kind row's two speeds (+0x1c / +0x1e), a body
 * (0202d968 on +0x24 from the transform), the zero velocity (+0x64c); kind 2 outside a session
 * (session bits & 4 clear) starts in mode 2 (+0x20); kinds whose byte in the 02082740 table is
 * not -1 mark the bucket with it (ov002 02076968); then register the piece (02076480). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016KickableKindRow {
    void *pfnStep;            /* 0x00 */
    int  nParamA;             /* 0x04 */
    int  nParamB;             /* 0x08 */
    short nSpeedA;            /* 0x0c */
    short nSpeedB;            /* 0x0e */
    short nSpeedC;            /* 0x10 */
    short nPad12;             /* 0x12 */
} Ov016KickableKindRow;

typedef struct Ov016KickableDef {
    u8 pad_00[0x6c];
    s8  nNodeKind;            /* 0x6c */
    u8  pad_6d[3];
    int nPlaceA;              /* 0x70 */
    int nPlaceB;              /* 0x74 */
    int nPlaceC;              /* 0x78 */
    u8  nKind;                /* 0x7c */
} Ov016KickableDef;

typedef struct Ov016Kickable {
    u8 pad_000[0xc];
    void *pfnStep;            /* 0x0c */
    u8  nBucket;              /* 0x10 */
    u8  pad_011;
    u16 nPieceFlags;          /* 0x12 */
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  nField17;             /* 0x17 */
    short nFacing;            /* 0x18 */
    u8  pad_01a[2];
    u16 nSpeedA;              /* 0x1c */
    u16 nSpeedB;              /* 0x1e */
    u8  nMode;                /* 0x20 */
    u8  pad_021[3];
    u8  body[0x464 - 0x24];   /* 0x24 */
    u16 nKickFlags;           /* 0x464 */
    u8  pad_466[2];
    int nWord468;             /* 0x468 */
    int nWord46c;             /* 0x46c */
    int nWord470;             /* 0x470 */
    VecFx32 target;           /* 0x474 */
    int nWord480;             /* 0x480 */
    int nWord484;             /* 0x484 */
    VecFx32 position;         /* 0x488 */
    int nGround;              /* 0x494 */
    u8  renderNode[0x4a4 - 0x498]; /* 0x498 */
    u8  transform[0x54c - 0x4a4];  /* 0x4a4 */
    VecFx32 rest;             /* 0x54c */
    u8  pad_558[0x61c - 0x558];
    u8  nSyncFlags;           /* 0x61c */
    u8  nAckMask;             /* 0x61d */
    u8  nByte61e;             /* 0x61e */
    u8  pad_61f;
    int nWord620;             /* 0x620 */
    int nWord624;             /* 0x624 */
    u8  pad_628[4];
    int nWord62c;             /* 0x62c */
    u16 nField2;              /* 0x630 */
    u8  nBit2;                /* 0x632 */
    u8  pad_633;
    VecFx32 home;             /* 0x634 */
    VecFx32 velocity;         /* 0x640 */
    VecFx32 vec64c;           /* 0x64c */
} Ov016Kickable;

extern Ov016Kickable *func_ov002_02076a38(Ov016KickableDef *pClass, int nSlot); /* take a piece from the class table */
extern int   func_ov002_0207c4c0(void *pPiece, void *pNode, int *pPlace, int nSlot, int nKind,
                                 int nParamA, int nParamB, int nParamC, int nFacing, int nFlag); /* place the node */
extern void  func_ov002_0207c53c(VecFx32 *pOut, VecFx32 *pPos, int *pPlace);  /* start position */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);              /* Actor_SetVecAndSyncChild */
extern void  func_0202d968(void *pBody, void *pRecord);                   /* construct an actor body */
extern void  func_ov002_02076968(int nBucket, int nMode);
extern void  func_ov002_02076480(int nBucket, void *pPiece);              /* register the piece */
extern Ov016KickableKindRow data_ov016_02082748[];                        /* per-kind rows */
extern const s8 data_ov016_02082740[];                                    /* per-kind bucket marks */
extern const VecFx32 data_02041dc8;                                       /* the zero vector */
extern u8    data_0204c240;                                               /* session bits */

Ov016Kickable *func_ov016_02082020(Ov016KickableDef *pClass, u16 nSlot, u8 nBucket, VecFx32 *pPos, short nFacing,
                                   u16 nField, u8 nBit, u16 nField2, u8 nBit2)
{
    VecFx32 start;
    int aPlace[5];
    Ov016Kickable *pPiece;
    int nMark;

    pPiece = func_ov002_02076a38(pClass, nSlot);
    func_ov002_0207c4c0(pPiece, pPiece->renderNode, aPlace, nSlot, pClass->nNodeKind, pClass->nPlaceA, pClass->nPlaceB, pClass->nPlaceC, nFacing, 1);
    func_ov002_0207c53c(&start, pPos, aPlace);
    func_0202b450(pPiece->transform, pPos);
    pPiece->nFacing = nFacing;
    pPiece->position = *pPos;
    pPiece->nGround = aPlace[2];
    pPiece->nStateField = nField;
    pPiece->nStateBit = nBit;
    pPiece->nSyncFlags = 0;
    pPiece->nBucket = nBucket;
    pPiece->pfnStep = data_ov016_02082748[pClass->nKind].pfnStep;
    pPiece->nPieceFlags |= 8;
    pPiece->nPieceFlags |= 0x40;
    pPiece->nField17 = 0;
    pPiece->home = pPiece->rest;
    pPiece->nByte61e = 0;
    pPiece->nWord624 = 0;
    pPiece->nWord620 = 0;
    pPiece->nField2 = nField2;
    pPiece->nBit2 = nBit2;
    pPiece->nWord62c = 0;
    func_0202d968(pPiece->body, pPiece->transform);
    pPiece->nSpeedA = data_ov016_02082748[pClass->nKind].nSpeedA;
    pPiece->nSpeedB = data_ov016_02082748[pClass->nKind].nSpeedC;
    pPiece->nKickFlags = 0;
    pPiece->nWord470 = 0;
    pPiece->nWord46c = pPiece->nWord470;
    pPiece->nWord468 = pPiece->nWord46c;
    pPiece->target = pPiece->home;
    pPiece->nWord480 = 0;
    pPiece->nWord484 = 0;
    pPiece->nMode = 0;
    pPiece->vec64c = data_02041dc8;
    if (pClass->nKind == 2 && (data_0204c240 & 4) == 0) {
        pPiece->nMode = 2;
    }
    nMark = data_ov016_02082740[pClass->nKind];
    if (nMark >= 0) {
        func_ov002_02076968(nBucket, nMark);
    }
    func_ov002_02076480(nBucket, pPiece);
    return pPiece;
}
