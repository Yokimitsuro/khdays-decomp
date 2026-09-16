/* func_ov015_020813c4 -- Ov015_ChestNotifyNeighbours: walk the pieces of the chest's
 * kind (ov002 02076688 list, next at +0x4) and, for every other live piece of the same
 * kind (+0x10) with a message handler (class +0x1c) not yet notified (bit in +0x734), ask
 * whether it is within nExtent of the chest: the class's hit test (+0x44, mode 1 with a
 * sphere shape at the chest position) answers 0 / 1, or 0xff to fall back on a sphere test
 * (ov002 0207c7fc) of the piece's hit node (02076d24, radius +0xc) against the chest
 * position when the class has a +0x24 handler.  A piece within range receives a hit
 * record (ov002 02076dac) carrying the opener (+0x726), kind 5, 10, 8 and mask 0x80 (def
 * class 0x1b) or 8, and its bit is set. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

/* Ov002HitShape: a sphere (shape 0) at the chest position */
typedef struct Ov015HitShape {
    s8   nShape;              /* 0x00: 0 sphere */
    u8   pad_01[3];
    VecFx32 vFrom;            /* 0x04 */
    union {
        int nRadius;          /* 0x10, shape 0 */
        VecFx32 vTo;          /* 0x10, shape 1 */
    } u;
} Ov015HitShape;              /* 0x1c */

/* Ov022HitRecord */
typedef struct Ov015HitRecord {
    VecFx32 vecPos;           /* 0x00: not set */
    u8   nId;                 /* 0x0c */
    u8   nKind;               /* 0x0d */
    u8   pad_0e[2];
    u32  nA;                  /* 0x10 */
    u32  nB;                  /* 0x14 */
    u32  nMask;               /* 0x18 */
} Ov015HitRecord;

typedef struct Ov015Piece Ov015Piece;

typedef struct Ov015PieceClass {
    u8   pad_00[0x1c];
    void *pfnMessage;         /* 0x1c */
    u8   pad_20[4];
    void *pfn24;              /* 0x24 */
    u8   pad_28[0x44 - 0x28];
    int (*pfnQuery)(Ov015Piece *pPiece, int nMode, Ov015HitShape *pShape); /* 0x44 */
} Ov015PieceClass;

struct Ov015Piece {
    u8   pad_00[4];
    Ov015Piece *pNext;        /* 0x04 */
    Ov015PieceClass *pClass;  /* 0x08 */
    u8   pad_0c[4];
    u8   nKind;               /* 0x10 */
};

typedef struct Ov015HitNode {
    u8   pad_00[0xc];
    int  nRadius;             /* 0x0c */
} Ov015HitNode;

typedef struct Ov015ChestDef {
    u8   pad_00[0x4c];
    u16  nClass;              /* 0x4c: 0x1b / 0x1c */
} Ov015ChestDef;

typedef struct Ov015Chest {
    u8   pad_000[8];
    Ov015ChestDef *pDef;      /* 0x008 */
    u8   pad_00c[4];
    u8   nKind;               /* 0x010 */
    u8   pad_011[0x726 - 0x11];
    s8   nOpener;             /* 0x726 */
    u8   pad_727[0x734 - 0x727];
    int  nNotifiedMask;       /* 0x734 */
} Ov015Chest;

extern Ov015Piece *func_ov002_02076688(u8 nKind);                          /* first piece of a kind */
extern VecFx32 *func_ov002_02076cc8(void *pPiece);                         /* piece position */
extern Ov015HitNode *func_ov002_02076d24(Ov015Piece *pPiece);              /* piece hit node */
extern int  func_ov002_0207c7fc(void *pFrom, int nRadius, VecFx32 *pAt, int nExtent); /* sphere test */
extern int  func_ov002_02076dac(Ov015Piece *pPiece, Ov015HitRecord *pRecord); /* deliver a hit record */

void func_ov015_020813c4(Ov015Chest *pChest, int nExtent)
{
    Ov015ChestDef *pDef;
    int i;
    Ov015Piece *pPiece;
    Ov015PieceClass *pClass;
    Ov015HitNode *pNode;
    u32 nResult;
    Ov015HitShape shape;
    Ov015HitRecord record;

    pDef = pChest->pDef;
    pPiece = func_ov002_02076688(pChest->nKind);
    i = 0;
    if (pPiece != 0) {
        while (pPiece != 0) {
            nResult = 0xff;
            if ((pChest->nNotifiedMask & (1 << i)) == 0) {
                if (pPiece != 0 && (Ov015Piece *)pChest != pPiece && (pClass = pPiece->pClass) != 0 && pClass->pfnMessage != 0
                    && pPiece->nKind == pChest->nKind) {
                    if (pClass->pfnQuery != 0) {
                        shape.nShape = 0;
                        shape.vFrom = *func_ov002_02076cc8(pChest);
                        shape.u.nRadius = nExtent;
                        nResult = (u8)pPiece->pClass->pfnQuery(pPiece, 1, &shape);
                    }
                    if (nResult == -1) {
                        pNode = func_ov002_02076d24(pPiece);
                        if (pPiece->pClass->pfn24 == 0 || pNode == 0) {
                            goto next;
                        }
                        if (func_ov002_0207c7fc(pNode, pNode->nRadius, func_ov002_02076cc8(pChest), nExtent) != 0) {
                            nResult = 1;
                        }
                    }
                    if (nResult == 1) {
                        record.nId = pChest->nOpener;
                        record.nKind = 5;
                        record.nA = 10;
                        record.nB = 8;
                        record.nMask = (pDef->nClass == 0x1b) ? 0x80 : 8;
                        func_ov002_02076dac(pPiece, &record);
                        pChest->nNotifiedMask |= 1 << i;
                    }
                }
            }
next:
            pPiece = pPiece->pNext;
            i++;
        }
    }
}
