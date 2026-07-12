/* Construct a named object: allocate 0x65c bytes, format a debug name via OS_SPrintf,
 * register it (+0x1a4), install the 020ce43c callback (+0x18c) and init. Return it. */
extern int func_0203d15c(int a);
extern void OS_SPrintf(char *buf, const char *fmt, int a);
extern int func_ov107_020c9c24(char *buf);
extern void func_ov107_020c6624(int a, int b);
extern const char data_ov266_020d3f60[];
extern void func_ov266_020ce43c(int);
int func_ov266_020cdd58(int param_1) {
    char buf[0x1d] = {0};
    int obj = func_0203d15c(0x65c);
    *(signed char *)(obj + 0x19c) = 0x5a;
    OS_SPrintf(buf, data_ov266_020d3f60, 90);
    *(int *)(obj + 0x1a4) = func_ov107_020c9c24(buf);
    *(int *)(obj + 0x18c) = (int)&func_ov266_020ce43c;
    func_ov107_020c6624(obj, param_1);
    return obj;
}
