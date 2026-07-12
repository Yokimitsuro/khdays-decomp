/* If the signed flag at (*(param_1+8))+0x58 is set, forward the +0x2c subobject
 * (and param_2) to its handler. */
extern void func_ov002_0207c770(int obj, int arg);

void func_ov002_0207a57c(int param_1, int param_2) {
    if (*(signed char *)(*(int *)(param_1 + 8) + 0x58) != 0) {
        func_ov002_0207c770(param_1 + 0x2c, param_2);
    }
}
