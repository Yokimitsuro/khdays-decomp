/* func_ov025_0208c314 -- ov008 menu "confirm" transition with a one-shot cue (id 0x35bd).
 * Resets two sub-widgets (func_ov025_02084c54/020511c8), toggles two others
 * (func_ov025_02084df0(1)/02051010(0)); if cue 0x35bd is not already active
 * (func_02023588), arm it: func_ov025_02084f78(0x1e,1,1), trigger func_020235a8(0x35bd) and
 * advance to step 4 (func_ov025_02084830); otherwise just set the active slot. Fires the UI
 * event func_02033b78(0,1) at the end. */
extern void func_ov025_02084c54(int a);
extern void func_ov025_02084fd8(int a);
extern void func_ov025_02084df0(int a);
extern void func_ov025_02084e20(int a);
extern int  func_02023588(int cue);
extern void func_ov025_02084f78(int a, int b, int c);
extern void func_020235a8(int cue);
extern void func_ov025_02084830(int step);
extern void func_ov025_02084798(int a, int b);
extern void func_02033b78(int a, int b);

void func_ov025_0208c314(void) {
    func_ov025_02084c54(0);
    func_ov025_02084fd8(0);
    func_ov025_02084df0(1);
    func_ov025_02084e20(0);
    if (func_02023588(0x35bd) == 0) {
        func_ov025_02084f78(0x1e, 1, 1);
        func_020235a8(0x35bd);
        func_ov025_02084830(4);
    } else {
        func_ov025_02084798(1, -1);
    }
    func_02033b78(0, 1);
}
