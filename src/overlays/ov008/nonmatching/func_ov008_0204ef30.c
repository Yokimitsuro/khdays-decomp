/* PROVEN TIE (strength reduction). Size and semantics match, but mwcc build 139
 * strength-reduces the per-slot index g+i*4+0x95a4 into a walking i*4 register
 * (or, with a base-const subscript, splits the constant differently), while the
 * ROM recomputes `add r1,g,i,lsl#2; add #0x9000; ldr [+0x5a4]`. Same induction
 * class as func_ov008_020830c8. Kept here so the ov008 blob stays byte-exact. */
extern void MIi_CpuClear16(int data, void *dest, unsigned int size);
extern int data_ov008_02090f04;

void func_ov008_0204ef30(void) {
    int i;
    for (i = 0; i <= 2; i++) {
        int g = *(int *)((char *)&data_ov008_02090f04 + 4);
        MIi_CpuClear16(0, *(void **)(g + i * 4 + 0x95a4), *(int *)(g + 0x95d0) << 6);
        *(unsigned char *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x963c) |= 1 << i;
    }
}
