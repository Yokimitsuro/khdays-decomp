extern int func_020235d0(int query, int kind);
extern int func_020235e8(int query, int kind, int value);
extern int func_02023c40(void);

/* Advance the play-time counter (key 0x20b7) by 2, or 3 in the faster mode; when
 * it reaches the mode's cap (0x3b / 0x77) reset it to 0 and report a rollover
 * (return 1), otherwise store the new value and return 0. */
int func_ov019_0207fcdc(void) {
    int t = func_020235d0(0x20b7, 8);
    int mode = func_020235d0(0x82 << 6, 5);
    int inc;

    if (func_02023c40() == 1) {
        inc = 3;
    } else {
        inc = 2;
    }
    t = t + inc;
    if (mode == 1) {
        if (t >= 0x3b) {
            func_020235e8(0x20b7, 8, 0);
            return 1;
        }
    } else {
        if (t >= 0x77) {
            func_020235e8(0x20b7, 8, 0);
            return 1;
        }
    }
    func_020235e8(0x20b7, 8, (unsigned short)t);
    return 0;
}
