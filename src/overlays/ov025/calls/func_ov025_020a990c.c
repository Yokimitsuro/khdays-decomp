/* Return the minimum of func_ov025_02085020(i) over i in [0, count), seeded from
 * func_020235d0(0x2689, 3) (masked to u16) or the first element when the list is
 * non-empty. count = func_ov025_02085008(). */
extern int func_020235d0(int a, int b);
extern unsigned int func_ov025_02085008(void);
extern int func_ov025_02085020(unsigned int i);
unsigned int func_ov025_020a990c(void) {
    unsigned int i;
    unsigned int count;
    unsigned int min;
    min = func_020235d0(0x2689, 3) & 0xffff;
    count = func_ov025_02085008();
    if (count != 0) {
        min = func_ov025_02085020(0);
    }
    for (i = 0; i < count; i = (i + 1) & 0xffff) {
        if ((int)min > func_ov025_02085020(i)) {
            min = func_ov025_02085020(i);
        }
    }
    return min;
}
