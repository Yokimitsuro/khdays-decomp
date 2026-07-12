/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x44; once it passes 0x800,
 * set +0x68 = 0x300, clear the +0x49 byte and register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov244_020d32bc(int);
void func_ov244_020d3278(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x44) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x44) = t;
    if (t <= 0x800) return;
    *(int *)(child + 0x68) = 0x300;
    *(signed char *)(child + 0x49) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov244_020d32bc);
}
