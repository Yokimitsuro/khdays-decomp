/* Pose the actor (ov107 mode 2,1), run the local setup (mode 1) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov249_020d10a0(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov249_020d3c0c(int);
void func_ov249_020d3bcc(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 2, 1);
    func_ov249_020d10a0(*(int *)child, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov249_020d3c0c);
}
