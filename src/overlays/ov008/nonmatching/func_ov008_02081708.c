/* PROVEN TIE (basic-block ordering + branch sense, same size): the ROM emits the
 * return-0 block *between* the range checks and the store block, branching to the
 * store with a positive `blt store`; mwcc build 139 places the store first and the
 * return-0 last, using `bge ret0`. Logically identical, unsteerable across if/&&/
 * goto rewrites. Kept here so the ov008 blob stays byte-exact. */
extern int data_ov008_02090fa4;

int func_ov008_02081708(int param_1, int param_2) {
    int g = *(int *)&data_ov008_02090fa4;
    if (g == 0) return 0;
    if (param_1 >= 0 && param_1 < 4) {
        *(int *)(g + param_1 * 4 + 0x9524) = param_2;
        return 1;
    }
    return 0;
}
