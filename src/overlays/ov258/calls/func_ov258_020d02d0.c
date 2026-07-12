/* Clear +0xc/+0x10, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov258_020d02f8(int);
int func_ov258_020d02d0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0xc) = 0;
    *(signed char *)(owner + 0x10) = 0;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov258_020d02f8);
}
