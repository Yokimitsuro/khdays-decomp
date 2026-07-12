/* Clear the +0x78/+0x7c fields, play the anim (ov107 mode 0xa) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov236_020d41a8(int);
void func_ov236_020d416c(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x78) = 0;
    *(signed char *)(child + 0x7c) = 0;
    func_ov107_020c9264(*(int *)child, 0xa, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020d41a8);
}
