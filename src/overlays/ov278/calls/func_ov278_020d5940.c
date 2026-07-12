/* Unless the busy byte at *(child+0x20) is set, play the anim (ov107 mode 0xe,1), clear the
 * +0x7c byte and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov278_020d598c(int);
void func_ov278_020d5940(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0x20) != 0) return;
    func_ov107_020c9264(*(int *)child, 0xe, 1);
    *(signed char *)(child + 0x7c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020d598c);
}
