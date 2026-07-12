/* Clear +0x34/+0x38, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov259_020d22b0(int);
int func_ov259_020d2288(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x34) = 0;
    *(signed char *)(owner + 0x38) = 0;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov259_020d22b0);
}
