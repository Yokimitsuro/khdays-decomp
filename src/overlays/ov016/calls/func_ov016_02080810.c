/* func_ov016_02080810 -- Ov016_FollowerCreate: take a follower piece from the class table (ov002
 * 02076a38), place its model node (+0x1c, ov002 0207c4c0 with kind 0x10 and no parameters),
 * give it unit scale (+0x19c) and the origin (0202b450 with the zero vector), then fill it: no
 * facing (+0x18), bucket (+0x10), the step function (+0xc = 02080480), the GameState field and
 * bit (+0x14 / +0x16), the range (+0x1ac), the hold duration in frames (+0x1b0 = seconds * 30),
 * track 0 (+0x1bf), timers cleared (+0x1b4, +0x1c0), the turn rate (+0x1c4), the player it
 * trails (+0x1c6), the initial angle 0x8000 (+0x1b8) and the cone (+0x1c8); finally register
 * the piece (02076480). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016FollowerDef Ov016FollowerDef;

typedef struct Ov016Follower {
    u8 pad_000[0xc];
    void *pfnStep;            /* 0x0c */
    u8  nBucket;              /* 0x10 */
    u8  pad_011[3];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  nField17;             /* 0x17 */
    u16 nFacing;              /* 0x18 */
    u8  pad_01a[2];
    u8  modelNode[0x28 - 0x1c]; /* 0x1c */
    u8  transform[0x19c - 0x28]; /* 0x28 */
    int nScale;               /* 0x19c */
    u8  pad_1a0[0xc];
    int nRange;               /* 0x1ac */
    int nDuration;            /* 0x1b0 */
    int nHoldTimer;           /* 0x1b4 */
    int nAngle;               /* 0x1b8 */
    u8  pad_1bc[3];
    u8  nTrack;               /* 0x1bf */
    int nField1c0;            /* 0x1c0 */
    u16 nTurnRate;            /* 0x1c4 */
    u8  nPlayer;              /* 0x1c6 */
    u8  pad_1c7;
    int nCone;                /* 0x1c8 */
} Ov016Follower;

extern Ov016Follower *func_ov002_02076a38(Ov016FollowerDef *pClass, int nSlot); /* take a piece from the class table */
extern int   func_ov002_0207c4c0(void *pPiece, void *pNode, int *pPlace, int nSlot, int nKind,
                                 int nParamA, int nParamB, int nParamC, int nFacing, int nFlag); /* place the node */
extern void  func_0202b450(void *pTransform, const VecFx32 *pVec);        /* Actor_SetVecAndSyncChild */
extern void  func_ov002_02076480(int nBucket, void *pPiece);              /* register the piece */
extern void *func_ov016_02080480(Ov016Follower *pSelf);                   /* Ov016_FollowerStep */
extern const VecFx32 data_02041dc8;                                       /* the zero vector */

Ov016Follower *func_ov016_02080810(Ov016FollowerDef *pClass, u16 nSlot, u8 nBucket, u16 nField, u8 nBit,
                                   int nPlayer, int nRange, int nSeconds, int nTurnRate, int nCone)
{
    Ov016Follower *pFollower;

    pFollower = func_ov002_02076a38(pClass, nSlot);
    func_ov002_0207c4c0(pFollower, pFollower->modelNode, 0, nSlot, 0x10, 0, 0, 0, 0, 1);
    pFollower->nScale = 0x1000;
    func_0202b450(pFollower->transform, &data_02041dc8);
    pFollower->nFacing = 0;
    pFollower->nBucket = nBucket;
    pFollower->pfnStep = (void *)func_ov016_02080480;
    pFollower->nStateField = nField;
    pFollower->nStateBit = nBit;
    pFollower->nField17 = 0;
    pFollower->nRange = nRange;
    pFollower->nDuration = nSeconds * 30;
    pFollower->nTrack = 0;
    pFollower->nField1c0 = 0;
    pFollower->nHoldTimer = 0;
    pFollower->nTurnRate = nTurnRate;
    pFollower->nPlayer = nPlayer;
    pFollower->nAngle = 0x8000;
    pFollower->nCone = nCone;
    func_ov002_02076480(nBucket, pFollower);
    return pFollower;
}
