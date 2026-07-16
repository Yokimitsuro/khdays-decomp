/* func_ov008_0206fda0 -- build the bitmask of occupied ranks for group param_2.
 * Walks the panel's entry list (obj+0x4d4); for every entry whose group id (+0) matches and whose
 * rank (+0x18) is non-zero, sets bit (rank-1). Mask is byte-wide. */
extern unsigned short *func_ov008_020565bc(int list, int node);

unsigned int func_ov008_0206fda0(int param_1, unsigned int param_2) {
    unsigned int mask = 0;
    unsigned short *n;
    for (n = func_ov008_020565bc(param_1 + 0x4d4, 0); n != 0;
         n = func_ov008_020565bc(param_1 + 0x4d4, (int)n)) {
        if (*n == param_2) {
            int rank = *(int *)((char *)n + 0x18);
            if (rank != 0) {
                mask = (mask | 1 << (rank - 1)) & 0xff;
            }
        }
    }
    return mask;
}
