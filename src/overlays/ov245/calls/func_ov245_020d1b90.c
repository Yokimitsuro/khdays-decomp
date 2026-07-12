/* Count the owner's +0x24 timer up; once it reaches 0x1800 mark state 2 and dispatch. */
extern int func_0203c634(int, int, int);
void func_ov245_020d1b90(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    int t = *(int *)(owner + 0x24) + *(int *)(a + 0x2c);
    *(int *)(owner + 0x24) = t;
    if (t < 0x1800) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
