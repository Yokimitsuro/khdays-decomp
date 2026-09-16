/* func_ov015_02082188 -- Ov015_SpawnChest: take a chest piece from its class table (ov002
 * 02076a38), place its render node (+0x498) with the class's placement parameters (kind
 * +0x7c, words +0x80 / +0x84 / +0x88, the facing), clear +0x618, build the start position
 * (unused), sync the transform (+0x4a4) to the requested position, then stamp the facing
 * (+0x18), the position (+0x488), the extent (+0x494), the GameState field / bit (+0x14 /
 * +0x16), the state bits (+0x724 = 0), the kind (+0x10), the handler block (+0xc =
 * 02081ca8), the piece flags (+0x12 |= 0x48), the step (+0x17 = 0), the timer (+0x728 = 0),
 * construct the actor body (+0x24, 0202d968) bound to the render transform (+0x4a4), set
 * the hit extents 0xc00 / 0x800 (+0x1c / +0x1e), clear the chest flags (+0x464) and the
 * three words after them, copy the lid position (+0x54c) into the home (+0x474), clear
 * +0x480 / +0x484, raise the body flag (+0x20) and register the piece in its bucket.
 * Returns the chest. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015SeqNode {
    u16  nFlags;              /* 0x00 */
    u8   pad_02[0x7c - 0x02];
    u16  nFacing;             /* 0x7c */
    u8   pad_7e[0xa4 - 0x7e];
    VecFx32 position;         /* 0xa4 */
    u8   pad_b0[0x104 - 0xb0];
} Ov015SeqNode;                /* 0x104 */

typedef struct Ov015RenderNode {
    u8   pad_00[0xc];
    int  nBits;               /* 0x0c */
    Ov015SeqNode node;        /* 0x10 */
} Ov015RenderNode;             /* 0x114 */

typedef struct Ov015ChestDef {
    u8   pad_00[0x7c];
    s8   nKind;               /* 0x7c */
    u8   pad_7d[3];
    int  nParam80;            /* 0x80 */
    int  nParam84;            /* 0x84 */
    int  nParam88;            /* 0x88 */
} Ov015ChestDef;

/* generic view of the piece the class table hands out; the chest raises its body flag
 * through this view (lever: a second variable for the same pointer keeps the copy early) */
typedef struct Ov015Piece {
    u8   pad_00[0x20];
    u8   bHasBody;            /* 0x20 */
} Ov015Piece;

typedef struct Ov015Chest {
    u8   pad_000[0xc];
    void *pHandlers;          /* 0x00c */
    u8   nKind;               /* 0x010 */
    u8   pad_011;
    u16  nFlags;              /* 0x012 */
    u16  nStateField;         /* 0x014 */
    u8   nStateBit;           /* 0x016 */
    u8   nStep;               /* 0x017 */
    short nFacing;            /* 0x018 */
    u8   pad_01a[2];
    u16  nExtentA;            /* 0x01c */
    u16  nExtentB;            /* 0x01e */
    u8   bHasBody;            /* 0x020 */
    u8   pad_021[3];
    u8   body[0x440];         /* 0x024: actor body (0202d968) bound to the render transform */
    u16  nChestFlags;         /* 0x464 */
    u8   pad_466[2];
    int  nWord468;            /* 0x468 */
    int  nWord46c;            /* 0x46c */
    int  nWord470;            /* 0x470 */
    VecFx32 homePos;          /* 0x474 */
    int  nWord480;            /* 0x480 */
    int  nWord484;            /* 0x484 */
    VecFx32 position;         /* 0x488 */
    int  nExtent;             /* 0x494 */
    Ov015RenderNode render;   /* 0x498 */
    u8   pad_5ac[0x618 - 0x5ac];
    int  nWord618;            /* 0x618 */
    Ov015SeqNode openNode;    /* 0x61c */
    u8   pad_720[4];
    u8   nStateBits;          /* 0x724 */
    u8   pad_725[3];
    int  nTimer;              /* 0x728 */
} Ov015Chest;

extern Ov015Chest *func_ov002_02076a38(Ov015ChestDef *pClass, int nSlot);   /* take a piece from the class table */
extern int  func_ov002_0207c4c0(void *pPiece, void *pNode, int *pPlace, int nSlot, int nKind,
                                int nParamA, int nParamB, int nParamC, int nFacing, int nFlag); /* place the node */
extern void func_ov002_0207c53c(VecFx32 *pOut, VecFx32 *pPos, int *pPlace);  /* start position */
extern void func_0202b450(void *pTransform, VecFx32 *pVec);                 /* Actor_SetVecAndSyncChild */
extern void func_0202d968(void *pBody, void *pRecord);                       /* construct an actor body */
extern void func_ov002_02076480(int nBucket, Ov015Chest *pPiece);           /* register the piece */
extern void func_ov015_02081ca8(void);                                       /* Ov015_ChestUpdate */

Ov015Chest *func_ov015_02082188(Ov015ChestDef *pClass, u16 nSlot, int nBucket, VecFx32 *pPos,
                                short nFacing, u16 nField, u8 nBit)
{
    VecFx32 start;
    int aPlace[5];
    Ov015Chest *pChest;
    Ov015Piece *pPiece;

    pPiece = (Ov015Piece *)func_ov002_02076a38(pClass, nSlot);
    pChest = (Ov015Chest *)pPiece;
    func_ov002_0207c4c0(pChest, &pChest->render, aPlace, nSlot, pClass->nKind,
                        pClass->nParam80, pClass->nParam84, pClass->nParam88, nFacing, 1);
    pChest->nWord618 = 0;
    func_ov002_0207c53c(&start, pPos, aPlace);
    func_0202b450(&pChest->render.nBits, pPos);
    pChest->nFacing = nFacing;
    pChest->position = *pPos;
    pChest->nExtent = aPlace[2];
    pChest->nStateField = nField;
    pChest->nStateBit = nBit;
    pChest->nStateBits = 0;
    pChest->nKind = nBucket;
    pChest->pHandlers = (void *)func_ov015_02081ca8;
    pChest->nFlags |= 0x48;
    pChest->nStep = 0;
    pChest->nTimer = 0;
    func_0202d968(pChest->body, &pChest->render.nBits);
    pChest->nExtentA = 0xc00;
    pChest->nExtentB = 0x800;
    pChest->nChestFlags = 0;
    pChest->nWord470 = 0;
    pChest->nWord46c = pChest->nWord470;
    pChest->nWord468 = pChest->nWord46c;
    pChest->homePos = pChest->render.node.position;
    pChest->nWord480 = 0;
    pChest->nWord484 = 0;
    pPiece->bHasBody = 1;
    func_ov002_02076480(nBucket, pChest);
    return pChest;
}
