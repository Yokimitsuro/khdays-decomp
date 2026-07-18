extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov190_020d5ce0[];
extern void func_ov190_020d3844(int);

int func_ov190_020d37b8(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x3e8);
    *(signed char *)(obj + 0x19c) = 34;
    OS_SPrintf(buf, data_ov190_020d5ce0, 34);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)func_ov190_020d3844;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
