/* Resolve func_02021980(param_1) and pass it as the second arg to func_02033f88
 * (mode 0); return 1. */
extern int func_02021980(int arg);
extern void func_02033f88(int a, int b);
int func_ov024_02083488(int param_1) {
    int r = func_02021980(param_1);
    func_02033f88(0, r);
    return 1;
}
