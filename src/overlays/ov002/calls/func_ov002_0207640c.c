/* Retire every live entry of the 0x20-slot table at +0x17c, slot 0x1f excepted --
 * that one is the scratch slot and is torn down elsewhere. Each entry is
 * unhooked by index first, then released. */
extern void func_ov002_02076450(int index);
extern void func_ov002_020769f0(void *entry);

typedef struct {
    char pad0000[0x17c];
    void *entries[0x20];        /* +0x17c */
} Ov002ListTable;

typedef struct {
    char pad0000[4];
    Ov002ListTable *pTable;     /* +4 */
} Ov002ListRoot;

extern Ov002ListRoot data_ov002_0207fa20;

void func_ov002_0207640c(void) {
    Ov002ListTable *table = data_ov002_0207fa20.pTable;
    int i;

    for (i = 0; i < 0x20; i++) {
        void *entry = table->entries[i];

        if (i != 0x1f && entry != 0) {
            func_ov002_02076450(i);
            func_ov002_020769f0(entry);
        }
    }
}
