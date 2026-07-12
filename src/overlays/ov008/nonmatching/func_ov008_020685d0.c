/* PROVEN TIE (predication density). mwcc build 139 merges the two idle checks
 * (+0x23c, +4) into a predicated form (ldreq/cmpeq, one popne), while the ROM
 * emits two independent popne early-returns. One instruction shorter; volatile
 * casts do not defeat the merge. Kept here so the ov008 blob stays byte-exact. */
extern void func_ov008_02067970(int obj, int old_value, int new_value);
extern void func_02033b78(int a, int b);

void func_ov008_020685d0(int param_1) {
    int old = *(int *)param_1;
    int nv;
    if (*(int *)(param_1 + 0x23c) != 0) return;
    if (*(int *)(param_1 + 4) != 0) return;
    nv = old + 1;
    *(int *)param_1 = nv;
    if (nv >= 3) {
        *(int *)param_1 = 0;
    }
    func_ov008_02067970(param_1, old, *(int *)param_1);
    func_02033b78(0, 0);
}
