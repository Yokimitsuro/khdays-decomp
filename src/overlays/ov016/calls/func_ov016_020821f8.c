/* func_ov016_020821f8 -- Ov016_HazardSetState: switch the hazard on or off.  Writes the state
 * into bit 1 of the hazard's GameState field (GameState_GetField / SetField on +0x14 / +0x16),
 * rewinds the model node (+0x3c) to track 1 (on) or 0 (off) and disables it while the node is
 * bound (bit 2 of the node byte at +0x34); when asked to spawn (bSpawn) and the definition has
 * a drop slot (def +0x68) with an id for the new state (def +0x6a when switching on, +0x6c when
 * switching off) that drop is spawned at the hazard's position (+0xe0, 02033d0c). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016HazardDef {
    u8 pad_00[0x68];
    short nDropSlot;          /* 0x68 */
    short aDropId[2];         /* 0x6a: [0] when switched on, [1] when switched off */
} Ov016HazardDef;

typedef struct Ov016Hazard {
    u8 pad_000[0x8];
    Ov016HazardDef *pDef;     /* 0x08 */
    u8 pad_00c[0x8];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  pad_017[0x34 - 0x17];
    u8  nNodeFlags34;         /* 0x34: bit 2 = model bound */
    u8  pad_035[0x3c - 0x35];
    u16 nNodeFlagsB;          /* 0x3c: the model node */
    u8  pad_03e[0xe0 - 0x3e];
    VecFx32 position;         /* 0xe0 */
} Ov016Hazard;

extern int  func_020235d0(u16 nField, u8 nBit);                      /* GameState_GetField */
extern void func_020235e8(u16 nField, u8 nBit, u16 nValue);          /* GameState_SetField */
extern void func_ov002_0207c618(void *pNode, int nTrack, int nFrame); /* rewind a sequence */
extern void func_0202af2c(void *pNode);                              /* SceneNode_Disable */
extern int  func_02033d0c(int nSlot, int nId, VecFx32 *pPos, u16 nFlags); /* Slot_Spawn */

void func_ov016_020821f8(Ov016Hazard *pSelf, int bState, int bSpawn)
{
    Ov016HazardDef *pDef;
    int nState;
    int nTrack;
    u16 nOn;

    nTrack = (bState != 0);
    pDef = pSelf->pDef;
    nOn = (bState ? 1 : 0);
    nState = func_020235d0(pSelf->nStateField, pSelf->nStateBit);
    func_020235e8(pSelf->nStateField, pSelf->nStateBit, (nOn << 1) | (nState & 0xffff0001));
    if (pSelf->nNodeFlags34 & 4) {
        func_ov002_0207c618(&pSelf->nNodeFlagsB, nTrack, 0);
        func_0202af2c(&pSelf->nNodeFlagsB);
    }
    if (bSpawn && pDef->nDropSlot >= 0 && pDef->aDropId[bState == 0] >= 0) {
        func_02033d0c(pDef->nDropSlot, pDef->aDropId[bState == 0], &pSelf->position, 0);
    }
}
