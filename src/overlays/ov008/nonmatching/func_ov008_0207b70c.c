/* NONMATCHING: register-allocation tie (twin of func_ov006_0204f9b0) -- ROM holds the option-
 * table global in r8, fallback string in r9; our mwcc swaps them. Menu label buffer fill. */
/* func_ov008_0207b70c -- fill a 4-row text buffer with the menu's option labels, ov008.
 * For each of 4 rows (0xb shorts apart), copies the corresponding option string from the option
 * table (base+0x154, 0xc0-byte stride) when the row is within the live option count (base+0x100),
 * or the empty/placeholder string (data_ov008_02090f24) for rows past the count. */
extern void func_020200e4(short *dst, short *src);   /* StrCopy16 */
extern short data_ov008_02090f24[];
extern int   data_ov008_02090bc4;

void func_ov008_0207b70c(short *dst) {
    short *fallback = data_ov008_02090f24;
    int i = 0;
    int off = 0;
    unsigned char count = *(unsigned char *)(data_ov008_02090bc4 + 0x100);
    do {
        if (i < (int)count) {
            func_020200e4(dst, (short *)(data_ov008_02090bc4 + 0x154 + off));
        } else {
            func_020200e4(dst, fallback);
        }
        i++;
        off += 0xc0;
        dst += 0xb;
    } while (i < 4);
}
