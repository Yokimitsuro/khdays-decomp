/* Unless the gate byte at *(child+0x48) is set, pick a landing point at (child)+0x64 =
 * base(+0x224) + rand(|+0x228 - +0x224| + 1), mark sub-state 2 and dispatch. */
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
void func_ov186_020d0ce0(int param_1) {
    int child = *(int *)(param_1 + 4);
    int base, d;
    if (*(unsigned char *)*(int *)(child + 0x48) != 0) return;
    base = *(int *)(*(int *)child + 0x224);
    d = *(int *)(*(int *)child + 0x228) - base;
    if (d < 0) d = -d;
    *(int *)(child + 0x64) = base + func_02023eb4(d + 1);
    *(signed char *)(*(int *)child + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
