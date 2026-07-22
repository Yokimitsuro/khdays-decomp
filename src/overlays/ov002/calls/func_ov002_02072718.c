/* Reverse lookup: which of the four roster slots holds a peer of the given kind.
 * Empty slots hold -1 and are skipped; -1 is also the not-found answer, which is
 * safe because an empty slot can never match. */
typedef struct {
    int reserved;
    void *entries[1];       /* +4 */
} Ov002RosterTable;

typedef struct {
    char pad0000[4];
    Ov002RosterTable *pTable;   /* +4 */
    char pad0008[0x27];
    signed char slots[4];       /* +0x2f */
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207fa10;

int func_ov002_02072718(int kind) {
    int i;
    Ov002LinkCtx *ctx = data_ov002_0207fa10;

    for (i = 0; i < 4; i++) {
        int slot = ctx->slots[i];
        if (slot >= 0 && kind == *(signed char *)ctx->pTable->entries[slot]) {
            return slot;
        }
    }

    return -1;
}
