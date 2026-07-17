/* NONMATCHING: register-allocation tie -- the ROM keeps pos in r0 and lim in r2, mwcc swaps them
 * (span matches in r1 either way). Neither declaration order (pos/span/lim vs span/pos/lim)
 * reproduces the ROM's choice; the two values are symmetric. */
/* func_ov008_02077908 -- scroll the mission list by param_2 and push the resulting bar position.
 * Clamps the offset (obj+0x168) to [-0x40, span-0x40], where span = (rowCount-0xc)*8 for the
 * current page (obj + obj[1]*4 + 0x144); then maps it through func_02020400 into the bar. */
extern int  func_02020400(int a, int b);
extern void func_ov008_02074758(int obj, int bar);

void func_ov008_02077908(int param_1, int param_2) {
    int pos = *(int *)(param_1 + 0x168) + param_2;
    int span = (*(int *)(param_1 + *(int *)(param_1 + 4) * 4 + 0x144) - 0xc) * 8;
    int lim = span - 0x40;
    *(int *)(param_1 + 0x168) = pos;
    if (pos > lim) {
        *(int *)(param_1 + 0x168) = lim;
    }
    if (*(int *)(param_1 + 0x168) < -0x40) {
        *(int *)(param_1 + 0x168) = -0x40;
    }
    func_ov008_02074758(param_1,
        func_02020400((0x60 - *(int *)(param_1 + 0x164)) * (*(int *)(param_1 + 0x168) + 0x40), span));
}
