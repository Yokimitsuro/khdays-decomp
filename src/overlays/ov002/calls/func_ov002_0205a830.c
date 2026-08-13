/* How wide is the last row of a list of `count` entries, and which page does it end on?
 *
 * The count is rounded up to a whole row before the division, so the column the caller gets back
 * is the position of the final entry in its row. The page number, six rows to a page, goes out
 * through the optional out-parameter.
 *
 * As in the sibling at 0205a87c, the division has to be called by address: the column is the
 * REMAINDER, which func_02020400 returns in r1, the high half of its long long. Writing `%` instead
 * emits _s32_div_f, which is not linkable here. */
extern long long func_02020400(int numerator, int denominator);

typedef struct {
    char pad0000[0x30];
    unsigned char bColumns;     /* +0x30 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

int func_ov002_0205a830(int *outPage, int count) {
    Ov002PanelSession *ctx = data_ov002_0207f620;
    int column = (int)(func_02020400(count + ctx->bColumns - 1, ctx->bColumns) >> 32);

    if (outPage != 0) {
        *outPage = column / 6;
    }

    return column;
}
