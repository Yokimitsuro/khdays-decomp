/* Pose the actor (ov107 mode 2,1), run the local setup (mode 1) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov230_020d3028(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov230_020d5b30(int);
void func_ov230_020d5af0(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 2, 1);
    func_ov230_020d3028(*(int *)child, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov230_020d5b30);
}
