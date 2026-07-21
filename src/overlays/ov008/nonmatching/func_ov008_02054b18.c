/* Push up to two subitem values (columns +0x34 for normal, +0x44 for alt) from param_2's row pair
 * into the subitem table, skipping -1 index/value entries; then record the alt flag in bit 0 of
 * +0x84.
 *
 * NON-MATCHING (equivalent), size-exact. Same loop-strength-reduction tie as func_ov008_02054d3c
 * (its single-column sibling), func_ov008_0208b148, and func_ov008_0205ffe8: the ROM keeps the
 * counter i live and computes param_2 + i<<2 inline each iteration with param_2 held in a register,
 * while mwcc 139 strength-reduces to a running pointer it must seed (mov) and step (add #4),
 * spending two extra callee-saved registers. Systematic for this compiler on `base + i*stride`
 * loops; no spelling suppresses it. */
extern void func_02032634(int obj, int idx, unsigned int val);

void func_ov008_02054b18(int param_1, int param_2, int param_3) {
    int i = 0;
    do {
        int idx = *(int *)(param_2 + i * 4 + 0x14);
        if (idx != -1) {
            if (param_3 == 0) {
                unsigned int val = *(unsigned int *)(param_2 + i * 4 + 0x34);
                if (val != 0xffffffff) {
                    func_02032634(param_1, idx, val);
                }
            } else {
                unsigned int val = *(unsigned int *)(param_2 + i * 4 + 0x44);
                if (val != 0xffffffff) {
                    func_02032634(param_1, idx, val);
                }
            }
        }
        i++;
    } while (i < 2);
    *(unsigned int *)(param_2 + 0x84) = (*(unsigned int *)(param_2 + 0x84) & 0xfffffffe) | (param_3 != 0);
}
