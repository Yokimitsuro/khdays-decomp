extern int func_02021980(void *a, void *b);
extern void func_ov069_020b8100(int a, int b, int c);

int func_ov069_020b8518(void *arg1, char *arg2) {
    unsigned short idx = (unsigned short)*(int *)(arg2 + 4);
    int a = func_02021980(arg1, arg2 + 8);
    int b = func_02021980(arg1, arg2 + 0x10);
    func_ov069_020b8100(idx, a, b);
    return 1;
}
