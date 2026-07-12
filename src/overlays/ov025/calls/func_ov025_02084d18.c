/* Pack a 32-bit tag from the handle at global+0x96b0 and the low 9 bits of
 * param_1 (no empty-slot check; see func_ov008_02050f40 for the checked twin). */
extern int data_ov025_020b5744;

int func_ov025_02084d18(int param_1) {
    int g = *(int *)((char *)&data_ov025_020b5744 + 4);
    int index = param_1 & 0x1ff;
    int handle = *(int *)(g + 0x96b0);
    return (((handle + 0x8000) & 0xfffffc) << 7) | 0x80000000 | index;
}
