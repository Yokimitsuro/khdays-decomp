/* Resolve three sub-records of param_2 (at +0, +8, +0x10) against param_1 and hand the
 * triple to the 02073ecc handler; always returns 1. */
extern int func_02021980(int a, int b);
extern void func_ov002_0206de58(int a, int b, int c);
int func_ov002_02075948(int param_1, int param_2) {
    int a = func_02021980(param_1, param_2);
    int b = func_02021980(param_1, param_2 + 8);
    int c = func_02021980(param_1, param_2 + 0x10);
    func_ov002_0206de58(a, b, c);
    return 1;
}
