/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x40; once it reaches 0x5000,
 * play the anim (ov107 mode 0xc) and dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov266_020d1b4c(int);
void func_ov266_020d1b00(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x40) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x40) = t;
    if (t < 0x5000) return;
    func_ov107_020c9264(*(int *)child, 0xc, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d1b4c);
}
