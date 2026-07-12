/* If func_ov227_020d14bc fails (<0), dispatch with a null handler and return;
 * else set anim (8 if child+0x78 else 0xc), clear +0x76/+0x75/+0x5c, dispatch. */
extern int func_ov227_020d14bc(int a, int b);
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov227_020d2b84(void);
void func_ov227_020d2b14(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (func_ov227_020d14bc(param_1, 0) < 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
        return;
    }
    func_ov107_020c9264(*(int *)child, *(int *)(child + 0x78) != 0 ? 8 : 0xc, 0);
    *(unsigned char *)(child + 0x76) = 0;
    *(unsigned char *)(child + 0x75) = 0;
    *(int *)(child + 0x5c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov227_020d2b84);
}
