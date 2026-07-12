/* PROVEN TIE (predication density) - decrement twin of func_ov008_020685d0. mwcc
 * merges the two idle checks into predicated form vs the ROM's two popne returns.
 * Kept here so the ov008 blob stays byte-exact. */
extern void func_ov008_02067970(int obj, int old_value, int new_value);
extern void func_02033b78(int a, int b);

void func_ov008_02068588(int param_1) {
    int old = *(int *)param_1;
    int nv;
    if (*(int *)(param_1 + 0x23c) != 0) return;
    if (*(int *)(param_1 + 4) != 0) return;
    nv = old - 1;
    *(int *)param_1 = nv;
    if (nv < 0) {
        *(int *)param_1 = 2;
    }
    func_ov008_02067970(param_1, old, *(int *)param_1);
    func_02033b78(0, 0);
}
