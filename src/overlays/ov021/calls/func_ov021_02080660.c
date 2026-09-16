/* func_ov021_02080660 -- Ov021_EmblemStart: start handler of the emblem; nothing once it has
 * been collected (state 4).  Binds the sequence node (+0x1c, 0202a634 mode 1 / 4 on the
 * definition's sequence +0x58, ov002 0206da70), gives it the emblem's position (+0xc0) and
 * facing (+0x98), raises its flag bit 5 and enables it (0202af1c); then binds the model node
 * (+0x124, 0202b930 on the definition's model +0x68) and puts it at a copy of the position
 * raised by 0x7d7 (+0x1d8); a fresh emblem (state 0) also shows the model (0202bedc 1). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov021EmblemDef {
    u8   pad_00[0x58];
    char szSequence[0x10];    /* 0x58 */
    char szModel[0x10];       /* 0x68 */
} Ov021EmblemDef;

typedef struct Ov021Emblem {
    u8   pad_000[8];
    Ov021EmblemDef *pDef;     /* 0x008 */
    u8   pad_00c[0x18 - 0xc];
    u16  nFacing;             /* 0x018 */
    u8   pad_01a[2];
    u16  nSeqFlags;           /* 0x01c: the sequence node */
    u8   pad_01e[0x98 - 0x1e];
    u16  nSeqFacing;          /* 0x098 */
    u8   pad_09a[0xc0 - 0x9a];
    VecFx32 seqPosition;      /* 0x0c0 */
    u8   pad_0cc[0x124 - 0xcc];
    u8   modelNode[0x1d8 - 0x124]; /* 0x124 */
    VecFx32 modelPosition;    /* 0x1d8 */
    u8   pad_1e4[0x2a8 - 0x1e4];
    VecFx32 position;         /* 0x2a8 */
    u8   nState;              /* 0x2b4 */
} Ov021Emblem;

extern void *func_ov002_0206da70(const char *pName);                 /* name -> resource entry */
extern void  func_0202a634(void *pNode, void *pEntry, int nA, int nB); /* RegisterSeqAndInit */
extern void  func_0202af1c(void *pNode);                             /* SceneNode_Enable */
extern void  func_0202b930(void *pNode, void *pEntry, int nA, int nB); /* bind a model node */
extern void  func_0202bedc(void *pNode, int nFlag);                  /* Obj_SetFlagBit3 */

void func_ov021_02080660(Ov021Emblem *pSelf)
{
    VecFx32 position;
    Ov021EmblemDef *pDef;

    pDef = pSelf->pDef;
    if (pSelf->nState == 4) {
        return;
    }
    func_0202a634(&pSelf->nSeqFlags, func_ov002_0206da70(pDef->szSequence), 1, 4);
    pSelf->seqPosition = pSelf->position;
    pSelf->nSeqFacing = pSelf->nFacing;
    pSelf->nSeqFlags |= 0x20;
    func_0202af1c(&pSelf->nSeqFlags);
    position = pSelf->position;
    position.y += 0x7d7;
    func_0202b930(pSelf->modelNode, func_ov002_0206da70(pDef->szModel), 1, 4);
    pSelf->modelPosition = position;
    if (pSelf->nState == 0) {
        func_0202bedc(pSelf->modelNode, 1);
    }
}
