/* func_ov015_02080fc0 -- Ov015_SpawnSpot: take a spot piece of kind nKind from its class
 * table (ov002 02076a38), zero its target (+0x30), actor (+0x3c), flags (+0x40) and facing
 * offset (+0x18), copy the zeroed target into the position (+0x1c), set the facing (+0x28),
 * the kind (+0x10), the handler block (+0xc = 02080d30), the collidable flag (bit 3 of
 * +0x12), the GameState field / bit (+0x14 / +0x16), the step 0x84 (+0x17), record it in
 * the table's per-kind slot (+0x154) and register it in bucket nKind (ov002 02076480). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015Spot {
    u8   pad_00[0xc];
    void *pHandlers;          /* 0x0c: class handler block */
    u8   nKind;               /* 0x10 */
    u8   pad_11;
    u16  nFlags;              /* 0x12 */
    u16  nStateField;         /* 0x14: GameState field */
    u8   nStateBit;           /* 0x16: its bit */
    u8   nStep;               /* 0x17 */
    short nFacingOffset;      /* 0x18 */
    u8   pad_1a[2];
    VecFx32 position;         /* 0x1c */
    int  nFacing;             /* 0x28 */
    u8   pad_2c[4];
    VecFx32 target;           /* 0x30 */
    void *pActor;             /* 0x3c */
    u8   nSpotFlags;          /* 0x40 */
} Ov015Spot;

typedef struct Ov015SpotDef {
    u8   pad_000[0x154];
    Ov015Spot *apSpot[9];     /* 0x154: the spot of each kind */
} Ov015SpotDef;

extern Ov015Spot *func_ov002_02076a38(Ov015SpotDef *pClass, int nSlot);  /* take a piece from the class table */
extern void func_ov002_02076480(int nBucket, Ov015Spot *pPiece);           /* register the piece */
extern void func_ov015_02080d30(void);                                     /* the spot handler block */

Ov015Spot *func_ov015_02080fc0(Ov015SpotDef *pClass, int nSlot, int nKind, int nField, u8 nBit, int nFacing)
{
    Ov015Spot *pSpot;

    pSpot = func_ov002_02076a38(pClass, nSlot);
    pSpot->target.x = 0;
    pSpot->target.y = 0;
    pSpot->target.z = 0;
    pSpot->pActor = 0;
    pSpot->nSpotFlags = 0;
    pSpot->nFacingOffset = 0;
    pSpot->position = pSpot->target;
    pSpot->nFacing = nFacing;
    pSpot->nKind = nKind;
    pSpot->pHandlers = (void *)func_ov015_02080d30;
    pSpot->nFlags |= 8;
    pSpot->nStateField = nField;
    pSpot->nStateBit = nBit;
    pSpot->nStep = 0x84;
    pSpot->nSpotFlags = 0;
    pClass->apSpot[nKind] = pSpot;
    func_ov002_02076480(nKind, pSpot);
    return pSpot;
}
