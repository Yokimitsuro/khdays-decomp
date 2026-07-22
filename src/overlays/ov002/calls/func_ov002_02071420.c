/* Find the 8-byte row whose first byte matches `key` inside the peer record at
 * roster index `index`. The row count is the signed byte at +1 of the record and
 * the rows hang off +0x1c. Reports 0 when the record has no rows or none match.
 *
 * The row address is rebuilt from base + i * 8 on the hit rather than handed
 * back as the walking pointer: the ROM keeps a pointer for the scan and does the
 * multiply once, at the exit. */
typedef struct {
    int reserved;
    void *entries[1];       /* +4 */
} Ov002RosterTable;

typedef struct {
    char pad0000[4];
    Ov002RosterTable *pTable;   /* +4 */
} Ov002LinkCtx;

typedef struct {
    char pad0000[1];
    signed char nRows;      /* +1 */
    char pad0002[0x1a];
    char *pRows;            /* +0x1c, stride 8, key in byte 0 */
} Ov002PeerRecord;

extern Ov002LinkCtx *data_ov002_0207fa10;

char *func_ov002_02071420(int key, int index) {
    Ov002LinkCtx *ctx = data_ov002_0207fa10;
    Ov002PeerRecord *rec = (Ov002PeerRecord *)ctx->pTable->entries[index];
    int i = 0;
    char *p;
    char *rows;
    int count = rec->nRows;

    if (count > 0) {
        rows = rec->pRows;
        p = rows;
        do {
            if (key == (unsigned char)*p) {
                return rows + i * 8;
            }
            i++;
            p += 8;
        } while (i < count);
    }

    return 0;
}
