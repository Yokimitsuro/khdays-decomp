/* Unless the gate byte at *(child+0xc) is set, mark sub-state 4 and dispatch. */
extern int func_0203c634(int a, int b, void *handler);
void func_ov274_020d1780(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0xc) != 0) return;
    *(signed char *)(*(int *)child + 0x1c7) = 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
