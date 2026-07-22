/* Step the wrap-around cursor BACKWARDS: (cursor + count - 1) modulo count, hand
 * the new index to func_ov002_0205eba4 and play the move sound. Mirror of
 * func_ov002_0205ed58. func_02020400 is the signed-divide helper and must be
 * called by address -- `%` emits _s32_div_f, which this project does not define. */
extern long long func_02020400(int a, int b);
extern void func_ov002_0205eba4(int index);
extern void func_02033b78(int a, int b);

extern char *data_ov002_0207f624;

void func_ov002_0205ed98(void) {
    char *ctx = data_ov002_0207f624;
    int count = *(int *)(ctx + 0x7e0);

    if (count <= 0) {
        return;
    }

    func_ov002_0205eba4((int)(func_02020400(*(int *)(ctx + 0x7dc) + count - 1, count) >> 0x20));
    func_02033b78(0, 0);
}
