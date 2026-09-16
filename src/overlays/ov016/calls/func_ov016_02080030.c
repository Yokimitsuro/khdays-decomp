/* func_ov016_02080030 -- Ov016_FollowerStart: when the definition names a model (def +0x58),
 * bind the model node (+0x1c, 0202b930 mode 1 / 4, ov002 0206da70 resolves the name), put it
 * at the rest position (+0xd0, 0202b450), copy the facing (+0x18) into the node (+0xa8, flag
 * bit 5 of +0x2c) unless it already has one (bit 5 of +0x28), flag the piece (bit 2 of +0x12),
 * rewind the sequence to the track byte (+0x1bf, ov002 0207c618 frame 0), disable the node
 * (0202af2c) and enable it (0202bedc) only if the follower's GameState bit is set. The hold
 * timer (+0x1b4) is reset either way. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016FollowerDef {
    u8 pad_00[0x58];
    char szModel[0x10];       /* 0x58 */
} Ov016FollowerDef;

typedef struct Ov016Follower {
    u8 pad_000[0x8];
    Ov016FollowerDef *pDef;   /* 0x08 */
    u8 pad_00c[0x6];
    u16 nPieceFlags;          /* 0x12 */
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  pad_017;
    u16 nFacing;              /* 0x18 */
    u8  pad_01a[2];
    u8  modelNode[0x28 - 0x1c]; /* 0x1c */
    u32 nNodeFlagsA;          /* 0x28: bit 5 = facing set */
    u16 nNodeFlagsB;          /* 0x2c */
    u8  pad_02e[0xa8 - 0x2e];
    u16 nNodeFacing;          /* 0xa8 */
    u8  pad_0aa[0xd0 - 0xaa];
    VecFx32 rest;             /* 0xd0 */
    u8  pad_0dc[0x1b4 - 0xdc];
    int nHoldTimer;           /* 0x1b4 */
    u8  pad_1b8[0x1bf - 0x1b8];
    signed char nTrack;       /* 0x1bf */
} Ov016Follower;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202b930(void *pNode, void *pEntry, int nA, int nB); /* bind a model node */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);          /* Actor_SetVecAndSyncChild */
extern void  func_ov002_0207c618(void *pNode, int nTrack, int nFrame); /* rewind a sequence */
extern void  func_0202af2c(void *pNode);                              /* SceneNode_Disable */
extern int   func_020235d0(u16 nField, u8 nBit);                      /* GameState_GetField */
extern void  func_0202bedc(void *pNode, int nFlag);                   /* Obj_SetFlagBit3 */

void func_ov016_02080030(Ov016Follower *pSelf)
{
    VecFx32 rest;
    Ov016FollowerDef *pDef;
    u16 nFacing;

    pDef = pSelf->pDef;
    if (pDef->szModel[0] != 0) {
        rest = pSelf->rest;
        func_0202b930(pSelf->modelNode, func_ov002_0206da70(pDef->szModel), 1, 4);
        func_0202b450(&pSelf->nNodeFlagsA, &rest);
        nFacing = pSelf->nFacing;
        if ((pSelf->nNodeFlagsA & 0x20) == 0) {
            pSelf->nNodeFacing = nFacing;
            pSelf->nNodeFlagsB |= 0x20;
        }
        pSelf->nPieceFlags |= 4;
        func_ov002_0207c618(&pSelf->nNodeFlagsB, pSelf->nTrack, 0);
        func_0202af2c(&pSelf->nNodeFlagsB);
        func_0202bedc(pSelf->modelNode, (func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 1) != 0);
    }
    pSelf->nHoldTimer = 0;
}
