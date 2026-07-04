extern int func_02021980(int a, void *b);
extern void func_02033bb4(int a, int b, int c);

int func_02022484(int param_1, unsigned short *param_2) {
    int a = func_02021980(param_1, param_2);
    int b = func_02021980(param_1, param_2 + 4);
    int c = func_02021980(param_1, param_2 + 8);
    func_02033bb4(a, b, c);
    return 1;
}
