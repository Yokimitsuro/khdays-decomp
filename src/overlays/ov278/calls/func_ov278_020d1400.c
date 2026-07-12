/* Play the anim (ov107 mode 0x13), kick the secondary anim (ov107_020c9ee8 mode 6 on
 * *(child)+0x3ac), set the target rate (+0x14 = owner_rate*30/50), set +0x28 = 0x3000 and
 * register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov278_020d1478(int);
void func_ov278_020d1400(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0x13, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)child + 0x3ac), 6, 0);
    *(int *)(child + 0x14) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 50;
    *(int *)(child + 0x28) = 0x3000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020d1478);
}
