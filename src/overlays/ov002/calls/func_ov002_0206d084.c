/* Find the key entry registered under the given id, or NULL.
 *
 * Ghidra models the owner as Ov002RootContext, with pKeyEntries at +0x8d14 and
 * bKeyEntryCount at +0x8d19, and the record as Ov002KeyEntry. The local structs
 * are the codegen view of those fields: reading the count straight out of the
 * loop condition, rather than through a local, is what puts the two live values
 * in the registers the original uses.
 */

extern char *data_ov002_0207fa00;

typedef struct {
    char pad00[0x40];
    short nKey;                      /* +0x40 */
    short nValue;                 /* +0x42 */
} Ov002KeyEntry;                 /* 0x44 */

typedef struct {
    Ov002KeyEntry *pKeyEntries;         /* +0x00 */
    unsigned char pad04;
    unsigned char nKeyEntryCount;           /* +0x05 */
    unsigned char pad06[2];
} Ov002KeyEntryTable;

Ov002KeyEntry *func_ov002_0206d084(int nId)
{
    int i;
    Ov002KeyEntryTable *pTable;

    pTable = (Ov002KeyEntryTable *)(data_ov002_0207fa00 + 0x8d14);

    for (i = 0; i < pTable->nKeyEntryCount; i++) {
        if (nId == pTable->pKeyEntries[i].nKey) {
            return &pTable->pKeyEntries[i];
        }
    }
    return 0;
}
