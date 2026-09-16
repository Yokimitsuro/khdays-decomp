/* func_ov016_020822e0 -- Ov016_HazardStart: start handler of the hazard.  Takes a copy of the
 * position (+0xe0), binds the model node (+0x2c, 0202b930 mode 1 / 4 on the definition's model
 * resource, ov002 0206da70) and puts it at that position (0202b450 on the transform +0x38);
 * copies the facing (+0x18) into the node (+0xb8, flag bit 5 of +0x3c) unless it already has
 * one (bit 5 of +0x38); reads the on/off state from bit 1 of the hazard's GameState field into
 * +0x2b8 and applies it through Ov016_HazardSetState (020821f8, without spawning); enables the
 * model node (0202bedc) only if the GameState bit 0 is set; and requests the drop resource
 * pair (0203355c) when the definition has a drop slot (def +0x68 >= 0). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016HazardDef {
    u8 pad_00[0x58];
    char szModel[0x10];       /* 0x58 */
    short nDropSlot;          /* 0x68 */
} Ov016HazardDef;

typedef struct Ov016Hazard {
    u8 pad_000[0x8];
    Ov016HazardDef *pDef;     /* 0x08 */
    u8 pad_00c[0x8];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  pad_017;
    u16 nFacing;              /* 0x18 */
    u8  pad_01a[0x2c - 0x1a];
    u8  renderNode[0x38 - 0x2c]; /* 0x2c */
    u32 nNodeFlagsA;          /* 0x38: bit 5 = facing set; the transform */
    u16 nNodeFlagsB;          /* 0x3c: the model node */
    u8  pad_03e[0xb8 - 0x3e];
    u16 nNodeFacing;          /* 0xb8 */
    u8  pad_0ba[0xe0 - 0xba];
    VecFx32 position;         /* 0xe0 */
    u8  pad_0ec[0x2b8 - 0xec];
    int bOn;                  /* 0x2b8 */
} Ov016Hazard;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202b930(void *pNode, void *pEntry, int nA, int nB); /* bind a model node */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);         /* Actor_SetVecAndSyncChild */
extern int   func_020235d0(u16 nField, u8 nBit);                     /* GameState_GetField */
extern void  func_ov016_020821f8(Ov016Hazard *pSelf, int bState, int bSpawn); /* Ov016_HazardSetState */
extern void  func_0202bedc(void *pNode, int nFlag);                  /* Obj_SetFlagBit3 */
extern void  func_0203355c(int nId);                                 /* Res_RequestIdPair */

void func_ov016_020822e0(Ov016Hazard *pSelf)
{
    VecFx32 position;
    Ov016HazardDef *pDef;
    u16 nFacing;

    pDef = pSelf->pDef;
    position = pSelf->position;
    func_0202b930(pSelf->renderNode, func_ov002_0206da70(pDef->szModel), 1, 4);
    func_0202b450(&pSelf->nNodeFlagsA, &position);
    nFacing = pSelf->nFacing;
    if ((pSelf->nNodeFlagsA & 0x20) == 0) {
        pSelf->nNodeFacing = nFacing;
        pSelf->nNodeFlagsB |= 0x20;
    }
    pSelf->bOn = ((u16)((func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 0xfffe) >> 1) & 1) != 0;
    func_ov016_020821f8(pSelf, pSelf->bOn, 0);
    func_0202bedc(pSelf->renderNode, (func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 1) != 0);
    if (pDef->nDropSlot >= 0) {
        func_0203355c(pDef->nDropSlot);
    }
}
