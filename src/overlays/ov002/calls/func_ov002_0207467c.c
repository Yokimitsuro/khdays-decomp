/* Query func_02021980(param_1); report to func_ov002_0206aae4 whether it was
 * nonzero and its low byte. Always returns 1. */
extern int func_02021980(void *arg);
extern void func_ov002_0206aae4(int present, int value);

int func_ov002_0207467c(void *param_1) {
    int x = func_02021980(param_1);
    func_ov002_0206aae4(x != 0, (unsigned char)x);
    return 1;
}
