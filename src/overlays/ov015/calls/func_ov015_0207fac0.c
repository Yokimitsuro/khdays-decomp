/* func_ov015_0207fac0 -- Ov015_PickupLoad: the pickup's load handler.  Marks it visible
 * (bit 2 of +0x12).  With a model name in the class table (+0x58) the model node (+0x2c) is
 * bound to that resource (ov002 0206da70, 0202b930), synced to the home position (+0x140,
 * 0202b450), given the facing (+0x18) at its +0x8c unless already facing-locked (bit 5 of
 * its +0xc, which is then set), its sequence started (0207fa40) at the kind's spin speed
 * (020828d8 by the class kind +0x84) with the rise speed (+0x138), and resource pair 0x39
 * requested (0203355c).  The pickup's own sequence node (+0x30) is then registered with
 * the class's sequence name (+0x68, 0202a634), placed at the home position (+0xd4) with the
 * facing (+0xac), facing-locked, and the taken-sequence bit (bit 0 of +0x14d) cleared. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202b930(void *pNode, void *pEntry, int nA, int nB); /* bind a model node */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);         /* Actor_SetVecAndSyncChild */
extern void  func_ov015_0207fa40(void *pPickup, void *pSequence, int nArg, int nSpin, int nRise); /* Ov015_StoreArgsRunTwoSubActionsIfFlag4 */
extern void  func_0203355c(int nId);                                 /* Res_RequestIdPair */
extern void  func_0202a634(void *pNode, void *pEntry, int nA, int nB); /* RegisterSeqAndInit */
extern u8    data_ov015_020828d8[];                                  /* per-kind pickup parameters, 8 bytes each */

typedef struct Ov015PickupDef {
    u8   pad_00[0x58];
    char szModel[0x10];       /* 0x58 */
    char szSequence[0x10];    /* 0x68 */
    u8   pad_78[0xc];
    u8   nKind;               /* 0x84 */
} Ov015PickupDef;

typedef struct Ov015Transform {
    int  nBits;               /* 0x00: bit 5 facing locked */
    u16  sequence;            /* 0x04: sequence node */
    u8   pad_06[0x80 - 0x06];
    u16  nFacing;             /* 0x80 */
} Ov015Transform;

typedef struct Ov015ModelNode {
    u8   pad_00[0xc];
    Ov015Transform transform; /* 0x0c */
} Ov015ModelNode;

typedef struct Ov015Pickup {
    u8   pad_000[8];
    Ov015PickupDef *pDef;     /* 0x008 */
    u8   pad_00c[6];
    u16  nFlags;              /* 0x012: bit 2 visible */
    u8   pad_014[4];
    u16  nFacing;             /* 0x018 */
    u8   pad_01a[0x2c - 0x1a];
    Ov015ModelNode *pModel;   /* 0x02c */
    u16  sequence;            /* 0x030: own sequence node, bit 5 facing locked */
    u8   pad_032[0xac - 0x32];
    u16  nSeqFacing;          /* 0x0ac */
    u8   pad_0ae[0xd4 - 0xae];
    VecFx32 seqPos;           /* 0x0d4 */
    u8   pad_0e0[0x138 - 0xe0];
    int  nRiseSpeed;          /* 0x138 */
    u8   pad_13c[4];
    VecFx32 home;             /* 0x140 */
    u8   nState;              /* 0x14c */
    u8   nStateBits;          /* 0x14d */
} Ov015Pickup;

void func_ov015_0207fac0(Ov015Pickup *pPickup)
{
    Ov015PickupDef *pDef;
    Ov015Transform *pTransform;
    u16 nFacing;

    pDef = pPickup->pDef;
    pPickup->nFlags |= 4;
    if (pDef->szModel[0] != 0) {
        func_0202b930(pPickup->pModel, func_ov002_0206da70(pDef->szModel), 1, 4);
        func_0202b450(&pPickup->pModel->transform, &pPickup->home);
        nFacing = pPickup->nFacing;
        pTransform = &pPickup->pModel->transform;
        if ((pTransform->nBits & 0x20) == 0) {
            pTransform->nFacing = nFacing;
            pTransform->sequence |= 0x20;
        }
        func_ov015_0207fa40(pPickup, &pPickup->pModel->transform.sequence, 0, data_ov015_020828d8[pDef->nKind * 8] << 12, pPickup->nRiseSpeed);
        func_0203355c(0x39);
    }
    func_0202a634(&pPickup->sequence, func_ov002_0206da70(pDef->szSequence), 1, 4);
    pPickup->seqPos = pPickup->home;
    pPickup->nSeqFacing = pPickup->nFacing;
    pPickup->sequence |= 0x20;
    pPickup->nStateBits &= ~1;
}
