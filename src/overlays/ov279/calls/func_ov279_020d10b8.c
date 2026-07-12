/* Play the anim (ov107 mode 3,1), pick a landing point at (child)+0x50 = base(+0x224) +
 * rand(|+0x228 - +0x224| + 1), then register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov279_020d1110(int);
void func_ov279_020d10b8(int param_1) {
    int child = *(int *)(param_1 + 4);
    int base, d;
    func_ov107_020c9264(*(int *)child, 3, 1);
    base = *(int *)(*(int *)child + 0x224);
    d = *(int *)(*(int *)child + 0x228) - base;
    if (d < 0) d = -d;
    *(int *)(child + 0x50) = base + func_02023eb4(d + 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov279_020d1110);
}
