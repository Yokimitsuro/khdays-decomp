extern int func_02021980(int a, void *b);
extern void func_02033b24(int a, int b);

int func_02022460(int param_1, unsigned short *param_2) {
    int a = func_02021980(param_1, param_2);
    int b = func_02021980(param_1, param_2 + 4);
    func_02033b24(a, b);
    return 1;
}
