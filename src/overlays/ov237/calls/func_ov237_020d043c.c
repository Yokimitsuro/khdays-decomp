/* Unless the child is busy, set +0x58, mark state 0xa and dispatch. */
extern int func_0203c634(int, int, int);
void func_ov237_020d043c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(int *)(owner + 0x58) = 1;
    *(signed char *)(*(int *)owner + 0x1c7) = 0xa;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
