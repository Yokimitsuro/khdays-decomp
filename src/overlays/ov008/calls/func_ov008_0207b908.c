/* When the global is mid key-sharing (word at +0x4e8 nonzero), set the low flag
 * bit at +0x4ad and store param_1 at +0x4ae; always flag the ready word at +0x4f4.
 * The global pointer is reloaded after each store (no strict aliasing). */
extern int data_ov008_02090f24;

void func_ov008_0207b908(int param_1) {
    int g = *(int *)&data_ov008_02090f24;
    if (*(int *)(g + 0x4e8) != 0) {
        *(unsigned char *)(g + 0x4ad) = (*(unsigned char *)(g + 0x4ad) & ~1) | 1;
        *(unsigned char *)(*(int *)&data_ov008_02090f24 + 0x4ae) = param_1;
    }
    *(int *)(*(int *)&data_ov008_02090f24 + 0x4f4) = 1;
}
