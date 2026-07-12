/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x1c; once it reaches 0x5000,
 * mark sub-state 0xb and dispatch with no handler. */
extern int func_0203c634(int a, int b, void *handler);
void func_ov213_020cf4b0(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x1c) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x1c) = t;
    if (t < 0x5000) return;
    *(signed char *)(*(int *)child + 0x1c7) = 0xb;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
