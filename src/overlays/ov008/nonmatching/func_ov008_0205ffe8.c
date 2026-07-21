/* Scan the 3-bank card grid at +0x19c4 (3 banks x 0x28 entries) for the first slot whose card id
 * (field +0x14) falls in the reaction-command range [0xbf, 0xf0]; on a hit, cache the tier-0x1e
 * record at +0x2078 and return 1, else 0.
 *
 * NON-MATCHING (equivalent), 4 bytes over. Same loop-strength-reduction tie as func_ov008_0208b148
 * and func_ov008_02054d3c: the ROM keeps the inner counter j live and scales it inline
 * (add rX, base, j lsl#2) with only the per-bank base held, while mwcc 139 strength-reduces j*4
 * into a running pointer that it must reset (mov) each outer iteration. The early return does not
 * suppress the reduction. It appears systematic for this compiler on nested loops with a scaled
 * inner index. */
extern int func_ov008_02055c84(int obj, int idx);

int func_ov008_0205ffe8(int param_1) {
    int base = param_1;
    int i = 0;
    do {
        int j = 0;
        do {
            int e = *(int *)(base + j * 4 + 0x19c4);
            if (e != 0) {
                int v = *(int *)(e + 0x14);
                if (v >= 0xbf && v <= 0xf0) {
                    *(int *)(param_1 + 0x2078) = func_ov008_02055c84(param_1 + 0x28c, 0x1e);
                    return 1;
                }
            }
            j++;
        } while (j < 0x28);
        i++;
        base += 0xa0;
    } while (i < 3);
    return 0;
}
