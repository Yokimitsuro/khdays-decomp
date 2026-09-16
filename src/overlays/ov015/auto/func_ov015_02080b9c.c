/* func_ov015_02080b9c -- Ov015_SpotFindEntryIdByKey: in table nTable of the spot's
 * descriptor (+0x8, tables at +0x58, 0x1c bytes each), find the entry whose key byte (+1)
 * equals nKey and return its id byte (+0); -1 when the table holds no such entry.
 * Codegen: the loop counter reuses the nTable parameter once the table pointer is
 * taken -- a fresh counter colours away from the parameter's register. */
typedef signed char s8;
typedef unsigned char u8;

typedef struct Ov015SpotEntry {
    s8  nId;                  /* 0x00 */
    s8  nKey;                 /* 0x01 */
    s8  nKind;                /* 0x02: 0 point, 1 link, 2 pickup */
    u8  pad_03[0x18 - 0x03];
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

typedef struct Ov015Spot {
    u8  pad_00[8];
    Ov015SpotDef *pDef;       /* 0x08 */
} Ov015Spot;

int func_ov015_02080b9c(Ov015Spot *pSpot, int nTable, int nKey)
{
    Ov015SpotTable *pTable;
    Ov015SpotEntry *pEntry;
    Ov015SpotEntry *aEntry;
    int nCount;

    pTable = &pSpot->pDef->aTable[nTable];
    nCount = pSpot->pDef->aTable[nTable].nCount;
    nTable = 0;                                  /* now the entry index */
    if (nCount > 0) {
        aEntry = pTable->aEntry;
        pEntry = aEntry;
        do {
            if (nKey == pEntry->nKey) {
                return aEntry[nTable].nId;
            }
            nTable++;
            pEntry++;
        } while (nTable < nCount);
    }
    return -1;
}
