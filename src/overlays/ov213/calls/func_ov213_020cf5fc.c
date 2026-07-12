/* Reset +0xc/+0x14 and set +0x10 = -0x800; unless the busy byte at *(child+8) is set, play the
 * anim (ov107 mode 0x11) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov213_020cf650(int);
void func_ov213_020cf5fc(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0xc) = 0;
    *(int *)(child + 0x10) = -0x800;
    *(int *)(child + 0x14) = 0;
    if (*(unsigned char *)*(int *)(child + 8) != 0) return;
    func_ov107_020c9264(*(int *)child, 0x11, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov213_020cf650);
}
