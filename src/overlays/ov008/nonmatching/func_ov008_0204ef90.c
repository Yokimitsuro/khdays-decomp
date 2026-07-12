/* PROVEN TIE (strength reduction) - twin of func_ov008_0204ef30 for slots 3..6.
 * Same walking-i*4 vs index-recompute induction tie. Kept here so the ov008 blob
 * stays byte-exact. */
extern void MIi_CpuClear16(int data, void *dest, unsigned int size);
extern int data_ov008_02090f04;

void func_ov008_0204ef90(void) {
    int i;
    for (i = 3; i <= 6; i++) {
        int g = *(int *)((char *)&data_ov008_02090f04 + 4);
        MIi_CpuClear16(0, *(void **)(g + i * 4 + 0x95a4), *(int *)(g + 0x95d0) << 6);
        *(unsigned char *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x963c) |= 1 << i;
    }
}
