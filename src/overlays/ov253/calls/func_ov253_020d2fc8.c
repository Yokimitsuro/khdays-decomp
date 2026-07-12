/* Unless the +0xc gate is busy, bump the +0x39c step counter; once it reaches 3 latch sub-state
 * 6, otherwise 2, and dispatch. */
extern int func_0203c634(int, int, void *);
void func_ov253_020d2fc8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 0xc)) != 0) return;
    *(signed char *)(*(int *)owner + 0x39c) = *(signed char *)(*(int *)owner + 0x39c) + 1;
    int obj = *(int *)owner;
    if (*(signed char *)(obj + 0x39c) >= 3) {
        *(unsigned char *)(obj + 0x1c7) = 6;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        *(unsigned char *)(obj + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    }
}
