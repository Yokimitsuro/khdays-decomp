/* Play the anim (ov107 mode 2) on *child and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov253_020cde24(int);
void func_ov253_020cddf0(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 2, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020cde24);
}
