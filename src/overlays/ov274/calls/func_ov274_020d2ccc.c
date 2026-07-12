/* Clear +0x24, play the anim (ov107 mode 0xa), clear the +0x50 byte, fire
 * ov107_020c5af8(*child, 0x163, 0xb, *(child)+0x3bc + 4) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov274_020d2d28(int);
void func_ov274_020d2ccc(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x24) = 0;
    func_ov107_020c9264(*(int *)child, 0xa, 0);
    *(signed char *)(child + 0x50) = 0;
    func_ov107_020c5af8(*(int *)child, 0x163, 0xb, *(int *)(*(int *)child + 0x3bc) + 4);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov274_020d2d28);
}
