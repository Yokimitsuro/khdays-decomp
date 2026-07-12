/* Clear +0x2c/+0x3c, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov238_020d2e58(int);
int func_ov238_020d2e30(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x2c) = 0;
    *(int *)(owner + 0x3c) = 0;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d2e58);
}
