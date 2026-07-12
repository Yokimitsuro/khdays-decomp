/* Build a 4-bit mask: bit i is set when slot i exists and its byte at +3 equals
 * param_1, for i in 0..3. Twin of func_ov008_0204ed98. */
extern int func_ov008_0204ecd8(int index);

int func_ov008_0204eddc(int param_1) {
    unsigned short mask = 0;
    int i;
    for (i = 0; i < 4; i++) {
        int p = func_ov008_0204ecd8(i);
        if (p != 0 && *(unsigned char *)(p + 3) == param_1) {
            mask = (unsigned short)(mask | (1 << i));
        }
    }
    return mask;
}
