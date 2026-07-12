/* Unless the busy byte at *(child+0x24) is set, mark sub-state 2 and dispatch with no handler. */
extern int func_0203c634(int a, int b, void *handler);
void func_ov236_020d3718(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0x24) != 0) return;
    *(signed char *)(*(int *)child + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
