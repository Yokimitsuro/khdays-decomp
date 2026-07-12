/* Resolve two sub-records of param_2 (at +0 and +8) against param_1 and hand the pair to
 * the 0206ca3c handler; always returns 1. */
extern int func_02021980(int a, int b);
extern void func_ov002_020743d0(int a, int b);
int func_ov002_02075924(int param_1, int param_2) {
    int a = func_02021980(param_1, param_2);
    int b = func_02021980(param_1, param_2 + 8);
    func_ov002_020743d0(a, b);
    return 1;
}
