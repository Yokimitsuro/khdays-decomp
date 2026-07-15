/* func_ov107_020c1dac -- set the 4-bit sub-field (bits 2..5) of entry[idx].flags
 * (@obj+0x51, stride 0xc) to val, ov107. */
void func_ov107_020c1dac(char *obj, int idx, int val) {
    signed char *p = (signed char *)(obj + 0x51 + idx * 0xc);
    *p = (*p & ~0x3c) | (((signed char)val & 0xf) << 2);
}
