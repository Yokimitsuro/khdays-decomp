/* func_ov016_02080b08 -- Ov016_BreakableStep: state function of an intact breakable.  While it
 * has not been hit (+0x2bc == 0) it watches the piece its drop key / argument name (+0x2c0 /
 * +0x2c4, ov002 0207679c): once that piece moves (02076d04 gives a velocity of non-zero length)
 * the breakable hits itself through its own hit handler (02080a14) with a hit record of kind
 * 4 from attacker 0xff; stays (0).  Once hit: the "in the room" bit (bit 3 of +0x12) is dropped
 * and the render node's resources released (0202bc30); a pending drop (+0x2bd) whose key and
 * argument are valid launches that piece with a record {4, 0, 0, -0x200, 0} at +0x2c8 (ov002
 * 02076dac).  Without a bound model (bit 2 of +0x12) the piece retires (ov002 02076bd8) to the
 * terminal state (ov002 0207cea4).  Otherwise the definition's drop (slot / id at def +0x78 /
 * +0x7a) is spawned at the position (02033d0c) and: with a sequence (def +0x68) the sequence
 * node (+0x1b0) takes the position (+0x254) and facing (+0x22c), is rewound (ov002 0207c618) and
 * enabled -> state 02080d1c; else with break tracks (+0x2be) the next track (+0x2bf) is rewound
 * on the model node (+0x3c), enabled and drawn -> Ov016_BreakableBreakStep (02080d24); else the
 * piece retires -> terminal. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef void *Ov016StateFn(void *pPiece);

typedef struct Ov016HitRecord {
    int nWord00;              /* 0x00 */
    int nWord04;              /* 0x04 */
    int nWord08;              /* 0x08 */
    u8  nAttacker;            /* 0x0c */
    u8  nKind;                /* 0x0d */
    u8  pad_0e[2];
    int nWord10;              /* 0x10 */
    int nWord14;              /* 0x14 */
    int nWord18;              /* 0x18 */
} Ov016HitRecord;

typedef struct Ov016LaunchRecord {
    int nWord00;              /* 0x00 */
    int nWord04;              /* 0x04 */
    int nWord08;              /* 0x08 */
    int nWord0c;              /* 0x0c */
    int nWord10;              /* 0x10 */
    int nWord14;              /* 0x14 */
    int nWord18;              /* 0x18 */
} Ov016LaunchRecord;

typedef struct Ov016BreakableDef {
    u8 pad_00[0x68];
    char szSequence[0x10];    /* 0x68 */
    short nDropSlot;          /* 0x78 */
    short nDropId;            /* 0x7a */
} Ov016BreakableDef;

typedef struct Ov016Breakable {
    u8 pad_000[0x8];
    Ov016BreakableDef *pDef;  /* 0x08 */
    u8 pad_00c[0x6];
    u16 nPieceFlags;          /* 0x12: bit 2 = model bound, bit 3 = in the room */
    u8 pad_014[0x2c - 0x14];
    u8  renderNode[0x3c - 0x2c]; /* 0x2c */
    u16 nNodeFlagsB;          /* 0x3c: the model node */
    u8  pad_03e[0xb8 - 0x3e];
    u16 nNodeFacing;          /* 0xb8 */
    u8  pad_0ba[0xe0 - 0xba];
    VecFx32 position;         /* 0xe0 */
    u8  pad_0ec[0x1b0 - 0xec];
    u16 nSeqFlags;            /* 0x1b0: the sequence node */
    u8  pad_1b2[0x22c - 0x1b2];
    u16 nSeqFacing;           /* 0x22c */
    u8  pad_22e[0x254 - 0x22e];
    VecFx32 seqPosition;      /* 0x254 */
    u8  pad_260[0x2bc - 0x260];
    u8  bHit;                 /* 0x2bc */
    u8  bDropPending;         /* 0x2bd */
    u8  nFrames;              /* 0x2be */
    u8  nTrack;               /* 0x2bf */
    int nDropKey;             /* 0x2c0 */
    int nDropArg;             /* 0x2c4 */
    Ov016LaunchRecord launch; /* 0x2c8 */
} Ov016Breakable;

