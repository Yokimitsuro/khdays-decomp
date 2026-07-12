/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x40; once it passes 0x200,
 * reset it and dispatch. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov210_020d43a4(int);
void func_ov210_020d4368(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x40) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x40) = t;
    if (t <= 0x200) return;
    *(int *)(child + 0x40) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov210_020d43a4);
}
