/* func_ov005_020570d0 -- clear the entry's 0x600-byte work area, ov005. Resolves the
 * area via func_ov005_0205708c(sel, 0) then 16-bit clears it. */
extern void *func_ov005_0205708c(int sel, int);
extern void MIi_CpuClear16(int val, void *dst, int size);
void func_ov005_020570d0(int sel) {
    void *area = func_ov005_0205708c(sel, 0);
    MIi_CpuClear16(0, area, 0x600);
}
