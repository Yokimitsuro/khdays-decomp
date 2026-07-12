/* Unless the gate byte at *(owner+8) is set, mark state 4 and dispatch via c634. */
extern int func_0203c634(int, int, int);
void func_ov253_020d0b88(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 8)) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
