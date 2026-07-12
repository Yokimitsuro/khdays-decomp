/* Set the target rate (+0x3c = owner_rate*30/15), play the anim (ov107 mode 3), set bit 8 of the
 * u16 at *(child)+0x1ae and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov126_020d197c(int);
void func_ov126_020d1908(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x3c) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 15;
    func_ov107_020c9264(*(int *)child, 3, 0);
    *(unsigned short *)(*(int *)child + 0x1ae) |= 8;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov126_020d197c);
}
