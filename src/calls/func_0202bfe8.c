/* func_0202bfe8 -- search every symbol table in one group for an 8-character name.
 *
 * func_0202bfa0 returns the group's 8-byte descriptor: a table count at +2 and a pointer
 * to an array of table pointers at +4. Each table has the same layout the already-matched
 * sibling func_02028df0 walks (entry count at +0x82, 0x14-byte entry array at +0xac, name
 * first in the entry), so the inner loop is that function's loop with a length of 8 instead
 * of 0xc. Null table slots are skipped. Returns the entry, or NULL if the name is absent.
 *
 * Structure copied from src/calls/func_02028df0.c: the count tests are real `if` guards, not
 * for-loop zero-trip tests, which is what puts each array load in the loop preheader after
 * the branch. Unlike that sibling this one returns the walking pointer itself, so there is
 * no index multiply on the return path. Declaration order of the locals is load-bearing for
 * the callee-saved colouring: ppTables must be declared ahead of nTableCount. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct SymbolEntry {
    char aName[8];
    u8   pad_08[0x14 - 8];
} SymbolEntry;

typedef struct SymbolTable {
    u8  pad_0000[0x82];
    u16 nEntryCount;
    u8  pad_0084[0xac - 0x84];
    SymbolEntry *pEntries;
} SymbolTable;

typedef struct SymbolTableList {
    u16 field_00;
    u16 nTableCount;
    SymbolTable **ppTables;
} SymbolTableList;

extern SymbolTableList *func_0202bfa0(int nGroup);
extern int strncmp(const char *a, const char *b, unsigned int n);

SymbolEntry *func_0202bfe8(int nGroup, const char *pName)
{
    int i;
    SymbolEntry *pEntry;
    int j;
    int nCount;
    SymbolTable **ppTables;
    int nTableCount;
    SymbolTableList *pList;
    SymbolTable *pTable;

    pList = func_0202bfa0(nGroup);
    nTableCount = pList->nTableCount;
    i = 0;

    if (nTableCount > 0) {
        ppTables = pList->ppTables;
        do {
            pTable = ppTables[i];
            if (pTable != 0) {
                nCount = pTable->nEntryCount;
                j = 0;
                pEntry = pTable->pEntries;
                if (nCount > 0) {
                    do {
                        if (strncmp(pEntry->aName, pName, 8) == 0) {
                            return pEntry;
                        }
                        j++;
                        pEntry++;
                    } while (j < nCount);
                }
            }
            i++;
        } while (i < nTableCount);
    }
    return 0;
}
