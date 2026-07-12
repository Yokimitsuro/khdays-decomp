/* Play the anim (ov107 mode 3,1) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov277_020d2754(int);
void func_ov277_020d2720(int param_1) {
    func_ov107_020c9264(*(int *)*(int *)(param_1 + 4), 3, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov277_020d2754);
}
