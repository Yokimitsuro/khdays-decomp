/* func_02028df0 -- look up a 12-character name in a table and return its entry.
 *
 * The table keeps its entry count at +0x82 and a pointer to a 0x14-byte entry array at
 * +0xac; an entry starts with its name, so the comparison runs against the entry itself.
 * Returns NULL when the name is not present.
 *
 * Two things make it match. The count test is a real `if` in the source, not a for-loop's
 * zero-trip test: the ROM loads the entry array AFTER the branch, in the loop preheader,
 * which is where mwcc puts it only when the source guards the whole loop. And the source
 * walks the array with its own pointer while returning `&pEntries[i]`, which is why the
 * loop advances a register by 0x14 per iteration yet the return still pays for a multiply. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct SymbolEntry {
    char aName[0xc];
    u8   pad_0c[8];
} SymbolEntry;

typedef struct SymbolTable {
    u8  pad_0000[0x82];
    u16 nEntryCount;
    u8  pad_0084[0xac - 0x84];
    SymbolEntry *pEntries;
} SymbolTable;

extern int strncmp(const char *a, const char *b, unsigned int n);

SymbolEntry *func_02028df0(SymbolTable *pTable, const char *pName)
{
    int i;
    SymbolEntry *pEntry;
    SymbolEntry *pEntries;
    int nCount = pTable->nEntryCount;

    i = 0;
    if (nCount > 0) {
        pEntries = pTable->pEntries;
        pEntry = pEntries;
        do {
            if (strncmp(pEntry->aName, pName, 0xc) == 0) {
                return &pEntries[i];
            }
            i++;
            pEntry++;
        } while (i < nCount);
    }
    return 0;
}
