/* func_ov015_02080884 -- Ov015_SpotDefFindNearestFreeEntry: mark table nTable visited (bit in
 * *pVisited) and look for the free pickup entry (kind 2 whose pickup's GameState field,
 * +0x14 / +0x16, has no bit above bit 0) of that table nearest to pFrom (ov002 02076cc8
 * position, VEC_Distance below 0x400000).  With one found it is accepted when nRange exceeds
 * its distance plus 100 units per link level already crossed (the pickup position is
 * fetched three times, unused) and its id returned, otherwise -1.  Without one, every
 * unvisited link entry (kind 1, link table +0x14 not yet in *pVisited) is followed: the linked
 * entry (+0x15) is looked up (020807f4) and the search recurses from its position with the
 * depth raised; the first hit is returned, else -1.  Codegen: the depth parameter is a short
 * raised in place; the second walk reuses the distance temporary as its index and keeps its
 * entry pointer block-scoped. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015SpotEntry {
    s8  nId;                  /* 0x00 */
    s8  nKey;                 /* 0x01 */
    s8  nKind;                /* 0x02: 0 point, 1 link, 2 pickup */
    u8  pad_03[5];
    union {
        void *pPickup;        /* 0x08: pickup piece (kind 2) */
        VecFx32 position;     /* 0x08: point / link position */
    } u;
    s8  nLinkTable;           /* 0x14 */
    s8  nLinkId;              /* 0x15 */
    u8  pad_16[2];
} Ov015SpotEntry;

typedef struct Ov015SpotTable {
    s8  nCount;               /* 0x00 */
    u8  pad_01[3];
    Ov015SpotEntry *aEntry;   /* 0x04 */
    u8  pad_08[0x1c - 0x08];
} Ov015SpotTable;

typedef struct Ov015SpotDef {
    u8  pad_00[0x58];
    Ov015SpotTable aTable[9]; /* 0x58 */
} Ov015SpotDef;

typedef struct Ov015Pickup {
    u8  pad_00[0x14];
    u16 nStateField;          /* 0x14 */
    u8  nStateBit;            /* 0x16 */
} Ov015Pickup;

typedef struct Ov015Spot Ov015Spot;

extern int  func_020235d0(u16 nField, u8 nBit);                            /* GameState_GetField */
extern VecFx32 *func_ov002_02076cc8(void *pPiece);                          /* piece position */
extern int  func_01ff8e94(const VecFx32 *pA, const VecFx32 *pB);            /* VEC_Distance */
extern Ov015SpotEntry *func_ov015_020807f4(Ov015Spot *pSpot, Ov015SpotDef *pDef, int nTable, int nId, int bByKey); /* Ov015_SpotDefFindEntry */
int func_ov015_02080884(Ov015Spot *pSpot, Ov015SpotDef *pDef, VecFx32 *pFrom, u32 nTable, int nRange, u16 *pVisited, short nDepth);

int func_ov015_02080884(Ov015Spot *pSpot, Ov015SpotDef *pDef, VecFx32 *pFrom, u32 nTable, int nRange, u16 *pVisited, short nDepth)
{
    int nId;
    int i;
    Ov015Pickup *pPickup;
    int nBest;
    Ov015SpotEntry *pLinked;
    Ov015SpotEntry *pEntry;
    int nDist;                /* the distance in the first walk, the entry index in the second (register identity) */

    nId = -1;
    nDepth++;
    *pVisited |= 1 << nTable;
    nBest = 0x400000;
    i = 0;
    if (pDef->aTable[nTable].nCount > 0) {
        do {
            pEntry = &pDef->aTable[nTable].aEntry[i];
            if (pEntry->nKind == 2) {
                pPickup = pEntry->u.pPickup;
                if ((u16)(((u32)func_020235d0(pPickup->nStateField, pPickup->nStateBit) & 0xfffe) >> 1) == 0) {
                    nDist = func_01ff8e94(pFrom, func_ov002_02076cc8(pPickup));
                    if (nBest > nDist) {
                        nBest = nDist;
                        nId = pEntry->nId;
                    }
                }
            }
            i++;
        } while (i < pDef->aTable[nTable].nCount);
    }
    if (nId != -1) {
        if (nRange > nBest + ((nDepth - 1) * 100 << 12)) {
            pEntry = func_ov015_020807f4(pSpot, pDef, nTable, nId, 0);
            pPickup = pEntry->u.pPickup;
            func_ov002_02076cc8(pPickup);   /* three position fetches whose results are unused */
            func_ov002_02076cc8(pPickup);
            func_ov002_02076cc8(pPickup);
            return nId;
        }
        return -1;
    }
    nDist = 0;
    if (pDef->aTable[nTable].nCount > 0) {
        do {
            Ov015SpotEntry *pLink;
            pLink = &pDef->aTable[nTable].aEntry[nDist];
            if (pLink->nKind == 1 && (*pVisited & (1 << pLink->nLinkTable)) == 0) {
                pLinked = func_ov015_020807f4(pSpot, pDef, pLink->nLinkTable, pLink->nLinkId, 0);
                nId = func_ov015_02080884(pSpot, pDef, &pLinked->u.position, pLink->nLinkTable, nRange, pVisited, nDepth);
                if (nId != -1) {
                    return nId;
                }
            }
            nDist++;
        } while (nDist < pDef->aTable[nTable].nCount);
    }
    return nId;
}
