/* func_ov008_020599a4 -- ov008 menu "confirm" transition with a one-shot cue (id 0x35bd).
 * Resets two sub-widgets (func_ov008_02050e2c/020511c8), toggles two others
 * (func_ov008_02050fe0(1)/02051010(0)); if cue 0x35bd is not already active
 * (func_02023588), arm it: func_ov008_02051168(0x1e,1,1), trigger func_020235a8(0x35bd) and
 * advance to step 4 (func_ov008_02050a08); otherwise just set the active slot. Fires the UI
 * event func_02033b78(0,1) at the end. */
extern void func_ov008_02050e2c(int a);
extern void func_ov008_020511c8(int a);
extern void func_ov008_02050fe0(int a);
extern void func_ov008_02051010(int a);
extern int  func_02023588(int cue);
extern void func_ov008_02051168(int a, int b, int c);
extern void func_020235a8(int cue);
extern void func_ov008_02050a08(int step);
extern void func_ov008_02050970(int a, int b);
extern void func_02033b78(int a, int b);

void func_ov008_020599a4(void) {
    func_ov008_02050e2c(0);
    func_ov008_020511c8(0);
    func_ov008_02050fe0(1);
    func_ov008_02051010(0);
    if (func_02023588(0x35bd) == 0) {
        func_ov008_02051168(0x1e, 1, 1);
        func_020235a8(0x35bd);
        func_ov008_02050a08(4);
    } else {
        func_ov008_02050970(1, -1);
    }
    func_02033b78(0, 1);
}
