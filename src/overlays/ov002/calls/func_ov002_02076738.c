/* Which slot of the 0x20-entry table holds this entry? Reports -1 when it is not
 * listed. The table pointer is hoisted out of the loop so the index reduces to a
 * single walk. */
typedef struct {
    char pad0000[0x17c];
    void *entries[0x20];        /* +0x17c */
} Ov002ListTable;

typedef struct {
    char pad0000[4];
    Ov002ListTable *pTable;     /* +4 */
} Ov002ListRoot;

extern Ov002ListRoot data_ov002_0207fa20;

int func_ov002_02076738(void *entry) {
    int i;
    Ov002ListTable *table = data_ov002_0207fa20.pTable;

    for (i = 0; i < 0x20; i++) {
        if (table->entries[i] == entry) {
            return i;
        }
    }

    return -1;
}
