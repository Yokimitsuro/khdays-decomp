/* Set +0x1c=0x300, mark state 4, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
int func_ov218_020cddf8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x1c) = 0x300;
    *(signed char *)(*(int *)owner + 0x1c7) = 4;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
