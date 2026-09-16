/* func_ov015_02080c00 -- Ov015_SpotArrive: an actor reached entry nKey of an armed spot
 * (bit 0 of +0x40).  For a plain entry (bLink == 0) the entry's id is looked up
 * (02080b9c, unused) and the current entry of the spot's table found (020807f4 with
 * +0x179); when bKeep is 0 the spot goes live (bit 1), the class table forgets the
 * player (+0x180), the current entry (+0x179) and its pointer (+0x17c), otherwise the
 * target (+0x30) becomes the entry's pickup position (ov002 02076cc8); the pickup becomes
 * the owner (+0x54) and the collidable flag (bit 3 of +0x12) is dropped.  For a link entry
 * the armed / live bits are dropped, the entry found by key, its link (table +0x14, id
 * +0x15) resolved, the linked spot (+0x154 of the table) armed, the link table (+0x178)
 * and the linked entry (+0x17c) recorded and the linked spot's target set to the linked
 * entry's position (+0x8). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015SpotEntry {
    s8  nId;                  /* 0x00 */
    s8  nKey;                 /* 0x01 */
    s8  nKind;                /* 0x02: 0 point, 1 link, 2 pickup */
    u8  pad_03[5];
    union {
        void *pPickup;        /* 0x08: pickup piece (kind 2) */
        VecFx32 position;     /* 0x08: point position */
    } u;
    s8  nLinkTable;           /* 0x14 */
    s8  nLinkId;              /* 0x15 */
    u8  pad_16[2];
} Ov015SpotEntry;

typedef struct Ov015Spot Ov015Spot;

typedef struct Ov015SpotDef {
    u8  pad_000[0x154];
    Ov015Spot *apSpot[9];     /* 0x154: the spot of each kind */
    u8  nLinkTable;           /* 0x178 */
    s8  nCurrent;             /* 0x179 */
    u8  pad_17a[2];
    Ov015SpotEntry *pCurrentEntry; /* 0x17c */
    s8  nPlayer;              /* 0x180 */
} Ov015SpotDef;

struct Ov015Spot {
    u8  pad_00[8];
    Ov015SpotDef *pDef;       /* 0x08 */
    u8  pad_0c[4];
    u8  nKind;                /* 0x10 */
    u8  pad_11;
    u16 nFlags;               /* 0x12: bit 3 collidable */
    u8  pad_14[0x30 - 0x14];
    VecFx32 target;           /* 0x30 */
    void *pActor;             /* 0x3c */
    u8  nSpotFlags;           /* 0x40: bit 0 armed, bit 1 live */
    u8  pad_41[0x54 - 0x41];
    void *pOwner;             /* 0x54 */
};

extern int  func_ov015_02080b9c(Ov015Spot *pSpot, int nTable, int nKey);   /* Ov015_SpotFindEntryIdByKey */
extern Ov015SpotEntry *func_ov015_020807f4(Ov015Spot *pSpot, Ov015SpotDef *pDef, int nTable, int nId, int bByKey); /* Ov015_SpotDefFindEntry */
extern VecFx32 *func_ov002_02076cc8(void *pPiece);                          /* piece position */

void func_ov015_02080c00(Ov015Spot *pSpot, int nKey, int bLink, int bKeep)
{
    Ov015SpotDef *pDef;
    Ov015SpotEntry *pEntry;
    Ov015SpotEntry *pLinked;
    Ov015Spot *pOther;

    pDef = pSpot->pDef;
    if ((pSpot->nSpotFlags & 1) == 0) {
        return;
    }
    if (bLink == 0) {
        func_ov015_02080b9c(pSpot, pSpot->nKind, nKey);
        pEntry = func_ov015_020807f4(pSpot, pDef, pSpot->nKind, pDef->nCurrent, 0);
        if (bKeep != 0) {
            pSpot->target = *func_ov002_02076cc8(pEntry->u.pPickup);
        } else {
            pSpot->nSpotFlags |= 2;
            pDef->nPlayer = -1;
            pDef->nCurrent = -1;
            pDef->pCurrentEntry = 0;
        }
        pSpot->pOwner = pEntry->u.pPickup;
        pSpot->nFlags &= ~8;
        return;
    }
    pSpot->nSpotFlags &= ~1;
    pSpot->nSpotFlags &= ~2;
    pEntry = func_ov015_020807f4(pSpot, pDef, pSpot->nKind, nKey, 1);
    pLinked = func_ov015_020807f4(pSpot, pDef, pEntry->nLinkTable, pEntry->nLinkId, 0);
    pOther = pDef->apSpot[pEntry->nLinkTable];
    pOther->nSpotFlags |= 1;
    pDef->nLinkTable = pEntry->nLinkTable;
    pDef->pCurrentEntry = pLinked;
    pOther->target = pLinked->u.position;
}
