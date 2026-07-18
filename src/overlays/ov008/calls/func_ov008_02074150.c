/* ⚠ The bare `return;` in a value-returning function is NOT a typo -- it is what the
 * original does. The ROM's early exit is a plain `popeq {...}` that never writes r0, so on
 * that path the caller reads whatever was left there (in practice param_1, which arrives in
 * r0 and is never clobbered). Writing `return param_1;` compiles a `moveq r0,r8` the ROM
 * does not have. Keep it, and do not "fix" it. */
extern int  func_ov008_020740a0(int field, int text);
extern void func_ov008_0207410c(int *field, int pos);
int *func_ov008_02074150(int *param_1, int param_2, int param_3, int param_4) {
    int pos = 0;
    int over = 0;
    int len;
    if (param_1 == 0 || param_2 == 0 || param_4 == 0) {
        return;
    }
    len = func_ov008_020740a0((int)param_1, param_2);
    if (len > param_3) {
        pos = param_4;
        over = 1;
    }
    if (pos != 0 && pos != *param_1) {
        func_ov008_0207410c(param_1, pos);
    }
    return (int *)over;
}
