/* Accumulate the owner rate (+0x2c) into the child timer (+0x4c); once it reaches
 * 0x666, stop the anim, run func_ov230_020d3028, reset the timer, and dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov230_020d3028(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov230_020d37b4(void);
void func_ov230_020d374c(int param_1) {
    int child = *(int *)(param_1 + 4);
    int c = *(int *)(child + 0x4c) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x4c) = c;
    if (c < 0x666) return;
    func_ov107_020c9264(*(int *)child, 0, 0);
    func_ov230_020d3028(*(int *)child, 0);
    *(int *)(child + 0x4c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov230_020d37b4);
}
