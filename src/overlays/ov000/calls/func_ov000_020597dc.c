/* func_ov000_020597dc -- fast-scroll the logo list down by up to 0xa rows, ov000. No-op
 * at the bottom (field[0]>=0x13) or while L/R are held (data_0204c18c & 0xc0). Advances
 * field[0]/field[1] by 0xa (clamped to 0x12), refreshing the display when it moves. */
extern unsigned short data_0204c18c;
extern void func_02033b78(int, int);
extern void func_ov000_02059d78(void);
void func_ov000_020597dc(short *s) {
    int old = s[0];
    if (old >= 0x13) return;
    if (data_0204c18c & 0xc0) return;
    if (old < 9) {
        s[0] = old + 0xa;
        s[1] += 0xa;
    } else {
        s[1] += 0x12 - old;
        s[0] = 0x12;
    }
    *(int *)((char *)s + 0x60) = 0;
    if (old != s[0]) {
        func_02033b78(0, 0);
    }
    func_ov000_02059d78();
}
