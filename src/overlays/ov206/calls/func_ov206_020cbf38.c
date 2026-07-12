/* Construct a named object: allocate 0x3e4 bytes, format a debug name via OS_SPrintf,
 * register it (+0x1a4), install the 020cbfc4 callback (+0x18c) and init. Return it. */
extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov206_020d0660[];
extern void func_ov206_020cbfc4(int);
int func_ov206_020cbf38(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x3e4);
    *(signed char *)(obj + 0x19c) = 41;
    OS_SPrintf(buf, data_ov206_020d0660, 41);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)&func_ov206_020cbfc4;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
