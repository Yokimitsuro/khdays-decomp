/* func_ov000_02059680 -- logo scroller step (reverse), ov000.
 * NONMATCHING: 1-instruction constant-sharing tie. The retail build keeps 0x1b in a
 * register (from field[1]=0x1b) and derives field[0]=0x1b-9 via `sub r2,#9`; our mwcc
 * emits a fresh `mov #0x12`. Same size, same logic. Kept for the PC port.
 *
 * Counts field[1] down; on underflow wraps it to 0x1b and advances field[0] (unless
 * near the end), then clamps field[0] to field[1]; refreshes the display. */
extern void func_02033b78(int, int);
extern void func_ov000_02059d78(void);
void func_ov000_02059680(short *s) {
    s[1]--;
    if (s[1] < 0) {
        s[1] = 0x1b;
        if (s[0] + 0xa <= 0x1b) {
            s[0] = 0x12;
            *(int *)((char *)s + 0x60) = 0;
        }
    }
    if (s[1] < s[0]) {
        s[0] = s[1];
        *(int *)((char *)s + 0x60) = 0;
    }
    func_02033b78(0, 0);
    func_ov000_02059d78();
}
