/* Return the minimum of func_ov008_02051244(i) over i in [0, count), seeded from
 * func_020235d0(0x2689, 3) (masked to u16) or the first element when the list is
 * non-empty. count = func_ov008_02051210(). */
extern int func_020235d0(int a, int b);
extern unsigned int func_ov008_02051210(void);
extern int func_ov008_02051244(unsigned int i);
unsigned int func_ov008_0205ae90(void) {
    unsigned int i;
    unsigned int count;
    unsigned int min;
    min = func_020235d0(0x2689, 3) & 0xffff;
    count = func_ov008_02051210();
    if (count != 0) {
        min = func_ov008_02051244(0);
    }
    for (i = 0; i < count; i = (i + 1) & 0xffff) {
        if ((int)min > func_ov008_02051244(i)) {
            min = func_ov008_02051244(i);
        }
    }
    return min;
}
