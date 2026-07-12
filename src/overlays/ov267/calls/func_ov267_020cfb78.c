/* Construct a named object: allocate 0x65c bytes, format a debug name via OS_SPrintf,
 * register it (+0x1a4), install the 020d025c callback (+0x18c) and init. Return it. */
extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov267_020d5d80[];
extern void func_ov267_020d025c(int);
int func_ov267_020cfb78(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x65c);
    *(signed char *)(obj + 0x19c) = 0x5a;
    OS_SPrintf(buf, data_ov267_020d5d80, 90);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)&func_ov267_020d025c;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
