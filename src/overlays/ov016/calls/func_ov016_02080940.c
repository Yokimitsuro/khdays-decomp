/* func_ov016_02080940 -- Ov016_BreakableStart: bind the model node (+0x2c, 0202b930 mode 1 / 4
 * on the definition's model resource, ov002 0206da70), copy the facing (+0x18) into it (+0xb8,
 * flag bit 5 of +0x3c) unless it already has one (bit 5 of +0x38); when the definition names a
 * sequence (def +0x68) bind the sequence node (+0x1b0, 0202a634), otherwise remember the model's
 * frame count (ov002 0207c6c0 on +0x3c) as the number of break frames (+0x2be); enable the model
 * node (0202bedc) only if the breakable's GameState bit is set; and request the drop resource
 * pair (0203355c) when the definition has a drop slot (def +0x78 >= 0). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov016BreakableDef {
    u8 pad_00[0x58];
    char szModel[0x10];       /* 0x58 */
    char szSequence[0x10];    /* 0x68 */
    short nDropSlot;          /* 0x78 */
} Ov016BreakableDef;

typedef struct Ov016Breakable {
    u8 pad_000[0x8];
    Ov016BreakableDef *pDef;  /* 0x08 */
    u8 pad_00c[0x8];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  pad_017;
    u16 nFacing;              /* 0x18 */
    u8  pad_01a[0x2c - 0x1a];
    u8  renderNode[0x38 - 0x2c]; /* 0x2c */
    u32 nNodeFlagsA;          /* 0x38: bit 5 = facing set */
    u16 nNodeFlagsB;          /* 0x3c */
    u8  pad_03e[0xb8 - 0x3e];
    u16 nNodeFacing;          /* 0xb8 */
    u8  pad_0ba[0x1b0 - 0xba];
    u8  seqNode[0x2be - 0x1b0]; /* 0x1b0 */
    u8  nFrames;              /* 0x2be */
} Ov016Breakable;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202b930(void *pNode, void *pEntry, int nA, int nB); /* bind a model node */
extern void  func_0202a634(void *pNode, void *pEntry, int nA, int nB); /* RegisterSeqAndInit */
extern u8    func_ov002_0207c6c0(void *pNode);                        /* frame count of a node */
extern int   func_020235d0(u16 nField, u8 nBit);                      /* GameState_GetField */
extern void  func_0202bedc(void *pNode, int nFlag);                   /* Obj_SetFlagBit3 */
extern void  func_0203355c(int nId);                                  /* Res_RequestIdPair */

void func_ov016_02080940(Ov016Breakable *pSelf)
{
    Ov016BreakableDef *pDef;
    u16 nFacing;

    pDef = pSelf->pDef;
    func_0202b930(pSelf->renderNode, func_ov002_0206da70(pDef->szModel), 1, 4);
    nFacing = pSelf->nFacing;
    if ((pSelf->nNodeFlagsA & 0x20) == 0) {
        pSelf->nNodeFacing = nFacing;
        pSelf->nNodeFlagsB |= 0x20;
    }
    if (pDef->szSequence[0] != 0) {
        func_0202a634(pSelf->seqNode, func_ov002_0206da70(pDef->szSequence), 1, 4);
    } else {
        pSelf->nFrames = func_ov002_0207c6c0(&pSelf->nNodeFlagsB);
    }
    func_0202bedc(pSelf->renderNode, (func_020235d0(pSelf->nStateField, pSelf->nStateBit) & 1) != 0);
    if (pDef->nDropSlot >= 0) {
        func_0203355c(pDef->nDropSlot);
    }
}
