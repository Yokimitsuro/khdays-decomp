/* Pose the actor (ov107 mode 2,1), run the local setup (mode 1) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov233_020cd49c(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov233_020d001c(int);
void func_ov233_020cffdc(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 2, 1);
    func_ov233_020cd49c(*(int *)child, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov233_020d001c);
}
