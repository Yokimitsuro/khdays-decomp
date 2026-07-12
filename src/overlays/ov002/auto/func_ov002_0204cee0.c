/*
 * Toggle flag bit 0x200 in the object's status word at (*(param_1+0x20))+0x38:
 * set it when param_2 is nonzero, clear it otherwise (predicated orr/bic on a
 * single load/store).
 */
void func_ov002_0204cee0(int param_1, int param_2) {
    int *flags = (int *)(*(int *)(param_1 + 0x20) + 0x38);

    if (param_2 != 0) {
        *flags |= 0x200;
    } else {
        *flags &= ~0x200;
    }
}
