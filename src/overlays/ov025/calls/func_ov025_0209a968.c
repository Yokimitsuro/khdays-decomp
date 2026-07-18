/* Single-case switch: two plain `if (...) return;` guards get if-converted into one
 * predicated chain (ldreq/cmpeq); the ROM emits two separate popne. Same shape as
 * ov008 02068588/020685d0. */
extern void func_ov025_02099d50(int *obj, int old, int now);
extern void func_02033b78(int a, int b);

void func_ov025_0209a968(int *param_1) {
    int old = *param_1;
    switch (param_1[0x8f]) {
    case 0:
        if (param_1[1] != 0) return;
        {
            int now = old - 1;
            *param_1 = now;
            if (now < 0) {
                *param_1 = 2;
            }
            func_ov025_02099d50(param_1, old, *param_1);
            func_02033b78(0, 0);
        }
        break;
    }
}
