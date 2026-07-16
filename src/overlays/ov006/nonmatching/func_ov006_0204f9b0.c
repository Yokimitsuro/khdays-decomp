/* NONMATCHING: structurally byte-exact (108B, correct pool order) except a register-allocation
 * tie -- the ROM holds the option-table global address in r8 and the fallback string in r9, where
 * our mwcc swaps them (r9/r4). Only register numbers differ. Title menu-label buffer fill. */
/* func_ov006_0204f9b0 -- fill a 4-row text buffer with the Mission Mode's menu labels, ov006.
 * For each of 4 rows (0xb shorts apart in the dst buffer), copies the corresponding option
 * string from the option table (base+0x154, 0xc0-byte stride) when the row is within the live
 * option count (base[0x100]); rows past the count get the empty/placeholder string
 * (data_ov006_020565e4). */
extern void func_020200e4(short *dst, short *src);   /* StrCopy16 */
extern short data_ov006_020565e4[];
extern int   data_ov006_020563d4;

void func_ov006_0204f9b0(short *dst) {
    short *fallback = data_ov006_020565e4;
    int i = 0;
    int off = 0;
    unsigned char count = *(unsigned char *)(data_ov006_020563d4 + 0x100);
    do {
        if (i < (int)count) {
            func_020200e4(dst, (short *)(data_ov006_020563d4 + 0x154 + off));
        } else {
            func_020200e4(dst, fallback);
        }
        i++;
        off += 0xc0;
        dst += 0xb;
    } while (i < 4);
}
