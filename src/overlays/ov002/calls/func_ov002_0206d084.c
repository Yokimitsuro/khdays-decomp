extern char *data_ov002_0207fa00;

typedef struct {
    char pad00[0x40];
    short nId;                      /* +0x40 */
    short pad42;
} Ov002NamedEntry;                  /* 0x44 */

typedef struct {
    Ov002NamedEntry *pList;         /* +0x00 */
    unsigned char pad04;
    unsigned char nCount;           /* +0x05 */
    unsigned char pad06[2];
} Ov002NameTable;

/* Find the registered entry carrying the given id, or NULL. */
Ov002NamedEntry *func_ov002_0206d084(int nId)
{
    int i;
    Ov002NameTable *pTable;

    pTable = (Ov002NameTable *)(data_ov002_0207fa00 + 0x8d14);

    for (i = 0; i < pTable->nCount; i++) {
        if (nId == pTable->pList[i].nId) {
            return &pTable->pList[i];
        }
    }
    return 0;
}
