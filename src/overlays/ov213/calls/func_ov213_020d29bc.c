/* Count the timer at (child)+8 down by the owner rate (+0x2c); once it goes negative, play the
 * anim (ov107 mode 0), clear +8 and the +0xc/+0xd bytes and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov213_020d2a14(int);
void func_ov213_020d29bc(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 8) - *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 8) = t;
    if (t >= 0) return;
    func_ov107_020c9264(*(int *)child, 0, 0);
    *(int *)(child + 8) = 0;
    *(signed char *)(child + 0xc) = 0;
    *(signed char *)(child + 0xd) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov213_020d2a14);
}
