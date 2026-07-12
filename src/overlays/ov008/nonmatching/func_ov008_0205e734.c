/* PROVEN TIE (register allocation). Structure and arithmetic match, but mwcc
 * build 139 keeps the row base in a callee-saved register (extra push of r5)
 * while the ROM advances the incoming r0 in place. Off by the one copy/push.
 * Kept here so the ov008 blob stays byte-exact. */
int func_ov008_0205e734(int param_1, int param_2) {
    unsigned char count = 0;
    int row;
    for (row = 0; row < 3; row++) {
        int i;
        for (i = 0; i < 0x28; i++) {
            int p = *(int *)(param_1 + i * 4 + 0x19c4);
            if (p != 0 && param_2 == *(int *)(p + 0x14)) {
                count = (unsigned char)(count + 1);
            }
        }
        param_1 += 0xa0;
    }
    return count;
}
