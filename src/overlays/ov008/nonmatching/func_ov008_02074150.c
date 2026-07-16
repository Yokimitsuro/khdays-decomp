/* NONMATCHING: register-allocation tie — the guard's `return param_1` is a bare predicated
 * `ldmeq` in the ROM (r0 still holds param_1, never clobbered); mwcc allocates param_1 to r8 and
 * emits a redundant `moveq r0,r8` before the ldmeq (92B vs 88B). */
/* func_ov008_02074150 -- scroll a text field to param_4 if the measured length
 * (func_ov008_020740a0) exceeds param_3; updates the head pointer when it actually changes
 * (func_ov008_0207410c). Returns whether it overflowed. */
extern int  func_ov008_020740a0(int field, int text);
extern void func_ov008_0207410c(int *field, int pos);

int *func_ov008_02074150(int *param_1, int param_2, int param_3, int param_4) {
    int pos = 0;
    int over = 0;
    int len;
    if (param_1 == 0 || param_2 == 0 || param_4 == 0) {
        return param_1;
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
