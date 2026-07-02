extern void func_0203c83c(int a, int b);
extern int *func_01fffca8(int a, int b, int c);
int func_0203bfb4(int param_1, int param_2) {
    int *p;
    func_0203c83c(param_2, param_1);
    p = func_01fffca8(param_1 + 0x88, 4, 0x64);
    *p = param_2;
    return 0;
}
