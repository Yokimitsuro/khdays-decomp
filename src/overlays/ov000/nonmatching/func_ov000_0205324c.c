/* func_ov000_0205324c -- NONMATCHING: 1-instr predication tie. The retail build
 * emits 'strheq; bxeq lr' (early return) then an unconditional else store; our
 * mwcc predicates the else block (strhne) instead, merging the return (-1 instr).
 * Logic is exact. Kept for the PC port. */
extern char *data_ov000_0205ac24;
void func_ov000_0205324c(int value) {
    char *base = data_ov000_0205ac24;
    if (base == 0) {
        return;
    }
    if ((short)*(int *)(base + 0x6a48) == 0) {
        *(short *)(base + 0x4af8) = value;
        return;
    }
    *(short *)(base + 0x4af8) = 0;
}
