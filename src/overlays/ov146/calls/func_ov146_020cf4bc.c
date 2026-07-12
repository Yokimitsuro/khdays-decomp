/* Unless the child is busy, set bit 1 of +0x5c, mark state 0 and dispatch. */
extern int func_0203c634(int, int, int);
void func_ov146_020cf4bc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int obj = *(int *)(owner + 8);
    if (*(unsigned char *)(obj + 0xad) != 0) return;
    *(int *)(obj + 0x5c) |= 2;
    *(signed char *)(*(int *)owner + 0x1c7) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
