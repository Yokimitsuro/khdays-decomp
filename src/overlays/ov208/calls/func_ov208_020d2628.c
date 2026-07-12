/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x2c; once it passes the
 * threshold at (child)+0x40, play the anim (ov107 mode 7) and dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov208_020d2678(int);
void func_ov208_020d2628(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x2c) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x2c) = t;
    if (t <= *(int *)(child + 0x40)) return;
    func_ov107_020c9264(*(int *)child, 7, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov208_020d2678);
}
