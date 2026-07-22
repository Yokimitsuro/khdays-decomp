/* Move the caret, clamped to the row count at +0xec. Does nothing while the
 * panel's enabled bit is clear -- a one-bit bitfield, which is what the
 * lsl #31 / lsrs #31 pair reports. */
extern void func_ov002_02058e2c(unsigned int row, int arg);

typedef struct {
    char pad0000[0x48];
    unsigned int bEnabled : 1;      /* +0x48 bit 0 */
    char pad004c[0xa0];
    unsigned short wRowCount;       /* +0xec */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f618;

void func_ov002_020592f8(unsigned int row, int arg) {
    Ov002PanelContext *ctx = data_ov002_0207f618;
    unsigned int limit;

    if (ctx->bEnabled == 0) {
        return;
    }

    limit = ctx->wRowCount;
    if (row > limit) {
        row = limit;
    }

    func_ov002_02058e2c(row, arg);
}