extern void  func_0202bc30(void *pNode);                              /* release the node's resources */
extern void *func_ov002_0207679c(int nKey, u16 nArg);                 /* resolve a pickup piece */
extern int   func_ov002_02076dac(void *pPiece, Ov016LaunchRecord *pRecord); /* deliver a hit record */
extern void  func_ov002_02076bd8(void *pPiece, int nMode);            /* retire a piece */
extern int   func_02033d0c(int nSlot, int nId, VecFx32 *pPos, u16 nFlags); /* Slot_Spawn */
extern void  func_ov002_0207c618(void *pNode, int nTrack, int nFrame); /* rewind a sequence */
extern void  func_0202af1c(void *pNode);                              /* SceneNode_Enable */
extern void  func_0202aa9c(void *pNode);                              /* Scene_DrawNode */
extern VecFx32 *func_ov002_02076d04(void *pPiece);                    /* a piece's velocity */
extern int   VEC_Mag(VecFx32 *pVec);
extern int   func_ov016_02080a14(Ov016Breakable *pSelf, Ov016HitRecord *pHit); /* Ov016_BreakableHit */
extern Ov016StateFn func_ov002_0207cea4;                              /* terminal state */
extern Ov016StateFn func_ov016_02080d1c;                              /* sequence playing state */
extern Ov016StateFn func_ov016_02080d24;                              /* Ov016_BreakableBreakStep */

Ov016StateFn *func_ov016_02080b08(Ov016Breakable *pSelf)
{
    Ov016HitRecord hit;
    Ov016BreakableDef *pDef;
    void *pDrop;
    VecFx32 *pVelocity;

    pDef = pSelf->pDef;
    if (pSelf->bHit != 0) {
        pSelf->nPieceFlags &= ~8;
        func_0202bc30(pSelf->renderNode);
        if (pSelf->bDropPending != 0) {
            if (pSelf->nDropKey >= 0 && pSelf->nDropArg >= 0
                && (pDrop = func_ov002_0207679c(pSelf->nDropKey & 0xff, pSelf->nDropArg & 0xffff)) != 0) {
                pSelf->launch.nWord14 = 4;
                pSelf->launch.nWord18 = 0;
                pSelf->launch.nWord00 = 0;
                pSelf->launch.nWord04 = -0x200;
                pSelf->launch.nWord08 = 0;
                func_ov002_02076dac(pDrop, &pSelf->launch);
            }
        }
        if ((pSelf->nPieceFlags & 4) == 0) {
            func_ov002_02076bd8(pSelf, 0);
            return func_ov002_0207cea4;
        }
        if (pDef->nDropSlot >= 0 && pDef->nDropId >= 0) {
            func_02033d0c(pDef->nDropSlot, pDef->nDropId, &pSelf->position, 0);
        }
        if (pDef->szSequence[0] != 0) {
            pSelf->seqPosition = pSelf->position;
            pSelf->nSeqFacing = pSelf->nNodeFacing;
            pSelf->nSeqFlags |= 0x20;
            func_ov002_0207c618(&pSelf->nSeqFlags, 0, 0);
            func_0202af1c(&pSelf->nSeqFlags);
            return func_ov016_02080d1c;
        }
        if (pSelf->nFrames != 0) {
            pSelf->nTrack++;
            func_ov002_0207c618(&pSelf->nNodeFlagsB, pSelf->nTrack, 0);
            func_0202af1c(&pSelf->nNodeFlagsB);
            func_0202aa9c(&pSelf->nNodeFlagsB);
            return func_ov016_02080d24;
        }
        func_ov002_02076bd8(pSelf, 0);
        return func_ov002_0207cea4;
    } else {
        pDrop = func_ov002_0207679c(pSelf->nDropKey & 0xff, pSelf->nDropArg & 0xffff);
        if (pDrop != 0 && (pVelocity = func_ov002_02076d04(pDrop)) != 0 && VEC_Mag(pVelocity) > 0) {
            hit.nAttacker = 0xff;
            hit.nWord10 = 0;
            hit.nWord14 = 4;
            hit.nWord18 = 0;
            hit.nWord00 = 0;
            hit.nWord04 = 0;
            hit.nWord08 = 0;
            hit.nKind = 4;
            func_ov016_02080a14(pSelf, &hit);
        }
    }
    return 0;
}
