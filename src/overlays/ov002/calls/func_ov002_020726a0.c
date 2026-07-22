/* Read back what a roster slot resolves to: the slot number itself, and the kind
 * byte of the peer record it points at. Both outputs are optional, and the kind
 * lookup is the one that costs a table walk, so it is guarded first. */
typedef struct {
    int reserved;
    void *entries[1];       /* +4, one peer record per roster index */
} Ov002RosterTable;

typedef struct {
    char pad0000[4];
    Ov002RosterTable *pTable;   /* +4 */
    char pad0008[0x27];
    signed char slots[4];       /* +0x2f, -1 = empty */
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207fa10;

void func_ov002_020726a0(int index, int *outKind, int *outSlot) {
    Ov002LinkCtx *ctx = data_ov002_0207fa10;
    int slot = ctx->slots[index];

    if (outKind != 0) {
        *outKind = *(signed char *)ctx->pTable->entries[slot];
    }

    if (outSlot != 0) {
        *outSlot = slot;
    }
}
