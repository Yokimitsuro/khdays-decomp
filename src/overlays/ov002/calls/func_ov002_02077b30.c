/* Take the next free entry of kind 1 and register it with the owner object at
 * +0x5c. A full table reports a negative id, which is handed back untouched. */
extern int func_ov002_02077560(int kind);
extern void func_02025668(void *owner, int id);

typedef struct {
    char pad0000[0x5c];
    void *pOwner;               /* +0x5c */
} Ov002EntryTable;

typedef struct {
    char pad0000[4];
    Ov002EntryTable *pTable;    /* +4 */
} Ov002EntryRoot;

extern Ov002EntryRoot data_ov002_0207fa28;

int func_ov002_02077b30(void) {
    int id = func_ov002_02077560(1);

    if (id >= 0) {
        func_02025668(data_ov002_0207fa28.pTable->pOwner, id);
    }

    return id;
}
