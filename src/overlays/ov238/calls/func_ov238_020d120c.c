/* Run 020d07f0 on the motion block; unless busy, mark state 3 and dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov238_020d07f0(int, int);
void func_ov238_020d120c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov238_020d07f0(param_1, *(int *)(*(int *)owner + 0x3e0) + 0x2c);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 3;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
