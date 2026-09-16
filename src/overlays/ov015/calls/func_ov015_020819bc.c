/* func_ov015_020819bc -- Ov015_ChestShow: the chest's show handler.  The closed model's
 * node position (+0x54c) is taken as the position; the render node (+0x498) is bound to the class's model
 * (+0x58; ov002 0206da70, 0202b930), given the facing (+0x18) and facing-locked unless
 * already locked (bit 5 of its +0xc), synced to the position (0202b450) and enabled
 * (0202af1c); the open node (+0x61c) is registered with the class sequence (+0x68,
 * 0202a634), given the facing, locked, placed at the position and enabled; the render node
 * gets flag bit 3 cleared (0202bedc); the chest becomes visible (bit 2 of +0x12); the node
 * matching the opened bit (bit 4 of +0x724: open node, else closed node) is started at the
 * saved time (+0x728, 020817f0); and resource pair 0x2e (class 0x1b) or 0x2f is requested. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015SeqNode {
    u16  nFlags;              /* 0x00: bit 5 facing locked */
    u8   pad_02[0x7c - 0x02];
    u16  nFacing;             /* 0x7c */
    u8   pad_7e[0xa4 - 0x7e];
    VecFx32 position;         /* 0xa4 */
    u8  pad_b0[0x104 - 0xb0];
} Ov015SeqNode;                /* 0x104 */

typedef struct Ov015RenderNode {
    u8   pad_00[0xc];
    int  nBits;               /* 0x0c: bit 5 facing locked */
    Ov015SeqNode node;        /* 0x10 */
} Ov015RenderNode;             /* 0x114 */

typedef struct Ov015ChestDef {
    u8   pad_00[0x4c];
    u16  nClass;              /* 0x4c: 0x1b / 0x1c */
    u8   pad_4e[0xa];
    char szModel[0x10];       /* 0x58 */
    char szSequence[0x10];    /* 0x68 */
} Ov015ChestDef;

typedef struct Ov015Chest {
    u8   pad_000[8];
    Ov015ChestDef *pDef;      /* 0x008 */
    u8   pad_00c[6];
    u16  nFlags;              /* 0x012: bit 2 visible */
    u8   pad_014[4];
    u16  nFacing;             /* 0x018 */
    u8   pad_01a[0x498 - 0x1a];
    Ov015RenderNode render;   /* 0x498: closed-lid model node (its sequence node's position, +0x54c, is the lid position) */
    u8   pad_5ac[0x61c - 0x5ac];
    Ov015SeqNode openNode;    /* 0x61c */
    u8   pad_720[4];
    u8   nStateBits;          /* 0x724: bit 4 opened */
    u8   pad_725[3];
    int  nTime;               /* 0x728 */
} Ov015Chest;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202b930(void *pNode, void *pEntry, int nA, int nB); /* bind a model node */
extern void  func_0202b450(void *pTransform, VecFx32 *pVec);         /* Actor_SetVecAndSyncChild */
extern void  func_0202af1c(void *pNode);                             /* SceneNode_Enable */
extern void  func_0202a634(void *pNode, void *pEntry, int nA, int nB); /* RegisterSeqAndInit */
extern void  func_0202bedc(void *pNode, int nFlag);                  /* Obj_SetFlagBit3 */
extern void  func_ov015_020817f0(void *pChest, void *pNode, int nArg, int nTime);
extern void  func_0203355c(int nId);                                 /* Res_RequestIdPair */

void func_ov015_020819bc(Ov015Chest *pChest)
{
    Ov015ChestDef *pDef;
    VecFx32 position;
    u16 nFacing;

    pDef = pChest->pDef;
    position = pChest->render.node.position;
    func_0202b930(&pChest->render, func_ov002_0206da70(pDef->szModel), 1, 4);
    nFacing = pChest->nFacing;
    if ((pChest->render.nBits & 0x20) == 0) {
        pChest->render.node.nFacing = nFacing;
        pChest->render.node.nFlags |= 0x20;
    }
    func_0202b450(&pChest->render.nBits, &position);
    func_0202af1c(&pChest->render.node);
    func_0202a634(&pChest->openNode, func_ov002_0206da70(pDef->szSequence), 1, 4);
    pChest->openNode.nFacing = pChest->nFacing;
    pChest->openNode.nFlags |= 0x20;
    pChest->openNode.position = position;
    func_0202af1c(&pChest->openNode);
    func_0202bedc(&pChest->render, 0);
    pChest->nFlags |= 4;
    if (pChest->nStateBits & 0x10) {
        func_ov015_020817f0(pChest, &pChest->openNode, 0, pChest->nTime);
    } else {
        func_ov015_020817f0(pChest, &pChest->render.node, 0, pChest->nTime);
    }
    func_0203355c(pDef->nClass == 0x1b ? 0x2e : 0x2f);
}
