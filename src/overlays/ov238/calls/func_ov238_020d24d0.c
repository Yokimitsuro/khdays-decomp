/* Copy +0x1c into +0x18, mark +0x31=2, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov238_020d24fc(int);
int func_ov238_020d24d0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x18) = *(int *)(owner + 0x1c);
    *(signed char *)(owner + 0x31) = 2;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d24fc);
}
