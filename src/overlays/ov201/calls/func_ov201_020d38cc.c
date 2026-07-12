/* Set the target rate (+0x60 = owner_rate*30/10), play the anim (ov107 mode 3), set bit 3
 * of the halfword at (*child)+0x1ae and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov201_020d393c(int);
void func_ov201_020d38cc(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x60) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 10;
    func_ov107_020c9264(*(int *)child, 3, 0);
    *(unsigned short *)(*(int *)child + 0x1ae) |= 8;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov201_020d393c);
}
