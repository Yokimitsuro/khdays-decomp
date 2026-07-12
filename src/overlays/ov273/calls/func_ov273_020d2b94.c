/* Clear +0x48, play the anim (ov107 mode 0xd), clear +0x1c / +0x68 / +0x69 / +0x60 and
 * register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov273_020d2be0(int);
void func_ov273_020d2b94(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x48) = 0;
    func_ov107_020c9264(*(int *)child, 0xd, 0);
    *(int *)(child + 0x1c) = 0;
    *(signed char *)(child + 0x68) = 0;
    *(signed char *)(child + 0x69) = 0;
    *(int *)(child + 0x60) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov273_020d2be0);
}
