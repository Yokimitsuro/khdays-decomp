/* func_ov015_020801c8 -- Ov015_SpawnPickup: take a pickup piece of kind nKind from its class
 * table (ov002 02076a38) and set it up: the flag offset (+0x153) is the slot; an unresolved
 * mission-flag base in the class (+0x86 == 0xffff) is resolved from the current mission
 * (ov002 0206b84c: 0x25a..0x25c) by the class's shape -- no model 0x1444 / 0x1450 / 0x1461,
 * linked keys 0x144b / 0x1459, otherwise 0x144d / 0x145f.  Without a model name (+0x58) the
 * model node (+0x2c) stays 0; otherwise a 0x184-byte node is allocated and cleared, placed with
 * the class parameters (ov002 0207c4c0: byte +0x82, shorts +0x7c / +0x7e / +0x80, the facing),
 * the start position built (0207c53c), the transform synced to the position (0202b450) and
 * the rise speed (+0x138) drawn (02023eb4) from the kind row's byte (data 020828d8) << 12.
 * Then the facing (+0x18), home (+0x140) and position (+0x1c) are stamped, the ground (+0x28)
 * from the placement, the kind (+0x10), the handler block (+0xc) from the kind row (data
 * 020828d4), the step (+0x17, collidable bit 3 of +0x12 when the class step +0x83 is not -1),
 * the second GameState field / bit (+0x150 / +0x152), the link key (+0x14e) cleared to -1,
 * the no-linked-object bit (bit 7 of +0x14d) set and dropped again by any non-negative link
 * key copied from aKey, the first GameState field / bit (+0x14 / +0x16), state 0 (+0x14c)
 * and limit 0 (+0x13c); the piece is registered in bucket nKind (ov002 02076480). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015PickupKindRow {
    void *pHandlers;          /* 0x00: class handler block of the kind */
    u8   nRise;               /* 0x04: rise speed scale */
    u8   pad_05[3];
} Ov015PickupKindRow;

typedef struct Ov015PickupDef {
    u8   pad_00[0x58];
    char szModel[0x10];       /* 0x58 */
    u8   pad_68[0x14];
    short nParam7c;           /* 0x7c */
    short nParam7e;           /* 0x7e */
    short nParam80;           /* 0x80 */
    s8   nParam82;            /* 0x82 */
    s8   nStepInit;           /* 0x83 */
    u8   nKind;               /* 0x84 */
    u8   pad_85;
    u16  nFlagBase;           /* 0x86: 0xffff = unresolved */
} Ov015PickupDef;

typedef struct Ov015ModelNode {
    u8   pad_00[0xc];
    u8   transform[0x184 - 0xc]; /* 0x0c */
} Ov015ModelNode;

typedef struct Ov015Pickup {
    u8   pad_000[0xc];
    void *pHandlers;          /* 0x00c */
    u8   nKind;               /* 0x010 */
    u8   pad_011;
    u16  nFlags;              /* 0x012: bit 3 collidable */
    u16  nStateField;         /* 0x014 */
    u8   nStateBit;           /* 0x016 */
    u8   nStep;               /* 0x017 */
    short nFacing;            /* 0x018 */
    u8   pad_01a[2];
    VecFx32 position;         /* 0x01c */
    int  nGround;             /* 0x028 */
    Ov015ModelNode *pModel;   /* 0x02c */
    u8   pad_030[0x138 - 0x30];
    int  nRiseSpeed;          /* 0x138 */
    int  nLimit;              /* 0x13c */
    VecFx32 home;             /* 0x140 */
    u8   nState;              /* 0x14c */
    u8   nStateBits;          /* 0x14d: bit 7 no linked object */
    short nLinkKey;           /* 0x14e: link keys are written from here, nKeys of them */
    u16  nStateField2;        /* 0x150 */
    u8   nStateBit2;          /* 0x152 */
    u8   nFlagOffset;         /* 0x153 */
} Ov015Pickup;

extern Ov015PickupKindRow data_ov015_020828d4[];                         /* per-kind pickup rows */

