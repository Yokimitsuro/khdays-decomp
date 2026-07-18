extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov128_020d4fe0[];
extern void func_ov128_020d3844(int);

int func_ov128_020d37b8(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x3c0);
    *(signed char *)(obj + 0x19c) = 7;
    OS_SPrintf(buf, data_ov128_020d4fe0, 7);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)func_ov128_020d3844;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
