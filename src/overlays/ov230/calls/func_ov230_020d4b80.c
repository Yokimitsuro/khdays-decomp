/* Count the timer at (child)+0x4c down by the owner rate (+0x2c); while it stays
 * positive keep waiting, otherwise stop the anim (ov107 mode 0x15) and dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov230_020d4bcc(int);
void func_ov230_020d4b80(int param_1) {
    int child = *(int *)(param_1 + 4);
    int c = *(int *)(child + 0x4c) - *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x4c) = c;
    if (c > 0) return;
    func_ov107_020c9264(*(int *)child, 0x15, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov230_020d4bcc);
}
