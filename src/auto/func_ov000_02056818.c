typedef struct Entry {
    unsigned short key;     /* +0x00 */
    char pad[0x14 - 2];     /* +0x02 */
    int active;             /* +0x14 */
    char pad2[0x38 - 0x18]; /* +0x18 */
} Entry;

typedef struct Container {
    char pad0[0xc];
    Entry *entries;  /* +0x0c */
    char pad1[0x30 - 0x10];
    int count;       /* +0x30 */
} Container;

Entry *func_ov000_02056818(Container *c, int key) {
    Entry *p;
    int i = 0;
    int n = c->count;
    if (n > 0) {
        p = c->entries;
        do {
            if (p->active != 0) {
                if (key == c->entries[i].key) {
                    break;
                }
            }
            p++;
            i++;
        } while (i < n);
    }
    return &c->entries[i];
}
