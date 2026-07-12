/* Dispatch to func_0203c634 with param_1, its signed byte at +0x20, and handler func_ov107_020c0acc. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov107_020c0acc(void);
int func_ov107_020c0a9c(int param_1) {
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov107_020c0acc);
}
