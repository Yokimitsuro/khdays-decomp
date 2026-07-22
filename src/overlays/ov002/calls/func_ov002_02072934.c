/* Report the seat's tick budget scaled by five: the local seat reads its own value from
 * +0x2294, every other seat reads it out of its peer record at +0x14.
 *
 * The peer record is fetched unconditionally, before the local-seat test -- the
 * ROM has one path into the table and branches only over the return. */
typedef struct {
    int reserved;
    void *entries[1];       /* +4 */
} Ov002RosterTable;

typedef struct {
    char pad0000[4];
    Ov002RosterTable *pTable;   /* +4 */
    char pad0008[0x228c];
    int nLocalBudget;           /* +0x2294 */
    char pad2298[0];
    signed char bLocalSeat;      /* +0x2298 */
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207fa10;

int func_ov002_02072934(int seat) {
    Ov002LinkCtx *ctx = data_ov002_0207fa10;
    char *rec = (char *)ctx->pTable->entries[seat];

    if (seat == ctx->bLocalSeat) {
        return ctx->nLocalBudget * 5;
    }

    return *(int *)(rec + 0x18);
}
