/* NONMATCHING: the ROM keeps the two guards as separate `cmp`/`ldmne` early-returns; mwcc fuses
 * them into a predicated chain (ldreq/cmpeq + one ldmne), 68B vs 72B. "Our compiler is smarter"
 * class. */
/* func_ov025_0209a968 -- step the ov025 tab selection back one, wrapping 0 -> 2.
 * Ignored while busy (obj[0x8f]) or mid-animation (obj[1]); notifies the change
 * (func_ov025_02099d50 with old and new) and fires UI event 0. */
extern void func_ov025_02099d50(int *obj, int old, int now);
extern void func_02033b78(int a, int b);

void func_ov025_0209a968(int *param_1) {
    int old = *param_1;
    if (param_1[0x8f] != 0) {
        return;
    }
    if (param_1[1] != 0) {
        return;
    }
    {
        int now = old - 1;
        *param_1 = now;
        if (now < 0) {
            *param_1 = 2;
        }
        func_ov025_02099d50(param_1, old, *param_1);
        func_02033b78(0, 0);
    }
}
