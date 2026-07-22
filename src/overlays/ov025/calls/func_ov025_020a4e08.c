/* Lay out `count` items and report the widest line produced. The helper consumes
 * as many as fit and writes back how many are left, so the loop runs until it
 * has placed them all -- capped at five passes so a helper that never consumes
 * anything cannot hang the frame. */
extern int func_02013768(int a, int b, int count, int *remaining);

typedef struct {
    char pad0000[0x20];
    int nA;     /* +0x20 */
    int nB;     /* +0x24 */
} Ov008Layout;

int func_ov025_020a4e08(Ov008Layout *self, int count) {
    int widest = 0;
    int remaining = 0;
    int pass;

    if (self == 0) {
        return 0;
    }

    if (count == 0) {
        return 0;
    }

    pass = 0;
    while (count != 0 && pass < 5) {
        int width = func_02013768(self->nA, self->nB, count, &remaining);

        if (width > widest) {
            widest = width;
        }

        pass++;
        count = remaining;
    }

    return widest;
}
