/* Dispatch to func_ov004_0204cf98 with handler func_ov004_0204cf60. */
extern int func_ov004_0204cf98(int a, int b, int c, void *handler);
extern void func_ov004_0204cf60(void);
int func_ov004_0204d120(int param_1, int param_2, int param_3) {
    return func_ov004_0204cf98(param_1, param_2, param_3, (void *)&func_ov004_0204cf60);
}
