/* Construct a named object: allocate 0x7c4 bytes, format a debug name via OS_SPrintf,
 * register it (+0x1a4), install the 020cc1a0 callback (+0x18c) and init. Return it. */
extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov252_020d4520[];
extern void func_ov252_020cc1a0(int);
int func_ov252_020cbf38(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x7c4);
    *(signed char *)(obj + 0x19c) = 0x4c;
    OS_SPrintf(buf, data_ov252_020d4520, 76);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)&func_ov252_020cc1a0;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
