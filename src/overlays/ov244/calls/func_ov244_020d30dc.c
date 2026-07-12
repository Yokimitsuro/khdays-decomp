/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x44. The first time the timer
 * falls in [0x555, 0x800) (latched by the +0x49 byte), set the latch, run ov244_020d1d68, and
 * unless the busy byte at *(child+0xc) is set, pick a landing point at (child)+0x4c = base(+0x224)
 * + rand(|+0x228 - +0x224| + 1) and mark sub-state 2. Always dispatch with no handler. */
extern void func_ov244_020d1d68(int a, int b);
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
void func_ov244_020d30dc(int param_1) {
    int child = *(int *)(param_1 + 4);
    int base, d;
    *(int *)(child + 0x44) += *(int *)(*(int *)param_1 + 0x2c);
    if (*(unsigned char *)(child + 0x49) == 0 && *(int *)(child + 0x44) >= 0x555 &&
        *(int *)(child + 0x44) < 0x800) {
        *(signed char *)(child + 0x49) = 1;
        func_ov244_020d1d68(child, 0);
    }
    if (*(unsigned char *)*(int *)(child + 0xc) != 0) return;
    base = *(int *)(*(int *)child + 0x224);
    d = *(int *)(*(int *)child + 0x228) - base;
    if (d < 0) d = -d;
    *(int *)(child + 0x4c) = base + func_02023eb4(d + 1);
    *(signed char *)(*(int *)child + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
