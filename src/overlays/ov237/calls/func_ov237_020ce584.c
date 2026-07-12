/* If +0x4ac is live, push angle/5 into +0x494 and mirror it into the linked node at +0x4a4,
 * then latch sub-state 2 and dispatch with no callback. */
extern int func_0203c634(int, int, void *);
void func_ov237_020ce584(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(int *)(*(int *)owner + 0x4ac) != 0) {
        *(int *)(*(int *)owner + 0x494) = (short)*(short *)(*(int *)owner + 0x218) / 5;
        *(int *)(*(int *)(*(int *)owner + 0x4a4) + 0x494) = *(int *)(*(int *)owner + 0x494);
    }
    *(unsigned char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
