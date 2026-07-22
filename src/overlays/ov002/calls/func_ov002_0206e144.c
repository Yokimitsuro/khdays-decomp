/* Find the registered handler whose key matches. The table hangs off +0x8d7c
 * with its entry count in the first byte and the entries from +4; each entry
 * starts with its own key halfword. Reports 0 when there is no table or no
 * match. */
typedef struct {
    unsigned char nCount;   /* +0 */
    char pad0001[3];
    void *entries[1];       /* +4 */
} Ov002HandlerTable;

typedef struct {
    char pad0000[0x8d7c];
    Ov002HandlerTable *pHandlers;   /* +0x8d7c */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

void *func_ov002_0206e144(unsigned short key) {
    int i;
    char *p;
    Ov002HandlerTable *table;
    int count;

    table = data_ov002_0207fa00->pHandlers;

    if (table != 0) {
        count = table->nCount;
        i = 0;

        if (count > 0) {
            p = (char *)table;
            do {
                if (key == **(unsigned short **)(p + 4)) {
                    return table->entries[i];
                }
                i++;
                p += 4;
            } while (i < count);
        }
    }

    return 0;
}
