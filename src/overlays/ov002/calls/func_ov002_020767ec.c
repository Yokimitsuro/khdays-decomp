/* Park the entry in the first free slot of the 0x40-slot spare table at +0x7c.
 * A full table leaves the slot pointer null and the store goes to address 0 --
 * that is what the ROM does, so the table is expected never to fill. */
typedef struct {
    char pad0000[0x7c];
    void *spare[0x40];          /* +0x7c */
} Ov002ListTable;

typedef struct {
    char pad0000[4];
    Ov002ListTable *pTable;     /* +4 */
} Ov002ListRoot;

extern Ov002ListRoot data_ov002_0207fa20;

void func_ov002_020767ec(void *entry) {
    Ov002ListTable *table = data_ov002_0207fa20.pTable;
    int i;
    void **slot = 0;

    for (i = 0; i < 0x40; i++) {
        if (table->spare[i] == 0) {
            slot = &table->spare[i];
            break;
        }
    }

    *slot = entry;
}
