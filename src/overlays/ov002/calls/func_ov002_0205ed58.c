/* Advance the wrap-around cursor: step +0x7dc on by one modulo the count at
 * +0x7e0, hand the new index to func_ov002_0205eba4 and play the move sound.
 * Does nothing while the count is zero or negative.
 *
 * func_02020400 is the MetroWerks signed-divide helper: quotient in r0, remainder
 * in r1. It has to be called by address rather than written as `%` -- mwcc emits
 * the call under the name _s32_div_f, which this project does not define, so the
 * arithmetic spelling fails on the reloc even though the instructions are right.
 * The long long return picks the remainder out of r1. */
extern long long func_02020400(int a, int b);
extern void func_ov002_0205eba4(int index);
extern void func_02033b78(int a, int b);

extern char *data_ov002_0207f624;

void func_ov002_0205ed58(void) {
    char *ctx = data_ov002_0207f624;
    int count = *(int *)(ctx + 0x7e0);

    if (count <= 0) {
        return;
    }

    func_ov002_0205eba4((int)(func_02020400(*(int *)(ctx + 0x7dc) + 1, count) >> 0x20));
    func_02033b78(0, 0);
}
