/* func_ov016_020819e0 -- Ov016_KickableStart: start handler of the kickable.  Takes a copy of
 * the rest position (+0x54c), binds the model node (+0x498, 0202b930 mode 1 / 4 on the
 * definition's model resource, ov002 0206da70), copies the facing (+0x18) into the transform
 * (+0x524, flag bit 5 of +0x4a8) unless it already has one (bit 5 of +0x4a4), puts the transform
 * at the rest position (0202b450), enables the node (0202bedc) only if the kickable's GameState
 * bit is set, marks the model bound (bit 2 of +0x12) and plays the current track (+0x61e) with
 * its two animation words (+0x624 / +0x620) through Ov016_KickableSetAnim (020815e8). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016KickableDef {
    u8 pad_00[0x58];
    char szModel[0x10];       /* 0x58 */
} Ov016KickableDef;

typedef struct Ov016Kickable {
    u8 pad_000[0x8];
    Ov016KickableDef *pDef;   /* 0x08 */
    u8 pad_00c[0x6];
    u16 nPieceFlags;          /* 0x12: bit 2 = model bound */
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  pad_017;
    u16 nFacing;              /* 0x18 */
    u8  pad_01a[0x498 - 0x1a];
    u8  renderNode[0x4a4 - 0x498]; /* 0x498 */
    u32 nNodeFlagsA;          /* 0x4a4: bit 5 = facing set; the transform */
    u16 nNodeFlagsB;          /* 0x4a8 */
    u8  pad_4aa[0x524 - 0x4aa];
    u16 nNodeFacing;          /* 0x524 */
    u8  pad_526[0x54c - 0x526];
    VecFx32 rest;             /* 0x54c */
    u8  pad_558[0x61e - 0x558];
    char nTrack;              /* 0x61e */
    u8  pad_61f;
    int nAnimWord620;         /* 0x620 */
    int nAnimWord624;         /* 0x624 */
} Ov016Kickable;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202b930(void *pNode, void *pEntry, int nA, int nB); /* bind a model node */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);         /* Actor_SetVecAndSyncChild */
extern int   func_020235d0(u16 nField, u8 nBit);                     /* GameState_GetField */
extern void  func_0202bedc(void *pNode, int nFlag);                  /* Obj_SetFlagBit3 */
extern void  func_ov016_020815e8(Ov016Kickable *pSelf, int nTrack, int nWord624, int nWord620); /* Ov016_KickableSetAnim */

void func_ov016_020819e0(Ov016Kickable *pSelf)
{
    VecFx32 position;
    Ov016KickableDef *pDef;
    u16 nFacing;

    pDef = pSelf->pDef;
    position = pSelf->rest;
    func_0202b930(pSelf->renderNode, func_ov002_0206da70(pDef->szModel), 1, 4);
    nFacing = pSelf->nFacing;
    if ((pSelf->nNodeFlagsA & 0x20) == 0) {
        pSelf->nNodeFacing = nFacing;
        pSelf->nNodeFlagsB |= 0x20;
    }
    func_0202b450(&pSelf->nNodeFlagsA, &position);
    func_0202bedc(pSelf->renderNode, (func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 1) != 0);
    pSelf->nPieceFlags |= 4;
    func_ov016_020815e8(pSelf, pSelf->nTrack, pSelf->nAnimWord624, pSelf->nAnimWord620);
}
