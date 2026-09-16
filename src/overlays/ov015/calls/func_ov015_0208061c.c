/* func_ov015_0208061c -- Ov015_SpawnTrigger: take a trigger piece from its class table
 * (ov002 02076a38), copy the name (+0x51), the centre (+0x30), the shape byte (+0x3c), the
 * extent (+0x40) and the parameter word (+0x4c), clear its state (+0x50), set the class
 * word (+0xc, the trigger handler block 02080540), the kind (+0x10), the GameState field /
 * bit pair (+0x14 / +0x16) and register it in bucket nKind (ov002 02076480). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015Trigger {
    u8   pad_00[0xc];
    void *pHandlers;          /* 0x0c: class handler block */
    u8   nKind;               /* 0x10 */
    u8   pad_11[3];
    u16  nStateField;         /* 0x14: GameState field */
    u8   nStateBit;           /* 0x16: its bit */
    u8   nStep;               /* 0x17 */
    u8   pad_18[0x30 - 0x18];
    VecFx32 centre;           /* 0x30 */
    s8   nShape;              /* 0x3c */
    u8   pad_3d[3];
    VecFx32 extent;           /* 0x40 */
    int  nParam;              /* 0x4c */
    u8   nState;              /* 0x50 */
    char szName[11];          /* 0x51 */
} Ov015Trigger;

extern Ov015Trigger *func_ov002_02076a38(void *pClass, int nSlot);   /* take a piece from the class table */
extern void func_0201f924(char *pDst, const char *pSrc);             /* StrCopy */
extern void func_ov002_02076480(int nBucket, Ov015Trigger *pPiece);  /* register the piece */
extern void func_ov015_02080540(void);                               /* Ov015_CutsceneStep2: the handler block */

Ov015Trigger *func_ov015_0208061c(void *pClass, int nSlot, int nKind, int nField, u8 nBit, VecFx32 *pCentre, int nParam, s8 nShape, VecFx32 *pExtent, const char *pName)
{
    Ov015Trigger *pPiece;

    pPiece = func_ov002_02076a38(pClass, nSlot);
    func_0201f924(pPiece->szName, pName);
    pPiece->centre = *pCentre;
    pPiece->nShape = nShape;
    pPiece->extent = *pExtent;
    pPiece->nParam = nParam;
    pPiece->nState = 0;
    pPiece->nKind = nKind;
    pPiece->pHandlers = (void *)func_ov015_02080540;
    pPiece->nStateField = nField;
    pPiece->nStateBit = nBit;
    pPiece->nStep = 0;
    func_ov002_02076480(nKind, pPiece);
    return pPiece;
}
