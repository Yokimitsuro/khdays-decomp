/* Advances the interpolation counter and recomputes the current value, clamping it into
 * [-0x10, 0x10] and resetting the ramp when it leaves the range.
 *
 * The counter has to be bumped and stored BEFORE the low bound is read; written the other
 * way round mwcc hoists the `ldr r4,[r5]` above the increment. */
extern int func_02020400(int a, int b);

void func_ov023_020836c0(int *o) {
    int n;
    int lo;
    int v;
    n = o[2] + 1;
    o[2] = n;
    lo = o[0];
    v = lo + func_02020400(n * (o[1] - lo), o[3]);
    o[4] = v;
    if (v > 0x10 || v < -0x10) {
        if (v > 0x10) {
            v = 0x10;
        } else {
            v = -0x10;
        }
        o[4] = v;
        o[3] = 0;
        o[2] = 0;
    }
}
