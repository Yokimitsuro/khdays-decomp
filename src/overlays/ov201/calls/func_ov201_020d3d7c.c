/* Mark sub-state 2, pick a landing point at (child)+0x80 = base(+0x224) + rand(|+0x228 -
 * +0x224| + 1) and dispatch with no handler. */
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
void func_ov201_020d3d7c(int param_1) {
    int child = *(int *)(param_1 + 4);
    int base, d;
    *(signed char *)(*(int *)child + 0x1c7) = 2;
    base = *(int *)(*(int *)child + 0x224);
    d = *(int *)(*(int *)child + 0x228) - base;
    if (d < 0) d = -d;
    *(int *)(child + 0x80) = base + func_02023eb4(d + 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
