/* If ov212_020cd63c(child, 1) reports ready, register the handler and return. Otherwise, unless
 * ov212_020cd63c(child, 0) is still busy, mark sub-state 2 and dispatch with no handler. */
extern int func_ov267_020d124c(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov267_020d3058(int);
void func_ov267_020d2fec(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (func_ov267_020d124c(child, 1) != 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov267_020d3058);
        return;
    }
    if (func_ov267_020d124c(child, 0) != 0) return;
    *(signed char *)(*(int *)child + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
