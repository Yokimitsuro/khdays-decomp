/* Tick the owner's +0x14 timer; on expiry mark state 4 and dispatch. */
extern int func_0203c634(int, int, int);
void func_ov218_020ccec8(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    int t = *(int *)(owner + 0x14) - *(int *)(a + 0x2c);
    *(int *)(owner + 0x14) = t;
    if (t > 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
