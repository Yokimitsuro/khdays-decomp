/* Look up the current row's label id in the table at +0x480. Which byte carries
 * the key depends on the record kind: kind 9 keeps it at +6, everything else at
 * +3. Reports 0 when the table has no entry. */
extern unsigned short *func_02010154(void *table, unsigned short key);

typedef struct {
    char pad0000[1];
    unsigned char bKind;        /* +1 */
    char pad0002[1];
    unsigned char bKeyA;        /* +3 */
    char pad0004[2];
    unsigned char bKeyB;        /* +6 */
    char pad0007[0x479];
    char table[1];              /* +0x480 */
} Ov002LabelContext;

extern Ov002LabelContext *data_ov002_0207f620;

int func_ov002_0205dfe8(void) {
    Ov002LabelContext *ctx = data_ov002_0207f620;
    unsigned short label = 0;
    unsigned short *found;
    int key;

    if (ctx->bKind == 9) {
        key = ctx->bKeyB;
    } else {
        key = ctx->bKeyA;
    }

    found = func_02010154(ctx->table, (unsigned short)key);
    if (found != 0) {
        label = *found;
    }

    return label;
}
