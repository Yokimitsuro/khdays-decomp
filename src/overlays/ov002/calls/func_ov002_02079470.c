/* If bit0 of the flag byte at param_1+0x1bb is set, forward the +0x3c subobject
 * (and param_2) to its handler. */
extern void func_ov002_0207c770(int obj, int arg);

void func_ov002_02079470(int param_1, int param_2) {
    if (*(unsigned char *)(param_1 + 0x1bb) & 1) {
        func_ov002_0207c770(param_1 + 0x3c, param_2);
    }
}
