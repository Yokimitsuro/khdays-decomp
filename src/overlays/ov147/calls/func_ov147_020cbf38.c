extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov147_020ce8c0[];
extern void func_ov147_020cc188(int);

int func_ov147_020cbf38(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x3f8);
    *(signed char *)(obj + 0x19c) = 17;
    OS_SPrintf(buf, data_ov147_020ce8c0, 17);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)func_ov147_020cc188;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
