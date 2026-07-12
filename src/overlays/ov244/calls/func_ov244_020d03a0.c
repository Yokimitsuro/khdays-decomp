/* Until +9 latches, accumulate the frame delta into +0x1c; once it passes 0x3333 fire the
 * 0x113/5 effect and set +9. Then unless the +0x30 gate is busy, latch sub-state 2 and dispatch. */
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
void func_ov244_020d03a0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(owner + 9) == 0) {
        int sum = *(int *)(owner + 0x1c) + *(int *)(*(int *)param_1 + 0x2c);
        *(int *)(owner + 0x1c) = sum;
        if (sum >= 0x3333) {
            func_ov107_020c5af8(*(int *)owner, 0x113, 5, *(int *)(*(int *)owner + 0x3c8) + 0x14);
            *(unsigned char *)(owner + 9) = 1;
        }
    }
    if (*(unsigned char *)(*(int *)(owner + 0x30)) != 0) return;
    *(unsigned char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
