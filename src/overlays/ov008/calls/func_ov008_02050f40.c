/* Pack a 32-bit tag from the handle stored at global+0x96b4 and the low 9 bits
 * of param_1: bit31 set, handle (rounded, masked) in bits 7.., index in bits 0-8.
 * Returns 0 when the handle slot is empty. */
extern int data_ov008_02090f04;

int func_ov008_02050f40(int param_1) {
    int g = *(int *)((char *)&data_ov008_02090f04 + 4);
    int handle = *(int *)(g + 0x96b4);
    if (handle == 0) return 0;
    return (((handle + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (param_1 & 0x1ff);
}
