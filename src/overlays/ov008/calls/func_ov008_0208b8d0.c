/* Narrows one 0x40-byte table row into the packed 0x20-byte record the UI uses.
 * In mode 2 the twelfth field is a fixed-point value: its integer part goes into the spare byte
 * at +0x13 and the slot at +0x18 gets the fixed marker instead. */
void func_ov008_0208b8d0(char *out, const int *table, int mode, int index) {
    const char *row = (const char *)table + index * 0x40;
    out[0] = (char)*(const int *)row;
    out[1] = (char)*(const int *)(row + 4);
    *(short *)(out + 2) = (short)*(const int *)(row + 8);
    *(short *)(out + 4) = (short)*(const int *)(row + 0xc);
    *(short *)(out + 6) = (short)*(const int *)(row + 0x10);
    *(int *)(out + 8) = *(const int *)(row + 0x14);
    *(short *)(out + 0xc) = (short)*(const int *)(row + 0x18);
    *(short *)(out + 0xe) = (short)*(const int *)(row + 0x1c);
    out[0x10] = (char)*(const int *)(row + 0x20);
    out[0x11] = (char)*(const int *)(row + 0x24);
    out[0x12] = (char)*(const int *)(row + 0x28);
    *(int *)(out + 0x14) = *(const int *)(row + 0x2c);
    if (mode != 2) {
        *(short *)(out + 0x18) = (short)*(const int *)(row + 0x30);
        row += 0x34;
    } else {
        out[0x13] = (char)(*(const int *)(row + 0x30) >> 12);
        row += 0x34;
        *(short *)(out + 0x18) = 0xb33;
    }
    *(short *)(out + 0x1a) = (short)*(const int *)row;
    *(short *)(out + 0x1c) = (short)*(const int *)(row + 4);
    *(short *)(out + 0x1e) = (short)*(const int *)(row + 8);
}
