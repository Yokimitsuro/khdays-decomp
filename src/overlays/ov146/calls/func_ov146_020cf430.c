/* Unless the child is busy, kick anim (1, phase 1), mark state 0 and dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, int);
void func_ov146_020cf430(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 8) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 1, 1);
    *(signed char *)(*(int *)owner + 0x1c7) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
