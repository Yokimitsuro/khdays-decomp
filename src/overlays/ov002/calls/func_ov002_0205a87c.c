/* Where does entry `index` sit on the grid? Reports its column, and optionally
 * writes its page number -- six rows to a page -- through the out-parameter.
 *
 * The column comes from the REMAINDER of the division, which func_02020400
 * returns in r1: the high half of its long long. The division must be called by
 * address because writing `%` emits _s32_div_f, which is not linkable here. */
extern long long func_02020400(int numerator, int denominator);

typedef struct {
    char pad0000[0x30];
    unsigned char bColumns;     /* +0x30 */
} Ov002ListContext;

extern Ov002ListContext *data_ov002_0207f620;

int func_ov002_0205a87c(int *outPage, int index) {
    Ov002ListContext *ctx = data_ov002_0207f620;
    int column = (int)(func_02020400(index + 1, ctx->bColumns) >> 32);

    if (outPage != 0) {
        *outPage = column / 6;
    }

    return column;
}
