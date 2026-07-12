/* Return the signed status byte at (global + index + 0x95ae), or 1 when the
 * global object is null. */
extern int data_ov008_02090fa4;

int func_ov008_020816e0(int param_1) {
    int g = *(int *)&data_ov008_02090fa4;
    if (g != 0) return *(signed char *)(g + param_1 + 0x95ae);
    return 1;
}
