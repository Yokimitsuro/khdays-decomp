/* Dispatch to func_ov004_0204cf98 with handler func_ov004_0204cf4c. */
extern int func_ov004_0204cf98(int a, int b, int c, void *handler);
extern void func_ov004_0204cf4c(void);
int func_ov004_0204d10c(int param_1, int param_2, int param_3) {
    return func_ov004_0204cf98(param_1, param_2, param_3, (void *)&func_ov004_0204cf4c);
}
