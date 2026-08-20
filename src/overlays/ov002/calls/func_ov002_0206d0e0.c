/* Read the value carried by the key entry registered under the given id,
 * or -1 when no entry matches.
 *
 * Ghidra models the owner as Ov002RootContext, with pKeyEntries at +0x8d14 and
 * bKeyEntryCount at +0x8d19; the record is Ov002KeyEntry, 0x44 bytes, with the
 * signed key at +0x40 and the value this function returns at +0x42. The local
 * structs below are the codegen view of those same fields: reading the count
 * straight out of the condition, rather than through a local, is what puts the
 * two live values in the registers the original uses.
 */

extern char *data_ov002_0207fa00;

typedef struct {
    char pad0000[0x40];
    short nKey;                     /* +0x40 */
    short nValue;                   /* +0x42 */
} Ov002KeyEntry;                    /* 0x44 */

typedef struct {
    Ov002KeyEntry *pKeyEntries;     /* root context +0x8d14 */
    unsigned char pad04;
    unsigned char nKeyEntryCount;   /* root context +0x8d19 */
    unsigned char pad06[2];
} Ov002KeyEntryTable;

short func_ov002_0206d0e0(int nId)
{
    int i;
    Ov002KeyEntryTable *pTable;

    pTable = (Ov002KeyEntryTable *)(data_ov002_0207fa00 + 0x8d14);

    for (i = 0; i < pTable->nKeyEntryCount; i++) {
        if (nId == pTable->pKeyEntries[i].nKey) {
            return pTable->pKeyEntries[i].nValue;
        }
    }
    return -1;
}
