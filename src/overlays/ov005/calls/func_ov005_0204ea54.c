/* Dispatch to func_ov005_0204e9cc with handler func_ov005_0204e75c. */
extern int func_ov005_0204e9cc(int a, int b, int c, void *handler);
extern void func_ov005_0204e75c(void);
int func_ov005_0204ea54(int param_1, int param_2, int param_3) {
    return func_ov005_0204e9cc(param_1, param_2, param_3, (void *)&func_ov005_0204e75c);
}