extern Ov015Pickup *func_ov002_02076a38(Ov015PickupDef *pClass, int nSlot); /* take a piece from the class table */
extern int   func_ov002_0206b84c(void);                                   /* current mission */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern int   func_ov002_0207c4c0(void *pPiece, void *pNode, int *pPlace, int nSlot, int nKind,
                                 int nParamA, int nParamB, int nParamC, int nFacing, int nFlag); /* place the node */
extern void  func_ov002_0207c53c(VecFx32 *pOut, VecFx32 *pPos, int *pPlace);  /* start position */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);                 /* Actor_SetVecAndSyncChild */
extern u32   func_02023eb4(u32 nRange);                                      /* RandNextScaled */
extern void  MIi_CpuClear16(u16 nData, void *pDst, u32 nSize);
extern void  func_ov002_02076480(int nBucket, Ov015Pickup *pPiece);          /* register the piece */

Ov015Pickup *func_ov015_020801c8(Ov015PickupDef *pClass, u16 nSlot, u16 nKind, u16 nField, u8 nBit,
                                 u16 nField2, u8 nBit2, VecFx32 *pPos, short nFacing, int nKeys, short *aKey)
{
    VecFx32 start;
    int aPlace[5];
    Ov015Pickup *pPickup;
    int nMission;
    int i;

    pPickup = func_ov002_02076a38(pClass, nSlot);
    pPickup->nFlagOffset = nSlot;
    if (pClass->nFlagBase == 0xffff) {
        nMission = func_ov002_0206b84c();
        if (pClass->szModel[0] == 0) {
            switch (nMission) {
            case 0x25a:
                pClass->nFlagBase = 0x1444;
                break;
            case 0x25b:
                pClass->nFlagBase = 0x1450;
                break;
            case 0x25c:
                pClass->nFlagBase = 0x1461;
                break;
            }
        } else if (nKeys > 0) {
            switch (nMission) {
            case 0x25a:
                pClass->nFlagBase = 0x144b;
                break;
            case 0x25b:
                pClass->nFlagBase = 0x1459;
                break;
            }
        } else {
            switch (nMission) {
            case 0x25a:
                pClass->nFlagBase = 0x144d;
                break;
            case 0x25b:
                pClass->nFlagBase = 0x145f;
                break;
            }
        }
    }
    if (pClass->szModel[0] != 0) {
        pPickup->pModel = NNSi_FndAllocFromDefaultExpHeap(0x184);
        MI_CpuFill8(pPickup->pModel, 0, 0x184);
        func_ov002_0207c4c0(pPickup, pPickup->pModel, aPlace, nSlot, pClass->nParam82,
                            pClass->nParam7c, pClass->nParam7e, pClass->nParam80, nFacing, 1);
        func_ov002_0207c53c(&start, pPos, aPlace);
        func_0202b450(pPickup->pModel->transform, pPos);
        pPickup->nRiseSpeed = func_02023eb4(data_ov015_020828d4[pClass->nKind].nRise) << 12;
    } else {
        pPickup->pModel = 0;
        start = *pPos;
    }
    pPickup->nFacing = nFacing;
    pPickup->home = *pPos;
    pPickup->position = *pPos;
    pPickup->nGround = aPlace[2];
    pPickup->nKind = nKind;
    pPickup->pHandlers = data_ov015_020828d4[pClass->nKind].pHandlers;
    if (pClass->nStepInit == -1) {
        pPickup->nFlags &= ~8;
    } else {
        pPickup->nFlags |= 8;
        pPickup->nStep = pClass->nStepInit;
    }
    pPickup->nStateField2 = nField2;
    pPickup->nStateBit2 = nBit2;
    MIi_CpuClear16(0xffff, &pPickup->nLinkKey, sizeof(short));
    pPickup->nStateBits |= 0x80;
    for (i = 0; i < nKeys; i++) {
        if (((&pPickup->nLinkKey)[i] = aKey[i]) >= 0) {
            pPickup->nStateBits &= ~0x80;
        }
    }
    pPickup->nStateField = nField;
    pPickup->nStateBit = nBit;
    pPickup->nState = 0;
    pPickup->nLimit = 0;
    func_ov002_02076480(nKind, pPickup);
    return pPickup;
}
