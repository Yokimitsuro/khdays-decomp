/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x50; once it reaches 0x1000,
 * mark sub-state 7 at *(child)+0x1c7 and dispatch with no handler. */
extern int func_0203c634(int a, int b, void *handler);
void func_ov279_020d25e8(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x50) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x50) = t;
    if (t < 0x1000) return;
    *(signed char *)(*(int *)child + 0x1c7) = 7;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
