/* func_02028e4c -- call `pfn(pTable, prim, arg)` once for every primitive of the room table that
 * references the named point `pEntry`. The kind mask picks the lists: bit 0 the 0x88-byte
 * primitives at +0xa0 (point refs 1..2), bit 1 and bit 2 the 0x84-byte ones at +0xa4 and +0xa8
 * (point refs 0..3). A ref of 0xff is unused; each primitive is reported at most once. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct SymbolEntry {
    char aName[0xc];
    u8   pad_0c[8];
} SymbolEntry;

typedef struct RoomPrim88 {
    u8 pad_00[0x80];
    u8 aRef[3];
    u8 pad_83[5];
} RoomPrim88;

typedef struct RoomPrim84 {
    u8 pad_00[0x80];
    u8 aRef[4];
} RoomPrim84;

typedef struct SymbolTable {
    u8  pad_0000[0x7c];
    u16 nPrimACount;            /* +0x7c */
    u16 nPrimBCount;            /* +0x7e */
    u16 nPrimCCount;            /* +0x80 */
    u16 nEntryCount;            /* +0x82 */
    u8  pad_0084[0xa0 - 0x84];
    RoomPrim88 *pPrimA;         /* +0xa0 */
    RoomPrim84 *pPrimB;         /* +0xa4 */
    RoomPrim84 *pPrimC;         /* +0xa8 */
    SymbolEntry *pEntries;      /* +0xac */
} SymbolTable;

typedef void (*RoomPrimCallback)(SymbolTable *pTable, void *pPrim, int arg);

void func_02028e4c(SymbolTable *pTable, int nKinds, SymbolEntry *pEntry, RoomPrimCallback pfn, int arg)
{
    int i;
    int k;

    if (nKinds & 1) {
        for (i = 0; i < pTable->nPrimACount; i++) {
            RoomPrim88 *pPrim = &pTable->pPrimA[i];

            for (k = 1; k <= 2; k++) {
                u8 nRef = pPrim->aRef[k];

                if (nRef != 0xff && pEntry == &pTable->pEntries[nRef]) {
                    pfn(pTable, pPrim, arg);
                    break;
                }
            }
        }
    }
    if (nKinds & 2) {
        for (i = 0; i < pTable->nPrimBCount; i++) {
            RoomPrim84 *pPrim = &pTable->pPrimB[i];

            for (k = 0; k < 4; k++) {
                u8 nRef = pPrim->aRef[k];

                if (nRef != 0xff && pEntry == &pTable->pEntries[nRef]) {
                    pfn(pTable, pPrim, arg);
                    break;
                }
            }
        }
    }
    if (nKinds & 4) {
        for (i = 0; i < pTable->nPrimCCount; i++) {
            RoomPrim84 *pPrim = &pTable->pPrimC[i];

            for (k = 0; k < 4; k++) {
                u8 nRef = pPrim->aRef[k];

                if (nRef != 0xff && pEntry == &pTable->pEntries[nRef]) {
                    pfn(pTable, pPrim, arg);
                    break;
                }
            }
        }
    }
}
