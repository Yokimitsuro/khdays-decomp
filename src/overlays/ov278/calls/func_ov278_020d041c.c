/* Unless the busy byte at *(child+4)+0xad is set, stop the two secondary anims (ov107_020c5c14
 * on *(child)+0x3b4 and +0x3b8), set +0x24 = 0x1e000, mark sub-state 0xa and dispatch. */
extern void func_ov107_020c5c14(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
void func_ov278_020d041c(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    func_ov107_020c5c14(*(int *)(*(int *)child + 0x3b4), 0);
    func_ov107_020c5c14(*(int *)(*(int *)child + 0x3b8), 0);
    *(int *)(child + 0x24) = 0x1e000;
    *(signed char *)(*(int *)child + 0x1c7) = 0xa;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
