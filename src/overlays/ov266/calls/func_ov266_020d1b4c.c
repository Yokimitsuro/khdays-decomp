/* Unless the busy byte at *(child+4)+0xad is set, mark sub-state 0xb at *(child)+0x1c7 and
 * dispatch with no handler. */
extern int func_0203c634(int a, int b, void *handler);
void func_ov266_020d1b4c(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)child + 0x1c7) = 0xb;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
