extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov173_020cecc0[];
extern void func_ov173_020cc020(int);

int func_ov173_020cbf38(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x3ac);
    *(signed char *)(obj + 0x19c) = 29;
    OS_SPrintf(buf, data_ov173_020cecc0, 29);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)func_ov173_020cc020;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
