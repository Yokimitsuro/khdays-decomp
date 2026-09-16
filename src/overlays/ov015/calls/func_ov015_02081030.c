/* func_ov015_02081030 -- Ov015_SpotDefCollectLinkedMasks: starting at table nTable of
 * the spot's class table, mark it visited (bit nTable of *pVisited), follow its four link
 * bytes (+0x18..+0x1b) into the tables they name -- stopping a walk that comes back to the
 * root table nRoot below the top level -- and OR the two 64-bit masks of every table
 * reached (+0x8 and +0x10) into pMask[0] / pMask[1]. */
typedef signed char        s8;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef struct Ov015SpotTable {
    s8  nCount;               /* 0x00 */
    u8  pad_01[3];
    void *aEntry;             /* 0x04 */
    u64 nMaskA;               /* 0x08 */
    u64 nMaskB;               /* 0x10 */
    s8  aLink[4];             /* 0x18: linked table ids, -1 = none */
} Ov015SpotTable;

typedef struct Ov015SpotDef {
    u8  pad_00[0x58];
    Ov015SpotTable aTable[9]; /* 0x58 */
} Ov015SpotDef;

typedef struct Ov015Spot {
    u8  pad_00[8];
    Ov015SpotDef *pDef;       /* 0x08 */
} Ov015Spot;

void func_ov015_02081030(Ov015Spot *pSpot, int nRoot, u32 nTable, int nDepth, u16 *pVisited, u64 *pMask)
{
    Ov015SpotTable *pTable;
    int nLink;
    int j;

    pTable = &pSpot->pDef->aTable[nTable];
    *pVisited |= 1 << nTable;
    for (j = 0; j < 4; j++) {
        nLink = pTable->aLink[j];
        if (nLink >= 0) {
            if (nRoot == nLink && nDepth != 0) {
                return;
            }
            if ((*pVisited & (1 << nLink)) == 0) {
                func_ov015_02081030(pSpot, nRoot, nLink, nDepth + 1, pVisited, pMask);
            }
        }
    }
    pMask[0] |= pTable->nMaskA;
    pMask[1] |= pTable->nMaskB;
}
