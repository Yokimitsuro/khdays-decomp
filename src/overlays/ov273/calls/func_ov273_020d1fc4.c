/* Set the target rate (+0x48 = owner_rate*30/10), play the anim (ov107 mode 0x12) and register
 * the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov273_020d2020(int);
void func_ov273_020d1fc4(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x48) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 10;
    func_ov107_020c9264(*(int *)child, 0x12, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov273_020d2020);
}
