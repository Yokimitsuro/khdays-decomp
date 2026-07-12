/* Unless the busy byte at *(child+0x30) is set, play the anim (ov107 mode 6), clear +0x1c and
 * the +9 byte and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov244_020d0a64(int);
void func_ov244_020d0a14(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0x30) != 0) return;
    func_ov107_020c9264(*(int *)child, 6, 0);
    *(int *)(child + 0x1c) = 0;
    *(signed char *)(child + 9) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov244_020d0a64);
}
