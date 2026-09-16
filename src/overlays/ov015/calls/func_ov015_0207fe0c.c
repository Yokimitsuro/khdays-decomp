/* func_ov015_0207fe0c -- Ov015_PickupUpdate: per-frame state function of a mission pickup
 * (frame delta from ov002 0207687c).  State 0 (idle): the model node's sequence (+0x2c
 * -> +0x10) is driven by the class placement stepper (ov002 0207c700, flag 1, limit
 * +0x13c).  State 2 (taken): the pickup is collected (0207fcec) and slot 0x39 spawns at
 * the model position (+0xb4) with 0 when a linked object took it, 1 otherwise; the model's
 * resources are released (0202bc30) and, when visible (bit 2 of +0x12), the own sequence
 * (+0x30) is rewound (ov002 0207c618), disabled (0202af2c) and the taken-sequence bit
 * (bit 0 of +0x14d) raised; the state becomes 3.  State 3 (rising): the home height
 * (+0x144) rises by 0x19a per frame unit, the visible model follows it, and past 0x1e000
 * the GameState field keeps only its bit 0 plus the collected bit 1, the piece is retired
 * (ov002 02076bd8) and the terminal state function (ov002 0207cea4) returned.  Otherwise
 * a visible pickup draws its model node (0202aa9c) and advances the taken sequence
 * (0207fdc4), and 0 is returned. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef void *Ov015StateFn(void *pPiece);

typedef struct Ov015SeqNode {
    u16  nFlags;              /* 0x00 */
    u8   pad_02[0xa4 - 0x02];
    VecFx32 position;         /* 0xa4 */
    u8   pad_b0[0x104 - 0xb0];
} Ov015SeqNode;                /* 0x104 */

typedef struct Ov015ModelNode {
    u8   pad_00[0xc];
    int  nBits;               /* 0x0c */
    Ov015SeqNode node;        /* 0x10 */
} Ov015ModelNode;

typedef struct Ov015Pickup {
    u8   pad_000[0x12];
    u16  nFlags;              /* 0x012: bit 2 visible */
    u16  nStateField;         /* 0x014 */
    u8   nStateBit;           /* 0x016 */
    u8   pad_017[0x2c - 0x17];
    Ov015ModelNode *pModel;   /* 0x02c */
    u16  sequence;            /* 0x030: own sequence node */
    u8   pad_032[0x13c - 0x32];
    int  nLimit;              /* 0x13c */
    VecFx32 home;             /* 0x140 */
    u8   nState;              /* 0x14c: 0 idle, 1 requested, 2 taken, 3 rising */
    u8   nStateBits;          /* 0x14d: bit 0 taken sequence playing */
} Ov015Pickup;

extern int  func_ov002_0207687c(void);                                 /* frame delta */
extern int  func_ov002_0207c700(void *pPiece, void *pNode, int nDelta, int nFlag, int nLimit, int *pElapsed); /* placement stepper */
extern int  func_ov015_0207fcec(Ov015Pickup *pPickup);                 /* Ov015_PickupCollect */
extern void func_02033d0c(int nSlot, int nArg, VecFx32 *pPos, int nD);  /* Slot_Spawn */
extern void func_0202bc30(void *pNode);                                /* ReleaseNodeResources */
extern void func_ov002_0207c618(void *pAnim, int nTrack, int nFrame);  /* rewind a sequence */
extern void func_0202af2c(void *pNode);                                /* SceneNode_Disable */
extern int  func_020235d0(u16 nField, u8 nBit);                        /* GameState_GetField */
extern void func_020235e8(u16 nField, u8 nBit, u16 nValue);            /* GameState_SetField */
extern void func_ov002_02076bd8(void *pPiece, int nMode);              /* retire a piece */
extern void func_0202aa9c(void *pNode);                                /* Scene_DrawNode */
extern int  func_ov015_0207fdc4(Ov015Pickup *pPickup, int nDelta);     /* Ov015_PickupPlayTakenSequence */
extern Ov015StateFn func_ov002_0207cea4;                               /* terminal state */

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

Ov015StateFn *func_ov015_0207fe0c(Ov015Pickup *pPickup)
{
    int nDelta;
    u32 nField;

    nDelta = func_ov002_0207687c();
    switch (pPickup->nState) {
    case 0:
        func_ov002_0207c700(pPickup, &pPickup->pModel->node, nDelta, 1, pPickup->nLimit, &pPickup->nLimit);
        break;
    case 2:
        if (func_ov015_0207fcec(pPickup) != 0) {
            func_02033d0c(0x39, 0, &pPickup->pModel->node.position, 0);
        } else {
            func_02033d0c(0x39, 1, &pPickup->pModel->node.position, 0);
        }
        func_0202bc30(pPickup->pModel);
        if (pPickup->nFlags & 4) {
            func_ov002_0207c618(&pPickup->sequence, 0, 0);
            func_0202af2c(&pPickup->sequence);
            pPickup->nStateBits |= 1;
        }
        pPickup->nState = 3;
        break;
    case 3:
        pPickup->home.y += FX_Mul(nDelta, 0x19a);
        if (pPickup->nFlags & 4) {
            pPickup->pModel->node.position = pPickup->home;
        }
        if (pPickup->home.y >= 0x1e000) {
            nField = func_020235d0(pPickup->nStateField, pPickup->nStateBit);
            func_020235e8(pPickup->nStateField, pPickup->nStateBit, (nField & 0xffff0001) | 2);
            func_ov002_02076bd8(pPickup, 0);
            return func_ov002_0207cea4;
        }
        break;
    }
    if (pPickup->nFlags & 4) {
        func_0202aa9c(&pPickup->pModel->node);
        func_ov015_0207fdc4(pPickup, nDelta);
    }
    return 0;
}
