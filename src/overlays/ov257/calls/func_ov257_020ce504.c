/* Per-frame spline step: set the target rate (+0x40 = owner_rate*30/5), evaluate the
 * spline point (020cccc0 from the 01ffa724 sample into +0x10); unless the gate byte at
 * *(child+0xc) is set, mark sub-state 2 and dispatch. */
extern void func_ov257_020ccf98(int a, int b, void *out1, void *out2);
extern void func_01ffa724(int a, void *b, int c);
extern int func_0203c634(int a, int b, void *handler);
struct frame_020ce790 { int a; int b[3]; };
void func_ov257_020ce504(int param_1) {
    int owner = *(int *)param_1;
    int child = *(int *)(param_1 + 4);
    struct frame_020ce790 f;
    *(int *)(child + 0x40) = *(int *)(owner + 0x2c) * 30 / 5;
    func_ov257_020ccf98(child, *(int *)(child + 0x60), &f.b, &f.a);
    func_01ffa724(f.a, &f.b, child + 0x10);
    if (*(unsigned char *)*(int *)(child + 0xc) != 0) return;
    *(signed char *)(*(int *)child + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
