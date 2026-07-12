/* If a pending request is queued at (param_1)+0x194, resolve it against +0x3c, run the
 * follow-up, and clear the request. */
extern int func_0203c6a4(int a, int b);
extern void func_0203c640(int a);
void func_ov282_020d3fe4(int param_1) {
    int req = *(int *)(param_1 + 0x194);
    if (req == 0) return;
    func_0203c640(func_0203c6a4(*(int *)(param_1 + 0x3c), req));
    *(int *)(param_1 + 0x194) = 0;
}
