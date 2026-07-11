/* Classify the halfword at *p by its top two bits (0xc000): 0 -> 0,
 * 0x4000 -> +(low5), 0x8000 -> -(low5), 0xc000 -> 0. */
int func_02005760(volatile unsigned short *p) {
    unsigned short top = *p & 0xc000;
    if (top == 0) return 0;
    if (top == 0x4000) return *p & 0x1f;
    if (top == 0x8000) return -(*p & 0x1f);
    return 0;
}
