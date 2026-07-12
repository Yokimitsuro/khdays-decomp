/* Construct a named object: allocate 0x3b4 bytes, format a debug name into a local buffer via
 * OS_SPrintf, register it (ov107_020c9c24 -> +0x1a4), install the ov119_020cc02c callback (+0x18c)
 * and init via ov107_020c6624. Return the object. */
extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov119_020cf980[];
extern void func_ov119_020cc02c(int);
int func_ov119_020cbf38(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x3b4);
    *(signed char *)(obj + 0x19c) = 3;
    OS_SPrintf(buf, data_ov119_020cf980, 3);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)&func_ov119_020cc02c;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
