/* Build a 4-bit mask: bit i is set when slot i exists and its first word is
 * nonzero, for i in 0..3. */
extern int func_020315c0(int index);

int func_ov008_0204ed98(void) {
    unsigned short mask = 0;
    int i;
    for (i = 0; i < 4; i++) {
        int *p = (int *)func_020315c0(i);
        if (p != 0 && *p != 0) {
            mask = (unsigned short)(mask | (1 << i));
        }
    }
    return mask;
}
