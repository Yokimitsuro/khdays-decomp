/* When param_1/param_2/param_4 are all non-null: query func_ov008_0206f864(param_1,
 * NONMATCHING (4B register-alloc tie): semantically exact but mwcc homes param_1 in r8
 * and emits a redundant `moveq r0,r8` before the predicated early-return `popeq`, where
 * the ROM keeps param_1 in r0 throughout. 4-member family ov008/... .
 * param_2); if it exceeds param_3, select param_4 as the new value and flag success. If a
 * value was selected and it differs from *param_1, commit it via func_ov008_0206f8d0.
 * Returns the success flag on the active path, or param_1 unchanged when a guard failed. */
extern int func_ov008_0206f864(int obj, int a);
extern void func_ov008_0206f8d0(int obj, int val);
int *func_ov008_0206f914(int *param_1, int param_2, int param_3, int param_4) {
    int sel = 0;
    int result = 0;
    if (param_1 == 0 || param_2 == 0 || param_4 == 0) {
        return param_1;
    }
    {
        int r = func_ov008_0206f864((int)param_1, param_2);
        if (r > param_3) {
            sel = param_4;
            result = 1;
        }
    }
    if (sel != 0 && sel != *param_1) {
        func_ov008_0206f8d0((int)param_1, sel);
    }
    return (int *)result;
}
