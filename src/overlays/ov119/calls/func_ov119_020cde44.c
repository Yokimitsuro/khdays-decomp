/* Set the target rate (+0x2c = owner_rate*30/10), play the anim (ov107 mode 1,1), pick a
 * landing point at (child)+0x50 = base(+0x224) + rand(|+0x228 - +0x224| + 1) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov119_020cdec4(int);
void func_ov119_020cde44(int param_1) {
    int child = *(int *)(param_1 + 4);
    int base, d;
    *(int *)(child + 0x2c) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 10;
    func_ov107_020c9264(*(int *)child, 1, 1);
    base = *(int *)(*(int *)child + 0x224);
    d = *(int *)(*(int *)child + 0x228) - base;
    if (d < 0) d = -d;
    *(int *)(child + 0x50) = base + func_02023eb4(d + 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov119_020cdec4);
}
