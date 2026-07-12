/* Tick the owner's +0x3c timer; when it runs out, mark state 4 and dispatch via c634. */
extern int func_0203c634(int, int, int);
void func_ov146_020cd138(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    int t = *(int *)(owner + 0x3c) - *(int *)(a + 0x2c);
    *(int *)(owner + 0x3c) = t;
    if (t > 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
