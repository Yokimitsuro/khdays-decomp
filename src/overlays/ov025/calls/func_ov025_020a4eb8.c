/* ⚠ The bare `return;` in a value-returning function is NOT a typo -- it is what the
 * original does. The ROM's early exit is a plain `popeq {...}` that never writes r0, so on
 * that path the caller reads whatever was left there (in practice param_1, which arrives in
 * r0 and is never clobbered). Writing `return param_1;` compiles a `moveq r0,r8` the ROM
 * does not have. Keep it, and do not "fix" it. */
extern int func_ov025_020a4e08(int obj, int a);
extern void func_ov025_020a4e74(int obj, int val);
int *func_ov025_020a4eb8(int *param_1, int param_2, int param_3, int param_4) {
    int sel = 0;
    int result = 0;
    if (param_1 == 0 || param_2 == 0 || param_4 == 0) {
        return;
    }
    {
        int r = func_ov025_020a4e08((int)param_1, param_2);
        if (r > param_3) {
            sel = param_4;
            result = 1;
        }
    }
    if (sel != 0 && sel != *param_1) {
        func_ov025_020a4e74((int)param_1, sel);
    }
    return (int *)result;
}
