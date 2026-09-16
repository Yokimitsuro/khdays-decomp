/* func_ov015_020807f4 -- Ov015_SpotDefFindEntry: search the class table's entry tables
 * (+0x58, 0x1c bytes each) for the entry whose id (bByKey == 0) or key (bByKey != 0) equals
 * nId.  A non-negative nTable restricts the search to that table; a negative one scans all
 * nine.  Returns the entry, or 0 when none matches.  The spot argument is not used.
 * Codegen: the table walker is a byte pointer with the +0x58 table base folded into each
 * access, nFirst is initialised before nEnd and declared after the entry index. */
typedef signed char s8;
typedef unsigned char u8;

typedef struct Ov015SpotEntry {
    s8  nId;                  /* 0x00 */
    s8  nKey;                 /* 0x01 */
    u8  pad_02[0x18 - 0x02];
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

Ov015SpotEntry *func_ov015_020807f4(void *pSpot, Ov015SpotDef *pDef, int nTable, int nId, int bByKey)
{
    Ov015SpotEntry *pEntry;
    int i;
    int nFirst;
    int nEnd;
    u8 *pRow;

    nFirst = 0;
    nEnd = 9;
    if (nTable >= 0) {
        nEnd = nTable + 1;
        nFirst = nTable;
    }
    if (nFirst < nEnd) {
        pRow = (u8 *)pDef + nFirst * sizeof(Ov015SpotTable);
        do {
            i = 0;
            if (((Ov015SpotTable *)(pRow + 0x58))->nCount > 0) {
                pEntry = ((Ov015SpotTable *)(pRow + 0x58))->aEntry;
                do {
                    if (bByKey == 0) {
                        if (pEntry->nId == nId) {
                            return pEntry;
                        }
                    } else if (pEntry->nKey == nId) {
                        return pEntry;
                    }
                    i++;
                    pEntry++;
                } while (i < ((Ov015SpotTable *)(pRow + 0x58))->nCount);
            }
            nFirst++;
            pRow += sizeof(Ov015SpotTable);
        } while (nFirst < nEnd);
    }
    return 0;
}
