/* Play the anim (ov107 mode 0,1) on *child and dispatch (no handler). */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
void func_ov236_020d413c(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
