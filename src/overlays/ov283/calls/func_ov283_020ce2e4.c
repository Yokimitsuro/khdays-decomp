/* Unless the child is busy, advance +0x50 by 0x5fa0, mark state 2 and dispatch. */
extern int func_0203c634(int, int, void *);
void func_ov283_020ce2e4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(int *)(owner + 0x50) += 0x5fa0;
    *(signed char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
