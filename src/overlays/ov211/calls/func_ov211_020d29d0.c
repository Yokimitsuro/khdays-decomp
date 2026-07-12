/* Only when bit 0 of the u16 flags low byte at *(obj)+0x60 is set: copy the sub-state from
 * *(obj)+0x1c9 into +0x1c7, pick a landing point at (child)+0x6c = base(+0x224) +
 * rand(|+0x228 - +0x224| + 1) and dispatch with no handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
void func_ov211_020d29d0(int param_1) {
    int child = *(int *)(param_1 + 4);
    int obj = *(int *)child;
    int base, d;
    if ((((struct hw60 *)(obj + 0x60))->lo & 1) == 0) return;
    *(signed char *)(obj + 0x1c7) = *(signed char *)(obj + 0x1c9);
    base = *(int *)(*(int *)child + 0x224);
    d = *(int *)(*(int *)child + 0x228) - base;
    if (d < 0) d = -d;
    *(int *)(child + 0x6c) = base + func_02023eb4(d + 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
