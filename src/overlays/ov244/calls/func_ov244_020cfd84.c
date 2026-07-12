/* Unless the busy byte at *(child+0x30) is set, map the counter at (child)+0x10 (0..3) to a
 * sub-state (4..7), advance the counter modulo 4 and dispatch with no handler. */
extern int func_0203c634(int a, int b, void *handler);
void func_ov244_020cfd84(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0x30) != 0) return;
    switch (*(short *)(child + 0x10)) {
    case 0: *(signed char *)(*(int *)child + 0x1c7) = 4; break;
    case 1: *(signed char *)(*(int *)child + 0x1c7) = 5; break;
    case 2: *(signed char *)(*(int *)child + 0x1c7) = 6; break;
    case 3: *(signed char *)(*(int *)child + 0x1c7) = 7; break;
    }
    *(short *)(child + 0x10) = (*(short *)(child + 0x10) + 1) % 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
