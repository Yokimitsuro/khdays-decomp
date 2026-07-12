/* Dispatch to func_0203c634 with param_1, its signed byte at +0x20, and handler func_ov146_020cec3c. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov146_020cec3c(void);
int func_ov146_020cec24(int param_1) {
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cec3c);
}
